#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MSGKEY 80
struct msgform
{
long mtype;
char mtext[1024];
}msg;
int msgqid;
void server();
void custmer();

void server()
{
int msgqid,pid,*pint;
msgqid=msgget(MSGKEY,0777);//得到消息队列标识符或创建一个消息队列对象   返回消息队列的标识符
pid=getpid();
pint=(int*)msg.mtext;
*pint=pid;msg.mtype=3;
msgsnd(msgqid,&msg,sizeof(int),0);//将消息写入到消息队列
printf("client:receive from pid%d\n",*pint);
}
void custmer()
{
int i,pid,*pint;extern cleanup();
for(i=0;i<20;i++)
signal(i,cleanup);
msgqid=msgget(MSGKEY,0777|IPC_CREAT);//从消息队列读取消
{
msgrvc(msgqid,&msg,256,3,0);
pint=(int*)msg.mtext;
pid=*pint;
printf("server:receive from pid%d\n",pid);
}
}
cleanup()
{
msgctl(msgqid,IPC_RMID,0);
exit(0);
}


main()
{
int p1,p2;
while((p1=fork())==-1);//建立进程1
if(p1==0)
{
server();
}
else
{
while((p2=fork())==-1);//建立进程2
if (p2==0)
{
custmer();
}
wait(0);
wait(0);
printf("father");
}
}
