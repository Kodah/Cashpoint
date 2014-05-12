//Mike Orr, Luke Segaran, Tom sugarev - May 14

#include "ChildAccount.h"

//Constructor/Destructor implementations

ChildAccount::ChildAccount( const double minimumBalance, const double minimumPaidIn,
		const double maximumPaidIn ) : SavingsAccount( minimumBalance ),
		minimumPaidIn_( minimumPaidIn ), maximumPaidIn_( maximumPaidIn )
{
}

ChildAccount::ChildAccount( const string &typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b, const TransactionList& trList,
						  const double minimumPaidIn, const double maximumPaidIn,
						  const double minimumBalance ) :
SavingsAccount(  typ, acctNum, sCode, cD, b, trList, minimumBalance ), minimumPaidIn_( minimumPaidIn ),
	maximumPaidIn_( maximumPaidIn )
{

}

//Public member methods

//Accessor methods
double ChildAccount::getMinimumPaidIn( void ) const
{
	return minimumPaidIn_;
}

double ChildAccount::getMaximumPaidIn( void ) const
{
	return maximumPaidIn_;
}

ostream& ChildAccount::putDataInStream( ostream& os ) const
{
	//put (unformatted) BankAccount details in stream
    os << accountType_		<< endl			//put account type
	   << accountNumber_	<< endl			//put account number
	   << sortCode_			<< endl			//put sort code
       << creationDate_		<< endl			//put creation date
	   << balance_			<< endl			//put balance
	   << minimumBalance_	<< endl			//put minimum balance
	   << minimumPaidIn_	<< endl			//put min paid in
	   << maximumPaidIn_	<< endl;		//put max paid in

	if (  transactions_.size() )
		os << transactions_;				//put all transactions, one per line

	return os;
}

istream& ChildAccount::getDataFromStream( istream& is )
{
		//get BankAccount details from stream
    is >> accountType_				//get account type
	   >> accountNumber_			//get account number
	   >> sortCode_					//get sort code
 	   >> creationDate_				//get creation date
	   >> balance_					//get balance_
	   >> minimumBalance_			//get min balance
	   >> minimumPaidIn_			//get min paid in
	   >> maximumPaidIn_			//get max paid in
	   >> transactions_;			//get all transactions (if any)

	return is; // return stream
}

const bool ChildAccount::canTransferIn( const double amount ) const
{
	return ((amount >= 0.0) && (amount >= minimumPaidIn_)
		&& (amount <= maximumPaidIn_));
}

const string ChildAccount::prepareFormattedAccountDetails( void ) const
{
	//collect account details in string
	ostringstream os;
	//account details
	os << endl << "ACCOUNT TYPE:    " << accountType_ << " ACCOUNT"						//display account type
	   << endl << "ACCOUNT NUMBER:  " << accountNumber_									//display account number
	   << endl << "SORT CODE:       " << sortCode_										//display sort code
	   << endl << "CREATION DATE:   " << creationDate_.toFormattedString()				//display creation date
	   << fixed << setprecision(2) << setfill(' ')
	   << endl << "BALANCE:         \234" << setw(10) << balance_						//display balance
	   << endl << "MIN BALANCE:     \234" << setw(10) << minimumBalance_				//display minimumBalance_
	   << endl << "MINIMUM PAID IN: \234" << setw(10) << minimumPaidIn_					//display minimum paid in
	   << endl << "MAXIMUM PAID IN: \234" << setw(10) << maximumPaidIn_;				//display maximum paid in

	return os.str();
}