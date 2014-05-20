//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#include "BankAccount.h"

//---------------------------------------------------------------------------
//BankAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

BankAccount::BankAccount() : accountNumber_( "null"), sortCode_( "null" ),
	  balance_( 0.0 ), fileName_( "null" )
{
}

BankAccount::BankAccount( const string& typ, const string& acctNum, const string& sCode,
                          const Date& cD, const double b,
                          const TransactionList& trList )
    : accountType_( typ ), accountNumber_( acctNum ), sortCode_( sCode ), creationDate_( cD ),
      balance_( b ), transactions_( trList ), fileName_( (FILEPATH + "account_" +  acctNum + "_" + sCode + ".txt") )
{
}

BankAccount::~BankAccount()
{
}


//____other public member functions

const string BankAccount::getAccountType( void ) const
{
    return accountType_; //return account type as string
}

const string BankAccount::getAccountNumber( void ) const
{
    return accountNumber_; //return account number as string
}
const string BankAccount::getSortCode( void ) const
{
    return sortCode_; // return sort code as string
}
const Date BankAccount::getCreationDate( void ) const
{
    return creationDate_; // return date created as Date
}
double BankAccount::getBalance( void ) const
{
    return balance_; // returns the balance of the account
}
const TransactionList BankAccount::getTransactions( void ) const
{
    return transactions_; // returns the list of transactions
}

string BankAccount::getFileName( void ) const
{
	return fileName_; // returns the account file name
}

const bool BankAccount::isEmptyTransactionList( void ) const
{
	return transactions_.size() == 0; // checks if the transaction list is empty
}

const bool BankAccount::canTransferOut( const double amount ) const
{
	return ((amount >= 0.0) && ((balance_ - amount) >= 0.0)); // virtual standard method
}

const bool BankAccount::canTransferIn( const double amount ) const
{
	return true;// virtual standard method
}

void BankAccount::recordDeposit( const double amountToDeposit )
{
    //create a deposit transaction
	Transaction aTransaction( "deposit_to_ATM", amountToDeposit );
    //update active bankaccount
    transactions_.addNewTransaction( aTransaction );		//update transactions_
    updateBalance( amountToDeposit );			//increase balance_
}

//This creates the transaction string and sends it to the "newTransaction" function to write it 
//to the file.
void BankAccount::recordTransferIn( const double amount, const string aAN, const string aSC )
{
	const string transaction = ( "Transfer_from_" + aAN + "_" + aSC ); 
	transactions_.addNewTransaction( Transaction( transaction, amount ) ); 

	updateBalance( amount ); //Change account balance
}
//This creates the transaction string and sends it to the "newTransaction" function to write it 
//to the file.
void BankAccount::recordTransferOut( const double amount, const string tAN, const string tSC )
{
	const string transaction = ( "Transfer_to_" + tAN + "_" + tSC ); 
	transactions_.addNewTransaction( Transaction( transaction, -amount ) ); 

	updateBalance( -amount ); //Change account balance
}

void BankAccount::recordWithdrawal( const double amountToWithdraw )
{
    Transaction aTransaction( "withdrawal_from_ATM", -amountToWithdraw ); //create a withdrawal transaction
    transactions_.addNewTransaction( aTransaction ); //update transactions_
    updateBalance( -amountToWithdraw );	//decrease balance_
}

const string BankAccount::prepareFormattedStatement( void ) const
{
	ostringstream os;
	
	os << prepareFormattedAccountDetails();
	//list of transactions (or message if empty)
	if ( transactions_.size() )
		os << "\n\nLIST OF TRANSACTIONS \n"	<< transactions_.toFormattedString();	//one per line
	else
		os << "\n\nNO TRANSACTIONS IN BANK ACCOUNT!";

	return os.str();
}

void BankAccount::readInBankAccountFromFile( const string& fileName )
{
	ifstream fromFile;

	fromFile.open( fileName.c_str(), ios::in); 	//open file in read mode

	if ( fromFile.fail() )
		cout << endl << "AN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        fromFile >> *this;  	//read  all info from bank account file

    fromFile.close();			//close file: optional here
}

void BankAccount::storeBankAccountInFile( const string& fileName ) const
{
	ofstream toFile;

	toFile.open( fileName.c_str(), ios::out );	//open copy file in write mode

	if ( toFile.fail() )
		cout << endl << "AN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        toFile << *this;	//store all info to bank account file

	toFile.close();			//close file: optional here
}

