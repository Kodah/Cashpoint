//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#ifndef TransactionListH
#define TransactionListH

//---------------------------------------------------------------------------
//TransactionList: class declaration
//---------------------------------------------------------------------------

#include "ListT.h"
#include "Transaction.h"

#include <cassert> 	// for assert()
#include <sstream>
#include <list>

class TransactionList
{
public:

	void   addNewTransaction( const Transaction&);
    const Transaction newestTransaction() const;
    const  TransactionList olderTransactions() const;
    void   deleteFirstTransaction();
    void   deleteGivenTransaction( const Transaction&);
	void deleteTransactionsUpToDate( const Date date );
	int    size() const;

	TransactionList getAllDepositTransactions() const;
	TransactionList getMostRecentTransactions(int) const;

	TransactionList getTransactionsForAmount(double);//for option 7
	TransactionList getTransactionsForDate(Date);//for option 7
	TransactionList getTransactionsForTitle(string);//for option 7
	int getNumberOfTransactions();//for option 7

	double getTotalTransactions() const;
	TransactionList getTransactionsUpToDate( const Date d ) const;
	TransactionList TransactionList::getTransactionsUpToDate( TransactionList trList, const Date date ) const;

	template <typename T> TransactionList getTransactionsForSearchCriteria( const T searchVal ) const;

	const string toFormattedString() const;		//return transactionlist as a (formatted) string
	ostream& putDataInStream( ostream& os) const;	//send TransactionList info into an output stream
	istream& getDataFromStream( istream& is);	//receive TransactionList info from an input stream

	TransactionList& operator +=( TransactionList trList );

private:
	template <typename T> const DWORD getTypeId( const T &type ) const
	{
		if( typeid( type ) == typeid( Date ) )
			return DATE;
		else if ( typeid( type ) == typeid( string ) )
			return STRING;
		else if ( typeid( type ) == typeid( double ) )
			return DOUBLE
	}
	
private:
    list<Transaction> listOfTransactions_;	//list of transactions
	list<Transaction>::iterator it_;
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const TransactionList&);	//insertion operator
istream& operator>>( istream& is, TransactionList& trl); //extraction operator

#endif

