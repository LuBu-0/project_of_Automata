#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "antlr4-runtime.h"
#include "pascalLexer.h"
#include "pascalParser.h"
#include "runtimeVisitor.h"

using namespace std;
using namespace antlr4;

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Usage: pascal filename.tc" << endl;
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
    pascalParser::StartContext *tree = parser.start();
    int errors = parser.getNumberOfSyntaxErrors();
    if(errors > 0) {
        cout << errors << " syntax errors found." << endl;
        return 1;
    } 

    cout << "Running program " << argv[1] << endl;
    runtimeVisitor visitor;
    visitor.visitStart(tree);    
    return 0;
}
