#include<stdio.h>
#define N 50
int b[N];
struct PCB
{
	int pn;   //process name进程名字
	int at;   //arrival time到达时间
	int st;   //service time服务时间
	int ct;   //completion time完成时刻
	int sc;  //sign completion标志是否完成
	int st1;  //剩余服务时间 
}process[N];
 
int sjf(int n)       //short job first函数 
{
	int i,j,x,y;
	for(i=1;i<=n;i++)      //输入各进程信息，存储到process数组中
	{
		process[i].sc=0;
		printf("\n%d:\n请依次输入进程的信息\n请输入pn:",i);
		scanf("%d",&process[i].pn);
		printf("请输入at:");
		scanf("%d",&process[i].at);
		printf("请输入st:");
		scanf("%d",&process[i].st);
		process[i].st1=process[i].st;
	}
	
	for(i=1;i<n;i++)      //排序，按到达时间升序排序，如果dt相等，则按st升序排序 
	for(j=1;j<n;j++)
	{
		if(process[j].at>process[j+1].at)
		{
			process[0]=process[j];
			process[j]=process[j+1];
			process[j+1]=process[0];
		}
		else if(process[j].at==process[j+1].at)
		{
			if(process[j].st>process[j+1].st)
			{
				process[0]=process[j];
				process[j]=process[j+1];
				process[j+1]=process[0];
			}
		}
	}
	
	//for(i=1;i<=n;i++)      //检查排序是否正确 
	//printf("%d %d %d\n",process[i].pn,process[i].at,process[i].st);
	
	printf("\n第几次调度进程 运行的进程pn 开始运行时间 运行时间 剩余服务时间 结束时间\n");
	int z=1;   //记录第几次调度进程 
	
	int time=process[1].at;    //最先到达的最短进程先执行 
	int sum=0;
	process[1].ct=time+process[1].st;
	process[1].sc=1;     
	process[1].st1=0;    
	time=process[1].ct;
	sum+=1;
	printf("%8d%12d%15d%11d%11d%11d\n",z++,process[1].pn,time-process[1].st,process[1].st,0,process[1].ct);
	
	int Tst=process[1].st,T;    //T记录所有进程中最长的时间
	for(i=2;i<=n;i++)           //Tst每次记录剩下该执行进程中最短作业长度  
		{
			if(process[i].st>Tst) Tst=process[i].st;
		}
	int M=2;//要调度的下一个进程
	
	while(sum<n)    //还有没执行的进程就继续 
	{
		T=Tst+1;
	for(i=2;i<=n;i++)       
	{
		if(process[i].sc==0)//如果还没完成
		{
	    	if(process[i].at<=time)//到达时间是否早于当前时间
	    	{
	    	if(process[i].st<T) {T=process[i].st;M=i;}
			}
			else break;
		}
	}
	
	if(process[M].sc==0)
	{
		if(time<process[M].at) time=process[M].at;
	 	time+=process[M].st;
	 	process[M].sc=1;
	 	process[M].st1=0;
	 	process[M].ct=time;
	 	sum++;
	 	printf("%8d%12d%15d%11d%11d%11d\n",z++,process[M].pn,time-process[M].st,process[M].st,0,process[M].ct);
	 	if(time<process[M+1].at) time=process[M+1].at;
	}
	}
}
 
int main()
{
	int n;
	printf("\t\t短作业优先调度算法\n");
	printf("请输入总进程数：\n");
	scanf("%d",&n);
	sjf(n);
	return 0;
}

