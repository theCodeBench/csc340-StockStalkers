#include "analysis.h"

int yearlyHighAnalysis(Stock stock) {
    if (stock.h_end.size() < 1)
        return 0;  // Not enough data, return inconclusive

	int high = stock.h_end.at(0), count = 0;

	// Find the high price of the last year
    for (auto end : stock.h_end)
    {
        if (end > high)
			high = end;

		if (++count == 260) break;  // Counts back a year, which is 260 work days
    }

	return stock.h_end.at(0) - high;
}
