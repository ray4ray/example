#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
const int buf_size = 1024;
const int echo_port = 20013;

int main(int argc, char** argv)
{
	int sockfd;
	int ret;
	struct sockaddr_in serv_addr;
	struct sockaddr_in *addrs;
	int msg_flag;
	char recv_buffer[256];
	//int addr_size = 1;
	char msg[15] = "hello world.\n";
	//struct sctp_initmsg initmsg;
	//struct sctp_status status;
	struct sctp_sndrcvinfo sndrcvinfo;
	int ochannel;
	int brst;
	sockfd = socket(AF_INET,SOCK_SEQPACKET,IPPROTO_SCTP);

	if(sockfd < 0)
	{
		fprintf(stderr,"error while initializing socket.\n");
		exit(1);
	}
	addrs = malloc(sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(echo_port);
	memcpy(addrs,&serv_addr,sizeof(struct sockaddr_in));
	//memset(&initmsg, 0, sizeof(initmsg));
	//initmsg.sinit_max_instreams = atoi(argv[2]);
	//initmsg.sinit_num_ostreams = atoi(argv[3]);
	//fprintf(stdout,"asking for %d input stream, %d output stream.\n",
		   //initmsg.sinit_max_instreams,initmsg.sinit_num_ostreams);
    //len = sizeof(struct sockaddr_in);
	while(1)
	{
		ret = sctp_sendmsg(sockfd,msg,sizeof(msg),addrs,sizeof(struct sockaddr_in),0,0,0,0,0);
		if(ret == -1)
		{
			fprintf(stderr,"sctp_sendmsg error.\n");
		}
		else
		{
			printf("sctp_sendmsg send successfully\n");
		}
		struct sockaddr_in clientaddr;
		sctp_recvmsg(sockfd, recv_buffer, sizeof(recv_buffer), (struct sockaddr*)NULL, 0, &sndrcvinfo, &msg_flag);
		printf("receive ack data=%s\n", recv_buffer);
		sleep(1);
	}
	//brst = setsockopt(sockfd, IPPROTO_SCTP,SCTP_INITMSG,
	//		 &initmsg,sizeof(initmsg));
	//if(brst != 0)
	//{
	//	fprintf(stderr,"error while set socket option.\n");
	//	 exit(1);
	//}
	//brst = sctp_connectx(sockfd, (struct sockaddr*) addrs, 1);
	//if(brst < 0)
	//{
	//	fprintf(stderr, "can not connect to host.\n");
	//	exit(1);
	//}
	//memset(&status,0,sizeof(status));
	//len = sizeof(status);
	//status.sstat_assoc_id = 1;
	//brst = getsockopt(sockfd, IPPROTO_SCTP,SCTP_STATUS,&status,&len);
	//if(brst < 0)
	//{
	//   fprintf(stderr,"error while geting socket option.\n");
	//   exit(1);
	//}
	//fprintf(stdout,"input stream:%d, output stream:%d\n",
		   //status.sstat_instrms,status.sstat_outstrms);
	//ochannel = atoi(argv[4]);
	//if(ochannel >= status.sstat_outstrms)
	//{
	//   fprintf(stdout,"writing on illegal channel %d \n", ochannel);
	// }
	//bzero(&sinfo,sizeof(sinfo));
	//sinfo.sinfo_stream = ochannel;
	//sctp_send(sockfd, msg, strlen(msg), &sinfo, 0);
	//sinfo.sinfo_flags = SCTP_EOF;
	//sctp_send(sockfd,NULL,0,&sinfo,0);
	close(sockfd);
	return 0;
}