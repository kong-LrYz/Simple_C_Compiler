/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    float_number = 258,            /* float_number  */
    int_number = 259,              /* int_number  */
    identifier = 260,              /* identifier  */
    one_char = 261,                /* one_char  */
    boolsym = 262,                 /* boolsym  */
    charsym = 263,                 /* charsym  */
    constsym = 264,                /* constsym  */
    staticsym = 265,               /* staticsym  */
    doublesym = 266,               /* doublesym  */
    floatsym = 267,                /* floatsym  */
    intsym = 268,                  /* intsym  */
    longsym = 269,                 /* longsym  */
    shortsym = 270,                /* shortsym  */
    signedsym = 271,               /* signedsym  */
    unsignedsym = 272,             /* unsignedsym  */
    voidsym = 273,                 /* voidsym  */
    falsesym = 274,                /* falsesym  */
    truesym = 275,                 /* truesym  */
    whilesym = 276,                /* whilesym  */
    dosym = 277,                   /* dosym  */
    ifsym = 278,                   /* ifsym  */
    elsesym = 279,                 /* elsesym  */
    ifelsesym = 280,               /* ifelsesym  */
    switchsym = 281,               /* switchsym  */
    casesym = 282,                 /* casesym  */
    defaultsym = 283,              /* defaultsym  */
    forsym = 284,                  /* forsym  */
    gotosym = 285,                 /* gotosym  */
    trysym = 286,                  /* trysym  */
    catchsym = 287,                /* catchsym  */
    continuesym = 288,             /* continuesym  */
    breaksym = 289,                /* breaksym  */
    andsym = 290,                  /* andsym  */
    orsym = 291,                   /* orsym  */
    newsym = 292,                  /* newsym  */
    deletesym = 293,               /* deletesym  */
    enumsym = 294,                 /* enumsym  */
    structsym = 295,               /* structsym  */
    returnsym = 296,               /* returnsym  */
    sizeofsym = 297,               /* sizeofsym  */
    typedefsym = 298,              /* typedefsym  */
    inlinesym = 299,               /* inlinesym  */
    throwsym = 300,                /* throwsym  */
    comma = 301,                   /* comma  */
    left_bracket = 302,            /* left_bracket  */
    right_bracket = 303,           /* right_bracket  */
    question = 304,                /* question  */
    colon = 305,                   /* colon  */
    equal = 306,                   /* equal  */
    muti_equal = 307,              /* muti_equal  */
    divi_equal = 308,              /* divi_equal  */
    mod_equal = 309,               /* mod_equal  */
    plus_equal = 310,              /* plus_equal  */
    minus_equal = 311,             /* minus_equal  */
    rshift_equal = 312,            /* rshift_equal  */
    lshift_equal = 313,            /* lshift_equal  */
    and_equal = 314,               /* and_equal  */
    xor_equal = 315,               /* xor_equal  */
    or_equal = 316,                /* or_equal  */
    logi_or = 317,                 /* logi_or  */
    logi_and = 318,                /* logi_and  */
    inclu_or = 319,                /* inclu_or  */
    exclu_or = 320,                /* exclu_or  */
    solo_and = 321,                /* solo_and  */
    double_equal = 322,            /* double_equal  */
    unequal = 323,                 /* unequal  */
    logi_not = 324,                /* logi_not  */
    bit_not = 325,                 /* bit_not  */
    less = 326,                    /* less  */
    greater = 327,                 /* greater  */
    less_and_equal = 328,          /* less_and_equal  */
    greater_and_equal = 329,       /* greater_and_equal  */
    lshift = 330,                  /* lshift  */
    rshift = 331,                  /* rshift  */
    plus = 332,                    /* plus  */
    minus = 333,                   /* minus  */
    star = 334,                    /* star  */
    slash = 335,                   /* slash  */
    mod = 336,                     /* mod  */
    left_paren = 337,              /* left_paren  */
    right_paren = 338,             /* right_paren  */
    semicolon = 339,               /* semicolon  */
    hash = 340,                    /* hash  */
    left_brace = 341,              /* left_brace  */
    right_brace = 342,             /* right_brace  */
    dot_star = 343,                /* dot_star  */
    arrow_star = 344,              /* arrow_star  */
    double_add = 345,              /* double_add  */
    double_minus = 346,            /* double_minus  */
    dot = 347,                     /* dot  */
    three_dots = 348,              /* three_dots  */
    arrow = 349,                   /* arrow  */
    single_quote = 350,            /* single_quote  */
    nullptr = 351                  /* nullptr  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 478 "parser.y"

    int ival;
    float fval;
    struct{
        int value;
        char* name;
        int ptr_level;
        int lastpar;                        //for function,record the last parameter's addr
        // int psize;                          //for function,record all parameters's size

    }sval;


    struct {
        int type;
        int kind;                       //constant or variable
        char* name;

        union {
            int b_val;                  //bool
            char c_val;
            double d_val;
            float f_val;
            int i_val;
            long l_val;
            short s_val;
            void* p_val;
        };
        int size;                       //for p_val
    }expr_attri;

    struct {
        int count;  /* 实参个数 */
        struct {
            int type;
            int kind;      /* constant 或 variable */
            char* name;    /* 变量名（常量时可忽略） */
            union {
                int b_val;
                char c_val;
                double d_val;
                float f_val;
                int i_val;
                long l_val;
                short s_val;
                void* p_val;
            };
            int size;      
        } args[32];
    } arg_list;

    struct {
       int type[10];
       int type_num;
       int basic_type;
    }decl_specifier_seq;



#line 220 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */
