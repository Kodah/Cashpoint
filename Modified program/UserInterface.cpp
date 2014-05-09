//Pascale Vacher - March 14
//OOP Assignment Semester 2

#include "UserInterface.h" 

//---------------------------------------------------------------------------
//UserInterface: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

//____other public member functions

//menu functions

void UserInterface::wait() const {
	char ch;
	cout << "\n\nPress RETURN to go back to menu\n";
	cin.get( ch);
	cin.get( ch);
//	flushall();
}
int UserInterface::readInCardIdentificationCommand() const {
    showCardIdentificationMenu();
    return ( readInCommand());
}
void UserInterface::showCardIdentificationMenu() const {
	cout << "\n\n\n      ________________________________________";
	cout << "\n      _______CARD IDENTIFICATION MENU________";
	cout << "\n      ________________________________________";
	cout << "\n       0           Quit CashPoint application";
	cout << "\n       1              Enter your card details";
	cout << "\n      ________________________________________";
}
int UserInterface::readInAccountProcessingCommand() const{
    showAccountProcessingMenu();
    return ( readInCommand());
}
void UserInterface::showAccountProcessingMenu() const {
	cout << "\n\n\n      ________________________________________";
	cout << "\n      ________ACCOUNT PROCESSING MENU________";
	cout << "\n      ________________________________________";
	cout << "\n       0 End account processing & remove card";
	cout << "\n       1                      Display balance";
	cout << "\n       2                Withdraw from account";
	cout << "\n       3                 Deposit into account";
	cout << "\n       4                       Show statement";
	cout << "\n       5                    Show all deposits  //Implemented";
	cout << "\n       6                  Show mini statement  //Implemented";
	cout << "\n       7           Show transations by search  //TO BE IMPLEMENTED FOR ASS 2";
	cout << "\n       8    Clear all transactions up to date  //TO BE IMPLEMENTED FOR ASS 2";
	cout << "\n       9          Transfer to another account  //Implemented";
	cout << "\n         ________________________________________";
}

int UserInterface::readInTransactionSearchCommand() const {
	showTransactionSearchMenu();
	return ( readInCommand());
}
void UserInterface::showTransactionSearchMenu() const {
	cout << "\n\n\n ________________________________________";
	cout << "\n		________TRANSACTION SEARCH MENU________";
	cout << "\n		________________________________________";
	cout << "\n		1 Search by amount";
	cout << "\n		2 Search by title";
	cout << "\n		3 Search by date";
	cout << "\n		4 Exit without search";
	cout << "\n		________________________________________";
}

const string UserInterface::readInCardToBeProcessed( string& aCardNumber) const {
	cout << "\n SELECT THE CARD ...\n";
	cout << "   CARD NUMBER:  ";         //ask for card number
    cin >> aCardNumber;
    cout << "\n=========================================";
    //create card file name
    return( FILEPATH + "card_" + aCardNumber + ".txt");
}

//Template function for option 7
template <typename T>
T UserInterface::UreadInSearchCriterion( void ) const
{
	T searchCriteria;

	cout << "\nPlease enter search criteria: ";
	cin >> searchCriteria;

	return searchCriteria;
}

double UserInterface::readInAmount() const //for option 7
{
	double amount;
	cout << "\nEnter amount to search: ";
	cin >> amount;
	return(amount);
}

string UserInterface::readInTitle() const //for option 7
{
	string title;
	cout << "\nEnter a title to search: ";
	cin >> title;

	return(title);
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
		cin >> chosenDate;

		if( !chosenDate.isValid( creationDate ) )
			cout << "You entered an invalid date..." << endl << endl;
		else
			return chosenDate;

	}while( true );

}

void UserInterface::noTransactionsFound() const //for option 7
{
	cout << "\nNO TRANSACTION IN BANK ACCOUNT MATCH THE SEARCH CRITERION GIVEN";
}

void UserInterface::showMatchingTransactionsOnScreenAmount(double amount, int noTrans, string strTrans) const //for option 7
{
	cout << "\n" << noTrans << " transactions for \234" << amount << "\n";
	cout << strTrans;
}

