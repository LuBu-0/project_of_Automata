CXX=g++
ANTLR_INCLUDE=/usr/include/antlr4-runtime
CXXFLAGS=-std=c++11 -Wno-attributes -I "$(ANTLR_INCLUDE)"
LDFLAGS=-lantlr4-runtime 
TCDEPS=runtimeVisitor.h
DEPS=pascalLexer.cpp pascalParser.cpp
OBJS=pascalParser.o pascalLexer.o
SCOBJS=syncheck.o
TCOBJS=pascal.o runtimeVisitor.o
ANTLRS=pascalBaseListener.h \
        pascalLexer.cpp \
        pascalLexer.tokens \
        pascalParser.cpp \
        pascalLexer.h \
        pascalParser.h \
        pascalBaseVisitor.h \
        pascalBaseVisitor.cpp \
        pascalVisitor.h \
        pascalVisitor.cpp \
        pascal.interp \
        pascalLexer.interp \
        pascal.tokens

all: syncheck pascal

syncheck: $(SCOBJS) $(OBJS) $(DEPS)
	$(CXX) -o syncheck $(SCOBJS) $(OBJS) $(LDFLAGS)

pascal: $(TCOBJS) $(OBJS) $(DEPS) $(TCDEPS)
	$(CXX) -o pascal $(TCOBJS) $(OBJS) $(LDFLAGS)

%.o: %.cpp $(DEPS) $(TCDEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(DEPS): pascal.g4
	antlr4 -Dlanguage=Cpp -no-listener -visitor pascal.g4

clean:
	rm -f $(OBJS) $(TCOBJS) $(SCOBJS) syncheck pascal $(ANTLRS)

