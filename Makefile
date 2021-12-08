all: Iperfer

CC = g++
Iperfer: main.cpp
	$(CC) -o Iperfer main.cpp iperfer_server.cpp iperfer_client.cpp