//Pascale Vacher - March 14
//OOP Assignment Semester 2

#include "TransactionList.h"

//---------------------------------------------------------------------------
//TransactionList: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors

//____other public member functions

void TransactionList::addNewTransaction( const Transaction& tr) {
    listOfTransactions_.addInFront( tr);
}
const Transaction TransactionList::newestTransaction() const {
    return (listOfTransactions_.first());
}
const TransactionList TransactionList::olderTransactions() const {
	TransactionList trlist( *this);
    trlist.deleteFirstTransaction();
    return trlist;
}
void TransactionList::deleteFirstTransaction() {
    listOfTransactions_.deleteFirst();
}
void TransactionList::deleteGivenTransaction( const Transaction& tr) {
    listOfTransactions_.deleteOne( tr);
}

void TransactionList::deleteTransactionsUpToDate( const Date date )
{
	//TransactionList trList = getTransactionsUpToDate( date ); //Non-recursive call
	TransactionList trList = getTransactionsUpToDate( *this, date ); //Recursive call
	int numTransactions = trList.size();

	// Non-recursive code
	/*for( int i(0); i < numTransactions; i++ )
	{
		Transaction tempTransaction = trList.newestTransaction();
		deleteGivenTransaction( tempTransaction );
        trList.deleteGivenTransaction( tempTransaction );
	}*/

	//Recursive version
	if( numTransactions == 0 )
		return;

	Transaction tempTransaction = trList.newestTransaction();

	deleteGivenTransaction( tempTransaction );
    trList.deleteGivenTransaction( tempTransaction );

	deleteTransactionsUpToDate( date );
}

int TransactionList::size() const {
    return (listOfTransactions_.length());
}

TransactionList TransactionList::getAllDepositTransactions() const{
	//Returns Transaction list of deposits
	TransactionList tempList (*this);
	TransactionList newList;
	while ( ! ( tempList.size() == 0))
	{
		if (tempList.newestTransaction().getAmount() > 0)
		{
			newList.addNewTransaction(tempList.newestTransaction());
		}
		tempList.deleteFirstTransaction();
	}

	return ( newList);
}

double TransactionList::getTotalTransactions() const {
	//Returns count of transactions
	TransactionList tempList (*this);
	double total = 0.0;

	while ( ! ( tempList.size() == 0))
		{
			if (tempList.newestTransaction().getAmount() > 0)
			{
				total += tempList.newestTransaction().getAmount();
				
			}
			tempList.deleteFirstTransaction();
		}
	return ( total);
}

TransactionList TransactionList::getTransactionsUpToDate( const Date date ) const
{//NON-RECURSIVE VERSION
	TransactionList trList( *this ), trList2;
	int numTransactions = trList.size();

	for( int i(0); i < numTransactions; i++ )
	{
		Transaction tempTransaction = trList.newestTransaction();
		
		if( tempTransaction.getDate() <= date )
			trList2.addNewTransaction( tempTransaction );
		
		trList.deleteGivenTransaction( tempTransaction );
	}
	
	return trList2;
}

TransactionList TransactionList::getTransactionsUpToDate( TransactionList trList, const Date date ) const
{// RECURSIVE VERSION
	TransactionList trList2;
	Transaction tempTransaction;

	if( trList.size() > 0 )
	{
		tempTransaction = trList.newestTransaction();
		
		if( tempTransaction.getDate() <= date )
			trList2.addNewTransaction( tempTransaction );

		trList.deleteFirstTransaction();
		trList2 += getTransactionsUpToDate( trList, date );
	}

	return trList2;
}

TransactionList TransactionList::getMostRecentTransactions(int trans)const{
	//Returns Transaction list of user defined length
	TransactionList tempList (*this);
	TransactionList newList;

	for (int i = 0; i < trans; i++)
	{
		newList.addNewTransaction(tempList.newestTransaction());
		tempList.deleteFirstTransaction();
	}
	return ( newList);
}

TransactionList TransactionList::getTransactionsForAmount(double amount)//for option 7
{
	TransactionList tempList (*this);
	TransactionList newList;
	while (tempList.size() != 0)
	{
		if (tempList.newestTransaction().getAmount() == amount)
		{
			newList.addNewTransaction(tempList.newestTransaction());
		}
		tempList.deleteFirstTransaction();
	}
	return (newList);
}

TransactionList TransactionList::getTransactionsForTitle(string title)//for option 7
{
	TransactionList tempList (*this);
	TransactionList newList;
	while (tempList.size() != 0)
	{
		if (tempList.newestTransaction().getTitle() == title)
		{
			newList.addNewTransaction(tempList.newestTransaction());
		}
		tempList.deleteFirstTransaction();
	}
	return (newList);
}

TransactionList TransactionList::getTransactionsForDate(Date date)//for option 7
{
	TransactionList tempList (*this);
	TransactionList newList;
	while (tempList.size() != 0)
	{
		if (tempList.newestTransaction().getDate() == date)
		{
			newList.addNewTransaction(tempList.newestTransaction());
		}
		tempList.deleteFirstTransaction();
	}
	return (newList);
}

int TransactionList::getNumberOfTransactions()//for option 7
{
	TransactionList tempList (*this);
	return (tempList.size());
}


const string TransactionList::toFormattedString() const {
//return transaction list as a (formatted) string
	ostringstream os_transactionlist;
    TransactionList tempTrList( *this);
	while ( ! ( tempTrList.size() == 0))
    {
		os_transactionlist << tempTrList.newestTransaction().toFormattedString() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return ( os_transactionlist.str());
}

ostream& TransactionList::putDataInStream( ostream& os) const {
//put (unformatted) transaction list into an output stream
    TransactionList tempTrList( *this);
	while ( ! ( tempTrList.size() == 0))
    {
		os << tempTrList.newestTransaction() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return os;
}
istream& TransactionList::getDataFromStream( istream& is) {
//read in (unformatted) transaction list from input stream
	Transaction aTransaction;
	is >> aTransaction;	//read first transaction
	while ( is != 0) 	//while not end of file
	{
		listOfTransactions_.addAtEnd( aTransaction);   //add transaction to list of transactions
		is >> aTransaction;	//read in next transaction
	}
	return is;
}


//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream& os, const TransactionList& aTransactionList) {
    return ( aTransactionList.putDataInStream( os));
}
istream& operator>>( istream& is, TransactionList& aTransactionList) {
	return ( aTransactionList.getDataFromStream( is));
}
