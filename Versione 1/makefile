bison -d -o parser.c syntax.y
flex -o lexer.c lexer.fl
gcc -o program parser.c lexer.c
./program < input