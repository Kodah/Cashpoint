//Mike Orr, Luke Segaran, Tom sugarev - May 14
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

class CashPoint
{
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
	void performCardCommand( const int );
    void performAccountProcessingCommand( const int );
    int  validateCard( const string& ) const;
	int  validateAccount( const string& ) const;
	void processOneCustomerRequests( void );
	void processOneAccountRequests( void );

    //commands
    
    void m1_produceBalance( void ) const; //option 1
    void m2_withdrawFromBankAccount( void ); //option 2
    void m3_depositToBankAccount( void ); //option 3
    void m4_produceStatement( void ) const; //option 4
	void m5_showAllDepositsTransactions( void ) const; //option 5
	void m6_showMiniStatement( void ) const; //option 6
	void m7_searchTransactions( void ) const; //option 7
	//void m7a_showTransactionsForAmount( void ) const;
	//void m7b_showTransactionsForTitle( void ) const;
	//void m7c_showTransactionsForDate( void ) const;
	void m8_clearTransactionsUpToDate( void ); //option 8
	void m9_transferCashToAnotherAccount( void ); //option 9

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
