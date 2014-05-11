//Mike Orr, Luke Segaran, Tom sugarev - May 14

#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H

#include "BankAccount.h"

class CurrentAccount : public BankAccount
{
public: //Public declarations
	//Constructors/Destructors
	CurrentAccount( const double overdraftLimit = 0.0 );
	CurrentAccount( const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList, const double overdraftLimit = 0.0 );

	//Accessor declarations
	double								getOverdraftLimit( void ) const;

	virtual ostream&					putDataInStream( ostream& os) const;
	virtual istream&					getDataFromStream( istream& is);

	virtual const bool					canTransferOut( const double amount ) const;
	
protected:
	const string prepareFormattedAccountDetails() const;

private: //Private member instances
	double overdraftLimit_;

};

#endif