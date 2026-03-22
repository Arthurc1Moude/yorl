%{
/*
 * Yorl Lexer - Flex/Lex specification
 * Modern lexical analyzer for Yorl language
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "yorl.tab.h"

int line_num = 1;
int col_num = 1;

#define YY_USER_ACTION col_num += yyleng;

/* Function declarations */
void yyerror(const char *s);
char* strip_quotes(char* str);
char* process_exception_marks(char* str);
char* strdup(const char *s);

/* Windows compatibility for strndup */
#ifndef strndup
char* strndup(const char *s, size_t n) {
    size_t len = strlen(s);
    if (n < len) len = n;
    char *result = (char*)malloc(len + 1);
    if (result) {
        memcpy(result, s, len);
        result[len] = '\0';
    }
    return result;
}
#endif
%}

%option noyywrap
%option yylineno

/* Definitions */
DIGIT       [0-9]
LETTER      [a-zA-Z]
ALPHANUM    [a-zA-Z0-9]
HEXDIGIT    [0-9a-fA-F]
WHITESPACE  [ \t\r]
NEWLINE     \n

/* Start conditions for multi-line handling */
%x COMMENT
%x LINE_COMMENT

%%

    /* Indented comments - skip indent and comment */
^{WHITESPACE}+"!"[^\n]* { /* Ignore indented comment lines completely */ }

    /* Comments - ! starts a comment until end of line */
"!"[^\n]*               { /* Ignore line comments completely */ }

    /* Exception marks - /em+N represents special characters */
"/em+1"                 { yylval.str = strdup("!"); return STRING; }
"/em+"[0-9]+            { 
                          /* Future exception marks */
                          int em_num = atoi(yytext + 4);
                          char buf[8];
                          snprintf(buf, sizeof(buf), "/em+%d", em_num);
                          yylval.str = strdup(buf);
                          return STRING;
                        }

    /* Version declaration - capture entire version line */
"^yorl"[ \t]+               { return VERSION_DECL; }

    /* Version number pattern - must come before FLOAT */
{DIGIT}+"."{DIGIT}+"."{DIGIT}+("-"{DIGIT}+)? { 
                          yylval.str = strdup(yytext);
                          return STRING; 
                        }

"^END_OF_YORL"              { return END_MARKER; }
    /* Keywords */
"class"                 { return CLASS; }
"import"                { return IMPORT; }
"function"              { return FUNCTION; }
"export"                { return EXPORT; }

    /* Special @ syntax */
"@url{"[^}]*"}"         { 
                          yylval.str = strndup(yytext + 5, yyleng - 6);
                          return URL; 
                        }
"@path{"[^}]*"}"        { 
                          yylval.str = strndup(yytext + 6, yyleng - 7);
                          return PATH; 
                        }
"@dep{"[^}]*"}"         { 
                          yylval.str = strndup(yytext + 5, yyleng - 6);
                          return DEP; 
                        }
"@set."[a-zA-Z0-9_.{}]*  { 
                          yylval.str = strdup(yytext);
                          return SET; 
                        }
"@call."[a-zA-Z0-9_.{}]* { 
                          yylval.str = strdup(yytext);
                          return CALL; 
                        }

    /* Object literals - process /em+ inside {} */
"{"[^}]*"}"             { 
                          char* content = strndup(yytext + 1, yyleng - 2);
                          /* Process exception marks in object content */
                          yylval.str = process_exception_marks(content);
                          free(content);
                          return OBJECT; 
                        }

    /* Strings */
'([^'\\]|\\.)*'         { 
                          yylval.str = strip_quotes(yytext);
                          return STRING; 
                        }
\"([^\"\\]|\\.)*\"      { 
                          yylval.str = strip_quotes(yytext);
                          return STRING; 
                        }

    /* Parenthesized expressions - NO /em+ processing (new rule) */
"("[^)]*")"             { 
                          yylval.str = strndup(yytext + 1, yyleng - 2);
                          return PAREN_EXPR; 
                        }

    /* Property with parenthesized value: -(key=value) */
