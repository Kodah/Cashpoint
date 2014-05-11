//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#include "UserInterface.h" 

//---------------------------------------------------------------------------
//UserInterface: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors & instance getter

UserInterface* UserInterface::uI = nullptr;

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
	delete uI;
}

UserInterface* UserInterface::getUserInterface( void )
{
	if( !uI )
		uI = new UserInterface();
	
	return uI;
}

//____other public member functions

//menu functions

void UserInterface::wait( void ) const
{
	char ch = ' ';

	cout << "\n\nPress RETURN to go back to menu\n";

	cin.get( ch );
	cin.get( ch );
}

int UserInterface::readInCardIdentificationCommand( void ) const
{
    showCardIdentificationMenu();
    return ( readInCommand() );
}

void UserInterface::showCardIdentificationMenu( void ) const
{
	cout << endl << endl << endl
		 << "      ________________________________________"
		 << endl << "      _______CARD IDENTIFICATION MENU________"
		 << endl << "      ________________________________________"
		 << endl << "       0           Quit CashPoint application"
		 << endl << "       1              Enter your card details"
		 << endl << "      ________________________________________";
}

int UserInterface::readInAccountProcessingCommand( void ) const
{
    showAccountProcessingMenu();
    return ( readInCommand() );
}

void UserInterface::showAccountProcessingMenu( void ) const
{
	cout << endl << endl << endl
		 << endl << "      ________________________________________"
		 << endl << "      ________ACCOUNT PROCESSING MENU________"
		 << endl << "      ________________________________________"
		 << endl << "       0 End account processing & remove card"
		 << endl << "       1                      Display balance"
		 << endl << "       2                Withdraw from account"
		 << endl << "       3                 Deposit into account"
		 << endl << "       4                       Show statement"
		 << endl << "       5                    Show all deposits"
		 << endl << "       6                  Show mini statement"
		 << endl << "       7           Show transactions by search"
		 << endl << "       8    Clear all transactions up to date"
		 << endl << "       9          Transfer to another account"
		 << endl << "       ________________________________________";
}

int UserInterface::readInTransactionSearchCommand( void ) const
{
	showTransactionSearchMenu();
	return readInCommand();
}
void UserInterface::showTransactionSearchMenu( void ) const
{
	cout << endl << endl << endl
		 << "				________________________________________"
		 << endl << "		________TRANSACTION SEARCH MENU_________"
		 << endl << "		________________________________________"
		 << endl << "		1 Search by amount"
		 << endl << "		2 Search by title"
		 << endl << "		3 Search by date"
		 << endl << "		4 Exit without search"
		 << endl << "		________________________________________";
}

const string UserInterface::readInCardToBeProcessed( string& aCardNumber) const
{
	cout << "\n SELECT THE CARD ...\n";

	cout << "   CARD NUMBER:  ";         //ask for card number
    cin >> aCardNumber;

    cout << endl << "=========================================";
    //create card file name
    return ( FILEPATH + "card_" + aCardNumber + ".txt" );
}

//Template function for option 7
template <typename T>
T UserInterface::readInSearchCriteria( void ) const
{
	T searchCriteria;

	cout << endl;
	//check the type of T to print the correct request
	if( typeid( T ) == typeid( double ) )
		cout << "Please enter amount to search on: ";
	else if( typeid( T ) == typeid( string ) )
		cout << "Please enter the transaction title: ";
	else if( typeid( T ) == typeid( Date ) )
		cout << "Please enter the date you wish to search on: ";

	cin >> searchCriteria;

	return searchCriteria;
}
template double UserInterface::readInSearchCriteria<double>( void ) const;
template string UserInterface::readInSearchCriteria<string>( void ) const;
template Date UserInterface::readInSearchCriteria<Date>( void ) const;



double UserInterface::readInAmount( void ) const
{
	double amount;
	//print request
	cout << endl << "Enter amount to search: ";
	//get the answer
	cin >> amount;

	return amount;
}

