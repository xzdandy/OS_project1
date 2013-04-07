/*
 * =====================================================================================
 *
 *       Filename:  PipeCopy.c
 *
 *    Description:  calculate time cost by PipeCopy_core.c
 *
 *        Version:  1.0
 *        Created:  03/24/2013 05:53:30 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  xzdandy, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "header/header.h"
 
 void cal_time(char *filename, char const *argv0, char const *argv1, char const *argv2){
 	pid_t pid;
 	pid = fork(); 
 	int status;

 	struct timeval startTime, endTime;
 	struct timezone tz;
 	struct tm *tm;
 	long run_time;

  	switch (pid){
 		case -1:
 			printf("Error: Failed to fork.\n"); break;

 		case 0:
 			execlp(filename,argv0,argv1,argv2,NULL);
 			exit(0);

 		default:
 			gettimeofday(&startTime,&tz);
 			wait(&status);
 			gettimeofday(&endTime,&tz);
 			run_time = endTime.tv_usec - startTime.tv_usec;
 			printf("Excutable time: %ld microseconds\n", run_time);
 	}
 }

 int main(int argc, char const *argv[])
 {
 	//cal_time("./MyCopy",argv[0],argv[1],argv[2]);
 	//cal_time("./ForkCopy",argv[0],argv[1],argv[2]);
 	cal_time("./PipeCopy_core",argv[0],argv[1],argv[2]);
 	printf("Child Completed.\n");
 	return 0;
 }

