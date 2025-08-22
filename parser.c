/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "emitter_tmpfile.h"


static FuncEmitterTF fe;
FILE *final_out;

#define TABLE_NUM 1000



enum symbol_type{
    symbol_bool,symbol_char,symbol_const,symbol_static,
    symbol_double,symbol_float,symbol_int,symbol_long,
    symbol_short,symbol_signed,symbol_unsigned,symbol_void,
    symbol_function,symbol_point
};

enum symbol_kind{
    constant,variable,type,function
};

enum symbol_bitmask{                                //use to exam specifier conflict
    BIT_BOOL        =           1 << 0,
    BIT_FLOAT       =           1 << 1,
    BIT_DOUBLE      =           1 << 2,
    BIT_CHAR        =           1 << 3,
    BIT_INT         =           1 << 4,
    BIT_VOID        =           1 << 5,



    BIT_LONG        =           1 << 6,
    BIT_SHORT       =           1 << 7,
    BIT_SIGNED      =           1 << 8,  
    BIT_UNSIGNED    =           1 << 9,

    BIT_CONST       =           1 << 10,
    BIT_STATIC      =           1 << 11,

    BIT_FUNCTION    =           1 << 12,
    BIT_POINTER     =           1 << 13
};


struct nametab_struct{
    char* name;
    enum symbol_type type[10];
    int type_num;
    enum symbol_type basic_type;
    enum symbol_kind kind;
    bool normal;
    unsigned int ref;

    int size;                           //unit:1byte(8bits)

    unsigned int adr;

    int link;
    
    
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
    int ptr_level;
    

};

struct btab_struct{
    enum symbol_type type[10];
    int type_num;
    enum symbol_type basic_type;
    char* name;

    unsigned int lastpar;
    unsigned int last;
    unsigned int psize;
    unsigned int vsize;
};

struct atab_struct{
    enum symbol_type intxtyp;
    enum symbol_type eltyp;
    unsigned int elref;
    int low;
    int high;
    unsigned int elsize;
    unsigned int size;
};

struct code_struct{

};


struct nametab_struct nametab[TABLE_NUM];
int nametab_count = 1;
int last_index = 0;                                 //the current function's last var
int par_index = 0;                                  //the current function's last par

struct btab_struct btab[TABLE_NUM];
int btab_count = 1;

int par_point = 8;                                  //参数偏移
int loc_point = 0;                                  //局部变量偏移
int var_point = 0;                                  //



struct atab_struct atab[TABLE_NUM];

struct code_struct code[TABLE_NUM];
unsigned int cx = 0;

int current_type[10];
int current_type_num = 0;
int current_basic_type;

int bitsmask = 0;                                   //use to exam specifier conflict

int stack[10];
int sp = 0;



int yylex();
void yyerror(const char *s);

void Enter_Nametab(int type[],int type_num,int basic_type,int kind,char* name,bool normal,int b_val,char c_val,double d_val,float f_val,int i_val,long l_val,short s_val,void* p_val,int ptr_level);
void Enter_Btab(int type[],int type_num,int basic_type,char* name,int lastpar,int last,int psize,int vsize);

void Is_Valid_Declarator(char* name,int loop);
void Is_Valid_Function(char* name);
void Is_correct_specifier();

void Display_Nametab();
void Display_Btab();

void Clear_current_type();
void Clear_After_Declaration();

void pushStack(int ele);
int popStack();


extern int yylineno;
extern char* yytext;

void yyerror(const char *s) {
    fprintf(stderr, "[Bison Error] at line %d: %s\n", yylineno, s);
    fprintf(stderr, "    Last matched token: '%s'\n", yytext);
    exit(0);
}

void Enter_Nametab(int type[],int type_num,int basic_type,int kind,char* name,bool normal,int b_val,char c_val,double d_val,float f_val,int i_val,long l_val,short s_val,void* p_val,int ptr_level){
    for(int i = 0;i < type_num;i++){
        nametab[nametab_count].type[i] = type[i];
    }
    nametab[nametab_count].type_num = type_num;

    nametab[nametab_count].basic_type = basic_type;

    if(basic_type == symbol_char){
        nametab[nametab_count].size = 1;
    }
    else if(basic_type == symbol_bool || basic_type == symbol_int || basic_type == symbol_float){
        nametab[nametab_count].size = 4;
    }
    else if(basic_type == symbol_double){
        nametab[nametab_count].size = 8;
    }

    nametab[nametab_count].kind = kind;

    nametab[nametab_count].name = name;

    nametab[nametab_count].normal = normal;

    if(normal == false){                                            //这是函数参数
        nametab[nametab_count].adr = par_point;
        par_point += nametab[nametab_count].size;
    }else{                                                          //这是函数的局部变量  或者 全局变量
        loc_point += nametab[nametab_count].size;
        nametab[nametab_count].adr = -loc_point;
    }


    nametab[nametab_count].link = last_index;
    last_index = nametab_count;


    nametab[nametab_count].b_val = b_val;
    nametab[nametab_count].c_val = c_val;
    nametab[nametab_count].d_val = d_val;
    nametab[nametab_count].f_val = f_val;
    nametab[nametab_count].i_val = i_val;
    nametab[nametab_count].l_val = l_val;
    nametab[nametab_count].s_val = s_val;
    nametab[nametab_count].p_val = p_val;

    nametab[nametab_count].ptr_level = ptr_level;


    nametab_count++;
}

void Enter_Btab(int type[],int type_num,int basic_type,char* name,int lastpar,int last,int psize,int vsize){
    
    for(int i = 0;i < type_num;i++){
        btab[btab_count].type[i] = type[i];
    }
    btab[btab_count].type_num = type_num;

    btab[btab_count].basic_type = basic_type;
    
    btab[btab_count].name = name;
    
    btab[btab_count].lastpar = lastpar;
    btab[btab_count].last = last;
    btab[btab_count].psize = psize;
    btab[btab_count].vsize = vsize;

    btab_count++;
}

void Is_Valid_Declarator(char* name,int loop){
    while(1){                                                                           //reseach in nametab
        if(loop == 0) break;
        if(strcmp(name,nametab[loop].name) == 0){
            printf("wrong:\tthe repeated declarator %s",name);
            exit(0);
        }
        loop = nametab[loop].link;
        if(loop == 0) break;
    }
    
    for(int i = 1;i < btab_count;i++){                                                  //reseach in btab
        if(strcmp(name,btab[i].name) == 0){
            printf("wrong:\tthe repeated function name %s",name);
            exit(0);
        }
    }
}

void Is_Valid_Function(char* name){
    for(int i = 1;i < btab_count;i++){
        if(strcmp(name,btab[i].name) == 0){
            printf("wrong:\tthe repeated function name %s",name);
            exit(0);
        }
    }
}

void Is_correct_specifier(){
    int tmp = bitsmask;
    int bits1 = tmp & 0x003F;
    int bits2 = (tmp >> 6) & 0x000F;
    int bits3 = (tmp >> 10) & 0x0002;
    int bits4 = (tmp >> 12) & 0x0002;

    if(bits1 > 1){
        printf("basic specifier only one!!!!\n");
        exit(0);
    }

    if((bits2 >> 2) == 3){
        printf("long and short can't both exist!!!!!\n");
        exit(0);
    }

    if((bits2 & 0x0002) == 3){
        printf("signed and unsigned can't both exist!!!!!\n");
        exit(0);
    }

    if(((bits1 & 0x0020) + bits2) > 1){
        printf("void and long,short,signed,unsigned can't both exist!!!!!\n");
        exit(0);
    }

    if(((bits1 & 0x0007) + bits2) > 1){
        printf("bool,float,double and long,short,signed,unsigned can't both exist!!!!!\n");
        exit(0);
    }
}


void Display_Nametab(){
    printf("the following is name table (nametab):\n");

        // Print table header
    printf("%-4s %-15s %-20s %-12s %-10s %-6s %-6s %-6s %-6s %-6s %s\n",
           "Idx", "Name", "Types", "BasicType", "Kind", "Norm", "Ref", "Size", "Adr", "Link", "Value");
    printf("---- --------------- -------------------- ------------ ---------- ------ ------ ------ ------ ------ --------------------\n");


    char* type_name[64];
    char* kind_name[10];
    
    type_name[symbol_bool] = strdup("bool");
    type_name[symbol_char] = strdup("char");
    type_name[symbol_const] = strdup("const");
    type_name[symbol_static] = strdup("static");
    type_name[symbol_double] = strdup("double");
    type_name[symbol_float] = strdup("float");
    type_name[symbol_int] = strdup("int");
    type_name[symbol_long] = strdup("long");
    type_name[symbol_short] = strdup("short");
    type_name[symbol_signed] = strdup("signed");
    type_name[symbol_unsigned] = strdup("unsigned");
    type_name[symbol_void] = strdup("void");
    type_name[symbol_function] = strdup("function");
    type_name[symbol_point] = strdup("point");

    kind_name[constant] = strdup("point");
    kind_name[variable] = strdup("variable");
    kind_name[type] = strdup("type");
    kind_name[function] = strdup("function");

    for(int i = 1;i < nametab_count;i++){
        
        // Build comma-separated type list
        char typestr[256] = "";
        for(int j = 0; j < nametab[i].type_num; j++){
            strcat(typestr, type_name[nametab[i].type[j]]);
            if(j + 1 < nametab[i].type_num) strcat(typestr, ",");
        }

                // Print aligned columns
        printf("%-4d %-15s %-20s %-12s %-10s %-6s %-6d %-6d %-6d %-6d ",
               i,
               nametab[i].name,
               typestr,
               type_name[nametab[i].basic_type],
               kind_name[nametab[i].kind],
               nametab[i].normal ? "true" : "false",
               nametab[i].ref,
               nametab[i].size,
               nametab[i].adr,
               nametab[i].link);
        // Print the value column based on basic_type
        switch(nametab[i].basic_type){
            case symbol_bool:
                printf("%s", nametab[i].b_val ? "true" : "false");
                break;
            case symbol_char:
                printf("%c", nametab[i].c_val);
                break;
            case symbol_double:
                printf("%lf", nametab[i].d_val);
                break;
            case symbol_float:
                printf("%f", nametab[i].f_val);
                break;
            case symbol_int:
                printf("%d", nametab[i].i_val);
                break;
            case symbol_long:
                printf("%ld", nametab[i].l_val);
                break;
            case symbol_short:
                printf("%hd", nametab[i].s_val);
                break;
            case symbol_point:
                printf("%p (lvl %d)", nametab[i].p_val, nametab[i].ptr_level);
                break;
            default:
                break;
            }


        printf("\n");
    }   
}

void Display_Btab(){
    printf("the following is block table (btab):\n");
    printf("%-4s %-15s %-20s %-12s %-10s %-10s %-10s %-10s\n",
           "Idx", "Name", "Types", "BasicType", "LastPar", "Last", "PSize", "VSize");
    printf("---- --------------- -------------------- ------------ ---------- ---------- ---------- ----------\n");

    char* type_name[64];
    type_name[symbol_bool] = "bool";
    type_name[symbol_char] = "char";
    type_name[symbol_const] = "const";
    type_name[symbol_static] = "static";
    type_name[symbol_double] = "double";
    type_name[symbol_float] = "float";
    type_name[symbol_int] = "int";
    type_name[symbol_long] = "long";
    type_name[symbol_short] = "short";
    type_name[symbol_signed] = "signed";
    type_name[symbol_unsigned] = "unsigned";
    type_name[symbol_void] = "void";
    type_name[symbol_function] = "function";
    type_name[symbol_point] = "point";


    for (int i = 1; i < btab_count; i++) {

        char typestr[128] = "";
        for (int j = 0; j < btab[i].type_num; j++) {
            strcat(typestr, type_name[btab[i].type[j]]);
            if (j + 1 < btab[i].type_num) strcat(typestr, ",");
        }
        printf("%-4d %-15s %-20s %-12s %-10u %-10u %-10u %-10u\n",
               i,
               btab[i].name ? btab[i].name : "(null)",
               typestr,
               type_name[btab[i].basic_type],
               btab[i].lastpar,
               btab[i].last,
               btab[i].psize,
               btab[i].vsize);
    }
}

void Clear_current_type(){
    current_type_num = 0;
    bitsmask &= 0x0000;
    current_basic_type = symbol_int;
}

void Clear_After_Declaration(){
    last_index = 0;                             //the function or gobal var declaration is finished, set last_index = 0.
    
    par_point = 8;                              //reset 参数偏移
    loc_point = 0;                              //reset 局部变量 或者 全局变量

    par_index = 0;
}

void pushStack(int ele){
    stack[sp++] = ele;
}

int popStack(){
    return stack[--sp];
}




