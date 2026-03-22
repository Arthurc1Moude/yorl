%{
/*
 * Yorl Parser - Bison/Yacc specification
 * Modern parser for Yorl language
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yorl_json.h"
#include "version.h"

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern int line_num;

void yyerror(const char *s);
void generate_json(FILE* fp, ASTNode* root);

/* AST Node functions */
ASTNode* create_node(const char *type, const char *value);
void add_child(ASTNode *parent, ASTNode *child);
void print_ast(ASTNode *node, int indent);
void free_ast(ASTNode *node);

ASTNode *root = NULL;
%}

%union {
    int ival;
    float fval;
    char *str;
    struct ASTNode *node;
}

/* Token declarations */
%token <str> VERSION_DECL END_MARKER
%token <str> CLASS IMPORT FUNCTION EXPORT
%token <str> IDENTIFIER STRING PROPERTY
%token <str> URL PATH DEP SET CALL
%token <str> OBJECT PAREN_EXPR BRACKET_EXPR COLOR
%token <ival> NUMBER INDENT
%token <fval> FLOAT
%token EQUALS SEMICOLON COMMA COLON BACKSLASH NEWLINE

/* Non-terminal types */
%type <node> program
%type <node> version_decl
%type <node> statement_list statement
%type <node> import_stmt class_stmt function_stmt export_stmt
%type <node> class_header class_body
%type <node> property_list property
%type <node> config_block config_list config_item
%type <node> config_header config_properties
%type <node> function_header function_body function_stmt_list function_statement
%type <node> export_header export_options
%type <node> value object_value
%type <node> end_marker
%type <str> identifier

/* Operator precedence */
%left COMMA
%right EQUALS

%%

/* Grammar rules */

program:
    version_decl statement_list end_marker newlines {
        $$ = create_node("Program", NULL);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        root = $$;
    }
    | version_decl statement_list end_marker {
        $$ = create_node("Program", NULL);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        root = $$;
    }
    | version_decl statement_list {
        $$ = create_node("Program", NULL);
        add_child($$, $1);
        add_child($$, $2);
        root = $$;
    }
    ;

version_decl:
    VERSION_DECL STRING BACKSLASH newlines {
        $$ = create_node("Version", $2);
    }
    | VERSION_DECL identifier BACKSLASH newlines {
        $$ = create_node("Version", $2);
    }
    ;

statement_list:
    /* empty */ {
        $$ = create_node("StatementList", NULL);
    }
    | statement_list statement {
        $$ = $1;
        if ($2) add_child($$, $2);
    }
    ;

statement:
    import_stmt { $$ = $1; }
    | class_stmt { $$ = $1; }
    | function_stmt { $$ = $1; }
    | export_stmt { $$ = $1; }
    | newlines { $$ = NULL; }
    ;

import_stmt:
    IMPORT PATH property_list SEMICOLON newlines {
        $$ = create_node("Import", $2);
        add_child($$, $3);
    }
    | IMPORT PATH property_list newlines {
        $$ = create_node("Import", $2);
        add_child($$, $3);
    }
    ;

class_stmt:
    class_header class_body {
        $$ = $1;
        add_child($$, $2);
    }
    ;

class_header:
    CLASS property_list SEMICOLON newlines {
        $$ = create_node("Class", NULL);
        add_child($$, $2);
    }
    | CLASS property_list newlines {
        $$ = create_node("Class", NULL);
        add_child($$, $2);
    }
    ;

class_body:
    config_list {
        $$ = create_node("ClassBody", NULL);
        add_child($$, $1);
    }
    ;

config_list:
    /* empty */ {
        $$ = create_node("ConfigList", NULL);
    }
    | config_list config_block {
        $$ = $1;
        add_child($$, $2);
    }
    | config_list newlines {
        $$ = $1;
        /* Skip empty lines */
    }
    ;

config_block:
    INDENT IDENTIFIER newlines {
        $$ = create_node("ConfigBlock", $2);
    }
    | INDENT IDENTIFIER newlines newlines config_list {
        $$ = create_node("ConfigBlock", $2);
        add_child($$, $5);
    }
    | INDENT IDENTIFIER newlines config_list {
        $$ = create_node("ConfigBlock", $2);
        add_child($$, $4);
    }
    | INDENT IDENTIFIER property_list SEMICOLON newlines {
        $$ = create_node("ConfigItem", $2);
        add_child($$, $3);
    }
    | INDENT IDENTIFIER property_list newlines {
        $$ = create_node("ConfigItem", $2);
        add_child($$, $3);
    }
    | INDENT IDENTIFIER property_list SEMICOLON newlines config_list {
        $$ = create_node("ConfigItem", $2);
        add_child($$, $3);
        add_child($$, $6);
    }
    | INDENT IDENTIFIER property_list newlines config_list {
        $$ = create_node("ConfigItem", $2);
        add_child($$, $3);
        add_child($$, $5);
    }
    ;

