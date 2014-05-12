//Mike Orr, Luke Segaran, Tom sugarev - May 14

#include "CurrentAccount.h"

//Constructor/Destructor implementations

CurrentAccount::CurrentAccount( const double overdraftLimit ) : overdraftLimit_( overdraftLimit )
{
}

CurrentAccount::CurrentAccount( const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList, const double overdraftLimit ) :
BankAccount(  "CURRENT", acctNum, sCode, cD, b, trList ), overdraftLimit_( overdraftLimit )
{

}

//Public member methods

//Accessor methods
double CurrentAccount::getOverdraftLimit( void ) const
{
	return overdraftLimit_;
}

ostream& CurrentAccount::putDataInStream( ostream& os ) const
{
	//put (unformatted) BankAccount details in stream
    os << accountType_ << endl			//put account type
	   << accountNumber_ << endl		//put account number
	   << sortCode_ << endl				//put sort code
       << creationDate_ << endl			//put creation date
	   << balance_ << endl				//put balance
	   << overdraftLimit_ << endl;

	if (  ! transactions_.size() == 0)
		os << transactions_;				//put all transactions, one per line

	return os;
}

istream& CurrentAccount::getDataFromStream( istream& is )
{
	//get BankAccount details from stream
    is >> accountType_;						//get account type
    is >> accountNumber_;					//get account number
	is >> sortCode_;						//get sort code
 	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance_
	is >> overdraftLimit_;					//get overdraftLimit
	is >> transactions_;					//get all transactions (if any)

	return is;
}

const bool CurrentAccount::canTransferOut( const double amount ) const
{
	return ((amount >= 0.0) && ((balance_ - amount) >= -overdraftLimit_));
}

const string CurrentAccount::prepareFormattedAccountDetails( void ) const
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
	   << endl << "OVERDRAFT:       \234" << setw(10) << overdraftLimit_				//display overdraft
	   << endl << "AVAILABLE:       \234" << setw(10) << (balance_ + overdraftLimit_);	//Available balance

	return os.str();
}