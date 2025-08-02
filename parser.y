%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


FILE *fp;

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


struct btab_struct btab[TABLE_NUM];
int btab_count = 0;

int var_point = 12;                                  //point variables's localation,unit:byte(8bits)


struct atab_struct atab[TABLE_NUM];

struct code_struct code[TABLE_NUM];
unsigned int cx = 0;

int current_type[10];
int current_type_num = 0;
int current_basic_type;

int bitsmask = 0;                                   //use to exam specifier conflict





int yylex();
void yyerror(const char *s);

void Enter_Nametab(int type[],int type_num,int basic_type,int kind,char* name,bool normal,int adr,int b_val,char c_val,double d_val,float f_val,int i_val,long l_val,short s_val,void* p_val,int ptr_level);
void Enter_Btab(int type[],int type_num,int basic_type,char* name,int lastpar,int last,int psize,int vsize);

void Is_Valid_Declarator(char* name);
void Is_Valid_Function(char* name);
void Is_correct_specifier();

void Display_Nametab();
void Display_Btab();

void Clear_current_type();
void Clear_After_Declaration();


extern int yylineno;
extern char* yytext;

void yyerror(const char *s) {
    fprintf(stderr, "[Bison Error] at line %d: %s\n", yylineno, s);
    fprintf(stderr, "    Last matched token: '%s'\n", yytext);
    exit(0);
}

