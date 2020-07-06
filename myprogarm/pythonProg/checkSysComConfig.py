#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import paramiko
import subprocess
import shlex
import re
import os
import time

Node_Info = {
    str('cp'): {'nodeName': '',
                'ip': '',
                'routing': '/opt/nokia/SS_TestRCPCCSMCU/'},
    str('mn'): {'nodeName': '',
                'ip': '',
                'routing': '/opt/nokia/SS_TestRCPCCSMCU/'},
    str('ei'): {'nodeName': '',
                'ip': '',
                'routing': '/opt/nokia/SS_TestRCPCCSRT/'},
    str('up'): {'nodeName': '',
                'ip': '',
                'routing': '/opt/nokia/SS_TestRCPCCSRT/'}
}

Nid_Info = {
    str('mn'): {'mcunid': ''},
    str('cp'): {'mcunid': ''},
    str('ei'): {'rtnid': ''},
}

global Base_Md5sum


def try_SSH():
    client = paramiko.SSHClient()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.load_host_keys(os.path.expanduser('~/.ssh/known_hosts'))
    for node in Node_Info.keys():
        client.connect(node, username='robot', password='rastre1')
        print("[+] Try to ssh the destination.")
    client.close()


def get_node_IP():
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    for node in Node_Info.keys():
        if node != 'mn':
            client.connect(Node_Info[node]['nodeName'],
                            username='robot', password='rastre1')
            stdin, stdout, stderr = client.exec_command('ip address')
            out = stdout.readlines()
            for line in out:
                if '169.254' in line and 'secondary intmsg0' not in line:
                    print(line, node)
                    Node_Info[node]['ip'] = str(
                        line.split('inet ')[1].split("/")[0])
        else:
            process = os.popen('ip address')
            output = process.readlines()
            for line in output:
                if '169.254' in line:
                    print(line, node)
                    Node_Info[node]['ip'] = str(
                        line.split('inet ')[1].split("/")[0])
    print(Node_Info)
    print("[+] Get the IP information Successful ,And close the connection!")
    client.close()


