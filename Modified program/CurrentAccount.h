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

	void								transferMoney( const double amount, BankAccount *toAccount );

	ostream&							putDataInStream( ostream& os) const;
	istream&							getDataFromStream( istream& is);
	
protected:
	const string prepareFormattedAccountDetails() const;

private: //Private member instances
	double overdraftLimit_;

};

#endif