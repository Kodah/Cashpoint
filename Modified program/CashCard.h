//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#ifndef CashCardH
#define CashCardH

//---------------------------------------------------------------------------
//Card: class declaration
//---------------------------------------------------------------------------

#include <fstream>
#include <iostream> 
#include <string>
#include <sstream>
#include <list>

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

class CashCard {
public:
    //constructors & destructor
	CashCard();
    CashCard( const string& cardNum, const list<string> &accList );

	//getter (assessor) functions
    const string getCardNumber() const;
    const list<string> getAccountsList() const;

	void readInCardFromFile( const string& fileName);
	bool onCard( const string& fileName) const;

	//functions to put data into and get data from streams
	const string toFormattedString() const;
	ostream& putDataInStream( ostream& os) const;
	istream& getDataFromStream( istream& is);

private:
    string cardNumber_;
    //List<string> accountsList_;
	list<string> accountsList_;
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const CashCard&);	//output operator
istream& operator>>( istream&, CashCard&);	//input operator

#endif
