
import xml.dom.minidom as xmldom
import os
import sys
import socket


def covert_to_python_list(vnfc_list_local_source):
    vnfc_list = vnfc_list_local_source.split(',')
    print(vnfc_list)
    return vnfc_list

def get_vnfc_type_list(vnfc_list, non_ccs_vnfc_list_src):
    vnfc_numb = len(vnfc_list)
    non_ccs_vnfc_list = non_ccs_vnfc_list_src.split(',')
    vnfc_type_list = []
    new_vnfc_list = []
    for vnfc in vnfc_list :
        vnfc_splited = vnfc.split('-')
        vnfc_type = vnfc_splited[0].upper()
        if vnfc_type not in vnfc_type_list and vnfc_type not in non_ccs_vnfc_list:
            vnfc_type_list.append(vnfc_type)
        if vnfc_type not in non_ccs_vnfc_list:
            new_vnfc_list.append(vnfc)
    print(vnfc_type_list)
    print(new_vnfc_list)
    return vnfc_type_list, new_vnfc_list

def get_single_node_list(vnfcs_info, vnfc_type_list, vnfc_list):
    vnfc_dir={}
    single_vnfc_dir = {}
    redundant_2N_vnfc_dir = {}
    scaling_vnfc_dir = {}
    for vnfc in vnfc_list :
        tmp_dir = {}
        tmp_dir['vnfc'] = []
        keys = vnfc_dir.keys()
        vnfc_splited = vnfc.split('-')
        vnfc_type = vnfc_splited[0].upper()
        if(vnfc_type not in keys):
            tmp_dir['numb'] = 1
            tmp_dir['vnfc'].append(vnfc)
            vnfc_dir[vnfc_type]=tmp_dir
        else:
            vnfc_dir[vnfc_type]['numb'] += 1
            vnfc_dir[vnfc_type]['vnfc'].append(vnfc)
    print(vnfc_dir)
    keys = vnfc_dir.keys()
    for vnfc_type in keys :
        if vnfcs_info[vnfc_type]['step'] == '0' and vnfc_dir[vnfc_type]['numb'] == 1:
             single_vnfc_dir[vnfc_type] = vnfc_dir[vnfc_type]['vnfc']
        elif vnfcs_info[vnfc_type]['step'] == '0' and vnfc_dir[vnfc_type]['numb'] == 2:
             redundant_2N_vnfc_dir[vnfc_type] = vnfc_dir[vnfc_type]['vnfc']
        else:
             scaling_vnfc_dir[vnfc_type] = vnfc_dir[vnfc_type]['vnfc']
    print(single_vnfc_dir)
    print(redundant_2N_vnfc_dir)
    print(scaling_vnfc_dir)
    return single_vnfc_dir, redundant_2N_vnfc_dir, scaling_vnfc_dir

def get_container_env(all_env_str, target_env_tuple):
    ret_val = {}
    #print(all_env_str)
    line_list = all_env_str.split('\n')
    #print(line_list)
    all_env_num = len(line_list)
    target_env_num = len(target_env_tuple)
    for line_index in range(all_env_num):
        #print(line_list[line_index])
        for index in range(target_env_num):
            if(target_env_tuple[index] in line_list[line_index]):
                #print(target_env_tuple[index])
                env_paire = line_list[line_index].split('=')
                ret_val[target_env_tuple[index]] = env_paire[-1]
                break
    return ret_val

