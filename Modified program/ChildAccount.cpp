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

ostream& ChildAccount::putDataInStream( ostream& os) const
{
	//put (unformatted) BankAccount details in stream
    os << accountType_ << "\n";				//put account type
    os << accountNumber_ << "\n";			//put account number
	os << sortCode_ << "\n";				//put sort code
    os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	os << minimumBalance_ << "\n";
	os << minimumPaidIn_ << "\n";
	os << maximumPaidIn_ << "\n";

	if (  ! transactions_.size() == 0)
		os << transactions_;				//put all transactions, one per line

	return os;
}

istream& ChildAccount::getDataFromStream( istream& is)
{
		//get BankAccount details from stream
    is >> accountType_;						//get account type
    is >> accountNumber_;					//get account number
	is >> sortCode_;						//get sort code
 	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance_
	is >> minimumBalance_;
	is >> minimumPaidIn_;
	is >> maximumPaidIn_;
	is >> transactions_;					//get all transactions (if any)

	return is;
}