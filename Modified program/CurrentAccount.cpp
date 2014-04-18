#include "CurrentAccount.h"

//Constructor/Destructor implementations

CurrentAccount::CurrentAccount( const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList, const double overdraftLimit ) :
BankAccount(  "CURRENT", acctNum, sCode, cD, b, trList ), overdraftLimit( overdraftLimit )
{

}

//Public member methods

//Accessor methods
double CurrentAccount::getOverdraftLimit( void ) const
{
	return overdraftLimit;
}