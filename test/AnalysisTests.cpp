#include "catch.hpp"
#include "../analysis.h"
#include <iostream>

using namespace std;

TEST_CASE("MACD")
{
    Trader trader("StockStalkers");

    auto stock = trader.singleStock("googl");

    REQUIRE(macd50Over200(stock) == 57);
}

TEST_CASE("YearlyHighAnalysis")
{
    Trader trader("StockStalkers");

    auto stock = trader.singleStock("googl");

    REQUIRE(yearlyHighAnalysis(stock) == -31);
}

TEST_CASE("STOSC")
{
    Trader trader("StockStalkers");

    auto stock = trader.singleStock("googl");

    REQUIRE(stosc(stock) == 12);
}

TEST_CASE("FindSupp")
{
    Trader trader("StockStalkers");

    auto stock = trader.singleStock("googl");

    REQUIRE(findsupp(stock) == 1053);
}

TEST_CASE("FindResist")
{
    Trader trader("StockStalkers");

    auto stock = trader.singleStock("googl");

    REQUIRE(findresist(stock) == 1055);
}