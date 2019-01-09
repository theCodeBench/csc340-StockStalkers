#include "Trader.h"
#include "LoggingHelper.h"
#include "analysis.h"

// Compare function to sort map by values, then keys
bool cmp_values_keys(const std::pair<string, int>& a, const std::pair<string, int>& b)
{
    return a.second != b.second ? a.second < b.second : a.first < b.first;
}

int main()
{
    Trader trader("StockStalkers");

    double supp;
    double resist;
    int weight = 1000;

    vector<OpenPosition> openPositions = trader.getOpenPositions();
    map<string, Stock> stocks = trader.getAvailablePositions();

    map<string, int> scores;
    map<string, int> warningScores;  // Used for take profit and stop loss scoring

    std::ostringstream logString;  // Used for logging

    // Score each stock with various analysis methods
    for (auto stock : stocks)
    {
        scores[stock.first] = macd50Over200(stock.second) * weight;  // Increases the weight of this analysis
        scores[stock.first] += yearlyHighAnalysis(stock.second) * weight;

        warningScores[stock.first] = stosc(stock.second);

        // Ensure we have enought data to perform this calculation
        if (stock.second.h_end.size() > 0)
        {
            supp = findsupp(stock.second);
            resist = findresist(stock.second);

            if (stock.second.h_end.at(0) > resist)
                scores[stock.first] -= resist * weight;
            else if (stock.second.h_end.at(0) < supp)
                scores[stock.first] += supp * weight;
        }
    }

    // Make regular sells
    Stock stock;
    double sellPrice;
    for (auto openPosition : openPositions)
    {
        // Only attempt to sell things we actually own
        if (openPosition.type == OpenPosition::SellType::DEFAULT)
        {
            // Sell things with a negative score, in the amount of negative confidence
            if (scores[openPosition.symbol] < 0)
            {
                trader.sell(openPosition, openPosition.count);

                // Log our sell
                logString << "Sold " << openPosition.count << " of " << openPosition.symbol << ".";
                LoggingHelper::LogAction(logString.str());
                logString.str("");
            }
            // Prepare stop losses for stocks with a negative warning score
            else if (warningScores[openPosition.symbol] < 0)  // Stock is overbought
            {
                sellPrice = trader.singleStock(openPosition.symbol).h_end.at(0) * 0.95;
                trader.createStopLoss(openPosition, sellPrice);

                // Log our sell
                logString << "Created stop loss in amount " << openPosition.count << " of " << openPosition.symbol << " for $" << sellPrice << ".";
                LoggingHelper::LogAction(logString.str());
                logString.str("");
            }
        }
    }


    // Sort scores by positive confidence level, so we buy the best ones first
    vector<std::pair<string, int>> sortableScores;
    for (auto stock : scores)
        sortableScores.push_back(stock);
    std::sort(sortableScores.begin(), sortableScores.end(), cmp_values_keys);

    // Make buys
    int buyAmount;
    for (auto stock : sortableScores)
    {
        // Quit early if we have no cash
        if (trader.getAccountCash() < 10)
            break;
        // Buy things with a positive score, in the cash amount of positive confidence
        if (stock.second > 0)
        {
            buyAmount = stock.second / (int)trader.singleStock(stock.first).h_end[0] + 1;
            trader.buy(stock.first, buyAmount);

            // Log our buy
            logString << "Bought " << buyAmount << " of " << stock.first << ".";
            LoggingHelper::LogAction(logString.str());
            logString.str("");
        }
    }

    // Output our current open positions
    openPositions = trader.getOpenPositions();
    for (auto op : openPositions )
        cout << op.symbol << ":" << op.count << endl;

    // Output our current account cash and log it to csv
    cout << trader.getAccountValue() << endl << endl;
    LoggingHelper::LogDailyValue(trader);

    return 0;
}
