'''
Usage: python3 GetStockData.py [filter_by_year]

If no arguments are provided, the script generates a new data/StockFile.txt with the last 20 years of historical data.

If a year is provided, the script generates a new data/StockFile.txt with only that year of historical data.
'''

import sys
import requests

FILE_PATH = 'data/StockFile20012002.txt'

URL = 'https://www.alphavantage.co/query'
ENDPOINT = 'TIME_SERIES_DAILY'
KEY = 'WUHTLV09M0HIZL4G'
OUTPUT_SIZE = 'full'  # 'full' (20 years) or 'compact' (100 days)
DATATYPE = 'csv'  # 'csv' or 'json'

SYMBOLS = (
    'aal','aapl','adbe','adi','adp','adsk','akam','algn','alxn','amat',
    'amgn','amzn','atvi','avgo','axp','ba','bidu','biib', 'bmrn','ca',
    'cat','celg','cern','chkp','chtr','cmcsa','cost','csco','csx','ctas',
    'ctrp','ctsh','ctxs','cvx','dis','disca','disck','dish','dltr','ea',
    'ebay','esrx','expe','fast','fb','fisv','fox','foxa','ge','gild',
    'goog','googl','gs','has','hd','holx','hsic','ibm','idxx','ilmn',
    'incy','intc','intu','isrg','jbht','jd','jnj','jpm','khc','klac',
    'ko','lbtya','lbtyk','lrcx','mar','mat','mcd','mchp','mdlz','meli',
    'mmm','mnst','mrk','msft','mu','mxim','myl','nclh','nflx','nke',
    'ntes','nvda','orly','payx','pcar','pcln','pfe','pg','pypl','qcom',
    'qvca','regn','rost','sbux','shpg','siri','stx','swks','symc','tmus',
    'trv','tsco','tsla','txn','ulta','unh','utx','v','viab','vod',
    'vrsk','vrtx','vz','wba','wdc','wmt','wynn','xlnx','xom','xray'
)

def get_params(symbol):
    return {'function': ENDPOINT, 'apikey': KEY, 'outputsize': OUTPUT_SIZE, 'datatype': DATATYPE, 'symbol': symbol}
    
def main():
    data = {}
    years_to_keep = sys.argv[1:] if len(sys.argv) > 1 else []  # Keep year(s) of data
    earliest_year = min(int(year) for year in years_to_keep)

    # Get data from the API
    for symbol in SYMBOLS:
        data[symbol] = requests.get(URL, params=get_params(symbol)).text.replace(',', ':').split('\r\n')[1:-1]

    # Skip records that we don't need to keep and reformat the data
    final_data = {key: [] for key in data.keys()}
    for symbol, symbol_data in data.items():
        for day_of_data in symbol_data:
            date, *the_rest = day_of_data.split(':')
            year = date[:4]

            if int(year) < earliest_year:
                break   # Don't need to keep processing years we don't want
            elif year not in years_to_keep:
                continue    # Don't need to process this record

            day = date[5:7]
            month = date[8:10]

            # Reformat the date and add it to the final data
            date = '{}/{}/{}:'.format(day, month, year)
            final_data[symbol].append(date + ':'.join(the_rest))

    # If a stock has no data, omit it from the final file
    final_data = {key: value for key, value in final_data.items() if value}

    # Write data to file
    with open(FILE_PATH, 'w') as f:
        for symbol, symbol_data in final_data.items():
            f.write('{0}{{\n{1}\n}}\n'.format(symbol, '\n'.join(symbol_data)))

if __name__ == '__main__':
    main()
