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

const bool ChildAccount::canTransferIn( const double amount ) const
{
	return ((amount >= 0.0) && (amount >= minimumPaidIn_)
		&& (amount <= maximumPaidIn_));
}

const string ChildAccount::prepareFormattedAccountDetails() const
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
	os << "\nMINIMUM PAID IN: \234" << setw(10) << minimumPaidIn_;					//display minimum paid in
	os << "\nMAXIMUM PAID IN: \234" << setw(10) << maximumPaidIn_;					//display maximum paid in

	return os.str();
}