void Enter_Nametab(int type[],int type_num,int basic_type,int kind,char* name,bool normal,int adr,int b_val,char c_val,double d_val,float f_val,int i_val,long l_val,short s_val,void* p_val,int ptr_level){
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

    nametab[nametab_count].adr = adr;
    var_point += nametab[nametab_count].size;

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

void Is_Valid_Declarator(char* name){

    if(last_index == 0){return;}

    int loop = nametab_count;

    loop--;
    while(1){
        if(strcmp(name,nametab[loop].name) == 0){
            printf("wrong:\tthe repeated declarator %s",name);
            exit(0);
        }
        loop = nametab[loop].link;
        if(loop == 0) break;
    }
}

void Is_Valid_Function(char* name){
    for(int i = 0;i < btab_count;i++){
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
    printf("the following is symbol table:\n");

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

}

void Clear_current_type(){
    current_type_num = 0;
    bitsmask &= 0x0000;
    current_basic_type = symbol_int;
}

void Clear_After_Declaration(){
    last_index = 0;                             //the function parser or gobal var declaration is finished, set last_index = 0.
    var_point = 12;                               //the function parser or gobal var declaration is finished, reset var_point.
}



%}


%union{
    int ival;
    float fval;
    struct{
        int value;
        char* name;
        int ptr_level;
        int lastpar;                        //for function,record the last parameter's addr
        int psize;                          //for function,record all parameters's size
        int is_functionName;                //for function
    }sval;


    struct {
        int type;
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
       int type[10];
       int type_num;
       int basic_type;
    }decl_specifier_seq;


}

%type<expr_attri> expression assignment-expression conditional-expression logical-or-expression logical-and-expression inclusive-or-expression exclusive-or-expression and-expression equality-expression relational-expression shift-expression
%type<expr_attri> additive-expression multiplicative-expression pm-expression cast-expression unary-expression postfix-expression primary-expression
%type<expr_attri> literal integer-literal character-literal floating-literal string-literal boolean-literal pointer-literal
%type<expr_attri> initializer-clause brace-or-equal-initializer initializer

%type<sval> unqualified-id id-expression declarator-id noptr-declarator ptr-declarator declarator

%type<decl_specifier_seq> decl-specifier-seq





%token<fval> float_number
%token<ival> int_number
%token<sval> identifier one_char


%token  boolsym charsym constsym staticsym doublesym floatsym intsym longsym shortsym signedsym unsignedsym voidsym
%token  falsesym truesym
%token  whilesym dosym ifsym elsesym ifelsesym switchsym casesym defaultsym forsym gotosym trysym catchsym
%token  continuesym breaksym
%token  andsym orsym
%token  newsym deletesym 
%token  enumsym structsym
%token  returnsym
%token  sizeofsym typedefsym
%token  inlinesym throwsym

 



%token comma left_bracket right_bracket question colon 
%token  equal muti_equal divi_equal mod_equal plus_equal minus_equal rshift_equal lshift_equal and_equal xor_equal or_equal //assignment operator
%token logi_or logi_and inclu_or exclu_or solo_and double_equal unequal logi_not bit_not
%token less greater less_and_equal greater_and_equal
%token lshift rshift
%token plus minus star slash mod left_paren right_paren semicolon hash left_brace right_brace 
%token dot_star arrow_star
%token double_add double_minus
%token dot three_dots arrow single_quote
%token	nullptr


%start translation-unit
%debug

%%

translation-unit:
    declaration-seq
    |/*empty*/
    ;

declaration-seq:
    declaration
    |declaration-seq declaration
    ;

declaration:
    block-declaration
    {
        Clear_After_Declaration();
    }
    |
    function-definition
    {
        Clear_After_Declaration();
    }
    |empty-declaration
    ;

block-declaration:
    simple-declaration
    /* |asm-definition */
    ;


simple-declaration:
    decl-specifier-seq semicolon
    |decl-specifier-seq init-declarator-list semicolon
    {
        Clear_current_type();                   //finish current type,need to be cleared.
    }
    |init-declarator-list semicolon
    |semicolon
    ;


/*decl specifier*/
decl-specifier-seq:
    decl-specifier
    {
        for(int i = 0;i < current_type_num;i++){
            $$.type[i] = current_type[i];
        }
        $$.type_num = current_type_num;

        $$.basic_type = current_basic_type;
    }
    |decl-specifier decl-specifier-seq
    ;

decl-specifier:
    storage-class-specifier
    |type-specifier
    |function-specifier
    |typedefsym        
    ;

storage-class-specifier:
    ;


type-specifier:
    trailing-type-specifier
    |class-specifier
    |enum-specifier
    ;


trailing-type-specifier:
    simple-type-specifier
    |cv-qualifier
    ;

simple-type-specifier:
    charsym             {if((bitsmask & BIT_CHAR) == (1 << 3)){printf("uncorrect:char char\n");exit(1);}             current_type[current_type_num++] = symbol_char;     current_basic_type = symbol_char;       bitsmask |= BIT_CHAR;}
    |boolsym            {if((bitsmask & BIT_BOOL) == (1 << 0)){printf("uncorrect:bool bool\n");exit(1);}             current_type[current_type_num++] = symbol_bool;     current_basic_type = symbol_bool;       bitsmask |= BIT_BOOL;}
    |shortsym           {if((bitsmask & BIT_SHORT) == (1 << 7)){printf("uncorrect:short short\n");exit(1);}          current_type[current_type_num++] = symbol_short;                                            bitsmask |= BIT_SHORT;}
    |intsym             {if((bitsmask & BIT_INT) == (1 << 4)){printf("uncorrect:int int\n");exit(1);}                current_type[current_type_num++] = symbol_int;      current_basic_type = symbol_int;        bitsmask |= BIT_INT;}
    |longsym            {if((bitsmask & BIT_LONG) == (1 << 6)){printf("uncorrect:long long\n");exit(1);}             current_type[current_type_num++] = symbol_long;                                             bitsmask |= BIT_LONG;}
    |signedsym          {if((bitsmask & BIT_SIGNED) == (1 << 8)){printf("uncorrect:signed signed\n");exit(1);}      current_type[current_type_num++] = symbol_signed;                                           bitsmask |= BIT_SIGNED;}
    |unsignedsym        {if((bitsmask & BIT_UNSIGNED) == (1 << 9)){printf("uncorrect:unsigned unsigned\n");exit(1);} current_type[current_type_num++] = symbol_unsigned;                                         bitsmask |= BIT_UNSIGNED;}
    |floatsym           {if((bitsmask & BIT_FLOAT) == (1 << 1)){printf("uncorrect:float float\n");exit(1);}          current_type[current_type_num++] = symbol_float;    current_basic_type = symbol_float;      bitsmask |= BIT_FLOAT;}
    |doublesym          {if((bitsmask & BIT_DOUBLE) == (1 << 2)){printf("uncorrect:double double\n");exit(1);}       current_type[current_type_num++] = symbol_double;   current_basic_type = symbol_double;     bitsmask |= BIT_DOUBLE;}
    |voidsym            {if((bitsmask & BIT_VOID) == (1 << 5)){printf("uncorrect:void void\n");exit(1);}             current_type[current_type_num++] = symbol_void;     current_basic_type = symbol_void;       bitsmask |= BIT_VOID;}
    ;


cv-qualifier:
    constsym            {if((bitsmask & BIT_CONST) == 1){printf("uncorrect:const const\n");exit(1);}          current_type[current_type_num++] = symbol_const;     bitsmask |= BIT_CONST;}
    ;


class-specifier:
    ;

enum-specifier:
    ;


function-specifier:
    inlinesym
    ;



/* asm-definition: */




/*init declarator*/
init-declarator-list:
    init-declarator
    |init-declarator-list comma init-declarator
    ;

init-declarator:                    //have initializer or not
    declarator initializer
    {
        if($1.is_functionName == 0){

            Is_Valid_Declarator($1.name);

            if(current_basic_type == symbol_void){
                printf("wrong: 'void' can't be assign\n");
                exit(0);
            }

            if(current_basic_type == $2.type){
            
            }
            else if(current_basic_type == symbol_char && $2.type == symbol_bool){
                $2.c_val = $2.b_val;
            }
            else if(current_basic_type == symbol_char && $2.type == symbol_int){
                $2.c_val = $2.i_val;
            }
            else if(current_basic_type == symbol_char && $2.type == symbol_float){
                printf("warning: implicit conversion from 'float' to 'char' changes value from 1.234 to 1 [-Wliteral-conversion]\n");
                $2.c_val = (int)$2.f_val;
            }
            else if(current_basic_type == symbol_char && $2.type == symbol_double){
                printf("warning: implicit conversion from 'double' to 'char' changes value from 1.234 to 1 [-Wliteral-conversion]\n");
                $2.c_val = (int)$2.d_val;
            }
        
            else if(current_basic_type == symbol_bool && $2.type == symbol_char){
                $2.b_val = ((int)$2.c_val == 0) ? 0 : 1;
            }
            else if(current_basic_type == symbol_bool && $2.type == symbol_int){
                $2.b_val = ($2.i_val == 0) ? 0 : 1;
            }
            else if(current_basic_type == symbol_bool && $2.type == symbol_float){
                $2.b_val = ($2.f_val == 0) ? 0 : 1;
            }
            else if(current_basic_type == symbol_bool && $2.type == symbol_double){
                $2.b_val = ($2.d_val == 0) ? 0 : 1;
            }

            else if(current_basic_type == symbol_int && $2.type == symbol_char){
                $2.i_val = (int)$2.c_val;
            }
            else if(current_basic_type == symbol_int && $2.type == symbol_bool){
            $2.i_val = $2.b_val;
            }
            else if(current_basic_type == symbol_int && $2.type == symbol_float){
                $2.i_val = (int)$2.f_val;
            }
            else if(current_basic_type == symbol_int && $2.type == symbol_double){
                $2.i_val = (int)$2.d_val;
            }

            else if(current_basic_type == symbol_float && $2.type == symbol_char){
                $2.f_val = (float)$2.c_val;
            }
            else if(current_basic_type == symbol_float && $2.type == symbol_bool){
                $2.f_val = (float)$2.b_val;
            }
            else if(current_basic_type == symbol_float && $2.type == symbol_int){
                $2.f_val = (float)$2.i_val;
            }
            else if(current_basic_type == symbol_float && $2.type == symbol_double){
                $2.f_val = (float)$2.d_val;
            }

            else if(current_basic_type == symbol_double && $2.type == symbol_char){
                $2.d_val = (double)$2.c_val;
            }
            else if(current_basic_type == symbol_double && $2.type == symbol_bool){
                $2.d_val = (double)$2.b_val;
            }
            else if(current_basic_type == symbol_double && $2.type == symbol_int){
                $2.d_val = (double)$2.i_val;
            }
            else if(current_basic_type == symbol_double && $2.type == symbol_float){
                $2.d_val = (double)$2.f_val;
            }

            Enter_Nametab(current_type,current_type_num,current_basic_type,variable,$1.name,true,var_point,$2.b_val,$2.c_val,$2.d_val,$2.f_val,$2.i_val,$2.l_val,$2.s_val,$2.p_val,$1.ptr_level);            //Enter nametab
        }
    }
    |declarator
    {
        if($1.is_functionName == 0){
            Is_Valid_Declarator($1.name);                
            Enter_Nametab(current_type,current_type_num,current_basic_type,variable,$1.name,true,var_point,0,0x00,0,0,0,0,0,NULL,$1.ptr_level);            //Enter nametab
        }
    }
    ;

declarator:
    ptr-declarator                                                  //example:  int* p; or int a;
    {
        $$.value = 0;
        $$.ptr_level = $1.ptr_level;
        $$.name = $1.name;
        $$.psize = $1.psize;
        $$.is_functionName = $1.is_functionName;
    }
    ;

ptr-declarator:
	noptr-declarator
    {
        $$.value = 0;
        $$.ptr_level = 0;
        $$.name = $1.name;
        $$.psize = $1.psize;
        $$.is_functionName = $1.is_functionName;
    }
 	|ptr-operator ptr-declarator     //Recursive form,example:   ** a;
    {
        $$.value = 0;
        $$.ptr_level = $2.ptr_level + 1;
        $$.name = $2.name;
    }
    ;

ptr-operator:
    star
    ;

noptr-declarator:
	declarator-id
    {
        $$.value = 0;
        $$.ptr_level = 0;
        $$.name = $1.name;
        $$.is_functionName = 0;
    }
    |declarator-id parameters-and-qualifiers                     //int f(int x);
    {
        $$.name = $1.name;
        $$.psize = var_point;
        $$.is_functionName = 1;
    }
    |noptr-declarator left_bracket   constant-expression right_bracket
    |left_paren ptr-declarator right_paren
    ;

declarator-id:
    id-expression
    {
        
        $$.value = 0;
        $$.ptr_level = 0;
        $$.name = $1.name;
    }
    ;

parameters-and-qualifiers:
	left_paren parameter-declaration-clause right_paren
    ;

parameter-declaration-clause:
    parameter-declaration-list
    |three_dots
    |parameter-declaration-list three_dots
    |/*empty*/
 	|parameter-declaration-list comma three_dots
    ;

parameter-declaration-list:
    parameter-declaration
    |parameter-declaration-list comma parameter-declaration

    ;

parameter-declaration:
	decl-specifier-seq declarator
    {
        Is_Valid_Declarator($2.name);
        Enter_Nametab($1.type,$1.type_num,$1.basic_type,variable,$2.name,false,var_point,0,0x00,0,0,0,0,0,NULL,$2.ptr_level);
        
        Clear_current_type();                   //finish current type,need to be cleared.
    }
 	|decl-specifier-seq declarator equal initializer-clause
    {
        Is_Valid_Declarator($2.name);

        if(current_basic_type == symbol_void){
            printf("wrong: 'void' can't be assign\n");
            exit(0);
        }

        if(current_basic_type == $4.type){
            
        }
        else if(current_basic_type == symbol_char && $4.type == symbol_bool){
            $4.c_val = $4.b_val;
        }
        else if(current_basic_type == symbol_char && $4.type == symbol_int){
            $4.c_val = $4.i_val;
        }
        else if(current_basic_type == symbol_char && $4.type == symbol_float){
            printf("warning: implicit conversion from 'float' to 'char' changes value from 1.234 to 1 [-Wliteral-conversion]\n");
            $4.c_val = (int)$4.f_val;
        }
        else if(current_basic_type == symbol_char && $4.type == symbol_double){
            printf("warning: implicit conversion from 'double' to 'char' changes value from 1.234 to 1 [-Wliteral-conversion]\n");
            $4.c_val = (int)$4.d_val;
        }
        
        else if(current_basic_type == symbol_bool && $4.type == symbol_char){
            $4.b_val = ((int)$4.c_val == 0) ? 0 : 1;
        }
        else if(current_basic_type == symbol_bool && $4.type == symbol_int){
            $4.b_val = ($4.i_val == 0) ? 0 : 1;
        }
        else if(current_basic_type == symbol_bool && $4.type == symbol_float){
            $4.b_val = ($4.f_val == 0) ? 0 : 1;
        }
        else if(current_basic_type == symbol_bool && $4.type == symbol_double){
            $4.b_val = ($4.d_val == 0) ? 0 : 1;
        }

        else if(current_basic_type == symbol_int && $4.type == symbol_char){
            $4.i_val = (int)$4.c_val;
            
        }
        else if(current_basic_type == symbol_int && $4.type == symbol_bool){
            $4.i_val = $4.b_val;
        }
        else if(current_basic_type == symbol_int && $4.type == symbol_float){
            $4.i_val = (int)$4.f_val;
        }
        else if(current_basic_type == symbol_int && $4.type == symbol_double){
            $4.i_val = (int)$4.d_val;
        }

        else if(current_basic_type == symbol_float && $4.type == symbol_char){
            $4.f_val = (float)$4.c_val;
        }
        else if(current_basic_type == symbol_float && $4.type == symbol_bool){
            $4.f_val = (float)$4.b_val;
        }
        else if(current_basic_type == symbol_float && $4.type == symbol_int){
            $4.f_val = (float)$4.i_val;
        }
        else if(current_basic_type == symbol_float && $4.type == symbol_double){
            $4.f_val = (float)$4.d_val;
        }

        else if(current_basic_type == symbol_double && $4.type == symbol_char){
            $4.d_val = (double)$4.c_val;
        }
        else if(current_basic_type == symbol_double && $4.type == symbol_bool){
            $4.d_val = (double)$4.b_val;
        }
        else if(current_basic_type == symbol_double && $4.type == symbol_int){
            $4.d_val = (double)$4.i_val;
        }
        else if(current_basic_type == symbol_double && $4.type == symbol_float){
            $4.d_val = (double)$4.f_val;
        }

        Enter_Nametab($1.type,$1.type_num,$1.basic_type,variable,$2.name,false,var_point,$4.b_val,$4.c_val,$4.d_val,$4.f_val,$4.i_val,$4.l_val,$4.s_val,$4.p_val,$2.ptr_level);
    
        Clear_current_type();                   //finish current type,need to be cleared.
    }
    ;


trailing-return-type:
    ;






initializer:
    brace-or-equal-initializer              //like:   int a = 5;    int b{5};
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }     
    |left_paren expression-list  right_paren     //like:  MyClass obj(1, 2);
    ;

