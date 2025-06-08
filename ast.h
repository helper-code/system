#ifndef AST_H
#define AST_H

typedef enum {
    NODE_NUM,
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        int value; // for NODE_NUM
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
        } op; // for NODE_ADD, NODE_SUB, NODE_MUL, NODE_DIV
    };
} ASTNode;

// Function declarations
ASTNode* createNumNode(int value);
ASTNode* createOpNode(NodeType type, ASTNode* left, ASTNode* right);
void printAST(ASTNode* node, int indent);
void freeAST(ASTNode* node);

#endif
