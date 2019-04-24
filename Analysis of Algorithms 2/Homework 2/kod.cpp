/*
 *
 * Muhammed Burak Bugrul
 * 150140015
 * Analysis of Algorithms 2
 * Project 2
 * 
 */

#include <cstdio>
#include <iostream>
#include <set>
#include <map>
#include <vector>

#define fi first
#define se second
#define pb push_back
#define SIZE(a) ((int)a.size())

using namespace std;

typedef pair<string, string> ss;

const int MAXN=100;

class Parser{
	
private:
	map<string,set<string> > terminals;
	map<string,vector<ss> > non_terminals;
	map<string,string> dn[MAXN][MAXN]; // For memoization
	
public:
	Parser();
	vector<string> split( string s ); // Returns a vector of strings that consists of words of given string
	string toLower( string s ); // Turns letters of a string to lower
	string f( vector<string> &input, string state, int beg, int end ); // Divide and Conquer logic parse function
	string extractParseTree( string input );
};

Parser::Parser(){
	
	// Creating terminal and non-terminal memory
	terminals["DT"].insert("that");   terminals["DT"].insert("this");     terminals["DT"].insert("a");         terminals["DT"].insert("the");
	terminals["NN"].insert("book");   terminals["NN"].insert("flight");   terminals["NN"].insert("cat");       terminals["NN"].insert("mat");  terminals["NN"].insert("i"); terminals["NN"].insert("you"); terminals["NN"].insert("they");
	terminals["VR"].insert("booked"); terminals["VR"].insert("included"); terminals["VR"].insert("preferred"); terminals["VR"].insert("sat");
	terminals["PR"].insert("from");   terminals["PR"].insert("to");       terminals["PR"].insert("on");        terminals["PR"].insert("near"); terminals["PR"].insert("through");
	terminals["AD"].insert("big");    terminals["AD"].insert("heavy");    terminals["AD"].insert("beautiful"); terminals["AD"].insert("cheap");

	non_terminals["NP"].pb(ss("NN","NN"));
	non_terminals["NP"].pb(ss("AD","NN"));
	non_terminals["NP"].pb(ss("AD","NP"));
	non_terminals["NP"].pb(ss("DT","NP"));
	non_terminals["NP"].pb(ss("DT","NN"));
	
	non_terminals["PP"].pb(ss("PR","NN"));
	non_terminals["PP"].pb(ss("PR","NP"));
	
	non_terminals["VP"].pb(ss("VR","PP"));
	non_terminals["VP"].pb(ss("NN","VR"));
	non_terminals["VP"].pb(ss("NP","VR"));
	non_terminals["VP"].pb(ss("VR","NP"));
	
	non_terminals["S"].pb(ss("NP","VP"));
	non_terminals["S"].pb(ss("NN","VP"));
}

vector<string> Parser::split( string s ){ // Returns a vector of strings that consists of words of given string
	
	vector<string> rev;
	string cur = "";
	
	for( int i=0 ; i<SIZE(s) ; i++ )
		if( s[i] == ' ' ){ // We have found a word
			rev.pb(cur);
			cur = "";
		}
		else
			cur += s[i];
	
	if( cur != "" ) // Last word
		rev.pb(cur);

	return rev;
}

string Parser::toLower( string s ){ // Turns letters of a string to lower
	
	for( int i=0 ; i<SIZE(s) ; i++ )
		if( s[i] >= 'A' && s[i] <= 'Z' )
			s[i] = 'a'+s[i]-'A';
	
	return s;
}

string Parser::f( vector<string> &input, string state, int beg, int end ){ // Divide and Conquer logic parse function
	
	if( dn[beg][end].find(state) != dn[beg][end].end() )
		return dn[beg][end][state];
	
	if( beg > end )
		return dn[beg][end][state] = "SYNTAX ERROR";
	
	if( beg == end && terminals[state].find(toLower(input[beg])) == terminals[state].end() ) // If there is just one word
		return dn[beg][end][state] = "SYNTAX ERROR";
	else if( beg == end )
		return dn[beg][end][state] = state + "(" + input[beg] + ")";
	
	for( int i=end ; i>beg ; i-- ) // Starting from right
		for( vector<ss>::iterator it = non_terminals[state].begin() ; it != non_terminals[state].end() ; it++ ){ // Trying every proper state transitions
			
			string left = f(input,it->fi,beg,i-1); // Solution of left subtree
			string right = f(input,it->se,i,end); // Solution of right subtree
			
			if( left != "SYNTAX ERROR" && right != "SYNTAX ERROR" ) // If both subtrees are valid
				return dn[beg][end][state] = state + "[" + left + " " + right + "]";
		}
	
	return dn[beg][end][state] = "SYNTAX ERROR"; // If there is not a valid parse method for this state
}

string Parser::extractParseTree( string input ){
	
	vector<string> splitted = split(input); // Splitting input into words
	
	for( int i=0 ; i<SIZE(splitted) ; i++ ) // Initializing dynamic array
		for( int j=i ;  j<SIZE(splitted) ; j++ )
			dn[i][j].clear();
	
	return f(splitted,"S",0,SIZE(splitted)-1); // Finding parse tree
}

int main( int argc, char **argv ){
	
	char ch;
	string s = "";
	Parser p;
	
	freopen(argv[1],"r",stdin);
	freopen("output.txt","w",stdout);
	
	while( scanf("%c",&ch) != EOF )
		if( ch == '\r' )
			continue;
		else if( ch == '\n' ){ // End of the line
			cout << p.extractParseTree(s) << endl;
			s = "";
		}
		else{
			s += ch;
		}
	
	if( s != "" ) // Last line
		cout << p.extractParseTree(s) << endl;
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
