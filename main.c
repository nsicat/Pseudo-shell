
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_parser.h"
#include "command.h"
#include <ctype.h>

#define _GNU_SOURCE







void processCommand(command_line* command)
{		

	    if (strcmp(command->command_list[0], "exit") == 0){
		    return;
	    }
            if (strcmp(command->command_list[0], "ls") == 0) {
                if(command->num_token != 1){
                    printf("Error! Unsupported parameters for command: ls\n");
                    fflush(stdout);
                    
                } 
                else{
                    listDir();
                }
                //printf("Can execute ls\n");
            } else if (strcmp(command->command_list[0], "pwd") == 0) {
                showCurrentDir();
                //printf("Can execute pwd\n");
            } else if (strcmp(command->command_list[0], "mkdir") == 0) {
                if (command->num_token == 2) {
                    makeDir(command->command_list[1]);
                    //printf("Can execute mkdir\n");
                } else {
                    printf("Unsupported parameters for command: mkdir \n");
                    fflush(stdout);
                }
            } else if (strcmp(command->command_list[0], "cd") == 0) {
                if (command->num_token == 2) {
                    changeDir(command->command_list[1]);
                    //printf("Can execute cd\n");
                } else {
                    printf("Unsupported parameters for command: cd \n");
                    fflush(stdout);
                }
            } else if (strcmp(command->command_list[0], "cp") == 0) {
                if (command->num_token == 3) {
                    copyFile(command->command_list[1],(command->command_list[2]));
                    //printf("Can execute cp\n");
                } else {
                    printf("Unsupported parameters for command: cp\n");
                    fflush(stdout);
                }
            } else if (strcmp(command->command_list[0], "mv") == 0) {
                if (command->num_token == 3) {
                    moveFile(command->command_list[1],(command->command_list[2]));
                    //printf("Can execute mv\n");
                } else {
                    printf("Unsupported parameters for command: mv\n");
                    fflush(stdout);
                }
            } else if (strcmp(command->command_list[0], "rm") == 0) {
                if (command->num_token == 2) {
                    deleteFile(command->command_list[1]);
                    //printf("Can execute rm\n");
                } else {
                    printf("Unsupported parameters for command: rm\n");
                    fflush(stdout);
                }
            } else if (strcmp(command->command_list[0], "cat") == 0) {
                if (command->num_token == 2) {
                    displayFile(command->command_list[1]);
                    //printf("Can execute cat\n"); 
                } else {
                    printf("Unsupported parameters for command: cat\n");
                    fflush(stdout);
                }
            } else {
                printf("Error! Unrecognized command: %s\n", command->command_list[0]);
                fflush(stdout);
            }
}




void fileMode(int argc, char *argv[]){  //I need my string_parser for this to work


    //opening file to read

    if (argc > 2){
	    fprintf(stderr, "Too many arguments in FileMode\n");
    }

    if (argc < 2) {
        fprintf(stderr, "Error: No input file provided.\n");
        return;
    }

	FILE *inFPtr;
    FILE *outPtr;
	inFPtr = fopen (argv[1], "r");
    outPtr = fopen("output.txt", "w+");

    if (outPtr == NULL) {
    perror("fopen");
    exit(1);
    }

    if (inFPtr == NULL){
	    perror("input file failed\n");
	    exit(EXIT_FAILURE);
    }

    FILE* originalSTDOUT = stdout;
    
    stdout = outPtr;

	//declear line_buffer
	size_t len = 128;
	char* line_buf = malloc (len);

	command_line large_token_buffer;
	command_line small_token_buffer;



	//loop until the file is over
	while (getline (&line_buf, &len, inFPtr) != -1)
	{
		//printf ("Line %d:\n", ++line_num);

		//tokenize line buffer
		//large token is seperated by ";"
		large_token_buffer = str_filler (line_buf, ";");
		//fprintf(stdout, ">>>");
		//iterate through each large token
		//printf(">>> ");
		for (int i = 0; large_token_buffer.command_list[i] != NULL; i++)                        // I need to call the commands isntead of listing them out int
		{
			//printf ("\tLine segment %d:\n", i + 1);
	
			char* command = large_token_buffer.command_list[i];

			while (isspace((unsigned char)*command)) command++;

			if (*command == '\0'){
				//free(*command);
				continue;
			}

			//tokenize large buffer
			//smaller token is seperated by " "
			small_token_buffer = str_filler (large_token_buffer.command_list[i], " ");

            processCommand(&small_token_buffer);

			free_command_line(&small_token_buffer);
			memset (&small_token_buffer, 0, 0);
		}



		//free smaller tokens and reset variable
		free_command_line (&large_token_buffer);
		memset (&large_token_buffer, 0, 0);
		//free(line_buf);
	}

    printf("End of file\n");
    printf("Bye Bye!\n");
    fflush(stdout);
	fclose(inFPtr);
    fclose(outPtr);
    stdout = originalSTDOUT;

	free (line_buf);


}





void interactiveMode(){

    //declare line buffer
    size_t len = 0;
    char* line_buf = malloc(len);

    command_line largeTokenBuffer;
    command_line smallTokenBuffer; //compensate for multiple commands in one line


    while (1){
        printf(">>> ");
	fflush(stdout);

        int trigger = 0; // switch for exit statement to exit infinite loop

        getline(&line_buf, &len, stdin); // I need to change into a getline

        line_buf[strcspn(line_buf, "\n")] = 0; //strip the trailing newline

        largeTokenBuffer = str_filler(line_buf, ";"); //seperating token by;
	
        for (int i = 0; largeTokenBuffer.command_list[i] != NULL; i++)
        {	

            char* command = largeTokenBuffer.command_list[i];

	    //trim ; ; 
	    while (isspace((unsigned char)*command)) command++;
	    
	    if (*command == '\0'){
		    continue;
	    }

            smallTokenBuffer = str_filler (largeTokenBuffer.command_list[i], " ");


	    if (strlen(smallTokenBuffer.command_list[0]) == 0){
		    continue;
	    }
		

	    if (smallTokenBuffer.command_list[0] == NULL || strcmp(smallTokenBuffer.command_list[0], "") == 0){
		    free_command_line(&smallTokenBuffer);
		    continue;
	    }
            if (strcmp(smallTokenBuffer.command_list[0], "exit") == 0 ){
                trigger = 1;
                free_command_line(&smallTokenBuffer);
                //free(&largeTokenBuffer);
                break; //exit program
            }

            processCommand(&smallTokenBuffer);

            
            free_command_line (&smallTokenBuffer);
		    memset(&smallTokenBuffer, 0, 0);

        

        }

        //free smaller tokens and reset variable
	    free_command_line (&largeTokenBuffer);
		memset(&largeTokenBuffer, 0, 0);

        if (trigger == 1)
        {
            break; // exit infinite loop
            
        }

	//free(line_buf);
    }

    free(line_buf);

}





int main(int argc, char* argv[]){

    //Im just gonna call my two functions with two if statements

    if (argc == 1) //what if my executable wasnt name psuedo shell
    {
        interactiveMode();
        return 0; // success

    }
    else{
        fileMode(argc, argv);
        return 0;
    }

}


