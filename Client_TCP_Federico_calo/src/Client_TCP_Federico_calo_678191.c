/*
 ============================================================================
 Name        : Client_TCP_Federico_Calo_678191.c
 Author      : Federico Calò Matricola 678191
 Description : laboratory exemption of computer networks: TCP sockets - CLIENT Side
 ============================================================================
 */


#if defined WIN32
#include <winsock.h>
#else
#define closessocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "protocol.h"


//function to clear socket
void clearwinsock() {
	#if defined WIN32
		WSACleanup();
	#endif
}

//L'utente deve inserire porta e ip
int main(int argc, char *argv[]) {

	#if defined WIN32
		WSADATA wsa_data;
		int result = WSAStartup(MAKEWORD(2 ,2), &wsa_data);
		if (result != 0) {
			printf ("error at WSASturtup\n");
			return -1;
		}
	#endif
	int c_socket;
	c_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (c_socket <0) {
			printf("socket creation failed.\n");
			closesocket(c_socket);
			clearwinsock();
			return -1;
		}
	// Build of sever connection
	int port;
	char ip[16];
	char response;

	//I validate the variables with the parameters entered from the command line
	if(argc==2){
			port=argv[1];

		}else if(argc==3){
			port=atoi(argv[1]);
			strcpy(ip,argv[2]);
		}else{
			port=PROTOPORT;
			strcpy(ip,"127.0.0.1");
		}

	struct sockaddr_in sad;
	memset(&sad, 0, sizeof(sad));
	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr(ip); // IP del server
	sad.sin_port = htons(port); // Server port
	//Connection to server
	int connection=connect(c_socket, (struct sockaddr *)&sad, sizeof(sad));
	if(connection<0){
		printf("\nConnection failed");
		closesocket(c_socket);
		clearwinsock();
		return -1;
	}
	struct msgStruct msg;


	char oprt[1000];

	do{
		//request the operation to user
		printf("\nInsert the operation: ");
		fflush(stdin);
		gets(oprt);

		//if the user insert '=' the client will exit
		if(oprt[0]!='='){
			//split the string with the space and memorize the valors into the struct

			char *token = strtok(oprt, " ");
			strcpy(msg.oper,token);

			token=strtok(NULL," ");
			msg.operand1=atof(token);

			token=strtok(NULL," ");
			msg.operand2=atof(token);

			int sizeStruct= sizeof(msg);

			int send_msg=send(c_socket, &msg, sizeStruct,0);
			if(send_msg<0){
				printf("\n error send()");
				clearwinsock();
			}
			fflush(stdout);

			//receve the response by the server
			int respons=recv(c_socket,&msg,sizeof(msg),0);

			if(respons<0){
				printf("\n error recv()");
				clearwinsock();
			}
			//I print the result distinguishing if the error message refers to the division
			if((strcmp(msg.message,"Unable to divide by 0")==0)){
				printf("%f %s %f = %s",msg.operand1,msg.oper,msg.operand2,msg.message);
			}else{
				printf("\n %s",msg.message);
				printf("\n %f %s %f = %f",msg.operand1,msg.oper,msg.operand2,msg.result);
			}

		}else{
			//if the user insert =, i send the message to the server to close the connction with the client
			int sizeStruct= sizeof(msg);
			int send_msg=send(c_socket, &msg, sizeStruct,0);
			if(send_msg<0){
				printf("\nSend end comunication failed");
				clearwinsock();
			}
		}
	}while(strcmp(oprt,"=")!=0);
	clearwinsock();

	system("pause");
	return EXIT_SUCCESS;
}
