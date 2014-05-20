//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#include "CashPoint.h"

//---------------------------------------------------------------------------
//CashPoint: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

CashPoint::CashPoint()
	: p_theActiveAccount_( nullptr ), p_theCashCard_( nullptr )
{
	theUI_ = UserInterface::getUserInterface();
}

CashPoint::~CashPoint()
{
	if( p_theActiveAccount_ )
		releaseBankAccount( p_theActiveAccount_, p_theActiveAccount_->getFileName() );

	if( p_theCashCard_ )
		releaseCashCard();
}

//____other public member functions

void CashPoint::activateCashPoint( void )
{
	int command;
	theUI_->showWelcomeScreen();
    command = theUI_->readInCardIdentificationCommand();

	while ( command != QUIT_COMMAND )
    {
		performCardCommand( command);
	    theUI_->showByeScreen();
		command = theUI_->readInCardIdentificationCommand();
	}

}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void CashPoint::performCardCommand( const int option )
{
	if( option == 1 )
	{
		string cashCardNum;
		string cashCardFileName( theUI_->readInCardToBeProcessed( cashCardNum)); //read in card name & produce cashcard filename
        int validCardCode( validateCard( cashCardFileName));		//check valid card
        theUI_->showValidateCardOnScreen( validCardCode, cashCardNum);

        if ( validCardCode == VALID_CARD ) //valid card
        {
			activateCashCard( cashCardFileName ); //dynamically create a cash card & store card data
			theUI_->showCardOnScreen(  p_theCashCard_->toFormattedString() ); //display card data with available accounts
			processOneCustomerRequests(); //process all request for current card (& bank accounts)
			releaseCashCard(); //free memory space used by cash card
        }
	}
	else
		theUI_->showErrorInvalidCommand();
}

int CashPoint::validateCard( const string& cashCardFileName ) const
{
//check that the card exists (valid)
    if ( !canOpenFile( cashCardFileName ) )   //invalid card
        return UNKNOWN_CARD;
    else if ( !linkedCard( cashCardFileName ) )  
		return EMPTY_CARD; //card empty (exist but no bank account listed on card)
	else
		return VALID_CARD; //card valid (exists and linked to at least one bank account)
}

const int CashPoint::validateAccount( const string& bankAccountFileName ) const
{
	//check that the account is valid 
    int validBankCode = VALID_ACCOUNT; // default to valid.
	BankAccount *tempAccount = activateBankAccount( bankAccountFileName );

    if ( !canOpenFile( bankAccountFileName ) ) 
		validBankCode = UNKNOWN_ACCOUNT; //account does not exist
	else if ( ! p_theCashCard_->onCard( bankAccountFileName ) ) 
    	validBankCode = INACCESSIBLE_ACCOUNT;//inaccessible account (exist but not listed on card)
	else if( p_theActiveAccount_ && (*tempAccount == *p_theActiveAccount_) )
		validBankCode = SAME_ACCOUNT;//Same account, so you can't transfer to same account. 

	if( tempAccount )
		releaseBankAccount( tempAccount, bankAccountFileName );

    return validBankCode;
}

void CashPoint::processOneCustomerRequests( void )
{
	//process from one account
    string anAccountNumber, anAccountSortCode;
    //select active account and check that it is valid
    string bankAccountFileName( theUI_->readInAccountToBeProcessed( anAccountNumber, anAccountSortCode ) );
    int validAccountCode( validateAccount( bankAccountFileName ) );  //check valid account
    theUI_->showValidateAccountOnScreen( validAccountCode, anAccountNumber, anAccountSortCode );

    if ( validAccountCode == VALID_ACCOUNT ) //valid account: exists, accessible with card & not already open
    {
       	//dynamically create a bank account to store data from file
        p_theActiveAccount_ = activateBankAccount( bankAccountFileName );
		//process all request for current card (& bank accounts)
    	processOneAccountRequests();
		//store new state of bank account in file & free bank account memory space
        p_theActiveAccount_ = releaseBankAccount( p_theActiveAccount_, bankAccountFileName );
    }
}

