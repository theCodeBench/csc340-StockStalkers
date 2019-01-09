#include "LoggingHelper.h"

string doubleToString(double value);

bool LoggingHelper::LogAction(string message)
{
    ofstream outFile(logActionFilePath, ios::app);
    if(!outFile.is_open())
    {
        return false;
    }

    string log = "[" + getDateTimeString() + "] " + message;   

    outFile << log << endl;

    outFile.close();

    return true;
}

bool LoggingHelper::LogError(string message)
{
    mkdir("logs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    ofstream outFile(logErrorFilePath, ios::app);
    if(!outFile.is_open())
    {
        return false;
    }

    string log = "[" + getDateTimeString() + "] " + message;   

    outFile << log << endl;
    outFile.close();

    return true;
}

bool LoggingHelper::LogDailyValue(Trader trader)
{
    mkdir("logs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    ofstream outFile(logDailyValuePath, ios::app);
    if(!outFile.is_open())
    {
        return false;
    }

    string log = getDateString() + "," + doubleToString(trader.getAccountValue()) + "," + getMarketValueString(trader);

    outFile << log << endl;
    outFile.close();
    
    return true;    
}

string LoggingHelper::getDateTimeString()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d/%m/%Y %I:%M:%S",timeinfo);
    string datestring(buffer);

    return datestring;
}

string LoggingHelper::getMarketValueString(Trader trader)
{
    map<string, Stock> stocks = trader.getAvailablePositions();
    double sum = 0;

    for(auto stockPair : stocks)
    {
        sum += stockPair.second.h_end[1];
    }

    return doubleToString(sum);
}

string LoggingHelper::getDateString()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d/%m/%Y",timeinfo);
    string datestring(buffer);

    return datestring;
}


string doubleToString(double value)
{
    std::ostringstream stringstream;
    stringstream << value;
    std::string doubleString = stringstream.str();

    return doubleString;
}






