//Mike Orr, Luke Segaran, Tom sugarev - May 14
//OOP Assignment Semester 2

#ifndef TimeH
#define TimeH

//---------------------------------------------------------------------------
//Time: class declaration
//---------------------------------------------------------------------------

//microsoft library includes
#include <iomanip>
#include <sstream>

//removed using namespace std to prevent namespace pollution
using std::string;
using std::ostringstream;
using std::ostream;
using std::istream;
using std::setfill;
using std::setw;

class Time //Time class
{
public:
	Time();						//default constructor
	Time( const Time& );   		//copy constructor
	Time( int h, int m, int s ); //basic constructor
	Time( long);				//conversion constructor
	~Time();					//destructor

	static const Time							currentTime( void ); //return system time

	int											getHours( void ) const;
	int											getMinutes( void ) const;
	int											getSeconds( void ) const;

	void										setTime( int h, int m, int s );
	void										setTime( long secs );
	void										increment( long secs );	//add secs to *this

	const string								toFormattedString( void ) const; //return time as formatted string ("HH:MM:SS")
	ostream&									putDataInStream( ostream& os) const; //send Time info into an output stream
	istream&									getDataFromStream( istream& is); //receive Time info from an input stream

	bool										operator==( const Time& t ) const;  //true if (*this == t)
	bool										operator!=( const Time& t ) const;  //true if (*this != t)
	bool										operator <( const Time& t ) const;	//true if (*this < t)
	const										Time operator +( const Time& t ) const;

private: //private member instances
   long											inSeconds_;
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const Time& );	//output operator
istream& operator>>( istream&, Time& );			//input operator

#endif