#line 527 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_float_number = 3,               /* float_number  */
  YYSYMBOL_int_number = 4,                 /* int_number  */
  YYSYMBOL_identifier = 5,                 /* identifier  */
  YYSYMBOL_one_char = 6,                   /* one_char  */
  YYSYMBOL_boolsym = 7,                    /* boolsym  */
  YYSYMBOL_charsym = 8,                    /* charsym  */
  YYSYMBOL_constsym = 9,                   /* constsym  */
  YYSYMBOL_staticsym = 10,                 /* staticsym  */
  YYSYMBOL_doublesym = 11,                 /* doublesym  */
  YYSYMBOL_floatsym = 12,                  /* floatsym  */
  YYSYMBOL_intsym = 13,                    /* intsym  */
  YYSYMBOL_longsym = 14,                   /* longsym  */
  YYSYMBOL_shortsym = 15,                  /* shortsym  */
  YYSYMBOL_signedsym = 16,                 /* signedsym  */
  YYSYMBOL_unsignedsym = 17,               /* unsignedsym  */
  YYSYMBOL_voidsym = 18,                   /* voidsym  */
  YYSYMBOL_falsesym = 19,                  /* falsesym  */
  YYSYMBOL_truesym = 20,                   /* truesym  */
  YYSYMBOL_whilesym = 21,                  /* whilesym  */
  YYSYMBOL_dosym = 22,                     /* dosym  */
  YYSYMBOL_ifsym = 23,                     /* ifsym  */
  YYSYMBOL_elsesym = 24,                   /* elsesym  */
  YYSYMBOL_ifelsesym = 25,                 /* ifelsesym  */
  YYSYMBOL_switchsym = 26,                 /* switchsym  */
  YYSYMBOL_casesym = 27,                   /* casesym  */
  YYSYMBOL_defaultsym = 28,                /* defaultsym  */
  YYSYMBOL_forsym = 29,                    /* forsym  */
  YYSYMBOL_gotosym = 30,                   /* gotosym  */
  YYSYMBOL_trysym = 31,                    /* trysym  */
  YYSYMBOL_catchsym = 32,                  /* catchsym  */
  YYSYMBOL_continuesym = 33,               /* continuesym  */
  YYSYMBOL_breaksym = 34,                  /* breaksym  */
  YYSYMBOL_andsym = 35,                    /* andsym  */
  YYSYMBOL_orsym = 36,                     /* orsym  */
  YYSYMBOL_newsym = 37,                    /* newsym  */
  YYSYMBOL_deletesym = 38,                 /* deletesym  */
  YYSYMBOL_enumsym = 39,                   /* enumsym  */
  YYSYMBOL_structsym = 40,                 /* structsym  */
  YYSYMBOL_returnsym = 41,                 /* returnsym  */
  YYSYMBOL_sizeofsym = 42,                 /* sizeofsym  */
  YYSYMBOL_typedefsym = 43,                /* typedefsym  */
  YYSYMBOL_inlinesym = 44,                 /* inlinesym  */
  YYSYMBOL_throwsym = 45,                  /* throwsym  */
  YYSYMBOL_comma = 46,                     /* comma  */
  YYSYMBOL_left_bracket = 47,              /* left_bracket  */
  YYSYMBOL_right_bracket = 48,             /* right_bracket  */
  YYSYMBOL_question = 49,                  /* question  */
  YYSYMBOL_colon = 50,                     /* colon  */
  YYSYMBOL_equal = 51,                     /* equal  */
  YYSYMBOL_muti_equal = 52,                /* muti_equal  */
  YYSYMBOL_divi_equal = 53,                /* divi_equal  */
  YYSYMBOL_mod_equal = 54,                 /* mod_equal  */
  YYSYMBOL_plus_equal = 55,                /* plus_equal  */
  YYSYMBOL_minus_equal = 56,               /* minus_equal  */
  YYSYMBOL_rshift_equal = 57,              /* rshift_equal  */
  YYSYMBOL_lshift_equal = 58,              /* lshift_equal  */
  YYSYMBOL_and_equal = 59,                 /* and_equal  */
  YYSYMBOL_xor_equal = 60,                 /* xor_equal  */
  YYSYMBOL_or_equal = 61,                  /* or_equal  */
  YYSYMBOL_logi_or = 62,                   /* logi_or  */
  YYSYMBOL_logi_and = 63,                  /* logi_and  */
  YYSYMBOL_inclu_or = 64,                  /* inclu_or  */
  YYSYMBOL_exclu_or = 65,                  /* exclu_or  */
  YYSYMBOL_solo_and = 66,                  /* solo_and  */
  YYSYMBOL_double_equal = 67,              /* double_equal  */
  YYSYMBOL_unequal = 68,                   /* unequal  */
  YYSYMBOL_logi_not = 69,                  /* logi_not  */
  YYSYMBOL_bit_not = 70,                   /* bit_not  */
  YYSYMBOL_less = 71,                      /* less  */
  YYSYMBOL_greater = 72,                   /* greater  */
  YYSYMBOL_less_and_equal = 73,            /* less_and_equal  */
  YYSYMBOL_greater_and_equal = 74,         /* greater_and_equal  */
  YYSYMBOL_lshift = 75,                    /* lshift  */
  YYSYMBOL_rshift = 76,                    /* rshift  */
  YYSYMBOL_plus = 77,                      /* plus  */
  YYSYMBOL_minus = 78,                     /* minus  */
  YYSYMBOL_star = 79,                      /* star  */
  YYSYMBOL_slash = 80,                     /* slash  */
  YYSYMBOL_mod = 81,                       /* mod  */
  YYSYMBOL_left_paren = 82,                /* left_paren  */
  YYSYMBOL_right_paren = 83,               /* right_paren  */
  YYSYMBOL_semicolon = 84,                 /* semicolon  */
  YYSYMBOL_hash = 85,                      /* hash  */
  YYSYMBOL_left_brace = 86,                /* left_brace  */
  YYSYMBOL_right_brace = 87,               /* right_brace  */
  YYSYMBOL_dot_star = 88,                  /* dot_star  */
  YYSYMBOL_arrow_star = 89,                /* arrow_star  */
  YYSYMBOL_double_add = 90,                /* double_add  */
  YYSYMBOL_double_minus = 91,              /* double_minus  */
  YYSYMBOL_dot = 92,                       /* dot  */
  YYSYMBOL_three_dots = 93,                /* three_dots  */
  YYSYMBOL_arrow = 94,                     /* arrow  */
  YYSYMBOL_single_quote = 95,              /* single_quote  */
  YYSYMBOL_nullptr = 96,                   /* nullptr  */
  YYSYMBOL_YYACCEPT = 97,                  /* $accept  */
  YYSYMBOL_98_translation_unit = 98,       /* translation-unit  */
  YYSYMBOL_99_declaration_seq = 99,        /* declaration-seq  */
  YYSYMBOL_declaration = 100,              /* declaration  */
  YYSYMBOL_101_block_declaration = 101,    /* block-declaration  */
  YYSYMBOL_102_simple_declaration = 102,   /* simple-declaration  */
  YYSYMBOL_103_decl_specifier_seq = 103,   /* decl-specifier-seq  */
  YYSYMBOL_104_decl_specifier = 104,       /* decl-specifier  */
  YYSYMBOL_105_storage_class_specifier = 105, /* storage-class-specifier  */
  YYSYMBOL_106_type_specifier = 106,       /* type-specifier  */
  YYSYMBOL_107_trailing_type_specifier = 107, /* trailing-type-specifier  */
  YYSYMBOL_108_simple_type_specifier = 108, /* simple-type-specifier  */
  YYSYMBOL_109_cv_qualifier = 109,         /* cv-qualifier  */
  YYSYMBOL_110_class_specifier = 110,      /* class-specifier  */
  YYSYMBOL_111_enum_specifier = 111,       /* enum-specifier  */
  YYSYMBOL_112_function_specifier = 112,   /* function-specifier  */
  YYSYMBOL_113_init_declarator_list = 113, /* init-declarator-list  */
  YYSYMBOL_114_init_declarator = 114,      /* init-declarator  */
  YYSYMBOL_declarator = 115,               /* declarator  */
  YYSYMBOL_116_ptr_declarator = 116,       /* ptr-declarator  */
  YYSYMBOL_117_ptr_operator = 117,         /* ptr-operator  */
  YYSYMBOL_118_noptr_declarator = 118,     /* noptr-declarator  */
  YYSYMBOL_119_declarator_id = 119,        /* declarator-id  */
  YYSYMBOL_120_parameters_and_qualifiers = 120, /* parameters-and-qualifiers  */
  YYSYMBOL_121_parameter_declaration_clause = 121, /* parameter-declaration-clause  */
  YYSYMBOL_122_parameter_declaration_list = 122, /* parameter-declaration-list  */
  YYSYMBOL_123_parameter_declaration = 123, /* parameter-declaration  */
  YYSYMBOL_initializer = 124,              /* initializer  */
  YYSYMBOL_125_brace_or_equal_initializer = 125, /* brace-or-equal-initializer  */
  YYSYMBOL_126_initializer_clause = 126,   /* initializer-clause  */
  YYSYMBOL_127_constant_expression = 127,  /* constant-expression  */
  YYSYMBOL_expression = 128,               /* expression  */
  YYSYMBOL_129_assignment_expression = 129, /* assignment-expression  */
  YYSYMBOL_130_conditional_expression = 130, /* conditional-expression  */
  YYSYMBOL_131_logical_or_expression = 131, /* logical-or-expression  */
  YYSYMBOL_132_logical_and_expression = 132, /* logical-and-expression  */
  YYSYMBOL_133_inclusive_or_expression = 133, /* inclusive-or-expression  */
  YYSYMBOL_134_exclusive_or_expression = 134, /* exclusive-or-expression  */
  YYSYMBOL_135_and_expression = 135,       /* and-expression  */
  YYSYMBOL_136_equality_expression = 136,  /* equality-expression  */
  YYSYMBOL_137_relational_expression = 137, /* relational-expression  */
  YYSYMBOL_138_shift_expression = 138,     /* shift-expression  */
  YYSYMBOL_139_additive_expression = 139,  /* additive-expression  */
  YYSYMBOL_140_multiplicative_expression = 140, /* multiplicative-expression  */
  YYSYMBOL_141_pm_expression = 141,        /* pm-expression  */
  YYSYMBOL_142_cast_expression = 142,      /* cast-expression  */
  YYSYMBOL_143_unary_expression = 143,     /* unary-expression  */
  YYSYMBOL_144_postfix_expression = 144,   /* postfix-expression  */
  YYSYMBOL_145_primary_expression = 145,   /* primary-expression  */
  YYSYMBOL_literal = 146,                  /* literal  */
  YYSYMBOL_147_integer_literal = 147,      /* integer-literal  */
  YYSYMBOL_148_character_literal = 148,    /* character-literal  */
  YYSYMBOL_149_floating_literal = 149,     /* floating-literal  */
  YYSYMBOL_150_string_literal = 150,       /* string-literal  */
  YYSYMBOL_151_boolean_literal = 151,      /* boolean-literal  */
  YYSYMBOL_152_pointer_literal = 152,      /* pointer-literal  */
  YYSYMBOL_153_id_expression = 153,        /* id-expression  */
  YYSYMBOL_154_unqualified_id = 154,       /* unqualified-id  */
  YYSYMBOL_155_qualified_id = 155,         /* qualified-id  */
  YYSYMBOL_156_unary_operator = 156,       /* unary-operator  */
  YYSYMBOL_157_new_expression = 157,       /* new-expression  */
  YYSYMBOL_158_delete_expression = 158,    /* delete-expression  */
  YYSYMBOL_159_type_id = 159,              /* type-id  */
  YYSYMBOL_160_type_specifier_seq = 160,   /* type-specifier-seq  */
  YYSYMBOL_161_assignment_operator = 161,  /* assignment-operator  */
  YYSYMBOL_162_throw_expression = 162,     /* throw-expression  */
  YYSYMBOL_163_braced_init_list = 163,     /* braced-init-list  */
  YYSYMBOL_164_expression_list = 164,      /* expression-list  */
  YYSYMBOL_165_initializer_list = 165,     /* initializer-list  */
  YYSYMBOL_166_function_definition = 166,  /* function-definition  */
  YYSYMBOL_167_function_body = 167,        /* function-body  */
  YYSYMBOL_168_compound_statement = 168,   /* compound-statement  */
  YYSYMBOL_169_statement_seq = 169,        /* statement-seq  */
  YYSYMBOL_statement = 170,                /* statement  */
  YYSYMBOL_171_labeled_statement = 171,    /* labeled-statement  */
  YYSYMBOL_172_expression_statement = 172, /* expression-statement  */
  YYSYMBOL_173_selection_statement = 173,  /* selection-statement  */
  YYSYMBOL_condition = 174,                /* condition  */
  YYSYMBOL_175_iteration_statement = 175,  /* iteration-statement  */
  YYSYMBOL_176_for_init_statement = 176,   /* for-init-statement  */
  YYSYMBOL_177_jump_statement = 177,       /* jump-statement  */
  YYSYMBOL_178_declaration_statement = 178, /* declaration-statement  */
  YYSYMBOL_179_try_block = 179,            /* try-block  */
  YYSYMBOL_180_handler_seq = 180,          /* handler-seq  */
  YYSYMBOL_handler = 181,                  /* handler  */
  YYSYMBOL_182_empty_declaration = 182     /* empty-declaration  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1601

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  86
/* YYNRULES -- Number of rules.  */
#define YYNRULES  222
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  335

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   351


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   547,   547,   548,   552,   553,   557,   562,   566,   570,
     576,   577,   581,   582,   588,   597,   601,   602,   603,   604,
     607,   612,   613,   614,   619,   620,   624,   625,   626,   627,
     628,   629,   630,   631,   632,   633,   638,   642,   645,   650,
     662,   663,   667,   750,   760,   772,   781,   790,   794,   800,
     811,   812,   816,   825,   829,   830,   831,   832,   833,   837,
     838,   843,   852,   950,   962,   966,   978,   982,   994,   999,
    1003,  1015,  1019,  1031,  1032,  1036,  1049,  1055,  1067,  1071,
    1083,  1087,  1099,  1103,  1115,  1119,  1131,  1135,  1147,  1148,
    1152,  1164,  1165,  1166,  1167,  1171,  1183,  1184,  1188,  1200,
    1422,  1635,  1647,  1754,  1961,  1965,  1977,  1978,  1982,  1994,
    1998,  2010,  2011,  2012,  2013,  2014,  2015,  2016,  2020,  2032,
    2033,  2034,  2035,  2036,  2037,  2038,  2039,  2040,  2044,  2056,
    2068,  2075,  2080,  2085,  2090,  2094,  2099,  2107,  2115,  2123,
    2131,  2135,  2140,  2148,  2156,  2162,  2166,  2172,  2182,  2186,
    2187,  2188,  2189,  2190,  2191,  2194,  2197,  2202,  2206,  2207,
    2213,  2214,  2215,  2216,  2217,  2218,  2219,  2220,  2221,  2222,
    2223,  2227,  2228,  2231,  2235,  2239,  2240,  2245,  2256,  2260,
    2261,  2265,  2266,  2270,  2271,  2272,  2273,  2274,  2275,  2276,
    2277,  2282,  2283,  2284,  2289,  2290,  2294,  2295,  2296,  2300,
    2301,  2302,  2307,  2308,  2309,  2310,  2311,  2312,  2313,  2317,
    2318,  2325,  2326,  2327,  2328,  2329,  2330,  2334,  2338,  2342,
    2343,  2346,  2351
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "float_number",
  "int_number", "identifier", "one_char", "boolsym", "charsym", "constsym",
  "staticsym", "doublesym", "floatsym", "intsym", "longsym", "shortsym",
  "signedsym", "unsignedsym", "voidsym", "falsesym", "truesym", "whilesym",
  "dosym", "ifsym", "elsesym", "ifelsesym", "switchsym", "casesym",
  "defaultsym", "forsym", "gotosym", "trysym", "catchsym", "continuesym",
  "breaksym", "andsym", "orsym", "newsym", "deletesym", "enumsym",
  "structsym", "returnsym", "sizeofsym", "typedefsym", "inlinesym",
  "throwsym", "comma", "left_bracket", "right_bracket", "question",
  "colon", "equal", "muti_equal", "divi_equal", "mod_equal", "plus_equal",
  "minus_equal", "rshift_equal", "lshift_equal", "and_equal", "xor_equal",
  "or_equal", "logi_or", "logi_and", "inclu_or", "exclu_or", "solo_and",
  "double_equal", "unequal", "logi_not", "bit_not", "less", "greater",
  "less_and_equal", "greater_and_equal", "lshift", "rshift", "plus",
  "minus", "star", "slash", "mod", "left_paren", "right_paren",
  "semicolon", "hash", "left_brace", "right_brace", "dot_star",
  "arrow_star", "double_add", "double_minus", "dot", "three_dots", "arrow",
  "single_quote", "nullptr", "$accept", "translation-unit",
  "declaration-seq", "declaration", "block-declaration",
  "simple-declaration", "decl-specifier-seq", "decl-specifier",
  "storage-class-specifier", "type-specifier", "trailing-type-specifier",
  "simple-type-specifier", "cv-qualifier", "class-specifier",
  "enum-specifier", "function-specifier", "init-declarator-list",
  "init-declarator", "declarator", "ptr-declarator", "ptr-operator",
  "noptr-declarator", "declarator-id", "parameters-and-qualifiers",
  "parameter-declaration-clause", "parameter-declaration-list",
  "parameter-declaration", "initializer", "brace-or-equal-initializer",
  "initializer-clause", "constant-expression", "expression",
  "assignment-expression", "conditional-expression",
  "logical-or-expression", "logical-and-expression",
  "inclusive-or-expression", "exclusive-or-expression", "and-expression",
  "equality-expression", "relational-expression", "shift-expression",
  "additive-expression", "multiplicative-expression", "pm-expression",
  "cast-expression", "unary-expression", "postfix-expression",
  "primary-expression", "literal", "integer-literal", "character-literal",
  "floating-literal", "string-literal", "boolean-literal",
  "pointer-literal", "id-expression", "unqualified-id", "qualified-id",
  "unary-operator", "new-expression", "delete-expression", "type-id",
  "type-specifier-seq", "assignment-operator", "throw-expression",
  "braced-init-list", "expression-list", "initializer-list",
  "function-definition", "function-body", "compound-statement",
  "statement-seq", "statement", "labeled-statement",
  "expression-statement", "selection-statement", "condition",
  "iteration-statement", "for-init-statement", "jump-statement",
  "declaration-statement", "try-block", "handler-seq", "handler",
  "empty-declaration", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-180)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-209)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     946,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,    23,  -180,     9,
    1083,  -180,  -180,  -180,    16,   406,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,   -27,  -180,   -10,  -180,    23,   -16,
     -33,  -180,  -180,  -180,  -180,  -180,   -57,  -180,  -180,  -180,
     -13,     8,  -180,    23,  -180,  1379,  1379,  -180,  -180,  -180,
    -180,  1473,   778,  -180,  -180,  -180,   455,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  1505,  1379,  -180,  -180,  -180,  -180,
    -180,  -180,   925,  1473,  1473,    49,  -180,   -24,  -180,  -180,
    -180,   456,    11,    -1,    22,    25,    90,    66,    84,    91,
      62,   102,  -180,  -180,    32,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  1473,  -180,  -180,  -180,  -180,  -180,
      14,    21,    56,  -180,    15,  -180,    23,    36,   -40,  -180,
      71,    33,   643,    43,    46,  1473,    80,    54,   150,    75,
      81,    88,  1062,    29,   968,  -180,  -180,  -180,    16,   -24,
      -6,  -180,   129,  -180,   549,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,   925,  -180,  -180,   590,   -31,   100,  -180,
    -180,  -180,    92,  1105,  1379,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  1473,  1379,  1473,  1473,
    1473,  1473,  1473,  1473,  1473,  1473,  1473,  1473,  1473,  1473,
    1473,  1473,  1473,  1473,  1473,  1473,  1473,  1379,  1199,  -180,
    -180,   187,   187,  -180,  -180,  1379,  -180,   134,  -180,   876,
    -180,   643,   737,   173,   737,   737,   147,   643,   361,   118,
    -180,  -180,  -180,  -180,     2,   119,  1379,  -180,  -180,  -180,
     124,  -180,  -180,  1473,  -180,  -180,   127,    10,    11,  -180,
      -1,    22,    25,    90,    66,    66,    84,    84,    84,    84,
      91,    91,    62,    62,   102,   102,   102,  -180,  -180,    70,
    -180,   131,  -180,  -180,  -180,  1379,  -180,  -180,  -180,    23,
     170,   135,   138,   140,   151,   643,  -180,  -180,  -180,   831,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  1379,
    -180,  -180,  -180,   166,   643,  1379,   643,   643,  -180,  1242,
     146,  -180,  -180,  1379,  -180,  -180,   -22,   211,  -180,   643,
      -2,  1336,  -180,   152,   643,  -180,   643,   643,     5,  -180,
    -180,  -180,  -180,   643,  -180
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      20,   146,   147,    27,    26,    36,    34,    33,    29,    30,
      28,    31,    32,    35,    19,    39,    47,   148,    13,     0,
      20,     4,     6,     9,   148,    14,    16,    17,    21,    24,
      25,    22,    23,    18,     0,    40,    43,    44,   148,    45,
      48,    52,   144,   145,     7,     8,     0,     1,     5,    10,
       0,    43,    15,   148,    12,   148,   148,    42,    63,    66,
      46,   148,    20,    49,    51,    11,   148,   177,   178,    41,
     139,   137,   142,   141,   148,   148,   150,   153,   154,   151,
     152,   149,   148,   148,   148,     0,   143,     0,    65,    67,
      72,    75,    77,    79,    81,    83,    85,    87,    90,    95,
      98,   101,   105,   108,   110,   118,   128,   131,   132,   133,
     134,   135,   136,   130,   148,   116,   117,    74,    68,   175,
       0,   174,     0,    69,    75,    55,   148,     0,    54,    59,
     146,     0,   148,     0,     0,   148,     0,     0,     0,     0,
       0,     0,   148,   149,   148,    13,   179,   217,   148,    24,
       0,    70,   130,   185,   148,   181,   183,   184,   186,   187,
     188,   189,   190,   148,   114,   172,    37,     0,     0,   157,
     111,   112,     0,   148,   148,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   126,
     127,   148,   148,   113,    64,   148,    50,    61,    53,    20,
      56,   148,   148,     0,   148,   148,     0,   148,   148,     0,
     221,   212,   211,   213,     0,     0,   148,   195,   180,   182,
       0,   159,   129,   148,   138,   122,     0,     0,    78,    73,
      80,    82,    84,    86,    88,    89,    91,    92,    93,    94,
      96,    97,    99,   100,   102,   103,   104,   106,   107,     0,
     120,     0,   124,   125,   176,   148,    58,    60,   191,   148,
     199,     0,     0,     0,     0,   148,   193,   210,   209,   148,
     216,   218,   219,   214,   215,    71,   115,   109,   123,   148,
     119,   121,    62,   173,   148,   148,   148,   148,   192,   148,
       0,   220,    76,   148,   201,   202,     0,   196,   198,   148,
       0,   148,   200,     0,   148,   204,   148,   148,     0,   203,
     197,   206,   205,   148,   207
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -180,  -180,  -180,   218,    65,    12,     7,  -180,  -180,   -74,
    -180,     0,  -180,  -180,  -180,  -180,   -21,   186,   -20,   -15,
    -180,  -180,  -180,  -180,  -180,  -180,    24,  -180,  -180,   -42,
     109,   -43,   -38,   -51,   -18,    59,    60,    58,    63,    61,
       3,   -44,     1,     4,   -56,   -72,   175,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,    30,  -180,  -180,  -180,
    -180,  -180,    87,    89,  -180,  -180,   -35,  -135,  -180,  -180,
    -180,   -46,  -180,  -118,  -180,    26,  -180,  -179,  -180,  -180,
    -180,  -180,  -180,   -36,  -180,  -180
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,   147,    23,   148,    25,    26,    27,
      28,    87,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    63,   127,   128,   129,    57,    58,   119,
     122,   150,   151,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    42,    43,   114,
     115,   116,   168,   169,   187,   117,   118,   120,   121,    44,
      67,   153,   154,   155,   156,   157,   158,   281,   159,   289,
     160,   161,   162,   291,   292,    45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,    59,    46,    50,    51,    68,   219,    24,   166,    47,
     123,   170,   171,    88,   223,   236,    59,    89,    89,    53,
      29,     1,     2,    60,   236,    29,    64,    24,     1,     2,
      41,    61,    52,    53,   -47,   -47,   239,   165,   246,   167,
     236,    55,   213,   124,   236,   283,   284,    41,   236,    62,
      41,   236,   242,   220,    41,   172,   236,    54,   173,    55,
     299,   323,    29,   189,   174,    22,   149,   215,    41,   126,
     166,    65,    56,   271,   188,   -47,   -47,   186,   237,   207,
     -47,   326,   149,    41,   123,    22,   293,   190,   333,   166,
      56,   191,   166,   230,    66,    16,   152,   214,    17,   234,
      49,   167,    16,   278,   216,    17,   217,   235,   -47,   286,
     310,   -47,   -47,   -47,   208,   222,   236,   124,   300,   218,
     167,   221,   209,   210,   211,   224,   212,    50,   225,    46,
     227,   247,   149,   267,   268,    89,   228,   194,   195,   196,
     197,   202,   203,   204,   149,   249,   264,   265,   266,    89,
     256,   257,   258,   259,   149,   229,    41,   192,   193,   198,
     199,    66,   152,   149,   269,   231,    29,   308,   200,   201,
      89,   297,   232,   274,   152,   -52,   -52,    89,    41,   280,
     -52,   280,   280,   243,   152,   275,   315,   244,   317,   318,
     205,   206,     1,     2,   282,   254,   255,   285,   295,   260,
     261,   325,   290,   294,   262,   263,   330,   296,   331,   332,
     298,   -52,   -52,   -52,   301,   334,   236,   313,   304,    29,
     305,   149,   149,   306,   149,   149,   126,   149,   149,   279,
     321,   279,   279,   302,   307,   324,   329,    89,    48,    69,
     287,   272,   273,   277,   226,   248,   280,   251,   250,   164,
     240,   152,   253,   252,   288,   241,   311,   152,   152,   303,
       0,   312,   316,     0,     0,     0,   320,     0,   314,     0,
       0,   322,     0,     0,     0,    89,     0,     0,   328,     0,
       0,     0,     0,     0,     0,   149,     0,     0,     0,   149,
       0,     0,     0,     0,     0,     0,   279,     0,     0,     0,
       0,     0,     0,     0,   149,     0,   149,   149,     0,    41,
       0,     0,     0,     0,     0,   152,     0,     0,     0,   149,
       0,     0,     0,     0,   149,     0,   149,   149,     0,     0,
       0,     0,     0,   149,   152,     0,   152,   152,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   152,
       0,     0,     0,     0,   152,     0,   152,   152,     0,     0,
       0,     0,     0,   152,    70,    71,     1,     2,     3,     4,
       5,     0,     6,     7,     8,     9,    10,    11,    12,    13,
      72,    73,  -208,  -208,  -208,  -208,     0,  -208,  -208,  -208,
    -208,  -208,  -208,     0,  -208,  -208,     0,     0,     0,     0,
       0,     0,  -208,    74,    14,    15,    75,   -20,   -20,     0,
       0,     0,   -20,     3,     4,     5,     0,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,    76,     0,     0,
      77,    78,     0,     0,     0,     0,     0,     0,    79,    80,
     143,     0,     0,   144,     0,   145,     0,  -208,  -208,    14,
      15,    83,    84,     0,     0,     0,    85,    86,    70,    71,
     130,     2,     3,     4,     5,     0,     6,     7,     8,     9,
      10,    11,    12,    13,    72,    73,   131,   132,   133,     0,
       0,   134,   135,   136,   137,   138,   139,     0,   140,   141,
       0,     0,     0,     0,     0,     0,   142,    74,    14,    15,
      75,   -20,   -20,     0,     0,   174,   -20,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,     0,
       0,    76,     0,     0,    77,    78,     0,     0,     0,     0,
       0,     0,    79,    80,   143,     0,     0,   144,     0,   145,
       0,    66,   146,     0,     0,    83,    84,     0,     0,     0,
      85,    86,    70,    71,   130,     2,     3,     4,     5,     0,
       6,     7,     8,     9,    10,    11,    12,    13,    72,    73,
     131,   132,   133,     0,     0,   134,   135,   136,   137,   138,
     139,     0,   140,   141,     0,     0,     0,     0,     0,     0,
     142,    74,    14,    15,    75,   -20,   -20,     3,     4,     5,
     -20,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,     0,     0,     0,    76,     0,     0,    77,    78,
       0,     0,     0,     0,     0,     0,    79,    80,   143,     0,
       0,   144,     0,   145,     0,    66,   238,     0,     0,    83,
      84,     0,     0,     0,    85,    86,    70,    71,   130,     2,
       3,     4,     5,     0,     6,     7,     8,     9,    10,    11,
      12,    13,    72,    73,   131,   132,   133,     0,     0,   134,
     135,   136,   137,   138,   139,     0,   140,   141,     0,     0,
       0,     0,     0,     0,   142,    74,    14,    15,    75,   -20,
     -20,     0,     0,     0,   -20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
       0,     0,    77,    78,     0,     0,     0,     0,     0,     0,
      79,    80,   143,     0,     0,   144,     0,   145,     0,    66,
       0,     0,     0,    83,    84,     0,     0,     0,    85,    86,
      70,    71,     1,     2,     3,     4,     5,     0,     6,     7,
       8,     9,    10,    11,    12,    13,    72,    73,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    74,
      14,    15,    75,     0,   -20,     3,     4,     5,   -20,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,     0,     0,    76,     0,     0,    77,    78,     0,     0,
       0,     0,     0,     0,    79,    80,    81,     0,     0,    82,
     -20,    14,    15,     0,     0,     0,     0,    83,    84,     0,
       0,     0,    85,    86,    70,    71,     1,     2,     3,     4,
       5,     0,     6,     7,     8,     9,    10,    11,    12,    13,
      72,    73,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   125,     0,    74,    14,    15,    75,     0,   -20,     0,
       0,     0,   -20,     3,     4,     5,     0,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,    76,     0,     0,
      77,    78,     0,     0,     0,     0,     0,     0,    79,    80,
      81,     0,     0,    82,     0,   309,     0,     0,     0,    14,
      15,    83,    84,     0,     0,     0,    85,    86,    70,    71,
       1,     2,     3,     4,     5,     0,     6,     7,     8,     9,
      10,    11,    12,    13,    72,    73,    -3,     0,     0,     0,
       0,     1,     2,     3,     4,     5,     0,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,    74,     0,   276,
      75,    70,    71,     1,     2,     3,     4,     5,     0,     6,
       7,     8,     9,    10,    11,    12,    13,    72,    73,    14,
      15,    76,     0,     0,    77,    78,     0,     0,     0,     0,
       0,     0,    79,    80,    81,     0,     0,    82,   -37,     0,
      74,     0,     0,    75,     0,    83,    84,     0,     0,     0,
      85,    86,     0,     0,     0,    16,     0,     0,    17,     0,
      18,     0,     0,     0,    76,     0,     0,    77,    78,     0,
       0,     0,     0,     0,     0,    79,    80,   143,     0,     0,
     144,   -37,     0,     0,     0,     0,     0,     0,    83,    84,
       0,     0,     0,    85,    86,    70,    71,     1,     2,     3,
       4,     0,     0,     6,     7,     8,     9,    10,    11,    12,
      13,    72,    73,    -2,     0,     0,     0,     0,     1,     2,
       3,     4,     5,     0,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,    74,     0,     0,    75,    70,    71,
       1,     2,     3,     4,     0,     0,     6,     7,     8,     9,
      10,    11,    12,    13,    72,    73,    14,    15,    76,     0,
       0,    77,    78,     0,     0,     0,     0,     0,     0,    79,
      80,    81,     0,     0,    82,     0,   233,    74,     0,     0,
      75,     0,    83,    84,     0,     0,     0,    85,    86,     0,
       0,     0,    16,     0,     0,    17,     0,    18,     0,     0,
       0,    76,     0,     0,    77,    78,     0,     0,     0,     0,
       0,     0,    79,    80,    81,     0,     0,    82,   245,     0,
       0,     0,     0,     0,     0,    83,    84,     0,     0,     0,
      85,    86,    70,    71,     1,     2,     3,     4,     0,     0,
       6,     7,     8,     9,    10,    11,    12,    13,    72,    73,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74,     0,     0,    75,    70,    71,     1,     2,     3,
       4,     0,     0,     6,     7,     8,     9,    10,    11,    12,
      13,    72,    73,     0,     0,    76,     0,     0,    77,    78,
       0,     0,     0,     0,     0,     0,    79,    80,    81,     0,
       0,    82,   270,     0,    74,     0,     0,    75,     0,    83,
      84,     0,     0,     0,    85,    86,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    76,     0,
       0,    77,    78,     0,     0,     0,     0,     0,     0,    79,
      80,    81,     0,     0,    82,   319,     0,     0,     0,     0,
       0,     0,    83,    84,     0,     0,     0,    85,    86,    70,
      71,     1,     2,     3,     4,     0,     0,     6,     7,     8,
       9,    10,    11,    12,    13,    72,    73,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    74,     0,
       0,    75,    70,    71,     1,     2,     3,     4,     0,     0,
       6,     7,     8,     9,    10,    11,    12,    13,    72,    73,
       0,     0,    76,     0,     0,    77,    78,     0,     0,     0,
       0,     0,     0,    79,    80,    81,     0,     0,    82,   327,
       0,    74,     0,     0,    75,     0,    83,    84,     0,     0,
       0,    85,    86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,     0,     0,    77,    78,
       0,     0,     0,     0,     0,     0,    79,    80,    81,     0,
       0,    82,     0,     0,     0,     0,     0,     0,     0,    83,
      84,     0,     0,     0,    85,    86,    70,    71,     1,     2,
       3,     4,     0,     0,     6,     7,     8,     9,    10,    11,
      12,    13,    72,    73,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
       1,     2,     3,     4,     0,    74,     6,     7,     8,     9,
      10,    11,    12,    13,    72,    73,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
       0,     0,    77,    78,     0,     0,     0,    74,     0,     0,
      79,    80,    81,     0,     0,    82,     0,     0,     0,     0,
       0,     0,     0,    83,    84,     0,     0,     0,    85,    86,
       0,    76,     0,     0,    77,    78,     0,     0,     0,     0,
       0,     0,    79,    80,    81,     0,     0,   163,     0,     0,
       0,     0,     0,     0,     0,    83,    84,     0,     0,     0,
      85,    86
};

