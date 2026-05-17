%{

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

int yylex();
void yyerror(char *s);

TList list = NULL;
int i=0, k=0;

char* tmp() {
	char* t = (char*)malloc(sizeof(char*));
	sprintf(t, "t%d", i);
	i++;
	return t;
}

char* newLabel() {
	char* l = (char*)malloc(sizeof(char*));
	sprintf(l, "L%d", k);
	k++;
	return l;
}

%}


%union {
	int number;
	char* identifier;
	struct label {
		char* label1;
		char* label2;
	} label;
}

%token <number> NUM
%token <identifier> ID
%token PRINT INT IF ELSE WHILE ENDFILE MAIN
%left '+' '-'
%left '*' '/'
%right UMINUS
%left OR
%left AND
%right NOT
%nonassoc EQ LT GT LE GE NE
%type <identifier> expr
%type <identifier> comp
%type <identifier> bexpr
%type <label> ifstmt
%type <label> whileM
%type <label> whilestmt

%%
program	: MAIN '(' ')' openb lstmt closeb ENDFILE			{ return 0; }
		 	;

lstmt		: lstmt stmt ';'
			| stmt ';'
			| lstmt openb lstmt closeb
			| openb lstmt closeb
			| ifstmt openb lstmt closeb															{ printf("%s:\n", $1.label1); }
			| whilestmt openb lstmt closeb														{ printf("goto %s;\n%s:\n", $1.label1 ,$1.label2); }
			| ifstmt openb lstmt closeb er1 ELSE er2 openb lstmt closeb					{ 	
			  																									printf("goto %s;\n", $1.label2);
			  																									printf("%s:\n", $1.label2);
			  																								}
			| lstmt ifstmt openb lstmt closeb 													{ printf("%s:\n", $2.label1); }
			| lstmt whilestmt openb lstmt closeb												{ printf("goto %s;\n%s:\n", $2.label1 ,$2.label2); }
			| lstmt ifstmt openb lstmt closeb er1 ELSE er2 openb lstmt closeb			{ 	
			  																									printf("goto %s;\n", $2.label2);
			  																									printf("%s:\n", $2.label2);
			  																								}
			;

er1		: 								{ printf("goto %s;\n", $<label>-3.label2); }
			;

er2		: 								{ printf("%s:\n", $<label>-5.label1); }
			;

ifstmt 	: IF '(' bexpr ')'		{
												char* ltmp = (char*)malloc(sizeof(char*));
												ltmp = newLabel();
												$$.label1 = newLabel();
												printf("if (%s) goto %s;\n", $3, ltmp); 
												printf("goto %s;\n", $$.label1);
												printf("%s:\n", ltmp);
												$$.label2 = newLabel();
											}
			;


whilestmt: WHILE whileM '(' bexpr ')'	{
														char* ltmp = (char*)malloc(sizeof(char*));
														ltmp = newLabel();
														$$.label2 = newLabel();
														$$.label1 = $2.label1;
														printf("if (%s) goto %s;\n", $4, ltmp);
														printf("goto %s;\n", $$.label2);
														printf("%s:\n", ltmp);
													}
			;

whileM 	: 								{ 
												$$.label1 = newLabel();
												printf("%s:\n", $$.label1);
											}
			;

openb		: '{'							{ printf("list = insertElement(list);\n"); }
			;

closeb	: '}'							{ printf("list = removeElement(list);\n"); }
			;

stmt		: INT ID 					{ printf("addVar(\"%s\", &list->table);\n", $2); }
			| INT ID '=' NUM  		{
												printf("addVar(\"%s\", &list->table);\n", $2);
												printf("setVarList(\"%s\", %d, list);\n", $2, $4);
											}
			| ID '=' expr				{ printf("setVarList(\"%s\", %s, list);\n", $1, $3); }
			| PRINT '(' ID ')'		{ printf("printf(\"%%s: %%d\\n\", \"%s\", getVarList(\"%s\", list));\n", $3, $3); }
			| ID '=' bexpr				{ printf("setVarList(\"%s\", %s, list);\n", $1, $3); }
			;

bexpr		: bexpr OR bexpr			{
												$$ = tmp();
												printf("%s = %s || %s;\n", $$, $1, $3);
											}
			| bexpr AND bexpr			{
												$$ = tmp();
												printf("%s = %s && %s;\n", $$, $1, $3);
											}
			| NOT bexpr					{
												$$ = tmp();
												printf("%s = !%s;\n", $$, $2);
											}
			| '(' bexpr ')'			{ $$ = $2; }
			| comp						{ $$ = $1; }
			;

comp		: expr LT expr				{
												$$ = tmp();
												printf("%s = %s < %s;\n", $$, $1, $3);
											}
			| expr LE expr				{
												$$ = tmp();
												printf("%s = %s <= %s;\n", $$, $1, $3);
											}
			| expr GT expr				{
												$$ = tmp();
												printf("%s = %s > %s;\n", $$, $1, $3);
											}
			| expr GE expr				{
												$$ = tmp();
												printf("%s = %s >= %s;\n", $$, $1, $3);
											}
			| expr EQ expr				{
												$$ = tmp();
												printf("%s = %s == %s;\n", $$, $1, $3);
											}
			| expr NE expr				{
												$$ = tmp();
												printf("%s = %s != %s;\n", $$, $1, $3);
											}
			| expr AND expr			{
												$$ = tmp();
												printf("%s = %s && %s;\n", $$, $1, $3);
											}
			| expr OR expr				{
												$$ = tmp();
												printf("%s = %s || %s;\n", $$, $1, $3);
											}
			;

expr  	: expr '+' expr			{  
												$$ = tmp();
												printf("%s = %s + %s;\n", $$, $1, $3);
											}
			| expr '-' expr			{ 
												$$ = tmp();
												printf("%s = %s - %s;\n", $$, $1, $3);
											}
			| expr '*' expr			{
												$$ = tmp();
												printf("%s = %s * %s;\n", $$, $1, $3);
											}
			| expr '/' expr			{
												$$ = tmp();
												printf("%s = %s / %s;\n", $$, $1, $3);
											}
			| '(' expr ')'				{ $$ = $2; }
			| '-' expr %prec UMINUS	{ 
												$$ = tmp();
												printf("%s = -%s;\n", $$, $2); 
											}
			| ID 							{ 
												$$ = tmp();
												printf("%s = getVarList(\"%s\", list);\n", $$, $1);
											}
			| NUM 						{
												$$ = tmp();
												printf("%s = %d;\n", $$, $1);
											}
			;

%%

int main () {
	if(yyparse() !=0)
		fprintf(stderr, "Abonormal exit\n");
	return 0;
}

void yyerror (char *s) {
	fprintf(stderr, "Error: %s\n", s);
}