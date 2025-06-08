#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

ASTNode* createNumNode(int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_NUM;
    node->value = value;
    return node;
}

ASTNode* createOpNode(NodeType type, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->op.left = left;
    node->op.right = right;
    return node;
}

void printAST(ASTNode* node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case NODE_NUM:
            printf("NUM: %d\n", node->value);
            break;
        case NODE_ADD:
            printf("ADD\n");
            break;
        case NODE_SUB:
            printf("SUB\n");
            break;
        case NODE_MUL:
            printf("MUL\n");
            break;
        case NODE_DIV:
            printf("DIV\n");
            break;
    }

    if (node->type != NODE_NUM) {
        printAST(node->op.left, indent + 1);
        printAST(node->op.right, indent + 1);
    }
}

void freeAST(ASTNode* node) {
    if (!node) return;
    if (node->type != NODE_NUM) {
        freeAST(node->op.left);
        freeAST(node->op.right);
    }
    free(node);
}