static const yytype_int16 yycheck[] =
{
       0,    36,    17,    24,    24,    51,    46,     0,    82,     0,
      61,    83,    84,    55,   132,    46,    51,    55,    56,    46,
      20,     5,     6,    38,    46,    25,    83,    20,     5,     6,
       0,    47,    25,    46,     5,     6,   154,    75,   173,    82,
      46,    51,   114,    61,    46,   224,   225,    17,    46,    82,
      20,    46,    83,    93,    24,     6,    46,    84,    82,    51,
      50,    83,    62,    64,    49,     0,    66,    46,    38,    62,
     144,    84,    82,   208,    63,    46,    47,    62,    84,    47,
      51,    83,    82,    53,   135,    20,    84,    65,    83,   163,
      82,    66,   166,   139,    86,    79,    66,    83,    82,   142,
      84,   144,    79,   221,    48,    82,   126,   142,    79,   227,
     289,    82,    83,    84,    82,    82,    46,   135,    48,    83,
     163,    50,    90,    91,    92,    82,    94,   148,    82,   144,
      50,   174,   132,   205,   206,   173,    82,    71,    72,    73,
      74,    79,    80,    81,   144,   187,   202,   203,   204,   187,
     194,   195,   196,   197,   154,     5,   126,    67,    68,    75,
      76,    86,   132,   163,   207,    84,   166,   285,    77,    78,
     208,   243,    84,   215,   144,    46,    47,   215,   148,   222,
      51,   224,   225,    83,   154,    51,   304,    95,   306,   307,
      88,    89,     5,     6,    21,   192,   193,    50,   236,   198,
     199,   319,    84,    84,   200,   201,   324,    83,   326,   327,
      83,    82,    83,    84,    83,   333,    46,    51,    83,   219,
      82,   221,   222,    83,   224,   225,   219,   227,   228,   222,
      84,   224,   225,   275,    83,    24,    84,   275,    20,    53,
     228,   211,   212,   219,   135,   186,   289,   189,   188,    74,
     163,   221,   191,   190,   228,   166,   292,   227,   228,   279,
      -1,   299,   305,    -1,    -1,    -1,   309,    -1,   303,    -1,
      -1,   313,    -1,    -1,    -1,   313,    -1,    -1,   321,    -1,
      -1,    -1,    -1,    -1,    -1,   285,    -1,    -1,    -1,   289,
      -1,    -1,    -1,    -1,    -1,    -1,   289,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   304,    -1,   306,   307,    -1,   279,
      -1,    -1,    -1,    -1,    -1,   285,    -1,    -1,    -1,   319,
      -1,    -1,    -1,    -1,   324,    -1,   326,   327,    -1,    -1,
      -1,    -1,    -1,   333,   304,    -1,   306,   307,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   319,
      -1,    -1,    -1,    -1,   324,    -1,   326,   327,    -1,    -1,
      -1,    -1,    -1,   333,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    51,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    66,    -1,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,
      79,    -1,    -1,    82,    -1,    84,    -1,    86,    87,    43,
      44,    90,    91,    -1,    -1,    -1,    95,    96,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    26,    27,    28,    29,    30,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    49,    51,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    79,    -1,    -1,    82,    -1,    84,
      -1,    86,    87,    -1,    -1,    90,    91,    -1,    -1,    -1,
      95,    96,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    26,    27,    28,    29,    30,
      31,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,     7,     8,     9,
      51,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,    -1,
      -1,    82,    -1,    84,    -1,    86,    87,    -1,    -1,    90,
      91,    -1,    -1,    -1,    95,    96,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    -1,    26,
      27,    28,    29,    30,    31,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    78,    79,    -1,    -1,    82,    -1,    84,    -1,    86,
      -1,    -1,    -1,    90,    91,    -1,    -1,    -1,    95,    96,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      43,    44,    45,    -1,    47,     7,     8,     9,    51,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    78,    79,    -1,    -1,    82,
      83,    43,    44,    -1,    -1,    -1,    -1,    90,    91,    -1,
      -1,    -1,    95,    96,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    93,    -1,    42,    43,    44,    45,    -1,    47,    -1,
      -1,    -1,    51,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    66,    -1,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,
      79,    -1,    -1,    82,    -1,    84,    -1,    -1,    -1,    43,
      44,    90,    91,    -1,    -1,    -1,    95,    96,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,     0,    -1,    -1,    -1,
      -1,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    42,    -1,    93,
      45,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    43,
      44,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    79,    -1,    -1,    82,    83,    -1,
      42,    -1,    -1,    45,    -1,    90,    91,    -1,    -1,    -1,
      95,    96,    -1,    -1,    -1,    79,    -1,    -1,    82,    -1,
      84,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    -1,    -1,
      82,    83,    -1,    -1,    -1,    -1,    -1,    -1,    90,    91,
      -1,    -1,    -1,    95,    96,     3,     4,     5,     6,     7,
       8,    -1,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,     0,    -1,    -1,    -1,    -1,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    -1,    42,    -1,    -1,    45,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    43,    44,    66,    -1,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    -1,    -1,    82,    -1,    84,    42,    -1,    -1,
      45,    -1,    90,    91,    -1,    -1,    -1,    95,    96,    -1,
      -1,    -1,    79,    -1,    -1,    82,    -1,    84,    -1,    -1,
      -1,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    79,    -1,    -1,    82,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    91,    -1,    -1,    -1,
      95,    96,     3,     4,     5,     6,     7,     8,    -1,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    -1,    -1,    45,     3,     4,     5,     6,     7,
       8,    -1,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    -1,    -1,    66,    -1,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,    -1,
      -1,    82,    83,    -1,    42,    -1,    -1,    45,    -1,    90,
      91,    -1,    -1,    -1,    95,    96,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    -1,    -1,    82,    83,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    91,    -1,    -1,    -1,    95,    96,     3,
       4,     5,     6,     7,     8,    -1,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      -1,    45,     3,     4,     5,     6,     7,     8,    -1,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      -1,    -1,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    78,    79,    -1,    -1,    82,    83,
      -1,    42,    -1,    -1,    45,    -1,    90,    91,    -1,    -1,
      -1,    95,    96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,    -1,
      -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,
      91,    -1,    -1,    -1,    95,    96,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,    -1,    42,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    69,    70,    -1,    -1,    -1,    42,    -1,    -1,
      77,    78,    79,    -1,    -1,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    91,    -1,    -1,    -1,    95,    96,
      -1,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    79,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    91,    -1,    -1,    -1,
      95,    96
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,     7,     8,     9,    11,    12,    13,    14,
      15,    16,    17,    18,    43,    44,    79,    82,    84,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   153,   154,   155,   166,   182,   116,     0,   100,    84,
     113,   115,   103,    46,    84,    51,    82,   124,   125,   163,
     116,    47,    82,   120,    83,    84,    86,   167,   168,   114,
       3,     4,    19,    20,    42,    45,    66,    69,    70,    77,
      78,    79,    82,    90,    91,    95,    96,   108,   126,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   156,   157,   158,   162,   163,   126,
     164,   165,   127,   130,   131,    93,   103,   121,   122,   123,
       5,    21,    22,    23,    26,    27,    28,    29,    30,    31,
      33,    34,    41,    79,    82,    84,    87,   101,   103,   108,
     128,   129,   153,   168,   169,   170,   171,   172,   173,   175,
     177,   178,   179,    82,   143,   129,   106,   128,   159,   160,
     142,   142,     6,    82,    49,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,   161,    63,    64,
      65,    66,    67,    68,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    88,    89,    47,    82,    90,
      91,    92,    94,   142,    83,    46,    48,   115,    83,    46,
      93,    50,    82,   170,    82,    82,   127,    50,    82,     5,
     168,    84,    84,    84,   128,   163,    46,    84,    87,   170,
     159,   160,    83,    83,    95,    83,   164,   128,   132,   126,
     133,   134,   135,   136,   137,   137,   138,   138,   138,   138,
     139,   139,   140,   140,   141,   141,   141,   142,   142,   128,
      83,   164,   153,   153,   126,    51,    93,   123,   170,   103,
     128,   174,    21,   174,   174,    50,   170,   102,   172,   176,
      84,   180,   181,    84,    84,   129,    83,   142,    83,    50,
      48,    83,   126,   115,    83,    82,    83,    83,   170,    84,
     174,   180,   129,    51,   163,   170,   128,   170,   170,    83,
     128,    84,   126,    83,    24,   170,    83,    83,   128,    84,
     170,   170,   170,    83,   170
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    98,    99,    99,   100,   100,   100,   101,
     102,   102,   102,   102,   103,   103,   104,   104,   104,   104,
     105,   106,   106,   106,   107,   107,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   109,   110,   111,   112,
     113,   113,   114,   114,   115,   116,   116,   117,   118,   118,
     118,   118,   119,   120,   121,   121,   121,   121,   121,   122,
     122,   123,   123,   124,   124,   125,   125,   126,   126,   127,
     128,   128,   129,   129,   129,   130,   130,   131,   131,   132,
     132,   133,   133,   134,   134,   135,   135,   136,   136,   136,
     137,   137,   137,   137,   137,   138,   138,   138,   139,   139,
     139,   140,   140,   140,   140,   141,   141,   141,   142,   142,
     143,   143,   143,   143,   143,   143,   143,   143,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   145,   145,
     145,   146,   146,   146,   146,   146,   146,   147,   148,   149,
     150,   151,   151,   152,   153,   153,   154,   154,   155,   156,
     156,   156,   156,   156,   156,   157,   158,   159,   160,   160,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   162,   162,   163,   164,   165,   165,   166,   167,   168,
     168,   169,   169,   170,   170,   170,   170,   170,   170,   170,
     170,   171,   171,   171,   172,   172,   173,   173,   173,   174,
     174,   174,   175,   175,   175,   175,   175,   175,   175,   176,
     176,   177,   177,   177,   177,   177,   177,   178,   179,   180,
     180,   181,   182
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       2,     3,     2,     1,     1,     2,     1,     1,     1,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     0,     1,
       1,     3,     2,     1,     1,     1,     2,     1,     1,     2,
       4,     3,     1,     3,     1,     1,     2,     0,     3,     1,
       3,     2,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     1,     5,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     1,     4,
       1,     2,     2,     2,     2,     4,     1,     1,     1,     4,
       3,     4,     3,     4,     3,     3,     2,     2,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       1,     1,     1,     1,     1,     0,     0,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     0,     1,     1,     3,     3,     1,     2,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     3,     1,     2,     5,     7,     5,     1,
       4,     3,     5,     7,     6,     7,     7,     8,     2,     1,
       1,     2,     2,     2,     3,     3,     3,     1,     3,     1,
       2,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 6: /* declaration: block-declaration  */
#line 558 "parser.y"
    {
        Clear_After_Declaration();
    }
#line 2239 "parser.c"
    break;

  case 7: /* declaration: function-definition  */
#line 563 "parser.y"
    {
        Clear_After_Declaration();
    }
#line 2247 "parser.c"
    break;

  case 11: /* simple-declaration: decl-specifier-seq init-declarator-list semicolon  */
#line 578 "parser.y"
    {
        Clear_current_type();                   //finish current type,need to be cleared.
    }
#line 2255 "parser.c"
    break;

  case 14: /* decl-specifier-seq: decl-specifier  */
#line 589 "parser.y"
    {
        for(int i = 0;i < current_type_num;i++){
            (yyval.decl_specifier_seq).type[i] = current_type[i];
        }
        (yyval.decl_specifier_seq).type_num = current_type_num;

        (yyval.decl_specifier_seq).basic_type = current_basic_type;
    }
#line 2268 "parser.c"
    break;

  case 26: /* simple-type-specifier: charsym  */
#line 624 "parser.y"
                        {if((bitsmask & BIT_CHAR) == (1 << 3)){printf("uncorrect:char char\n");exit(1);}             current_type[current_type_num++] = symbol_char;     current_basic_type = symbol_char;       bitsmask |= BIT_CHAR;}
#line 2274 "parser.c"
    break;

  case 27: /* simple-type-specifier: boolsym  */
#line 625 "parser.y"
                        {if((bitsmask & BIT_BOOL) == (1 << 0)){printf("uncorrect:bool bool\n");exit(1);}             current_type[current_type_num++] = symbol_bool;     current_basic_type = symbol_bool;       bitsmask |= BIT_BOOL;}
#line 2280 "parser.c"
    break;

  case 28: /* simple-type-specifier: shortsym  */
#line 626 "parser.y"
                        {if((bitsmask & BIT_SHORT) == (1 << 7)){printf("uncorrect:short short\n");exit(1);}          current_type[current_type_num++] = symbol_short;                                            bitsmask |= BIT_SHORT;}
#line 2286 "parser.c"
    break;

  case 29: /* simple-type-specifier: intsym  */
#line 627 "parser.y"
                        {if((bitsmask & BIT_INT) == (1 << 4)){printf("uncorrect:int int\n");exit(1);}                current_type[current_type_num++] = symbol_int;      current_basic_type = symbol_int;        bitsmask |= BIT_INT;}
#line 2292 "parser.c"
    break;

  case 30: /* simple-type-specifier: longsym  */
#line 628 "parser.y"
                        {if((bitsmask & BIT_LONG) == (1 << 6)){printf("uncorrect:long long\n");exit(1);}             current_type[current_type_num++] = symbol_long;                                             bitsmask |= BIT_LONG;}
#line 2298 "parser.c"
    break;

  case 31: /* simple-type-specifier: signedsym  */
#line 629 "parser.y"
                        {if((bitsmask & BIT_SIGNED) == (1 << 8)){printf("uncorrect:signed signed\n");exit(1);}      current_type[current_type_num++] = symbol_signed;                                           bitsmask |= BIT_SIGNED;}
#line 2304 "parser.c"
    break;

  case 32: /* simple-type-specifier: unsignedsym  */
#line 630 "parser.y"
                        {if((bitsmask & BIT_UNSIGNED) == (1 << 9)){printf("uncorrect:unsigned unsigned\n");exit(1);} current_type[current_type_num++] = symbol_unsigned;                                         bitsmask |= BIT_UNSIGNED;}
#line 2310 "parser.c"
    break;

  case 33: /* simple-type-specifier: floatsym  */
#line 631 "parser.y"
                        {if((bitsmask & BIT_FLOAT) == (1 << 1)){printf("uncorrect:float float\n");exit(1);}          current_type[current_type_num++] = symbol_float;    current_basic_type = symbol_float;      bitsmask |= BIT_FLOAT;}
#line 2316 "parser.c"
    break;

  case 34: /* simple-type-specifier: doublesym  */
#line 632 "parser.y"
                        {if((bitsmask & BIT_DOUBLE) == (1 << 2)){printf("uncorrect:double double\n");exit(1);}       current_type[current_type_num++] = symbol_double;   current_basic_type = symbol_double;     bitsmask |= BIT_DOUBLE;}
#line 2322 "parser.c"
    break;

  case 35: /* simple-type-specifier: voidsym  */
#line 633 "parser.y"
                        {if((bitsmask & BIT_VOID) == (1 << 5)){printf("uncorrect:void void\n");exit(1);}             current_type[current_type_num++] = symbol_void;     current_basic_type = symbol_void;       bitsmask |= BIT_VOID;}
#line 2328 "parser.c"
    break;

  case 36: /* cv-qualifier: constsym  */
#line 638 "parser.y"
                        {if((bitsmask & BIT_CONST) == 1){printf("uncorrect:const const\n");exit(1);}          current_type[current_type_num++] = symbol_const;     bitsmask |= BIT_CONST;}
#line 2334 "parser.c"
    break;

  case 42: /* init-declarator: declarator initializer  */
#line 668 "parser.y"
    {
        Is_Valid_Declarator((yyvsp[-1].sval).name,par_index);                     //compare declarator and current fucnction's par
        Is_Valid_Declarator((yyvsp[-1].sval).name,last_index);                //compare declarator and current fucnction's vars
        
        if(current_basic_type == symbol_void){
            printf("wrong: 'void' can't be assign\n");
            exit(0);
        }

        if(current_basic_type == (yyvsp[0].expr_attri).type){
            
        }
        else if(current_basic_type == symbol_char && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyvsp[0].expr_attri).c_val = (yyvsp[0].expr_attri).b_val;
        }
        else if(current_basic_type == symbol_char && (yyvsp[0].expr_attri).type == symbol_int){
            (yyvsp[0].expr_attri).c_val = (yyvsp[0].expr_attri).i_val;
        }
        else if(current_basic_type == symbol_char && (yyvsp[0].expr_attri).type == symbol_float){
            printf("warning: implicit conversion from 'float' to 'char' changes value from 1.234 to 1 [-Wliteral-conversion]\n");
            (yyvsp[0].expr_attri).c_val = (int)(yyvsp[0].expr_attri).f_val;
        }
        else if(current_basic_type == symbol_char && (yyvsp[0].expr_attri).type == symbol_double){
            printf("warning: implicit conversion from 'double' to 'char' changes value from 1.234 to 1 [-Wliteral-conversion]\n");
            (yyvsp[0].expr_attri).c_val = (int)(yyvsp[0].expr_attri).d_val;
        }
        
        else if(current_basic_type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_char){
            (yyvsp[0].expr_attri).b_val = ((int)(yyvsp[0].expr_attri).c_val == 0) ? 0 : 1;
        }
        else if(current_basic_type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_int){
            (yyvsp[0].expr_attri).b_val = ((yyvsp[0].expr_attri).i_val == 0) ? 0 : 1;
        }
        else if(current_basic_type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_float){
            (yyvsp[0].expr_attri).b_val = ((yyvsp[0].expr_attri).f_val == 0) ? 0 : 1;
        }
        else if(current_basic_type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_double){
            (yyvsp[0].expr_attri).b_val = ((yyvsp[0].expr_attri).d_val == 0) ? 0 : 1;
        }

        else if(current_basic_type == symbol_int && (yyvsp[0].expr_attri).type == symbol_char){
            (yyvsp[0].expr_attri).i_val = (int)(yyvsp[0].expr_attri).c_val;
        }
        else if(current_basic_type == symbol_int && (yyvsp[0].expr_attri).type == symbol_bool){
         (yyvsp[0].expr_attri).i_val = (yyvsp[0].expr_attri).b_val;
        }
        else if(current_basic_type == symbol_int && (yyvsp[0].expr_attri).type == symbol_float){
            (yyvsp[0].expr_attri).i_val = (int)(yyvsp[0].expr_attri).f_val;
        }
        else if(current_basic_type == symbol_int && (yyvsp[0].expr_attri).type == symbol_double){
            (yyvsp[0].expr_attri).i_val = (int)(yyvsp[0].expr_attri).d_val;
        }

        else if(current_basic_type == symbol_float && (yyvsp[0].expr_attri).type == symbol_char){
            (yyvsp[0].expr_attri).f_val = (float)(yyvsp[0].expr_attri).c_val;
        }
        else if(current_basic_type == symbol_float && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyvsp[0].expr_attri).f_val = (float)(yyvsp[0].expr_attri).b_val;
        }
        else if(current_basic_type == symbol_float && (yyvsp[0].expr_attri).type == symbol_int){
            (yyvsp[0].expr_attri).f_val = (float)(yyvsp[0].expr_attri).i_val;
        }
        else if(current_basic_type == symbol_float && (yyvsp[0].expr_attri).type == symbol_double){
            (yyvsp[0].expr_attri).f_val = (float)(yyvsp[0].expr_attri).d_val;
        }

        else if(current_basic_type == symbol_double && (yyvsp[0].expr_attri).type == symbol_char){
            (yyvsp[0].expr_attri).d_val = (double)(yyvsp[0].expr_attri).c_val;
        }
        else if(current_basic_type == symbol_double && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyvsp[0].expr_attri).d_val = (double)(yyvsp[0].expr_attri).b_val;
        }
        else if(current_basic_type == symbol_double && (yyvsp[0].expr_attri).type == symbol_int){
            (yyvsp[0].expr_attri).d_val = (double)(yyvsp[0].expr_attri).i_val;
        }
        else if(current_basic_type == symbol_double && (yyvsp[0].expr_attri).type == symbol_float){
            (yyvsp[0].expr_attri).d_val = (double)(yyvsp[0].expr_attri).f_val;
        }

            Enter_Nametab(current_type,current_type_num,current_basic_type,variable,(yyvsp[-1].sval).name,true,(yyvsp[0].expr_attri).b_val,(yyvsp[0].expr_attri).c_val,(yyvsp[0].expr_attri).d_val,(yyvsp[0].expr_attri).f_val,(yyvsp[0].expr_attri).i_val,(yyvsp[0].expr_attri).l_val,(yyvsp[0].expr_attri).s_val,(yyvsp[0].expr_attri).p_val,(yyvsp[-1].sval).ptr_level);            //Enter nametab

    }
