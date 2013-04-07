/*
 * =====================================================================================
 *
 *       Filename:  BurgerBuddies.c
 *
 *    Description:  deal with the cook, cashier and customer
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
#include <semaphore.h>

//global variable
int const NUM = 10;
sem_t max_ham,now_ham,cus,order,mutex,order_finish;

//function declared
void *Cook(void *args);
void *Customer(void *args);
void *Cashier(void *args);
pthread_attr_t create_attr();
void cook_start(int cook_num, pthread_t cook_t[],pthread_attr_t attr);
void customer_start(int cus_num, pthread_t cus_t[],pthread_attr_t attr);
void cashier_start(int cas_num, pthread_t cas_t[],pthread_attr_t attr);
void join(int num, pthread_t p_t[]);
void semaphore_init(int RackSize);

int main(int argc, char const *argv[])
{
	//print out bascial information
	printf("Cooks [%d], Cashiers [%d], Customers [%d]\n", atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
	printf("Begin run.\n");
	//initiate attr
	pthread_attr_t attr = create_attr();

	//initiate pthread 
	pthread_t cook_t[atoi(argv[1])];
	pthread_t cus_t[atoi(argv[3])];
	pthread_t cas_t[atoi(argv[2])];
	
	//initiate sem
	semaphore_init(atoi(argv[4]));
 	
 	//All threads  begin
	cook_start(atoi(argv[1]),cook_t,attr);
	customer_start(atoi(argv[3]),cus_t,attr);
	cashier_start(atoi(argv[2]),cas_t,attr);

	//join all threads
	join(atoi(argv[2]),cas_t);
	join(atoi(argv[3]),cus_t);
	join(atoi(argv[1]),cook_t);
	return 0;
}

void semaphore_init(int RackSize){
	sem_init(&max_ham,0,RackSize);
	sem_init(&now_ham,0,0);
	sem_init(&cus,0,0);
	sem_init(&order,0,0);
	sem_init(&mutex,0,1);
	sem_init(&order_finish,0,1);
}

void join(int num, pthread_t p_t[]){
	int error;
	for (int i = 0; i < num; ++i)
	{
		/* code */
		error = pthread_join(p_t[i],NULL);
		if (error)
		{
			printf("Error: return code from pthread %d is %d\n",i,error);
			exit(-1);
		}
	}
}

void cook_start(int cook_num, pthread_t cook_t[],pthread_attr_t attr){
	int *Cooks = new int [cook_num];
	int error;
	for (int i = 0; i < cook_num; ++i)
	{
		/* code */
		Cooks[i] = i+1;
		error = pthread_create(&cook_t[i],&attr,Cook,&Cooks[i]);
		if (error){
			printf("Error: return code from cook pthread %d is %d\n",i,error);
			exit(-1);
		}
	}
}

void customer_start(int cus_num, pthread_t cus_t[],pthread_attr_t attr){
	int *Cuss = new int [cus_num];
	int error;
	for (int i = 0; i < cus_num; ++i)
	{
		/* code */
		Cuss[i] = i+1;
		error = pthread_create(&cus_t[i],&attr,Customer,&Cuss[i]);
		if (error){
			printf("Error: return code from customer pthread %d is %d\n",i,error);
			exit(-1);
		}
	}
}

void cashier_start(int cas_num, pthread_t cas_t[],pthread_attr_t attr){
	int *Cass = new int [cas_num];
	int error;
	for (int i = 0; i < cas_num; ++i)
	{
		/* code */
		Cass[i] = i+1;
		error = pthread_create(&cas_t[i],&attr,Cashier,&Cass[i]);
		if (error){
			printf("Error: return code from cashier pthread %d is %d\n",i,error);
			exit(-1);
		}
	}
}

pthread_attr_t create_attr(){
	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	pthread_attr_setscope(&attr1, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr1,PTHREAD_CREATE_JOINABLE);
	return attr1;
}

void *Cook(void *args){
	int id = *(int *)args;
	do{
		sleep(rand()%NUM);
		sem_wait(&max_ham);
		printf("Cook[%d] makes a burger.\n",id);
		sem_post(&now_ham);
	}while(true);
}

void *Customer(void *args){
	int id = *(int *)args;
	do{
		sleep(rand()%(NUM*5));
		printf("Customer[%d] comes.\n", id);
		sem_post(&cus);
		sem_wait(&order);
		printf("Customer[%d] leaves.\n", id);
		sem_post(&order_finish);
	}while(true);
}

void *Cashier(void *args){
	int id = *(int *)args;
	do{
		sem_wait(&order_finish);
		sem_wait(&cus);
		printf("Cashier[%d] accepts an order.\n", id);
		sem_wait(&mutex);
		sem_wait(&now_ham);
		printf("Cashier[%d] take a burger to customor\n", id);
		sem_post(&order);
		sem_post(&mutex);
	}while(true);
}