/*
 * =====================================================================================
 *
 *       Filename:  MyShell.c
 *
 *    Description:  intimate the terminal
 *
 *        Version:  1.0
 *        Created:  03/25/2013 10:15:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xzdandy 
 *   Organization:  
 *
 * =====================================================================================
 */

 #include "header/header.h"
 
 int main(int argc, char const *argv[])
 {
 	char line[40];

 	pid_t pid;
 	int status;
 	char *line_argv[] = {line,0};
 	//input loop
 	while(true){
 		printf("myshell> ");
 		scanf("%s",line);
 		fflush(stdin);

 		//exit
 		if (strcmp(line,"exit") == 0) break;

 		//create a child process
 		pid = fork();

 		switch (pid){
 			case -1:
 				printf("Error: Failed to fork.\n"); break;
 			case 0:
 				if (execvp(line,line_argv) == -1){
 					printf("Error: running command: '%s'\n", line);
 					exit(0);
 				}
 				break;
 			default:
 				wait(&status);
 		}

 	}
 	printf("Child Completed.\n");
 	return 0;
 }














