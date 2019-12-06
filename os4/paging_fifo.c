#include<stdio.h>
void accept();
int search(int );
int pages[30],frames[5],np,nf,pf=0;
void main()
{
	int i,x,j;
	accept();
	for(i=0;i<np;i++)
	{
		x=search(pages[i]);
		if(x==0)
		{
			printf("\n\nPage %d found in frame\n",pages[i]);
		}
		else
		{
			frames[pf%nf]=pages[i];
			pf++;
		}
		printf("\t");
		for(j=0;j<nf;j++)
		{
			
			printf("%d\n",frames[j]);
		}
	}
	printf("\n\n total number of Page faults=%d",pf);
}
void accept()
{
	int i;
	printf("\n Enter how many pages you have to store:\t");
	scanf("%d",&np);
	for(i=0;i<np;i++)
	{
		printf("\n Enter page number:\t");
		scanf("%d",&pages[i]);
	}
	printf("\n Enter the size of frame:\t");
        scanf("%d",&nf);
	for(i=0;i<nf;i++)
        {
                frames[i]=-1;
        }
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
