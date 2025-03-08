/*
 * string_parser.c
 *
 *  Created on: Nov 25, 2020
 *      Author: gguan, Monil
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_parser.h"

#define _GUN_SOURCE


int count_token (char* buf, const char* delim)
{
	//TODO：
	/*
	*	#1.	Check for NULL string
	*	#2.	iterate through string counting tokens
	*		Cases to watchout for
	*			a.	string start with delimeter
	*			b. 	string end with delimeter
	*			c.	account NULL for the last token
	*	#3. return the number of token (note not number of delimeter)
	*/
	
	
	char* token;
	char* saveptr = NULL;

	token = strtok_r(buf, delim, &saveptr);

	int count = 0;

	while (token != NULL){
		if (strlen(token) > 0){
			//printf("buf: %s, count: %d\n", token, count);
			++count;

		}
		token = strtok_r(NULL, delim, &saveptr);
	}
	return count;
}


command_line str_filler (char* buf, const char* delim)
{
    command_line cmd;
    if (buf == NULL || delim == NULL) {
        cmd.num_token = 0;
        cmd.command_list = NULL;
        return cmd;
    }

    // Create a copy of the buffer to avoid modifying the original
    char* buf_copy = strdup(buf);

    // Count the tokens using the improved count_token function
    cmd.num_token = count_token(buf_copy, delim);
	//printf("num_token before using count: %d\n", cmd.num_token);
    free(buf_copy);  // Free the buffer copy after counting tokens

    // Allocate memory for the command_list array, plus one extra for NULL
    cmd.command_list = (char**) malloc((cmd.num_token + 1) * sizeof(char*));
    if (cmd.command_list == NULL) {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Now tokenize the original buf (we'll modify it during tokenization)
    char* saveptr;

	strtok_r(buf, "\n", &saveptr);
    char* token = strtok_r(buf, delim, &saveptr);
    int index = 0;

    while (token != NULL) {
        // Skip over empty tokens (i.e., when consecutive delimiters are found)
        if (strlen(token) > 0) {
            cmd.command_list[index] = strdup(token);  // Duplicate the token
            index++;
        }
        token = strtok_r(NULL, delim, &saveptr);
    }

    // Update the actual number of tokens in case we skipped any empty ones
    cmd.num_token = index;

    // Set the last element to NULL
    cmd.command_list[index] = NULL;

    return cmd;
}







void free_command_line(command_line* command)
{
	//TODO：
	/*
	*	#1.	free the array base num_token
	*/
	for (int i = 0 ; i < command->num_token; i++){
		free(command->command_list[i]);
	}
	free(command->command_list);
}
