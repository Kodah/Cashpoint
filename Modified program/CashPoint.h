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
    void activateCashPoint( void );
private:
	//data items
    BankAccount* p_theActiveAccount_;
    CashCard* p_theCashCard_;
    UserInterface *theUI_;

	//support functions
	void performCardCommand( int );
    void performAccountProcessingCommand( int );
    int  validateCard( const string& ) const;
	int  validateAccount( const string& ) const;
	void processOneCustomerRequests( void );
	void processOneAccountRequests( void );

    void performSubMenuCommand( int );
    //commands
    //option 1
    void m1_produceBalance( void ) const;
    //option 2
    void m2_withdrawFromBankAccount( void );
    //option 3
    void m3_depositToBankAccount( void );
    //option 4
    void m4_produceStatement( void ) const;
	//option 5
	void m5_showAllDepositsTransactions( void );
	//option 6
	void m6_showMiniStatement( void );
	//option 7
	void m7_searchTransactions( void );//for option 7
	//void m7a_showTransactionsForAmount( void );//for option 7
	//void m7b_showTransactionsForTitle( void );//for option 7
	//void m7c_showTransactionsForDate( void );//for option 7
	//option 8
	void m8_clearTransactionsUpToDate( void );
	//option 9
	void m9_transferCashToAnotherAccount( void );

    //support file handling functions & creation of dynamic objects
    bool canOpenFile( const string& ) const;
	int checkAccountType( const string& ) const;
	bool linkedCard( string cashCardFileName ) const;

	void attemptTransfer( BankAccount *pToAccount );

	BankAccount* activateBankAccount( const string& );
	BankAccount* releaseBankAccount( BankAccount*, string);

    void activateCashCard( const string& );
	void releaseCashCard( void );

	void displayAssociatedAccounts( void ) const;
};

#endif
