#ifndef ISAACCOUNT_H
#define ISAACCOUNT_H

#include "SavingsAccount.h"

class ISAAccount : public SavingsAccount
{
public: //Public declarations
	//Constructors/Destructors
	ISAAccount( const Date endDepositPeriod = Date(), const double minimumBalance = 0.0,
		const double currentYearlyDeposit = 0.0, const double maximumYearlyDeposit = 1000.0 );

	ISAAccount( const string &typ, const string& acctNum, const string& sCode,
                const Date& cD, double b, const TransactionList& trList, const double minimumBalance = 0.0,
				const Date endDepositPeriod = Date(), const double currentYearlyDeposit = 0.0,
				const double maximumYearlyDeposit = 1000.0 );
	//Accessor declarations
	double								getCurrentYearlyDeposit( void ) const;
	double								getMaximumYearlyDeposit( void ) const;

	Date								getEndDepositPeriod( void ) const;

	ostream&							putDataInStream( ostream& os) const;
	istream&							getDataFromStream( istream& is);
	
protected:
	const string prepareFormattedAccountDetails() const;

private: //Private method declarations
	//Setter declarations
	void								updateCurrentYearlyDeposit( const double deposit );

private: //Private member instances
	double								currentYearlyDeposit_, maximumYearlyDeposit_;
	Date								endDepositPeriod_;
};

#endif