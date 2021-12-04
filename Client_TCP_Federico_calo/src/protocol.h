#define BUFFERSIZE 2000 //size of the buffer
#define PROTOPORT 60000 //server port


/**
 * I defined a struct to serialize the protocol to exchange message between client side and server side.
 * operator is a String of character representing the symbol +,-,*,/.
 * operand 1 and operand2 are the numbers
 * result is a number representing the risult
 * message is a string used to indicate if the operation is correct
 */
struct msgStruct {
	char oper[2];
	float operand1;
	float operand2;
	float result;
	char message[50];
};
