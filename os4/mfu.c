#include<stdio.h>
void accept();
int getMFU(int );
int search(int );
int pages[30],frames[5],np,nf,pf=0,fno;
void main()
{
	int i,x,j;
	accept();
	for(i=0;i<np;i++)
	{
		x=search(pages[i]);
		if(x==1)
		{
			fno=getMFU(i);
			frames[fno]=pages[i];
			pf++;
		}
		printf("\n\n");
		for(j=0;j<nf;j++)
		{	
                       printf("\n");
			printf("%d\t",frames[j]);
		}
	}
	printf("\n\n total number of Page faults=%d",pf);
}
int getMFU(int pos)
{
	int freq[10]={0};
        int count[10]={0};
        int c=1;
	int max,i,j;
	for(i=0;i<nf;i++)
	{
		if(frames[i]==-1)
		{
			return i;
		}
	}
	for(i=pos-1;i>=0;i--)
	{
		for(j=0;j<nf;j++)
		{
			if((pages[i]==frames[j]))
			{
				freq[j]=freq[j]++;                       
			}
		}
	}
	max=freq[0];
	int p=0;
        int maxcount=0;
	for(j=1;j<nf;j++)
	{
		if(freq[j]>max)
		{
			max=freq[j];
			p=j;
		}
	}
	for(i=0;i<nf;i++)
	{
		if(freq[i]==max)
		{
			maxcount++;
		}
	}
	if(maxcount==1)
	{
		return p;
	}
	else
	{
		for(i=pos-1;i>=0;i--)
		{
			for(j=0;j<nf;j++)
			{
				if((pages[i]==frames[j])&&(freq[j]==maxcount)&&(count[j]==0))
				{
					count[j]=c;
					c++;
					break;
				}
			}
		}
                int max1=count[0];
		for(j=1;j<nf;j++)
		{
			if(count[j]>max1)
			{
				max1=count[j];
				p=j;
			}
	       	}
                return p;
	}

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
