/*
 * =====================================================================================
 *
 *       Filename:  MoreShell.c
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
 
 int parseLine(char *line, char *command_array[]) {
	char *p;
	int count=0;
	p = strtok(line, " ");
	while (p && strcmp(p,"|")!=0) {
		command_array[count] = p;
		count++;
		p = strtok(NULL," ");
	}
	return count;
}


 int main(int argc, char const *argv[])
 {
 	char line[256];

 	pid_t pid;
 	int status;
 	char *line_argv[10];
 	int count;

 	//input loop
 	while(true){
 		printf("moreshell> ");
 		fflush(stdin);
 		gets(line);

 		//produce line_argv
 		count = parseLine(line,line_argv);
 		line_argv[count] = NULL;

 		//exit
 		if (strcmp(line_argv[0],"exit") == 0) break;

 		//create a child process
 		pid = fork();

 		switch (pid){
 			case -1:
 				printf("Error: Failed to fork.\n"); break;
 			case 0:
 				if (execvp(line_argv[0],line_argv) == -1){
 					printf("Error: running command: '%s'\n", line);
 					exit(0);
 				}
 				break;
 			default:
 				wait(&status);
 		}

 	}
 	return 0;
 }














