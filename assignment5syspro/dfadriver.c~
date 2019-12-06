/*
DFA driver
Software Description-
Finite automata is a mathematical model of a machine with finite number of internal configurations or states. Input  to the machine is from  a finite
set of symbols that forms the alphabet denoted by sumation symbol. Machine keeps on changing its state on consuming an input symbol and the state can be one
among the finite set of states denoted by Q.these transitions can be specified either by giving a transition table or a transition diagram denoted  by delta
The machine alwys starts in a specific state which is designed as start state and is denoted  as q0. There are some states in Q which are final states or accepting states . The  set of Final States is denoted by F.Thus a Finite automata is characterized by these five components and mathematically it is a five touple.

The langauge accepted by FA is the set of all strings for which  the FA halts in a Final State. The languages accepted by FA are Regular languages. In case of Deterministic FA, the transitions are uniquely defined on a state and input symbol.

DFA driver is a software that helps on a state and input symbol.
*/
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
void Execute();
main()
{
	int ch;
	do
	{
		printf("\n1.accept:");
		printf("\n2.display:");
		printf("\n3.Execute:");
		printf("\n4.exit:");
		printf("\nEnter the choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:accept();
			       break;
			case 2:display();
			       break;
			case 3:Execute();
			       break;
		}
	}while(ch!=4);
}
void accept()
{
	int i,j;
	printf("\nEnter the number of states:");
	scanf("%d",&d.m);
	printf("\nEnter the number of Symbols:");
	scanf("%d",&d.n);
	printf("\nAccept transition of evary states:");
	for(i=0;i<=d.m-1;i++)
	{
		for(j=0;j<=d.n-1;j++)
		{
			printf("\nEnter the transition between q%d and %c is:",i,j+97);
			scanf("%d",&d.delta[i][j]);
		}
	}
        printf("\n Enter the final states:");
        for(i=0;i<=d.m-1;i++)
	{
        scanf("%d",&d.final[i]);
	}  
}
void display()
{
	int i,j;
	printf("\n Display the number of states:");
	printf("%d",d.m);
	printf("\n Display the number of symbols:");
	printf("%d",d.n);
	printf("\nDisplay the transition table:\n");
        for(i=0;i<=d.n-1;i++)
         printf("\t%c",i+97);
        printf("\n--------------------------------------");
	for(i=0;i<=d.m-1;i++)
	{       printf("\nq%d\t",i);
		for(j=0;j<=d.n-1;j++)
		{
			printf("q%d\t",d.delta[i][j]);
		}
		printf("\n");
	}
        printf("\nDisplay the final states:");
        for(i=0;i<=d.m-1;i++)
        printf("%d\t",d.final[i]);
}
void Execute()
{ 
	int i,j,k,l=1;
	char str[30];
	printf("\nEnter the string:");
	scanf("%s",str);
	int len=strlen(str);
	printf("\n string length is %d:",len);
	int cs=0;
	for(i=0;i<len;i++)
	{
		for(j=0;j<d.n;j++)
		{
			if(str[i]==j+97)
				cs=d.delta[cs][j];
		}
	}
	if(d.final[cs]==1)
		printf("\nString is accepted:");
	else
		printf("\nString is rejected:");
}
