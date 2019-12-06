#include<stdio.h>
void accept();
int getLRU(int );
int search(int );
int pages[30],frames[5],np,nf,pf=0,count[5],nc,fno;
void main()
{
	int i,x,j;
	accept();
	for(i=0;i<np;i++)
	{
		x=search(pages[i]);
		if(x==1)
		{
			fno=getLRU(i);
			frames[fno]=pages[i];
			pf++;
			printf("\n\n");
			for(j=0;j<nf;j++)
			{
				printf("\n");
				printf("%d",frames[j]);
			}
		}
	}
	printf("\n\n total number of Page faults=%d",pf);
}
int getLRU(int pos)
{
	int c=1,i,j,max,p;
	for(i=0;i<nf;i++)
	{
		if(frames[i]==-1)
		return i;
	}
	for(i=pos-1;i>=0;i--)
	{
		for(j=0;j<nf;j++)
		{
			if((pages[i]==frames[j])&&(count[j]==0))
			{
				count[j]=c;
				c++;
				break;
			}
		}
	}
	max=count[0];
	p=0;
	for(i=1;i<nf;i++)
	{
		if(max<count[i])
		{
			max=count[i];
			p=i;
		}
	}
	return p;	
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
	nc=nf;
	for(i=0;i<nf;i++)
        {
                frames[i]=-1;
		count[i]=0;
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
