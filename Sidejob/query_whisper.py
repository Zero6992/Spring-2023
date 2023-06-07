import aiohttp
import asyncio
import requests
from bs4 import BeautifulSoup
import datetime
import json
from enum import Enum

class WhisperState(Enum):
    Unknown = 0
    Unconfirmed = 1
    Confirmed = 2

class Whisper:
    def __init__(self, id, ticker, last_update, current_state, earnings_date, is_earnings_post_market, last_price):
        self.id = id
        self.ticker = ticker
        self.last_update = last_update
        self.current_state = current_state
        self.earnings_date = earnings_date
        self.is_earnings_post_market = is_earnings_post_market
        self.last_price = last_price

def whisper_to_dict(whisper):
    return {
        'id': whisper.id,
        'ticker': whisper.ticker,
        'last_update': str(whisper.last_update),
        'current_state': whisper.current_state.value,
        'earnings_date': str(whisper.earnings_date),
        'earnings_post_market': whisper.is_earnings_post_market,
        'last_price': whisper.last_price[1:],
    }

async def get_whisper_updates(tickers):
    result = {}
    try:
        with open('data.json', 'r') as f:
            whispers = json.load(f)
    except FileNotFoundError:
        whispers = {}


    headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36'}
    async with aiohttp.ClientSession() as session:
        for ticker in tickers:
            try:
                async with session.get(f"https://www.earningswhispers.com/stocks/{ticker}", headers=headers) as r:
                    text = await r.text()
                    soup = BeautifulSoup(text, 'html.parser')
                context_string_data = None
                for script in soup.find_all("script"):
                    if "@context" in script.text:
                        context_string_data = json.loads(script.text)
                        break

                if context_string_data is None:
                    continue

                earnings_date = datetime.datetime.strptime(context_string_data['startDate'], "%Y-%m-%dT%H:%M%SZ") - datetime.timedelta(hours = 4)
                is_earnings_post_market =  True if earnings_date.hour < 12 else False
                price = soup.find(id="topquote").text
                confirmation = soup.find(id="epsconfirmed").get("class")[1]
                state = WhisperState.Unknown

                if "icon-no" in confirmation:
                    state = WhisperState.Unconfirmed
                elif "icon-checkmark" in confirmation:
                    state = WhisperState.Confirmed

                db_whisper = whispers.get(ticker, None)

                if db_whisper is None:
                    id = 0
                else:
                    id = db_whisper.get('id', 0)

                whisper = Whisper(id, ticker, datetime.datetime.now(), state, earnings_date, is_earnings_post_market, price)
                whispers[ticker] = whisper_to_dict(whisper)
                result[whisper] = db_whisper
                whisper.last_price = whisper.last_price[1:]
                print(f"Updated {whisper.ticker}: {whisper.last_price}, {whisper.earnings_date}, {whisper.current_state.name}")
            except Exception as e:
                print(f"Failed to update: {ticker} - {str(e)}")

    with open('data.json', 'w') as f:
        json.dump(whispers, f)

    return result

