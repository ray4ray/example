#!/bin/bash

mkdir $1

cp ./src/C_Platform/CCS_RT/Services/exe/LINUX_PC64/libCCS.so ./$1
cp ./src/C_Platform/CCS_RT/TestCodes/exe/LINUX_PC64/libCCS_SCT.so ./$1
cp ./src/C_Platform/CCS_RT/CCS_Daemon/exe/LINUX_PC64/CCSSCTDaemonExe ./$1
cp ./src/C_Platform/CCS_RT/Services/AaEmServices/exe/LINUX_PC64/CCSEmDispatcherExe ./$1

scp -r $1/ _rcpadmin@10.68.180.208:/home/
