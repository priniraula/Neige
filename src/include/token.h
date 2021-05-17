#pragma once
#ifndef TOKEN_H
#define TOKEN_H

enum token_type {

  // Brackets
  TOKEN_LEFT_PARENTHESIS, // {
  TOKEN_RIGHT_PARENTHESIS, // }
  TOKEN_LEFT_SQUARE_BRACKET, // [
  TOKEN_RIGHT_SQUARE_BRACKET, // ]
  TOKEN_LEFT_BRACKET, // (
  TOKEN_RIGHT_BRACKET, // )

  TOKEN_ARITHMETIC_ADD, // +
  TOKEN_ARITHMETIC_SUB, // -
  TOKEN_ARITHMETIC_MUL, // *
  TOKEN_ARITHMETIC_DIV, // /
  TOKEN_ARITHMETIC_EXP, // **
  TOKEN_ARITHMETIC_MOD, // %

  TOKEN_BOOL_LESS_THAN, // <
  TOKEN_BOOL_GREATER_THAN, // >
  TOKEN_BOOL_EQUALS, // ==
  TOKEN_BOOL_LESS_THAN_EQUAL, // <=
  TOKEN_BOOL_GREATER_THAN_EQUAL, // >=
  TOKEN_BOOL_NOT_EQUALS, // !=

  TOKEN_BOOL_AND, // &&
  TOKEN_BOOL_OR, // ||

  TOKEN_BITWISE_AND, // &
  TOKEN_BITWISE_OR, // |
  TOKEN_BITWISE_NOT, // !
  TOKEN_BITWISE_XOR, // ^
  TOKEN_BITWISE_LEFT_SHIFT, // <<
  TOKEN_BITWISE_RIGHT_SHIFT, // >>

  TOKEN_ID,

  TOKEN_COLON, // :
  TOKEN_COMA, // ,
  TOKEN_THIN_ARROW, // ->
  TOKEN_THICK_ARROW, // =>

  TOKEN_EOF, // END OF FILE TOKEN

  TOKEN_ASSIGN, // =
  TOKEN_INT, // INTEGER TOKEN
};

typedef struct TOKEN {
  char *content;
  enum token_type token_value;

} neige_token_t;


/**
 * Initialize the token with the specified content value and token type
 * @param content string value of the content
 * @param type is anyof token 
 * @return token value associated with the content and the specified token type
 */
neige_token_t *initialize_token (char *content, enum token_type type);

/**
 * Prints the content of the token
 * @param token the token to print
 */
void print_token (neige_token_t *token);

#endif