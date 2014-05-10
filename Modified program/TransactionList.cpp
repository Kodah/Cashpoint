//Pascale Vacher - March 14
//OOP Assignment Semester 2

#include "TransactionList.h"

//---------------------------------------------------------------------------
//TransactionList: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors

//____other public member functions

void TransactionList::addNewTransaction( const Transaction& tr)
{
   // listOfTransactions_.addInFront( tr);
	it_ = listOfTransactions_.begin();
	listOfTransactions_.insert( it_, tr );
}
const Transaction TransactionList::newestTransaction() const
{
    //return (listOfTransactions_.first());
	return listOfTransactions_.front();
}
const TransactionList TransactionList::olderTransactions() const {
	TransactionList trlist( *this);
    trlist.deleteFirstTransaction();
    return trlist;
}
void TransactionList::deleteFirstTransaction()
{
    //listOfTransactions_.deleteFirst();
	it_ = listOfTransactions_.begin();
	listOfTransactions_.erase( it_, it_ );
}

void TransactionList::deleteGivenTransaction( const Transaction& tr)
{
    //listOfTransactions_.deleteOne( tr);
	listOfTransactions_.remove( tr );
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

int TransactionList::size() const
{
    //return (listOfTransactions_.length());
	return listOfTransactions_.size();
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

//Template function for option 7
template <typename T>
TransactionList TransactionList::getTransactionsForSearchCriteria( const T searchVal ) const
{
	TransactionList tempList( *this );
	TransactionList newList;

	int numTransactions = tempList.size();

	for( int i(0); i < numTransactions; i++ )
	{
		if ( (tempList.newestTransaction().getAmount() == searchVal) ||
			 (tempList.newestTransaction().getDate()   == searchVal) ||
			 (tempList.newestTransaction().getTitle()  == searchVal) )
		{
			newList.addNewTransaction(tempList.newestTransaction());
		}

		tempList.deleteFirstTransaction();
	}

	return newList;
}

template TransactionList TransactionList::getTransactionsForSearchCriteria<int>( const int ) const;
template TransactionList TransactionList::getTransactionsForSearchCriteria<string>( const string ) const;
template TransactionList TransactionList::getTransactionsForSearchCriteria<Date>( const Date ) const;

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
		it_ = listOfTransactions_.end();
		listOfTransactions_.insert( it_, aTransaction );
		//listOfTransactions_.addAtEnd( aTransaction);   //add transaction to list of transactions
		is >> aTransaction;	//read in next transaction
	}
	return is;
}

TransactionList& TransactionList::operator +=( TransactionList trList )
{
	int trListSize = trList.size();

	for( int i(0); i < trListSize; i++ )
	{
		addNewTransaction( trList.newestTransaction() );
		trList.deleteFirstTransaction();
	}

	return *this;
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
