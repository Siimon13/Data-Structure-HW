/*
  Simon Chen
  N10013388
  sc4900


*/

// Code from Weiss
// Symbol is the class that will be placed on the Stack.
// This is code from Weiss
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
#include <map>
#include <vector>


using namespace std;

class Tokenizer
{
public:
  Tokenizer( istream & input )
    : currentLine( 1 ), errors( 0 ), inputStream( input ) { }
    
  // The public routines
  char getNextOpenClose( );
  string getNextID( );
  int getLineNumber( ) const;
  int getErrorCount( ) const;
    
private:
  enum CommentType { SLASH_SLASH, SLASH_STAR };
    
  istream & inputStream;     // Reference to the input stream
  char ch;                   // Current character
  int currentLine;           // Current line
  int errors;                // Number of errors detected
    
  // A host of internal routines
  bool nextChar( );
  void putBackChar( );
  void skipComment( CommentType start );
  void skipQuote( char quoteType );
  string getRemainingString( );
};


// nextChar sets ch based on the next character in
// inputStream and adjusts currentLine if necessary.
// It returns the result of get.
// putBackChar puts the character back onto inputStream.
// Both routines adjust currentLine if necessary.
bool Tokenizer::nextChar( )
{
  if( !inputStream.get( ch ) )
    return false;
  if( ch == '\n' )
    currentLine++;
  return true;
}

void Tokenizer::putBackChar( )
{
  inputStream.putback( ch );
  if( ch == '\n' )
    currentLine--;
}

// Precondition: We are about to process a comment;
//                 have already seen comment start token.
// Postcondition: Stream will be set immediately after
//                 comment ending token.
void Tokenizer::skipComment( CommentType start )
{
  if( start == SLASH_SLASH )
    {
      while( nextChar( ) && ( ch != '\n' ) )
	;
      return;
    }
    
  // Look for */
  bool state = false;    // Seen first char in comment ender.
    
  while( nextChar( ) )
    {
      if( state && ch == '/' )
	return;
      state = ( ch == '*' );
    }
  cout << "Unterminated comment at line " << getLineNumber( ) << endl;
  errors++;
}

// Precondition: We are about to process a quote;
//                   have already seen beginning quote.
// Postcondition: Stream will be set immediately after
//                   matching quote.
void Tokenizer::skipQuote( char quoteType )
{
  while( nextChar( ) )
    {
      if( ch == quoteType )
	return;
      if( ch == '\n' )
        {
	  cout << "Missing closed quote at line " << ( getLineNumber( ) - 1 ) << endl;
	  errors++;
	  return;
        }
      // If a backslash, skip next character.
      else if( ch == '\\' )
	nextChar( );
    }
}

// Return the next opening or closing symbol or '\0' (if EOF).
// Skip past comments and character and string constants.
char Tokenizer::getNextOpenClose( )
{
  while( nextChar( ) )
    {
      if( ch == '/' )
        {
	  if( nextChar( ) )
            {
	      if( ch == '*' )
		skipComment( SLASH_STAR );
	      else if( ch == '/' )
		skipComment( SLASH_SLASH );
	      else if( ch != '\n' )
		putBackChar( );
            }
        }
      else if( ch == '\'' || ch == '"' )
	skipQuote( ch );
      else if( ch == '\\' )  // Extra case, not in text
	nextChar( );
      else if( ch == '(' || ch == '[' || ch == '{' ||
	       ch == ')' || ch == ']' || ch == '}' )
	return ch;
    }
  return '\0';       // End of file
}

// Return current line number.
int Tokenizer::getLineNumber( ) const
{
  return currentLine;
}

// Return current line number.
int Tokenizer::getErrorCount( ) const
{
  return errors;
}

// Return indicates if ch can be part of a C++ identifier.
bool isIdChar( char ch )
{
  return ch == '_' || isalnum( ch );
}

// Return an identifier read from input stream.
// First character is already read into ch.
string Tokenizer::getRemainingString( )
{
  string result;
    
  for( result = ch; nextChar( ); result += ch )
    if( !isIdChar( ch ) )
      {
	putBackChar( );
	break;
      }
    
  return result;
}

// Return next identifier, skipping comments
// string constants, and character constants.
// Return "" if end of stream is reached.
string Tokenizer::getNextID( )
{
  while( nextChar( ) )
    {
      if( ch == '/' )
        {
	  if( nextChar( ) )
            {
	      if( ch == '*' )
		skipComment( SLASH_STAR );
	      else if( ch == '/' )
		skipComment( SLASH_SLASH );
	      else
		putBackChar( );
            }
        }
      else if( ch == '\\' )
	nextChar( );
      else if( ch == '\'' || ch == '"' )
	skipQuote( ch );
      else if( !isdigit( ch ) && isIdChar( ch ) )
	return getRemainingString( );
    }
  return "";       // End of file
}

struct Symbol
{
  char token;
  int  theLine;
};

class Balance
{
public:
    Balance( istream & is ):tok( is ),errors( 0 ){}
    int checkBalance(); // returns the number of mismatched parenthesis
private:
    Tokenizer tok;
    int errors;
  void checkMatch( const Symbol & oParen, const Symbol & cParen );   
};

int Balance::checkBalance(){
  stack<char> parastack;

  char currpara = '\n';
  char check;


  while(currpara != '\0'){

    currpara = tok.getNextOpenClose();

    if (currpara == '(' || currpara == '{' || currpara == '['){

      parastack.push(currpara);    
    }

    else if( currpara != '\0'){

      if (parastack.size() == 0){
	errors++;
      }
      else{
	check = parastack.top();
      
	parastack.pop();

	if ((currpara == ')' && check != '(') || 
	    (check == '{' && currpara != '}') ||
	    (check == '[' && currpara != ']')){

	  errors++;

	}
      }
    }

  }

  errors += parastack.size();

  return errors;
}

void Balance::checkMatch( const Symbol & oParen, const Symbol & cParen ){
  

}
  
void stringToUpper(string &s)
{
  for(unsigned int l = 0; l < s.length(); l++)
    {
      s[l] = toupper(s[l]);
    }
}

int wordValue (const vector<int>& pointValues, const string& word) {
  int points = 0;
  
  string uWord = word;
  stringToUpper(uWord);

  for(const char& c : uWord) {
    int ind = c-'A';
    points += pointValues[ind];
  }

  return points;
}

int main(){
  ifstream ifs("Letter_point_value.txt");
  if (!ifs) cerr << "Failure to open file" << endl;

  char letter;
  int pt;


  vector<int> ptVal(26);
  
  map<char, int> ptdict;

  while (ifs >> pt >> letter) {
    
    int ind = letter - 'A';
    ptVal[ind] = pt;

  }

  // cout << wordValue(ptVal, "cAT");

  ifstream efs("ENABLE.txt");
  if (!efs) cerr << "Failure to open file" << endl;

  string word;
  map<string, int> wordValues;

  while(efs >> word){
    wordValues[word] = wordValue(ptVal,word);
  }
  
  // cerr << "test.cc" << endl;

  // Balance b(ifs);
  
  // cout << b.checkBalance();

}
