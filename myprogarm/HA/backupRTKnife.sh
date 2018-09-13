#!/bin/bash
#cd $1
#cp CCSMCUDaemonExe /opt/nokia/SS_RCPCCSMCU/
#mv /opt/nokia/SS_RCPCCSMCU/CCSMCUDaemonExe /opt/nokia/SS_RCPCCSMCU/CCSMCUDaemonExe.bak
#cp libCCS.so  /opt/nokia/lib64/MCU/
cp /opt/nokia/lib64/RT/libCCS.so  /opt/nokia/lib64/RT/libCCS.so.bak
#cp CCSMCUSCTDaemonExe /opt/nokia/SS_TestRCPCCSMCU/
cp /opt/nokia/SS_TestRCPCCSRT/CCSSCTDaemonExe /opt/nokia/SS_TestRCPCCSRT/CCSSCTDaemonExe.bak
#cp CCSMCUSCTApplicationExe /opt/nokia/SS_TestRCPCCSMCU/
#mv /opt/nokia/SS_TestRCPCCSMCU/CCSMCUSCTApplicationExe  /opt/nokia/SS_TestRCPCCSMCU/CCSMCUSCTApplicationExe.bak
#cp libCCS_SCT.so /opt/nokia/SS_TestRCPCCSMCU/lib64/
cp /opt/nokia/SS_TestRCPCCSRT/lib64/libCCS_SCT.so   /opt/nokia/SS_TestRCPCCSRT/lib64/libCCS_SCT.so.bak
# cp libSYNC.so /opt/nokia/SS_TestRCPCCSMCU/lib64/
#mv /opt/nokia/SS_TestRCPCCSMCU/lib64/libSYNC.so /opt/nokia/SS_TestRCPCCSMCU/lib64/libSYNC.so.bak


