#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "BankAccount.h"

class SavingsAccount : public BankAccount
{
public: //Public declarations
	//Constructors/Destructors
	SavingsAccount( const double minimumBalance = 0.0 );
	SavingsAccount( const string& typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList, const double minimumBalance = 0.0 );
	
	//Accessor declarations
	double								getMinimumBalance( void ) const;

	virtual ostream&					putDataInStream( ostream& os) const = 0;
	virtual istream&					getDataFromStream( istream& is) = 0;

protected: //Protected member instances
	double								minimumBalance_;

};

#endif