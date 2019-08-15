#include<sys/socket.h>    /* basic socket definitions */
#include<netinet/in.h>    /* sockaddr_in{} and other Internet defns */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<stdarg.h>
#include<stdarg.h>
#include<stdarg.h>
#include<memory.h>
int main(int argc, char **argv)
{
    int                    listenfd, listenfd1, connfd;
    pid_t                childpid;
    socklen_t            clilen;
    struct sockaddr_in    cliaddr, servaddr;

    if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("socket error");

    memset(&servaddr,0, sizeof(struct sockaddr_in));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(0xC0A8000B);
    servaddr.sin_port        = htons(20401);

    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        printf("first bind: failed to bind, strerror: %s\n", strerror(errno));
    printf("first bind successfully \n");


        if ( (listenfd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
                printf("socket error");


        memset(&servaddr,0, sizeof(struct sockaddr_in));
        servaddr.sin_family      = AF_INET;
        servaddr.sin_addr.s_addr = htonl(0xC0A8000B);
        servaddr.sin_port        = htons(20401);

    printf("secod bind \n");
    if (bind(listenfd1, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        {
           printf("second bind: failed to bind, strerror: %s\n", strerror(errno));
           return 0;
        }    
        printf("first bind successfully \n");
}

/**
[root@k8s-env-k8s-master-0 ~]# gcc testBindDiffSocketSameAddress.c -o testBindDiffSocketSameAddress
[root@k8s-env-k8s-master-0 ~]# ./testBindDiffSocketSameAddress
first bind successfully
secod bind
second bind: failed to bind, strerror: Address already in use

http://man7.org/linux/man-pages/man2/bind.2.html
***/