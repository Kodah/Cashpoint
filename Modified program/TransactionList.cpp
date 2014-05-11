//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#include "TransactionList.h"

//---------------------------------------------------------------------------
//TransactionList: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors

//____other public member functions

void TransactionList::addNewTransaction( const Transaction& tr )
{
   // listOfTransactions_.addInFront( tr);
	it_ = listOfTransactions_.begin();
	listOfTransactions_.insert( it_, tr );
}

const Transaction TransactionList::newestTransaction( void ) const
{
    //return (listOfTransactions_.first());
	return listOfTransactions_.front();
}
const TransactionList TransactionList::olderTransactions( void ) const
{
	TransactionList trlist( *this );
    trlist.deleteFirstTransaction();

    return trlist;
}
void TransactionList::deleteFirstTransaction( void )
{
    //listOfTransactions_.deleteFirst();
	it_ = listOfTransactions_.begin();
	listOfTransactions_.erase( it_ );
}

void TransactionList::deleteGivenTransaction( const Transaction& tr )
{
    //listOfTransactions_.deleteOne( tr);
	listOfTransactions_.remove( tr );
}

//delete the transactions up to a certain date
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
	//check there are still transactions
	if( numTransactions == 0 )
		return;
	//create a temp transaction of the latest transaction
	Transaction tempTransaction = trList.newestTransaction();
	//then delete it
	deleteGivenTransaction( tempTransaction );
    trList.deleteGivenTransaction( tempTransaction );
	//then call the funtion again
	deleteTransactionsUpToDate( date );
}

int TransactionList::size( void ) const
{
    //return (listOfTransactions_.length());
	return listOfTransactions_.size();
}

TransactionList TransactionList::getAllDepositTransactions( void ) const
{
	//Returns Transaction list of deposits
	return getTransactionsForTitle( *this, DEPOSITTITLE );
}

double TransactionList::getTotalTransactions( void ) const
{
	//Returns count of transactions
	TransactionList tempList( *this );
	double total = 0.0;
	int listSize = tempList.size();

	for( int i(0); i < listSize; i++ )
	{
		total += tempList.newestTransaction().getAmount();
		tempList.deleteFirstTransaction();
	}

	//
	/*while ( ! ( tempList.size() == 0))
		{
			if (tempList.newestTransaction().getAmount() > 0)
			{
				total += tempList.newestTransaction().getAmount();
				
			}
			tempList.deleteFirstTransaction();
		}*/

	return total;
}

