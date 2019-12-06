#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct DFA{
	int m;
	int n;
	int delta[10][10];
	int final[10];
};
struct DFA d={3,3,{{1,0,0},{2,0,0},{2,2,2}},{0,0,1}};
void accept();
void display();
void execute();
int main()
{
	int ch;
      while(1)
{
	printf("\n.menu");
	printf("\n1.Accept");
	printf("\n2.display");
	printf("\n3.execute");
	printf("\n4.exit");
	printf("\nEnter the choice:");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:accept();break;
		case 2:display();break;
		case 3:execute();break;
		case 4:exit(0);
	}
}
}
void execute()
{
        int i,j;
	char str[30];
	printf("\nEnter the string:");
	scanf("%s",str);
	int len=strlen(str);
	int cs=0;
	for(i=0;i<len;i++)
	{
		for(j=0;j<d.n;j++)
		{
			if(str[i]==j+97)
			{
				cs=d.delta[cs][j];
			}
		}
	}
	if(d.final[cs]==1)
	{
		printf("\nString is accepted:");
	}
	else
	{
		printf("\nString is Rejected");
	}
}
void accept()
{
       int i,j;
	printf("\nEnter the sates:");
	scanf("%d",&d.m);
	printf("\nEnter the symbols:");
	scanf("%d",&d.n);
	printf("\nEnter the transitional table:");
	for(i=0;i<d.m;i++)
	{
		for(j=0;j<d.n;j++)
		{
			printf("\nEnter the transition between state q%d and %c:",i,j+97);
			scanf("%d",&d.delta[i][j]);
		}
	}
	printf("\nEnter the transitional table:");
	for(j=0;j<d.m;j++)
	{
		scanf("%d",&d.final[j]);
	}
}
void display()
{
       int i,j;
	printf("\nNumber of states:");
	printf("%d",d.m);
	printf("\nNumber of symbols:");
	printf("%d",d.n);
	printf("\nTransitional Table\n");
        printf("\t");
	for(i=0;i<d.n;i++)
	{
		printf("%c\t",i+97);
	}
        printf("\n");
	for(i=0;i<d.m;i++)
	{
		printf("q%d\t",i);
		for(j=0;j<d.n;j++)
		{
			printf("q%d\t",d.delta[i][j]);
		}
		printf("\n");
	}
	printf("\nDisplay final states:");
	for(j=0;j<d.m;j++)
	{
		printf("%d\t",d.final[j]);
	}

}
