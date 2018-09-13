#include<sys/socket.h>	/* basic socket definitions */
#include<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>


#define	MAXLINE	20		/* to see datagram truncation */
extern int errno;


static void
err_doit(int errnoflag, const char *fmt, va_list ap)
{
	int		errno_save;
	char	buf[MAXLINE];

	errno_save = errno;		/* value caller might want printed */
	vsprintf(buf, fmt, ap);
	if (errnoflag)
		sprintf(buf+strlen(buf), ": %s", strerror(errno_save));
	strcat(buf, "\n");
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(stderr);		/* SunOS 4.1.* doesn't grok NULL argument */
	return;
}

void
/* $f err_sys $ */
err_sys(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	exit(1);
}

ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}

void
Writen(int fd, void *ptr, size_t nbytes)
{
	if (writen(fd, ptr, nbytes) != nbytes)
		err_sys("writen error");
}

void str_echo(int sockfd)
{
	int		n;
	char    buf[MAXLINE];

again:
	while ( (n = read(sockfd, buf, MAXLINE)) > 0){
		if (writen(sockfd, buf, n) != n)
		   err_sys("writen error");
    }
	
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_sys("str_echo: read error");
}

int main(int argc, char **argv)
{
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	memset(&servaddr,0, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(0xa9fe0014);
	servaddr.sin_port        = htons(9877);

	if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");

	if (listen(listenfd, 1024) < 0)
		err_sys("listen error");

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0)
		    err_sys("accept error");
		
        if ( (childpid = fork()) == -1)
		    err_sys("fork error");
		if ( childpid == 0) {	         /* child process */
            if (close(listenfd) == -1)   /* close listening socket */
		        err_sys("close error");
			str_echo(connfd);	/* process the request */
			exit(0);
		}
		
		if (close(connfd) == -1)   /* parent closes connected socket */
		    err_sys("close error");			
	}
}