void CashPoint::processOneAccountRequests( void )
{
	int option = theUI_->readInAccountProcessingCommand();
	//select option from account processing menu
	while ( option != QUIT_COMMAND )
	{
		performAccountProcessingCommand( option );   //process command for selected option
		theUI_->wait();
        option = theUI_->readInAccountProcessingCommand();   //select another option
	}
}


void CashPoint::performAccountProcessingCommand( const int option ) // option chosen by user on functionality
{
	switch ( option )
	{
		case 1:
			m1_produceBalance(); // displays their account balance
			break;

		case 2:
			m2_withdrawFromBankAccount(); // take money out
 			break;

		case 3:
			m3_depositToBankAccount(); // place money in account
			break;

		case 4:
			m4_produceStatement(); // show statement
			break;
				// new below
		case 5:
			m5_showAllDepositsTransactions(); // see all money deposited
			break;

		case 6:
			m6_showMiniStatement(); // show small version of statement
			break;

		case 7:
			m7_searchTransactions(); // search on user specified category
			break;

		case 8:
			m8_clearTransactionsUpToDate(); // remove transactions to user specified date
			break;

		case 9:
			m9_transferCashToAnotherAccount(); // transfer money from one account to another on same card
			break;

		default:
			theUI_->showErrorInvalidCommand(); // invalid input
	}
}

//------ menu options
//---option 1
void CashPoint::m1_produceBalance( void ) const
{
	double balance( p_theActiveAccount_->getBalance() ); // get balance
	theUI_->showProduceBalanceOnScreen( balance ); // show it
}

//---option 2
void CashPoint::m2_withdrawFromBankAccount( void )
{
    double amountToWithdraw( theUI_->readInWithdrawalAmount() ); // get amount from user
    bool transactionAuthorised( p_theActiveAccount_->canTransferOut( amountToWithdraw ) ); // true if authed

    if ( transactionAuthorised )//transaction is accepted: money can be withdrawn from account
        p_theActiveAccount_->recordWithdrawal( amountToWithdraw );

    theUI_->showWithdrawalOnScreen( transactionAuthorised, amountToWithdraw ); // display relevant text on screen
}

//---option 3
void CashPoint::m3_depositToBankAccount( void )
{
    const double amountToDeposit( theUI_->readInDepositAmount() ); // deposit from user
	const bool bCanTransferIn( p_theActiveAccount_->canTransferIn( amountToDeposit ) ); // true if can place in account

	if( bCanTransferIn )
		p_theActiveAccount_->recordDeposit( amountToDeposit ); // record deposit if taken place

	theUI_->showDepositOnScreen( bCanTransferIn, amountToDeposit ); // display on screen
}

//---option 4
void CashPoint::m4_produceStatement( void ) const // full statement
{
	theUI_->showStatementOnScreen( p_theActiveAccount_->prepareFormattedStatement() ); // prepare and display
}

//---option 5
void CashPoint::m5_showAllDepositsTransactions( void ) const
{
	string str;
	double total = 0.0;
	//checks to see if there are any transactions
	bool noTransaction = p_theActiveAccount_->isEmptyTransactionList();

	//if there are then produce the deposits
	if( !noTransaction )
		p_theActiveAccount_->produceAllDepositTransactions( str, total );

	//show the deposits on the screen.
	theUI_->showAllDepositsOnScreen( noTransaction, str, total );

}

//---option 6
void CashPoint::m6_showMiniStatement( void ) const
{
	string str;
	double total = 0.0;
	//check to see if there are any transactions
	bool noTransaction = p_theActiveAccount_->isEmptyTransactionList();
	
	if ( !noTransaction )
	{
		//ask the user how many transactions they want to see
		int noOfTran = theUI_->readInNumberOfTransactions();
		p_theActiveAccount_->produceNMostRecentTransactions( noOfTran, str, total );
	}
	//show the transactions on the screen.
	theUI_->showMiniStatementOnScreen(noTransaction, str, total);
}
//---option 7

