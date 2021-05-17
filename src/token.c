#include "include/token.h"
#include <stdlib.h>
#include <stdio.h>

neige_token_t *initialize_token (char *content, enum token_type type){
  neige_token_t *token = calloc(1, sizeof(struct TOKEN));

  token->content = content;
  token->token_value = type;

  return token;
}

void print_token (neige_token_t *token){
  printf("TOKEN value: %s  -> type %d\n", token->content, token->token_value);
}