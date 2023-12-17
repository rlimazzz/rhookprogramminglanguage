#include "include/token.h"
#include "include/lexer.h"
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

lexer_T* init_lexer(char* contents){
	lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
	lexer->contents = contents;
	lexer->index = 0;
	lexer->character = contents[lexer->index];

	return lexer;
}

void lexer_advance(lexer_T* lexer){
	if(lexer->character != '\0' && lexer->index < strlen(lexer->contents)) {
		lexer->index += 1;
		lexer->character = lexer->contents[lexer->index];
	}

	
}

void lexer_skip_white_spaces(lexer_T* lexer){
	while(lexer->character == ' ' || lexer->character == 10) {
		lexer_advance(lexer);
	}
}

token_T* lexer_get_next_token(lexer_T* lexer){
	while(lexer->character != '\0' && lexer->index < strlen(lexer->contents) ) {
		if(lexer->character == '\0' || lexer->character == 10) {
			lexer_skip_white_spaces(lexer);
		}

		if(lexer->character == '"') {
			return lexer_collect_string(lexer);
		}

		switch(lexer->character) {
			case '=' : 
				return lexer_advance_with_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer)));
				break;
			case '(' :
				return lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer)));	
				break;
			case ')' :
				return lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer)));
				break;
			case ';' :
				return lexer_advance_with_token(lexer,init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer)));
				break;
				
				
		}
	}
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token) {

}
token_T* lexer_collect_string(lexer_T* lexer){
	lexer_advance(lexer);

	char* value = calloc(1, sizeof(char));
	value[0] = '\0';

	while(lexer->character != '"') {
		char* s = lexer_get_current_char_as_string(lexer);
		value = realloc(value , (strlen(value) + strlen(s) + 1) * sizeof(char));
		strcat(value, s);

	}

	lexer_advance(lexer);

	return init_token(TOKEN_STRING, value);
}

char* lexer_get_current_char_as_string(lexer_T* lexer){

}

