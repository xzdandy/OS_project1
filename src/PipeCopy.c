/*
 * =====================================================================================
 *
 *       Filename:  PipeCopy.c
 *
 *    Description:  copy by using pipe
 *
 *        Version:  1.0
 *        Created:  03/24/2013 03:13:01 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  xzdandy, 
 *   Organization:  
 *
 * =====================================================================================
 */

 #include "header/header.h"

 int main(int argc, char const *argv[])
 {
	FILE *src;
    
    //open read_file and check
    src = fopen(argv[1],"r");
    if (src == NULL){
        printf("Could not open the file '%s'.\n",argv[1]);
        exit(-1);
    }
    
    FILE *desk;

    desk = fopen(argv[2],"w+");

    if (desk == NULL){
        printf("Could not open the file '%s'.\n",argv[2]);
        fclose(src);
        exit(-1);
    } 	


 	//create pipe
 	int ch;
 	int mypipe[2];
 	if (pipe(mypipe)){
 		fprintf(stderr, "Pipe failed.\n");
 		return -1;
 	}

 	//create process
 	pid_t pid;
 	pid = fork();

 	switch (pid){
 		case -1:
 			printf("Error: Failed to fork.\n"); break;
 			break;

 		//child process reader
 		case 0:
 			close(mypipe[1]);
 			while (read(mypipe[0],&ch,1)>0){
 				fputc(ch,desk);
 			}
 			close(mypipe[0]);
 			exit(0);
 		
 		//parent process writer
 		default:
 			close(mypipe[0]);
 			while ((ch = fgetc(src)) != EOF){
 				write(mypipe[1],&ch,1);
 			}
 			close(mypipe[1]);
 	}

 	fclose(src);
 	fclose(desk);
 	return 0;
 }


