#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// for lex
#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN,
    END,    // '\n'
    ENDFILE,
    INT,    // integer num
    ID,     // variable
    ADDSUB, // + or -
    MULDIV, // * or /
    ASSIGN, // = 
    LPAREN, // (
    RPAREN, // )
    INCDEC, // ++ or --
    AND,    // &
    OR,     // |
    XOR     // ^
} TokenSet;

TokenSet getToken(void);
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];

// Test if a token matches the current token
int match(TokenSet token);
// Get the next token
void advance(void);
// Get the lexeme of the current token
char *getLexeme(void);


// for parser
#define TBLSIZE 64
// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 1

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    printf("EXIT 1\n"); \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

int sbcount = 0;
Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
void initTable(void);
// Get the value of a variable
int getval(char *str);
// Set the value of a variable
int setval(char *str, int val);
//
int getvarnum(char *str);
// Make a new node according to token type and lexeme
BTNode *makeNode(TokenSet tok, const char *lexe);
// Free the syntax tree
void freeTree(BTNode *root);

BTNode *factor(void);
BTNode *unary_expr(void);
BTNode *muldiv_expr(void);
BTNode *muldiv_expr_tail(BTNode *left);
BTNode *addsub_expr(void);
BTNode *addsub_expr_tail(BTNode *left);
BTNode *and_expr(void);
BTNode *and_expr_tail(BTNode *left);
BTNode *xor_expr(void);
BTNode *xor_expr_tail(BTNode *left);
BTNode *or_expr(void);
BTNode *or_expr_tail(BTNode *left);
BTNode *assign_expr();
void statement(void);


// origine
/*
BTNode *factor(void);
BTNode *term(void);
BTNode *term_tail(BTNode *left);
BTNode *expr(void);
BTNode *expr_tail(BTNode *left);
*/

// Print error message and exit the program
void err(ErrorType errorNum);


// for codeGen
int regnum = 0;
// Evaluate the syntax tree
int evaluateTree(BTNode *root);
// Print the syntax tree in prefix
void printPrefix(BTNode *root);
// Print the assembly code
void printAssembly(BTNode *root, int regnum);
// check if there is ID
int hasID(BTNode *root);
/*============================================================================================
lex implementation
============================================================================================*/

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        i = 1;
        if (c == '+'){
            c = fgetc(stdin);
            if (c == '+'){
                lexeme[i] = c;
                i++;
                lexeme[i] = '\0';
                return INCDEC;
            }else{
                ungetc(c, stdin);
                lexeme[i] = '\0';
                return ADDSUB;
            }
        }else if (c == '-'){
            c = fgetc(stdin);
            if (c == '-'){
                lexeme[i] = c;
                i++;
                lexeme[i] = '\0';
                return INCDEC;
            }else{
                ungetc(c, stdin);
                lexeme[i] = '\0';
                return ADDSUB;
            }
        }
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isalpha(c) || isdigit(c) || c == '_') && i < MAXLEN){
           lexeme[i] = c;
           ++i;
           c = fgetc(stdin); 
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == '&'){
        lexeme[0] = c;
        lexeme[1] = '\0';
        return AND;
    } else if (c == '|') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return OR;
    } else if (c == '^') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return XOR;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}


/*============================================================================================
parser implementation
============================================================================================*/

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getval(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return 0;
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

int newvar = 0;
int getvarnum(char *str){
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return i;
    if(!newvar) error(SYNTAXERR);
    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return sbcount - 1;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}


// factor := INT | ID | INCDEC ID |
//           LPAREN assign_expr RPAREN
BTNode *factor(void){
    BTNode *retp = NULL, *left = NULL;

    if(match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) {
        retp = makeNode(ID, getLexeme());
        advance();
    } else if (match(INCDEC)) {
        retp = makeNode(INCDEC, getLexeme());
        advance();
        if (match(ID)) {
            retp->right = makeNode(ID, "1");
            retp->left = makeNode(ID, getLexeme());
            advance();
        } else {
            error(NOTNUMID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN)) {
            advance();
        } else {
            error(MISPAREN);
        }
    } else {
        error(NOTNUMID);
    }
    return retp;
}

// unary_expr := ADDSUB unary_expr | factor
BTNode *unary_expr(void){
    BTNode *retp = NULL;

    if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->left = makeNode(INT, "0");
        retp->right = unary_expr();
    } else {
        retp = factor();
    }
    return retp;
}

