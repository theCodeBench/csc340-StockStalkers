#include "analysis.h"

// Does a MACD, with 50 days for the short period and 200 days for the long period
int macd50Over200(Stock stock)
{
    int ct = 0;
    double longSum = 0.0, shortSum = 0.0;

    // Compare the 50 and 200 day sma's
    for (double price : stock.h_end)
    {
        longSum += price;
        if (++ct < 50)
            shortSum += price;

        if (ct == 200) break;
    }
    longSum /= 200;
    shortSum /= 50;

    return shortSum - longSum;
}
