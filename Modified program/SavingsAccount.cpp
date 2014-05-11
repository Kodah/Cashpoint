//Mike Orr, Luke Segaran, Tom sugarev - May 14

#include "SavingsAccount.h"

//Constructor/Destructor implementations

SavingsAccount::SavingsAccount( const double minimumBalance ) : minimumBalance_( minimumBalance )
{
}

SavingsAccount::SavingsAccount( const string& typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList, const double minimumBalance ) :
BankAccount(  typ, acctNum, sCode, cD, b, trList ), minimumBalance_( minimumBalance )
{

}

//Public member methods

//Accessor methods

double SavingsAccount::getMinimumBalance( void ) const
{
	return minimumBalance_;
}

/*ostream& SavingsAccount::putDataInStream( ostream& os) const
{
	//put (unformatted) BankAccount details in stream
    os << accountType_ << "\n";				//put account type
    os << accountNumber_ << "\n";			//put account number
	os << sortCode_ << "\n";				//put sort code
    os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	os << minimumBalance_ << "\n";

	if (  ! transactions_.size() == 0)
		os << transactions_;				//put all transactions, one per line

	return os;
}

istream& SavingsAccount::getDataFromStream( istream& is)
{
		//get BankAccount details from stream
    is >> accountType_;						//get account type
    is >> accountNumber_;					//get account number
	is >> sortCode_;						//get sort code
 	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance_
	is >> minimumBalance_;
	is >> transactions_;					//get all transactions (if any)

	return is;
}*/

const bool SavingsAccount::canTransferOut( const double amount ) const
{
	return ((amount >= 0.0) && ((balance_ - amount) >= minimumBalance_));
}