const double UserInterface::readInTransferAmount( void ) const
{
	//print request
	cout << endl << "ENTER AMOUNT TO TRANSFER: \x9C";
	return readInPositiveAmount();
}

string UserInterface::readInTitle( void ) const
{
	string title;
	//ask for a title
	cout << endl << "Enter a title to search: ";
	cin >> title;
	//return the title
	return title;
}

Date UserInterface::readInValidDate( const Date creationDate ) const
{
	Date chosenDate;
	char strCreationDate[ 16 ];

	memset( strCreationDate, 0, sizeof(strCreationDate) );
	strcpy( strCreationDate, creationDate.toFormattedString().c_str() );

	do
	{
		printf( "Enter a date later or equal to %s (DD/MM/YYYY): ", strCreationDate );
		//read in the date
		cin >> chosenDate;
		//check to see if the date is after the creation date
		if( !chosenDate.isValid( creationDate ) )
			cout << "You entered an invalid date..." << endl << endl;
		else
			return chosenDate;

	}while( true );

}
//output no transactions found
void UserInterface::noTransactionsFound( void ) const
{
	cout << endl << "NO TRANSACTION IN BANK ACCOUNT MATCH THE SEARCH CRITERION GIVEN";
}

/*void UserInterface::showMatchingTransactionsOnScreenAmount( const double amount, const int noTrans, const string strTrans ) const
{
	cout << endl << noTrans << " transactions for \234" << amount << endl << strTrans;
}

void UserInterface::showMatchingTransactionsOnScreenTitle( const string title, const int noTrans, const string strTrans ) const
{
	cout << endl << noTrans << " transactions for " << title << endl << strTrans;
}

void UserInterface::showMatchingTransactionsOnScreenDate( const Date date, const int noTrans, const string strTrans ) const
{
	cout << endl << noTrans << " transactions for " << date << endl << strTrans;
}*/

//template to output the transactions that meat the seach criteria
template <typename T>
void UserInterface::showMatchingTransactionsOnScreen( const T criteria, const int noTrans, const string strTrans ) const //for option 7
{
	cout << endl << noTrans << " transactions for " << criteria << endl << strTrans;
}

template void UserInterface::showMatchingTransactionsOnScreen<double>(	const double, const int, const string ) const;
template void UserInterface::showMatchingTransactionsOnScreen<Date>( const Date, const int, const string ) const;
template void UserInterface::showMatchingTransactionsOnScreen<string>(	const string, const int, const string ) const;

//print the transactions upto chosen date
void UserInterface::showTransactionsUpToDateOnScreen( const Date date, const int numTransactions, const string transactions ) const
{
	printf( "There are %d transactions up to %s.\n\n%s",
		numTransactions, date.toFormattedString().c_str(), transactions.c_str() );
}

void UserInterface::showValidateCardOnScreen( const int validCode, const string &cashCardNum ) const
{
	if( validCode == VALID_CARD ) //card valid: it exists, is accessible with that card (and not already open)
		printf( "\nTHE CARD (NUMBER: %s) EXISTS!\n", cashCardNum.c_str() );
	else if( validCode == UNKNOWN_CARD ) //card does not exist
		printf( "\nERROR: INVALID CARD\n\nTHE CARD (NUMBER: %s) DOES NOT EXIST!\n", cashCardNum.c_str() );
	else if( validCode == EMPTY_CARD ) //account exists but is not accessible with that card
		printf( "\nERROR: EMPTY CARD\nTHE CARD (NUMBER: %s) DOES NOT LINK TO ANY ACCOUNT!\n", cashCardNum.c_str() );
}

void UserInterface::showCardOnScreen( const string& aCardDetails ) const
{
    cout << "\n========================================="
		 << "\n________ CARD DETAILS ___________________"
		 << aCardDetails
		 << "\n________ END CARD DETAILS _______________"
		 << "\n=========================================";
}

