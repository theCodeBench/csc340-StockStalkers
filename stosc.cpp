#include "analysis.h"

// %K = (Current Close - Lowest Low) / (Highest High - Lowest Low) * 100
// %D = 3-day SMA of %K
int stosc(Stock stock)
{
    double k1, k2, k3, d;

    if (stock.h_low.size() < 16 || stock.h_high.size() < 16 || stock.h_end.size() < 3)
        return 0;  // Not enough data to perform calculation, so return inconclusive

    double l1 = stock.h_low.at(2), l2 = stock.h_low.at(1), l3 = stock.h_low.at(0),
           h1 = stock.h_high.at(2), h2 = stock.h_high.at(1), h3 = stock.h_high.at(0);

    // Calculate the 3 lowest lows and highest highs over 3 14 day periods offset by 1 day
    for (int i = 0; i < 16; ++i)
    {
        if (stock.h_low.at(i) < l1 && i < 14)
            l1 = stock.h_low.at(i);
        if (stock.h_low.at(i) < l2 && i < 15)
            l2 = stock.h_low.at(i);
        if (stock.h_low.at(i) < l3)
            l3 = stock.h_low.at(i);

        if (stock.h_high.at(i) > h1 && i < 14)
            h1 = stock.h_high.at(i);
        if (stock.h_high.at(i) < h2 && i < 15)
            h2 = stock.h_high.at(i);
        if (stock.h_high.at(i) < h3)
            h3 = stock.h_high.at(i);
    }

    // Compute the 3 %k values
    k1 = (stock.h_end.at(2) - l1) / (h1 - l1) * 100;
    k2 = (stock.h_end.at(1) - l2) / (h2 - l2) * 100;
    k3 = (stock.h_end.at(0) - l3) / (h3 - l3) * 100;

    // Find the SMA of the %k values, %d
    d = (k1 + k2 + k3) / 3;

    // Calculate and return our confidence score
    if (d <= 20)  // Stock is oversold
        return d - 21;
    else if (d >= 80)  // Stock is overbought
        return d - 79;

    return 0;  // Inconclusive
}
