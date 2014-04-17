//Pascale Vacher - March 14
//OOP Assignment Semester 2

#ifndef BankAccountH
#define BankAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"
#include "Constants.h"

#include <fstream>
using namespace std;


class BankAccount {
public:
    //constructors & destructor
	BankAccount();
    BankAccount( const string& typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList);
    ~BankAccount();

	//getter (assessor) functions
	const string getAccountType() const;
    const string getAccountNumber() const;
    const string getSortCode() const;
    const Date getCreationDate() const;
	double getBalance() const;
    const TransactionList getTransactions() const;
    bool	isEmptyTransactionList() const;

	//functions to put data into and get data from streams
	ostream& putDataInStream( ostream& os) const;
	istream& getDataFromStream( istream& is);

	//other operations
	const string prepareFormattedStatement() const;

    void recordDeposit( double amount);
	void recordTransfer( const double amount, const string transaction );

	double borrowable() const;
	bool canWithdraw( double amount) const;
    void recordWithdrawal( double amount);
	void transferMoney( double amount, BankAccount &toAccount );

	void readInBankAccountFromFile( const string& fileName);
	void storeBankAccountInFile( const string& fileName) const;
	void produceAllDepositTransactions(string& str, double& total) const;
	void produceNMostRecentTransactions(int noOfTran, string& str, double& total) const;

private:
    //data items
    string accountType_;
    string accountNumber_;
    string sortCode_;
    Date   creationDate_;
	double balance_;
    TransactionList transactions_;
 
	//support functions
	void updateBalance( double amount);
	const string prepareFormattedAccountDetails() const;

};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const BankAccount&);	//output operator
istream& operator>>( istream&, BankAccount&);	    //input operator

#endif
