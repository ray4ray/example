#include <stdio.h>
#include <stdarg.h>		/* ANSI C header file */
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <syslog.h>		/* for syslog() */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>

extern int errno;
#define	MAXLINE	100		/* to see datagram truncation */
#define SERV_MAX_SCTP_STRM	10	/* normal maximum streams */
#define	SA	struct sockaddr
#define	SERV_PORT 9877

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
/* $f err_ret $ */
err_ret(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	return;
}


void
/* $f err_quit $ */
err_quit(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(0, fmt, ap);
	va_end(ap);
	exit(1);
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

void
Inet_pton(int family, const char *strptr, void *addrptr)
{
	int		n;

	if ( (n = inet_pton(family, strptr, addrptr)) < 0)
		err_sys("inet_pton error for %s", strptr);	/* errno set */
	else if (n == 0)
		err_quit("inet_pton error for %s", strptr);	/* errno not set */

	/* nothing to return */
}

void
Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen)
{
	if (setsockopt(fd, level, optname, optval, optlen) < 0)
		err_sys("setsockopt error");
}


void
Close(int fd)
{
	if (close(fd) == -1)
		err_sys("close error");
}


/* Define bzero() as a macro if it's not in standard C library. */
#ifndef	HAVE_BZERO
#define	bzero(ptr,n)		memset(ptr, 0, n)
/* $$.If bzero$$ */
/* $$.If memset$$ */
#endif


/* include Socket */
int
Socket(int family, int type, int protocol)
{
	int		n;

	if ( (n = socket(family, type, protocol)) < 0)
		err_sys("socket error");
	return(n);
}

void
Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0)
		err_sys("bind error");
}

/* include Listen */
void
Listen(int fd, int backlog)
{
	char	*ptr;

		/*4can override 2nd argument with environment variable */
	if ( (ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	if (listen(fd, backlog) < 0)
		err_sys("listen error");
}
/* end Listen */

int
Sctp_recvmsg(int s, void *msg, size_t len,
	     struct sockaddr *from, socklen_t *fromlen,
	     struct sctp_sndrcvinfo *sinfo,
	     int *msg_flags)
{
	int ret;
#if 0
	printf("Sctp_recvmsg: s:%d, msg:0x%8x, len:%d, from: 0x%8x, fromlen:%d, sinfo: 0x%8x, msg_flag:0x%8x\n",
		     s, msg, len, from, *fromlen, sinfo, msg_flags);
#endif
	ret = sctp_recvmsg(s,msg,len,from,fromlen,sinfo,msg_flags);
	if(ret < 0){
		err_sys("sctp_recvmsg error");
	}
	return(ret);
}

sctp_assoc_t
sctp_address_to_associd(int sock_fd, struct sockaddr *sa, socklen_t salen)
{
	struct sctp_paddrparams sp;
	int siz;

	siz = sizeof(struct sctp_paddrparams);
	bzero(&sp,siz);
	memcpy(&sp.spp_address,sa,salen);
	sctp_opt_info(sock_fd,0,
		   SCTP_PEER_ADDR_PARAMS, &sp, &siz);
	return(sp.spp_assoc_id);
}

void
Getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlenptr)
{
	if (getsockopt(fd, level, optname, optval, optlenptr) < 0)
		err_sys("getsockopt error");
}

int 
sctp_get_no_strms(int sock_fd,struct sockaddr *to, socklen_t tolen)
{
	int retsz;
	struct sctp_status status;
	retsz = sizeof(status);	
	bzero(&status,sizeof(status));

	status.sstat_assoc_id = sctp_address_to_associd(sock_fd,to,tolen);
	Getsockopt(sock_fd,IPPROTO_SCTP, SCTP_STATUS,
		   &status, &retsz);
	return(status.sstat_outstrms);
}

int
Sctp_sendmsg (int s, void *data, size_t len, struct sockaddr *to,
	      socklen_t tolen, uint32_t ppid, uint32_t flags,
	      uint16_t stream_no, uint32_t timetolive, uint32_t context)
{
	int ret;
	ret = sctp_sendmsg(s,data,len,to,tolen,ppid,flags,stream_no,
			  timetolive,context);
	if(ret < 0){
		err_sys("sctp_sendmsg error");
	}
	return(ret);
}