// muldiv_expr := unary_expr muldiv_expr_tail
BTNode *muldiv_expr(void){
    BTNode *node = unary_expr();
    return muldiv_expr_tail(node);
}

// muldiv_expr_tail := MULDIV unary_expr muldiv_expr_tail | NiL 
BTNode *muldiv_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = unary_expr();
        return muldiv_expr_tail(node);
    } else {
        return left;
    }
}

// addsub_expr := muldiv_expr addsub_expr_tail 
BTNode *addsub_expr(void){
    BTNode *node = muldiv_expr();
    return addsub_expr_tail(node);
}

// addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | NiL 
BTNode *addsub_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr();
        return addsub_expr_tail(node);
    } else {
        return left;
    }
}

// and_expr := addsub_expr and_expr_tail 
BTNode *and_expr(void){
    BTNode *node = addsub_expr();
    return and_expr_tail(node);
}

// and_expr_tail := AND addsub_expr and_expr_tail | NiL 
BTNode *and_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(AND)) {
        node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr();
        return and_expr_tail(node);
    } else {
        return left;
    }
}

// xor_expr := and_expr xor_expr_tail 
BTNode *xor_expr(void){
    BTNode *node = and_expr();
    return xor_expr_tail(node);
}

// xor_expr_tail := XOR and_expr xor_expr_tail | NiL 
BTNode *xor_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(XOR)) {
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        return xor_expr_tail(node);
    } else {
        return left;
    }
}

// or_expr := xor_expr or_expr_tail 
BTNode *or_expr(void){
    BTNode *node = xor_expr();
    return or_expr_tail(node);
}

// or_expr_tail := OR xor_expr or_expr_tail | NiL 
BTNode *or_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(OR)) {
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr();
        return or_expr_tail(node);
    } else {
        return left;
    }
}

// assign_expr := ID ASSIGN assign_expr | or_expr 
BTNode *assign_expr(){
    BTNode *node = NULL, *left = NULL;

    if (match(ID)) {
        left = or_expr();
        if(match(ASSIGN)){
            node = makeNode(ASSIGN, getLexeme());
            advance();
            if(left->data != ID) error(SYNTAXERR);
            node->left = left;
            node->right = assign_expr();
        } else if (match(END) || match(RPAREN)) {
            node = left;
        } else {
            if(match(INT) || match(ID)) error(SYNTAXERR);
            node = or_expr();
            node->left = left;
        }
    } else {
        node = or_expr(); 
    }
    return node;
}



// not share
// statement := END | assign_expr END 
void statement(void){
    BTNode *retp = NULL;

    if (match(END)) {
        //printf(">> ");
        advance();
    } else if (match(ENDFILE)) {
        printf("MOV r0 [0]\n");
        printf("MOV r1 [4]\n");
        printf("MOV r2 [8]\n");
        printf("EXIT 0\n");
        exit(0);
    } else {
        retp = assign_expr();
        if (match(END)) {
            /*
            printf("Prefix traversal: ");
            printPrefix(retp);
            printf("\n");
            */
            //evaluateTree(retp);
            printAssembly(retp, regnum);
            //printf("%d\n", evaluateTree(retp));
            
            freeTree(retp);
            //printf(">> ");
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    exit(0);
}


/*============================================================================================
codeGen implementation
============================================================================================*/


int hasID(BTNode *root){
    int a , b, c;
    a = b = c = 0;
    if(root->left) a = hasID(root->left);
    if(root->right) b = hasID(root->right);
    if(root->data == ID) c = 1;
    return (a || b || c);
}

int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme);
                break;
            case INT:
                retval = atoi(root->lexeme);
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);
                break;
            case ADDSUB:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                }
                break;
            case MULDIV:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0){
                        int isID = hasID(root->right);
                        if(!isID) error(DIVZERO);
                    }
                    retval = lv / rv;
                }
                break;
            case INCDEC:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "++") == 0) {
                    retval = setval(root->left->lexeme, lv+rv);
                } else if (strcmp(root->lexeme, "--") == 0) {
                    retval = setval(root->left->lexeme, lv-rv);
                }
                break;
            case AND:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                retval = lv & rv;
                break;
            case OR:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                retval = lv | rv;
                break;
            case XOR:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                retval = lv ^ rv;
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

