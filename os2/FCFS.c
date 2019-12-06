/*
CPU Scheduling
CPU Scheduling is one of the important task is one of the important task performed by the operating system.In multiprogramming operating systems many processes are loaded into memory for execution and these processes are sharing the CPU and other resources of computer system.

Schedular is a program that decides which program will execute next at the CPU which program will be loaded into memory for execution.

CPU schedular is a program module of an operating system that selects the process to execute next at CPU out of the processes that are in memory.This schedular is also called as Short term schedular or CPU Scheduler
There are 3 types of schedulars as

1)Short Term Schedular
2)Long Term Schedular
3)Medium Term Schedular

We have to implement various Short Term Scheduling algorithm as a part of this practical assignment

Various CPU Scheduling algorithms are:
1)First Come First Serve(FCFS)
2)Shortest Job First(SJF)
3)Priority Scheduling
4) Round Robin Scheduling(RR)

These scheduling algorithms are further classified into 2 types as Preemptive and Non-Preemptive.FCFS scheduling is always Non-Preemptive while Round Robin is always Preemptive ,While Shortest Job First and Priority Scheduling can be preemptive or non-preemptive

The performance of various scheduling algorithms is compared on the basis of following criteria called as scheduling criteria's as
1)CPU Utilization
2)Throughput
3)Turnaround Time
4)Waiting Time
5)Response Time
*/
#include<stdio.h>
#include<stdlib.h>
struct process_table
{
	int at,first_bt,next_bt,ft,tat,wt,temp_bt;
}p[10];

struct Ganttchart
{
	int pid,endtime;
}GT[30];


int np;
int nslots=0;
int ct=0;
void Accept();
int getprocessbyFCFS();
void showPT();
void showGT();
void showAvg();
main()
{
        int i;
	int x;
	Accept();
	while(1)
	{
		x=getprocessbyFCFS();
		if(x==-1)
			break;
		GT[nslots].pid=x;
		ct=ct+p[x].temp_bt;
		p[x].temp_bt=0;
		GT[nslots].endtime=ct;
		nslots++;
	}
 
	for(i=0;i<np;i++)
	{
		p[i].temp_bt=p[i].next_bt;
	}
	while(1)
	{
		x=getprocessbyFCFS();
		if(x==-1)
			break;
		GT[nslots].pid=x;
		ct=ct+p[x].temp_bt;
  		p[x].temp_bt=0;
		GT[nslots].endtime=ct;
		nslots++;
                p[x].ft=ct;
                p[x].tat=p[x].ft-p[x].at;
                p[x].wt=p[x].tat-p[x].first_bt-p[x].next_bt-2;
	}
        showPT();
        printf("\n\n");
        showGT();
        showAvg();
}
void showAvg()
{
         int i;
        float l=0,m=0;
        for(i=0;i<np;i++)
	{
         l=l+p[i].tat;
         m=m+p[i].wt;
	}
        float avgtat,avgwt;
        avgwt=m/np;
        avgtat=l/np;
        printf("\n\n");
        printf("\nAverage turnaround time=%f",avgtat);
        printf("\nAverage waiting time=%f\n\n",avgwt);
}
void showPT()
{
	int i;
	printf("process\tAT\tBT1\tBT2\tFT\tTAT\tWT\n");
	for(i=0;i<np;i++)
	{
		printf("p%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,p[i].at,p[i].first_bt,p[i].next_bt,p[i].ft,p[i].tat,p[i].wt);
	}
}
void showGT()
{       
        int i;
        printf("\n\n");
        for(i=0;i<(nslots*5);i++)
        printf("-");
        printf("\n");
        printf("|");
        for(i=0;i<nslots;i++)
	{
        printf(" P%d |",GT[i].pid);
	}
        printf("\n");
        for(i=0;i<(nslots*5);i++)
        printf("-");
        printf("\n");
        printf("0  ");
        for(i=0;i<nslots;i++)
	{
        printf(" %d   ",GT[i].endtime);
	}
}
int getprocessbyFCFS()
{
	int i;
	int pno=-1;
	int min=1000;
	for(i=0;i<np;i++)
	{
		if(min>p[i].at && p[i].temp_bt>0 && p[i].at<=ct)
		{
			min=p[i].at;
			pno=i;
		}
	}
	return pno;
}


void Accept()
{
	printf("\nEnter the Number of processes:");
	scanf("%d",&np);
	int i;
	for(i=0;i<np;i++)
	{
		printf("\nEnter the arrival time first burst time for %d proccess:",i);
		scanf("%d%d",&p[i].at,&p[i].first_bt);
		p[i].temp_bt=p[i].first_bt;
		p[i].next_bt=(rand()%10)+1;
        }
       printf("\n\n");
}