#line 2421 "parser.c"
    break;

  case 43: /* init-declarator: declarator  */
#line 751 "parser.y"
    {
        Is_Valid_Declarator((yyvsp[0].sval).name,par_index);                     //compare declarator and current fucnction's pars
        Is_Valid_Declarator((yyvsp[0].sval).name,last_index);                //compare declarator and current fucnction's vars
        
        Enter_Nametab(current_type,current_type_num,current_basic_type,variable,(yyvsp[0].sval).name,true,0,0x00,0,0,0,0,0,NULL,(yyvsp[0].sval).ptr_level);            //Enter nametab
    }
#line 2432 "parser.c"
    break;

  case 44: /* declarator: ptr-declarator  */
#line 761 "parser.y"
    {
        (yyval.sval).value = 0;
        (yyval.sval).ptr_level = (yyvsp[0].sval).ptr_level;
        (yyval.sval).name = (yyvsp[0].sval).name;
        // $$.psize = $1.psize;

        (yyval.sval).lastpar = (yyvsp[0].sval).lastpar;      //when declarator is function' name,lastpar has meaning.
    }
#line 2445 "parser.c"
    break;

  case 45: /* ptr-declarator: noptr-declarator  */
#line 773 "parser.y"
    {
        (yyval.sval).value = 0;
        (yyval.sval).ptr_level = 0;
        (yyval.sval).name = (yyvsp[0].sval).name;
        // $$.psize = $1.psize;

        (yyval.sval).lastpar = (yyvsp[0].sval).lastpar;      //when declarator is function' name,lastpar has meaning.
    }
