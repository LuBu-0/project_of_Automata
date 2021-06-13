#include <iostream>
#include <fstream>
#include <string>
#include "antlr4-runtime.h"
#include "pascalLexer.h"
#include "pascalParser.h"

using namespace std;
using namespace antlr4;

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Usage: syncheck filename.pas" << endl;
        return 1;
    }
    ifstream pascalFile(argv[1]);
    if(pascalFile.fail()){
        // File open error
        cout << "Error while reading file " << argv[1] << endl;
        return 1;
    }
    ANTLRInputStream input(pascalFile);
    pascalLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    pascalParser parser(&tokens);
    tree::ParseTree *tree = parser.start();
    int errors = parser.getNumberOfSyntaxErrors();
    if(errors > 0) {
        cout << errors << " syntax errors found." << endl;
        return 1;
    } 
    cout << "No syntax errors found." << endl;   
    return 0;
}
