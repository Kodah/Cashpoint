#include "ChildAccount.h"

//Constructor/Destructor implementations

ChildAccount::ChildAccount( const string& acctNum, const string& sCode,
                          const Date& cD, double b, const TransactionList& trList,
						  const double minimumPaidIn, const double MaximumPaidIn ) :
SavingsAccount(  "CHILDSAVINGS", acctNum, sCode, cD, b, trList ), minimumPaidIn( minimumPaidIn ),
	maximumPaidIn( maximumPaidIn )
{

}

//Public member methods

//Accessor methods
double ChildAccount::getMinimumPaidIn( void ) const
{
	return minimumPaidIn;
}

double ChildAccount::getMaximumPaidIn( void ) const
{
	return maximumPaidIn;
}