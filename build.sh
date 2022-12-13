rm -rf out
mkdir out
g++ -g server/server.cc -o out/server server/ticketManage.cc
g++ ./client/client.cc -o ./out/client
g++ -g server/test_algorithm.cc -o out/test_algorithm server/ticketManage.cc
cp ./server/ticket_data ./out/ticket_data