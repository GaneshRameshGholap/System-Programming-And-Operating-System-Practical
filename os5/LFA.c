/*
Linked File Allocation
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct FAT
{
char fname[20];
int  ib;
struct FAT *next;
}*start=NULL;
int tb;
int *bitvector;
void createFile();
int search();
void deleteFile();
void showFAT();
void showAllocated();
void showAvailable();
int main()
{
	int ch;
	printf("Enter the number of blocks:");
	scanf("%d",&tb);
	bitvector=(int*)malloc(sizeof(int)*tb);
	int i;
	//bitvector=(int*)calloc((sizeof(int)),tb);
	for(i=0;i<tb;i++)
	{
		bitvector[i]=0;
	}
	while(1)
	{
		printf("\n.Menu:");
		printf("\n1.create file:");
		printf("\n2.Delete file:");
		printf("\n3.show file allocation table:");
		printf("\n4.show allocated blocks:");
		printf("\n5.show available blocks:");
		printf("\n6.exit:");
		printf("\nEnter the choice:");
		scanf("%d",&ch);
		switch(ch)
		{
                        case 1:createFile();break;
                        case 2:deleteFile();break;
                        case 3:showFAT();break;
                        case 4:showAllocated();break;
                        case 5:showAvailable();break;
			case 6:exit(0);break;
		}
	}
}
void deleteFile()
{
        int i,j,ibno,k,tmp;
        struct FAT *q,*q1;
	char str[20];
	printf("Enter the file name:");
	scanf("%s",str);
	int x=search(str);
	if(x==-1)
	{
		printf("File Not Exist:");
		return;
	}
	else
	{
		if(x==1)
                {
                        q=start;
                        start=start->next;
			ibno=q->ib;
                        free(q);
                }
		else
		{
			q=start;
			for(i=0;i<(x-1);i++)
			{
				q1=q;
				q=q->next;
			}
			q1->next=q->next;
			ibno=q->ib;
                	free(q);
		}
		k=ibno;
		while(bitvector[k]!=-1)
		{
			tmp=k;
			k=bitvector[k];
			bitvector[tmp]=0;
		}
		bitvector[k]=0;
	} 
}
void showAllocated()
{
	int i;
	for(i=0;i<tb;i++)
	{
		if(bitvector[i]!=0)
		{
			printf("%d\t",i);
		}
	}
}
void showAvailable()
{
	int i;
	for(i=0;i<tb;i++)
	{
		if(bitvector[i]==0)
		{
                 printf("%d\t",i);
		}
	}
}
void showFAT()
{
	struct FAT *q;
	printf("\nFile_name\tinitial_block\n");
	q=start;
	while(q!=NULL)
	{
		printf("\t%s\t\t%d\n",q->fname,q->ib);
                   q=q->next;
	}
}
void createFile()
{
	char str[20];
	int n;
	printf("\nEnter The File Name:");
	scanf("%s",str);
	printf("\nEnter the number of blocks:");
	scanf("%d",&n);
	int x=search(str);
	if(x!=-1)
	{
		printf("File already exist:");
		return;
	}
        int i,j,cnt=0;
	
	for(i=0;i<tb;i++)
	{
		if(bitvector[i]==0)
		{
			cnt++;
		}
	}
	if(cnt<n)
	{
		printf("\n Memory is full");
		return;
	}
	int c=0,nb,tp,initialblock;
	for(i=0;i<tb;i++)
	{
		if(bitvector[i]==0)
		{
			if(c==0)
			{
				initialblock=i;
				tp=i;
				c++;
			}
			else
			{
				bitvector[tp]=i;
				c++;
				tp=i;
				if(c==n)
				{
					bitvector[i]=-1;
					break;
				}
			}
		}
	}
	struct FAT *temp,*q;
	temp=(struct FAT*)malloc(sizeof(struct FAT));
	if(start==NULL)
	{
		strcpy(temp->fname,str);
		temp->ib=initialblock;
		temp->next=NULL;
		start=temp;
	}
	else
	{
		q=start;
		while(q->next!=NULL)
		{
			q=q->next;
		}
                q->next=temp;
		strcpy(temp->fname,str);
		temp->ib=initialblock;
	}
}
int search(char str[20])
{
	int pos=1;
	struct FAT *q=start;
	while(q!=NULL)
	{
		if(strcmp(q->fname,str)==0)
		{
			return pos;
		}
		q=q->next;
		pos++;
	}
	return -1; 
}

