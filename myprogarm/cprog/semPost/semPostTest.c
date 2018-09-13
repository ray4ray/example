#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <assert.h>

int N = 3;
sem_t *sendSem, *echoSem;
#define SEND_SEM "/TEST_SEND_SEM"
#define ECHO_SEM "/TEST_ECHO_SEM"

void consumeCPUA(const char* functionName)
{
    int i, sum;
	i = sum = 0;
    for(;i<500000;i++)
	{
	    sum+=i;
	}
	printf("%s(): %s(): sum:%d\n",functionName, __FUNCTION__,sum);
}

void consumeCPUB(const char* functionName)
{
    int i, sum;
	i = sum = 0;
    for(;i<800000;i++)
	{
	    sum+=i;
	}
	printf("%s(): %s(): sum:%d\n",functionName,__FUNCTION__,sum);
}

void SendThread()
{
        static unsigned int loop1 = 0;
        while(loop1 < N+1)
        {
		    consumeCPUA(__FUNCTION__);
		    printf("%s(): put %d message to ringbuffer and post a semaphore later\n",__FUNCTION__, (loop1+1));
			sem_post(echoSem);
			printf("%s(): have post a semaphore, loop1:%d\n",__FUNCTION__, (loop1+1));

			printf("%s(): wait for semaphore to check ringbuffer,  loop1:%d\n",__FUNCTION__, (loop1+1));
			sem_wait(sendSem);
			printf("%s(): pull message from ringbuffer, loop1:%d\n",__FUNCTION__, (loop1+1));
            loop1++;
        }
        printf("%s(): exit. loop1:%d\n",__FUNCTION__,loop1);
        if(loop1 == N+1)
		{
            pthread_exit(NULL);
		}
}

void EchoTread()
{
        static unsigned int loop2 = 0;
        while(loop2 < N+1)
        {
		    printf("%s(): waiting semaphore for pull %d message from ringbuffer\n",__FUNCTION__, (loop2+1));
			sem_wait(echoSem);
			printf("%s(): got a semaphore. loop2: %d\n",__FUNCTION__, (loop2+1));
			consumeCPUB(__FUNCTION__);

			printf("%s(): post semaphone for notifying ringbuffer ready, loop2: %d\n",__FUNCTION__, (loop2+1));
			sem_post(sendSem);
			printf("%s(): pull message from ringbuffer,  loop2: %d\n",__FUNCTION__, (loop2+1));
            loop2++;
        }

		printf("%s(): exit. loop2:%d\n",__FUNCTION__,(loop2+1));
        if(loop2 == N+1)
		{
            pthread_exit(NULL);
		}
}


int main(int argc, char** argv)
{
        pthread_t pid1,pid2;
        pthread_attr_t attr;
        int ret;
        
        sendSem = sem_open(SEND_SEM, O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH), 0);
        echoSem = sem_open(ECHO_SEM, O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH), 0);

        ret = pthread_attr_init(&attr);
        assert(ret==0);
        pthread_attr_setschedpolicy(&attr,SCHED_OTHER);
		
        if((pthread_create(&pid1,&attr,(void *)&SendThread,NULL)) != 0)
        {
             printf("pthread create error\n");
	}
	else
	{
            printf("SendThread pid : %u\n",(unsigned int)pid1);
	}

        if((pthread_create(&pid2,&attr,(void *)&EchoTread,NULL)) != 0)
        {       
	    printf("pthread create error\n");
	}
	else
	{
            printf("EchoThread pid : %u\n",(unsigned int)pid2);
           
	}

        pthread_join(pid1,NULL);
        pthread_join(pid2,NULL);
        
		sem_close(sendSem);
		sem_close(echoSem);
        return 0;
}