//this function returns a formatted string of deposit transactions
//as well as the amount of transactions.
void BankAccount::produceAllDepositTransactions( string& str, double& total ) const
{
	TransactionList trl( transactions_.getAllDepositTransactions() );

	total	= trl.getTotalTransactions();
	str		= trl.toFormattedString();
}

//this function returns a formatted string of the last N transactions
//as well as the amount of transactions.
void BankAccount::produceNMostRecentTransactions( const int noOfTran, string& str, double& total ) const
{
	TransactionList trl( transactions_.getMostRecentTransactions( noOfTran ) );

	total	= trl.getTotalTransactions();
	str		= trl.toFormattedString();
}

//this function returns a formatted string of transactions upto a certain date
//as well as the amount of transactions.
string BankAccount::produceTransactionsUpToDate( const Date date, int &numTransactions ) const
{
	TransactionList trList = transactions_.getTransactionsUpToDate( date );
	numTransactions = trList.size();

	return trList.toFormattedString();
}

//Template function for option 7
//this returns a formatted string of transactions
//as well as the amount of transactions for certain criteria.
template <typename T>
string BankAccount::produceTransactionsForSearchCriteria( const T searchVal, int& noTrans ) const
{
	//calls another template function to get the transactions depending on the type sent

	TransactionList trl = transactions_.getTransactionsForSearchCriteria(searchVal);

	if( typeid(double) == typeid(T) )
	{ //if searching on amount, get negated searchVal as well as positive
		TransactionList trl2 = transactions_.getTransactionsForSearchCriteria(-searchVal);
		trl += trl2;
	}

	noTrans = trl.getNumberOfTransactions();
	return trl.toFormattedString();
}

//the three templates to accept types double, string or date.
template string BankAccount::produceTransactionsForSearchCriteria<double>( const double, int & ) const;
template string BankAccount::produceTransactionsForSearchCriteria<string>( const string, int & ) const;
template string BankAccount::produceTransactionsForSearchCriteria<Date>( const Date, int & ) const;

/*void BankAccount::produceTransactionsForAmount( const double amount, string& strTrans, int& noTrans )
{
	TransactionList trl( transactions_.getTransactionsForAmount( amount ) );

	noTrans		= trl.getNumberOfTransactions();
	strTrans	= trl.toFormattedString();
}

void BankAccount::produceTransactionsForTitle( const string title, string& strTrans, int& noTrans ) const
{
	TransactionList trl( transactions_.getTransactionsForTitle( title ) );

	noTrans		= trl.getNumberOfTransactions();
	strTrans	= trl.toFormattedString();
}

void BankAccount::produceTransactionsForDate( const Date date, string& strTrans, int& noTrans ) const
{
	TransactionList trl( transactions_.getTransactionsForDate( date ) );
	noTrans		= trl.getNumberOfTransactions();
	strTrans	= trl.toFormattedString();
}*/

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void BankAccount::updateBalance( double amount )
{
    balance_ += amount;   //add/take amount to/from balance_
}

void BankAccount::recordDeletionOfTransactionUpToDate( const Date date )
{
	transactions_.deleteTransactionsUpToDate( date );
}

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream& os, const BankAccount& aBankAccount )
{
	//put (unformatted) BankAccount details in stream
    return ( aBankAccount.putDataInStream( os ) );
}

istream& operator>>( istream& is, BankAccount& aBankAccount )
{
	//get BankAccount details from stream
	return ( aBankAccount.getDataFromStream( is));
}

bool operator ==( BankAccount &bA1, BankAccount &bA2 )
{
	if( bA1.getAccountNumber() != bA2.getAccountNumber() )
		return false; //Account numbers are different; dealing with different accounts

	if( bA1.getSortCode() != bA2.getSortCode() )
		return false; //Sort codes are different; dealing with different accounts

	return true; //Accounts are the same
}

bool operator !=( BankAccount &bA1, BankAccount &bA2 )
{
	if( bA1.getAccountNumber() != bA2.getAccountNumber() )
		return true; //Account numbers are different; dealing with different accounts

	if( bA1.getSortCode() != bA2.getSortCode() )
		return true; //Sort codes are different; dealing with different accounts

	return false; //Accounts are the same
}