const string UserInterface::readInAccountToBeProcessed( string &anAccountNumber, string &aSortCode ) const
{
    cout << "\n SELECT THE ACCOUNT ...\n";

	cout << "   ACCOUNT NUMBER:  ";	//ask for account number
    cin >> anAccountNumber;

	cout << "   SORT CODE:       ";	//ask for sort code
    cin >> aSortCode;

    cout << "\n=========================================";

    //create account file name
    return ( FILEPATH + "account_" + anAccountNumber + "_" + aSortCode + ".txt" );
}

void UserInterface::showValidateAccountOnScreen( const int validCode, const string &accNum, const string &srtCode ) const
{
    if( validCode == VALID_ACCOUNT ) //account valid: it exists, is accessible with that card (and not already open: TO BE IMPLEMENTED)
        	printf( "\nTHE ACCOUNT (NUMBER: %s CODE: %s) IS NOW OPEN!\n", accNum.c_str(), srtCode.c_str() );
	else if( validCode == UNKNOWN_ACCOUNT )	//account does not exist
        	printf( "\nERROR: INVALID ACCOUNT"
			"\nTHE ACCOUNT (NUMBER: %s CODE: %s) DOES NOT EXIST!", accNum.c_str(), srtCode.c_str() );
	else if( validCode == INACCESSIBLE_ACCOUNT ) //account exists but is not accessible with that card
        	printf( "\nERROR: INVALID ACCOUNT"
				"\nTHE ACCOUNT (NUMBER: %s CODE: %s) IS NOT ACCESSIBLE WITH THIS CARD!", accNum.c_str(), srtCode.c_str() );
	else if( validCode == SAME_ACCOUNT )
			printf( "\nTHE ACCOUNT (NUMBER: %s CODE: %s) IS ALREADY OPEN!\n",
			accNum.c_str(), srtCode.c_str() );
}

void UserInterface::displayAssociatedAccounts( list<string> accList, const BankAccount *pActiveAcc ) const
{
	if( !pActiveAcc || accList.empty() )
		return;

	string activeAccNo = pActiveAcc->getAccountNumber();
	string activeSrtCode = pActiveAcc->getSortCode();

	do
	{
		string temp = accList.front();

		if( temp.substr( 0, 3 ).c_str() != activeAccNo ||
			temp.substr( 4, 5 ).c_str() != activeSrtCode )
		{
			printf( "\nACCOUNT NO: %s\tSORT CODE: %s",
				temp.substr( 0, 3 ).c_str(),
				temp.substr( 4, 5 ).c_str() );
		}

		accList.remove( temp );

	}while( !accList.empty() );
}

//input functions

double UserInterface::readInWithdrawalAmount( void ) const
{
    //ask for the amount to withdraw
    cout << endl << "AMOUNT TO WITHDRAW: \234";
	return readInPositiveAmount();
}
double UserInterface::readInDepositAmount( void ) const
{
    //ask for the amount to deposit
    cout << endl << "AMOUNT TO DEPOSIT: \234";
	return readInPositiveAmount();
}

int UserInterface::readInNumberOfTransactions( void ) const
{
	cout << endl << "AMOUNT OF TRANSACTIONS: ";
	return  static_cast<int>( readInPositiveAmount() );
}

//output functions

void UserInterface::showProduceBalanceOnScreen( const double balance ) const
{
	printf( "\nTHE CURRENT BALANCE IS: \234%12.2f", balance );
}

void UserInterface::showWithdrawalOnScreen( const bool trAuthorised, const double amountWithdrawn ) const
{
    if ( trAuthorised )
		printf( "\nTRANSACTION AUTHORISED!: \n\234%.2f WITHDRAWN FROM ACCOUNT\n", amountWithdrawn );
    else //not enough money
		printf( "\nTRANSACTION IMPOSSIBLE!\n" );
}

