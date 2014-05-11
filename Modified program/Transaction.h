//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#ifndef TransactionH
#define TransactionH

//---------------------------------------------------------------------------
//Transaction: class declaration
//---------------------------------------------------------------------------
//microsoft library includes
#include <iostream>
//our header includes
#include "Date.h"
#include "Time.h"
//removed using namespace std to prevent namespace pollution
using std::fixed;
using std::setprecision;

class Transaction // Transaction class
{
public:
	Transaction();	//default constructor
	Transaction( const Date&, const Time&, const string&, double );	//constructor
    Transaction( const string&, double );   //constructor

	const Date									getDate( void ) const; //return transaction date_
	const Time									getTime( void ) const; //return transaction time_
	const string								getTitle( void ) const; //return transaction title_
	const double								getAmount( void ) const; //return transaction amount

	const string								toFormattedString( void ) const; //return transaction as a formatted string
	ostream&									putDataInStream( ostream& os) const; //send Transaction info into an output stream
	istream&									getDataFromStream( istream& is); //receive Transaction info from an input stream

	bool										operator==( const Transaction& ) const; //"equal" operator
	bool										operator!=( const Transaction& ) const; //"not-equal" operator

private:
    Date										date_; //transaction date
	Time										time_; //transaction time
	string										title_;	//transaction title
	double										amount_; //transaction amount
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const Transaction& );	//output operator
istream& operator>>( istream&, Transaction& );	//input operator


#endif
