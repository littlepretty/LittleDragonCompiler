EXE = LittleDragonCompiler

RM = rm -f

INCLUDES = -I../includes
CFLAGS = -c -Wall
CC = g++ $(INCLUDES)

.PHONY: all
all: $(EXE)

.PHONY: clean
clean:
	$(RM) *.o $(EXE)
	

$(EXE):	main.o Parser.o Lexer.o Token.o Word.o DataType.o Node.o Expr.o Op.o Logical.o Stmt.o Env.o
	$(CC) $^ -o $@
	$(RM) $^
	
main.o: main.cpp 
	$(CC) $(CFLAGS) $<
	
Lexer.o: Lexer.cpp 
	$(CC) $(CFLAGS) $<
	
Parser.o: Parser.cpp 
	$(CC) $(CFLAGS) $<
	
Token.o: Token.cpp 
	$(CC) $(CFLAGS) $<
	
Word.o: Word.cpp 
	$(CC) $(CFLAGS) $<
	
DataType.o: DataType.cpp 
	$(CC) $(CFLAGS) $<
	
Node.o: Node.cpp 
	$(CC) $(CFLAGS) $<

Expr.o: Expr.cpp 
	$(CC) $(CFLAGS) $<
	
Op.o: Op.cpp 
	$(CC) $(CFLAGS) $<
	
Logical.o: Logical.cpp 
	$(CC) $(CFLAGS) $<
	
Stmt.o: Stmt.cpp 
	$(CC) $(CFLAGS) $<
	
Env.o: Env.cpp 
	$(CC) $(CFLAGS) $<
	
	
