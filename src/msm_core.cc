/*
 * =====================================================================================
 *
 *       Filename:  msm_core.c
 *
 *    Description:  merge in several threads
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

 struct thread_argument2
 {
 	/* data */
 	int *data;
 	int low;
 	int high;
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
 void MergeSort_simple(int *R,int low,int high)
 {
    int mid;
    if(low<high)
    {
        mid=(low+high)/2;
        MergeSort_simple(R,low,mid);
        MergeSort_simple(R,mid+1,high);
        Merge(R,low,mid,high);
    }
 }

 void *MergeSort(void *args){
 	thread_argument2 *merge_arg;
 	merge_arg = (thread_argument2 *)args;

 	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	pthread_attr_setscope(&attr1, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr1,PTHREAD_CREATE_JOINABLE);

	pthread_t t1,t2;
	int rc1,rc2;

 	int mid;

 	thread_argument2 arg1,arg2;
 	void *status1,*status2;

    mid = (merge_arg->low+merge_arg->high)/2;
 	if (merge_arg->low + 16 < merge_arg->high)
 	{	

 		arg1.data = merge_arg->data;
 		arg1.low = merge_arg->low;
 		arg1.high = mid;

 		arg2.data = merge_arg->data;
 		arg2.low = mid+1;
 		arg2.high = merge_arg->high;

 		rc1 = pthread_create(&t1,&attr1,MergeSort,&arg1);
    	if (rc1) {
        	printf("ERROR; return code from pthread_create(t1) is %d\n", rc1);
        	exit(-1);
    	}

 		rc2 = pthread_create(&t2,&attr1,MergeSort,&arg2);
    	if (rc2) {
        	printf("ERROR; return code from pthread_create(t2) is %d\n", rc2);
        	exit(-1);
    	}

    	rc1 = pthread_join (t1, &status1);
    	if (rc1)
    	{
        	printf("ERROR; return code from pthread_join(t1) is %d\n", rc1);
        	exit(-1);
    	}

    	rc2 = pthread_join (t2, &status2);
    	if (rc2)
    	{
        	printf("ERROR; return code from pthread_join(t2) is %d\n", rc2);
        	exit(-1);
    	}

    	Merge(merge_arg->data,merge_arg->low,mid,merge_arg->high);
    }
    else if(merge_arg->low < merge_arg->high){
        MergeSort_simple(merge_arg->data,merge_arg->low,mid);
        MergeSort_simple(merge_arg->data,mid+1,merge_arg->high);
        Merge(merge_arg->data,merge_arg->low,mid,merge_arg->high);
    }
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


	thread_argument2 arg;
	arg.data = my_arg.data;
	arg.low = 0;
	arg.high = my_arg.length-1;

    rc = pthread_create(&t1,&attr1,MergeSort,&arg);
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
	printf("All threads end.\n");
 	return 0;
 }

















