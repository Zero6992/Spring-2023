import discord
from discord.ext import tasks
from datetime import datetime
from query_whisper import get_whisper_updates, WhisperState

class MyClient(discord.Client):
    def __init__(self) -> None:
        intents = discord.Intents.default()
        intents.guilds = True
        intents.messages = True
        super().__init__(intents=intents)

        self.channel_list = []

    async def on_ready(self):
        self.update_channel_list.start()
        self.get_and_update_whisper_updates.start()
        self.send_earmings_messages.start()

    @tasks.loop(seconds=600)
    async def get_and_update_whisper_updates(self):
        tickers = [channel.name.split('-')[0] for channel in self.channel_list]
        whisper_updates = await get_whisper_updates(tickers)
        for channel in self.channel_list:
            for whisper, _ in whisper_updates.items():
                if whisper.ticker == channel.name.split('-')[0]:
                    whisper.last_price = round(float(whisper.last_price))
                    new_channel_name = f"{whisper.ticker}-{whisper.last_price}-usd"
                    try:
                        await channel.edit(name=new_channel_name)
                        print(f"Successfully updated channel name to: {new_channel_name} at {datetime.now()}")
                    except Exception as e:
                        print(f"Failed to update channel name or send message: {str(e)}")

    @tasks.loop(hours=168)
    async def send_earmings_messages(self):
        tickers = [channel.name.split('-')[0] for channel in self.channel_list]
        whisper_updates = await get_whisper_updates(tickers)
        for channel in self.channel_list:
            for whisper, _ in whisper_updates.items():
                if whisper.ticker == channel.name.split('-')[0]:
                    try:
                        await self.send_whisper_info(channel, whisper)
                    except Exception as e:
                        print(f"Failed to send message: {str(e)}")

    async def send_whisper_info(self, channel, whisper):
        earnings_date = whisper.earnings_date.strftime('%Y-%m-%d')
        earnings_post_market_sign = "⭕" if whisper.is_earnings_post_market else "❌"
        await channel.send(f"""
```
current earnings state: {WhisperState(whisper.current_state).name}
earnings date: {earnings_date}
earings post market: {earnings_post_market_sign}
```
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
    @get_and_update_whisper_updates.before_loop
    async def before_update_channel_list(self):
        await self.wait_until_ready()

client = MyClient()
client.run('MTA1MDM2MjczNjE1NDAwNTU0NA.GhKuTJ.C2T3A3D8XDKcoAgAKHGqQG-7QgfVGjy_nQbH1M')