#line 2458 "parser.c"
    break;

  case 46: /* ptr-declarator: ptr-operator ptr-declarator  */
#line 782 "parser.y"
    {
        (yyval.sval).value = 0;
        (yyval.sval).ptr_level = (yyvsp[0].sval).ptr_level + 1;
        (yyval.sval).name = (yyvsp[0].sval).name;
    }
#line 2468 "parser.c"
    break;

  case 48: /* noptr-declarator: declarator-id  */
#line 795 "parser.y"
    {
        (yyval.sval).value = 0;
        (yyval.sval).ptr_level = 0;
        (yyval.sval).name = (yyvsp[0].sval).name;
    }
#line 2478 "parser.c"
    break;

  case 49: /* noptr-declarator: declarator-id parameters-and-qualifiers  */
#line 801 "parser.y"
    {
        (yyval.sval).name = (yyvsp[-1].sval).name;

        (yyval.sval).lastpar = last_index;

        par_index = last_index;             //record current function's last parameter's index
        last_index = 0;                     //the function's parameter declaration is finished, set last_index = 0 
    
        fetf_begin(&fe, final_out, (yyvsp[-1].sval).name, 0);             //init emitter
    }
#line 2493 "parser.c"
    break;

  case 52: /* declarator-id: id-expression  */