config_properties:
    property_list {
        $$ = create_node("ConfigProperties", NULL);
        add_child($$, $1);
    }
    ;

function_stmt:
    function_header function_body {
        $$ = $1;
        add_child($$, $2);
    }
    ;

function_header:
    FUNCTION property_list SEMICOLON newlines {
        $$ = create_node("Function", NULL);
        add_child($$, $2);
    }
    | FUNCTION property_list newlines {
        $$ = create_node("Function", NULL);
        add_child($$, $2);
    }
    ;

function_body:
    function_stmt_list {
        $$ = create_node("FunctionBody", NULL);
        add_child($$, $1);
    }
    ;

function_stmt_list:
    /* empty */ {
        $$ = create_node("FunctionStatements", NULL);
    }
    | function_stmt_list INDENT function_statement SEMICOLON newlines {
        $$ = $1;
        add_child($$, $3);
    }
    | function_stmt_list INDENT function_statement newlines {
        $$ = $1;
        add_child($$, $3);
    }
    ;

function_statement:
    SET EQUALS value {
        $$ = create_node("SetStatement", $1);
        add_child($$, $3);
    }
    | CALL property_list {
        $$ = create_node("CallStatement", $1);
        add_child($$, $2);
    }
    ;

export_stmt:
    export_header export_options SEMICOLON newlines {
        $$ = $1;
        add_child($$, $2);
    }
    | export_header export_options newlines {
        $$ = $1;
        add_child($$, $2);
    }
    ;

export_header:
    EXPORT identifier {
        $$ = create_node("Export", $2);
    }
    | EXPORT CLASS OBJECT {
        char* combined = malloc(strlen("class.") + strlen($3) + 3);
        sprintf(combined, "class.{%s}", $3);
        $$ = create_node("Export", combined);
        free(combined);
    }
    | EXPORT FUNCTION OBJECT {
        char* combined = malloc(strlen("function.") + strlen($3) + 3);
        sprintf(combined, "function.{%s}", $3);
        $$ = create_node("Export", combined);
        free(combined);
    }
    | EXPORT IDENTIFIER OBJECT {
        char* combined = malloc(strlen($2) + strlen($3) + 3);
        sprintf(combined, "%s.{%s}", $2, $3);
        $$ = create_node("Export", combined);
        free(combined);
    }
    | EXPORT {
        $$ = create_node("Export", NULL);
    }
    ;

export_options:
    property_list {
        $$ = create_node("ExportOptions", NULL);
        add_child($$, $1);
    }
    ;

property_list:
    /* empty */ {
        $$ = create_node("PropertyList", NULL);
    }
    | property_list property {
        $$ = $1;
        add_child($$, $2);
    }
    ;

property:
    PROPERTY EQUALS value {
        $$ = create_node("Property", $1);
        add_child($$, $3);
    }
    | PROPERTY EQUALS OBJECT {
        $$ = create_node("Property", $1);
        ASTNode *val = create_node("Object", $3);
        add_child($$, val);
    }
    | PROPERTY EQUALS BRACKET_EXPR {
        $$ = create_node("Property", $1);
        ASTNode *val = create_node("BracketExpr", $3);
        add_child($$, val);
    }
    | PROPERTY value {
        $$ = create_node("Property", $1);
        add_child($$, $2);
    }
    | PROPERTY PAREN_EXPR {
        $$ = create_node("Property", $1);
        ASTNode *val = create_node("ParenExpr", $2);
        add_child($$, val);
    }
    | PROPERTY BRACKET_EXPR {
        $$ = create_node("Property", $1);
        ASTNode *val = create_node("BracketExpr", $2);
        add_child($$, val);
    }
    | PROPERTY OBJECT {
        $$ = create_node("Property", $1);
        ASTNode *val = create_node("Object", $2);
        add_child($$, val);
    }
    | PROPERTY {
        $$ = create_node("Property", $1);
    }
    | SET EQUALS value {
        $$ = create_node("SetProperty", $1);
        add_child($$, $3);
    }
    | SET value {
        $$ = create_node("SetProperty", $1);
        add_child($$, $2);
    }
    | SET {
        $$ = create_node("SetProperty", $1);
    }
    ;

value:
    STRING { $$ = create_node("String", $1); }
    | NUMBER { 
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", $1);
        $$ = create_node("Number", buf); 
    }
    | FLOAT { 
        char buf[32];
        snprintf(buf, sizeof(buf), "%f", $1);
        $$ = create_node("Float", buf); 
    }
    | COLOR { $$ = create_node("Color", $1); }
    | URL { $$ = create_node("URL", $1); }
    | PATH { $$ = create_node("Path", $1); }
    | DEP { $$ = create_node("Dependency", $1); }
    | OBJECT { $$ = create_node("Object", $1); }
    | CLASS { $$ = create_node("Identifier", "class"); }
    | CLASS PAREN_EXPR { 
        char* combined = malloc(strlen("class") + strlen($2) + 10);
        sprintf(combined, "class(%s)", $2);
        $$ = create_node("Identifier", combined);
        free(combined);
    }
    | identifier { $$ = create_node("Identifier", $1); }
    | identifier PAREN_EXPR { 
        char* combined = malloc(strlen($1) + strlen($2) + 10);
        sprintf(combined, "%s(%s)", $1, $2);
        $$ = create_node("Identifier", combined);
        free(combined);
    }
    ;

