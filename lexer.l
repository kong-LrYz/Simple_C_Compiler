%{

#include"parser.h"
    
%}

%%

[ \t\r\n]+          {}

"bool"                {return boolsym;}
"char"                {return charsym;}
"const"               {return constsym;}
"static"              {return staticsym;}
"double"              {return doublesym;}
"float"               {return floatsym;}
"int"                 {return intsym;}
"long"                {return longsym;}
"short"               {return shortsym;}
"signed"              {return signedsym;}
"unsigned"            {return unsignedsym;}
"void"                {return voidsym;}

"false"               {return falsesym;}
"true"                {return truesym;}

"while"               {return whilesym;}
"do"                    {return dosym;}
"if"                  {return ifsym;}
"else"                {return elsesym;}
"ifelse"              {return ifelsesym;}
"switch"              {return switchsym;}
"case"                {return casesym;}
"default"             {return defaultsym;}
"for"                 {return forsym;}
"goto"                {return gotosym;}
"try"                 {return trysym;}
"catch"               {return catchsym;}

"continue"            {return continuesym;}
"break"               {return breaksym;}

"and"                 {return andsym;}
"or"                  {return orsym;}

"new"                 {return newsym;}
"delete"              {return deletesym;}

"enum"                {return enumsym;}
"struct"              {return structsym;}

"return"              {return returnsym;}

"sizeof"              {return sizeofsym;}
"typedef"             {return typedefsym;}

"inline"              {return inlinesym;}

"NULL"                {return nullptr;}

"throw"                 {return throwsym;}

[0-9]+\.[0-9]+ {yylval.fval = atof(yytext);return float_number;}
[0-9]+  {yylval.ival = atoi(yytext);return int_number;}
[a-zA-Z][a-zA-Z0-9_]+ {yylval.sval.value = 0;yylval.sval.name = strdup(yytext);yylval.sval.ptr_level = 0;return identifier;}
[a-zA-Z]    {yylval.sval.value = 0;yylval.sval.name = strdup(yytext);yylval.sval.ptr_level = 0;return one_char;}



"*="            {return muti_equal;}
"/="            {return divi_equal;}
"%="            {return mod_equal;}
"+="            {return plus_equal;}
"-="            {return minus_equal;}
">>="           {return rshift_equal;}
"<<="           {return lshift_equal;}
"&="            {return and_equal;}
"^="            {return xor_equal;}
"|="            {return or_equal;}
"..."           {return three_dots;}

"||"            {return logi_or;}
"&&"            {return logi_and;}
"|"             {return inclu_or;}
"^"             {return exclu_or;}
"&"             {return solo_and;}
"!"             {return logi_not;}
"~"             {return bit_not;}

"=="            {return double_equal;}
"!="            {return unequal;}


">="            {return greater_and_equal;}
"<="            {return less_and_equal;}
">"             {return greater;}
"<"             {return less;} 

"<<"            {return lshift;}
">>"            {return rshift;}


"+"             {return plus;}
"-"             {return minus;}
"*"             {return star;}
"/"             {return slash;}
"%"             {return mod;}



".*"            {return dot_star;}
"->*"           {return arrow_star;}

"++"            {return double_add;}
"--"            {return double_minus;}
"->"            {return arrow;}

"="             {return equal;}
"("             {return left_paren;}
")"             {return right_paren;}   
";"             {return semicolon;}
"#"             {return hash;}
"{"             {return left_brace;}
"}"             {return right_brace;}
","             {return comma;}
"["             {return left_bracket;}              
"]"             {return right_bracket;}
"?"             {return question;}
":"             {return colon;}
"."             {return dot;}
"'"             {return single_quote;}




%%


int yywrap(void) {
    return 1;
}