void CashPoint::m7_searchTransactions( void ) const
{
	//output the menu and read in the search method
	int option = theUI_->readInTransactionSearchCommand();
	int numTransactions = 0;
	string transactions = "";

	if( !p_theActiveAccount_->getTransactions().size() )
	{
		theUI_->noTransactionsFound();
		return;
	}
	
	if( option == AMOUNT )
	{
		//call the readInSearchCriteria for double
		double criteria = theUI_->readInSearchCriteria<double>();
		//produce the transactions for that amount.
		//call the produceTransactionsForSearchCriteria for double
		transactions = p_theActiveAccount_->produceTransactionsForSearchCriteria<double>( criteria, numTransactions );

		//check to see if the returned number of transactions is 0
		//show no transactions if it is, otherwise send the transactions to the ui
		if( !numTransactions )
			theUI_->noTransactionsFound();
		else
			theUI_->showMatchingTransactionsOnScreen<double>( criteria, numTransactions, transactions );
	}
	else if( option == TITLE )
	{
		//call the readInSearchCriteria for string
		string criteria = theUI_->readInSearchCriteria<string>();
		//produce the transactions for that title.
		//call the produceTransactionsForSearchCriteria for string
		transactions = p_theActiveAccount_->produceTransactionsForSearchCriteria<string>( criteria, numTransactions );
		
		//check to see if the returned number of transactions is 0
		//show no transactions if it is, otherwise send the transactions to the ui
		if( !numTransactions )
			theUI_->noTransactionsFound();
		else
			theUI_->showMatchingTransactionsOnScreen<string>( criteria, numTransactions, transactions );
	}
	else if( option == DATE )
	{
		//call the readInSearchCriteria for date
		Date criteria = theUI_->readInSearchCriteria<Date>();
		//get the creation date of the account to check the user entered a valid date
		Date creationDate = p_theActiveAccount_->getCreationDate();
		
		//check to make sure the date is valid.
		if( !criteria.isValid( creationDate ) )
		{
			printf( "The date entered is invalid format <DD/MM/YYYY>, "
				"date must be on or after %s.\n", criteria.toFormattedString().c_str() );

			return;
		}
		
		//produce the transactions for that date.
		//call the produceTransactionsForSearchCriteria for date
		transactions = p_theActiveAccount_->produceTransactionsForSearchCriteria<Date>( criteria, numTransactions );

		//check to see if the returned number of transactions is 0
		//show no transactions if it is, otherwise send the transactions to the ui
		if( !numTransactions )
			theUI_->noTransactionsFound();
		else
			theUI_->showMatchingTransactionsOnScreen<Date>( criteria, numTransactions, transactions );
	}
}


/*void CashPoint::m7_searchTransactions( void ) const // non-recursive
{
	if( p_theActiveAccount_->isEmptyTransactionList() ) // have no transactions
	{
		theUI_->showNoTransactionsOnScreen(); // tell user
		return; // return
	}

	switch( theUI_->readInTransactionSearchCommand() ) // amount, title or date
	{
	case AMOUNT:
		m7a_showTransactionsForAmount();
		break;

	case TITLE:
		m7b_showTransactionsForTitle();
		break;

	case DATE:
		m7c_showTransactionsForDate(); 
		break;
	}
}

void CashPoint::m7a_showTransactionsForAmount( void ) const // before recursion
{
	int noTrans = 0;
	string strTrans;

	double amount = theUI_->readInAmount(); // read amount to search on
	p_theActiveAccount_->produceTransactionsForAmount( amount, strTrans, noTrans ); // collect results

	if( noTrans )
		theUI_->showMatchingTransactionsOnScreenAmount( amount, noTrans, strTrans ); // show user
	else
		theUI_->noTransactionsFound();
}

void CashPoint::m7b_showTransactionsForTitle( void ) const
{
	int noTrans = 0;
	string strTrans;

	string title = theUI_->readInTitle(); // read title from user
	p_theActiveAccount_->produceTransactionsForTitle( title, strTrans, noTrans ); //collect data

	if( noTrans )
		theUI_->showMatchingTransactionsOnScreenTitle( title, noTrans, strTrans ); // show user
	else
		theUI_->noTransactionsFound();
}

void CashPoint::m7c_showTransactionsForDate( void ) const
{
	int noTrans = 0;
	string strTrans;

	Date date = theUI_->readInValidDate( p_theActiveAccount_->getCreationDate() ); // read in from user
	p_theActiveAccount_->produceTransactionsForDate( date, strTrans, noTrans ); // collect results

	if( noTrans )
		theUI_->showMatchingTransactionsOnScreenDate( date, noTrans, strTrans ); // show user
	else
		theUI_->noTransactionsFound();
}*/

