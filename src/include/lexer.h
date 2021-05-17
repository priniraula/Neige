#pragma once
#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <stdio.h>

typedef struct LEXER {
  char current_character;
  char *content;
  size_t current_index;
  size_t content_size;

} neige_lexer_t;

#define EOF_CHARACTER '\0'
#define NEW_LINE_CHARACTER '\n'
#define WHITE_SPACE_CHARACTER ' '
#define TAB_CHARACTER '\t'
#define CARRIAGE_RETURN_CHARACTER '\r'

/**
 * Initialize the lexer with the specified content value 
 * @param content string value of the content
 * @return lexer with file content along with current index and character set to the
 * first character in the content
 */
neige_lexer_t *initialize_lexer (char *content);

/**
 * Advances the lexer by moving to the next word present in the content
 * @param lexer lexer to move forward
 */
void lexer_advance(neige_lexer_t *lexer);

/**
 * Skips the whitespaces it finds currently if it is present in the content
 * whitespaces include NEW_LINE_CHARACTER, WHITE_SPACE_CHARACTER, TAB_CHARACTER and CARRIAGE_RETURN_CHARACTER
 * @param lexer whitespaces found in the lexer's content to remove
 */
void lexer_ignore_whitespaces (neige_lexer_t *lexer);

/**
 * Creates a token of the next word / symbols / num present in the lexer
 * @param lexer source to tokenize
 * @return token consisting of the source value and its type
 */
neige_token_t *lexer_next_token (neige_lexer_t *lexer);

/**
 * Creates a new token with its token's content consisting of the word, with
 * token id of ID
 * @param lexer ID to parse in the lexer
 * @return token consisiting of the word with token id as ID
 */
neige_token_t *lexer_parse_id (neige_lexer_t *lexer);

/**
 * Creates a new token with its token's content consisting of the integers, with
 * token id of INT 
 * @param lexer ID to parse in the lexer
 * @return token consisiting of the word with token id as INT 
 */
neige_token_t *lexer_parse_number (neige_lexer_t *lexer);

/**
 * Advances the token and returns the current token
 * @param lexer the lexer to advance
 * @param token current token to return
 * @return simply returns the token
 */
neige_token_t *lexer_advance_with (neige_lexer_t *lexer, neige_token_t *token);

/**
 * Returns the character in content whose position is (current index + offset)
 * @param lexer contains the source file
 * @param offset integer value to add to the current index
 * @return character present in that index. If the offset + curr index is greater than source file size
 * then, EOF CHARACTER is returned
 */
char lexer_peek (neige_lexer_t *lexer, int offset);

#endif