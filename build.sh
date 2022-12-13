g++  ./server/ticketManage.cc -c
mv ./ticketManage.o ./out/
g++ ./out/ticketManage.o ./server/server.cc -o ./out/server.out
g++ ./client/client.cc -o ./out/client.out
g++ ./out/ticketManage.o ./server/test_algorithm.cc -o ./out/test_algorithm.out