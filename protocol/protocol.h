/*
 * protocol.h
 *
 */

#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "oicq.h"


int ProtocolZip(int socket, char *buffer,
                 void *p_data, int data_length, 
                 PackType pack_type);
int ProtocolUnzip(int sock, char *buffer, int data_length,
                  PackHead **p_pack_head, void **p_data);
LNode *GetOnlineUserList(int g_tcp_sock, LinkList p_online_user_head);


#endif /**< __PROTOCOL_H*/
