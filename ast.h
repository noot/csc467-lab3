
#ifndef AST_H_
#define AST_H_ 1

#include <stdarg.h>

// Dummy node just so everything compiles, create your own node/nodes
//
// The code provided below is an example ONLY. You can use/modify it,
// but do not assume that it is correct or complete.
//
// There are many ways of making AST nodes. The approach below is an example
// of a descriminated union.
//

// Forward declarations
struct node_;
typedef struct node_ node;
extern node *ast;

typedef enum {
  UNKNOWN               = 0,

  SCOPE_NODE            = (1 << 0),

  DECLARATIONS_NODE     = (1 << 1),
  STATEMENTS_NODE       = (1 << 1) | (1 << 2),
  DECLARATION_NODE      = (1 << 1) | (1 << 3),
  STATEMENT_NODE        = (1 << 1) | (1 << 4),
  ELSE_STATEMENT_NODE   = (1 << 1) | (1 << 5),

  EXP_NODE              = (1 << 2),
  VAR_NODE              = (1 << 2) | (1 << 3),
  UNARY_OP_NODE  = (1 << 2) | (1 << 4),
  CONSTRUCTOR_NODE      = (1 << 2) | (1 << 5),
  FUNCTION_NODE         = (1 << 2) | (1 << 6),
  FUNCTION_NAME_NODE    = (1 << 2) | (1 << 7), // don't know if we need this
  ARGUMENTS_OPT_NODE    = (1 << 2) | (1 << 8),
  ARGUMENTS_NODE        = (1 << 2) | (1 << 9),

  INT_NODE              = (1 << 2) | (1 << 10), 
  FLOAT_NODE            = (1 << 2) | (1 << 11),
  IDENT_NODE            = (1 << 2) | (1 << 12),
  TYPE_NODE             = (1 << 2) | (1 << 13),
  BOOL_NODE             = (1 << 2) | (1 << 14),

  //IF_STATEMENT_NODE     = (1 << 1) | (1 << 11),
  //WHILE_STATEMENT_NODE  = (1 << 1) | (1 << 12),
  ASSIGNMENT_NODE       = (1 << 1) | (1 << 15),
  NESTED_SCOPE_NODE     = (1 << 1) | (1 << 16)
} node_kind;

struct node_ {

  // an example of tagging each node with a type
  node_kind kind;

  union {
    struct { 
      node *declarations;
      node *statements;
    } scope;

    struct {
      node *declarations;
      node *declaration;
    } declarations;

    struct {
      node *statements;
      node *statement;
    } statements;

    struct {
      bool is_const;
      char *id;
      node *type;
      node *exp;
    } declaration;

    struct {

    } statement;

    struct {

    } else_statement;

    struct {

    } type;

    struct {

    } exp;

    struct {

    } variable;

    struct {
      int op;
      node *right;
    } unary_expr;

    struct {

    } constructor;

    struct {

    } function;

    struct {

    } function_name;

    struct {

    } arguments_opt;

    struct {

    } arguments;
    // struct {
    //   int op;
    //   node *left;
    //   node *right;
    // } binary_expr;
  };
};

node *ast_allocate(node_kind type, ...);
void ast_free(node *ast);
void ast_print(node * ast);
int semantic_check(node * ast);

#endif /* AST_H_ */
