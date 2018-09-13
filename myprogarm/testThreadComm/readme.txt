[root@MMN-0(RCP-180) /home/_rcpadmin/gsuo/testThread]
# gcc testThreadComm.c -o testThreadComm -pthread
[root@MMN-0(RCP-180) /home/_rcpadmin/gsuo/testThread]
# ./testThreadComm
main: hello
child1: thread -142465280 enter
child2: thread -150857984 enter
child2: success to allocate mem 0xf00008c0
child1: read memory allocated by child2,MemPtr:0xf00008c0, first u32: 0xabcdef, second u32: 0xfecdab
child1: ready for free Mem 0xf00008c0
child1: freed Mem 0xf00008c0
child1: read memory freed by child1,MemPtr:0xf00008c0, first u32: 0x0, second u32: 0x0
child1: return
child2: return
main thread exit
