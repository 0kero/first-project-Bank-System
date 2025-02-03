#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <vector>
#include <iomanip>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
	short _day;
	short _month;
	short _year;

    time_t timenowsecond = time(0);
    tm* now = localtime(&timenowsecond);

	static string _MonthName(short month)
	{
		string months[13] = { "","Jan", "Feb", "Mar","Apr", "May", "Jun","Jul", "Aug", "Sep","Oct", "Nov", "Dec" };
		return months[month];
	}
	enum _enCompareDate { before = -1, Equal, after };
	static _enCompareDate _CompareDate(clsDate date1, clsDate date2)
	{
		if (IsDateBeforeDate2(date1, date2))
		{
			return _enCompareDate::before;
		}
		else if (IsDateEqualDate2(date1, date2))
		{
			return _enCompareDate::Equal;
		}
		return _enCompareDate::after;
	}


public:

	//those are constructors for this class
	clsDate()
	{
		this->_day = now->tm_mday;
		this->_month = now->tm_mon + 1;
		this->_year = now->tm_year + 1900;
	}
	clsDate(string date)
	{
		vector <string>seperatethedate = clsString::Split(date, "/");
		_day = stoi(seperatethedate[0]);
		_month = stoi(seperatethedate[1]);
		_year = stoi(seperatethedate[2]);
	}
	clsDate(short day,short month,short year)
	{
		this->_day = day;
		this->_month = month;
		this->_year = year;
	}
	clsDate(short days, short year)
	{
		clsDate date = DayOrderInYearToDate(days, year);
		_day = date._day;
		_month = date._month;
		_year = date._year;
	}

	//here are set and get properties
	void setDay(short day)
	{
		this->_day = day;
	}
	short getDay()
	{
		return _day;
	}
	_declspec(property(get = getDay, put = setDay))short Day;

	void setMonth(short month)
	{
		this->_month = month;
	}
	short getMonth()
	{
		return _month;
	}
	_declspec(property(get = getMonth, put = setMonth))short Month;
	
	void setYear(short year)
	{
		this->_year = year;
	}
	short getYear()
	{
		return _year;
	}
	_declspec(property(get = getYear, put = setYear))short Year;


	static bool IsLeapYear(short year)
	{
		return ((year % 400) == 0) || ((year % 4 == 0) && (year % 100 != 0));
	}
	bool IsLeapYear()
	{
		return IsLeapYear(_year);
	}

	static short NumberOfDaysInYear(short year)
	{
		return (IsLeapYear(year)) ? 366 : 365;
	}
	short NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(_year);
	}

	static short NumberOfHoursInYear(short year)
	{
		return NumberOfDaysInYear(year) * 24;
	}
	short NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(_year);
	}

	static int NumberOfMinutesInYear(short year)
	{
		return NumberOfHoursInYear(year) * 60;
	}
	int NumberOfMinutesInYear()
	{
		return NumberOfMinutesInYear(_year);
	}

	static int NumberOfSecondsInYear(short year)
	{
		return NumberOfMinutesInYear(year) * 60;
	}
	int NumberOfSecondsInYear()
	{
		return NumberOfSecondsInYear(_year);
	}

	static short NumberOfDaysInMonth(short month, short year)
	{
		return (month == 2) ? (IsLeapYear(year)) ? 29 : 28 :
			(month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31;

	}
	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_month, _year);
	}

	static short NumberOfHoursInMonth(short month, short year)
	{
		return NumberOfDaysInMonth(month, year) * 24;
	}
	short NumberOfHoursInMonth()
	{
		return NumberOfHoursInMonth(_month, _year);
	}

	static int NumberOfMinutesInMonth(short month, short year)
	{
		return NumberOfHoursInMonth(month, year) * 60;
	}
	int NumberOfMinutesInMonth()
	{
		return NumberOfMinutesInMonth(_month, _year);
	}

	static int NumberOfSecondsInMonth(short month, short year)
	{
		return NumberOfMinutesInMonth(month, year) * 60;
	}
	int NumberOfSecondsInMonth()
	{
		return NumberOfSecondsInMonth(_month, _year);
	}

	static clsDate DayOrderInYearToDate(short numberofdays, short year)
	{
		clsDate date;
		if (numberofdays == 366)
		{
			date._day = 31;
			date._month = 12;
			date._year = year;
		}
		short result = 0;
		for (short i = 1; i < 13; i++)
		{
			result += NumberOfDaysInMonth(i, year);
			if (numberofdays < result)
			{
				result -= NumberOfDaysInMonth(i, year);
				date._year = year;
				date._month = i;
				date._day = numberofdays - result;
				break;
			}
		}
		return date;
	}

	static short DayIndex(clsDate date)
	{
		short a, y, m;
		a = (14 - date._month) / 12;
		y =date._year - a;
		m = date._month + 12 * a - 2;
		return ((date._day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7);

	}
	short DayIndex()
	{
		return DayIndex(*this);
	}

	static void PrintDayInfo(clsDate date)
	{
		string days[7] = { "sunday","monday","tuesday","wednesday","thursday","friday","saturday" };
		short dayindex = DayIndex(date);
		cout << "Date: " << date._day << "/" << date._month << "/" << date._year << endl;
		cout << "Day order: " << dayindex << endl;
		cout << "Day name: " << days[dayindex] << endl;

	}
	void PrintDayInfo()
	{
		PrintDayInfo(*this);
	}

	static void PrintMonthCalendar(clsDate date)
	{
		short daysinmonth = NumberOfDaysInMonth(date._month, date._year);
		short dayindex = DayIndex(date);
		cout << "_______________" << _MonthName(date._month) << "_______________\n" << endl;
		cout << "Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;
		for (short i = 0; i < dayindex; i++)
			cout << "     ";

		for (short i = 1; i <= daysinmonth; i++)
		{

			cout << setw(3) << i << setw(2) << " ";

			if (++dayindex == 7)
			{
				cout << endl;
				dayindex = 0;
			}
		}
		cout << "\n";
		cout << "_________________________________" << endl;
	}
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(*this);
	}

	static void PrintYearCalendar(clsDate date)
	{
		cout << "_________________________________\n\n";
		cout << "\tCalendar - " << date._year << endl;
		cout << "_________________________________\n\n\n";

		for (date._month = 1; date._month <= 12; date._month++)
		{
			PrintMonthCalendar(date);

			cout << "\n";
		}
		cout << endl;
	}
	void PrintYearCalendar()
	{
		PrintYearCalendar(*this);
	}

	static short NumberOfDaysToSpecificDay(clsDate date)
	{
		short result = 0;
		for (short i = 1; i < date._month; i++)
		{
			result += NumberOfDaysInMonth(i, date._year);
		}
		return result + date._day;
	}
	short NumberOfDaysToSpecificDay()
	{
		return NumberOfDaysToSpecificDay(*this);
	}

	static clsDate AddDays(clsDate& date, int numberofdaystoadd)
	{
		short numofdays = NumberOfDaysToSpecificDay(date);
		numofdays += numberofdaystoadd;
		while (numofdays > 366)
		{
			numofdays -= NumberOfDaysInYear(date._year);
			date._year++;

		}

		date = DayOrderInYearToDate(numofdays,date._year);
		return date;
	}
	void AddDays(int numberofdaystoadd)
	{
		AddDays(*this, numberofdaystoadd);
	}

	static bool IsDateBeforeDate2(clsDate date1, clsDate date2)
	{
		if ((date1._year != date2._year))
			return  (date1._year < date2._year);

		return (NumberOfDaysToSpecificDay(date1) < NumberOfDaysToSpecificDay(date2));
	}
	bool IsDateBeforeDate2(clsDate date2)
	{
		return  IsDateBeforeDate2(*this, date2);
	}

	static bool IsDateEqualDate2(clsDate date1, clsDate date2)
	{
		return (date1._year == date2._year) ? ((date1._month == date2._month) ? ((date1._day == date2._day) ?
			true : false) : false) : false;
	}
	bool IsDateEqualDate2( clsDate date2)
	{
		return IsDateEqualDate2(*this, date2);
	}

	static bool IsDateAfterDate2(clsDate date1, clsDate date2)
	{
		return (!IsDateBeforeDate2(date1, date2) && !IsDateEqualDate2(date1, date2));
	}
	bool IsDateAfterDate2(clsDate date2)
	{
		return IsDateAfterDate2(*this, date2);
	}

	static bool IsLastDayInMonth(clsDate date)
	{
		return (date._day == NumberOfDaysInMonth(date._month, date._year));
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(clsDate date)
	{
		return (date._month == 12);
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(*this);
	}

	static clsDate IncreaseDateByOneDay(clsDate &date)
	{

		if (IsLastDayInMonth(date) && (IsLastMonthInYear(date)))
		{
			date._day = 1;
			date._month = 1;
			date._year++;
			return date;

		}
		if (IsLastDayInMonth(date))
		{
			date._day = 1;
			date._month++;
			return date;

		}
		else
			date._day++;
		return date;

	}
	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}

	static short CalculateTheDifferenceBetween2Dates(clsDate date1, clsDate date2)
	{
		short result = 0;
		if (IsDateBeforeDate2(date1, date2))
		{

			if (date1._year == date2._year)
			{
				return (NumberOfDaysToSpecificDay(date2) - NumberOfDaysToSpecificDay(date1));
			}
			else
			{
				result += NumberOfDaysToSpecificDay(date2);
				for (short i = date1._year + 1; i < date2._year; i++)
				{
					result += NumberOfDaysInYear(i);

				}
				result += (NumberOfDaysInYear(date1._year) - NumberOfDaysToSpecificDay(date1));
				return result;
			}


		}
		else
		{
			clsDate temp;
			temp = date1;
			date1 = date2;
			date2 = temp;

			return CalculateTheDifferenceBetween2Dates(date1, date2) * -1;
		}
	}
	short CalculateTheDifferenceBetween2Dates(clsDate date2)
	{
		return CalculateTheDifferenceBetween2Dates(*this, date2);
	}

	static int MyAgeInDays(clsDate dateofbirth)
	{
		//using default constructor sets the second date as today's date
		return CalculateTheDifferenceBetween2Dates(dateofbirth, clsDate());
	}

	static clsDate IncreaseDateByXDays(clsDate& date ,int days)
	{
		for (int i = 0; i < days; i++)
		{
			date = IncreaseDateByOneDay(date);;
		}
		return date;
	}
	void IncreaseDateByXDays(int days)
	{
		IncreaseDateByXDays(*this, days);
	}

	static clsDate IncreaseDateByOneWeek(clsDate &date)
	{
		for (int i = 0; i < 7; i++)
		{
			date = IncreaseDateByOneDay(date);
		}
		return date;
	}
	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks( clsDate &date, int weeks)
	{
		for (int i = 0; i < weeks; i++)
		{
			date = IncreaseDateByOneWeek(date);
		}
		return date;
	}
	void IncreaseDateByXWeeks(int weeks)
	{
		IncreaseDateByXWeeks(*this,weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate &date)
	{

		if (IsLastMonthInYear(date))
		{
			date._year++;
			date._month = 1;
		}
		else
		{
			date._month++;
		}
		short NumberOfDaysInCurrentMonth =
			NumberOfDaysInMonth(date._month, date._year);
		if (date._day > NumberOfDaysInCurrentMonth)
		{
			date._day = NumberOfDaysInCurrentMonth;
		}
		
		return date;
	}
	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths( clsDate &date, int months)
	{
		for (int i = 0; i < months; i++)
		{
			date = IncreaseDateByOneMonth(date);
		}
		return date;
	}
	void IncreaseDateByXMonths(int months)
	{
		IncreaseDateByXMonths(*this, months);
	}

	static clsDate IncreaseDateByOneYear(clsDate &date)
	{
		date._year++;
		return date;
	}
	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate &date,int years)
	{
		for (int i = 0; i < years; i++)
		{
			date = IncreaseDateByOneYear(date);
		}
		return date;
	}
	void IncreaseDateByXYears(int years)
	{
		IncreaseDateByXYears(*this, years);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate &date,int years)
	{
		date._year += years;
		return date;
	}
	void IncreaseDateByXYearsFaster(int years)
	{
		IncreaseDateByXYearsFaster(*this, years);
	}

	static clsDate IncreaseDateByOneDecade(clsDate &date)
	{
		date._year += 10;
		return date;
	}
	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades( clsDate& date,int decades)
	{
		for (int i = 0; i < decades; i++)
		{
			date = IncreaseDateByOneDecade(date);
		}
		return date;
	}
	void IncreaseDateByXDecades(int decades)
	{
		IncreaseDateByXDecades(*this, decades);
	}

	static clsDate IncreaseDateByXDecadesFaster(clsDate &date, int decades)
	{
		date._year += 10 * decades;
		return date;
	}
	void IncreaseDateByXDecadesFaster(int decades)
	{
		IncreaseDateByXDecadesFaster(*this, decades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate &date)
	{
		date._year += 100;
		return date;
	}
	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate &date)
	{
		date._year += 1000;
		return date;
	}
	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}


	static clsDate DecreaseDateByOneDay(clsDate& date)
	{
		if (date._day == 1 && date._month == 1)
		{
			date._year--;
			date._month = 12;
			date._day = 31;
			return date;
		}
		else if (date._day == 1)
		{
			date._month--;
			date._day = NumberOfDaysInMonth(date._year, date._month);
			return date;
		}
		else
		{
			date._day--;
			return date;
		}
	}
	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& date, int days)
	{
		for (int i = 0; i < days; i++)
		{
			date = DecreaseDateByOneDay(date);
		}
		return date;
	}
	void DecreaseDateByXDays(int days)
	{
		DecreaseDateByXDays(*this, days);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& date)
	{
		for (int i = 0; i < 7; i++)
		{
			date = DecreaseDateByOneDay(date);
		}
		return date;
	}
	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate& date, int weeks)
	{
		for (int i = 0; i < weeks; i++)
		{
			date = DecreaseDateByOneWeek(date);
		}
		return date;
	}
	void DecreaseDateByXWeeks(int weeks)
	{
		DecreaseDateByXWeeks(*this, weeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& date)
	{
		if (date._month == 1)
		{
			date._year--;
			date._month = 12;
		}
		else
		{
			date._month--;
		}
		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(date._month, date._year);
		if (date._day > NumberOfDaysInCurrentMonth)
		{
			date._day = NumberOfDaysInCurrentMonth;
		}
		return date;
	}
	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate& date, int months)
	{
		for (int i = 0; i < months; i++)
		{
			date = DecreaseDateByOneMonth(date);
		}
		return date;
	}
	void DecreaseDateByXMonths(int months)
	{
		DecreaseDateByXMonths(*this, months);
	}

	static clsDate DecreaseDateByOneYear(clsDate& date)
	{
		date._year--;
		if (date._month == 2 && IsLeapYear(date._year))
		{
			date._day = 29;
		}
		else if (date._month == 2 && !IsLeapYear(date._year))
		{
			date._day = 28;
		}
		return date;
	}
	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& date, int years)
	{
		for (int i = 0; i < years; i++)
		{
			date = DecreaseDateByOneYear(date);
		}
		return date;
	}
	void DecreaseDateByXYears(int years)
	{
		DecreaseDateByXYears(*this, years);
	}

	static clsDate DecreaseDateByXYearsFaster(clsDate& date, int years)
	{
		date._year -= years;
		if (date._month == 2 && IsLeapYear(date._year))
		{
			date._day = 29;
		}
		else if (date._month == 2 && !IsLeapYear(date._year))
		{
			date._day = 28;
		}
		return date;
	}
	void DecreaseDateByXYearsFaster(int years)
	{
		DecreaseDateByXYearsFaster(*this, years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& date)
	{
		date._year -= 10;
		return date;
	}
	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& date, int decades)
	{
		for (int i = 0; i < decades; i++)
		{
			date = DecreaseDateByOneDecade(date);
		}
		return date;
	}
	void DecreaseDateByXDecades(int decades)
	{
		DecreaseDateByXDecades(*this, decades);
	}

	static clsDate DecreaseDateByXDecadesFaster(clsDate& date, int decades)
	{
		date._year -= 10 * decades;
		return date;
	}
	void DecreaseDateByXDecadesFaster(int decades)
	{
		DecreaseDateByXDecadesFaster(*this, decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& date)
	{
		date._year -= 100;
		return date;
	}
	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& date)
	{
		date._year -= 1000;
		return date;
	}
	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate date)
	{
		return (DayIndex(date) == 6);
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate date)
	{
		return (DayIndex(date) == 5 || DayIndex(date) == 6);
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate date)
	{
		return !(IsWeekEnd(date));
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilEndOfWeek(clsDate date)
	{
		return 6 - (DayIndex(date));
	}
	short DaysUntilEndOfWeek()
	{
		return DaysUntilEndOfWeek(*this);
	}

	static short DaysUntilEndOfMonth(clsDate date)
	{
		return NumberOfDaysInMonth(date._month, date._year) - date._day;
	}
	short DaysUntilEndOfMonth()
	{
		return DaysUntilEndOfMonth(*this);
	}

	static short DaysUntilEndOfYear(clsDate date)
	{
		return NumberOfDaysInYear(date._year) - NumberOfDaysToSpecificDay(date);
	}
	short DaysUntilEndOfYear()
	{
		return DaysUntilEndOfYear(*this);
	}

	static short ActualVacationDays(clsDate date1, clsDate date2)
	{
		short counter = 0;
		while (IsDateBeforeDate2(date1, date2))
		{
			if (!IsWeekEnd(date1))
			{
				counter++;
			}
			date1 = IncreaseDateByOneDay(date1);
		}
		return counter;
	}
	short ActualVacationDays(clsDate date2)
	{
		return ActualVacationDays(*this, date2);
	}

	static clsDate ReturnDateAfterVacation(clsDate date, short vacationdays)
	{
		while (vacationdays > 0)
		{
			if (IsBusinessDay(date)) 
			{
				vacationdays--;
			}
			date = IncreaseDateByOneDay(date);  
		}
		return date;
	}
	clsDate ReturnDateAfterVacation(short vacationdays)
	{
		return ReturnDateAfterVacation(*this, vacationdays);
	}

	static void DateComparison(clsDate date1, clsDate date2)
	{
		_enCompareDate datecomparison = _CompareDate(date1, date2);
		switch (datecomparison)
		{
		case clsDate::before:
			cout << "date 1 is before date 2\n";
			break;
		case clsDate::Equal:
			cout << "date 1 is equal to date 2\n";
			break;
		case clsDate::after:
			cout << "date 1 is after date 2\n";
			break;
		default:
			break;
		}

	}
	void  DateComparison(clsDate date2)
	{
		DateComparison(*this, date2);
	}

	static bool IsValidDate(clsDate date)
	{
		return !(date._day < 1 || date._day > NumberOfDaysInMonth(date._month, date._year) || date._month > 12);
	}
	bool IsValidDate()
	{
		return IsValidDate(*this);
	}

	static clsDate GetSystemDate()
	{
		return clsDate();
	}
	static void Print(clsDate date)
	{
		cout << to_string(date._day) + "/" + to_string(date._month) + "/" + to_string(date._year) << endl;
	}
	void Print()
	{
		Print(*this);
	}

	static string DateObjectToString(clsDate date)
	{
		string datestring;
		datestring = to_string(date.Day) + "/" +
			to_string(date.Month) + "/" +
			to_string(date.Year);
		return datestring;
	}
    string DateObjectToString()
	{
		return DateObjectToString(*this);
	}
    string GetDateLogLine()
	{
		return DateObjectToString(clsDate()) + " - " +
			to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
	}
};

