//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#include "Date.h"

//---------------------------------------------------------------------------
//Date: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors
Date::Date() 						//default constructor
{
}

Date::Date( int d, int m, int y) 	//constructor
{
	dateTime_.day	= d;
	dateTime_.month = m;
	dateTime_.year	= y;
}

//____other public member functions
int Date::getDay( void ) const
{
	return dateTime_.day;
}

int Date::getMonth( void ) const
{
	return dateTime_.month;
}

int Date::getYear( void ) const
{
	return dateTime_.year;
}

DateTime Date::getDate( void ) const
{
	return dateTime_;
}

//checks to see if the date is after the creation date
//if it needs to be
bool Date::isValid( const Date creationDate ) const
{
	if( Date::isValidDate( *this ) &&
		*this >= creationDate && *this <= Date::currentDate() )
		return true;

	return false;
}

//checks to see if the date is a real date
//doesn't take leap years into account
bool Date::isValidDate( const Date date )
{
	if( date.dateTime_.day < 1 )
		return false;

	switch( date.dateTime_.month )
	{
	case JAN: case MAR: case MAY:
	case JUL: case AUG: case OCT:
	case DEC:
		if( date.dateTime_.day > 31 )
		   return false;

		break;

	case FEB:
		if( date.dateTime_.day > 28 )
			return false;

		break;

	case APR: case JUN: case SEPT:
	case NOV:
		if( date.dateTime_.day > 30 )
			return false;

		break;

	default:
		return false;
	}

	return true;
}

const Date Date::currentDate( void )
{	//returns the current date
	time_t now( time(0) );
	struct tm& t( *localtime(&now) );
    return Date( t.tm_mday, t.tm_mon + 1,  t.tm_year + 1900 );
}

void Date::setDate( const int d, const int m, const int y )
{
	dateTime_.day	= d;
	dateTime_.month = m;
	dateTime_.year	= y;
}

string Date::toFormattedString( void ) const
{
//return date formatted output ("DD/MM/YYYY")
	ostringstream os_date;
	os_date << setfill('0')
			<< setw(2) << dateTime_.day << "/"
			<< setw(2) << dateTime_.month << "/"
			<< setw(2) << dateTime_.year
			<< setfill(' ');

	return ( os_date.str() );
}

ostream& Date::putDataInStream( ostream& os ) const
{
//put (unformatted) date (D/M/Y) into an output stream
	os << setw(2) << dateTime_.day << "/";
	os << setw(2) << dateTime_.month << "/";
	os << setw(4) << dateTime_.year;

	return os;
}
istream& Date::getDataFromStream( istream& is )
{
//read in date from (unformatted) input stream ("DD/MM/YY")
	char ch;			//(any) colon field delimiter
	is >> dateTime_.day >> ch >> dateTime_.month >> ch >> dateTime_.year;
	return is;
}

//---------------------------------------------------------------------------
//overloaded operator functions
//---------------------------------------------------------------------------

bool Date::operator==( const Date& d ) const
{ //comparison operator
	return
		(( dateTime_.day == d.dateTime_.day) &&
		 ( dateTime_.month == d.dateTime_.month) &&
		 ( dateTime_.year == d.dateTime_.year));
}

bool Date::operator!=( const Date& d ) const
{ //user existing to determing !=
	return ( !(*this == d) );
}
bool Date::operator<( const Date& d ) const
{ //NEW
//true if (strictly) earlier than d (i.e., *this < d)
	return ( ( dateTime_.year < d.dateTime_.year)
	     || (( dateTime_.year == d.dateTime_.year)
			&& (dateTime_.month < d.dateTime_.month) )
	     || (( dateTime_.year == d.dateTime_.year)
			&& (dateTime_.month == d.dateTime_.month)
			&& (dateTime_.day < d.dateTime_.day)));
}

bool Date::operator<=( const Date &d ) const
{ //use existing operators to determine <=
	return ( (*this < d) || (*this == d) );
}

bool Date::operator>( const Date &d ) const
{//true if this > d
	return ( ( dateTime_.year > d.dateTime_.year)
	     || (( dateTime_.year == d.dateTime_.year)
			&& (dateTime_.month > d.dateTime_.month) )
	     || (( dateTime_.year == d.dateTime_.year)
			&& (dateTime_.month == d.dateTime_.month)
			&& (dateTime_.day > d.dateTime_.day)) );
}

bool Date::operator>=( const Date &d ) const
{ // use existing operators to determine >=
	return ( (*this > d) || (*this == d) );
}

DateTime& Date::operator>>( DateTime &dateTime ) const
{ // stream dateTime to dateTime_
	dateTime.day	= dateTime_.day;
	dateTime.month	= dateTime_.month;
	dateTime.year	= dateTime_.year;

	dateTime.second = dateTime_.second;
	dateTime.minute = dateTime_.minute;
	dateTime.hour	= dateTime_.hour;

	return dateTime;
}

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream& os, const Date& aDate )
{
    return ( aDate.putDataInStream( os ));
}

istream& operator>>( istream& is, Date& aDate )
{
	return ( aDate.getDataFromStream( is ) );
}