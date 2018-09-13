#!/bin/bash
DATE=$(date +%m%d%H%M)
tcpdump -i intmsg0 -w tcpdump${DATE}_$1.cap

