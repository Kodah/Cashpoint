#include "SavingsAccount.h"

//Constructor/Destructor implementations

SavingsAccount::SavingsAccount( const string& typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList, const double minimumBalance ) :
BankAccount(  typ, acctNum, sCode, cD, b, trList ), minimumBalance( minimumBalance )
{

}

//Public member methods

//Accessor methods

double SavingsAccount::getMinimumBalance( void ) const
{
	return minimumBalance;
}