def get_node_id():
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    for node in Node_Info.keys():
        found = 0
        print(Node_Info[node]['nodeName'])
        if node != 'mn':
            client.connect(Node_Info[node]['nodeName'],
                            username='robot', password='rastre1')
            stdin, stdout, stderr = client.exec_command(
                "cat /etc/opt/nokia/ccs/node_id/IsReadOwnNidFile")
            out = stdout.readlines()
            for line in out:
                print("stdout:", line)
            if '1' in line:
                waittimecount = 0
                waittimeout = 30
                while waittimecount < waittimeout:
                    if found == 1:
                        break
                    if node == 'up':
                        stdin, stdout, stderr = client.exec_command(
                            "sudo chmod 777 /etc/opt/nokia/ccs/node_id/*")
                        stdin, stdout, stderr = client.exec_command(
                            "sudo ls /etc/opt/nokia/ccs/node_id/")
                        out = stdout.readlines()
                        stdin1, stdout1, stderr1 = client.exec_command(
                            "cat /etc/opt/nokia/ccs/node_id/mcu_own_nid")
                        out1 = stdout1.readlines()
                        for lineup1 in out1:
                            if "0x" in lineup1:
                                Nid_Info[node]['mcunid'] = lineup1
                                print("up nid_info mcu: ",
                                    Nid_Info[node]['mcunid'])
                            else:
                                print("up mcu sleep")
                                time.sleep(1)
                                waittimecount += 1
                        stdin, stdout, stderr = client.exec_command(
                            "sudo chmod 777 /etc/opt/nokia/ccs/node_id/*")
                        stdin, stdout, stderr = client.exec_command(
                            "sudo ls /etc/opt/nokia/ccs/node_id/")
                        stdin2, stdout2, stderr2 = client.exec_command(
                            "cat /etc/opt/nokia/ccs/node_id/rt_own_nid")
                        out2 = stdout2.readlines()
                        for lineup2 in out2:
                            if "0x" in lineup2:
                                Nid_Info[node]['rtnid'] = lineup2
                                print("up nid_info rt: ",
                                    Nid_Info[node]['rtnid'])
                                found = 1
                                break
                            else:
                                print("up rt sleep")
                                time.sleep(1)
                                waittimecount += 1
                    elif node == 'cp':
                        stdin, stdout, stderr = client.exec_command(
                            "sudo chmod 777 /etc/opt/nokia/ccs/node_id/*")
                        stdin, stdout, stderr = client.exec_command(
                            "sudo ls /etc/opt/nokia/ccs/node_id/")
                        out = stdout.readlines()
                        stdin, stdout1, stderr = client.exec_command(
                            "cat /etc/opt/nokia/ccs/node_id/mcu_own_nid")
                        out = stdout1.readlines()
                        for linecp in out:
                            if "0x" in linecp:
                                Nid_Info[node]['mcunid'] = linecp
                                print("cp nid_info mcu: ",
                                      Nid_Info[node]['mcunid'], node)
                                found = 1
                                break
                            else:
                                print("sleep", node)
                                time.sleep(1)
                                waittimecount += 1
                    elif node == 'ei':
                        stdin, stdout, stderr = client.exec_command(
                            "sudo chmod 777 /etc/opt/nokia/ccs/node_id/*")
                        stdin, stdout, stderr = client.exec_command(
                            "sudo ls /etc/opt/nokia/ccs/node_id/")
                        out = stdout.readlines()
                        stdin, stdout, stderr = client.exec_command(
                            "cat /etc/opt/nokia/ccs/node_id/rt_own_nid")
                        out = stdout.readlines()
                        for lineei in out:
                            if "0x" in lineei:
                                Nid_Info[node]['rtnid'] = lineei
                                print("ei nid_info mcu: ",
                                      Nid_Info[node]['rtnid'])
                                found = 1
                                break
                            else:
                                print("sleep", node)
                                time.sleep(1)
                                waittimecount += 1
                    else:
                        print("invalid node")
            else:
                print("IsReadOwnNidFile is not 1, use default value")
                Nid_Info['mn']['mcunid'] = 0x1140
                Nid_Info['cp']['mcunid'] = 0x1150
                Nid_Info['ei']['rtnid'] = 0x1160
                Nid_Info['up']['rtnid'] = 0x1180
                Nid_Info['up']['mcunid'] = 0x1190
        if node == 'mn':
            p = os.popen("cat /etc/opt/nokia/ccs/node_id/IsReadOwnNidFile")
            out = p.read()
            print("mn IsReadOwnNidFile:", out)
            for line in out:
                print("stdout:", line)
            if '1' in line:
                waittimecount = 0
                waittimeout = 30
                while waittimecount < waittimeout:
                    if found == 1:
                        break
                    print("node step2: ", node, found)
                    p = os.popen("sudo chmod 777 /etc/opt/nokia/ccs/node_id/*")
                    p1 = os.popen("cat /etc/opt/nokia/ccs/node_id/mcu_own_nid")
                    outmn = p1.read()
                    print("mn mcu_own_nid:", outmn)
                    if "0x" in outmn:
                        Nid_Info[node]['mcunid'] = outmn
                        print("mn nid_info mcu: ", Nid_Info[node]['mcunid'])
                        found = 1
                        break
                    else:
                        print("sleep", node)
                        time.sleep(1)
                        waittimecount += 1
    print(Nid_Info)
    print("[+] Get the NID information Successful ,And close the connection!")
    client.close()


def get_node_name():
    import os
    command = "sudo dvmcli -n"
    p = os.popen(command)
    out = p.read()
    print(out)
    for lines in out.splitlines():
        print(lines.split(" ")[0])
        nodeName = lines.split(" ")[0]
        node = nodeName.split("-")[0]
        node_index = nodeName.split("-")[1]
        if "mn" in node:
            Node_Info['mn']['nodeName'] = str(nodeName) + ".local"
        if 'cp' in node:
            Node_Info['cp']['nodeName'] = str(nodeName) + ".local"
        if 'ei' in node and int(node_index) == 0:
            Node_Info['ei']['nodeName'] = str(nodeName) + ".local"
        if 'up' in nodeName:
            Node_Info['up']['nodeName'] = str(nodeName) + ".local"


def copyTorobot():
    #    original_path = '/opt/nokia/SS_TestRCPCCSMCU/SysComRoute-.xml'
    #    now_path = '/home/robot/'
    copyTo = 'sudo cp /opt/nokia/SS_TestRCPCCSMCU/SysComRoute-.xml /home/robot/'
    try:
        os.system(copyTo)
        return 1
    except:
        return 0


