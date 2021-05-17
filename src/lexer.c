#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

neige_lexer_t* initialize_lexer (char *content){
  neige_lexer_t *lexer = calloc(1, sizeof(struct LEXER));

  lexer->content = content;
  lexer->content_size = strlen(content);
  lexer->current_index = 0;
  lexer->current_character = content[0];

  return lexer;
}

void lexer_advance(neige_lexer_t *lexer){
  if (lexer->current_index < lexer->content_size && lexer->current_character != EOF_CHARACTER){
    lexer->current_index += 1;
    lexer->current_character = lexer->content[lexer->current_index];
  }
}

void lexer_ignore_whitespaces (neige_lexer_t *lexer){
  while (lexer->current_character == NEW_LINE_CHARACTER || lexer->current_character == WHITE_SPACE_CHARACTER || 
         lexer->current_character == TAB_CHARACTER || lexer->current_character == CARRIAGE_RETURN_CHARACTER){
    lexer_advance(lexer);
  }
}

neige_token_t *lexer_parse_id (neige_lexer_t *lexer){
  char *current_content = calloc(1, sizeof(char));

  while(isalpha(lexer->current_character)){
    current_content = realloc(current_content, (strlen(current_content) + 1 + 1) * sizeof(char));
    strcat(current_content, (char[2]){lexer->current_character, EOF_CHARACTER});
    lexer_advance(lexer);
  }
  
  return initialize_token(current_content, TOKEN_ID);
}

neige_token_t *lexer_parse_number (neige_lexer_t *lexer){
  char *current_content = calloc(1, sizeof(char));

  while(isdigit(lexer->current_character)){
    current_content = realloc(current_content, (strlen(current_content) + 1 + 1) * sizeof(char));
    strcat(current_content, (char[2]){lexer->current_character, EOF_CHARACTER});
    lexer_advance(lexer);
  }
  
  return initialize_token(current_content, TOKEN_INT);
}

neige_token_t *lexer_advance_with (neige_lexer_t *lexer, neige_token_t *token){
  lexer_advance(lexer);
  return token;
}

neige_token_t *lexer_next_token (neige_lexer_t *lexer){
  while (lexer->current_character != EOF_CHARACTER){
    lexer_ignore_whitespaces(lexer);
    if (isalpha(lexer->current_character)){
      return lexer_advance_with(lexer, lexer_parse_id(lexer));
    }
    if (isdigit(lexer->current_character)){
      return lexer_advance_with(lexer, lexer_parse_number(lexer));
    }

    switch(lexer->current_character){
      case EOF_CHARACTER: return initialize_token(0, TOKEN_EOF); break;
      case '=': {
        char next_character = lexer_peek(lexer, 1);
        if (next_character == '>'){
          return lexer_advance_with(lexer, initialize_token("=>", TOKEN_THICK_ARROW));
        }
        else if (next_character == '='){
          return lexer_advance_with(lexer, initialize_token("==", TOKEN_BOOL_EQUALS));
        }
        else {
          return lexer_advance_with(lexer, initialize_token("=", TOKEN_ASSIGN));
        }
      } break;

      case '<': {
        char next_character = lexer_peek(lexer, 1);
        if (next_character == '='){
          return lexer_advance_with(lexer, initialize_token("<=", TOKEN_BOOL_LESS_THAN_EQUAL));
        }
        else if (next_character == '<'){
          return lexer_advance_with(lexer, initialize_token("<<", TOKEN_BITWISE_LEFT_SHIFT));
        }
        else {
          return lexer_advance_with(lexer, initialize_token("<", TOKEN_BOOL_LESS_THAN));
        }
      } break;

      case '>': {
        char next_character = lexer_peek(lexer, 1);
        if (next_character == '='){
          return lexer_advance_with(lexer, initialize_token(">=", TOKEN_BOOL_GREATER_THAN_EQUAL));
        }
        else if (next_character == '>'){
          return lexer_advance_with(lexer, initialize_token(">>", TOKEN_BITWISE_RIGHT_SHIFT));
        }
        else {
          return lexer_advance_with(lexer, initialize_token(">", TOKEN_BOOL_GREATER_THAN));
        }
      } break;

      case '!': {
        if (lexer_peek(lexer, 1) == '='){
          return lexer_advance_with(lexer, initialize_token("!=", TOKEN_BOOL_NOT_EQUALS));
        }
        return lexer_advance_with(lexer, initialize_token("!", TOKEN_BITWISE_NOT));
      } break;

      case '{': return lexer_advance_with(lexer, initialize_token("{", TOKEN_LEFT_PARENTHESIS)); break;
      case '}': return lexer_advance_with(lexer, initialize_token("}", TOKEN_RIGHT_PARENTHESIS)); break;

      case '[': return lexer_advance_with(lexer, initialize_token("[", TOKEN_LEFT_SQUARE_BRACKET)); break;
      case ']': return lexer_advance_with(lexer, initialize_token("]", TOKEN_RIGHT_SQUARE_BRACKET)); break;

      case '(': return lexer_advance_with(lexer, initialize_token("(", TOKEN_LEFT_BRACKET)); break;
      case ')': return lexer_advance_with(lexer, initialize_token(")", TOKEN_RIGHT_BRACKET)); break;

      case ':': return lexer_advance_with(lexer, initialize_token(":", TOKEN_COLON)); break;
      case ',': return lexer_advance_with(lexer, initialize_token(",", TOKEN_COMA)); break;

      case '+': return lexer_advance_with(lexer, initialize_token("+", TOKEN_ARITHMETIC_ADD)); break;
      case '/': return lexer_advance_with(lexer, initialize_token("+", TOKEN_ARITHMETIC_DIV)); break;
      case '%': return lexer_advance_with(lexer, initialize_token("%", TOKEN_ARITHMETIC_MOD)); break;

      case '-': {
        if (lexer_peek(lexer, 1) == '>'){
          return lexer_advance_with(lexer, initialize_token("->", TOKEN_THIN_ARROW));
        }
        return lexer_advance_with(lexer, initialize_token("-", TOKEN_ARITHMETIC_SUB));
      } break;

      case '*': {
        if (lexer_peek(lexer, 1) == '*'){
          return lexer_advance_with(lexer, initialize_token("**", TOKEN_ARITHMETIC_EXP));
        }
        return lexer_advance_with(lexer, initialize_token("*", TOKEN_ARITHMETIC_MUL));
      } break;

      case '&': {
        if (lexer_peek(lexer, 1) == '&'){
          return lexer_advance_with(lexer, initialize_token("&&", TOKEN_BOOL_AND));
        }
        return lexer_advance_with(lexer, initialize_token("-", TOKEN_BITWISE_AND));
      } break;

      case '|': {
        if (lexer_peek(lexer, 1) == '|'){
          return lexer_advance_with(lexer, initialize_token("||", TOKEN_BOOL_OR));
        }
        return lexer_advance_with(lexer, initialize_token("|", TOKEN_BITWISE_OR));
      } break;

      case '^': return lexer_advance_with(lexer, initialize_token("^", TOKEN_BITWISE_XOR)); break;

      default: printf("UNXPECTED CHARACTER FOUND '%c'. LEXER CANNOT PARSE. STOP.\n", lexer->current_character); exit(1); 
    }
  }
  return initialize_token(0, TOKEN_EOF);
}

char lexer_peek (neige_lexer_t *lexer, int offset){
  if (lexer->current_index + offset < lexer->content_size){
    return lexer->content[lexer->current_index + offset];
  }
  return lexer->content[lexer->content_size];
}