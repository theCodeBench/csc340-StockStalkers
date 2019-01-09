#include "analysis.h"

// Does a MACD, with 50 days for the short period and 200 days for the long period
double findsupp(Stock stock)
{
    double support = 0;
    double prev = 0;

    // Compare the 50 and 200 day sma's
    for (int price : stock.h_end)
    {
        if (prev == 0)
            support = price;

        if (price < support)
            support = price;

        if (price < prev)
            break;
        prev = price;
    }

    return support;
}

double findresist(Stock stock)
{
    double resist = 0;
    double prev = 100000000;

    // Compare the 50 and 200 day sma's
    for (int price : stock.h_end)
    {
        if (prev == 100000000)
            resist = price;

        if (price > resist)
            resist = price;

        if (price > prev)
            break;
        prev = price;
    }

    return resist;
}
