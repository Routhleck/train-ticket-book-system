g++  ./server/ticketManage.cc -c ./out/ticketManage.o
g++ ./ticketManage.o ./server/server.cc -o ./out/server.out
g++ ./client/client.cc -o ./out/client.out