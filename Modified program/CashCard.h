//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#ifndef CashCardH
#define CashCardH

//---------------------------------------------------------------------------
//Card: class declaration
//---------------------------------------------------------------------------
//microsoft library includes
#include <fstream>
#include <iostream> 
#include <string>
#include <sstream>
#include <list>

#include "BankAccount.h"

//removed using namespace std to prevent namespace pollution
using std::string;
using std::ostream;
using std::istream;
using std::ifstream;
using std::ios;
using std::cout;
using std::endl;
using std::ostringstream;
using std::list;
using std::iterator;
using std::find;

class CashCard //CashCard class
{
public:
    //constructors & destructor
	CashCard();
    CashCard( const string& cardNum, const list<string> &accList );

	//getter (assessor) functions
    const string						getCardNumber( void ) const;
    const list<string>					getAccountsList( void ) const;
	const string						getAssociatedAccounts( BankAccount *acc ) const;

	void								readInCardFromFile( const string& fileName);
	bool								onCard( const string& fileName) const;

	//functions to put data into and get data from streams
	const string						toFormattedString( void ) const;
	ostream&							putDataInStream( ostream& os ) const;
	istream&							getDataFromStream( istream& is );

private: //private member instances
    string								cardNumber_;
    //List<string>						accountsList_;
	list<string>						accountsList_;
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const CashCard&);	//output operator
istream& operator>>( istream&, CashCard&);	//input operator

#endif
