//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#ifndef DateH
#define DateH

//---------------------------------------------------------------------------
//Date: class declaration
//---------------------------------------------------------------------------
//microsoft header and library includes
#include <iomanip>
#include <sstream>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
//our header includes
#include "Constants.h"
//removed using namespace std to prevent namespace pollution
using std::ostream;
using std::istream;
using std::ostringstream;
using std::setfill;
using std::setw;
//typedef of our DateTime struct
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

class Date //Date class
{
public:
	Date();								//default constructor
	Date( int, int, int);				//constructor

	int										getDay( void ) const; //return a data member value, day_
	int										getMonth( void ) const; //return a data member value, month_
	int										getYear( void ) const;	//return a data member value, year_
	DateTime								getDate( void ) const; // returns DateTime instance
	void									setDate( int, int, int ); //set new values for date
    static const							Date currentDate( void ); //return the current date

	static bool								isValidDate( const Date date );
	bool									isValid( const Date date ) const;

	string									toFormattedString( void ) const ;	//return date as formatted string ("DD/MM/YYYY")

	ostream& putDataInStream( ostream& os) const;	//send Date info into an output stream
	istream& getDataFromStream( istream& is);		//receive Date info from an input stream

	bool									operator==( const Date& d) const; //true if (*this == d)
	bool									operator!=( const Date& d) const; //true if (*this != d)
	bool									operator<( const Date& d) const; //true if (*this < d)  (strictly earlier)
	bool									operator<=( const Date &d ) const; //true if (*this <= d)
	bool									operator>( const Date &d) const; //true if (*this > d)
	bool									operator>=( const Date &d ) const; //true if (*this >= d)
	DateTime&								operator>>( DateTime &dateTime ) const;

private: //private member instances
	DateTime								dateTime_;

};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const Date&);	//output operator
istream& operator>>( istream&, Date&);	//input operator

#endif
