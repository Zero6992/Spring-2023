import json
import discord
from discord.ext import tasks
from datetime import datetime
from query_whisper import update_last_price, update_other_info, dict_to_whisper, WhisperState

class MyClient(discord.Client):
    def __init__(self) -> None:
        intents = discord.Intents.default()
        intents.guilds = True
        intents.messages = True
        super().__init__(intents=intents)

        self.channel_list = []

    async def on_ready(self):
        self.update_channel_list.start()
        self.send_last_price.start()
        self.send_earmings_messages.start()

    @tasks.loop(seconds=600)
    async def send_last_price(self):
        tickers = [channel.name.split('-')[0] for channel in self.channel_list]
        whisper_updates = await update_last_price(tickers)
        for channel in self.channel_list:
            for ticker, whisper in whisper_updates.items():
                if ticker == channel.name.split('-')[0]:
                    whisper['last_price'] = round(float(whisper['last_price']))
                    new_channel_name = f"{ticker}-{whisper['last_price']}-usd"
                    try:
                        await channel.edit(name=new_channel_name)
                        print(f"Successfully updated channel name to: {new_channel_name} at {datetime.now()}")
                    except Exception as e:
                        print(f"Failed to update channel name or send message: {str(e)}")

    @tasks.loop(hours=24)
    async def send_earmings_messages(self):
        tickers = [channel.name.split('-')[0] for channel in self.channel_list]
        try:
            with open('data.json', 'r') as f:
                whispers = json.load(f)
        except FileNotFoundError:
            whispers = {}
        whisper_updates = await update_other_info(tickers)
        for channel in self.channel_list:
            for ticker, whisper in whisper_updates.items():
                if ticker == channel.name.split('-')[0]:
                    # Check if the current_state, earnings_date, or earnings_post_market has changed.
                    if whisper:
                            old_whisper = whispers.get(ticker, {})
                            if (
                                old_whisper.get('current_state', None) != whisper['current_state'] or
                                old_whisper.get('earnings_date', None) != whisper['earnings_date'] or
                                old_whisper.get('earnings_post_market', None) != whisper['earnings_post_market']
                            ):
                                try:
                                    await self.send_whisper_info(channel, whisper)
                                except Exception as e:
                                    print(f"Failed to send message: {str(e)}")

    async def send_whisper_info(self, channel, whisper):
        earnings_date = whisper['earnings_date'].replace('T', ' ')
        earnings_post_market_sign = "⭕" if whisper['earnings_post_market'] else "❌"
        await channel.send(f"""
### 💰 current earnings state: {WhisperState(whisper['current_state']).name}
### 📅 earnings date: {earnings_date}
### 📈 earings post market: {earnings_post_market_sign}
""")

    @tasks.loop(seconds=310)
    async def update_channel_list(self):
        self.channel_list = []
        for guild in self.guilds:
            for channel in guild.channels:
                if isinstance(channel, discord.TextChannel) and channel.category and channel.category.name[0].isdigit():
                    self.channel_list.append(channel)

    @update_channel_list.before_loop
    @send_earmings_messages.before_loop
    @send_last_price.before_loop
    async def before_update_channel_list(self):
        await self.wait_until_ready()

client = MyClient()
client.run('')
