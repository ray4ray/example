
Client compile

[root@MMN-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# ls
commonlib.h  sctpclient01.c  sctpserv  sctpserv01.c  sctpserv01.o
[root@MMN-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# gcc -c sctpclient01.c
[root@MMN-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# gcc -o sctpC sctpclient01.o /usr/lib64/libsctp.so

Server compile

[root@MMN-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# ls
commonlib.h  sctpclient01.c  sctpserv  sctpserv01.c  sctpserv01.o
[root@MMN-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# gcc -c sctpserv01.c
[root@MMN-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# gcc -o sctpServ sctpserv01.o /usr/lib64/libsctp.so

Test

[root@MCP-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# ./sctpserv

[root@MMN-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# ./sctpC 169.254.64.4
[0]adadf
From str:0 seq:0 (assoc:0x13):[0]adadf
[0]sadasfasd
From str:0 seq:0 (assoc:0x14):[0]sadasfasd
[3]adfsfsfasfasfasfasfas
From str:3 seq:0 (assoc:0x15):[3]adfsfsfasfasfasfasfas
[0]dfasfsadfasfsafsafaf
From str:0 seq:0 (assoc:0x16):[0]dfasfsadfasfsafsafaf
[2]asfasfasfas
From str:2 seq:0 (assoc:0x17):[2]asfasfasfas




