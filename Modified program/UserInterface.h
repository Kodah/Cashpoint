//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#ifndef UserInterfaceH 
#define UserInterfaceH

//---------------------------------------------------------------------------
//UserInterface: class declaration
//---------------------------------------------------------------------------
#include <iostream>

#include "Time.h"
#include "Date.h"

using std::cout;
using std::endl;
using std::cin;

class UserInterface
{
private:
	UserInterface();
	~UserInterface();

	static UserInterface *uI;
public:
    void	showWelcomeScreen() const;
    void	showByeScreen() const;

	static UserInterface* getUserInterface( void );

	int		readInCardIdentificationCommand() const;
	int		readInAccountProcessingCommand() const;
	int		readInTransactionSearchCommand( void ) const;

	void	showErrorInvalidCommand() const;
    void	wait() const;
	const string	readInCardToBeProcessed( string& cardNum) const;
    void	showValidateCardOnScreen( int validCode, const string& cardNum) const;
	void	showCardOnScreen( const string& cardSt) const;
	const string  readInAccountToBeProcessed( string& aNum, string& sCod) const;
	void	showValidateAccountOnScreen( const int valid, const string& aNum, const string& sCod) const;

    double	readInWithdrawalAmount() const;
    double	readInDepositAmount() const;
	int		readInNumberOfTransactions() const; //not sure if this is in the right group of functions	

	template <typename T> T readInSearchCriteria( void ) const;
	
	double	readInAmount() const; //for option 7
	const double readInTransferAmount( void ) const;
	string  readInTitle() const; //for option 7
	Date	readInValidDate( const Date d ) const;
	void	noTransactionsFound() const;//for option 7

	//void showMatchingTransactionsOnScreenAmount( const double amount, const int noTrans, const string strTrans ) const; //for option 7
	//void showMatchingTransactionsOnScreenTitle( const string title, const int noTrans, const string strTrans ) const; //for option 7
	//void showMatchingTransactionsOnScreenDate( const Date date, const int noTrans, const string strTrans ) const; //for option 7
	template <typename T> void showMatchingTransactionsOnScreen( const T criteria, const int noTrans, const string strTrans ) const;

	void showTransactionsUpToDateOnScreen( const Date date, const int numTransactions, string transactions ) const;

	double	readInPositiveAmount() const;

    void	showProduceBalanceOnScreen( double bal) const;
    void	showDepositOnScreen( const bool auth, const double deposit ) const;
    void	showWithdrawalOnScreen( bool auth, double withdrawal) const;
    void	showStatementOnScreen( const string&) const;
	void	showAllDepositsOnScreen(bool noTransaction, string str, double total) const;
	void	showMiniStatementOnScreen( const bool noTransaction, const string str, const double total ) const;
	void	showNoTransactionsOnScreen( void ) const;
	void	showDeletionOfTransactionUpToDateOnScreen( const int numTransactions, const Date date ) const;
	void	showTransferOnScreen( const bool trOutOk, const bool trInOk, const double amount ) const;

	bool	readInConfirmDeletion( void ) const;

private:
    //support functions
	void	showCardIdentificationMenu() const;
	void	showAccountProcessingMenu() const;
	void	showTransactionSearchMenu() const;
    int		readInCommand() const;
};

#endif