#line 817 "parser.y"
    {
        (yyval.sval).value = 0;
        (yyval.sval).ptr_level = 0;
        (yyval.sval).name = (yyvsp[0].sval).name;
    }
#line 2503 "parser.c"
    break;

  case 61: /* parameter-declaration: decl-specifier-seq declarator  */
#line 844 "parser.y"
    {
        if(last_index != 0){
            Is_Valid_Declarator((yyvsp[0].sval).name,last_index); 
        }
        Enter_Nametab((yyvsp[-1].decl_specifier_seq).type,(yyvsp[-1].decl_specifier_seq).type_num,(yyvsp[-1].decl_specifier_seq).basic_type,variable,(yyvsp[0].sval).name,false,0,0x00,0,0,0,0,0,NULL,(yyvsp[0].sval).ptr_level);
        
        Clear_current_type();                   //finish current type,need to be cleared.
    }
#line 2516 "parser.c"
    break;

  case 62: /* parameter-declaration: decl-specifier-seq declarator equal initializer-clause  */
#line 853 "parser.y"
    {
        if(last_index != 0){
            Is_Valid_Declarator((yyvsp[-2].sval).name,last_index); 
        }

        if(current_basic_type == symbol_void){
            printf("wrong: 'void' can't be assign\n");
            exit(0);
        }

        if(current_basic_type == (yyvsp[0].expr_attri).type){
            
        }
        else if(current_basic_type == symbol_char && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyvsp[0].expr_attri).c_val = (yyvsp[0].expr_attri).b_val;
        }
        else if(current_basic_type == symbol_char && (yyvsp[0].expr_attri).type == symbol_int){
            (yyvsp[0].expr_attri).c_val = (yyvsp[0].expr_attri).i_val;
        }
        else if(current_basic_type == symbol_char && (yyvsp[0].expr_attri).type == symbol_float){
            printf("warning: implicit conversion from 'float' to 'char' changes value from 1.234 to 1 [-Wliteral-conversion]\n");
            (yyvsp[0].expr_attri).c_val = (int)(yyvsp[0].expr_attri).f_val;
        }
        else if(current_basic_type == symbol_char && (yyvsp[0].expr_attri).type == symbol_double){
            printf("warning: implicit conversion from 'double' to 'char' changes value from 1.234 to 1 [-Wliteral-conversion]\n");
            (yyvsp[0].expr_attri).c_val = (int)(yyvsp[0].expr_attri).d_val;
        }
        
        else if(current_basic_type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_char){
            (yyvsp[0].expr_attri).b_val = ((int)(yyvsp[0].expr_attri).c_val == 0) ? 0 : 1;
        }
        else if(current_basic_type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_int){
            (yyvsp[0].expr_attri).b_val = ((yyvsp[0].expr_attri).i_val == 0) ? 0 : 1;
        }
        else if(current_basic_type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_float){
            (yyvsp[0].expr_attri).b_val = ((yyvsp[0].expr_attri).f_val == 0) ? 0 : 1;
        }
        else if(current_basic_type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_double){
            (yyvsp[0].expr_attri).b_val = ((yyvsp[0].expr_attri).d_val == 0) ? 0 : 1;
        }

        else if(current_basic_type == symbol_int && (yyvsp[0].expr_attri).type == symbol_char){
            (yyvsp[0].expr_attri).i_val = (int)(yyvsp[0].expr_attri).c_val;
            
        }
        else if(current_basic_type == symbol_int && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyvsp[0].expr_attri).i_val = (yyvsp[0].expr_attri).b_val;
        }
        else if(current_basic_type == symbol_int && (yyvsp[0].expr_attri).type == symbol_float){
            (yyvsp[0].expr_attri).i_val = (int)(yyvsp[0].expr_attri).f_val;
        }
        else if(current_basic_type == symbol_int && (yyvsp[0].expr_attri).type == symbol_double){
            (yyvsp[0].expr_attri).i_val = (int)(yyvsp[0].expr_attri).d_val;
        }

        else if(current_basic_type == symbol_float && (yyvsp[0].expr_attri).type == symbol_char){
            (yyvsp[0].expr_attri).f_val = (float)(yyvsp[0].expr_attri).c_val;
        }
        else if(current_basic_type == symbol_float && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyvsp[0].expr_attri).f_val = (float)(yyvsp[0].expr_attri).b_val;
        }
        else if(current_basic_type == symbol_float && (yyvsp[0].expr_attri).type == symbol_int){
            (yyvsp[0].expr_attri).f_val = (float)(yyvsp[0].expr_attri).i_val;
        }
        else if(current_basic_type == symbol_float && (yyvsp[0].expr_attri).type == symbol_double){
            (yyvsp[0].expr_attri).f_val = (float)(yyvsp[0].expr_attri).d_val;
        }

        else if(current_basic_type == symbol_double && (yyvsp[0].expr_attri).type == symbol_char){
            (yyvsp[0].expr_attri).d_val = (double)(yyvsp[0].expr_attri).c_val;
        }
        else if(current_basic_type == symbol_double && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyvsp[0].expr_attri).d_val = (double)(yyvsp[0].expr_attri).b_val;
        }
        else if(current_basic_type == symbol_double && (yyvsp[0].expr_attri).type == symbol_int){
            (yyvsp[0].expr_attri).d_val = (double)(yyvsp[0].expr_attri).i_val;
        }
        else if(current_basic_type == symbol_double && (yyvsp[0].expr_attri).type == symbol_float){
            (yyvsp[0].expr_attri).d_val = (double)(yyvsp[0].expr_attri).f_val;
        }

        Enter_Nametab((yyvsp[-3].decl_specifier_seq).type,(yyvsp[-3].decl_specifier_seq).type_num,(yyvsp[-3].decl_specifier_seq).basic_type,variable,(yyvsp[-2].sval).name,false,(yyvsp[0].expr_attri).b_val,(yyvsp[0].expr_attri).c_val,(yyvsp[0].expr_attri).d_val,(yyvsp[0].expr_attri).f_val,(yyvsp[0].expr_attri).i_val,(yyvsp[0].expr_attri).l_val,(yyvsp[0].expr_attri).s_val,(yyvsp[0].expr_attri).p_val,(yyvsp[-2].sval).ptr_level);
    
        Clear_current_type();                   //finish current type,need to be cleared.
    }
#line 2606 "parser.c"
    break;

  case 63: /* initializer: brace-or-equal-initializer  */
#line 951 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2622 "parser.c"
    break;

  case 65: /* brace-or-equal-initializer: equal initializer-clause  */
#line 967 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2638 "parser.c"
    break;

  case 67: /* initializer-clause: assignment-expression  */
#line 983 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2654 "parser.c"
    break;

  case 70: /* expression: assignment-expression  */
#line 1004 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2670 "parser.c"
    break;

  case 72: /* assignment-expression: conditional-expression  */
#line 1020 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2686 "parser.c"
    break;

  case 75: /* conditional-expression: logical-or-expression  */
