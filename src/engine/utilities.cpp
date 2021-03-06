#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>

#include "constants.h"

namespace Utilities
{

double changeCompoundingBasis(
    double rate, int origCompoundsPerYear, int newCompoundsPerYear)
{
    return 1.0 - pow(1.0 - rate, float(origCompoundsPerYear) / float(newCompoundsPerYear));
}

double calculatePayment(double balance, int amortTerm, double periodicRate)
{
    if (amortTerm == 0)
    {
        return periodicRate * balance;
    }
    else
    {
        return balance * periodicRate / (1 - pow(1 + periodicRate, -amortTerm));
    }
}

namespace DateTime
{
struct tm createTime(int year, int month, int day)
{
    struct tm date;
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    return date;
}

struct tm addDateInterval(struct tm date, int years, int months, int days)
{
    date.tm_year += years;
    date.tm_mon += months;
    date.tm_mday += days;
    mktime(&date);  // Automatically adjusts any out-of-bounds values
    return date;
}

struct tm fromYYYYMMDD(int date_YYYYMMDD)
{
    auto dateStr_YYYYYMMDD = std::to_string(date_YYYYMMDD);
    int year = std::stoi(dateStr_YYYYYMMDD.substr(0, 4));
    int month = std::stoi(dateStr_YYYYYMMDD.substr(4, 2));
    int day = std::stoi(dateStr_YYYYYMMDD.substr(6, 2));
    return createTime(year, month, day);
}

int toYYYYMMDD(struct tm date)
{
    char date_YYYYMMDD[9];
    strftime(date_YYYYMMDD, 9, "%Y%m%d", &date);
    return std::stoi(date_YYYYMMDD);
}

int daysBetween(struct tm date1, struct tm date2, bool inclusiveEnd = true)
{
    double secondsBetween = std::difftime(mktime(&date2), mktime(&date1));
    return int(secondsBetween / 60.0 / 60.0 / 24.0) + (inclusiveEnd ? 1 : 0);
}

int monthsBetween(struct tm date1, struct tm date2)
{
    // Ignores the day of month
    return (date2.tm_year - date1.tm_year) * 12 + date2.tm_mon - date1.tm_mon;
}

} // namespace DateTime

} // namespace Utilities
