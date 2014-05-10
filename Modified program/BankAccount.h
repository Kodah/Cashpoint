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


class BankAccount
{
public:
    //constructors & destructor
	BankAccount();
    BankAccount( const string& typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList );
    ~BankAccount();

	//getter (assessor) functions
	const string getAccountType() const;
	static const char * getTypeFromFile( const string accNo, const string srtCode );
    const string getAccountNumber() const;
    const string getSortCode() const;
    const Date getCreationDate() const;
	double getBalance() const;
    const TransactionList getTransactions() const;
	string getFileName( void ) const;
    bool	isEmptyTransactionList() const;

	//functions to put data into and get data from streams
	virtual ostream& putDataInStream( ostream& os ) const = 0;
	virtual istream& getDataFromStream( istream& is ) = 0;

	//other operations
	const string prepareFormattedStatement() const;

    void recordDeposit( double amount);
	void recordTransfer( const double amount, const string transaction );

	double borrowable() const;
	virtual bool canWithdraw( double amount ) const;
    void recordWithdrawal( double amount );

	virtual void transferMoney( const double amount, BankAccount *toAccount );

	void readInBankAccountFromFile( const string& fileName );
	void storeBankAccountInFile( const string& fileName ) const;
	void produceAllDepositTransactions( string& str, double& total ) const;
	void produceNMostRecentTransactions( const int noOfTran, string& str, double& total ) const;
	string produceTransactionsUpToDate( const Date date, int &numTransactions ) const;

	//void produceTransactionsForAmount( const double amount, string& strTrans, int& noTrans ) const;
	//void produceTransactionsForDate( const Date date, string& strTrans, int& noTrans ) const;
	//void produceTransactionsForTitle( const string title, string& strTrans, int& noTrans ) const;

	template <typename T>
	string produceTransactionsForSearchCriteria( const T searchVal, int& noTrans ) const;

	void updateBalance( const double amount );
	void deleteTransactionsUpToDate( const Date d );

	void recordDeletionOfTransactionUpToDate( const Date date );

protected:
    //data items
    string accountType_, accountNumber_, sortCode_, fileName_;
    Date   creationDate_;
	double balance_;
    TransactionList transactions_;
 
	//support functions
	
	virtual const string prepareFormattedAccountDetails() const = 0;

};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const BankAccount& );		//output operator
istream& operator>>( istream&, BankAccount& );			//input operator
bool operator !=( BankAccount &bA1, BankAccount &bA2 );	//Not equal comparison operator
bool operator ==( BankAccount &bA1, BankAccount &bA2 );	//Equal comparison operator

#endif
