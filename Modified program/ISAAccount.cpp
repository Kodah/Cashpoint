//Mike Orr, Luke Segaran, Tom sugarev - May 14

#include "ISAAccount.h"

ISAAccount::ISAAccount( const Date, const double minimumBalance,
					   const double currentYearlyDeposit, const double maximumYearlyDeposit )
					   : SavingsAccount( minimumBalance ), currentYearlyDeposit_( currentYearlyDeposit ),
					   maximumYearlyDeposit_( maximumYearlyDeposit )
{

}

ISAAccount::ISAAccount( const string &typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b, const TransactionList& trList, const double minimumBalance,
						  const Date endDepositPeriod, const double currentYearlyDeposit,
						  const double maximumYearlyDeposit )
						  : SavingsAccount( typ, acctNum, sCode, cD, b, trList, minimumBalance ),
						  endDepositPeriod_( endDepositPeriod ),
						  currentYearlyDeposit_( currentYearlyDeposit ), maximumYearlyDeposit_( maximumYearlyDeposit )
{
}

//Public member methods

//Accessor methods
double ISAAccount::getCurrentYearlyDeposit( void ) const
{
	return currentYearlyDeposit_;
}

double ISAAccount::getMaximumYearlyDeposit( void ) const
{
	return maximumYearlyDeposit_;
}

Date ISAAccount::getEndDepositPeriod( void ) const
{
	return endDepositPeriod_;
}

//Private member methods

//Setter methods
void ISAAccount::updateCurrentYearlyDeposit( const double deposit )
{
	currentYearlyDeposit_ += deposit;
}

ostream& ISAAccount::putDataInStream( ostream& os) const
{
	//put (unformatted) BankAccount details in stream
    os << accountType_ << "\n";				//put account type
    os << accountNumber_ << "\n";			//put account number
	os << sortCode_ << "\n";				//put sort code
    os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	os << minimumBalance_ << "\n";			//put min balance
	os << currentYearlyDeposit_ << "\n";	//put current yearly deposit
	os << maximumYearlyDeposit_ << "\n";	//put max yearly deposit
	os << endDepositPeriod_ << "\n";		//put deposit end date

	if (  ! transactions_.size() == 0)
		os << transactions_;				//put all transactions, one per line

	return os;
}

istream& ISAAccount::getDataFromStream( istream& is)
{
		//get BankAccount details from stream
    is >> accountType_;						//get account type
    is >> accountNumber_;					//get account number
	is >> sortCode_;						//get sort code
 	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance_
	is >> minimumBalance_;					//get min balance
	is >> currentYearlyDeposit_;			//get current yearly deposit
	is >> maximumYearlyDeposit_;			//get max yearly deposit
	is >> endDepositPeriod_;				//get deposit end date
	is >> transactions_;					//get all transactions (if any)

	return is;
}

const bool ISAAccount::canTransferIn( const double amount ) const
{
	return (((currentYearlyDeposit_ + amount ) <= maximumYearlyDeposit_) &&
		(Date::currentDate() < endDepositPeriod_) && (amount >= 0.0));
}

void ISAAccount::recordTransferIn( const double amount, const string aAN, const string aSC )
{
	const string transaction = ( "Transfer_from_" + aAN + "_" + aSC ); 
	transactions_.addNewTransaction( Transaction( transaction, amount ) ); 

	updateCurrentYearlyDeposit( amount );
	updateBalance( amount ); //Change account balance
}

const string ISAAccount::prepareFormattedAccountDetails( void ) const
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
	   << endl << "MIN BALANCE:     \234" << setw(10) << minimumBalance_
	   << endl << "CURRENT YEARS DEPOSIT: \234" << setw(10) << currentYearlyDeposit_	//display current year deposit
	   << endl << "MAX YEARS DEPOSIT: \234" << setw(10) << maximumYearlyDeposit_		//display max year deposit
	   << endl << "DEPOSIT RENEWAL DATE: " << endDepositPeriod_.toFormattedString();	//display deposit renewal date

	return os.str();
}