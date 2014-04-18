#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H

#include "BankAccount.h"

class CurrentAccount : public BankAccount
{
public: //Public declarations
	//Constructors/Destructors
	CurrentAccount( const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList, const double overdraftLimit = 0.0 );

	//Accessor declarations
	double								getOverdraftLimit( void ) const;
private: //Private member instances
	double overdraftLimit;

};

#endif