#line 1037 "parser.y"
    {

        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2703 "parser.c"
    break;

  case 77: /* logical-or-expression: logical-and-expression  */
#line 1056 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2719 "parser.c"
    break;

  case 79: /* logical-and-expression: inclusive-or-expression  */
#line 1072 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2735 "parser.c"
    break;

  case 81: /* inclusive-or-expression: exclusive-or-expression  */
#line 1088 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}        
    }
#line 2751 "parser.c"
    break;

  case 83: /* exclusive-or-expression: and-expression  */
#line 1104 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2767 "parser.c"
    break;

  case 85: /* and-expression: equality-expression  */
#line 1120 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2783 "parser.c"
    break;

  case 87: /* equality-expression: relational-expression  */
#line 1136 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2799 "parser.c"
    break;

  case 90: /* relational-expression: shift-expression  */
#line 1153 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2815 "parser.c"
    break;

  case 95: /* shift-expression: additive-expression  */
#line 1172 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2831 "parser.c"
    break;

  case 98: /* additive-expression: multiplicative-expression  */
#line 1189 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 2847 "parser.c"
    break;

  case 99: /* additive-expression: additive-expression plus multiplicative-expression  */
#line 1201 "parser.y"
        {

        if((yyvsp[-2].expr_attri).kind == variable || (yyvsp[0].expr_attri).kind == variable){                             //need generate code

        }else{                                                                      //constant folding
            if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_bool){
                (yyval.expr_attri).type = symbol_bool;
                (yyval.expr_attri).b_val = (yyvsp[-2].expr_attri).b_val + (yyvsp[0].expr_attri).b_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_char){
                (yyval.expr_attri).type = symbol_int;
                (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).b_val + (int)(yyvsp[0].expr_attri).c_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_double){
                (yyval.expr_attri).type = symbol_double;
                (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).b_val + (yyvsp[0].expr_attri).d_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_float){
                (yyval.expr_attri).type = symbol_float;
                (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).b_val + (yyvsp[0].expr_attri).f_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_int){
                (yyval.expr_attri).type = symbol_int;
                (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).b_val + (yyvsp[0].expr_attri).i_val;
            }
            // else if($1.type == symbol_bool && $3.type == symbol_long){
            //     $$.type = symbol_long;
            //     $$.l_val = (long)$1.b_val + $3.l_val;
            // }
            // else if($1.type == symbol_bool && $3.type == symbol_short){
            //     $$.type = symbol_int;
            //     $$.i_val = (int)$1.b_val + (int)$3.s_val;
            // }
            else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_point){
                (yyval.expr_attri).type = symbol_int;
                (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).b_val + (int)(yyvsp[0].expr_attri).s_val;
            }
        

            else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_bool){
                (yyval.expr_attri).type = symbol_int;
                (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val + (yyvsp[0].expr_attri).b_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_char){
                (yyval.expr_attri).type = symbol_int;
                (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val + (int)(yyvsp[0].expr_attri).c_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_double){
                (yyval.expr_attri).type = symbol_double;
                (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).c_val + (yyvsp[0].expr_attri).d_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_float){
                (yyval.expr_attri).type = symbol_float;
                (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).c_val + (yyvsp[0].expr_attri).f_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_int){
                (yyval.expr_attri).type = symbol_int;
                (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val + (yyvsp[0].expr_attri).i_val;
            }
            // else if($1.type == symbol_char && $3.type == symbol_long){
            //     $$.type = symbol_long;
            //     $$.l_val = (long)$1.c_val + $3.l_val;
            // }
            // else if($1.type == symbol_char && $3.type == symbol_short){
            //     $$.type = symbol_int;
            //     $$.i_val = (int)$1.c_val + (int)$3.s_val;
            // }


            else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_bool){
                (yyval.expr_attri).type = symbol_double;
                (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val + (double)(yyvsp[0].expr_attri).b_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_char){
                (yyval.expr_attri).type = symbol_double;
                (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val + (double)(yyvsp[0].expr_attri).c_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_double){
                (yyval.expr_attri).type = symbol_double;
                (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val + (yyvsp[0].expr_attri).d_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_float){
                (yyval.expr_attri).type = symbol_double;
                (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val + (double)(yyvsp[0].expr_attri).f_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_int){
                (yyval.expr_attri).type = symbol_double;
                (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val + (double)(yyvsp[0].expr_attri).i_val;
            }
            // else if($1.type == symbol_double && $3.type == symbol_long){
            //     $$.type = symbol_double;
            //     $$.d_val = $1.d_val + (double)$3.l_val;
            // }
            // else if($1.type == symbol_double && $3.type == symbol_short){
            //     $$.type = symbol_double;
            //     $$.d_val = $1.d_val + (double)$3.s_val;
            // }


            else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_bool){
                (yyval.expr_attri).type = symbol_float;
                (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val + (float)(yyvsp[0].expr_attri).b_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_char){
                (yyval.expr_attri).type = symbol_float;
                (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val + (float)(yyvsp[0].expr_attri).c_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_double){
                (yyval.expr_attri).type = symbol_double;
                (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).f_val + (yyvsp[0].expr_attri).d_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_float){
                (yyval.expr_attri).type = symbol_float;
                (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val + (yyvsp[0].expr_attri).f_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_int){
                (yyval.expr_attri).type = symbol_float;
                (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val + (float)(yyvsp[0].expr_attri).i_val;
            }
            // else if($1.type == symbol_float && $3.type == symbol_long){
            //     $$.type = symbol_float;
            //     $$.f_val = $1.f_val + (float)$3.l_val;
            // }
            // else if($1.type == symbol_float && $3.type == symbol_short){
            //     $$.type = symbol_float;
            //     $$.f_val = $1.f_val + (float)$3.s_val;
            // }


            else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_bool){
                (yyval.expr_attri).type = symbol_int;
                (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val + (yyvsp[0].expr_attri).b_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_char){
                (yyval.expr_attri).type = symbol_int;
                (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val + (int)(yyvsp[0].expr_attri).c_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_double){
                (yyval.expr_attri).type = symbol_double;
                (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).i_val + (yyvsp[0].expr_attri).d_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_float){
                (yyval.expr_attri).type = symbol_float;
                (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).i_val + (yyvsp[0].expr_attri).f_val;
            }
            else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_int){
                (yyval.expr_attri).type = symbol_int;
                (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val + (yyvsp[0].expr_attri).i_val;
            }
            // else if($1.type == symbol_int && $3.type == symbol_long){
            //     $$.type = symbol_long;
            //     $$.l_val = (long)$1.i_val + $3.l_val;
            // }
            // else if($1.type == symbol_int && $3.type == symbol_short){
            //     $$.type = symbol_int;
            //     $$.i_val = $1.i_val + (int)$3.s_val;
            // }


            // else if($1.type == symbol_long && $3.type == symbol_bool){
            //     $$.type = symbol_long;
            //     $$.l_val = $1.l_val + (long)$3.b_val;
            // }
            // else if($1.type == symbol_long && $3.type == symbol_char){
            //     $$.type = symbol_long;
            //     $$.l_val = $1.l_val + (long)$3.c_val;
            // }
            // else if($1.type == symbol_long && $3.type == symbol_double){
            //     $$.type = symbol_double;
            //     $$.d_val = (double)$1.l_val + $3.d_val;
            // }
            // else if($1.type == symbol_long && $3.type == symbol_float){
            //     $$.type = symbol_float;
            //     $$.f_val = (float)$1.l_val + $3.f_val;
            // }
            // else if($1.type == symbol_long && $3.type == symbol_int){
            //     $$.type = symbol_long;
            //     $$.l_val = $1.l_val + (long)$3.i_val;
            // }
            // else if($1.type == symbol_long && $3.type == symbol_long){
            //     $$.type = symbol_long;
            //     $$.l_val = $1.l_val + $3.l_val;
            // }
            // else if($1.type == symbol_long && $3.type == symbol_short){
            //     $$.type = symbol_long;
            //     $$.l_val = $1.l_val + (long)$3.s_val;
            // }


            // else if($1.type == symbol_short && $3.type == symbol_bool){
            //     $$.type = symbol_int;
            //     $$.i_val = (int)$1.s_val + $3.b_val;
            // }
            // else if($1.type == symbol_short && $3.type == symbol_char){
            //     $$.type = symbol_int;
            //     $$.i_val = (int)$1.s_val + (int)$3.c_val;
            // }
            // else if($1.type == symbol_short && $3.type == symbol_double){
            //     $$.type = symbol_double;
            //     $$.d_val = (double)$1.s_val + $3.d_val;
            // }
            // else if($1.type == symbol_short && $3.type == symbol_float){
            //     $$.type = symbol_float;
            //     $$.f_val = (float)$1.s_val + $3.f_val;
            // }
            // else if($1.type == symbol_short && $3.type == symbol_int){
            //     $$.type = symbol_int;
            //     $$.i_val = (int)$1.s_val + $3.i_val;
            // }
            // else if($1.type == symbol_short && $3.type == symbol_long){
            //     $$.type = symbol_long;
            //     $$.l_val = (long)$1.s_val + $3.l_val;
            // }
            // else if($1.type == symbol_short && $3.type == symbol_short){
            //     $$.type = symbol_short;
            //     $$.s_val = $1.s_val + $3.s_val;
            // }
        }

        
    }
#line 3073 "parser.c"
    break;

  case 100: /* additive-expression: additive-expression minus multiplicative-expression  */
#line 1423 "parser.y"
    {
        if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyval.expr_attri).type = symbol_bool;
            (yyval.expr_attri).b_val = (yyvsp[-2].expr_attri).b_val - (yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_char){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).b_val - (int)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_double){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).b_val - (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_float){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).b_val - (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_int){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).b_val - (yyvsp[0].expr_attri).i_val;
        }
        // else if($1.type == symbol_bool && $3.type == symbol_long){
        //     $$.type = symbol_long;
        //     $$.l_val = (long)$1.b_val - $3.l_val;
        // }
        // else if($1.type == symbol_bool && $3.type == symbol_short){
        //     $$.type = symbol_int;
        //     $$.i_val = (int)$1.b_val - (int)$3.s_val;
        // }
        

        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val - (yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_char){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val - (int)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_double){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).c_val - (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_float){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).c_val - (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_int){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val - (yyvsp[0].expr_attri).i_val;
        }
        // else if($1.type == symbol_char && $3.type == symbol_long){
        //     $$.type = symbol_long;
        //     $$.l_val = (long)$1.c_val - $3.l_val;
        // }
        // else if($1.type == symbol_char && $3.type == symbol_short){
        //     $$.type = symbol_int;
        //     $$.i_val = (int)$1.c_val - (int)$3.s_val;
        // }


        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val - (double)(yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_char){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val - (double)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_double){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val - (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_float){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val - (double)(yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_int){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val - (double)(yyvsp[0].expr_attri).i_val;
        }
        // else if($1.type == symbol_double && $3.type == symbol_long){
        //     $$.type = symbol_double;
        //     $$.d_val = $1.d_val - (double)$3.l_val;
        // }
        // else if($1.type == symbol_double && $3.type == symbol_short){
        //     $$.type = symbol_double;
        //     $$.d_val = $1.d_val - (double)$3.s_val;
        // }


        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val - (float)(yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_char){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val - (float)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_double){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).f_val - (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_float){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val - (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_int){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val - (float)(yyvsp[0].expr_attri).i_val;
        }
        // else if($1.type == symbol_float && $3.type == symbol_long){
        //     $$.type = symbol_float;
        //     $$.f_val = $1.f_val - (float)$3.l_val;
        // }
        // else if($1.type == symbol_float && $3.type == symbol_short){
        //     $$.type = symbol_float;
        //     $$.f_val = $1.f_val - (float)$3.s_val;
        // }


        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val - (yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_char){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val - (int)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_double){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).i_val - (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_float){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).i_val - (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_int){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val - (yyvsp[0].expr_attri).i_val;
        }
        // else if($1.type == symbol_int && $3.type == symbol_long){
        //     $$.type = symbol_long;
        //     $$.l_val = (long)$1.i_val - $3.l_val;
        // }
        // else if($1.type == symbol_int && $3.type == symbol_short){
        //     $$.type = symbol_int;
        //     $$.i_val = $1.i_val - (int)$3.s_val;
        // }


        // else if($1.type == symbol_long && $3.type == symbol_bool){
        //     $$.type = symbol_long;
        //     $$.l_val = $1.l_val - (long)$3.b_val;
        // }
        // else if($1.type == symbol_long && $3.type == symbol_char){
        //     $$.type = symbol_long;
        //     $$.l_val = $1.l_val - (long)$3.c_val;
        // }
        // else if($1.type == symbol_long && $3.type == symbol_double){
        //     $$.type = symbol_double;
        //     $$.d_val = (double)$1.l_val - $3.d_val;
        // }
        // else if($1.type == symbol_long && $3.type == symbol_float){
        //     $$.type = symbol_float;
        //     $$.f_val = (float)$1.l_val - $3.f_val;
        // }
        // else if($1.type == symbol_long && $3.type == symbol_int){
        //     $$.type = symbol_long;
        //     $$.l_val = $1.l_val - (long)$3.i_val;
        // }
        // else if($1.type == symbol_long && $3.type == symbol_long){
        //     $$.type = symbol_long;
        //     $$.l_val = $1.l_val - $3.l_val;
        // }
        // else if($1.type == symbol_long && $3.type == symbol_short){
        //     $$.type = symbol_long;
        //     $$.l_val = $1.l_val - (long)$3.s_val;
        // }

        // else if($1.type == symbol_short && $3.type == symbol_bool){
        //     $$.type = symbol_int;
        //     $$.i_val = (int)$1.s_val - $3.b_val;
        // }
        // else if($1.type == symbol_short && $3.type == symbol_char){
        //     $$.type = symbol_int;
        //     $$.i_val = (int)$1.s_val - (int)$3.c_val;
        // }
        // else if($1.type == symbol_short && $3.type == symbol_double){
        //     $$.type = symbol_double;
        //     $$.d_val = (double)$1.s_val - $3.d_val;
        // }
        // else if($1.type == symbol_short && $3.type == symbol_float){
        //     $$.type = symbol_float;
        //     $$.f_val = (float)$1.s_val - $3.f_val;
        // }
        // else if($1.type == symbol_short && $3.type == symbol_int){
        //     $$.type = symbol_int;
        //     $$.i_val = (int)$1.s_val - $3.i_val;
        // }
        // else if($1.type == symbol_short && $3.type == symbol_long){
        //     $$.type = symbol_long;
        //     $$.l_val = (long)$1.s_val - $3.l_val;
        // }
        // else if($1.type == symbol_short && $3.type == symbol_short){
        //     $$.type = symbol_short;
        //     $$.s_val = $1.s_val - $3.s_val;
        // }
    }
#line 3287 "parser.c"
    break;

  case 101: /* multiplicative-expression: pm-expression  */
#line 1636 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}   
    }
#line 3303 "parser.c"
    break;

  case 102: /* multiplicative-expression: multiplicative-expression star pm-expression  */
#line 1648 "parser.y"
    {
        if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).b_val * (yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_char){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).b_val * (int)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_double){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).b_val * (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_float){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).b_val * (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_int){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).b_val * (yyvsp[0].expr_attri).i_val;
        }
        
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val * (yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_char){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val * (int)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_double){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).c_val * (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_float){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).c_val * (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_int){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val * (yyvsp[0].expr_attri).i_val;
        }

        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val * (double)(yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_char){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val * (double)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_double){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val * (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_float){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val * (double)(yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_int){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val * (double)(yyvsp[0].expr_attri).i_val;
        }
        
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val * (float)(yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_char){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val * (float)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_double){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).f_val * (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_float){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val * (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_int){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val * (float)(yyvsp[0].expr_attri).i_val;
        }
        
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_bool){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val * (yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_char){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val * (int)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_double){
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).i_val * (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_float){
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).i_val * (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_int){
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val * (yyvsp[0].expr_attri).i_val;
        }
    }
#line 3414 "parser.c"
    break;

  case 103: /* multiplicative-expression: multiplicative-expression slash pm-expression  */
#line 1755 "parser.y"
    {
        if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_bool){
            if((yyvsp[0].expr_attri).b_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).b_val / (yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_char){
            if((int)(yyvsp[0].expr_attri).c_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).b_val / (int)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_double){
            if((yyvsp[0].expr_attri).d_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).b_val / (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_float){
            if((yyvsp[0].expr_attri).f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }           
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).b_val / (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_bool && (yyvsp[0].expr_attri).type == symbol_int){
            if((yyvsp[0].expr_attri).i_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }            
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).b_val / (yyvsp[0].expr_attri).i_val;
        }
        
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_bool){
            if((yyvsp[0].expr_attri).b_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val / (yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_char){
            if((int)(yyvsp[0].expr_attri).c_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val / (int)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_double){
            if((yyvsp[0].expr_attri).d_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).c_val / (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_float){
            if((yyvsp[0].expr_attri).f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).c_val / (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_char && (yyvsp[0].expr_attri).type == symbol_int){
            if((yyvsp[0].expr_attri).i_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            } 
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (int)(yyvsp[-2].expr_attri).c_val / (yyvsp[0].expr_attri).i_val;
        }

        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_bool){
            if((yyvsp[0].expr_attri).b_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val / (double)(yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_char){
            if((int)(yyvsp[0].expr_attri).c_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val / (double)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_double){
            if((yyvsp[0].expr_attri).d_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val / (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_float){
            if((yyvsp[0].expr_attri).f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val / (double)(yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_double && (yyvsp[0].expr_attri).type == symbol_int){
            if((yyvsp[0].expr_attri).i_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (yyvsp[-2].expr_attri).d_val / (double)(yyvsp[0].expr_attri).i_val;
        }
        
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_bool){
            if((yyvsp[0].expr_attri).b_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val / (float)(yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_char){
            if((int)(yyvsp[0].expr_attri).c_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val / (float)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_double){
            if((yyvsp[0].expr_attri).d_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).f_val / (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_float){
            if((yyvsp[0].expr_attri).f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val / (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_float && (yyvsp[0].expr_attri).type == symbol_int){
            if((yyvsp[0].expr_attri).f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (yyvsp[-2].expr_attri).f_val / (float)(yyvsp[0].expr_attri).i_val;
        }
        
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_bool){
            if((yyvsp[0].expr_attri).b_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val / (yyvsp[0].expr_attri).b_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_char){
            if((int)(yyvsp[0].expr_attri).c_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val / (int)(yyvsp[0].expr_attri).c_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_double){
            if((yyvsp[0].expr_attri).d_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_double;
            (yyval.expr_attri).d_val = (double)(yyvsp[-2].expr_attri).i_val / (yyvsp[0].expr_attri).d_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_float){
            if((yyvsp[0].expr_attri).f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_float;
            (yyval.expr_attri).f_val = (float)(yyvsp[-2].expr_attri).i_val / (yyvsp[0].expr_attri).f_val;
        }
        else if((yyvsp[-2].expr_attri).type == symbol_int && (yyvsp[0].expr_attri).type == symbol_int){
            if((yyvsp[0].expr_attri).i_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            (yyval.expr_attri).type = symbol_int;
            (yyval.expr_attri).i_val = (yyvsp[-2].expr_attri).i_val / (yyvsp[0].expr_attri).i_val;
        }
    }
#line 3625 "parser.c"
    break;

  case 105: /* pm-expression: cast-expression  */
#line 1966 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 3641 "parser.c"
    break;

  case 108: /* cast-expression: unary-expression  */
#line 1983 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 3657 "parser.c"
    break;

  case 110: /* unary-expression: postfix-expression  */
#line 1999 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 3673 "parser.c"
    break;

  case 118: /* postfix-expression: primary-expression  */
#line 2021 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 3689 "parser.c"
    break;

  case 128: /* primary-expression: literal  */
#line 2045 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[0].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[0].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[0].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[0].expr_attri).size;}
    }
#line 3705 "parser.c"
    break;

  case 129: /* primary-expression: left_paren expression right_paren  */
#line 2057 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[-1].expr_attri).type;
        if((yyval.expr_attri).type == symbol_bool) (yyval.expr_attri).b_val = (yyvsp[-1].expr_attri).b_val;
        else if((yyval.expr_attri).type == symbol_char) (yyval.expr_attri).c_val = (yyvsp[-1].expr_attri).c_val;
        else if((yyval.expr_attri).type == symbol_double) (yyval.expr_attri).d_val = (yyvsp[-1].expr_attri).d_val;
        else if((yyval.expr_attri).type == symbol_float) (yyval.expr_attri).f_val = (yyvsp[-1].expr_attri).f_val;
        else if((yyval.expr_attri).type == symbol_int) (yyval.expr_attri).i_val = (yyvsp[-1].expr_attri).i_val;
        else if((yyval.expr_attri).type == symbol_long) (yyval.expr_attri).l_val = (yyvsp[-1].expr_attri).l_val;
        else if((yyval.expr_attri).type == symbol_short) (yyval.expr_attri).s_val = (yyvsp[-1].expr_attri).s_val;
        else if((yyval.expr_attri).type == symbol_point) {(yyval.expr_attri).p_val = (yyvsp[-1].expr_attri).p_val; (yyval.expr_attri).size = (yyvsp[-1].expr_attri).size;}
    }
#line 3721 "parser.c"
    break;

  case 130: /* primary-expression: id-expression  */
#line 2069 "parser.y"
    {
        
    }
#line 3729 "parser.c"
    break;

  case 131: /* literal: integer-literal  */
#line 2076 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type; 
        (yyval.expr_attri).i_val = (yyvsp[0].expr_attri).i_val;
    }
#line 3738 "parser.c"
    break;

  case 132: /* literal: character-literal  */
#line 2081 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        (yyval.expr_attri).c_val = (yyvsp[0].expr_attri).c_val;
    }
#line 3747 "parser.c"
    break;

  case 133: /* literal: floating-literal  */
#line 2086 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        (yyval.expr_attri).f_val = (yyvsp[0].expr_attri).f_val;
    }
#line 3756 "parser.c"
    break;

  case 134: /* literal: string-literal  */
#line 2091 "parser.y"
    {

    }
#line 3764 "parser.c"
    break;

  case 135: /* literal: boolean-literal  */
#line 2095 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type; 
        (yyval.expr_attri).b_val = (yyvsp[0].expr_attri).b_val;   
    }
#line 3773 "parser.c"
    break;

  case 136: /* literal: pointer-literal  */
#line 2100 "parser.y"
    {
        (yyval.expr_attri).type = (yyvsp[0].expr_attri).type;
        (yyval.expr_attri).p_val = (yyvsp[0].expr_attri).p_val;
    }
#line 3782 "parser.c"
    break;

  case 137: /* integer-literal: int_number  */
#line 2108 "parser.y"
    {
        (yyval.expr_attri).type = symbol_int; 
        (yyval.expr_attri).i_val = (yyvsp[0].ival);
    }
#line 3791 "parser.c"
    break;

  case 138: /* character-literal: single_quote one_char single_quote  */
#line 2116 "parser.y"
    {
        (yyval.expr_attri).type = symbol_char; 
        (yyval.expr_attri).c_val = (yyvsp[-1].sval).name[0];
    }
#line 3800 "parser.c"
    break;

  case 139: /* floating-literal: float_number  */
#line 2124 "parser.y"
    {
        (yyval.expr_attri).type = symbol_float; 
        (yyval.expr_attri).f_val = (yyvsp[0].fval);
    }
#line 3809 "parser.c"
    break;

  case 141: /* boolean-literal: truesym  */
#line 2136 "parser.y"
    {
        (yyval.expr_attri).type = symbol_bool; 
        (yyval.expr_attri).b_val = 1;
    }
#line 3818 "parser.c"
    break;

  case 142: /* boolean-literal: falsesym  */
#line 2141 "parser.y"
    {
        (yyval.expr_attri).type = symbol_bool; 
        (yyval.expr_attri).b_val = 0;
    }
#line 3827 "parser.c"
    break;

  case 143: /* pointer-literal: nullptr  */
#line 2149 "parser.y"
    {
        (yyval.expr_attri).type = symbol_point;
        (yyval.expr_attri).p_val = NULL;
    }
#line 3836 "parser.c"
    break;

  case 144: /* id-expression: unqualified-id  */
#line 2157 "parser.y"
    {
        (yyval.sval).value = 0;
        (yyval.sval).ptr_level = 0;
        (yyval.sval).name = (yyvsp[0].sval).name;
    }
#line 3846 "parser.c"
    break;

  case 146: /* unqualified-id: identifier  */
#line 2167 "parser.y"
    {
        (yyval.sval).value = 0;
        (yyval.sval).ptr_level = 0;
        (yyval.sval).name = (yyvsp[0].sval).name;
    }
#line 3856 "parser.c"
    break;

  case 147: /* unqualified-id: one_char  */
#line 2173 "parser.y"
    {
        (yyval.sval).value = 0;
        (yyval.sval).ptr_level = 0;
        (yyval.sval).name = (yyvsp[0].sval).name;
    }
#line 3866 "parser.c"
    break;

  case 177: /* function-definition: decl-specifier-seq declarator function-body  */
#line 2246 "parser.y"
    {  
        Is_Valid_Function((yyvsp[-1].sval).name);
        Enter_Btab((yyvsp[-2].decl_specifier_seq).type,(yyvsp[-2].decl_specifier_seq).type_num,(yyvsp[-2].decl_specifier_seq).basic_type,(yyvsp[-1].sval).name,(yyvsp[-1].sval).lastpar,last_index,par_point - 8,par_point - 8 + loc_point);      //enter btab;

        fetf_fix_locals(&fe,loc_point);                     //set real VSize
        fetf_end(&fe);                                      //insert prologue
    }
#line 3878 "parser.c"
    break;


#line 3882 "parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2354 "parser.y"

extern int yydebug;

int main(int argc,char* argv[]){

    if (argc < 2) {
        printf("用法: %s <source_file>\n", argv[0]);
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror("无法打开文件");
        return 1;
    }

    extern FILE *yyin;
    yyin = f;

    final_out = fopen("output.asm", "w+");   

    /* yydebug = 1; */
    yyparse();
    Display_Nametab();
    Display_Btab();


    fclose(f);
    return 0;
}
