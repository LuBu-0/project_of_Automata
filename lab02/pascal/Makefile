CXX=g++
ANTLR_INCLUDE=/usr/include/antlr4-runtime
CXXFLAGS=-std=c++11 -Wno-attributes -I "$(ANTLR_INCLUDE)"
LDFLAGS=-lantlr4-runtime # -L "$(ANTLR_HOME)/lib"
DEPS=pascalLexer.cpp pascalParser.cpp
OBJS=pascalParser.o pascalLexer.o
SCOBJS=syncheck.o
ANTLRS=pascalBaseListener.h \
        pascalLexer.cpp \
        pascalLexer.tokens \
        pascalParser.cpp \
        pascalLexer.h \
        pascalParser.h \
        pascal.interp \
        pascalLexer.interp \
        pascal.tokens

all: syncheck

syncheck: $(SCOBJS) $(OBJS) $(DEPS)
	$(CXX) -o syncheck $(SCOBJS) $(OBJS) $(LDFLAGS)

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(DEPS): pascal.g4
	antlr4 -Dlanguage=Cpp -no-listener -no-visitor pascal.g4

clean:
	rm -f $(OBJS) $(TOBJS) $(SCOBJS) syncheck $(ANTLRS)

