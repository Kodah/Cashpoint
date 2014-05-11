//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#ifndef BankAccountH
#define BankAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

#include "TransactionList.h"
#include "Constants.h"

#include <fstream>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::ios;

class BankAccount
{
public:
    //constructors & destructor
	BankAccount();
    BankAccount( const string& typ, const string& acctNum, const string& sCode,
                 const Date& cD, const double b, const TransactionList& trList );

    ~BankAccount();

	//getter (assessor) functions
	const string getAccountType( void ) const;
    const string getAccountNumber( void ) const;
    const string getSortCode( void ) const;
    const Date getCreationDate( void ) const;
	double getBalance( void ) const;
    const TransactionList getTransactions( void ) const;
	string getFileName( void ) const;

    const bool isEmptyTransactionList( void ) const;
	virtual const bool canTransferOut( const double amount ) const;
	virtual const bool canTransferIn( const double amount ) const;


	//functions to put data into and get data from streams
	virtual ostream& putDataInStream( ostream &os ) const = 0;
	virtual istream& getDataFromStream( istream &is ) = 0;

	//other operations
	const string prepareFormattedStatement( void ) const;

    void recordDeposit( const double amount );

	virtual void recordTransferIn( const double amount, const string aAN, const string aSC );
	void recordTransferOut( const double amount, const string tAN, const string tSC );

    void recordWithdrawal( double amount );

	void readInBankAccountFromFile( const string &fileName );
	void storeBankAccountInFile( const string &fileName ) const;
	void produceAllDepositTransactions( string &str, double &total ) const;
	void produceNMostRecentTransactions( const int noOfTran, string &str, double &total ) const;
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

ostream& operator<<( ostream&, const BankAccount& ); //output operator
istream& operator>>( istream&, BankAccount& ); //input operator
bool operator !=( BankAccount &bA1, BankAccount &bA2 );	//Not equal comparison operator
bool operator ==( BankAccount &bA1, BankAccount &bA2 );	//Equal comparison operator

#endif
