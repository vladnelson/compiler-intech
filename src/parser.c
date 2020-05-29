#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include "symbol.h"
#include "buffer.h"
#include "parser.h"
#include "ast.h"
#include "utils.h"
#include "stack.h"
#include "lexer.h"

#define DEBUG true

extern symbol_t **pglobal_table;
extern ast_t **past;

ast_list_t *parse_parameters(buffer_t *buffer)
{

  //char currentchar = buf_getchar(buffer);
  // printf("Param => char %d\n", currentchar);
  //char type = NULL;
  //har nameType = NULL;
  char *type = lexer_getalphanum(buffer);
  char *nameType = NULL;
  ast_t *typeFirstParam = NULL;
  ast_list_t *listofParam = NULL;
  if (type != "")
  {
    buf_skipblank(buffer);
    nameType = lexer_getalphanum(buffer);
    printf("Hee => %s\n", type);
    printf("Hee => %s\n", nameType);
    typeFirstParam = ast_new_variable(nameType, 2);
  }
  if (typeFirstParam != NULL)
  {
    listofParam = ast_list_new_node(typeFirstParam);
    buf_skipblank(buffer);
    char nextchar = buf_getchar(buffer);
    printf("nextchar => %d\n", nextchar);

    if (nextchar == 44)
    { //  virgule
      while (nextchar != 41)
      {
        buf_skipblank(buffer);
        char *typeorder = lexer_getalphanum(buffer);
         printf("nextchar => %s\n", typeorder);
        buf_skipblank(buffer);
        char *nameTypeorder = lexer_getalphanum(buffer);
         printf("nextchar => %s\n", nameTypeorder);
        ast_t *newtparam = ast_new_variable( nameTypeorder, 2);
        listofParam = ast_list_add(&listofParam, newtparam);
        
        buf_skipblank(buffer);
        nextchar = buf_getchar(buffer);
      }
    }
  }

  return listofParam;
}

int parse_return_type(buffer_t *buffer)
{
  return 2;
}

ast_list_t *parse_function_body(buffer_t *buffer)
{
  return NULL;
}

ast_t *parse_function(buffer_t *buffer)
{
  char *beforechar = lexer_getalphanum(buffer);
  char currentchar = buf_getchar(buffer);

  while (currentchar != 40)
  {
    beforechar = lexer_getalphanum(buffer);
    buf_skipblank(buffer);
    currentchar = buf_getchar(buffer);
  }

  char *name = beforechar;
  printf("Nom de la fonction => %s \n", name);

  ast_list_t *params = parse_parameters(buffer);
  int return_type = parse_return_type(buffer);
  ast_list_t *stmts = parse_function_body(buffer);

  return ast_new_function(name, return_type, params, stmts);
}

/**
 * This function generates ASTs for each global-scope function
 */
ast_list_t *parse(buffer_t *buffer)
{
  ast_t *function = parse_function(buffer);
  ast_print(function);
  // TODO
  if (DEBUG)
    printf("** end of file. **\n");
  return NULL;
}
