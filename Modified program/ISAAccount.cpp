#include "ISAAccount.h"

ISAAccount::ISAAccount( const string& acctNum, const string& sCode,
                          const Date& cD, double b, const TransactionList& trList,
						  const Date endDepositPeriod, const double maximumYearlyDeposit )
						  : SavingsAccount( "ISASAVINGS", acctNum, sCode, cD, b, trList ),
						  endDepositPeriod( endDepositPeriod ),
						  currentYearlyDeposit( 0.0 ), maximumYearlyDeposit( maximumYearlyDeposit )
{
}

//Public member methods

//Accessor methods
double ISAAccount::getCurrentYearlyDeposit( void ) const
{
	return currentYearlyDeposit;
}

double ISAAccount::getMaximumYearlyDeposit( void ) const
{
	return maximumYearlyDeposit;
}

Date ISAAccount::getEndDepositPeriod( void ) const
{
	return endDepositPeriod;
}

//Private member methods

//Setter methods
void ISAAccount::updateCurrentYearlyDeposit( const double deposit )
{
	currentYearlyDeposit += deposit;
}