brace-or-equal-initializer:
    equal initializer-clause
    {
        $$.type = $2.type;
        if($$.type == symbol_bool) $$.b_val = $2.b_val;
        else if($$.type == symbol_char) $$.c_val = $2.c_val;
        else if($$.type == symbol_double) $$.d_val = $2.d_val;
        else if($$.type == symbol_float) $$.f_val = $2.f_val;
        else if($$.type == symbol_int) $$.i_val = $2.i_val;
        else if($$.type == symbol_long) $$.l_val = $2.l_val;
        else if($$.type == symbol_short) $$.s_val = $2.s_val;
        else if($$.type == symbol_point) {$$.p_val = $2.p_val; $$.size = $2.size;}
    } 
    |braced-init-list
    ;

initializer-clause:
    assignment-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    } 
    |braced-init-list
    ;


constant-expression:
    conditional-expression
    ;

expression:                                         //like: x = 1, y = 2;
    assignment-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }               
    |expression comma assignment-expression
    ;

assignment-expression:                                      //like: x += y;
    conditional-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }                      
    |logical-or-expression assignment-operator initializer-clause   
    |throw-expression
    ;

conditional-expression:                             //like: bool y = (a > b ? 1 : 0);
    logical-or-expression
    {

        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
    |logical-or-expression question expression colon assignment-expression
    ;
    


logical-or-expression:                              //like: a || b
    logical-and-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
    |logical-or-expression logi_or logical-and-expression
    ;

logical-and-expression:                             //like: a && b
    inclusive-or-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
    |logical-and-expression logi_and inclusive-or-expression
    ;

inclusive-or-expression:                            //like: a | b
    exclusive-or-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}        
    } 
    |inclusive-or-expression inclu_or exclusive-or-expression
    ;

