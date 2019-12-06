#include<stdio.h>
#include<stdlib.h>
struct process_table
{
	int at,first_bt,next_bt,ft,tat,wt,temp_bt;
}p[10];


struct Ganttchart
{
	int pid,endtime;
}GT[50];

int ts;
int np;
int nslots=0;
int ct=0;
void Accept();
int getprocessbyRR();
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
		x=getprocessbyRR();
		if(x==-1)
			break;
		GT[nslots].pid=x;

                if(p[x].temp_bt>ts)
                {
		ct=ct+ts;
		p[x].temp_bt=p[x].temp_bt-ts;
                }
                else
                {
                  ct=ct+p[x].temp_bt;
                  p[x].temp_bt=0;
                }

		GT[nslots].endtime=ct;
		nslots++;
	}
 
	for(i=0;i<np;i++)
	{
		p[i].temp_bt=p[i].next_bt;
	}
	while(1)
	{
		x=getprocessbyRR();
		if(x==-1)
			break;
		GT[nslots].pid=x;

		if(p[x].temp_bt>ts)
                {
                ct=ct+ts;
                p[x].temp_bt=p[x].temp_bt-ts;
                }
                else
                {
                  ct=ct+p[x].temp_bt;
                  p[x].temp_bt=0;
                }

		GT[nslots].endtime=ct;
		nslots++;
                if(p[x].temp_bt==0)
                {
                p[x].ft=ct;
                p[x].tat=p[x].ft-p[x].at;
                p[x].wt=p[x].tat-p[x].first_bt-p[x].next_bt-2;
	        }
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
int getprocessbyRR()
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
{	printf("\nEnter the Number of processes:");
	scanf("%d",&np);
	int i;
	for(i=0;i<np;i++)
	{
		printf("\nEnter the arrival time first burst time for %d proccess:",i);
		scanf("%d%d",&p[i].at,&p[i].first_bt);
		p[i].temp_bt=p[i].first_bt;
		p[i].next_bt=(rand()%10)+1;
        }
        printf("\nEnter the TimeSlice:");
        scanf("%d",&ts);
        printf("\n\n");
}