"-""("[^)]*")"          { 
                          /* Return dash as property marker, then paren expr will follow */
                          yyless(1); /* Put back everything except the dash */
                          yylval.str = strdup("");
                          return PROPERTY;
                        }

    /* Bracketed expressions */
"["[^\]]*"]"            { 
                          yylval.str = strndup(yytext + 1, yyleng - 2);
                          return BRACKET_EXPR; 
                        }

    /* Numbers */
{DIGIT}+"."{DIGIT}+     { 
                          yylval.fval = atof(yytext);
                          return FLOAT; 
                        }
{DIGIT}+"-"{DIGIT}+"-"{DIGIT}+ { 
                          yylval.str = strdup(yytext);
                          return STRING; 
                        }
{DIGIT}+                { 
                          yylval.ival = atoi(yytext);
                          return NUMBER; 
                        }

    /* Color codes */
"#"{HEXDIGIT}{6}        { 
                          yylval.str = strdup(yytext);
                          return COLOR; 
                        }

    /* Identifiers and config blocks */
"."{ALPHANUM}[a-zA-Z0-9_.-]* { 
                          yylval.str = strdup(yytext);
                          return IDENTIFIER; 
                        }
{LETTER}{ALPHANUM}*     { 
                          yylval.str = strdup(yytext);
                          return IDENTIFIER; 
                        }

    /* Properties (start with dash) - capture only the key, not =value */
"-"{ALPHANUM}[a-zA-Z0-9_.]* { 
                          yylval.str = strdup(yytext + 1);
                          return PROPERTY; 
                        }

    /* Operators and punctuation */
"="                     { return EQUALS; }
";"                     { return SEMICOLON; }
","                     { return COMMA; }
":"                     { return COLON; }
"\\"                    { return BACKSLASH; }

    /* Blank lines - ignore completely */
^{WHITESPACE}*{NEWLINE} { 
                          line_num++;
                          col_num = 1;
                          /* Don't return NEWLINE for blank lines */
                        }

    /* Indentation - count spaces at start of line */
^{WHITESPACE}+          { 
                          yylval.ival = yyleng;
                          return INDENT; 
                        }

    /* Whitespace (not at start of line) */
{WHITESPACE}+           { /* ignore */ }

    /* Newline */
{NEWLINE}               { 
                          line_num++;
                          col_num = 1;
                          return NEWLINE; 
                        }

    /* Catch-all for unknown characters */
.                       { 
                          /* Silently ignore unknown characters in permissive mode */
                        }

%%

/* Helper function to strip quotes from strings */
char* strip_quotes(char* str) {
    int len = strlen(str);
    char* result = (char*)malloc(len - 1);
    strncpy(result, str + 1, len - 2);
    result[len - 2] = '\0';
    return result;
}

/* Helper function to process exception marks in strings */
char* process_exception_marks(char* str) {
    if (!str) return NULL;
    
    char* result = (char*)malloc(strlen(str) * 2 + 1);
    char* dst = result;
    char* src = str;
    
    while (*src) {
        if (strncmp(src, "/em+", 4) == 0) {
            /* Found exception mark */
            src += 4;
            int em_num = 0;
            while (*src >= '0' && *src <= '9') {
                em_num = em_num * 10 + (*src - '0');
                src++;
            }
            
            /* Convert exception mark to actual character */
            switch (em_num) {
                case 1: *dst++ = '!'; break;  /* /em+1 = ! */
                case 2: *dst++ = '@'; break;  /* /em+2 = @ */
                case 3: *dst++ = '#'; break;  /* /em+3 = # */
                case 4: *dst++ = '$'; break;  /* /em+4 = $ */
                case 5: *dst++ = '%'; break;  /* /em+5 = % */
                case 6: *dst++ = '^'; break;  /* /em+6 = ^ */
                case 7: *dst++ = '&'; break;  /* /em+7 = & */
                case 8: *dst++ = '*'; break;  /* /em+8 = * */
                case 9: *dst++ = '('; break;  /* /em+9 = ( */
                case 10: *dst++ = ')'; break; /* /em+10 = ) */
                default:
                    /* Unknown exception mark - keep as is */
                    sprintf(dst, "/em+%d", em_num);
                    dst += strlen(dst);
                    break;
            }
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
    
    return result;
}