exclusive-or-expression:                            //like: a ^ b
    and-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
    |exclusive-or-expression exclu_or and-expression
    ;

and-expression:                                     //like: a & b
    equality-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
    |and-expression solo_and equality-expression
    ;

equality-expression:                                //like: a == b     a != b
	relational-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
    |equality-expression double_equal relational-expression
 	|equality-expression unequal relational-expression
    ;

relational-expression:                              //like: a < b  a > b   a <= b  a >= b
    shift-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
 	|relational-expression less shift-expression
 	|relational-expression greater shift-expression
 	|relational-expression less_and_equal shift-expression
 	|relational-expression greater_and_equal shift-expression
    ;

shift-expression:                                   //like: a << 2  a >> 2
    additive-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
 	|shift-expression lshift additive-expression
 	|shift-expression rshift additive-expression
    ;

additive-expression:                                //like: a + b     a - b
    multiplicative-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
 	|additive-expression plus multiplicative-expression
 	{
        if($1.type == symbol_bool && $3.type == symbol_bool){
            $$.type = symbol_bool;
            $$.b_val = $1.b_val + $3.b_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_char){
            $$.type = symbol_int;
            $$.i_val = $1.b_val + (int)$3.c_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.b_val + $3.d_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = (float)$1.b_val + $3.f_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_int){
            $$.type = symbol_int;
            $$.i_val = (int)$1.b_val + $3.i_val;
        }
        // else if($1.type == symbol_bool && $3.type == symbol_long){
        //     $$.type = symbol_long;
        //     $$.l_val = (long)$1.b_val + $3.l_val;
        // }
        // else if($1.type == symbol_bool && $3.type == symbol_short){
        //     $$.type = symbol_int;
        //     $$.i_val = (int)$1.b_val + (int)$3.s_val;
        // }
        else if($1.type == symbol_bool && $3.type == symbol_point){
            $$.type = symbol_int;
            $$.i_val = (int)$1.b_val + (int)$3.s_val;
        }
        

        else if($1.type == symbol_char && $3.type == symbol_bool){
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val + $3.b_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_char){
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val + (int)$3.c_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.c_val + $3.d_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = (float)$1.c_val + $3.f_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_int){
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val + $3.i_val;
        }
        // else if($1.type == symbol_char && $3.type == symbol_long){
        //     $$.type = symbol_long;
        //     $$.l_val = (long)$1.c_val + $3.l_val;
        // }
        // else if($1.type == symbol_char && $3.type == symbol_short){
        //     $$.type = symbol_int;
        //     $$.i_val = (int)$1.c_val + (int)$3.s_val;
        // }


        else if($1.type == symbol_double && $3.type == symbol_bool){
            $$.type = symbol_double;
            $$.d_val = $1.d_val + (double)$3.b_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_char){
            $$.type = symbol_double;
            $$.d_val = $1.d_val + (double)$3.c_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = $1.d_val + $3.d_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_float){
            $$.type = symbol_double;
            $$.d_val = $1.d_val + (double)$3.f_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_int){
            $$.type = symbol_double;
            $$.d_val = $1.d_val + (double)$3.i_val;
        }
        // else if($1.type == symbol_double && $3.type == symbol_long){
        //     $$.type = symbol_double;
        //     $$.d_val = $1.d_val + (double)$3.l_val;
        // }
        // else if($1.type == symbol_double && $3.type == symbol_short){
        //     $$.type = symbol_double;
        //     $$.d_val = $1.d_val + (double)$3.s_val;
        // }


        else if($1.type == symbol_float && $3.type == symbol_bool){
            $$.type = symbol_float;
            $$.f_val = $1.f_val + (float)$3.b_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_char){
            $$.type = symbol_float;
            $$.f_val = $1.f_val + (float)$3.c_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.f_val + $3.d_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = $1.f_val + $3.f_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_int){
            $$.type = symbol_float;
            $$.f_val = $1.f_val + (float)$3.i_val;
        }
        // else if($1.type == symbol_float && $3.type == symbol_long){
        //     $$.type = symbol_float;
        //     $$.f_val = $1.f_val + (float)$3.l_val;
        // }
        // else if($1.type == symbol_float && $3.type == symbol_short){
        //     $$.type = symbol_float;
        //     $$.f_val = $1.f_val + (float)$3.s_val;
        // }


        else if($1.type == symbol_int && $3.type == symbol_bool){
            $$.type = symbol_int;
            $$.i_val = $1.i_val + $3.b_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_char){
            $$.type = symbol_int;
            $$.i_val = $1.i_val + (int)$3.c_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.i_val + $3.d_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = (float)$1.i_val + $3.f_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_int){
            $$.type = symbol_int;
            $$.i_val = $1.i_val + $3.i_val;
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
    |additive-expression minus multiplicative-expression
    {
        if($1.type == symbol_bool && $3.type == symbol_bool){
            $$.type = symbol_bool;
            $$.b_val = $1.b_val - $3.b_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_char){
            $$.type = symbol_int;
            $$.i_val = $1.b_val - (int)$3.c_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.b_val - $3.d_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = (float)$1.b_val - $3.f_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_int){
            $$.type = symbol_int;
            $$.i_val = (int)$1.b_val - $3.i_val;
        }
        // else if($1.type == symbol_bool && $3.type == symbol_long){
        //     $$.type = symbol_long;
        //     $$.l_val = (long)$1.b_val - $3.l_val;
        // }
        // else if($1.type == symbol_bool && $3.type == symbol_short){
        //     $$.type = symbol_int;
        //     $$.i_val = (int)$1.b_val - (int)$3.s_val;
        // }
        

        else if($1.type == symbol_char && $3.type == symbol_bool){
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val - $3.b_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_char){
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val - (int)$3.c_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.c_val - $3.d_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = (float)$1.c_val - $3.f_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_int){
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val - $3.i_val;
        }
        // else if($1.type == symbol_char && $3.type == symbol_long){
        //     $$.type = symbol_long;
        //     $$.l_val = (long)$1.c_val - $3.l_val;
        // }
        // else if($1.type == symbol_char && $3.type == symbol_short){
        //     $$.type = symbol_int;
        //     $$.i_val = (int)$1.c_val - (int)$3.s_val;
        // }


        else if($1.type == symbol_double && $3.type == symbol_bool){
            $$.type = symbol_double;
            $$.d_val = $1.d_val - (double)$3.b_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_char){
            $$.type = symbol_double;
            $$.d_val = $1.d_val - (double)$3.c_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = $1.d_val - $3.d_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_float){
            $$.type = symbol_double;
            $$.d_val = $1.d_val - (double)$3.f_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_int){
            $$.type = symbol_double;
            $$.d_val = $1.d_val - (double)$3.i_val;
        }
        // else if($1.type == symbol_double && $3.type == symbol_long){
        //     $$.type = symbol_double;
        //     $$.d_val = $1.d_val - (double)$3.l_val;
        // }
        // else if($1.type == symbol_double && $3.type == symbol_short){
        //     $$.type = symbol_double;
        //     $$.d_val = $1.d_val - (double)$3.s_val;
        // }


        else if($1.type == symbol_float && $3.type == symbol_bool){
            $$.type = symbol_float;
            $$.f_val = $1.f_val - (float)$3.b_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_char){
            $$.type = symbol_float;
            $$.f_val = $1.f_val - (float)$3.c_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.f_val - $3.d_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = $1.f_val - $3.f_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_int){
            $$.type = symbol_float;
            $$.f_val = $1.f_val - (float)$3.i_val;
        }
        // else if($1.type == symbol_float && $3.type == symbol_long){
        //     $$.type = symbol_float;
        //     $$.f_val = $1.f_val - (float)$3.l_val;
        // }
        // else if($1.type == symbol_float && $3.type == symbol_short){
        //     $$.type = symbol_float;
        //     $$.f_val = $1.f_val - (float)$3.s_val;
        // }


        else if($1.type == symbol_int && $3.type == symbol_bool){
            $$.type = symbol_int;
            $$.i_val = $1.i_val - $3.b_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_char){
            $$.type = symbol_int;
            $$.i_val = $1.i_val - (int)$3.c_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.i_val - $3.d_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = (float)$1.i_val - $3.f_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_int){
            $$.type = symbol_int;
            $$.i_val = $1.i_val - $3.i_val;
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
    ;

multiplicative-expression:                                          //like: a * b    a / b    a % b
    pm-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}   
    }
 	|multiplicative-expression star pm-expression
    {
        if($1.type == symbol_bool && $3.type == symbol_bool){
            $$.type = symbol_int;
            $$.i_val = $1.b_val * $3.b_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_char){
            $$.type = symbol_int;
            $$.i_val = $1.b_val * (int)$3.c_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.b_val * $3.d_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = (float)$1.b_val * $3.f_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_int){
            $$.type = symbol_int;
            $$.i_val = (int)$1.b_val * $3.i_val;
        }
        
        else if($1.type == symbol_char && $3.type == symbol_bool){
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val * $3.b_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_char){
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val * (int)$3.c_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.c_val * $3.d_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = (float)$1.c_val * $3.f_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_int){
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val * $3.i_val;
        }

        else if($1.type == symbol_double && $3.type == symbol_bool){
            $$.type = symbol_double;
            $$.d_val = $1.d_val * (double)$3.b_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_char){
            $$.type = symbol_double;
            $$.d_val = $1.d_val * (double)$3.c_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = $1.d_val * $3.d_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_float){
            $$.type = symbol_double;
            $$.d_val = $1.d_val * (double)$3.f_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_int){
            $$.type = symbol_double;
            $$.d_val = $1.d_val * (double)$3.i_val;
        }
        
        else if($1.type == symbol_float && $3.type == symbol_bool){
            $$.type = symbol_float;
            $$.f_val = $1.f_val * (float)$3.b_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_char){
            $$.type = symbol_float;
            $$.f_val = $1.f_val * (float)$3.c_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.f_val * $3.d_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = $1.f_val * $3.f_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_int){
            $$.type = symbol_float;
            $$.f_val = $1.f_val * (float)$3.i_val;
        }
        
        else if($1.type == symbol_int && $3.type == symbol_bool){
            $$.type = symbol_int;
            $$.i_val = $1.i_val * $3.b_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_char){
            $$.type = symbol_int;
            $$.i_val = $1.i_val * (int)$3.c_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_double){
            $$.type = symbol_double;
            $$.d_val = (double)$1.i_val * $3.d_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_float){
            $$.type = symbol_float;
            $$.f_val = (float)$1.i_val * $3.f_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_int){
            $$.type = symbol_int;
            $$.i_val = $1.i_val * $3.i_val;
        }
    }
 	|multiplicative-expression slash pm-expression
    {
        if($1.type == symbol_bool && $3.type == symbol_bool){
            if($3.b_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }
            $$.type = symbol_int;
            $$.i_val = $1.b_val / $3.b_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_char){
            if((int)$3.c_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }
            $$.type = symbol_int;
            $$.i_val = $1.b_val / (int)$3.c_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_double){
            if($3.d_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }
            $$.type = symbol_double;
            $$.d_val = (double)$1.b_val / $3.d_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_float){
            if($3.f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }           
            $$.type = symbol_float;
            $$.f_val = (float)$1.b_val / $3.f_val;
        }
        else if($1.type == symbol_bool && $3.type == symbol_int){
            if($3.i_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }            
            $$.type = symbol_int;
            $$.i_val = (int)$1.b_val / $3.i_val;
        }
        
        else if($1.type == symbol_char && $3.type == symbol_bool){
            if($3.b_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val / $3.b_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_char){
            if((int)$3.c_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val / (int)$3.c_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_double){
            if($3.d_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_double;
            $$.d_val = (double)$1.c_val / $3.d_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_float){
            if($3.f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_float;
            $$.f_val = (float)$1.c_val / $3.f_val;
        }
        else if($1.type == symbol_char && $3.type == symbol_int){
            if($3.i_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            } 
            $$.type = symbol_int;
            $$.i_val = (int)$1.c_val / $3.i_val;
        }

        else if($1.type == symbol_double && $3.type == symbol_bool){
            if($3.b_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_double;
            $$.d_val = $1.d_val / (double)$3.b_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_char){
            if((int)$3.c_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_double;
            $$.d_val = $1.d_val / (double)$3.c_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_double){
            if($3.d_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_double;
            $$.d_val = $1.d_val / $3.d_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_float){
            if($3.f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_double;
            $$.d_val = $1.d_val / (double)$3.f_val;
        }
        else if($1.type == symbol_double && $3.type == symbol_int){
            if($3.i_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_double;
            $$.d_val = $1.d_val / (double)$3.i_val;
        }
        
        else if($1.type == symbol_float && $3.type == symbol_bool){
            if($3.b_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_float;
            $$.f_val = $1.f_val / (float)$3.b_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_char){
            if((int)$3.c_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_float;
            $$.f_val = $1.f_val / (float)$3.c_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_double){
            if($3.d_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_double;
            $$.d_val = (double)$1.f_val / $3.d_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_float){
            if($3.f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_float;
            $$.f_val = $1.f_val / $3.f_val;
        }
        else if($1.type == symbol_float && $3.type == symbol_int){
            if($3.f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_float;
            $$.f_val = $1.f_val / (float)$3.i_val;
        }
        
        else if($1.type == symbol_int && $3.type == symbol_bool){
            if($3.b_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_int;
            $$.i_val = $1.i_val / $3.b_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_char){
            if((int)$3.c_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_int;
            $$.i_val = $1.i_val / (int)$3.c_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_double){
            if($3.d_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_double;
            $$.d_val = (double)$1.i_val / $3.d_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_float){
            if($3.f_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_float;
            $$.f_val = (float)$1.i_val / $3.f_val;
        }
        else if($1.type == symbol_int && $3.type == symbol_int){
            if($3.i_val == 0){
                printf("error:divide zero error!\n");
                exit(0);
            }             
            $$.type = symbol_int;
            $$.i_val = $1.i_val / $3.i_val;
        }
    }
 	|multiplicative-expression mod pm-expression
    ;

pm-expression:
    cast-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }                                               
 	|pm-expression dot_star cast-expression                         //low usage
 	|pm-expression arrow_star cast-expression
    ;

cast-expression:                                                    //like: (double) a
    unary-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
 	|left_paren type-id right_paren cast-expression                 //change the var type
    ;

unary-expression:
    postfix-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }                                           
    |double_add cast-expression                                     //like: ++x
    |double_minus cast-expression                                   //like: --x       
 	|unary-operator cast-expression                                 //like: +x -x &x
 	|sizeofsym unary-expression                                     //like: sizeof a
 	|sizeofsym left_paren type-id right_paren                       //like: sizeof(a)
 	|new-expression
 	|delete-expression
    ;

postfix-expression:
    primary-expression
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
 	|postfix-expression left_bracket expression right_bracket                      //like: arr[3]
 	|postfix-expression left_paren  right_paren                                //like: foo()、bar(1, 2)
    |postfix-expression left_paren expression-list right_paren
 	|simple-type-specifier left_paren  right_paren          
    |simple-type-specifier left_paren expression-list right_paren      //like: int(3.14)  3.14-->3
 	|postfix-expression dot   id-expression                   //like: obj.member
 	|postfix-expression arrow  id-expression                   //like: ptr->member
 	|postfix-expression double_add                                  //like: i++
 	|postfix-expression double_minus                                  //like: i--
    ;

primary-expression:                                                 //like: x、42、(a + b)
    literal
    {
        $$.type = $1.type;
        if($$.type == symbol_bool) $$.b_val = $1.b_val;
        else if($$.type == symbol_char) $$.c_val = $1.c_val;
        else if($$.type == symbol_double) $$.d_val = $1.d_val;
        else if($$.type == symbol_float) $$.f_val = $1.f_val;
        else if($$.type == symbol_int) $$.i_val = $1.i_val;
        else if($$.type == symbol_long) $$.l_val = $1.l_val;
        else if($$.type == symbol_short) $$.s_val = $1.s_val;
        else if($$.type == symbol_point) {$$.p_val = $1.p_val; $$.size = $1.size;}
    }
 	|left_paren expression right_paren
    {
        $$.type = $2.type;
        if($$.type == symbol_bool) $$.b_val = $2.b_val;
        else if($$.type == symbol_char) $$.c_val = $2.c_val;
        else if($$.type == symbol_double) $$.d_val = $2.d_val;
        else if($$.type == symbol_float) $$.f_val = $2.f_val;
        else if($$.type == symbol_int) $$.i_val = $2.i_val;
        else if($$.type == symbol_long) $$.l_val = $2.l_val;
        else if($$.type == symbol_short) $$.s_val = $2.s_val;
        else if($$.type == symbol_point) {$$.p_val = $2.p_val; $$.size = $2.size;}
    }
 	|id-expression
    {
        
    }
    ;
    
literal:	 
 	integer-literal
    {
        $$.type = $1.type; 
        $$.i_val = $1.i_val;
    }
 	|character-literal
    {
        $$.type = $1.type;
        $$.c_val = $1.c_val;
    }
 	|floating-literal
    {
        $$.type = $1.type;
        $$.f_val = $1.f_val;
    }
 	|string-literal
    {

    }
 	|boolean-literal
    {
        $$.type = $1.type; 
        $$.b_val = $1.b_val;   
    }
 	|pointer-literal
    {
        $$.type = $1.type;
        $$.p_val = $1.p_val;
    }
    ;

integer-literal:
    int_number
    {
        $$.type = symbol_int; 
        $$.i_val = $1;
    }
    ;

character-literal:
    single_quote one_char single_quote
    {
        $$.type = symbol_char; 
        $$.c_val = $2.name[0];
    }
    ;

floating-literal:
    float_number
    {
        $$.type = symbol_float; 
        $$.f_val = $1;
    }
    ;

string-literal:
    id-expression
    ;

boolean-literal:
    truesym
    {
        $$.type = symbol_bool; 
        $$.b_val = 1;
    }
    |falsesym
    {
        $$.type = symbol_bool; 
        $$.b_val = 0;
    }
    ;

pointer-literal:
	nullptr
    {
        $$.type = symbol_point;
        $$.p_val = NULL;
    }
    ;

id-expression:
	unqualified-id
    {
        $$.value = 0;
        $$.ptr_level = 0;
        $$.name = $1.name;
    }
 	|qualified-id
    ;

unqualified-id:
	identifier                                      //like: x count
    {
        $$.value = 0;
        $$.ptr_level = 0;
        $$.name = $1.name;
    }
    |one_char
    {
        $$.value = 0;
        $$.ptr_level = 0;
        $$.name = $1.name;
    }
    ;



qualified-id:
    ;

unary-operator:
    star
 	|solo_and
 	|plus
 	|minus
 	|logi_not
 	|bit_not
    ;

new-expression:
    ;

delete-expression:
  ;  


type-id:
    type-specifier-seq
    ;

type-specifier-seq:
    type-specifier
    |type-specifier type-specifier-seq
    ;



assignment-operator:
    equal
    |muti_equal
    |divi_equal
    |mod_equal
    |plus_equal
    |minus_equal
    |rshift_equal
    |lshift_equal
    |and_equal
    |xor_equal
    |or_equal
    ;

throw-expression:
    throwsym
    |throwsym assignment-expression
    ;

braced-init-list:
    ;

expression-list:
    initializer-list
    ;

initializer-list:
    initializer-clause 
 	|initializer-list comma initializer-clause
    ;

/*function definition*/
function-definition:

    decl-specifier-seq declarator function-body
    {  
        Is_Valid_Function($2.name);
        // Enter_Btab($1.type,$1.type_num,$1.basic_type,$2.name,$2.lastpar,last_index,$2.psize,var_point);      //enter btab;

    }
    ;

function-body:
    compound-statement                              
    ;

compound-statement:
    left_brace  right_brace
    |left_brace statement-seq right_brace                //like:   {return a + b;}
    ;

statement-seq:
    statement
 	|statement-seq statement
    ;

statement:                                                  //all statement
	labeled-statement                                       //like: label:, case, default.    use in goto or switch
    |expression-statement                                   //like: x = y + 1;   func();
 	|compound-statement                                     //like:   {return a + b;}  
 	|selection-statement                                    //like: if, if-else, switch
 	|iteration-statement                                    //like: for, while, do-while
 	|jump-statement                                         //like: return, break, continue, goto
 	|declaration-statement                                  //like: int x = 0;  double y = 3.14;
 	|try-block                                              //like: try catch 
    ;


labeled-statement:
 	identifier colon statement                              //like: start: x++; goto start;
 	|casesym constant-expression colon statement            //like: case 1: doSomething(); break;
 	|defaultsym colon statement                             //like:default: break;
    ;


expression-statement:                                       //like: x = y + 1;   func();
    semicolon
    |expression semicolon
    ;

selection-statement:
 	ifsym left_paren condition right_paren statement        //like: if(x = 0) y = 1;
 	|ifsym  left_paren condition right_paren statement elsesym statement //like: if(x = 0) y = 1; else y = 2;
 	|switchsym left_paren condition right_paren statement    //like: switch(x) case1: y=1; case2: y=2;
    ;

condition:
	expression                                              //like: x > 0
 	|decl-specifier-seq declarator equal initializer-clause //like: int x = get();
 	|decl-specifier-seq declarator braced-init-list         //like: int x{42};
    ;


iteration-statement:
	whilesym left_paren condition right_paren statement             //like: while(x == 0) { count++; }
 	|dosym statement whilesym left_paren expression right_paren semicolon   //like: do {count++;} while(x == 0);
 	|forsym left_paren for-init-statement  semicolon  right_paren statement    //like: for(int i = 0;) {}
    |forsym left_paren for-init-statement condition semicolon  right_paren statement    //like for(int i = 0;i < 10;) {}
    |forsym left_paren for-init-statement  semicolon expression right_paren statement   //like for(int i = 0;i++) {}
    |forsym left_paren for-init-statement condition semicolon expression right_paren statement  //like: for(int i = 0;i < 10;i++) {}
 	|forsym left_paren for-range-declaration : for-range-initializer right_paren statement      //like: for (auto& item : items) process(item);
    ;

for-init-statement:
    expression-statement
 	|simple-declaration
    ;

for-range-initializer:
    ;

jump-statement:
    breaksym semicolon                              //like: break;
 	|continuesym semicolon                          //like: continue;
 	|returnsym  semicolon                           //like: return;
    |returnsym expression semicolon                 //like: return x+y;
    |returnsym braced-init-list semicolon           //like: return {1};
 	|gotosym identifier semicolon                   //like: goto start;
    ;

declaration-statement:                              //like: int x;
    block-declaration           
    ;

try-block:
    trysym compound-statement handler-seq           //like: try{} catch(const std::exception& e){}
    ;

handler-seq:
    handler
 	|handler handler-seq
    ;

handler:
    ;


empty-declaration:
    semicolon
    ;

%%
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

    fp = fopen("output.asm", "w+");   

    /* yydebug = 1; */
    yyparse();
    Display_Nametab();



    fclose(f);
    return 0;
}