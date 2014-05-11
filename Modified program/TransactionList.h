//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#ifndef TransactionListH
#define TransactionListH

//---------------------------------------------------------------------------
//TransactionList: class declaration
//---------------------------------------------------------------------------
//microsoft library includes
#include <list>
//our header includes
#include "Transaction.h"
//removed using namespace std to prevent namespace pollution
using std::list;
using std::endl;

class TransactionList // TransactionList class
{
public: //Setters
	void							addNewTransaction( const Transaction& ); //add transaction to front
    TransactionList					olderTransactions( void ) const; //remove 1st and return rest
    void							deleteFirstTransaction( void );
    void							deleteGivenTransaction( const Transaction& ); //delete specified transaction
	void							deleteTransactionsUpToDate( const Date date ); //delete transaction to specified date
	// Getters
	int								size( void ) const; //get number of elements
	Transaction						newestTransaction( void ) const; //get first element

	TransactionList					getAllDepositTransactions( void ) const; //every deposit transaction
	TransactionList					getMostRecentTransactions( int numTrans ) const; //newest transactions of user specified amount

	TransactionList					getTransactionsForAmount( TransactionList trList, const double amount ) const; //before templates
	TransactionList					getTransactionsForDate( TransactionList trList, const Date date ) const;
	TransactionList					getTransactionsForTitle( TransactionList trList, const string title ) const;
	int								getNumberOfTransactions( void ) const; //pointless method, but required by specification

	double							getTotalTransactions( void ) const; //mis-leading name, but same as specification returns total of all transactions
	TransactionList					getTransactionsUpToDate( const Date d ) const;
	TransactionList					getTransactionsUpToDate( TransactionList trList, const Date date ) const; //for recursion

	template <typename T> TransactionList getTransactionsForSearchCriteria( const T searchVal ) const;

	const string					toFormattedString( void ) const; //return transactionlist as a (formatted) string
	ostream&						putDataInStream( ostream& os ) const; //send TransactionList info into an output stream
	istream&						getDataFromStream( istream& is ); //receive TransactionList info from an input stream

	TransactionList& operator +=( TransactionList trList );
	
private:
    list<Transaction>				listOfTransactions_; //list of transactions
	list<Transaction>::iterator		it_; //list<Transaction>::iterator
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const TransactionList& ); //insertion operator
istream& operator>>( istream &is, TransactionList &trl ); //extraction operator

#endif

