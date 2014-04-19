#ifndef CHILDACCOUNT_H
#define CHILDACCOUNT_H

#include "SavingsAccount.h"

class ChildAccount : public SavingsAccount
{
public: //Public declarations
	//Constructors/Destructors
	ChildAccount( const double minimumBalance = 0.0, const double minimumPaidIn = 0.0,
		const double maximumPaidIn = 0.0 );

	ChildAccount( const string &typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b, const TransactionList& trList,
						  const double minimumBalance = 0.0,
						  const double minimumPaidIn = 0.0, const double maximumPaidIn = 0.0 );

	//Accessor declarations
	double								getMinimumPaidIn( void ) const;
	double								getMaximumPaidIn( void ) const;

	ostream&							putDataInStream( ostream& os) const;
	istream&							getDataFromStream( istream& is);

private: //Private member instances
	double								minimumPaidIn_, maximumPaidIn_;

};

#endif