object_value:
    OBJECT {
        $$ = create_node("Object", $1);
    }
    ;

identifier:
    IDENTIFIER { $$ = $1; }
    | IDENTIFIER IDENTIFIER {
        char *combined = malloc(strlen($1) + strlen($2) + 2);
        sprintf(combined, "%s %s", $1, $2);
        $$ = combined;
    }
    ;

end_marker:
    END_MARKER {
        $$ = create_node("EndMarker", NULL);
    }
    | END_MARKER identifier {
        $$ = create_node("EndMarker", $2);
    }
    | END_MARKER identifier EQUALS identifier {
        char* combined = malloc(strlen($2) + strlen($4) + 10);
        sprintf(combined, "%s=%s", $2, $4);
        $$ = create_node("EndMarker", combined);
        free(combined);
    }
    | END_MARKER identifier EQUALS identifier identifier {
        char* combined = malloc(strlen($2) + strlen($4) + strlen($5) + 10);
        sprintf(combined, "%s=%s%s", $2, $4, $5);
        $$ = create_node("EndMarker", combined);
        free(combined);
    }
    ;

newlines:
    NEWLINE
    | newlines NEWLINE
    ;

%%

/* AST Node implementation */

ASTNode* create_node(const char *type, const char *value) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = strdup(type);
    node->value = value ? strdup(value) : NULL;
    node->children = NULL;
    node->child_count = 0;
    node->child_capacity = 0;
    return node;
}

void add_child(ASTNode *parent, ASTNode *child) {
    if (!child) return;
    
    if (parent->child_count >= parent->child_capacity) {
        parent->child_capacity = parent->child_capacity == 0 ? 4 : parent->child_capacity * 2;
        parent->children = (ASTNode**)realloc(parent->children, 
                                              parent->child_capacity * sizeof(ASTNode*));
    }
    parent->children[parent->child_count++] = child;
}

void print_ast(ASTNode *node, int indent) {
    if (!node) return;
    
    for (int i = 0; i < indent; i++) printf("  ");
    printf("%s", node->type);
    if (node->value) printf(": %s", node->value);
    printf("\n");
    
    for (int i = 0; i < node->child_count; i++) {
        print_ast(node->children[i], indent + 1);
    }
}

void free_ast(ASTNode *node) {
    if (!node) return;
    
    free(node->type);
    if (node->value) free(node->value);
    
    for (int i = 0; i < node->child_count; i++) {
        free_ast(node->children[i]);
    }
    
    if (node->children) free(node->children);
    free(node);
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse error at line %d: %s\n", line_num, s);
}

int main(int argc, char **argv) {
    int json_output = 0;
    int show_version = 0;
    char* input_file = NULL;
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--json") == 0) {
            json_output = 1;
        } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            show_version = 1;
        } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            printf("%s\n\n", get_yorl_full_version());
            printf("Usage: %s [options] <file.yorl>\n\n", argv[0]);
            printf("Options:\n");
            printf("  --json        Output JSON format\n");
            printf("  --version, -v Show version information\n");
            printf("  --help, -h    Show this help message\n");
            printf("\nComments:\n");
            printf("  ! comment     Line comment (until end of line)\n");
            printf("  /em+1         Exception mark (literal !)\n");
            printf("  /em+N         Exception mark N\n");
            printf("\nExamples:\n");
            printf("  %s file.yorl           # Parse and show AST\n", argv[0]);
            printf("  %s --json file.yorl    # Output JSON\n", argv[0]);
            printf("  %s --version           # Show version\n", argv[0]);
            return 0;
        } else if (argv[i][0] != '-') {
            input_file = argv[i];
        }
    }
    
    if (show_version) {
        printf("%s\n", get_version_info());
        return 0;
    }
    
    if (input_file) {
        FILE *file = fopen(input_file, "r");
        if (!file) {
            perror(input_file);
            return 1;
        }
        yyin = file;
    }
    
    if (!json_output) {
        printf("%s\n", get_yorl_full_version());
        printf("==========================================\n\n");
    }
    
    int result = yyparse();
    
    if (result == 0 && root) {
        if (json_output) {
            // Output JSON format
            generate_json(stdout, root);
        } else {
            // Output AST tree
            printf("\n=== Abstract Syntax Tree ===\n");
            print_ast(root, 0);
            printf("\n=== Parse Successful ===\n");
        }
        free_ast(root);
    } else {
        if (!json_output) {
            printf("\n=== Parse Failed ===\n");
        }
    }
    
    if (input_file) {
        fclose(yyin);
    }
    
    return result;
}
