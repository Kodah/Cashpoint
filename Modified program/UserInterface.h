//Pascale Vacher - March 14
//OOP Assignment Semester 2

#ifndef UserInterfaceH 
#define UserInterfaceH

//---------------------------------------------------------------------------
//UserInterface: class declaration
//---------------------------------------------------------------------------
#include "Time.h"
#include "Date.h"
#include "constants.h"

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class UserInterface
{
public:
	//constructors & destructor
    void	showWelcomeScreen() const;
    void	showByeScreen() const;

	int		readInCardIdentificationCommand() const;
	int		readInAccountProcessingCommand() const;
	int		readInTransactionSearchCommand() const;

	void	showErrorInvalidCommand() const;
    void	wait() const;
	const string	readInCardToBeProcessed( string& cardNum) const;
    void	showValidateCardOnScreen( int validCode, const string& cardNum) const;
	void	showCardOnScreen( const string& cardSt) const;
	const string  readInAccountToBeProcessed( string& aNum, string& sCod) const;
	void	showValidateAccountOnScreen( int valid, const string& aNum, const string& sCod) const;

    double	readInWithdrawalAmount() const;
    double	readInDepositAmount() const;
	int		readInNumberOfTransactions() const; //not sure if this is in the right group of functions	

	template <typename T> T UreadInSearchCriterion( void ) const;
	
	double	readInAmount() const; //for option 7
	string  readInTitle() const; //for option 7
	Date	readInValidDate( const Date d ) const;
	void	noTransactionsFound() const;//for option 7

	void showMatchingTransactionsOnScreenAmount(double amount, int noTrans, string strTrans) const; //for option 7
	void showMatchingTransactionsOnScreenTitle(string title, int noTrans, string strTrans) const; //for option 7
	void showMatchingTransactionsOnScreenDate(Date date, int noTrans, string strTrans) const; //for option 7

	void showTransactionsUpToDateOnScreen( const Date date, const int numTransactions, string transactions ) const;

	double	readInPositiveAmount() const;

    void	showProduceBalanceOnScreen( double bal) const;
    void	showDepositOnScreen( bool auth, double deposit) const;
    void	showWithdrawalOnScreen( bool auth, double withdrawal) const;
    void	showStatementOnScreen( const string&) const;
	void	showAllDepositsOnScreen(bool noTransaction, string str, double total) const;
	void	showMiniStatementOnScreen(bool noTransaction, string str, double total) const;
	void	showNoTransactionsOnScreen( void ) const;
	void	showDeletionOfTransactionUpToDateOnScreen( const int numTransactions, const Date date ) const;

	bool	readInConfirmDeletion( void ) const;

private:
    //support functions
	void	showCardIdentificationMenu() const;
	void	showAccountProcessingMenu() const;
	void	showTransactionSearchMenu() const;
    int		readInCommand() const;
};

#endif
