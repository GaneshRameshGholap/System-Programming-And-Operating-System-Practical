/*
Banker's Algorithm
Software Description- This algorithm is related to handling deadlocks.There are three methods to handle deadlocks
1)Deadlock Prevention
2)Deadlock Avoidance
3)Deadlock Detection
*/
#include<stdio.h>
#include<stdlib.h>
int Avail[10];

int Max[10][10];
int Alloc[10][10];
int Need[10][10];
int Request[10];
int Finish[10]={0};
int work[10];
int Safe[10]={0};
int n,m;
int proc;
int pno;
void Accept_matrix();
void Display_matrix();
void Find_Need();
void Accept_available();
void Bankers_algo();
void Safety_algo();
int compare_need(int);
void resource_request_algo();
void Accept_Request();
main()
{
	printf("Enter the no.of processes and resources");
	scanf("%d%d",&n,&m);
	int ch;
	while(1)
	{
		printf("\n.menu");
		printf("\n1.Accept_matrix:");
		printf("\n2.Accept_avialable:");
		printf("\n3.Find_Need");
		printf("\n4.Display_matrix:");
		printf("\n5.Accept_request:");
		printf("\n6.Bankers:");
		printf("\n8.Apply Saftey Algo");
                printf("\n9.exit:");
		printf("\nEnter the choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:Accept_matrix();break;
			case 2:Accept_available();break;
			case 3:Find_Need();break;
			case 4:Display_matrix();break;
			case 5:Accept_Request();break;
			case 6:Bankers_algo();break;
                        case 7:Saftey_algo();break;
			case 8:exit(0);break;
		}
	}
}
void Bankers_algo()
{
	resource_request_algo();
}
void resource_request_algo()
{
	int i;
	//check if Requesti<=Needi
	for(i=0;i<m;i++)
	{
		if(Request[i]>Need[proc][i])
		{
			printf("Error..process exceeds its Max demand");
			exit(1);
		}
	}
	//check if Request[i]<=Available
	for(i=0;i<m;i++)
	{
		if(Request[i]>Avail[i])
		{
			printf("Process must wait,resources not available");
			exit(1);
		}
	}
	//pretend to have allocated requested resources
	for(i=0;i<m;i++)
	{
		Avail[i]=Avail[i]-Request[i];
		Alloc[proc][i]=Alloc[proc][i]+Request[i];
		Need[proc][i]=Need[proc][i]-Request[i];
	}
	//run Saftey algorithm to check wheather safe sequesnce exists or not
	Safety_algo();
}
void Safety_algo()
{
	int over=0,i,j,k,I=0,flag;
	//initialize work=available
	for(i=0;i<m;i++)
		work[i]=Avail[i];
	while(!over)
	{
		//check for any not finished process
		for(i=0;i<n;i++)
		{
			if(Finish[i]==0)
			{
				flag=0;
				pno=compare_need(i);
				if(pno>-1)
					break;
			}
		}
		if(i==n)
		{
			printf("System is unsafe");
			exit(1);
		}
		if(i<n && pno>=0)
		{
			for(k=0;k<m;k++)
				work[k]+=Alloc[pno][k];
			Finish[pno]=1;
			Safe[I++]=pno;//add process in safe sequence
			if(I>=n)
			{
				printf("\nSafe sequence is:");
				for(I=0;I<n;I++)
					printf("P%d\t",Safe[I]);
				over=1;
			}
		}
	}
}
int compare_need(int p)
{
	int i,j,flag=0;
	for(j=0;j<m;j++)
	{
		if(Need[p][j]>work[j])
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
		return p;
	return -1;
}
void Accept_Request()
{
	int i;
	printf("\nEnter process no:");
	scanf("%d",&proc);
	for(i=0;i<m;i++)
	{
		scanf("%d",&Request[i]);
	}
}
void Accept_available()
{
	int i;
	printf("\nEnter the Available vector:");
	for(i=0;i<m;i++)
	{
		printf("\nDisplay the available resources of resource type %d:",i);
		scanf("%d",&Avail[i]);
	}
}
void Accept_matrix()
{
	int i,j;
	printf("\nEnter the Allocation Matrix:");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&Alloc[i][j]);
		}
	}
	printf("\nEnter the Maximum Demand matrix:");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&Max[i][j]);
		}
	}
}
void Find_Need()
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			Need[i][j]=Max[i][j]-Alloc[i][j];
		}
	}
}
void Display_matrix()
{
	int i,j;
	printf("\n\tAllocation\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%d\t",Alloc[i][j]);	
		}
		printf("\n");
	}
	printf("\n\tMax\n:");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%d\t",Max[i][j]);
		}
		printf("\n");
	}
	printf("\n\tNeed\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%d\t",Need[i][j]);
		}
		printf("\n");
	}
	printf("\nAvailable\n");
	for(j=0;j<m;j++)
	{
		printf("%d",Avail[j]);
		printf("\t");
	}
}