//---option 8
void CashPoint::m8_clearTransactionsUpToDate( void ) // clear to user specified date
{
	Date clearDate; // locals
	string transactions = "";
	int numTransactions( 0 );
	char answer = ' ';

	//check to see if there are any transactions in the account
	if( p_theActiveAccount_->isEmptyTransactionList() ) // if there are no transactions
	{
		//if not print appropriate response and return
		printf( "\nThere are no previous transactions stored for this account.\n" );
		return;
	}

	//read in a valid date to check the date is real and not before the creation date
	clearDate = theUI_->readInValidDate( p_theActiveAccount_->getCreationDate() );
	//get all the transactions before that date.
	transactions = p_theActiveAccount_->produceTransactionsUpToDate( clearDate, numTransactions );

	//make sure there are transactions returned.
	if( transactions.empty() )
	{
		printf( "\nThere are no prior transactions up to and on %s\n", clearDate.toFormattedString().c_str() );
		return;
	}

	//show the transactions found
	theUI_->showTransactionsUpToDateOnScreen( clearDate, numTransactions, transactions );
	//then check the user definately wants to delete them
	if( !theUI_->readInConfirmDeletion() )
		return;
	
	//delete the transactions and record it.
	p_theActiveAccount_->recordDeletionOfTransactionUpToDate( clearDate );
	theUI_->showDeletionOfTransactionUpToDateOnScreen( numTransactions, clearDate );
}

//---option 9
void CashPoint::m9_transferCashToAnotherAccount( void )
{
	//Instance declarations
	BankAccount *pToAccount = nullptr;
	string toAccNo = "", toSrtCode = "";
	string associated = p_theCashCard_->getAssociatedAccounts( p_theActiveAccount_ );
	//display card
	theUI_->showCardOnScreen( p_theCashCard_->toFormattedString(), true, associated );
	//Display accounts available to receive a transfer

	//Get the account from the user, and receive relevant file name
	string fileName = theUI_->readInAccountToBeProcessed( toAccNo, toSrtCode );
	//Get validation status of account
	const DWORD validation = validateAccount( fileName );
	theUI_->showValidateAccountOnScreen( validation, toAccNo, toSrtCode ); //Display validation text	 
	
	if( validation == VALID_ACCOUNT )
	{	//Get a new instance of the correct account
		pToAccount = activateBankAccount( fileName );
		attemptTransfer( pToAccount ); //attempt to transfer funds
	}		

	//Destroy the pointer to prevent leaks and store bank account state
	if( pToAccount )
		releaseBankAccount( pToAccount, fileName );

}

//------private file functions

bool CashPoint::canOpenFile( const string& st ) const
{
	FILE *file = nullptr;
	bool exist = false;

    if( !fopen_s( &file, st.c_str(), "r" ) ) // open file
	{
        exist = true; // returned 0 - file exists
		fclose( file ); // close the file
	}

    return exist;
}

