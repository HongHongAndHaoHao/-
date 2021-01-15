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
main()
{
int p1,p2;
while((p1=fork())==-1);
if(p1==0)
   {
    server();
     exit(0);
}
else
{
while((p2=fork())==-1);
      if (p2==0)
{
custmer();
exit(0);
}
wait(0);
wait(0);
printf("father");
}
}
void server()
{
int msgqid,pid,*pint;
     msgqid=msgget(MSGKEY,0777);
pid=getpid();
pint=(int*)msg.mtext;
*pint=pid;msg.mtype=3;
msgsnd(msgqid,&msg,sizeof(int),0)
printf("client:receive from pid%d\n",*pint);
}


void custmer()
{
int i,pid,*pint;extern cleanup();
for(i=0;i<20;i++)
signal(i,cleanup);
msgqid=msgget(MSGKEY,0777|IPC_CREAT);
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