def get_md5sum_value(node, path):
    out = os.popen('sudo ssh {node} sudo md5sum {path}'.format(
        node=node, path=path))
    print("In Node :", node)
    print(out.read())
    output = out.read()
    md_value = output.split(" ")[0]
    return str(md_value)


def compare_to_md5_value(base_md5sum, compare_md5sum):
    if base_md5sum == compare_md5sum:
        return True
    print("base:", base_md5sum)
    print("comapre:", compare_md5sum)
    return False


def SendXmlToNode():
    ''' First, send all XML to /home/robot/
        Then, ssh the server,
        finally, cp xml to destination path.'''
    for num in range(3):
        for element in Node_Info.keys():
            os.system('sudo scp /home/robot/SysComRoute-.xml {0}:{1}'.
                      format(Node_Info[element]['nodeName'], Node_Info[element]['routing']))
            os.system('sudo ssh {node} sudo cp -f {route_file}/SysComRoute-.xml /ram'.
                      format(node=Node_Info[element]['nodeName'], route_file=Node_Info[element]['routing']))
            print("Send file to ", Node_Info[element]['nodeName'])
            if "up" in element:
                os.system('sudo scp /home/robot/SysComRoute-.xml {0}:/opt/nokia/SS_TestRCPCCSMCU/'.
                          format(Node_Info['up']['nodeName']))
                os.system('sudo ssh {node} sudo cp -f {route_file}/SysComRoute-.xml /ram/MCU'.
                          format(node=Node_Info[element]['nodeName'], route_file=Node_Info["up"]['routing']))
        time.sleep(3)
        compare_md5sum_mn = get_md5sum_value(
            Node_Info['mn']['nodeName'], "/opt/nokia/SS_TestRCPCCSMCU/SysComRoute-.xml")
        if compare_to_md5_value(Base_Md5sum, compare_md5sum_mn) is False:
            continue
        compare_md5sum_ei = get_md5sum_value(
            Node_Info['ei']['nodeName'], "/opt/nokia/SS_TestRCPCCSRT/SysComRoute-.xml")
        if compare_to_md5_value(Base_Md5sum, compare_md5sum_ei) is False:
            continue
        compare_md5sum_cp = get_md5sum_value(
            Node_Info['cp']['nodeName'], "/opt/nokia/SS_TestRCPCCSMCU/SysComRoute-.xml")
        if compare_to_md5_value(Base_Md5sum, compare_md5sum_cp) is False:
            continue
        compare_md5sum_up_rt = get_md5sum_value(
            Node_Info['up']['nodeName'], "/opt/nokia/SS_TestRCPCCSRT/SysComRoute-.xml")
        if compare_to_md5_value(Base_Md5sum, compare_md5sum_up_rt) is False:
            continue
        compare_md5sum_up_mcu = get_md5sum_value(
            Node_Info['up']['nodeName'], "/opt/nokia/SS_TestRCPCCSMCU/SysComRoute-.xml")
        if compare_to_md5_value(Base_Md5sum, compare_md5sum_up_mcu) is False:
            continue
        print("Md5sum values equal with others, so the SysComRoute-.xml is replaced successful.")
        return
    print("Re-try three times, but still can not copy successful.")


