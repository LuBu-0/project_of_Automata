#include <iostream>
#include <string>
#include <exception>
#include "runtimeVisitor.h"

using namespace std;

antlrcpp::Any runtimeVisitor::visitId_list(pascalParser::Id_listContext *ctx) {
    // Prima variabile nella lista di identificatori
    string varname = ctx->ID()->getText();
    // Resto della lista
    pascalParser::Id_listContext *tail = ctx->id_list();
    // controllo che la variabile non sia già stata dichiarata
    if(this->vars.find(varname) != tclehis->vars.end()) {
        cerr << "Error: Duplicate variable declaration '" << varname << "'" << endl;
        exit(EXIT_FAILURE);
    }
    this->vars[varname] = 0;
    // Continua sul resto della lista di identificatori, se presente
    if(tail != NULL) 
        return visitId_list(tail);
    return NULL;
}

antlrcpp::Any runtimeVisitor::visitAssign(pascalParser::AssignContext *ctx) {
    string varname = ctx->ID()->getText();
    // controllo che la variabile sia stata dichiarata
    if(this->vars.find(varname) == this->vars.end()) {
        cerr << "Error: Undefined variable '" << varname << "'" << endl;
        exit(EXIT_FAILURE);
    }
    int value = visitExpr(ctx->expr());
    this->vars[varname] = value;
    return NULL;
}

antlrcpp::Any runtimeVisitor::visitOut(pascalParser::OutContext *ctx) {
    // verifico se devo stampare intero o stringa
    if(ctx->expr() != NULL) {
        // caso stampa intero
        int value = visitExpr(ctx->expr());
        cout << value << endl;
    } else {
        string s = ctx->STRING()->getText();
        cout << s.substr(1, s.length()-2) << endl;
    }
    // DONE: implementare il caso stampa di una stringa 
    return NULL;
}

antlrcpp::Any runtimeVisitor::visitIn(pascalParser::InContext *ctx) {
    // DONE: implementa la lettura dell'input da tastiera
    // il metodo deve aggiornare il valore della variabile
    string varname = ctx->ID()->getText();
    if(this->vars.find(varname) == this->vars.end()) {
        cerr << "Error: Undefined variable '" << varname << "'" << endl;
        exit(EXIT_FAILURE);
    }
    cin >> vars[varname];
    return NULL;
}


antlrcpp::Any runtimeVisitor::visitBranch(pascalParser::BranchContext *ctx) {
    // stabilisce il valore della guardia
    bool guard = visitGuard(ctx->guard());
    if(guard) {
        // se guardia vera, esegue ramo then
        visitCode_block(ctx->code_block(0));
    } else {
        if(ctx->code_block().size() == 2) {
            visitCode_block(ctx->code_block(1));
        }
    }
    // DONE: implementa l'esecuzione del ramo else (se presente) quando la guardia è falsa 
    return NULL;
}

antlrcpp::Any runtimeVisitor::visitLoop(pascalParser::LoopContext *ctx) {
    // DONE: implementa l'esecuzione del ciclo repeat-until
    do {
        visitSt_list(ctx->st_list());
    } while(!visitGuard(ctx->guard()));
    return NULL;
}

antlrcpp::Any runtimeVisitor::visitExpr(pascalParser::ExprContext *ctx) {
    // controllo in quale caso sono
    int value = 0;
    if(ctx->ID() != NULL) {
        // caso ID
        string varname = ctx->ID()->getText();
        if(this->vars.find(varname) == this->vars.end()) {
            cerr << "Error: Undefined variable '" << varname << "'" << endl;
            exit(EXIT_FAILURE);
        }
        value = this->vars[varname];
    } else if(ctx->NUMBER() != NULL) {
        // caso NUMBER
        string numtext = ctx->NUMBER()->getText();
        value = std::stoi(numtext); 
    } else if(ctx->PLUS() != NULL) {
        // caso expr + expr
        // calcolo il valore della prima expr
        int left = visitExpr(ctx->expr(0));
        // calcolo il valore della seconda expr
        int right = visitExpr(ctx->expr(1));
        // il risultato finale è la somma
        value = left + right;
    } else if(ctx->MINUS() != NULL) {
        // caso expr - expr
        // calcolo il valore della prima expr
        int left = visitExpr(ctx->expr(0));
        // calcolo il valore della seconda expr
        int right = visitExpr(ctx->expr(1));
        // il risultato finale è la differenza
        value = left - right;
    } else if(ctx->MULT() != NULL) {
        // caso expr * expr
        // calcolo il valore della prima expr
        int left = visitExpr(ctx->expr(0));
        // calcolo il valore della seconda expr
        int right = visitExpr(ctx->expr(1));
        // il risultato finale è la moltiplicazione
        value = left * right;
    } else if(ctx->DIV() != NULL) {
        // caso expr / expr
        // calcolo il valore della prima expr
        int left = visitExpr(ctx->expr(0));
        // calcolo il valore della seconda expr
        int right = visitExpr(ctx->expr(1));
        // il risultato finale è la divisione
        value = left / right;
    } else if(ctx->MOD() != NULL) {
        // caso expr % expr
        // calcolo il valore della prima expr
        int left = visitExpr(ctx->expr(0));
        // calcolo il valore della seconda expr
        int right = visitExpr(ctx->expr(1));
        // il risultato finale è il modulo
        value = left % right;
    } else if(ctx->expr().size() == 1) {
        // caso parentesi
        value = visitExpr(ctx->expr(0));
    } 
    return value;
}

antlrcpp::Any runtimeVisitor::visitGuard(pascalParser::GuardContext *ctx) {
    // DONE: implementa la valutazione di una espressione booleana
    // il metodo ritorna true se l'espressione è vera, false altrimenti
    if(ctx->NOT() != NULL) {
        return !visitGuard(ctx->guard(0));
    } else if(ctx->AND() != NULL) {
        return visitGuard(ctx->guard(0)) && visitGuard(ctx->guard(1));
    } else if (ctx->OR() != NULL) {
        return visitGuard(ctx->guard(0)) || visitGuard(ctx->guard(1));
    } else if(ctx->guard().size() == 1) {
        return visitGuard(ctx->guard(0));
    } else {
        return visitRelation(ctx->relation());
    }
}

antlrcpp::Any runtimeVisitor::visitRelation(pascalParser::RelationContext *ctx) {
    // DONE: implementa la valutazione di un confronto 
    // il metodo ritorna true se il confronto è vero, false altrimenti
    if(ctx->EQ() != NULL) {
        return static_cast<int>(visitExpr(ctx->expr(0))) == static_cast<int>(visitExpr(ctx->expr(1)));
    } else if(ctx->LT() != NULL) {
        return static_cast<int>(visitExpr(ctx->expr(0))) < static_cast<int>(visitExpr(ctx->expr(1)));
    } else if(ctx->LEQ() != NULL) {
        return static_cast<int>(visitExpr(ctx->expr(0))) <= static_cast<int>(visitExpr(ctx->expr(1)));
    } else if(ctx->GT() != NULL) {
        return static_cast<int>(visitExpr(ctx->expr(0))) > static_cast<int>(visitExpr(ctx->expr(1)));
    } else if(ctx->GEQ() != NULL) {
        return static_cast<int>(visitExpr(ctx->expr(0))) >= static_cast<int>(visitExpr(ctx->expr(1)));
    } else if (ctx->NEQ() != NULL) {
        return static_cast<int>(visitExpr(ctx->expr(0))) != static_cast<int>(visitExpr(ctx->expr(1)));
    }
    // next line is just to avoid warning
    return false;
}