bool CashPoint::linkedCard( string cashCardFileName ) const
{
//check that card is linked with account data
	ifstream inFile;
	inFile.open( cashCardFileName.c_str(), ios::in); 	//open file
 	bool linked(false);
	if ( ! inFile.fail()) //file should exist at this point 
	{	//check that it contain some info in addition to card number
		string temp;
		inFile >> temp; //read card number
		inFile >> temp;	//ready first account data or eof
		if (inFile.eof())
			linked = false;
		else
			linked = true;
		inFile.close();			//close file: optional here
	}
	return linked;
}

void CashPoint::attemptTransfer( BankAccount *pToAccount )
{
	//Transfer the money
	char answer = ' '; //For use with checking if the user wishes to continue
	const double amount = theUI_->readInTransferAmount();
	string tAN = "", tSC = "", aAN = "", aSC = "";

	//check the account can send the money
	//check the other account can recieve the money
	const bool trOutOk = p_theActiveAccount_->canTransferOut( amount );
	const bool trInOk  = pToAccount->canTransferIn( amount );

	if( trInOk && trOutOk )
	{
		//get the account number and sort code
		tAN = pToAccount->getAccountNumber();
		tSC = pToAccount->getSortCode();
		
		//check the user definately wants to transfer the money
		printf( "\nThe transfer can be granted.\n"
				"Are you sure you wish to transfer %.2f to %s %s (Y/N): ",
				amount, tAN.c_str(), tSC.c_str() );
			
		cin >> answer;

		if( answer == 'Y' || answer == 'y' )
		{
			//record the transfer out of the account
			p_theActiveAccount_->recordTransferOut( amount, tAN, tSC );
			
			aAN = p_theActiveAccount_->getAccountNumber();
			aSC = p_theActiveAccount_->getSortCode();
			//record the transfer into the account
			pToAccount->recordTransferIn( amount, aAN, aSC );
		}
		else
		{
			//else cancel the transfer
			printf( "\n\nTransfer cancelled.\n" );
			return;
		}
	}
	//show the transaction complete on the screen
	theUI_->showTransferOnScreen( trOutOk, trInOk, amount );
}

void CashPoint::activateCashCard( const string &aCCFileName )
{
//dynamically create a cash card to store data from file
    //effectively create the cash card instance with the data
	p_theCashCard_ = new CashCard;
    p_theCashCard_->readInCardFromFile( aCCFileName);
}

void CashPoint::releaseCashCard( void )
{
//release the memory allocated to the dynamic instance of a CashCard
	delete p_theCashCard_;
	p_theCashCard_ = nullptr;
}

int CashPoint::checkAccountType( const string& aBAFileName ) const
{
    //(simply) identify type/class of account from the account number
    //start with 0 for bank account, 1 for current account, 2 for saving account, etc.
	return( atoi( aBAFileName.substr( FILEPATH.length() + 8, 1).c_str() ));
}

BankAccount* CashPoint::activateBankAccount(  const string& aBAFileName ) const
{
	//check the type of the account (already checked for validity)
	int accType( checkAccountType( aBAFileName));
    //effectively create the active bank account instance of the appropriate class
	//& store the appropriate data read from the file
	BankAccount* p_BA( nullptr );

	switch( accType)
    {
		case CURRENT:
			cout << "\n-------CURRENT-------\n";
			p_BA = new CurrentAccount;
			p_BA->readInBankAccountFromFile( aBAFileName );
			break;

		case CHILDSAVINGS:
			cout << "\n-------CHILD-------\n";
			p_BA = new ChildAccount;
			p_BA->readInBankAccountFromFile( aBAFileName );
			break;

		case ISASAVINGS:
			cout << "\n-------ISA-------\n";
			p_BA = new ISAAccount;
			p_BA->readInBankAccountFromFile( aBAFileName );
			break;
    }
	//use dynamic memory allocation: the bank account created will have to be released in releaseBankAccount
	return p_BA;
}

BankAccount* CashPoint::releaseBankAccount( BankAccount* p_BA, const string aBAFileName ) const
{
//store (possibly updated) data back in file
    p_BA->storeBankAccountInFile( aBAFileName );
	//effectively destroy the bank account instance
	delete p_BA;
	return nullptr;
}