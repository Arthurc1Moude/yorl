/*
 * Yorl JSON Output Generator - Header
 */
#ifndef YORL_JSON_H
#define YORL_JSON_H

#include <stdio.h>

/* Forward declaration */
typedef struct ASTNode ASTNode;

/* AST Node structure (must match yorl.y) */
struct ASTNode {
    char *type;
    char *value;
    ASTNode **children;
    int child_count;
    int child_capacity;
};

/* JSON generation functions */
char* json_escape(const char* str);
void print_indent(FILE* fp, int indent);
void ast_to_json(FILE* fp, ASTNode* node, int indent);
void generate_json(FILE* fp, ASTNode* root);

#endif /* YORL_JSON_H */

/* JSON buffer functions */
void json_buffer_append(const char* str);
char* get_json_output(void);
void reset_json_buffer(void);