if __name__ == '__main__':
    #    try_SSH()
    print("Starting get node name >>>>>>>>>")
    get_node_name()
    for node in Node_Info.keys():
        os.system(
            'ssh-keyscan -t rsa {} >> ~/.ssh/known_hosts'.format(Node_Info[node]['nodeName']))

    get_node_IP()
    flag = copyTorobot()
    if flag == 1:
        print("[+] Copying file to /home/robot. Running Success.")
    else:
        print("[-] Copying file to /home/robot. Running Failed.")

    file1 = open('/home/robot/SysComRoute-.xml', 'r+')
    file2 = open('/home/robot/tmp.xml', 'w+')

    ei = str(Node_Info['ei']['ip'])
    print(ei)
    up = str(Node_Info['up']['ip'])
    print(up)
    cp = str(Node_Info['cp']['ip'])
    print(cp)
    mn = str(Node_Info['mn']['ip'])
    print(mn)

    #get_node_id()
    Nid_Info['mn']['mcunid'] = "0xE040"
    Nid_Info['cp']['mcunid'] = "0xE050"
    Nid_Info['ei']['rtnid'] = "0xE060"
    Nid_Info['up']['rtnid'] = "0xE080"
    Nid_Info['up']['mcunid'] = "0xE090"

    output = file1.readlines()
    for line in output:
        if 'rsic="UP_MCU_NIDffff"' in line and 'lsic="UP_RT_NIDffff"' not in line:
            line = line.replace("29214", "29210")
        if 'lsic="UP_MCU_NIDffff"' in line and 'rsic="EI_RT_NIDffff"' in line:
            line = line.replace("10.5.5.9", "127.0.0.1")
            line = line.replace("10.5.5.6:29214", "127.0.0.1:29212")
        if 'lsic="UP_MCU_NIDffff"' in line and 'rsic="MN_MCU_NIDffff"' in line:
            line = line.replace("10.5.5.9:29214", "127.0.0.1:29215")
            line = line.replace("10.5.5.4:29214", "127.0.0.1:29212")
        if 'lsic="UP_MCU_NIDffff"' in line and 'rsic="CP_MCU_NIDffff"' in line:
            line = line.replace("10.5.5.9:29214", "127.0.0.1:29216")
            line = line.replace("10.5.5.5:29214", "127.0.0.1:29212")
        if 'lsic="UP_MCU_NIDffff"' in line and 'rsic="UP_RT_NIDffff"' in line:
            line = line.replace("10.5.5.9", "127.0.0.1")
            line = line.replace("10.5.5.8", "127.0.0.1")
        if 'lsic="UP_RT_NIDffff"' in line and 'rsic="UP_MCU_NIDffff"' in line:
            line = line.replace("10.5.5.9", "127.0.0.1")
            line = line.replace("10.5.5.8", "127.0.0.1")
        try:
            if len(ei) > 5:
                line = line.replace("10.5.5.6", ei)
            if len(cp) > 5:
                line = line.replace("10.5.5.5", cp)
            if len(mn) > 5:
                line = line.replace("10.5.5.4", mn)
            if len(up) > 5:
                line = line.replace("10.5.5.8", up)
                line = line.replace("10.5.5.9", up)
        except:
            print("[-] Replace IP and port failed.")
        file2.write(line)

    file1.close()
    file2.close()

    file3 = open('/home/robot/tmp.xml', 'r+')
    file4 = open('/home/robot/tmp1.xml', 'w+')
    outputfile3 = file3.readlines()
    replaceNidFinish = 0
    totalline = 0
    for line in outputfile3:
        totalline += 1
    print("totalline:", totalline)
    while replaceNidFinish == 0:
        lineIdx = 0
        for line in outputfile3:
            if 'MN_MCU_NID' in line:
                line = line.replace("MN_MCU_NID", Nid_Info['mn']['mcunid'])
            elif 'EI_RT_NID' in line:
                line = line.replace("EI_RT_NID", Nid_Info['ei']['rtnid'])
            elif 'CP_MCU_NID' in line:
                line = line.replace("CP_MCU_NID", Nid_Info['cp']['mcunid'])
            elif 'UP_RT_NID' in line:
                line = line.replace("UP_RT_NID", Nid_Info['up']['rtnid'])
            elif 'UP_MCU_NID' in line:
                line = line.replace("UP_MCU_NID", Nid_Info['up']['mcunid'])
            else:
                lineIdx += 1
                if lineIdx == totalline:
                    replaceNidFinish = 1
                    print("replaceNidFinish!!!!!!!!!")
            file4.write(line)
        file3.close()
        file4.close()
        command = "sudo mv /home/robot/tmp1.xml /home/robot/tmp.xml"
        os.system(command)
        file3 = open('/home/robot/tmp.xml', 'r+')
        if replaceNidFinish == 0:
            file4 = open('/home/robot/tmp1.xml', 'w+')
        outputfile3 = file3.readlines()
    file3.close()

    try:
        command = "sudo mv /home/robot/tmp.xml /home/robot/SysComRoute-.xml"
        os.system(command)
        os.system(
            "sudo chown _nokrcpsysccs:_nokrcpsysccs /home/robot/SysComRoute-.xml")
        print("[+] Move the File Success!")
    except:
        print("[-] Move the File Failed!")

    global Base_Md5sum
    Base_Md5sum = get_md5sum_value(
        Node_Info['mn']['nodeName'], "/home/robot/SysComRoute-.xml")
    SendXmlToNode()
    print("[+] The environment is deployed Successful!")
    print("[+] Reboot Now!!!!!")
    os.system('sudo reboot')
