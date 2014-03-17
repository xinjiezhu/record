/*
 * protocol.c
 *
 */
#include "protocol.h"
#include "debug.h"

/**
 *@brief zip protocol
 *
 *@pragram[in] int socket, char *buffer, void *p_data, int data_length, PackType pack_type
 *
 *@return RET_OK success
 *@return RET_ERR fail
 */
int ProtocolZip(int sock, char *buffer, void *p_data, int data_length, PackType pack_type)
{
    /**initialize*/
    int ret = -1;

    PackHead *p_pack_head = NULL;
    p_pack_head = (PackHead *)buffer;
        
    memset(buffer, 0, sizeof(buffer));

    p_pack_head->version = htons(VERSION);
    p_pack_head->type = htons(pack_type);
    p_pack_head->len = htonl(data_length);
    /*
    Debug("p_pack_head->version = [%d], p_pack_head->type = [%d], p_pack_head->len = [%d]\n", \
        ntohs(p_pack_head->version), ntohs(p_pack_head->type), ntohl(p_pack_head->len));
    */
    memcpy(p_pack_head->buf, p_data, data_length);

    if (0 > (ret = write(sock, buffer, PACK_HEAD_LENGTH + data_length)))
    {
        DEBUGLOG("write error");
        return RET_ERR;
    }
    return RET_OK;

}



/**
 *@brief unzip protocol
 *
 *@pragram[in] int socket, char *buffer
 *
 *@pragran[out] PackHead **p_pack_head void **p_data
 *
 *@return int ret
 *
 */
int ProtocolUnzip(int sock, char *buffer, int data_length,
                  PackHead **p_pack_head, void **p_data)
{
    int ret = RET_ERR;
    
    /**read*/
    if (0 > (ret = read(sock, buffer, PACK_HEAD_LENGTH + data_length)))
    {
        DEBUGLOG("read error");
        return ret;
    }
    if (0 == ret)
    {
        return ret;
    }

    *p_pack_head = (PackHead *)buffer;
    /*
    Debug("*p_pack_head->version = [%d], *p_pack_head->type = [%d], *p_pack_head->len = [%d]\n", \
        ntohs((*p_pack_head)->version), ntohs((*p_pack_head)->type), ntohl((*p_pack_head)->len));
    */
    *p_data = (*p_pack_head)->buf;
    return ret;
}


/**
 *@brief get newest online list;
 *
 *@paragram 
 *
 *@return head pointer
 *
 */
LNode *GetOnlineUserList(int g_tcp_sock, LinkList p_online_user_head)
{

    char buf[BUFFER_SIZE] = {0};
    int bytesread = RET_ERR;
    PackHead *p_pack_head = NULL;
    void *p_data;

    trace();
    ProtocolZip(g_tcp_sock, buf, NULL, 0, OICQ_REQ_CLIENTS);
    trace();
    while (1)
    {
        trace();
        if (0 > (bytesread  = ProtocolUnzip(g_tcp_sock, buf, 
                            ONLINE_USER_INFO_LENGTH, &p_pack_head, &p_data)))
        {
            DEBUGLOG("Protocol unzip error");
            raise(SIGUSR1);
        }
        trace();
        if (OICQ_ASK_CLIENTS == ntohs(p_pack_head->type))
        {
            /**receive online user list from service*/
            p_online_user_head = CreateOnlineUserList(p_online_user_head, p_data);

            
        }
        trace();
        if (OICQ_EXIT == ntohs(p_pack_head->type))
        {
            trace();
            break;
        }
    } 
    trace();
    return p_online_user_head;
}
