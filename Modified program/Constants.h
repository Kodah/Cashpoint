//Pascale Vacher - March 14
//OOP Assignment Semester 2

#ifndef ConstantsH
#define ConstantsH

#include <string>
using namespace std;

//menu command
const int QUIT_COMMAND( 0);

//account type
enum AccountType
{
	BANK,
	CURRENT,
	SAVINGS,
	CHILDSAVINGS,
	ISASAVINGS
};

//card state
enum CardState
{
	VALID_CARD,
	UNKNOWN_CARD,
	EMPTY_CARD
};

//account state
enum AccountState
{
	VALID_ACCOUNT,
	UNKNOWN_ACCOUNT,
	INACCESSIBLE_ACCOUNT
};

//month
enum Month
{
	JAN = 1,
	FEB,
	MAR,
	APR,
	MAY,
	JUN,
	JUL,
	AUG,
	SEPT,
	OCT,
	NOV,
	DEC
};

//ressource path
const string FILEPATH( "data\\");

#endif