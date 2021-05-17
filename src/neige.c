#include "include/neige.h"
#include "include/lexer.h"
#include "include/token.h"

void neige_compile (char* source){
  neige_lexer_t *lexer = initialize_lexer(source);
  neige_token_t *token = 0;

  while ((token = lexer_next_token(lexer)->token_value != TOKEN_EOF)){
    printf("TOKEN: %s\n", token->content);
  }
  printf("FINISHED \n");
}