void UserInterface::showMatchingTransactionsOnScreenTitle(string title, int noTrans, string strTrans) const //for option 7
{
	cout << "\n" << noTrans << " transactions for " << title << "\n";
	cout << strTrans;
}

void UserInterface::showMatchingTransactionsOnScreenDate(Date date, int noTrans, string strTrans) const //for option 7
{
	cout << "\n" << noTrans << " transactions for " << date << "\n";
	cout << strTrans;
}

void UserInterface::showTransactionsUpToDateOnScreen( const Date date, const int numTransactions, string transactions ) const
{
	printf( "There are %d transactions up to %s.\n\n%s",
		numTransactions, date.toFormattedString().c_str(), transactions.c_str() );
}

void UserInterface::showValidateCardOnScreen( int validCode, const string& cashCardNum) const {
    switch( validCode)
    {
    	case VALID_CARD:		//card valid: it exists, is accessible with that card (and not already open: TO BE IMPLEMENTED)
			cout << "\nTHE CARD (NUMBER: " << cashCardNum << ") EXIST!";
            break;
    	case UNKNOWN_CARD:		//card does not exist
			cout << "\nERROR: INVALID CARD\n"
                 << "\nTHE CARD (NUMBER: " << cashCardNum << ") DOES NOT EXIST!";
            break;
    	case EMPTY_CARD:		//account exists but is not accessible with that card
        	cout << "\nERROR: EMPTY CARD"
                  << "\nTHE CARD (NUMBER: " << cashCardNum << ") DOES NOT LINK TO ANY ACCOUNT!";
             break;
    }
}

void UserInterface::showCardOnScreen( const string& aCardDetails) const {
    cout << "\n=========================================";
    cout << "\n________ CARD DETAILS ___________________";
	cout << aCardDetails;
    cout << "\n________ END CARD DETAILS _______________";
    cout << "\n=========================================";
}

const string UserInterface::readInAccountToBeProcessed( string& anAccountNumber, string& aSortCode) const {
    cout << "\n SELECT THE ACCOUNT ...\n";
	cout << "   ACCOUNT NUMBER:  ";	//ask for account number
    cin >> anAccountNumber;
	cout << "   SORT CODE:       ";	//ask for sort code
    cin >> aSortCode;
    cout << "\n=========================================";
    //create account file name
    return( FILEPATH + "account_" + anAccountNumber + "_" + aSortCode + ".txt");
}

void UserInterface::showValidateAccountOnScreen( int validCode, const string& accNum, const string& srtCode) const {
    switch( validCode)
    {
    	case VALID_ACCOUNT:		//account valid: it exists, is accessible with that card (and not already open: TO BE IMPLEMENTED)
        	cout << "\nTHE ACCOUNT (NUMBER: " << accNum
             	 << " CODE: " << srtCode << ") IS NOW OPEN!";
            break;
    	case UNKNOWN_ACCOUNT:		//account does not exist
        	cout << "\nERROR: INVALID ACCOUNT"
                 << "\nTHE ACCOUNT (NUMBER: " << accNum
                 << " CODE: " << srtCode << ") DOES NOT EXIST!";
            break;
    	case INACCESSIBLE_ACCOUNT:		//account exists but is not accessible with that card
        	cout << "\nERROR: INVALID ACCOUNT"
             	 << "\nTHE ACCOUNT (NUMBER: " << accNum
             	 << " CODE: " << srtCode << ") IS NOT ACCESSIBLE WITH THIS CARD!";
            break;
    }
}

//input functions

double UserInterface::readInWithdrawalAmount() const {
    //ask for the amount to withdraw
    cout << "\nAMOUNT TO WITHDRAW: \234" ;
	return ( readInPositiveAmount());
}
double UserInterface::readInDepositAmount() const {
    //ask for the amount to deposit
    cout << "\nAMOUNT TO DEPOSIT: \234" ;
	return ( readInPositiveAmount());
}

