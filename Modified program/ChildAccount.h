#ifndef CHILDACCOUNT_H
#define CHILDACCOUNT_H

#include "SavingsAccount.h"

class ChildAccount : public SavingsAccount
{
public: //Public declarations
	//Constructors/Destructors
	ChildAccount( const string& acctNum, const string& sCode,
                          const Date& cD, double b, const TransactionList& trList,
						  const double minimumPaidIn = 0.0, const double MaximumPaidIn = 0.0 );

	//Accessor declarations
	double								getMinimumPaidIn( void ) const;
	double								getMaximumPaidIn( void ) const;
private: //Private member instances
	double								minimumPaidIn, maximumPaidIn;

};

#endif