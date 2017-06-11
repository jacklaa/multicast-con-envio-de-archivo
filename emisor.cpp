#include "SocketMulticast.h"
#include "PaqueteDatagrama.h"
#include <stdlib.h>

#define BUFLEN 100 

using namespace std;

int sendF(char *filename, int ttl, char *HELLO_GROUP, int PORT);

int main(int args, char *argv[]) {
	if (args != 5) {
		cout << "Modo de uso: " << argv[0] << "filename ip port ttl" << endl;
		exit(-1);
	}
	cout << "aqui" << endl;
	sendF(argv[1], atoi(argv[4]), argv[2], atoi(argv[3]));
	cout << "aqui2" << endl;
	return 0;
}


int sendF(char *filename, int ttl, char *HELLO_GROUP, int PORT){
	SocketMulticast sock(PORT);

    int bufSize = 100;
    int sentBytes = 0;
    char cad[bufSize];

    FILE * pFile;
    long remainingBytes;
    size_t result;

    pFile=fopen(filename , "rb" );

    if( pFile == NULL){
    	cout << "no se pudo abrir la imagen" << endl;
        return -1; 
    }
    fseek (pFile , 0 , SEEK_END);
    remainingBytes = ftell (pFile);
    rewind (pFile);

    int bufferSize = remainingBytes > bufSize ? bufSize : remainingBytes;

    PaqueteDatagrama data2(cad, strlen(cad), HELLO_GROUP, 4444);
	sock.envia(data2, ttl);

    while(remainingBytes > 0){
      fseek (pFile , sentBytes , SEEK_SET);
        result = fread(cad,1,bufferSize,pFile);
        if(bufferSize < remainingBytes){
        	//aqui
        	PaqueteDatagrama data(cad, strlen(cad), HELLO_GROUP, 4444);
			sock.envia(data, ttl);
        }
        else{
        	PaqueteDatagrama data(cad, strlen(cad), HELLO_GROUP, 4444);
			sock.envia(data, ttl);
            bufferSize = remainingBytes;
        }
        //if (recvfrom(socket, buffer, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1){
        //  printf("error en recvfrom\n");
        //}
        remainingBytes -= bufferSize;
        sentBytes += bufferSize;
    }

    fclose(pFile);
    char fin[100];
    strcpy(fin,"fin");
    PaqueteDatagrama data(fin, strlen(fin), HELLO_GROUP, 4444);
	sock.envia(data, ttl);
	cout << "termino" << endl;
    return 1;
}
