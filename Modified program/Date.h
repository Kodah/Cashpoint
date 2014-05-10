//Pascale Vacher - March 14
//OOP Assignment Semester 2

#ifndef DateH
#define DateH

//---------------------------------------------------------------------------
//Date: class declaration
//---------------------------------------------------------------------------

#include <ctime>	// for date functions
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <list>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

#include "Constants.h"

using namespace std;

typedef struct DateTime
{
	int day;
	int month;
	int year;

	int second;
	int minute;
	int hour;

	DateTime() : day(1), month(1), year(2000),
		second(0), minute(0), hour(0)
	{
	}
} *PDATETIME, DATETIME;

class Date
{
public:
	Date();								//default constructor
	Date( int, int, int);				//constructor

	int getDay() const;					//return a data member value, day_
	int getMonth() const;				//return a data member value, month_
	int getYear() const;				//return a data member value, year_
	void setDate( int, int, int);		//set new values for date
    static const Date currentDate() ;   //return the current date

	static bool isValidDate( const Date date );
	bool isValid( const Date date ) const;

	string toFormattedString() const ;				//return date as formatted string ("DD/MM/YYYY")

	ostream& putDataInStream( ostream& os) const;	//send Date info into an output stream
	istream& getDataFromStream( istream& is);		//receive Date info from an input stream

	bool operator==( const Date& d) const;  	//true if (*this == d)
	bool operator!=( const Date& d) const;  	//true if (*this != d)
	bool operator<( const Date& d) const;		//true if (*this < d)  (strictly earlier)
	bool operator<=( const Date &d ) const;
	bool operator>( const Date &d) const;
	bool operator>=( const Date &d ) const;
	DateTime& operator>>( DateTime &dateTime ) const;

private:
	DateTime dateTime_;

};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const Date&);	//output operator
istream& operator>>( istream&, Date&);	//input operator

#endif
