//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#ifndef TransactionListH
#define TransactionListH

//---------------------------------------------------------------------------
//TransactionList: class declaration
//---------------------------------------------------------------------------

#include <list>

#include "Transaction.h"

using std::list;
using std::endl;

class TransactionList
{
public:
	void   addNewTransaction( const Transaction& );
    const Transaction newestTransaction( void ) const;
    const  TransactionList olderTransactions( void ) const;
    void   deleteFirstTransaction( void );
    void   deleteGivenTransaction( const Transaction&);
	void deleteTransactionsUpToDate( const Date date );
	int  size( void ) const;

	TransactionList getAllDepositTransactions( void ) const;
	TransactionList getMostRecentTransactions( const int numTrans ) const;

	TransactionList getTransactionsForAmount( TransactionList trList, const double amount ) const;
	TransactionList getTransactionsForDate( TransactionList trList, const Date date ) const;
	TransactionList getTransactionsForTitle( TransactionList trList, const string title ) const;
	int getNumberOfTransactions( void ) const;

	double getTotalTransactions( void ) const;
	TransactionList getTransactionsUpToDate( const Date d ) const;
	TransactionList getTransactionsUpToDate( TransactionList trList, const Date date ) const;

	template <typename T> TransactionList getTransactionsForSearchCriteria( const T searchVal ) const;

	const string toFormattedString( void ) const;	//return transactionlist as a (formatted) string
	ostream& putDataInStream( ostream& os) const;	//send TransactionList info into an output stream
	istream& getDataFromStream( istream& is);		//receive TransactionList info from an input stream

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

