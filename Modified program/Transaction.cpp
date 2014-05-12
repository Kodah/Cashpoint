//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#include "Transaction.h"

//---------------------------------------------------------------------------
//Transaction: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors
Transaction::Transaction()
{ 
}

Transaction::Transaction( const Date& d, const Time& t, const string& s, const double a )
: date_( d ), time_( t ), title_( s ), amount_( a )
{ 
}

Transaction::Transaction( const string& s, const double a )
: title_( s), amount_( a ), date_( Date::currentDate() ), time_( Time::currentTime() ) //get date and time from system
{
}

//____other public member functions
const Date Transaction::getDate( void ) const
{
	return date_; //pass transaction's date
}

const Time Transaction::getTime( void ) const
{
	return time_;//pass transaction's time
}

const string Transaction::getTitle( void ) const
{
	return title_; //pass transaction's title
}

const double Transaction::getAmount( void ) const
{
	return amount_; //pass transaction's amount
}

const string Transaction::toFormattedString( void ) const
{
//return (formatted) transaction as a string ("HH:MM:SS")
	ostringstream os_transaction;

	os_transaction << setfill('0')
	<< date_ << " "
	<< time_ << " "
	<< setfill('-')
	<< setw(30) << title_ << " "
	<< setfill(' ') << fixed << setprecision(2)
    << "\234" << setw(8) << amount_;

	return os_transaction.str();
}

ostream& Transaction::putDataInStream( ostream& os ) const
{
//put (unformatted) transaction into an output stream
	os << date_ << " "
	   << time_ << " "
	   << title_ << " "
       << amount_;

	return os;
}
istream& Transaction::getDataFromStream( istream& is )
{
//read in (unformatted) transaction from input stream
	is >> date_ >> time_ >> title_ >> amount_;
	return is;
}

//---------------------------------------------------------------------------
//overloaded operator functions
//---------------------------------------------------------------------------

bool Transaction::operator==( const Transaction& tr ) const
{
	return
		(( date_   == tr.date_)   &&
		 ( time_   == tr.time_)   &&
		 ( title_  == tr.title_)  &&
		 ( amount_ == tr.amount_));
}

bool Transaction::operator!=( const Transaction& tr ) const
{
	return ( !(*this == tr) );
}

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream& os, const Transaction& aTransaction )
{
    return ( aTransaction.putDataInStream( os ));
}

istream& operator>>( istream& is, Transaction& aTransaction )
{
	return ( aTransaction.getDataFromStream( is));
}
