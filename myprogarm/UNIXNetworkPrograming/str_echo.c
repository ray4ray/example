#include	"unp.h"


int
Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int		n;
	if ( (n = accept(fd, sa, salenptr)) < 0) {
			err_sys("accept error");
	}
	return(n);
}


