#ifndef ISAACCOUNT_H
#define ISAACCOUNT_H

#include "SavingsAccount.h"

class ISAAccount : public SavingsAccount
{
public: //Public declarations
	//Constructors/Destructors
	ISAAccount( const string& acctNum, const string& sCode,
                          const Date& cD, double b, const TransactionList& trList,
						  const Date endDepositPeriod, const double maximumYearlyDeposit = 1000.0 );
	//Accessor declarations
	double								getCurrentYearlyDeposit( void ) const;
	double								getMaximumYearlyDeposit( void ) const;

	Date								getEndDepositPeriod( void ) const;

private: //Private method declarations
	//Setter declarations
	void								updateCurrentYearlyDeposit( const double deposit );

private: //Private member instances
	double								currentYearlyDeposit, maximumYearlyDeposit;
	Date								endDepositPeriod;
};

#endif