TransactionList TransactionList::getTransactionsUpToDate( const Date date ) const
{//NON-RECURSIVE VERSION
	TransactionList trList( *this ), trList2;
	int numTransactions = trList.size();

	//goes through each transaction in the transaction list
	for( int i(0); i < numTransactions; i++ )
	{
		//gets the latest transaction
		Transaction tempTransaction = trList.newestTransaction();
		//checks to see if the transaction is before or equal to the date
		//add the transaction to another list
		if( tempTransaction.getDate() <= date )
			trList2.addNewTransaction( tempTransaction );
		
		//then delete the transaction from the old list
		trList.deleteGivenTransaction( tempTransaction );
	}
	//return the new transaction list
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

TransactionList TransactionList::getMostRecentTransactions( int trans ) const
{
	//Returns Transaction list of user defined length
	TransactionList tempList( *this );
	TransactionList newList;

	int numTransactions = this->size();

	if( numTransactions < trans )
		trans = numTransactions;

	for (int i = 0; i < trans; i++)
	{
		newList.addNewTransaction(tempList.newestTransaction());
		tempList.deleteFirstTransaction();
	}

	return newList;
}

//template for getting the transactions depending on title, date or amount
template <typename T>
TransactionList TransactionList::getTransactionsForSearchCriteria( const T searchVal ) const
{
	TransactionList tempList( *this );
	TransactionList newList;
	ostringstream oss;
	string date = "", amount = "", title = "", value = "";

	int numTransactions = tempList.size();

	//go through each transaction
	for( int i(0); i < numTransactions; i++ )
	{
		//put the date of the latest transaction into an ostringstream
		oss << tempList.newestTransaction().getDate();
		date = oss.str();
		oss.str( "" );
		//put the amount of the latest transaction into an ostringstream
		oss << tempList.newestTransaction().getAmount();
		amount = oss.str();
		oss.str( "" );
		//put the title of the latest transaction into an ostringstream
		oss << tempList.newestTransaction().getTitle();
		title = oss.str();
		oss.str( "" );
		//put the passed value into an ostringstream
		oss << searchVal;
		value = oss.str();
		oss.str( "" );

		//check the latest transaction against the passed value
		//add the lastest transaction to the new list
		if( date == value || amount == value || title == value )
			newList.addNewTransaction( tempList.newestTransaction() );

		//delete the transaction
		tempList.deleteFirstTransaction();
	}

	return newList;
}

//templates for double, string and Date
template TransactionList TransactionList::getTransactionsForSearchCriteria<double>( const double ) const;
template TransactionList TransactionList::getTransactionsForSearchCriteria<string>( const string ) const;
template TransactionList TransactionList::getTransactionsForSearchCriteria<Date>( const Date ) const;

TransactionList TransactionList::getTransactionsForAmount( TransactionList trList, const double amount ) const
{
	TransactionList newList;
	Transaction tempTransaction;

	//check there are still transactions left
	if( trList.size() > 0 )
	{
		//get the latest transaction
		tempTransaction = trList.newestTransaction();
		//check if the values match
		//if so add the transaction the the new list
		if( tempTransaction.getAmount() == amount )
			newList.addNewTransaction( tempTransaction );
		
		//delete the first transaction and call the function again
		trList.deleteFirstTransaction();
		newList += getTransactionsForAmount( trList, amount );
	}

	return newList;
}

TransactionList TransactionList::getTransactionsForTitle( TransactionList trList, const string title ) const
{ 
	TransactionList newList;
	Transaction tempTransaction;
	//check there are still transactions left
	if( trList.size() > 0 )
	{
		//get the latest transaction
		tempTransaction = trList.newestTransaction();
		//check if the values match
		//if so add the transaction the the new list
		if( tempTransaction.getTitle() == title )
			newList.addNewTransaction( tempTransaction );

		//delete the first transaction and call the function again
		trList.deleteFirstTransaction();
		newList += getTransactionsForTitle( trList, title );
	}

	return newList;
}

TransactionList TransactionList::getTransactionsForDate( TransactionList trList, const Date date ) const
{
	TransactionList newList;
	Transaction tempTransaction;
	//check there are still transactions left
	if( trList.size() > 0 )
	{
		//get the latest transaction
		tempTransaction = trList.newestTransaction();
		//check if the values match
		//if so add the transaction the the new list
		if( tempTransaction.getDate() == date )
			newList.addNewTransaction( tempTransaction );
		
		//delete the first transaction and call the function again
		trList.deleteFirstTransaction();
		newList += getTransactionsForDate( trList, date );
	}

	return newList;
}

int TransactionList::getNumberOfTransactions( void ) const
{
	return size();
}


const string TransactionList::toFormattedString( void ) const
{
//return transaction list as a (formatted) string
	ostringstream os_transactionlist;
    TransactionList tempTrList( *this );

	int listSize = tempTrList.size();

	for( int i(0); i < listSize; i++ )
	{
		os_transactionlist << tempTrList.newestTransaction().toFormattedString() << endl;
        tempTrList.deleteFirstTransaction();
	}

	return os_transactionlist.str();
}

ostream& TransactionList::putDataInStream( ostream& os ) const
{
//put (unformatted) transaction list into an output stream
    TransactionList tempTrList( *this );
	int numTrans = tempTrList.size();

	for( int i(0); i < numTrans; i++ )
	{
		os << tempTrList.newestTransaction() << endl;
        tempTrList.deleteFirstTransaction();
	}

	return os;
}

istream& TransactionList::getDataFromStream( istream& is )
{
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

ostream& operator<<( ostream& os, const TransactionList& aTransactionList )
{
    return aTransactionList.putDataInStream( os );
}

istream& operator>>( istream& is, TransactionList& aTransactionList )
{
	return aTransactionList.getDataFromStream( is );
}
