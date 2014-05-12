//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#include "CashCard.h"

//---------------------------------------------------------------------------
//CashCard: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

CashCard::CashCard()
    : cardNumber_( "null")
{}
CashCard::CashCard( const string& cardNum, const list<string> &accList )
    : cardNumber_( cardNum ), accountsList_( accList )
{}

//____other public member functions

const string CashCard::getCardNumber( void ) const
{
    return cardNumber_; // return the card identifier
}

const list<string> CashCard::getAccountsList( void ) const
{
    return accountsList_; // list of accounts associated with card
}

const string CashCard::getAssociatedAccounts( BankAccount *acc ) const
{
	ostringstream os;
	list<string> accList = getAccountsList();

	if( !acc || accList.empty() )
		return ""; //check account is active and there are accounts

	string activeAccNo = acc->getAccountNumber(); //get account details
	string activeSrtCode = acc->getSortCode();

	do
	{
		string temp = accList.front(); //get first from list

		if( temp.substr( 0, 3 ).c_str() != activeAccNo ||
			temp.substr( 4, 5 ).c_str() != activeSrtCode )
		{ //if account is not active
			os << endl << "ACCOUNT NO: " << temp.substr( 0, 3 )
			   << "\t" << "SORT CODE: "  << temp.substr( 4, 5 );
		}

		accList.remove( temp ); //remove from temp list

	}while( !accList.empty() ); //until list is empty

	return os.str();
}

bool CashCard::onCard( const string& accFileName ) const // see if account is associated with card
{
    //e.g., data\account_001_00-44.txt
	string accName = accFileName.substr( 13, 9);	//account identifier

	list<string>::const_iterator findIt = find( accountsList_.begin(), accountsList_.end(), accName );

	if( findIt == accountsList_.end() )
		return false;

	return true;
	//return ( accountsList_.member( accName)); //check if member of the card account list
}

void CashCard::readInCardFromFile( const string& accFileName )
{
	ifstream fromFile;
	fromFile.open( accFileName.c_str(), ios::in); 	//open file in read mode
	if ( fromFile.fail())
		cout << endl << "AN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        fromFile >> (*this);   //read all info from card file
//  fromFile.close();			//close file: optional here
}

const string CashCard::toFormattedString( void ) const
{
//return cash card as a (formatted) string
	ostringstream os_card;

	os_card << endl << "CARD NUMBER:    " << cardNumber_ << endl;	//display card no
	os_card << endl << "LIST OF ACCOUNTS ";						//display transactions

	if ( accountsList_.empty() )
		os_card << "IS EMPTY!!!";
	else
	{
	   	list<string> tempAccList( accountsList_ ); //make a copy of the list of accounts on card

		while ( ! ( tempAccList.empty()))
   		{
      		os_card << endl;

			string s = tempAccList.front();     //account details (e.g., "001_00-44")
			string s_accNum = s.substr( 0, 3);	//account number (e.g., "001")
			string s_srtCod = s.substr( 4, 5);	//sort code (e.g., "00-44")

			os_card << "  ACCOUNT NUMBER: " << s_accNum;
			os_card << "  SORT CODE: " << s_srtCod;

       		tempAccList.remove( s );
		}
    }

	return os_card.str();
}

ostream& CashCard::putDataInStream( ostream& os ) const
{
//put (formatted) CashCard details in stream
    os << cardNumber_ << endl;	//store card number
    list<string> tempAccounts( accountsList_ );

    while ( !tempAccounts.empty() ) 	//while not empty
	{
		string ele = tempAccounts.front();
		os << ele << endl; 	//copy each account name & <Return> in file
	    tempAccounts.remove( ele );	//delete account reference from history of transactions
	}

	return os;
}
istream& CashCard::getDataFromStream( istream& is )
{
//get CashCard details from stream
	is >> cardNumber_;	//read card number
	string anAccountName;
	is >> anAccountName;	//read first account name

    while ( is != 0) 	//while not end of file
    {
		accountsList_.insert( accountsList_.end(), anAccountName );//add account
		is >> anAccountName;	//read next account name
	}

	return is;
}
//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream& os, const CashCard& aCashCard )
{
						//Card formatted output
    return ( aCashCard.putDataInStream( os ) );
}

istream& operator>>( istream& is, CashCard& aCashCard)
{
						//read in CashCard details
	return ( aCashCard.getDataFromStream( is ) );
}
