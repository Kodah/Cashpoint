//Pascale Vacher - March 14
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

	template <typename T> TransactionList getTransactionsForSearchCriterion( const T searchVal ) const;

	const string toFormattedString() const;		//return transactionlist as a (formatted) string
	ostream& putDataInStream( ostream& os) const;	//send TransactionList info into an output stream
	istream& getDataFromStream( istream& is);	//receive TransactionList info from an input stream

	TransactionList& operator +=( TransactionList trList )
	{
		int trListSize = trList.size();

		for( int i(0); i < trListSize; i++ )
		{
			addNewTransaction( trList.newestTransaction() );
			trList.deleteFirstTransaction();
		}

		return *this;
	}


private:
    List<Transaction> listOfTransactions_;	//list of transactions
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const TransactionList&);	//insertion operator
istream& operator>>( istream& is, TransactionList& trl); //extraction operator

#endif

