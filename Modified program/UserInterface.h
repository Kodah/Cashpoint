//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#ifndef UserInterfaceH 
#define UserInterfaceH

//---------------------------------------------------------------------------
//UserInterface: class declaration
//---------------------------------------------------------------------------
//microsoft library includes
#include <iostream>

//our header includes
#include "BankAccount.h"

//removed using namespace std to prevent namespace pollution
using std::cin;

class UserInterface // UserInterface Singleton class
{
private: //constructors + destructors
	UserInterface();
	~UserInterface();

	static UserInterface *uI; //for singleton implementation
public:
	static UserInterface*			getUserInterface( void );
									//Get input from user
	int								readInCardIdentificationCommand( void ) const;
	int								readInAccountProcessingCommand( void ) const;
	int								readInTransactionSearchCommand( void ) const;
	const string					readInCardToBeProcessed( string& cardNum ) const;
	const string					readInAccountToBeProcessed( string& aNum, string& sCod ) const;
	double							readInWithdrawalAmount( void ) const;
    double							readInDepositAmount( void ) const;
	int								readInNumberOfTransactions( void ) const;

	template <typename T> T			readInSearchCriteria( void ) const;
	
	double							readInAmount( void ) const;
	const double					readInTransferAmount( void ) const;
	string							readInTitle( void ) const;
	Date							readInValidDate( const Date d ) const;
	double							readInPositiveAmount( void ) const;
	bool							readInConfirmDeletion( void ) const;

    void							wait( void ) const; //hold
									//Display declarations
	void							showWelcomeScreen( void ) const;
    void							showByeScreen( void ) const;
	void							showErrorInvalidCommand( void ) const; //display error
    void							showValidateCardOnScreen( int validCode, const string& cardNum ) const;
	void							showCardOnScreen( const string& cardSt, const bool bAssociated = false, const string associated = "" ) const;

	void							showValidateAccountOnScreen( const int valid, const string& aNum, const string& sCod ) const;
	void							displayAssociatedAccounts( const string associated = "" ) const;

	void							noTransactionsFound( void ) const;//for option 7
									//Before using templates
	//void							showMatchingTransactionsOnScreenAmount( const double amount, const int noTrans, const string strTrans ) const;
	//void							showMatchingTransactionsOnScreenTitle( const string title, const int noTrans, const string strTrans ) const;
	//void							showMatchingTransactionsOnScreenDate( const Date date, const int noTrans, const string strTrans ) const;
	template <typename T> void		showMatchingTransactionsOnScreen( const T criteria, const int noTrans, const string strTrans ) const; //replaces above 3

	void							showTransactionsUpToDateOnScreen( const Date date, const int numTransactions, string transactions ) const;
	void							showProduceBalanceOnScreen( double bal ) const;
    void							showDepositOnScreen( const bool auth, const double deposit ) const;
    void							showWithdrawalOnScreen( bool auth, double withdrawal ) const;
    void							showStatementOnScreen( const string& ) const;
	void							showAllDepositsOnScreen( const bool noTransaction, const string str, const double total ) const;
	void							showMiniStatementOnScreen( const bool noTransaction, const string str, const double total ) const;
	void							showNoTransactionsOnScreen( void ) const;
	void							showDeletionOfTransactionUpToDateOnScreen( const int numTransactions, const Date date ) const;
	void							showTransferOnScreen( const bool trOutOk, const bool trInOk, const double amount ) const;

private: //private support declarations
	void							showCardIdentificationMenu( void ) const;
	void							showAccountProcessingMenu( void ) const;
	void							showTransactionSearchMenu( void ) const;
    int								readInCommand( void ) const;
};

#endif
