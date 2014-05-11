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
    os << accountType_ << "\n";				//put account type
    os << accountNumber_ << "\n";			//put account number
	os << sortCode_ << "\n";				//put sort code
    os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	os << overdraftLimit_ << "\n";

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

const string CurrentAccount::prepareFormattedAccountDetails() const
{
		//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << accountType_ << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << accountNumber_;									//display account number
	os << "\nSORT CODE:       " << sortCode_;										//display sort code
	os << "\nCREATION DATE:   " << creationDate_.toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << balance_;						//display balance
	os << "\nOVERDRAFT:       \234" << setw(10) << overdraftLimit_;						//display overdraft
	os << "\nAVAILABLE:       \234" << setw(10) << (balance_ + overdraftLimit_);			//Available balance

	return os.str();
}