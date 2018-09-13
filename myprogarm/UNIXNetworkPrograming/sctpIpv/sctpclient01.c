#include"commonlib.h"
#include <time.h>

#define	SCTP_MAXLINE	1600

void
sctpstr_cli_echoall(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen)
{
	struct sockaddr_in peeraddr;
	struct sctp_sndrcvinfo sri;
	char sendline[SCTP_MAXLINE], recvline[SCTP_MAXLINE];
	socklen_t len;
	int rd_sz,i,strsz;
	int msg_flags;

	bzero(sendline,sizeof(sendline));
	bzero(&sri,sizeof(sri));
	while (fgets(sendline, SCTP_MAXLINE - 9, fp) != NULL) {
		strsz = strlen(sendline);
		if(sendline[strsz-1] == '\n') {
			sendline[strsz-1] = '\0';
			strsz--;
		}
		for(i=0;i<SERV_MAX_SCTP_STRM;i++) {
			snprintf(sendline + strsz, sizeof(sendline) - strsz,
				".msg.%d", i);
			Sctp_sendmsg(sock_fd, sendline, sizeof(sendline), 
				     to, tolen, 
				     0, 0,
				     i,
				     0, 0);
		}
		for(i=0;i<SERV_MAX_SCTP_STRM;i++) {
			len = sizeof(peeraddr);
			rd_sz = Sctp_recvmsg(sock_fd, recvline, sizeof(recvline),
				     (SA *)&peeraddr, &len,
				     &sri,&msg_flags);
			
			printf("From str:%d seq:%d (assoc:0x%x):",
				sri.sinfo_stream,sri.sinfo_ssn,
				(u_int)sri.sinfo_assoc_id);
			printf("%.*s, 0x%x\n",rd_sz,recvline, msg_flags);
		}
	}
}


void
sctpstr_cli(int sock_fd, struct sockaddr *to, socklen_t tolen, const int Pktsize, const int loopCount)
{
	struct sockaddr_in peeraddr;
	struct sctp_sndrcvinfo sri;
	char sendline[MAXLINE], recvline[MAXLINE];
	socklen_t len;
	int out_sz,rd_sz,ret, i=0;
	int msg_flags, padingLen;
	struct timeval start,end;
	long timeuse, sumTime=0,averageTime=0, maxTimeUse=0;
	char filename[100];
	time_t Curtime;
    memset(sendline, 0, sizeof(sendline));
	memset(recvline, 0, sizeof(recvline));

	bzero(&sri,sizeof(sri));
	len = sizeof(peeraddr);
	char tmp[20]="[0]";
	sri.sinfo_stream = strtol(&tmp[1],NULL,0);
	uint16_t stream_no = sri.sinfo_stream;
	char tmpline[MAXLINE]="1234567890";
	for(i=0;i<150;i++)
	{
	    strcat (tmpline,"1234567890");
	}
	printf("tmpline len %d\n", strlen(tmpline));
	padingLen = Pktsize - 30;

    time(&Curtime);

    struct tm *RetTime = localtime( &Curtime );
#if 0
        printf("Time: %04d-%02d-%02d %02d:%02d:%02d \r"
                ,RetTime->tm_year + 1900
                ,RetTime->tm_mon + 1 
                ,RetTime->tm_mday
                ,RetTime->tm_hour
                ,RetTime->tm_min
               ,RetTime->tm_sec);
#endif
	sprintf(filename,"/var/log/rttTestPktSize%dloopCount%d-%02d-%02d-%02d.txt",
		   Pktsize,loopCount,RetTime->tm_hour,RetTime->tm_min,RetTime->tm_sec);
    printf("filepath: %s\n",filename);
	FILE *fp;
    if(NULL == (fp=fopen(filename,"w+")))
    {
        err_sys("getMsgTrackInfoFile, Open file failed!");
        return;
    }

	i=0;
	while (i++< loopCount) {
#if 0	
		if(sendline[0] != '[') {
			printf("Error, line must be of the form '[streamnum]text'\n");
			continue;
		}
#endif
		sprintf(sendline, "%5d hello sctp hello sctp   ", i);
		strncat(sendline, tmpline, padingLen);

		out_sz = strlen(sendline);
		printf("sendline len %d\n", strlen(tmpline));
#if 0
		Sctp_sendmsg(sock_fd, sendline, out_sz, 
			     to, tolen,
			     0, 0,
			     sri.sinfo_stream,
			     0, 0);
#endif
        gettimeofday(&start, NULL);
		ret = sctp_sendmsg(sock_fd,sendline,out_sz,to,tolen,0,0,stream_no,
				  0,0);

		if(ret < 0){
			err_sys("sctp_sendmsg error");
		}

#if 0
		rd_sz = Sctp_recvmsg(sock_fd, recvline, sizeof(recvline),
			     (SA *)&peeraddr, &len,
			     &sri,&msg_flags);
#endif
		rd_sz = sctp_recvmsg(sock_fd,recvline,MAXLINE,(SA *)&peeraddr,&len,&sri,&msg_flags);
     	if(rd_sz < 0){
     		err_sys("sctp_recvmsg error");
     	}
		gettimeofday(&end, NULL );
		timeuse =1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
		printf("time=%ld\n",timeuse);
		sumTime += timeuse;
		if(maxTimeUse < timeuse)
		{
			maxTimeUse = timeuse;
		}
		
		if(0 != strcmp(sendline,recvline))
		{
		    printf("loop %d, test failed, echo data error", i);
			break;
		}
        fprintf(fp, "%10ld\t\n",timeuse);
        usleep(1000);  //sleep 1ms
#if 0
		printf("for loop %d, from str:%d seq:%d (assoc:0x%x):\n %.*s \n\n",
		       i,sri.sinfo_stream,sri.sinfo_ssn,
	       (u_int)sri.sinfo_assoc_id,rd_sz, recvline);
#endif
		//printf("%.*s, 0x%x\n",rd_sz,recvline, msg_flags);
	}
	if(i>0)
	{
		averageTime = sumTime/i;
		printf("########average RTT %ld, Max:%ld\n", averageTime, maxTimeUse);
	}
	fclose(fp);
}


int
main(int argc, char **argv)
{
	int sock_fd;
	struct sockaddr_in servaddr;
	struct sctp_event_subscribe evnts;
	int echo_to_all = 0;

#if 0
	if(argc < 2)
		err_quit("Missing host argument - use '%s host [echo]'\n",
		       argv[0]);
	if(argc > 2) {
		printf("Echoing messages to all streams\n");
		echo_to_all = 1;
	}
#endif
    int size      = atoi(argv[2]);
    int loopCount = atoi(argv[3]);
    printf("input parameter: IP:%s, Pktsize:%d,loop count:%d \n", argv[1],size,loopCount);

    sock_fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    
	bzero(&evnts, sizeof(evnts));
	evnts.sctp_data_io_event = 1;
	Setsockopt(sock_fd,IPPROTO_SCTP, SCTP_EVENTS,
		   &evnts, sizeof(evnts));
#if 0
	if(echo_to_all == 0)
		sctpstr_cli(sock_fd,(SA *)&servaddr,sizeof(servaddr));
	else
		sctpstr_cli_echoall(stdin,sock_fd,(SA *)&servaddr,sizeof(servaddr));
#endif
	sctpstr_cli(sock_fd,(SA *)&servaddr,sizeof(servaddr),size,loopCount);
	
	Close(sock_fd);
	return(0);
}
