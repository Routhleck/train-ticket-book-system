g++ ./server/ticketManage.cc -c
g++ ./ticketManage.o ./server/server.cc -o ./out/server.out
g++ ./client/client.cc -o ./out/client.out
./out/server.out
# ./client.out 127.0.0.1 8087

# g++ ./server/ticketManage.cc -c
# g++ ./ticketManage.o ./test.cc -o ./out/test
# ./out/test