void printAssembly(BTNode *root, int regnum) {
    int retval = 0, lv = 0, rv = 0;
    int varnum;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                varnum = 4 * getvarnum(root->lexeme);
                retval = getval(root->lexeme);
                printf("MOV r%d [%d]\n", regnum, varnum);
                break;
            case INT:
                retval = atoi(root->lexeme);
                printf("MOV r%d %d\n", regnum, retval);
                break;
            case ASSIGN:
                newvar = 1;
                varnum = 4 * getvarnum(root->left->lexeme);
                newvar = 0;
                printAssembly(root->right, regnum);
                printf("MOV [%d] r%d\n", varnum, regnum);
                break;
            case ADDSUB:
                printAssembly(root->left, regnum);
                printAssembly(root->right, regnum+1);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                    printf("ADD r%d r%d\n", regnum, regnum+1);
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                    printf("SUB r%d r%d\n", regnum, regnum+1);
                }
                break;
            case MULDIV:
                printAssembly(root->left, regnum);
                printAssembly(root->right, regnum+1);
                if (strcmp(root->lexeme, "*") == 0) {
                    printf("MUL r%d r%d\n", regnum, regnum+1);
                } else if (strcmp(root->lexeme, "/") == 0) {
                    rv = evaluateTree(root->right);
                    if (rv == 0){
                        lv = hasID(root->right);
                        if(!lv) error(DIVZERO);
                    }
                    printf("DIV r%d r%d\n", regnum, regnum+1);
                }
                break;
            case INCDEC:
                varnum = 4 * getvarnum(root->left->lexeme);
                printf("MOV r%d [%d]\n", regnum, varnum);
                printf("MOV r%d 1\n", regnum + 1);
                if (strcmp(root->lexeme, "++") == 0) {
                    printf("ADD r%d r%d\n", regnum, regnum+1);
                } else if (strcmp(root->lexeme, "--") == 0) {
                    printf("SUB r%d r%d\n", regnum, regnum+1);
                }
                printf("MOV [%d] r%d\n", varnum, regnum);
                break;
            case AND:
                printAssembly(root->left, regnum);
                printAssembly(root->right, regnum+1);
                printf("AND r%d r%d\n", regnum, regnum+1);
                break;
            case OR:
                printAssembly(root->left, regnum);
                printAssembly(root->right, regnum+1);
                printf("OR r%d r%d\n", regnum, regnum+1);
                break;
            case XOR:
                printAssembly(root->left, regnum);
                printAssembly(root->right, regnum+1);
                printf("XOR r%d r%d\n", regnum, regnum+1);
                break;
            default:
                retval = 0;
        }
    }
}
void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}


/*============================================================================================
main
============================================================================================*/

// This package is a calculator
// It works like a Python interpretor
// Example:
// >> y = 2
// >> z = 2
// >> x = 3 * y + 4 / (2 * z)
// It will print the answer of every line
// You should turn it into an expression compiler
// And print the assembly code according to the input

// This is the grammar used in this package
// You can modify it according to the spec and the slide
// statement  :=  ENDFILE | END | expr END
// expr    	  :=  term expr_tail
// expr_tail  :=  ADDSUB term expr_tail | NiL
// term 	  :=  factor term_tail
// term_tail  :=  MULDIV factor term_tail| NiL
// factor	  :=  INT | ADDSUB INT |
//		   	      ID  | ADDSUB ID  |
//		   	      ID ASSIGN expr |
//		   	      LPAREN expr RPAREN |
//		   	      ADDSUB LPAREN expr RPAREN

int main() {
    //freopen("input.txt", "w", stdout);
    initTable();
    //printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}
