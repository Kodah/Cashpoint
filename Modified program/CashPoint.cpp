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

	while ( command != QUIT_COMMAND)
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
    int validCardCode;

    if ( !canOpenFile( cashCardFileName ) )   //invalid card
        return UNKNOWN_CARD;
    else if ( !linkedCard( cashCardFileName ) )  
		return EMPTY_CARD; //card empty (exist but no bank account listed on card)
	else
		return VALID_CARD; //card valid (exists and linked to at least one bank account)
}

int CashPoint::validateAccount( const string& bankAccountFileName ) const
{
//check that the account is valid 
//MORE WORK NEEDED: in case of transfer
    int validBankCode;

    if ( !canOpenFile( bankAccountFileName ) ) 
		validBankCode = UNKNOWN_ACCOUNT; //account does not exist
	else if ( ! p_theCashCard_->onCard( bankAccountFileName ) ) //unaccessible account (exist but not listed on card)
    	validBankCode = INACCESSIBLE_ACCOUNT;
	else
		validBankCode = VALID_ACCOUNT; //account valid (exists and accessible)

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


void CashPoint::performAccountProcessingCommand( const int option )
{
	switch ( option )
	{
		case 1:
			m1_produceBalance();
			break;

		case 2:
			m2_withdrawFromBankAccount();
 			break;

		case 3:
			m3_depositToBankAccount();
			break;

		case 4:
			m4_produceStatement();
			break;
				// new below
		case 5:
			m5_showAllDepositsTransactions();
			break;

		case 6:
			m6_showMiniStatement();
			break;

		case 7:
			m7_searchTransactions();
			break;

		case 8:
			m8_clearTransactionsUpToDate();
			break;

		case 9:
			m9_transferCashToAnotherAccount();
			break;

		default:
			theUI_->showErrorInvalidCommand();
	}
}

//------ menu options
//---option 1
void CashPoint::m1_produceBalance( void ) const
{
	double balance( p_theActiveAccount_->getBalance() );
	theUI_->showProduceBalanceOnScreen( balance );
}

//---option 2
void CashPoint::m2_withdrawFromBankAccount( void )
{
    double amountToWithdraw( theUI_->readInWithdrawalAmount() );
    bool transactionAuthorised( p_theActiveAccount_->canWithdraw( amountToWithdraw ) );

    if ( transactionAuthorised)
    {   //transaction is accepted: money can be withdrawn from account
        p_theActiveAccount_->recordWithdrawal( amountToWithdraw);
    }   //else do nothing

    theUI_->showWithdrawalOnScreen( transactionAuthorised, amountToWithdraw);
}

//---option 3
void CashPoint::m3_depositToBankAccount( void )
{
    const double amountToDeposit( theUI_->readInDepositAmount() );
	const bool bCanTransferIn( p_theActiveAccount_->canTransferIn( amountToDeposit ) );

	if( bCanTransferIn )
		p_theActiveAccount_->recordDeposit( amountToDeposit );

	theUI_->showDepositOnScreen( bCanTransferIn, amountToDeposit );
}

//---option 4
void CashPoint::m4_produceStatement( void ) const
{
	theUI_->showStatementOnScreen( p_theActiveAccount_->prepareFormattedStatement() );
}

//---option 5
void CashPoint::m5_showAllDepositsTransactions( void ) const
{
	string str;
	double total = 0.0;

	bool noTransaction = p_theActiveAccount_->isEmptyTransactionList();

	if( !noTransaction )
		p_theActiveAccount_->produceAllDepositTransactions(str, total );

	theUI_->showAllDepositsOnScreen( noTransaction, str, total );

}

//---option 6
void CashPoint::m6_showMiniStatement( void ) const
{
	string str;
	double total = 0.0;

	bool noTransaction = p_theActiveAccount_->isEmptyTransactionList();
	
	if ( !noTransaction )
	{
		int noOfTran = theUI_->readInNumberOfTransactions();
		p_theActiveAccount_->produceNMostRecentTransactions( noOfTran, str, total );
	}

	theUI_->showMiniStatementOnScreen(noTransaction, str, total);
}
//---option 7

void CashPoint::m7_searchTransactions( void ) const
{
	int option = theUI_->readInTransactionSearchCommand();
	int numTransactions = 0;
	string transactions = "";
	
	if( option == 1 )
	{
		double criteria = theUI_->readInSearchCriteria<double>();
		transactions = p_theActiveAccount_->produceTransactionsForSearchCriteria<double>( criteria, numTransactions );

		if( !numTransactions )
			theUI_->noTransactionsFound();
		else
			theUI_->showMatchingTransactionsOnScreen<double>( criteria, numTransactions, transactions );
	}
	else if( option == 2 )
	{
		string criteria = theUI_->readInSearchCriteria<string>();
		transactions = p_theActiveAccount_->produceTransactionsForSearchCriteria<string>( criteria, numTransactions );

		if( !numTransactions )
			theUI_->noTransactionsFound();
		else
			theUI_->showMatchingTransactionsOnScreen<string>( criteria, numTransactions, transactions );
	}
	else if( option == 3 )
	{
		Date criteria = theUI_->readInSearchCriteria<Date>();
		Date creationDate = p_theActiveAccount_->getCreationDate();

		if( !criteria.isValid( creationDate ) )
		{
			printf( "The date entered is invalid format <DD/MM/YYYY>, "
				"date must be on or after %s.\n", criteria.toFormattedString().c_str() );

			return;
		}

		transactions = p_theActiveAccount_->produceTransactionsForSearchCriteria<Date>( criteria, numTransactions );

		if( !numTransactions )
			theUI_->noTransactionsFound();
		else
			theUI_->showMatchingTransactionsOnScreen<Date>( criteria, numTransactions, transactions );
	}
}


/*void CashPoint::m7_searchTransactions( void ) const
{
	if( p_theActiveAccount_->isEmptyTransactionList() )
	{
		theUI_->showNoTransactionsOnScreen();
		return;
	}

	switch( theUI_->readInTransactionSearchCommand() )
	{
	case AMOUNT:
		m7a_showTransactionsForAmount();
		//m7_showTransactions(1);
		break;

	case TITLE:
		m7b_showTransactionsForTitle();
		//m7_showTransactions(2);
		break;

	case DATE:
		m7c_showTransactionsForDate(); 
		//m7_showTransactions(3);
		break;
	}
}

void CashPoint::m7a_showTransactionsForAmount( void ) const
{
	int noTrans = 0;
	string strTrans;

	double amount = theUI_->readInAmount();
	p_theActiveAccount_->produceTransactionsForAmount( amount, strTrans, noTrans );

	if( noTrans )
		theUI_->showMatchingTransactionsOnScreenAmount( amount, noTrans, strTrans );
	else
		theUI_->noTransactionsFound();
}

void CashPoint::m7b_showTransactionsForTitle( void ) const
{
	int noTrans = 0;
	string strTrans;

	string title = theUI_->readInTitle();
	p_theActiveAccount_->produceTransactionsForTitle( title, strTrans, noTrans );

	if( noTrans )
		theUI_->showMatchingTransactionsOnScreenTitle( title, noTrans, strTrans );
	else
		theUI_->noTransactionsFound();
}

void CashPoint::m7c_showTransactionsForDate( void ) const
{
	int noTrans = 0;
	string strTrans;

	Date date = theUI_->readInValidDate( p_theActiveAccount_->getCreationDate() );
	p_theActiveAccount_->produceTransactionsForDate( date, strTrans, noTrans );

	if( noTrans )
		theUI_->showMatchingTransactionsOnScreenDate( date, noTrans, strTrans );
	else
		theUI_->noTransactionsFound();
}*/

//---option 8
void CashPoint::m8_clearTransactionsUpToDate( void )
{
	Date clearDate;
	string transactions = "";
	int numTransactions( 0 );
	char answer = ' ';

	if( p_theActiveAccount_->isEmptyTransactionList() )
	{
		cout << "There are no previous transactions stored for this account." << endl;
		return;
	}

	clearDate = theUI_->readInValidDate( p_theActiveAccount_->getCreationDate() );
	transactions = p_theActiveAccount_->produceTransactionsUpToDate( clearDate, numTransactions );

	if( transactions.empty() )
	{
		printf( "There are no prior transactions up to and on %s\n", clearDate.toFormattedString().c_str() );
		return;
	}

	theUI_->showTransactionsUpToDateOnScreen( clearDate, numTransactions, transactions );

	if( !theUI_->readInConfirmDeletion() )
		return;

	p_theActiveAccount_->recordDeletionOfTransactionUpToDate( clearDate );
	theUI_->showDeletionOfTransactionUpToDateOnScreen( numTransactions, clearDate );
}

//---option 9
void CashPoint::m9_transferCashToAnotherAccount( void )
{
	//Instance declarations
	BankAccount *pToAccount = nullptr;
	string toAccNo = "", toSrtCode = "";

	//display card
	theUI_->showCardOnScreen( p_theCashCard_->toFormattedString() );
	//Display accounts available to receive a transfer
	displayAssociatedAccounts();
	printf( "\nSELECT ACCOUNT TO TRANSFER TO...\n" );
	//Get the account from the user, and receive relevant file name
	string fileName = theUI_->readInAccountToBeProcessed( toAccNo, toSrtCode );
	//Get validation status of account
	const DWORD validation = validateAccount( fileName );
	
	if( validation == VALID_ACCOUNT )
	{	//Get a new instance of the correct account
		pToAccount = activateBankAccount( fileName );

			//Check if the account we are transferring to is the same as the active account
		if( *p_theActiveAccount_ == *pToAccount )
		{
			printf( "\nTHE ACCOUNT (NUMBER: %s CODE: %s) IS ALREADY OPEN!\n",
				toAccNo.c_str(), toSrtCode.c_str() );
		}
		else
		{
			//Display validation text		
			theUI_->showValidateAccountOnScreen( validation, toAccNo, toSrtCode );
			attemptTransfer( pToAccount );
		}
	}
	else //Display validation text		
		theUI_->showValidateAccountOnScreen( validation, toAccNo, toSrtCode );

	//Destroy the pointer to prevent leaks and store bank account state
	if( pToAccount )
		releaseBankAccount( pToAccount, fileName );

}

//------private file functions

bool CashPoint::canOpenFile( const string& st ) const
{
//check if a file already exist
	ifstream inFile;
	inFile.open( st.c_str(), ios::in); 	//open file
	//if does not exist fail, otherwise open file but do nothing to it
	bool exist;
    if ( inFile.fail())
        exist = false;
    else
        exist = true;
    inFile.close();			//close file: optional here
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

	const bool trOutOk = p_theActiveAccount_->canTransferOut( amount );
	const bool trInOk  = pToAccount->canTransferIn( amount );

	if( trInOk && trOutOk )
	{
		tAN = pToAccount->getAccountNumber();
		tSC = pToAccount->getSortCode();

		printf( "\nThe transfer can be granted.\n"
				"Are you sure you wish to transfer %.2f to %s %s (Y/N): ",
				amount, tAN.c_str(), tSC.c_str() );
			
		cin >> answer;

		if( answer == 'Y' || answer == 'y' )
		{
			p_theActiveAccount_->recordTransferOut( amount, tAN, tSC );

			aAN = p_theActiveAccount_->getAccountNumber();
			aSC = p_theActiveAccount_->getSortCode();

			pToAccount->recordTransferIn( amount, aAN, aSC );
		}
		else
		{
			printf( "\n\nTransfer cancelled.\n" );
			return;
		}
	}

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

BankAccount* CashPoint::activateBankAccount(  const string& aBAFileName )
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

BankAccount* CashPoint::releaseBankAccount( BankAccount* p_BA, string aBAFileName )
{
//store (possibly updated) data back in file
    p_BA->storeBankAccountInFile( aBAFileName);
	//effectively destroy the bank account instance
	delete p_BA;
	return nullptr;
}

void CashPoint::displayAssociatedAccounts( void ) const
{
	List <string> accountList = p_theCashCard_->getAccountsList();
	string activeAccNo = p_theActiveAccount_->getAccountNumber();
	string activeSrtCode = p_theActiveAccount_->getSortCode();

	while( !accountList.isEmpty() )
	{
		string temp = accountList.first();

		if( temp.substr( 0, 3 ).c_str() != activeAccNo ||
			temp.substr( 4, 5 ).c_str() != activeSrtCode )
		{
			printf( "ACCOUNT NO: %s\tSORT CODE: %s\n",
				temp.substr( 0, 3 ).c_str(),
				temp.substr( 4, 5 ).c_str() );
		}

		accountList.deleteFirst();
	}
}