def parse_syscom_route_profile(profile, vnfc_type_list): 
    vnfc_type_numb = len(vnfc_type_list)
    if('syscom_profile.xml' not in profile or 0 == vnfc_type_numb):
        print("invalid parameters: profile:%s,  vnfc_type_numb:%d"%(profile, vnfc_type_numb))
        return

    import xml.dom.minidom as xmldom
    #parse profile 
    domobj = xmldom.parse(profile)
    elementobj = domobj.documentElement

    #find all vnfc item
    vnfcObj = elementobj.getElementsByTagName("vnfc")
    vnfcNum = len(vnfcObj)
    #print("getElementsByTagName:",vnfcNum)
    output = {}

    for vnfcIndex in range(vnfcNum):
         tmpOutput = {}
         #print("VNFC name :",vnfcObj[vnfcIndex].getAttribute("name"))
         vnfc_type = vnfcObj[vnfcIndex].getAttribute("type")
         if vnfc_type not in vnfc_type_list:
             continue
         peerObj = vnfcObj[vnfcIndex].getElementsByTagName("peer")
         node_id_obj = vnfcObj[vnfcIndex].getElementsByTagName("base")
         node_id = node_id_obj[0].firstChild.data
         print(node_id)
         step_obj = vnfcObj[vnfcIndex].getElementsByTagName("step")
         step = step_obj[0].firstChild.data
         print(step)
         tmpOutput['step'] = step
         tmpOutput['node_ID'] = node_id
         peerNum = len(peerObj)
         #print("number of peer : ",peerNum)
         peer_list=[]
         for peerIndex in range(peerNum):
              #print("peer node: ", peerObj[peerIndex].firstChild.data)
              peer = peerObj[peerIndex].firstChild.data
              if peer in vnfc_type_list:
                  peer_list.append(peerObj[peerIndex].firstChild.data)
         print(peer_list)
         tmpOutput['peer'] = peer_list
         output[vnfc_type] = tmpOutput
    print(output)
    return output

def generate_syscom_route_base_on_profile(vnfcs_info, vnfc_type_list, single_vnfc_dir, redudant_2n_vnfc_dir, scaling_vnfc_dir):
    vnfcs_info_s = str(vnfcs_info)
    print(vnfcs_info_s)
    print(type(vnfcs_info_s))

    route_dir_vnfc_type = {}
    vnfc_type_numb = len(vnfc_type_list)
    for index in range(vnfc_type_numb):
         vnfc_type = vnfc_type_list[index]
         route_dir_vnfc_type[vnfc_type] = vnfcs_info[vnfc_type]['peer']
    print(route_dir_vnfc_type)
    route_dir_vnfc_type_t = str(route_dir_vnfc_type).replace('u','')
    print(route_dir_vnfc_type_t)

    for vnfc in vnfc_list :
        vnfc_splited = vnfc.split('-')
        vnfc_type = vnfc_splited[0].upper()

    for syscom_info in syscom_info_tuple:
        route_info_from_profile = route_info_from_profile.replace(syscom_info[0],syscom_info[1])

    print("replace profile info")
    print(route_info_from_profile)
    route_info_from_profile = eval(route_info_from_profile)
    #print(route_info_from_profile)

    local_list = list(route_info_from_profile.keys())
    target_route = {}
    for local in local_list :
        tmp_peer_list = route_info_from_profile[local]
        temp_route_list = []
        temp_route_numb = len(tmp_peer_list)
        for peerIndex in range(temp_route_numb):
            temp_item = local + 'FFFF' + '  ' + tmp_peer_list[peerIndex] + 'FFFF'
            #print("temp_item: %s", temp_item)
            temp_route_list.append(temp_item)
        target_route[local] = temp_route_list
    #print("syscom target route")
    #print(target_route)
    return target_route

def check_syscom_route_in_container_env(route_info_from_profile, current_route):
    if(0 == len(route_info_from_profile) | 0 == len(current_route)):
        print("empty target route or current route")
        print("route_info_from_profile: ")
        print(route_info_from_profile)
        print("current route: ")
        print(current_route)
        return

    #print(current_route)
    #current_base_node_Id = get_env(BASE_NID)
    current_base_node_Id = '0xE400'
    if(False == current_base_node_Id):
        print("get invalid base node ID")
        return

    target_route_keys = route_info_from_profile[current_base_node_Id]
    miss_route = False
    #miss_route_count = 0
    print("target syscom route:")
    for route_key in target_route_keys :
        print(route_key)
        if(route_key not in current_route):
            miss_route = True
            #miss_route_count++
            print("miss route: %s"%route_key)

    if(True == miss_route):
         return "fail to setup target syscom route"
    return "success to setup target syscom route"
    

