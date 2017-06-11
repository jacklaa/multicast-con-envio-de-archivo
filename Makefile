test: SocketMulticast.o PaqueteDatagrama.o
	g++ emisor.cpp SocketMulticast.o PaqueteDatagrama.o -o EMI
	g++ receptor.cpp SocketMulticast.o PaqueteDatagrama.o -o REC

SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h PaqueteDatagrama.o
	g++ SocketDatagrama.cpp -c
SocketMulticast.o: SocketMulticast.cpp SocketMulticast.h PaqueteDatagrama.o
	g++ SocketMulticast.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c

clean:
	rm SocketMulticast.o PaqueteDatagrama.o SocketDatagrama.o EMI REC
