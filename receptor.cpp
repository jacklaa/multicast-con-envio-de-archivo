#include "SocketMulticast.h"
#include <stdlib.h>

using namespace std;

#define BUFLEN 100
int receiveF(char *filename, int port, char *ip); 

int main(int args, char *argv[]) {
	
	if (args != 4) {
		cout << "Modo de uso: " << argv[0] << " ip port filename" << endl;
		exit(-1);
	}

	receiveF(argv[3], atoi(argv[2]), argv[1]);
	return 0;
}

int receiveF(char *filename, int port, char *ip){

	SocketMulticast sock(port);

    FILE *image;

    image = fopen(filename, "wb");

    if(image == NULL){
        cout << "error al abrir la imagen" << endl;
        return -1; 
    }

    cout << "esperando..." << endl;
    PaqueteDatagrama data(100000);
	sock.recibe(data, ip); 

    while(1){
    	PaqueteDatagrama data(100000);
		sock.recibe(data, ip);       

        if(strcmp(data.obtieneDatos(),"fin")==0){
            break;
        }
        fwrite(data.obtieneDatos(),1,BUFLEN,image);
    }

    fclose(image);
    return 1;
}
