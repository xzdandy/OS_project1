/*
 * =====================================================================================
 *
 *       Filename:  MyCopy_core.c
 *
 *    Description:  copy file
 *
 *        Version:  1.0
 *        Created:  03/19/2013 05:56:05 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  xzdandy, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "header/header.h"

int main(int argc, char const *argv[]){
    FILE *src;
    
    //open read_file and check
    src = fopen(argv[1],"r");
    if (src == NULL){
        printf("Could not open the file '%s'.\n",argv[1]);
        exit(-1);
    }

    //open or create write_file and check
    FILE *desk;

    desk = fopen(argv[2],"w+");

    if (desk == NULL){
        printf("Could not open the file '%s'.\n",argv[2]);
        fclose(src);
        exit(-1);
    }
    
    //read and wirte
    unsigned char buffer[20];
    int read_num;
    while (true){
        read_num = fread(buffer,sizeof(unsigned char),20,src);
        if (read_num == 0) break;
        else{
            fwrite(buffer,sizeof(unsigned char),read_num,desk);
        }
    }

    //close file
    fclose(src);
    fclose(desk);
    return 0;
}










