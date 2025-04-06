#include <iostream>  //library for cout 
#include <fstream>   //library to read files 
#include <cctype>    // library to check characters 
#include <string>    //library for the string type 

using namespace std; // it allows me to skip writing std::

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define END_OF_FILE -1

#define INT_LIT 10 // means character 
#define IDENT 11 //means the token is an identifier 
#define ASSIGN_OP 20 //means the token is an addition operation 
#define ADD_OP 21 //means the token is an addition operation 
#define SUB_OP 22 //means the token is a subtraction an operation 
#define MULT_OP 23 //means the token is an multiplication operation 
#define DIV_OP 24 //means the token is an division operation 
#define LEFT_PAREN 25 //means the token is a left bracket   
#define RIGHT_PAREN 26 //means the token is a right bracket

int charClass; // used to store the type of current character 
string lexeme; // used to store the group of characters 
char nextChar; // using to read the character  
int nextToken; // the token code for the lexeme 
ifstream in_fp; // file object to read front.in 

void addChar();
void getChar();
void getNonBlank();
int lookup(char ch);
int lex();

void addChar() {
    lexeme += nextChar; //adding the value of the nextchar to the lexeme 
}

void getChar() { //void in a function does not return anything it just reads the next char
    if (in_fp.get(nextChar)) { //in_fp input file from (ifstream in_fp;) and the if checks if the read was successful 
        if (isalpha(nextChar)) //function from isalpha() it checks if the nextchar is an alphabetic
            charClass = LETTER; //it tells the chrecter it just read that its a letter 
        else if (isdigit(nextChar)) //it checks either the character is a digit 
            charClass = DIGIT; //its a number 
        else
            charClass = UNKNOWN; //if its not a digit of=r a letter then its a symbol and we set it to unknown 
    }
    else {
        charClass = END_OF_FILE; //means stop reading its the end 
    }
}

void getNonBlank() {
    while (isspace(nextChar)) //this function skips any spaces 
        getChar();
}

int lookup(char ch) { //new fnction named lookup
    switch (ch) { //it will compare ch to many different operation 
    case '(': // it will do the following if the character is '('
        addChar(); //take the current character from nextchar and adds it to lexems 

        nextToken = LEFT_PAREN; //assign the nextToken to left_paren
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN; //RIGHT_PAREN stands for )
        break;
    case '+':
        addChar();
        nextToken = ADD_OP; //stands for +
        break;
    case '-': //stands for -
        addChar();
        nextToken = SUB_OP; //stands for subtraction  
        break;
    case '*':
        addChar();
        nextToken = MULT_OP; //stands for multiplication *
        break;
    case '/':
        addChar();
        nextToken = DIV_OP; //stands for division 
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP; //stands for =
        break;
    default:
        addChar();
        nextToken = END_OF_FILE; // the symbol is not recognized 
        break;
    }
    return nextToken; //return the token type 
}

int lex() {
    lexeme = ""; //clears the lexeme
    getNonBlank(); //call function that skips all spaces

    switch (charClass) {
    case LETTER:
        addChar(); //add the first letter to lexeme 
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT; //set token type to identifier 
        break;

    case DIGIT:
        addChar(); //add the first digit
        getChar();//get next charecter
        while (charClass == DIGIT) { //keep adding digits until you reach something else 
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN:
        lookup(nextChar); //finds out what kind of operators this is 
        getChar(); //reads the next character 
        break;

    case END_OF_FILE: //it happens when there is no more files to read 
        nextToken = END_OF_FILE;
        lexeme = "EOF";
        break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;

    return nextToken; //prints the token and lexeme 
}

int main() {
    in_fp.open("front.in"); //opens the file 

    if (!in_fp) {
        cerr << "ERROR - cannot open front.in" << endl;
        return 1; //it calls lex() until it reaches the end of the file 
    }

    getChar();

    do {
        lex();
    } while (nextToken != END_OF_FILE);

    in_fp.close(); //closes the file 
    return 0;
}