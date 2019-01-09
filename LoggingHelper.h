#ifndef _LOGGING_HELPER_
#define _LOGGING_HELPER_

#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <sys/stat.h>
#include <map>

#include "Trader.h"

using namespace std;

const string logPathBase = "logs/";
const string logActionFilePath = "TradingLog.txt";
const string logErrorFilePath = logPathBase + "ErrorLog.out";
const string logDailyValuePath = logPathBase + "DailyValueLog.csv";

class LoggingHelper
{
    public:
        static bool LogAction(string message);

        static bool LogError(string message);
        
        static bool LogDailyValue(Trader trader);
        
    private:
        LoggingHelper();

        static string getMarketValueString(Trader trader);

        static string getDateTimeString();
        
        static string getDateString();
};


#endif