void UserInterface::showDepositOnScreen( const bool trAuthorised, const double amountDeposited ) const
{
    if ( trAuthorised )
    	printf( "\nTRANSACTION AUTHORISED!:\n\234%.2f DEPOSITED INTO ACCOUNT\n", amountDeposited );
    else //too much to deposit
		printf( "\nTRANSACTION IMPOSSIBLE!\n" );
}

void UserInterface::showStatementOnScreen( const string &statement ) const
{
    printf( "\nPREPARING STATEMENT..."
			"\n________ ACCOUNT STATEMENT _____%s"
			"\n________ END ACCOUNT STATEMENT _____\n", statement.c_str() );
}

void UserInterface::showAllDepositsOnScreen( const bool noTransaction, const string str, const double total ) const
{

	if ( !noTransaction )
	{
		cout << "ALL DEPOSIT TRANSACTIONS REQUESTED AT "
			 << Time::currentTime()
			 << " ON "
			 << Date::currentDate() << endl
			 << str
			 << "Total: \234" << total;
	} 
	else
		cout << "NO TRANSACTIONS IN BANK ACCOUNT";
}

void UserInterface::showMiniStatementOnScreen( const bool noTransaction, const string str, const double total ) const
{
	if ( !noTransaction )
	{
		cout << "RECENT TRANSACTIONS REQUESTED AT "
			 << Time::currentTime()
			 << " ON "
			 << Date::currentDate() << endl
			 << str
			 << "Total: \234" << total;
	}
	else
		cout << "NO TRANSACTIONS IN BANK ACCOUNT";
}


void UserInterface::showNoTransactionsOnScreen( void ) const
{
	cout << endl << endl << endl << "There are no transactions.";
}


//print the number of transactions deleted 
void UserInterface::showDeletionOfTransactionUpToDateOnScreen( const int numTransactions, const Date date ) const
{
	printf( "THE %d TRANSACTIONS UP TO DATE %s HAVE BEEN DELETED.\n",
		numTransactions, date.toFormattedString().c_str() );
}

//show if the transfer was a success
//if it wasn't print the appropriate reason
void UserInterface::showTransferOnScreen( const bool trOutOk, const bool trInOk, const double amount ) const
{
	if( trOutOk && trInOk )
		printf( "\n\nTransfer of \x9C%.2f was a success\n", amount );

	if( !trOutOk )
	{
		printf( "\n\nINSUFFICIENT FUNDS TO TRANSFER \x9C%.2f\n", amount );
		return;
	}

	if( !trInOk )
		printf( "\n\nACCOUNT CANNOT RECEIVE FUNDS \x9C%.2f\n", amount );
}

bool UserInterface::readInConfirmDeletion( void ) const
{
	char answer = ' ';
	//check user wants to delete
	cout << endl << "Are you sure you wish to delete these transactions (Y/N)? ";
	//read in answer
	cin >> answer;

	if( answer == 'Y' || answer == 'y' )
		return true;

	return false;
}


//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void UserInterface::showWelcomeScreen( void ) const
{
	cout << endl << endl << endl
		 << "             _____WELCOME TO THE ATM_____";
}

void UserInterface::showByeScreen( void ) const
{
    cout << endl << endl << endl
		 << "________________NEXT CUSTOMER..."
		 << endl << endl;
}

int UserInterface::readInCommand( void ) const
{
	int com( 0 );

	cout << endl << "          ENTER YOUR COMMAND: ";
	cin >> com;

	return com;
}

void UserInterface::showErrorInvalidCommand( void ) const
{
	cout << endl << "INVALID COMMAND CHOICE, TRY AGAIN";
}

double UserInterface::readInPositiveAmount( void ) const
{
    double amount( 0.0 );

	do
    {
		cin >> amount;

		if( amount <= 0.0 )
			cout << endl << "AMOUNT SHOULD BE A POSITIVE AMOUNT, TRY AGAIN: ";
		else
			return amount;
		
	}while( true );
}