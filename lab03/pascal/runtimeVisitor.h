#pragma once

#include "antlr4-runtime.h"
#include "pascalVisitor.h"
#include "pascalBaseVisitor.h"

/**
 * This class provides a concrete visitor which only needs to handle a subset of the available methods.
 */
class  runtimeVisitor : public pascalBaseVisitor {
protected:
    std::map<std::string,int> vars;
    
public:

  antlrcpp::Any visitId_list(pascalParser::Id_listContext *ctx);

  antlrcpp::Any visitAssign(pascalParser::AssignContext *ctx);

  antlrcpp::Any visitOut(pascalParser::OutContext *ctx);

  antlrcpp::Any visitIn(pascalParser::InContext *ctx);

  antlrcpp::Any visitBranch(pascalParser::BranchContext *ctx);

  antlrcpp::Any visitLoop(pascalParser::LoopContext *ctx);

  antlrcpp::Any visitExpr(pascalParser::ExprContext *ctx);

  antlrcpp::Any visitGuard(pascalParser::GuardContext *ctx);

  antlrcpp::Any visitRelation(pascalParser::RelationContext *ctx);

};

