#!/bin/bash

mkdir $1
#cp ./opt/nokia/SS_RCPCCSRT/CCSApplicationExe   ./packet_$1
#cp ./opt/nokia/SS_RCPCCSRT/ccs.appstart ./packet_$1
mv libCCS.so ./$1
mv CCSSCTDaemonExe ./$1
mv libCCS_SCT.so ./$1
mv LINUX_* ./$1
mv tcpdump* ./$1
#cp ./opt/nokia/SS_RCPCCSRT/CCSEmDispatcherExe ./packet_$1


#scp -r root@10.140.163.206:/home/btscloud/gsuo/build/rt/SS_RCPCCSRT/src/C_Platform/CCS_RT/Services/lib/LINUX_PC64/libCCS.so /home/_rcpadmin/gsuo/
#scp -r root@10.140.163.206:/home/btscloud/gsuo/build/rt/SS_RCPCCSRT/src/C_Platform/CCS_RT/TestCodes/lib/LINUX_PC64/libCCS_SCT.so /home/_rcpadmin/gsuo/
#scp -r root@10.140.163.206:/home/btscloud/gsuo/build/rt/SS_RCPCCSRT/src/C_Platform/CCS_RT/CCS_Daemon/exe/LINUX_PC64/CCSSCTDaemonExe /home/_rcpadmin/gsuo/
#scp -r root@10.140.163.207:/workspace/hongfezh/RT/SS_TestRCPCCSRT/build/SS_TestRCPCCSRT-l*.tar.xz /drives/d/Mymaterial/RCP/task/AaMem/PerformanceTest/$1
