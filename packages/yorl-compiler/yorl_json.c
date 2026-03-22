/*
 * Yorl JSON Output Generator
 * Converts AST to JSON format
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yorl_json.h"

/* Escape string for JSON */
char* json_escape(const char* str) {
    if (!str) return strdup("null");
    
    size_t len = strlen(str);
    char* escaped = malloc(len * 2 + 3); // Worst case: all chars need escaping
    char* p = escaped;
    
    *p++ = '"';
    for (size_t i = 0; i < len; i++) {
        switch (str[i]) {
            case '"':  *p++ = '\\'; *p++ = '"'; break;
            case '\\': *p++ = '\\'; *p++ = '\\'; break;
            case '\n': *p++ = '\\'; *p++ = 'n'; break;
            case '\r': *p++ = '\\'; *p++ = 'r'; break;
            case '\t': *p++ = '\\'; *p++ = 't'; break;
            default:   *p++ = str[i]; break;
        }
    }
    *p++ = '"';
    *p = '\0';
    
    return escaped;
}

/* Print indentation */
void print_indent(FILE* fp, int indent) {
    for (int i = 0; i < indent; i++) {
        fprintf(fp, "  ");
    }
}

/* Print AST node as JSON */
void ast_to_json(FILE* fp, ASTNode* node, int indent) {
    if (!node) {
        fprintf(fp, "null");
        return;
    }
    
    fprintf(fp, "{\n");
    
    // Print type
    print_indent(fp, indent + 1);
    fprintf(fp, "\"type\": %s", json_escape(node->type));
    
    // Print value if present
    if (node->value) {
        fprintf(fp, ",\n");
        print_indent(fp, indent + 1);
        fprintf(fp, "\"value\": %s", json_escape(node->value));
    }
    
    // Print children if present
    if (node->child_count > 0) {
        fprintf(fp, ",\n");
        print_indent(fp, indent + 1);
        fprintf(fp, "\"children\": [\n");
        
        for (int i = 0; i < node->child_count; i++) {
            print_indent(fp, indent + 2);
            ast_to_json(fp, node->children[i], indent + 2);
            
            if (i < node->child_count - 1) {
                fprintf(fp, ",");
            }
            fprintf(fp, "\n");
        }
        
        print_indent(fp, indent + 1);
        fprintf(fp, "]");
    }
    
    fprintf(fp, "\n");
    print_indent(fp, indent);
    fprintf(fp, "}");
}

/* Generate JSON output from AST */
void generate_json(FILE* fp, ASTNode* root) {
    ast_to_json(fp, root, 0);
    fprintf(fp, "\n");
}
