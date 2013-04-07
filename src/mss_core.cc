/*
 * =====================================================================================
 *
 *       Filename:  mss_core.c
 *
 *    Description:  merge in one thread
 *
 *        Version:  1.0
 *        Created:  03/30/2013 02:39:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: xzdandy, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "header/header.h"

 // define the struct
 struct thread_argument
 {
 	int *data;
 	int length;
 };

 // read the data from file
 thread_argument getData(char const *src_address){
 	struct thread_argument my_arg;
 	
 	//open the file
 	FILE *src;
 	src = fopen(src_address,"r");
    if (src == NULL){
        printf("Could not open the file '%s'.\n",src_address);
        exit(-1);
    }

    int data;
    int offset;
    bool first = true;
    while(fscanf(src,"%d",&data)>0){
    	if (first){
    		my_arg.length = data;
    		my_arg.data = new int[my_arg.length];
    		first = false;
    		offset = 0;
    	}
    	else{
    		my_arg.data[offset++] = data;
    	}
    }

    fclose(src);
    return my_arg;
 }
 
 // do merge
 void Merge(int *R,int low,int m,int high)
 {
    int i=low,j=m+1,p=0;
    int *R1; 
    R1=(int *)malloc((high-low+1)*sizeof(int));
    if(!R1) return; 
    while(i<=m&&j<=high) R1[p++]=(R[i]<=R[j])?R[i++]:R[j++];
    while(i<=m) R1[p++]=R[i++];
    while(j<=high) R1[p++]=R[j++];
    for(p=0,i=low;i<=high;p++,i++) R[i]=R1[p];
 } 
 
 //mergesort
 void MergeSort(int *R,int low,int high)
 {
    int mid;
    if(low<high)
    {
        mid=(low+high)/2;
        MergeSort(R,low,mid);
        MergeSort(R,mid+1,high);
        Merge(R,low,mid,high);
    }
 }

 //thread function
 void *function(void *args){
    thread_argument *merge_arg;
    merge_arg = (thread_argument *)args;
    MergeSort(merge_arg->data,0,merge_arg->length-1);
    pthread_exit(NULL);
 }

 //write data
 void putData(thread_argument argv, char const *dest_address){
    FILE *dest;
    
    dest = fopen(dest_address,"w+");
    if (dest == NULL){
        printf("Could not open or create the file '%s'.\n",dest_address);
        exit(-1);
    }

    int error;

    error = fprintf(dest,"%d ",argv.length);
    if (error<0)
    {
            printf("Error occurs when writing into %s",dest_address);
    }
    
    for (int i = 0; i < argv.length; ++i)
    {
        error = fprintf(dest,"%d ",argv.data[i]);
        if (error<0)
        {
            printf("Error occurs when writing into %s",dest_address);
        }
    }
    fclose(dest);
 }

 int main(int argc, char const *argv[])
 {
 	struct thread_argument my_arg;
 	my_arg = getData("data.in");
 	int rc;

 	pthread_t t1;
	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	pthread_attr_setscope(&attr1, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr1,PTHREAD_CREATE_JOINABLE);

    rc = pthread_create(&t1,&attr1,function,&my_arg);
    if (rc) {
        printf("ERROR; return code from pthread_create(t1) is %d\n", rc);
        exit(-1);
    }

    void* status1;
    rc = pthread_join (t1, &status1);
    if (rc)
    {
        printf("ERROR; return code from pthread_join(t1) is %d\n", rc);
        exit(-1);
    }

    putData(my_arg,"data.out");
	printf("Thread ends.\n");
 	return 0;
 }
















