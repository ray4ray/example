#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int fd = -1;
int child_fd = -1;
pthread_t tid;
char msg[15] = "copy that!";
char child_msg[15] = "msg from child!";
char child_buffer[256];
int child_ready = 0;

void child_thread(void* arg)
{
	int assoc_id = *(int*)arg;
	printf("assoc_id = %d\n",assoc_id);
	child_fd = sctp_peeloff(fd,assoc_id);
	child_ready = 1;
	while(1)
	{
		struct sockaddr_in clientaddr;
		int fromlen = sizeof(clientaddr);
		struct sctp_sndrcvinfo sndrcvinfo;
		int msg_flag;
		int length = sctp_recvmsg(child_fd, child_buffer, sizeof(child_buffer), (struct sockaddr*)&clientaddr, (socklen_t*)&fromlen, &sndrcvinfo, &msg_flag);
		printf("****************************************************\n");
		printf("Child Event: data event length=%d\n", length);
		char addrbuf[100];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addrbuf, INET6_ADDRSTRLEN);
		int port = ntohs(clientaddr.sin_port);
		printf("child data from=%s:%d\n", addrbuf, port);
		printf("child data=%s\n", child_buffer);
		sleep(2);
		//sctp_sendmsg(child_fd,child_msg,sizeof(child_msg),(struct sockaddr*)&clientaddr,sizeof(struct sockaddr_in),0,0,0,0,0);
	}
	
}
static void handle_event(void *buf)
{
 
	struct sctp_assoc_change   *sac;
	struct sctp_send_failed    *ssf;
	struct sctp_paddr_change   *spc;
	struct sctp_remote_error   *sre;
	struct sctp_shutdown_event *sse;
 
	union sctp_notification  *snp;
 
	snp = (union sctp_notification*)buf;
	switch (snp->sn_header.sn_type)
	{
 
		case SCTP_ASSOC_CHANGE:
		{
			sac = &snp->sn_assoc_change;
			printf("assoc_change: state=%hu, error=%hu, instr=%hu outstr=%hu associd=%d\n", 
				sac->sac_state, 
				sac->sac_error,
				sac->sac_inbound_streams, 
				sac->sac_outbound_streams,
				sac->sac_assoc_id);
			switch(sac->sac_state)
			{
				case SCTP_COMM_UP:
				{
					pthread_create(&tid,NULL,child_thread,&(sac->sac_assoc_id));
					break;
				}
					
			}
			break;
		}
		case SCTP_SEND_FAILED:
		{
			ssf = &snp->sn_send_failed;
			printf("sendfailed: len=%hu err=%d assoc_i=%d ssf_data=%d\n", ssf->ssf_length, ssf->ssf_error, ssf->ssf_assoc_id, ssf->ssf_data[0]);
			break;
		}
		case SCTP_PEER_ADDR_CHANGE:
		{
			spc = &snp->sn_paddr_change;
			struct sockaddr_in  *sin = (struct sockaddr_in *)&spc->spc_aaddr;
			char  addrbuf[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET, &sin->sin_addr, addrbuf, INET6_ADDRSTRLEN);
			printf("peeraddrchange: %s state=%d, error=%d\n", addrbuf, spc->spc_state, spc->spc_error);
			break;
		}
		case SCTP_REMOTE_ERROR:
		{
			sre = &snp->sn_remote_error;
			printf("remote_error: err=%hu len=%hu\n", ntohs(sre->sre_error), ntohs(sre->sre_length));
			break;
		}
 
		case SCTP_SHUTDOWN_EVENT:
		{
			sse = &snp->sn_shutdown_event;
			printf("shutdown event: assoc_id=%d\n", sse->sse_assoc_id);
			break;
		}
		default:
		{
			printf("unknown type: %hu\n", snp->sn_header.sn_type);
			break;
		}
	}
}
 
 
int main(int agrc, char* agrv[])
{
	/* Create a 1-to-many style SCTP socket. */
	//int fd = -1;

	if ((fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP)) < 0)
	{
		perror("socket");
		exit(1);
	}
 
     /* Enable all notifications and events */
	struct sctp_event_subscribe event;
     event.sctp_data_io_event = 1;
     event.sctp_association_event = 1;
     event.sctp_address_event = 1;
     event.sctp_send_failure_event = 1;
     event.sctp_peer_error_event = 1;
     event.sctp_shutdown_event = 1;
     event.sctp_partial_delivery_event = 1;
     event.sctp_adaptation_layer_event = 1;
     if (setsockopt(fd, IPPROTO_SCTP, SCTP_EVENTS, &event, sizeof(event)) != 0)
	{
          perror("setevent failed");
		exit(1);
	}
 
	/* Configure auto-close timer. */
	//int timeout = 5;
	//if (setsockopt(fd, IPPROTO_SCTP, SCTP_AUTOCLOSE, &timeout, 4) < 0) 
	//{
	//	perror("setsockopt SCTP_AUTOCLOSE");
	//	exit(1);
	//}
 
 
	/* Bind the socket to all local addresses. */
	struct sockaddr_in sin;
	bzero((char*)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(20013);
	sin.sin_addr.s_addr = inet_addr(agrv[1]);
	if (bind(fd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		perror("bind");
		exit(1);
	}
 
	/* Enable accepting associations. */
	if (listen(fd, 1) < 0) 
	{
		perror("listen");
		exit(1);
	}
 
	char buffer[256];
	int bufferlen = 256;
	bzero(buffer, bufferlen);
	
	struct sockaddr_in clientaddr;
	int fromlen = sizeof(clientaddr);
	struct sctp_sndrcvinfo sndrcvinfo;
	int msg_flag;
	
	while(1) 
	{ 
		if(child_ready==0)
		{
			int length = sctp_recvmsg(fd, buffer, bufferlen, (struct sockaddr*)&clientaddr, (socklen_t*)&fromlen, &sndrcvinfo, &msg_flag);
			if(length > 0)
			{
				//printf("server receive sth\n");
			}
	 
			if (msg_flag &  MSG_NOTIFICATION)
			{
				printf("****************************************************\n");
				printf("Event: notificaiton length=%d\n", length);
				handle_event((void*)buffer);
			}
			else
			{
				printf("****************************************************\n");
				printf("Event: data event length=%d\n", length);
				char addrbuf[100];
				inet_ntop(AF_INET, &clientaddr.sin_addr, addrbuf, INET6_ADDRSTRLEN);
				int port = ntohs(clientaddr.sin_port);
				printf("data from=%s:%d\n", addrbuf, port);
				printf("data=%s\n", buffer);
				sctp_sendmsg(fd,msg,sizeof(msg),(struct sockaddr*)&clientaddr,sizeof(struct sockaddr_in),0,0,0,0,0);
			}
			//int assoc = sctp_address_to_associd(fd,(struct sockaddr*)&clientaddr,(socklen_t*)&fromlen);
			//if(assoc == 0)
			//{
			//	printf("can't get association id\n");
			//}
			//else
			//	printf("current assoc id is %d\n",assoc);
		}
		else
		{
			//printf("child_fd = %d in parent\n",child_fd);
			sctp_sendmsg(child_fd,msg,sizeof(msg),(struct sockaddr*)&clientaddr,sizeof(struct sockaddr_in),0,0,0,0,0);
		}
	}
 
 
	if (close(fd) < 0) 
	{
		perror("close");
		exit(1);
	}
 
	return (0);
}
