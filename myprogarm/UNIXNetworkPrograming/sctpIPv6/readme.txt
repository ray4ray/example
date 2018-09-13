
Client compile

[root@MMN-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# gcc -c sctpclient01.c
[root@MMN-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# gcc -o sctpC  sctpclient01.o /usr/lib64/libsctp.so

Server compile

[root@MCP-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# gcc -c sctpserv01.c
[root@MCP-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# gcc -o sctpserv  sctpserv01.o /usr/lib64/libsctp.so

Test
[root@MCP-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# ./sctpserv


[root@MCP-0(RCP-180) /home/_rcpadmin/gsuo/networkTest]
# ./sctpC remoteIP
[0]asds
From str:0 seq:0 (assoc:0xf):[0]asds
[1]asdafsfasfsd
From str:1 seq:0 (assoc:0x10):[1]asdafsfasfsd
[0]sdaasd
From str:0 seq:0 (assoc:0x11):[0]sdaasd
[4]adasas
From str:4 seq:0 (assoc:0x12):[4]adasas