int UserInterface::readInNumberOfTransactions() const {
	cout << "\nAMOUNT OF TRANSACTIONS: ";
	return ( static_cast<int>(readInPositiveAmount()));
}

//output functions

void UserInterface::showProduceBalanceOnScreen( double balance) const {
	cout << fixed << setprecision(2) << setfill(' ');
    cout << "\nTHE CURRENT BALANCE IS: \234" << setw(12) << balance;//display balance
}
void UserInterface::showWithdrawalOnScreen( bool trAuthorised, double amountWithdrawn) const {
    if ( trAuthorised)
    	cout << "\nTRANSACTION AUTHORISED!: \n\234"
             << setw(0) << amountWithdrawn
             << " WITHDRAWN FROM ACCOUNT";
    else //not enough money
		cout << "\nTRANSACTION IMPOSSIBLE!";
}
void UserInterface::showDepositOnScreen( bool trAuthorised, double amountDeposited) const {
    if ( trAuthorised)
    	cout << "\nTRANSACTION AUTHORISED!:\n\234"
             << setw(0) << amountDeposited
             << " DEPOSITED INTO ACCOUNT";
    else //too much to deposit
		cout << "\nTRANSACTION IMPOSSIBLE!";
}
void UserInterface::showStatementOnScreen( const string& statement) const {
    cout << "\nPREPARING STATEMENT...";
    cout << "\n________ ACCOUNT STATEMENT _____";
	cout << statement;
    cout << "\n________ END ACCOUNT STATEMENT _____";
}

void UserInterface::showAllDepositsOnScreen(bool noTransaction, string str, double total) const {

	if (!noTransaction)
	{
		cout << "ALL DEPOSIT TRANSACTIONS REQUESTED AT ";
		cout << Time::currentTime();
		cout << " ON ";
		cout << Date::currentDate() << "\n";
		cout << str;
		cout << "Total: \234" <<total;
	} 
	else
	{
		cout << "NO TRANSACTIONS IN BANK ACCOUNT";
	}
}

void UserInterface::showMiniStatementOnScreen(bool noTransaction, string str, double total) const {

	if (!noTransaction)
	{
		cout << "RECENT TRANSACTIONS REQUESTED AT ";
		cout << Time::currentTime();
		cout << " ON ";
		cout << Date::currentDate() << "\n";
		cout << str;
		cout << "Total: \234" <<total;
	}
	
	else
	{
		cout << "NO TRANSACTIONS IN BANK ACCOUNT";
	}
}


void UserInterface::showNoTransactionsOnScreen() const{
	cout << "\n\n\n There are no transactions.";
}

void UserInterface::showDeletionOfTransactionUpToDateOnScreen( const int numTransactions, const Date date ) const
{
	printf( "THE %d TRANSACTIONS UP TO DATE %s HAVE BEEN DELETED.\n",
		numTransactions, date.toFormattedString().c_str() );
}

bool UserInterface::readInConfirmDeletion( void ) const
{
	char answer = ' ';

	cout << endl << "Are you sure you wish to delete these transactions (Y/N)? ";
	cin >> answer;

	if( answer == 'Y' || answer == 'y' )
		return true;

	return false;
}


//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void UserInterface::showWelcomeScreen() const {
	cout << "\n\n\n             _____WELCOME TO THE ATM_____";
}
void UserInterface::showByeScreen() const {
    cout << "\n\n\n________________NEXT CUSTOMER...\n\n";
}
int UserInterface::readInCommand() const{
	int com;
	cout << "\n          ENTER YOUR COMMAND: ";
	cin >> com;
	return com;
}
void UserInterface::showErrorInvalidCommand() const {
	cout << "\nINVALID COMMAND CHOICE, TRY AGAIN";
}
double UserInterface::readInPositiveAmount() const {
    double amount;
	cin >> amount;
	while ( amount <= 0.0)
    {
	    cout << "\nAMOUNT SHOULD BE A POSITIVE AMOUNT, TRY AGAIN: ";
		cin >> amount;
	}
    return amount;
}