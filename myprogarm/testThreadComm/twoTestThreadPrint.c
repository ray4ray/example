#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 


int flag=0;
void * child1(void *arg)  
{  
    pthread_t tid=pthread_self();  
	void * msgPtr = GLO_NULL;
    printf("child1: thread %d enter\nchild1: start sleep\n",tid);
    int i =0;
	while(i++<10)
	{
	    pthread_mutex_lock(&mutex);
		falg = !flag;
        printf("child2: flag%d", flag);
        pthread_mutex_unlock(&mutex);
	}
	
	printf("child1: return\n");
	return;
}


void * child2(void *arg)  
{  
    pthread_t tid=pthread_self();
    printf("child2: thread %d enter\n",tid);  
    int i =0
	while(i++<10)
	{
	    pthread_mutex_lock(&mutex);
        falg = !flag;
	    printf("child2: flag%d", flag);
        pthread_mutex_unlock(&mutex);
	}
	printf("child2: wakeup, return\n");
	return;
}

int main(void)  
{  
    pthread_t tid1,tid2;
	
	pthread_mutex_t mutex;
	
	pthread_mutex_init (&mutex,NULL);
 
    printf("main: hello\n");  

    ret = pthread_create(&tid1,NULL,child1,NULL);
	if(0 != ret)
	{
	   printf("main: failed to create child1\n");
	}

    ret = pthread_create(&tid2,NULL,child2,NULL);
	if(0 != ret)
	{
	   printf("main: failed to create child2\n");
	}
    sleep(60);
    //pthread_key_delete(key);

	if(0! = pthread_mutex_destroy(&mutex))
	{
        print("failed to destroy mutex ");	
	}

    printf("main thread exit\n"); 
    return 0;  
} 
