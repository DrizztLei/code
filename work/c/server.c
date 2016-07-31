/*************************************
文件名： server.c
linux 下socket网络编程简例  - 服务端程序
服务器端口设为 0x8888   （端口和地址可根据实际情况更改，或者使用参数传入）
服务器地址设为 192.168.1.104
作者:kikilizhm#163.com (将#换为@)
*/
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>
int main()
{
    int sfp,nfp; /* 定义两个描述符 */
    struct sockaddr_in s_add,c_add;
    int sin_size;
    unsigned short portnum = 0x8888; /* 服务端使用端口 */
    printf("server starting.\n");
    sfp = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sfp)
    {
        printf("socket fail ! \r\n");
        return -1;
    }
    printf("socket ok !\r\n");
    /* 填充服务器端口地址信息，以便下面使用此地址和端口监听 */
    bzero(&s_add,sizeof(struct sockaddr_in));
    s_add.sin_family=AF_INET;
    s_add.sin_addr.s_addr=htonl(INADDR_ANY); /* 这里地址使用全0，即所有 */
    s_add.sin_port=htons(portnum);
    /* 使用bind进行绑定端口 */
    if(-1 == bind(sfp,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
    {
        printf("bind fail !\r\n");
        return -1;
    }
    printf("bind ok !\r\n");
    /* 开始监听相应的端口 */
    if(-1 == listen(sfp,5))
    {
        printf("listen fail !\r\n");
        return -1;
    }
    printf("listen ok\r\n");
    while(1)
    {
        sin_size = sizeof(struct sockaddr_in);
        /* accept服务端使用函数，调用时即进入阻塞状态，等待用户进行连接，在没有客户端进行连接时，程序停止在此处，
           不会看到后面的打印，当有客户端进行连接时，程序马上执行一次，然后再次循环到此处继续等待。
           此处accept的第二个参数用于获取客户端的端口和地址信息。
        */
        nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);
        if(-1 == nfp)
        {
            printf("accept fail !\r\n");
            return -1;
        }
        printf("accept ok!\r\nServer start get connect from %#x : %#x\r\n",ntohl(c_add.sin_addr.s_addr),ntohs(c_add.sin_port));
        /* 这里使用write向客户端发送信息，也可以尝试使用其他函数实现 */
        if(-1 == write(nfp,"hello,welcome to my server \r\n",32))
        {
            printf("write fail!\r\n");
            return -1;
        }
        printf("write ok!\r\n");
        close(nfp);
    }
    close(sfp);
    return 0;
}
