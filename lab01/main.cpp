#include <iostream>
#include <fstream>
#include <string>
#include "automata.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Usage: main filename" << endl;
        return 1;
    }

    // open input file
    ifstream inputFile(argv[1]);
    if(inputFile.fail()){
        // file open error
        cout << "Error while reading file " << argv[1] << endl;
        return 1;
    }    
    // read file into a string
    string inputProgram((istreambuf_iterator<char>(inputFile)),
                        (istreambuf_iterator<char>()));
	cout << "Input: " << inputProgram << endl;
    // close input file
    inputFile.close();
    // Try to recognize with automaton for "repeat"
	WordDFA repeatDFA("repeat");
	cout << "REPEAT: " << repeatDFA.run(inputProgram) << endl;
	// Try to recognize with automaton for comments
	CommentDFA commentDFA; 
	cout << "COMMENT: " << commentDFA.run(inputProgram) << endl;

    return 0;
}
