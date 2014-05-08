//Pascale Vacher - March 14
//OOP Assignment Semester 2

#include "BankAccount.h"

//---------------------------------------------------------------------------
//BankAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

BankAccount::BankAccount()
    : accountNumber_( "null"),
      sortCode_( "null"),
	  balance_( 0.0)
{}
BankAccount::BankAccount( const string& typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList)
    : accountType_(typ),
	  accountNumber_( acctNum), sortCode_( sCode),
      creationDate_( cD),
      balance_( b),
      transactions_( trList)
{}
BankAccount::~BankAccount()
{}


//____other public member functions

const string BankAccount::getAccountType() const {
    return accountType_;
}

const char * BankAccount::getTypeFromFile( const string accNo, const string srtCode )
{
	const char *fileName = (FILEPATH + "account_" + accNo + "_" + srtCode + ".txt").c_str();

	FILE *file = nullptr;
	char buffer[ 60 ];

	fopen_s( &file, fileName, "r" );
	fgets( buffer, sizeof( buffer ), file );
	fclose( file );

	return buffer;
}

const string BankAccount::getAccountNumber() const {
    return accountNumber_;
}
const string BankAccount::getSortCode() const {
    return sortCode_;
}
const Date BankAccount::getCreationDate() const {
    return creationDate_;
}
double BankAccount::getBalance() const {
    return balance_;
}
const TransactionList BankAccount::getTransactions() const {
    return transactions_;
}
bool BankAccount::isEmptyTransactionList() const {
	return transactions_.size() == 0;
}

void BankAccount::recordDeposit( double amountToDeposit) {
    //create a deposit transaction
	Transaction aTransaction( "deposit_to_ATM", amountToDeposit);
    //update active bankaccount
    transactions_.addNewTransaction( aTransaction);		//update transactions_
    updateBalance( amountToDeposit);			//increase balance_
}

void BankAccount::recordTransfer( const double amount, const string transaction )
{
	transactions_.addNewTransaction( Transaction( transaction, amount ) );   
}

double BankAccount::borrowable() const {
//return borrowable amount
    return balance_;
}
bool BankAccount::canWithdraw( double amountToWithdraw ) const {
//check if enough money in account
    return ( amountToWithdraw <= borrowable());
}

void BankAccount::recordWithdrawal( double amountToWithdraw) {
	//create a withdrawal transaction
    Transaction aTransaction( "withdrawal_from_ATM", -amountToWithdraw);
    //update active bankaccount
    transactions_.addNewTransaction( aTransaction);		//update transactions_
    updateBalance( -amountToWithdraw);			//decrease balance_
}

void BankAccount::transferMoney( const double amount, BankAccount *toAccount )
{
	char answer = ' '; //For use with checking if the user wishes to continue
	double balance = getBalance(); //Store the current balance of the account

	string toAccNo = toAccount->getAccountNumber();
	string toSrtCode = toAccount->getSortCode();

	if( *this != *toAccount ) //Check that the two accounts are not the same
	{
		printf( "ACCOUNT BALANCE: \x9C%.2f\n", balance ); //Let the customer know their balance.

		if( (balance - amount) >= 0 ) //If the transfer does not leave us in negative digits
		{
			printf( "The transfer can be granted.\n" );
			printf( "Are you sure you wish to transfer %.2f to %s %s (Y/N): ",
				amount, toAccNo.c_str(), toSrtCode.c_str() );
			
			cin >> answer;

			if( answer == 'Y' || answer == 'y' ) //Check if the user still wishes to proceed
			{
				updateBalance( -amount ); //Change each account's balance
				toAccount->updateBalance( amount );
				
				recordTransfer( -amount, "Transfer_to_" + toAccNo + "_" + toSrtCode ); //Record the transfer
				toAccount->recordTransfer( amount, "Transfer_from_" + accountNumber_ + "_" + sortCode_ );
				
				//storeBankAccountInFile( FILEPATH + "account_" + accountNumber_ + "_" + sortCode_ + ".txt" ); //Save the accounts' current state
				//toAccount->storeBankAccountInFile( FILEPATH + "account_" + toAccNo + "_" + toSrtCode + ".txt" );
				
				cout << "Transfer success" << endl;
			}
			else
				cout << "The transfer did not take place" << endl;
		}
		else
			printf( "INSUFFICIENT FUNDS TO TRANSFER \x9C%.2f\n", amount );
	}
}

const string BankAccount::prepareFormattedStatement() const {
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	//list of transactions (or message if empty)
	if ( transactions_.size() > 0)
		os << "\n\nLIST OF TRANSACTIONS \n"	<< transactions_.toFormattedString();	//one per line
	else
		os << "\n\nNO TRANSACTIONS IN BANK ACCOUNT!";
	return ( os.str());
}

