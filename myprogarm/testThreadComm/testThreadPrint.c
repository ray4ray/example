#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 

//pthread_key_t key;  
#define GLO_NULL (0)

#if 0
void echomsg(int t)  
{  
   printf("destructor excuted in thread %d,param=%d\n",pthread_self(),t);
}
#endif

typedef struct commonMsgList
{
   void* msgPtr;
   unsigned int msgLen;
}commonMsgList;

commonMsgList msgList;

void * child1(void *arg)  
{  
    pthread_t tid=pthread_self();  
	void * msgPtr = GLO_NULL;
    printf("child1: thread %d enter\nchild1: start sleep\n",tid);
    //pthread_setspecific(key,(void *)tid);
    sleep(20);
	printf("child1: wakeup\n");
	msgPtr = msgList.msgPtr;
	printf("child1: read memory allocated by child2,MemPtr:0x%x, first u32: 0x%x, second u32: 0x%x\n",
	            msgPtr, *((unsigned int *) msgPtr),*((unsigned int *) msgPtr+1));
    printf("child1: ready for free Mem 0x%x\n",msgPtr);

	free(msgPtr);
	printf("child1: freed Mem 0x%x\n",msgPtr);
	printf("child1: read memory freed by child1,MemPtr:0x%x, first u32: 0x%x, second u32: 0x%x\n",
	            msgPtr, *((unsigned int *) msgPtr),*((unsigned int *) msgPtr+1));
	//must set the value as NULL
    msgPtr = msgList.msgPtr = GLO_NULL;
	
    sleep(10);
	printf("child1: return\n");
	return;
}

void * child2(void *arg)  
{  
    pthread_t tid=pthread_self();
    void * msgPtr = GLO_NULL;	
    printf("child2: thread %d enter\n",tid);  
    //pthread_setspecific(key,(void *)tid);

	
    printf("child2: success to allocate mem 0x%x\nchild2: start sleep \n",msgPtr);
    sleep(20);
	printf("child2: wakeup, return\n");
	return;
}

int main(void)  
{  
    pthread_t tid1,tid2;
    int ret;
	 
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
    sleep(35);
    //pthread_key_delete(key);
    printf("main thread exit\n"); 
    return 0;  
}  