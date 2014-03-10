EXE		=	LittleDragonCompiler
CC		=	g++
CFLAGS	=	-c -Wall
RM		=	rm -f


.PHONY: all
all: $(EXE).out

.PHONY: clean
clean:
	$(RM) *.o *.out
	

$(EXE).out:	main.o Parser.o Lexer.o Token.o Word.o DataType.o Node.o Expr.o Op.o Logical.o Stmt.o Env.o
	$(CC) $^ -o $@
	$(RM) $^
	
main.o: main.cpp Lexer.h Parser.h
	$(CC) $(CFLAGS) $<
	
Lexer.o: Lexer.cpp Lexer.h Word.h DataType.h
	$(CC) $(CFLAGS) $<
	
Parser.o: Parser.cpp Parser.h Lexer.h Token.h Stmt.h DataType.h Env.h Logical.h
	$(CC) $(CFLAGS) $<
	
Token.o: Token.cpp Token.h 
	$(CC) $(CFLAGS) $<
	
Word.o: Word.h Word.cpp Token.h
	$(CC) $(CFLAGS) $<
	
DataType.o: DataType.cpp DataType.h Word.h
	$(CC) $(CFLAGS) $<
	
Node.o: Node.cpp Node.h ExternGlobal.h
	$(CC) $(CFLAGS) $<

Expr.o: Expr.cpp Expr.h Node.h Token.h Word.h DataType.h
	$(CC) $(CFLAGS) $<
	
Op.o: Op.cpp Op.h Expr.h Token.h DataType.h
	$(CC) $(CFLAGS) $<
	
Logical.o: Logical.cpp Logical.h Expr.h DataType.h
	$(CC) $(CFLAGS) $<
	
Stmt: Stmt.cpp Stmt.h Expr.h Node.h Op.h
	$(CC) $(CFLAGS) $<
	
Env.o: Env.cpp Env.h Expr.h Word.h
	$(CC) $(CFLAGS) $<
	
	