def main(argv):
    print('this message is from main function')
    print(argv[1])
    vnfc_list_local_source='cp-0,db-0,db-1,ei-0,ei-1,mn-0,up-0'
    vnfc_list = covert_to_python_list(vnfc_list_local_source)
    print(vnfc_list)
    non_ccs_vnfc = 'DB,CD,UP'
    vnfc_type_list, new_vnfc_list = get_vnfc_type_list(vnfc_list, non_ccs_vnfc)
    print(vnfc_type_list)
    print(new_vnfc_list)
    vnfcs_info = parse_syscom_route_profile(argv[1], vnfc_type_list)
    single_vnfc_dir, redundant_2n_vnfc_dir, scaling_vnfc_dir = get_single_node_list(vnfcs_info, vnfc_type_list, new_vnfc_list)
    target_route = generate_syscom_route_base_on_profile(vnfcs_info, vnfc_type_list, new_vnfc_list, single_vnfc_dir, redundant_2n_vnfc_dir, scaling_vnfc_dir)
    covert_multi_paramters_to_list('XP','FHOAM','OAM')
    covert_multi_paramters_to_list('XP','FHOAM')
    covert_multi_paramters_to_list(['OAM','0xE010'],['FHOAM','E500'],['CPRT','0xE040'])
    covert_multi_paramters_to_list()
    current_route = '\nTimestamp <09:38:13.866032>\nID   FD   LSIC        RSIC        LIP            LPORT  RIP            RPORT   PROTOCOL  RETAIN  MSGID \n---  ---  ----------  ----------  -------------  -----  -------------  -----   --------  ------  ------\n1    25   0xE400FFFF  0xE010FFFF  192.168.0.101  49156  192.168.0.101  49155   SCTP      YES     0x0001\n2    25   0xE400FFFF  0xE100FFFF  192.168.0.101  49156  192.168.0.102  49155   SCTP      YES     0x0001\n3    25   0xE400FFFF  0xE200FFFF  192.168.0.101  49156  192.168.0.102  49156   SCTP      YES     0x0001\n4    25   0xE400FFFF  0xE300FFFF  192.168.0.101  49156  192.168.0.102  49157   SCTP      YES     0x0001\nPORT   DESTINATION SICAD  MSGID\n-----  -----------------  ------\n '
    print(current_route)
    result = check_syscom_route_in_container_env(target_route, current_route)
    print(result)
    all_env = '\nLWSD_PORT_49188_TCP_PORT=49188\nSYSCOM_ENDPOINT_ROLE=OAM\nSYSCOM_RUNTIME_ENV=vDU\nHOSTNAME=cran2-mcu-mn-deployment-0\nLWSD_SERVICE_HOST=10.254.130.22\nLWSD_SERVICE_PORT=49188\nLWSD_PORT=tcp://10.254.130.22:49188\nLWSD_PORT_49188_TCP_PROTO=tcp\nMINISTARTER_CONF_FILE=/etc/ccs-mcu-starter.json\nKUBERNETES_PORT_443_TCP_PROTO=tcp\nKUBERNETES_PORT_443_TCP_ADDR=10.254.0.1\nLWSD_SERVICE_PORT_LWSD=49188\nBASE_NID=57360\nGENAPI_TRACE_STDERR=\nSYSCOM_INTERFACE=internal\nKUBERNETES_PORT=tcp://10.254.0.1:443\nPWD=/\nHOME=/root\nCCS_TYPE=MGT\nKUBERNETES_SERVICE_PORT_HTTPS=443\nKUBERNETES_PORT_443_TCP_PORT=443\nKUBERNETES_PORT_443_TCP=tcp://10.254.0.1:443\nPCIDEVICE_NOKIA_K8S_IO_SRIOV_ENS11F1=0000:b3:05.0\nTERM=xterm\nLWSD_PORT_49188_TCP=tcp://10.254.130.22:49188\nSHLVL=1\nKUBERNETES_SERVICE_PORT=443\nLIGHTWEIGHTSERVICEDISCOVERY_DAEMON_ADDR=ipv4:lwsd:49188\nLWSD_PORT_49188_TCP_ADDR=10.254.130.22\nSYSCOM_ROUTE_PROFILE_PATH=/opt/nokia/SS_OAM/OAMAGENT\nMASTER_NID=57360\nPATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin\nSYSCOM_PORT=49155\nKUBERNETES_SERVICE_HOST=10.254.0.1\nSHARED_CPUS=2-4,22-24\nCCS_EARLY_LOG_TO_STDOUT=true\n_=/usr/bin/env\n'
    result = get_container_env(all_env, ('SYSCOM_ENDPOINT_ROLE', 'BASE_NID'))
    print(result)

if __name__ == '__main__':
    main(sys.argv)
