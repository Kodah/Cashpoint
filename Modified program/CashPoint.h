//Pascale Vacher - March 14
//OOP Assignment Semester 2

#ifndef CashPointH
#define CashPointH 

//---------------------------------------------------------------------------
//CashPoint: class declaration
//---------------------------------------------------------------------------

#include "CashCard.h"

#include "CurrentAccount.h"
#include "ChildAccount.h"
#include "ISAAccount.h"

#include "UserInterface.h"

#include <fstream>
#include <string>
#include <list>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
using namespace std;

class CashPoint {
public:
	//constructors & destructor
	CashPoint();	//default constructor
	~CashPoint();	//destructor
    void activateCashPoint();
private:
	//data items
    BankAccount* p_theActiveAccount_;
    CashCard* p_theCashCard_;
    UserInterface *theUI_;

	//support functions
	void performCardCommand( int);
    void performAccountProcessingCommand( int);
    int  validateCard( const string&) const;
	int  validateAccount( const string&) const;
	void processOneCustomerRequests();
	void processOneAccountRequests();

    void performSubMenuCommand( int);
    //commands
    //option 1
    void m1_produceBalance() const;
    //option 2
    void m2_withdrawFromBankAccount();
    //option 3
    void m3_depositToBankAccount();
    //option 4
    void m4_produceStatement() const;
	//option 5
	void m5_showAllDepositsTransactions();
	//option 6
	void m6_showMiniStatement();
	//option 7
	void m7_searchTransactions();//for option 7
	void m7a_showTransactionsForAmount();//for option 7
	void m7b_showTransactionsForTitle();//for option 7
	void m7c_showTransactionsForDate();//for option 7
	//option 8
	void m8_clearTransactionsUpToDate();
	//option 9
	void m9_transferCashToAnotherAccount();

    //support file handling functions & creation of dynamic objects
    bool canOpenFile( const string&) const;
	int checkAccountType( const string&) const;
	bool linkedCard( string cashCardFileName) const;

	void attemptTransfer( BankAccount *pToAccount );

	BankAccount* activateBankAccount( const string&);
	BankAccount* releaseBankAccount( BankAccount*, string);

    void activateCashCard( const string&);
	void releaseCashCard();

	void displayAssociatedAccounts( void ) const;
};

#endif
