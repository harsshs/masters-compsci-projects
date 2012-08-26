/*
 * rUDPClient.c
 *
 *  Created on: Nov 30, 2009
 *      Author: Deepak Konidena
 */

# include <stdio.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>

# define MAXBUFFER 255

int main(int argc, char **argv){

	int clientSockDesc;
	struct sockaddr_in serverSockAddr;
	struct sockaddr_in fromSockAddr;
	unsigned short serverPort;
	unsigned int fromSockLen;
	char *serverIPAddr;
	char *Msg;
	char cBuffer[MAXBUFFER];
	int MsgLen;
	int recvMsgLen;

	if( (argc < 4) || (argc > 5)){
		fprintf(stderr,"\nUsage: %s <Server IP> <Message> <Server Port>", argv[0]);
		exit(1);
	}

	serverIPAddr = argv[1];
	Msg = argv[2];
	serverPort = atoi(argv[3]);

	if((MsgLen = strlen(Msg)) > MAXBUFFER)
		fprintf(stderr,"\n Message too long");

	if((clientSockDesc = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		fprintf(stderr,"\n socket() failed");

	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_addr.s_addr = inet_addr(serverIPAddr);
	serverSockAddr.sin_port = htons(serverPort);

	if(sendto(clientSockDesc, Msg, MsgLen, 0,(struct sockaddr *)&serverSockAddr, sizeof(serverSockAddr))!= MsgLen)
		fprintf(stderr,"\nsendto() sent a different number of bytes than originally expected!");

	recvMsgLen = sizeof(fromSockAddr);

	if((recvMsgLen = recvfrom(clientSockDesc, cBuffer, MAXBUFFER, 0, (struct sockaddr *)&fromSockAddr, &recvMsgLen))!= recvMsgLen)
		fprintf(stderr,"\nrecvfrom() failed");

	if(serverSockAddr.sin_addr.s_addr != fromSockAddr.sin_addr.s_addr){
		fprintf(stderr,"\n Error: Received a packet from unknown source");
		exit(1);
	}

	cBuffer[recvMsgLen] = '\0';
	printf("\n Received: %s\n", cBuffer);

	close(clientSockDesc);

	exit(0);

}
