/*
Demand Paging
Demand Paging the one of the most commanly used method of implanting the Virtual Memory Management Sceme.
*/
#include<stdio.h>
#include<stdlib.h>
int pages[30],frames[5],np,nf,pf=0;
void accept();
int search(int);
void main()
{
	int i,j;
	accept();
	for(i=0;i<np;i++)
	{
		if(search(pages[i])==1)
		{

			frames[pf%nf]=pages[i];
			pf++;
		}
		for(j=0;j<nf;j++)
		{
			printf("%d\t",frames[j]);
		}
		printf("\n");			
	}
	printf("\n\ntotal no. of page faults:%d\t",pf);
}
int search(int p)
{
	int i;
	for(i=0;i<nf;i++)
	{
		if(frames[i]==p)
		{
			return 0;
		}
	}
	return 1;	
	
}
void accept()
{
	int i;
	printf("\nEnter the Total No. of pages:");
	scanf("%d",&np);
	for(i=0;i<np;i++)
	{
		printf("\nEnter Page Number:");
		scanf("%d",&pages[i]);
	}
	printf("\nEnter the Minimum No. of frames:");
        scanf("%d",&nf);
	for(i=0;i<nf;i++)
        {
         	frames[i]=-1;       
        }
}
