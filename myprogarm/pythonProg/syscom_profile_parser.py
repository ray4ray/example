import xml.dom.minidom as xmldom
import os
import sys
import socket


# def parse_syscom_route_profile(profile, vnfc_type_list):
#     vnfc_type_numb = len(vnfc_type_list)
#     if('syscom_profile.xml' not in profile or 0 == vnfc_type_numb):
#         print("invalid parameters: profile:%s,  vnfc_type_numb:%d" %
#               (profile, vnfc_type_numb))
#         return

#     import xml.dom.minidom as xmldom
#     #parse profile
#     domobj = xmldom.parse(profile)
#     elementobj = domobj.documentElement

#     #find all vnfc item
#     vnfcObj = elementobj.getElementsByTagName("vnfc")
#     vnfcNum = len(vnfcObj)
#     #print("getElementsByTagName:",vnfcNum)
#     output = []

#     for vnfcIndex in range(vnfcNum):
#         tmpOutput = []
#         vnfc_type = vnfcObj[vnfcIndex].getAttribute("type")
#         tmpOutput.append(vnfc_type)
#         #print("VNFC type :", vnfc_type)
#         if vnfc_type not in vnfc_type_list:
#             continue
#         peerObj = vnfcObj[vnfcIndex].getElementsByTagName("peer")
#         node_id_obj = vnfcObj[vnfcIndex].getElementsByTagName("base")
#         node_id = node_id_obj[0].firstChild.data
#         tmpOutput.append(node_id)
#         #print(node_id)
#         step_obj = vnfcObj[vnfcIndex].getElementsByTagName("step")
#         step = step_obj[0].firstChild.data
#         #print(step)
#         tmpOutput.append(step)
#         peerNum = len(peerObj)
#         #print("number of peer : ",peerNum)
#         peer_list = []
#         for peerIndex in range(peerNum):
#             #print("peer node: ", peerObj[peerIndex].firstChild.data)
#             peer = peerObj[peerIndex].firstChild.data
#             if peer in vnfc_type_list:
#                 peer_list.append(peerObj[peerIndex].firstChild.data)
#         #print(peer_list)
#         tmpOutput.append(peer_list)
#         output.append(tmpOutput)
#     print(output)

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
        vnfc_type = vnfcObj[vnfcIndex].getAttribute("type")
        #print("VNFC type :", vnfc_type)
        if vnfc_type not in vnfc_type_list:
            continue
        peerObj = vnfcObj[vnfcIndex].getElementsByTagName("peer")
        node_id_obj = vnfcObj[vnfcIndex].getElementsByTagName("base")
        node_id = node_id_obj[0].firstChild.data
        #print(node_id)
        step_obj = vnfcObj[vnfcIndex].getElementsByTagName("step")
        step = step_obj[0].firstChild.data
        #print(step)
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
        #print(peer_list)
        tmpOutput['peer'] = peer_list
        output[vnfc_type] = tmpOutput
    print(output)

# def generate_peer_vnfc_dir(vnfcs_info, vnfc_type_list):
#     #print(vnfcs_info)
#     #vnfcs_info_str = str(vnfcs_info)
#     #vnfcs_info_str = vnfcs_info_str.replace(vnfcs_info_str[0],'')
#     #print(vnfcs_info_str)
#     #vnfcs_info_dir = eval(vnfcs_info_str)
#     route_dir_vnfc_type = {}
#     vnfc_type_numb = len(vnfc_type_list)
#     for index in range(vnfc_type_numb):
#         vnfc_type = vnfc_type_list[index]
#         #route_dir_vnfc_type[vnfc_type] = vnfcs_info_dir[vnfc_type]['peer']
#         route_dir_vnfc_type[vnfc_type] = vnfcs_info[vnfc_type]['peer']
#     print(route_dir_vnfc_type)
#     route_dir_vnfc_type_t = str(route_dir_vnfc_type).replace('u', '')
#     print(route_dir_vnfc_type_t)
#     return route_dir_vnfc_type_t


# # def filter_syscom_route_keyword(source_route):
# #     import re
# #     route_list = source_route.split('\n')
# #     valid_route = []
# #     for line in route_list:
# #         if 'SCTP' in line:
# #             #item_list = line.split(' ')
# #             item_list = re.split(r" +", line)
# #             ## hard code pattern, TODO
# #             route = item_list[2] + '  ' + item_list[3]
# #             valid_route.append(route)
# #             #print(route)
# #     return valid_route

def main(argv):
    #print('this message is from main function')
    #print(argv[1])
    #print(argv[2])
    parse_syscom_route_profile(argv[1], argv[2])

    # vnfcs_info = {u'CP': {'peer': [u'MN', u'EI'], 'step': u'0', 'node_ID': u'0xE050'}, u'MN': {'peer': [u'CP', u'EI'], 'step': u'0', 'node_ID': u'0xE040'}, u'EI': {'peer': [u'MN', u'CP'], 'step': u'1', 'node_ID': u'0xE060'}}
    # vnfc_type_list = [u'CP', u'EI', u'MN']
    # generate_peer_vnfc_dir(vnfcs_info, vnfc_type_list)

    # current_route = '\nTimestamp <09:38:13.866032>\nID   FD   LSIC        RSIC        LIP            LPORT  RIP            RPORT   PROTOCOL  RETAIN  MSGID \n---  ---  ----------  ----------  -------------  -----  -------------  -----   --------  ------  ------\n1    25   0xE040FFFF  0xE050FFFF  192.168.0.101  49156  192.168.0.101  49155   SCTP      YES     0x0001\n2    25   0xE040FFFF  0xE060FFFF  192.168.0.101  49156  192.168.0.102  49155   SCTP      YES     0x0001\n3    25   0xE040FFFF  0xE061FFFF  192.168.0.101  49156  192.168.0.102  49156   SCTP      YES     0x0001\n4    25   0xE040FFFF  0xE300FFFF  192.168.0.101  49156  192.168.0.102  49157   SCTP      YES     0x0001\nPORT   DESTINATION SICAD  MSGID\n-----  -----------------  ------\n '
    # print(current_route)
    # filter_syscom_route_keyword(current_route)

## parameter:  profile file with path  /tmp/syscom_profile.xml
## parameter:  VNFC type list
if __name__ == '__main__':
    main(sys.argv)