void BankAccount::readInBankAccountFromFile( const string& fileName) {
	ifstream fromFile;
	fromFile.open( fileName.c_str(), ios::in); 	//open file in read mode
	if ( fromFile.fail())
		cout << "\nAN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        fromFile >> (*this);  	//read  all info from bank account file
    fromFile.close();			//close file: optional here
}

void BankAccount::storeBankAccountInFile( const string& fileName) const {
	ofstream toFile;
	toFile.open( fileName.c_str(), ios::out);	//open copy file in write mode
	if ( toFile.fail())
		cout << "\nAN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        toFile << (*this);	//store all info to bank account file
	toFile.close();			//close file: optional here
}

ostream& BankAccount::putDataInStream( ostream& os) const {
//put (unformatted) BankAccount details in stream
    os << accountType_ << "\n";				//put account type
    os << accountNumber_ << "\n";			//put account number
	os << sortCode_ << "\n";				//put sort code
    os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	if (  ! transactions_.size() == 0)
		os << transactions_;				//put all transactions, one per line
	return os;
}
istream& BankAccount::getDataFromStream( istream& is) {
//get BankAccount details from stream
    is >> accountType_;						//get account type
    is >> accountNumber_;					//get account number
	is >> sortCode_;						//get sort code
 	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance_
	is >> transactions_;					//get all transactions (if any)
	return is;
}

void BankAccount::produceAllDepositTransactions(string& str, double& total) const{
	TransactionList trl (transactions_.getAllDepositTransactions());

	total = trl.getTotalTransactions();
	str = trl.toFormattedString();
}

void BankAccount::produceNMostRecentTransactions(int noOfTran, string& str, double& total) const{
	TransactionList trl (transactions_.getMostRecentTransactions(noOfTran));

	total = trl.getTotalTransactions();
	str = trl.toFormattedString();
}

string BankAccount::produceTransactionsUpToDate( const Date date, int &numTransactions ) const
{
	TransactionList trList = transactions_.getTransactionsUpToDate( date );
	numTransactions = trList.size();
	return trList.toFormattedString();
}

void BankAccount::produceTransactionsForAmount(double amount, string& strTrans, int& noTrans)//for option 7
{
	TransactionList trl (transactions_.getTransactionsForAmount(amount));
	noTrans = trl.getNumberOfTransactions();
	strTrans = trl.toFormattedString();
}

void BankAccount::produceTransactionsForTitle(string title, string& strTrans, int& noTrans)//for option 7
{
	TransactionList trl (transactions_.getTransactionsForTitle(title));
	noTrans = trl.getNumberOfTransactions();
	strTrans = trl.toFormattedString();
}

void BankAccount::produceTransactionsForDate(Date date, string& strTrans, int& noTrans)//for option 7
{
	TransactionList trl (transactions_.getTransactionsForDate(date));
	noTrans = trl.getNumberOfTransactions();
	strTrans = trl.toFormattedString();
}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void BankAccount::updateBalance( double amount) {
    balance_ += amount;   //add/take amount to/from balance_
}

void BankAccount::deleteTransactionsUpToDate( const Date date )
{
	TransactionList trList = transactions_.getTransactionsUpToDate( date );
	Transaction *tempTransaction = nullptr;

	while( tempTransaction = (Transaction *)&trList.newestTransaction() )
	{
		transactions_.deleteGivenTransaction( *tempTransaction );
		trList.deleteGivenTransaction( *tempTransaction );
	}
}

void BankAccount::recordDeletionOfTransactionUpToDate( const Date date )
{
	deleteTransactionsUpToDate( date );


}

const string BankAccount::prepareFormattedAccountDetails() const {
	//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << accountType_ << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << accountNumber_;									//display account number
	os << "\nSORT CODE:       " << sortCode_;										//display sort code
	os << "\nCREATION DATE:   " << creationDate_.toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << balance_;	//display balance
	return ( os.str());
}

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream& os, const BankAccount& aBankAccount) {
//put (unformatted) BankAccount details in stream
    return ( aBankAccount.putDataInStream( os));
}

istream& operator>>( istream& is, BankAccount& aBankAccount) {
//get BankAccount details from stream
	return ( aBankAccount.getDataFromStream( is));
}

bool operator ==( BankAccount bA1, BankAccount bA2 )
{
	if( bA1.getAccountNumber() != bA2.getAccountNumber() )
		return false; //Account numbers are different; dealing with different accounts

	if( bA1.getSortCode() != bA2.getSortCode() )
		return false; //Sort codes are different; dealing with different accounts

	return true; //Accounts are the same
}

bool operator !=( BankAccount bA1, BankAccount bA2 )
{
	if( bA1.getAccountNumber() != bA2.getAccountNumber() )
		return true; //Account numbers are different; dealing with different accounts

	if( bA1.getSortCode() != bA2.getSortCode() )
		return true; //Sort codes are different; dealing with different accounts

	return false; //Accounts are the same
}