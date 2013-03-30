/*
 * =====================================================================================
 *
 *       Filename:  DupShell.c
 *
 *    Description:  command lines with pipes
 *
 *        Version:  1.0
 *        Created:  03/27/2013 10:40:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xzdandy, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "header/header.h"

 int main(int argc, char const *argv[])
 {	
 	char *line = "";
 	char *command_arrayA[] = {"wc",NULL};
 	char *command_arrayB[] = {"ls","-l",NULL};


 	int status;

 	//create pipe
 	int mypipe[2];
 	if (pipe(mypipe)){
 		fprintf(stderr, "Pipe failed.\n");
 		return -1;
 	}
 	
 	// fork process
 	pid_t pidA, pidB;
 	pidA = fork();
 	
 	if (pidA == -1) printf("Error: Failed to fork process A.\n");
 	if (pidA > 0) pidB = fork();
 	if (pidB == -1) printf("Error: Failed to fork process B.\n");

 	//close both end in parent
 	if (pidA > 0 && pidB > 0){
 		close(mypipe[0]);
 		close(mypipe[1]);
 	}    

 	//process A
 	if (pidA == 0){
 		close(mypipe[0]);
 		close(1);

 		dup2(mypipe[1],STDOUT_FILENO);
 		close(mypipe[1]);

 		if (execvp(command_arrayB[0],command_arrayB) == -1)
			{ printf("Error: running command: '%s'\n", line);}
 	}

 	if (pidB == 0){
 		close(mypipe[1]);
 		close(0);

 		dup2(mypipe[0],STDIN_FILENO);
 		close(mypipe[0]);

 		if (execvp(command_arrayA[0],command_arrayA) == -1)
			{ printf("Error: running command: '%s'\n",line); }
 	}

 	if (pidA>0 && pidB>0) wait(&status);
 	return 0;
 }

