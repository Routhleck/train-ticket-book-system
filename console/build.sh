# g++ ./server/server.cc -o server.out
# g++ ./client/client.cc -o client.out
# ./server.out 8087 &
# ./client.out 127.0.0.1 8087

g++ ./server/ticketManage.cc -c
g++ ./ticketManage.o ./test.cc -o ./out/test
./out/test