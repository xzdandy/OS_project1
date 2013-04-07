/*
 * =====================================================================================
 *
 *       Filename:  ForkCopy_core.c
 *
 *    Description:  copy by creating a process
 *
 *        Version:  1.0
 *        Created:  03/23/2013 11:53:10 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  xzdandy 
 *   Organization:  
 *
 * =====================================================================================
 */

 #include "header/header.h"

 int main(int argc, char const *argv[])
 {
 	// create a process
 	int status;
 	pid_t ForkPID;
 	ForkPID = fork();

 	switch (ForkPID){
 		// fork failure
 		case -1:
 			printf("Error: Failed to fork.\n"); break;

 		//child process
 		case 0:

 			execlp("./MyCopy_core",argv[0],argv[1],argv[2],NULL);
 			exit(0);
 		//parent process
 		default:
 			wait(&status);
 	}
 	return 0;
 }


