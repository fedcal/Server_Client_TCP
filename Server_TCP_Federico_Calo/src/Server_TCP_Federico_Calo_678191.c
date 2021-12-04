/*
 ============================================================================
 Name        : Server_TCP_Federico_Calo_678191.c
 Author      : Federico Calò Matricola 678191
 Description : Server side of the lab exame
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

//function for clean socket
void clearwinsock() {
	#if defined WIN32
		WSACleanup();
	#endif
}

//function for dividing between two numbers
float division(float oper1,float oper2);
//function for the sum of two numbers
float add(float oper1,float oper2);
//function for subtraction between two numbers
float sub(float oper1,float oper2);
//function for multiplying two numbers
float mult(float oper1,float oper2);


int main(int argc, char *argv[]) {
	int port;
	//I validate the variables with the parameters entered from the command line
	if(argc>1){
		port=atoi(argv[1]);
	}else
		port=PROTOPORT;
	if(port<0){
		printf("port number not valid\n",argv[1]);
		return 0;
	}
	printf("The Server is listening on the port: %d\n",port);

	//defined library for run server on the different operative system.
	#if defined WIN32
		WSADATA wsa_data;
		int result=WSAStartup(MAKEWORD(2,2),&wsa_data);
		if(result!=0){
			printf("Error At WSAStartup\n");
			clearwinsock();
			return -1;
		}
	int socket_server;
		socket_server=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(socket_server==INVALID_SOCKET){
			printf("Error socket server\n");
			clearwinsock();
			return -1;
		}
	#endif

	//define the socket struct
	struct sockaddr_in sad;
	memset(&sad,0,sizeof(sad));
	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	sad.sin_port = htons(port);

	//Bind the server socket
	int bind_socket=bind(socket_server, (struct sockaddr*) &sad, sizeof(sad));
	if(bind_socket<0){
		printf("\n bind() failed");
		closesocket(socket_server);
		clearwinsock();
		return -1;
	}
	//Listen
	int listen_size=listen(socket_server,QLEN);
	if(listen_size<0){
		printf("\n listen() failed");
		closesocket(socket_server);
		clearwinsock();
		return -1;
	}
	// Accpet a new connection
	struct sockaddr_in cad; // structure for the client address
	int client_socket; // socket descriptor for the client
	int client_len; // the size of the client address
	printf("Waiting for a client to connect...\n");
	fflush(stdout);
	client_len=sizeof(cad);

	//loop server
	while(1){
		client_len=sizeof(cad);
		if((client_socket=accept(socket_server,(struct sockaddr*)&cad,&client_len))<0){
			printf("\n accept() failed\n");
		}

		printf("Connection established with ` %s : %d`\n", inet_ntoa(cad.sin_addr), port);
		struct msgStruct msg;

		do{

			int recv_msg=recv(client_socket,&msg,sizeof(struct msgStruct),0);

			if(recv_msg<0){
				printf("\nImpossible recive the message");
			}else{
				printf("\nMessage from the client recived");
			}

			float result=0;
			float div=0;


			//according to the operator I perform the different functions
			switch (msg.oper[0]){
				case '+':
						strcpy(msg.message,"Operation calculated");
						result=add(msg.operand1,msg.operand2);
						msg.result=result;
						break;
				case '-':
						strcpy(msg.message,"Operation calculated");
						result=sub(msg.operand1,msg.operand2);
						msg.result=result;
						break;
				case '/':
						if(msg.operand2==div){
							strcpy(msg.message,"Unable to divide by 0");
						}else{
							strcpy(msg.message,"Operation calculated");
							result=division(msg.operand1,msg.operand2);
							msg.result=result;
						}
						break;
				case '*':
						strcpy(msg.message,"Operation calculated");
						result=mult(msg.operand1,msg.operand2);
						msg.result=result;
						break;
			}


			//send the struct to the client
			printf("\nSTRUTTURA D : %s %f %f", msg.oper, msg.operand1, msg.operand2);
			int client_send= send(client_socket, &msg, sizeof(struct msgStruct),0);

			printf("\n Struttura inviata");

			if(client_send<0){
				printf("\n I cannot send the message to the client");

			}
		}while(strcmp(msg.oper,"=")!=0);
		closesocket(client_socket);

	}
	closesocket(socket_server);
	clearwinsock();


	return EXIT_SUCCESS;
	system("pause");
}

//implementation function

float division(float oper1,float oper2){
	float result=0;
	result=oper1/oper2;
	return result;
}
float add(float oper1,float oper2){
	float result=0;
	result=oper1+oper2;
	return result;
}
float sub(float oper1,float oper2){
	float result=0;
	result=oper1-oper2;
	return result;
}
float mult(float oper1,float oper2){
	float result=0;
	result=oper1*oper2;
	return result;
}
