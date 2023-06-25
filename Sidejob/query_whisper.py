import json
import datetime
import aiohttp
from bs4 import BeautifulSoup
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

async def update_last_price(tickers):
    result = {}

    headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36'}
    async with aiohttp.ClientSession() as session:
        for ticker in tickers:
            try:
                async with session.get(f"https://www.earningswhispers.com/stocks/{ticker}", headers=headers) as r:
                    text = await r.text()
                    soup = BeautifulSoup(text, 'html.parser')

                    # Update last price
                    price = soup.find(id="topquote").text[1:]  # Extract and remove dollar sign

                    # Retrieve previous whisper if it exists
                    try:
                        with open('data.json', 'r') as f:
                            whispers = json.load(f)
                    except FileNotFoundError:
                        whispers = {}
                    db_whisper = whispers.get(ticker, {})

                    # Create/update new whisper dict
                    whisper = {**db_whisper, 'last_update': datetime.datetime.now().isoformat(), 'last_price': price}

                    whispers[ticker] = whisper
                    result[ticker] = whisper
                    print(f"Updated {ticker}: {price}")
            except Exception as e:
                print(f"Failed to update: {ticker} - {str(e)}")

            with open('data.json', 'w') as f:
                json.dump(whispers, f)

    return result


async def update_other_info(tickers):
    result = {}

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
                    confirmation = soup.find(id="epsconfirmed").get("class")[1]
                    state = WhisperState.Unknown.value

                    if "icon-no" in confirmation:
                        state = WhisperState.Unconfirmed.value
                    elif "icon-checkmark" in confirmation:
                        state = WhisperState.Confirmed.value

                    # Retrieve previous whisper if it exists
                    try:
                        with open('data.json', 'r') as f:
                            whispers = json.load(f)
                    except FileNotFoundError:
                        whispers = {}
                    db_whisper = whispers.get(ticker, {})

                    # Create/update new whisper dict
                    whisper = {
                        **db_whisper,
                        'last_update': datetime.datetime.now().isoformat(),
                        'current_state': state,
                        'earnings_date': earnings_date.isoformat(),
                        'earnings_post_market': is_earnings_post_market
                    }
                    whispers[ticker] = whisper
                    result[ticker] = whisper
            except Exception as e:
                print(f"Failed to update: {ticker} - {str(e)}")

            with open('data.json', 'w') as f:
                json.dump(whispers, f)

    return result