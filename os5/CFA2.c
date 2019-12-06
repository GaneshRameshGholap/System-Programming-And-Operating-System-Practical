#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct FAT
{
char fname[20];
int  ib,nb;
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
        int i,j;
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
		q=start;
		for(i=0;i<(x-1);i++)
		{
			q1=q;
			q=q->next;
		}
		for(j=q->ib;j<(q->ib+q->nb);j++)
		{
			bitvector[j]=0;
		}
		if(x==1)
		{
			q=start;
			start=start->next;
			free(q);
		}
                else
                {
		q1->next=q->next;
		free(q);
                }
	} 
}
void showAllocated()
{
	int i;
	for(i=0;i<tb;i++)
	{
		if(bitvector[i]==1)
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
	int i;
	struct FAT *q;
	printf("\nFile_name\tinitial_block\tnumber_of_blocks\n");
	q=start;
	while(q!=NULL)
	{
		printf("\t%s\t\t%d\t\t%d\n",q->fname,q->ib,q->nb);
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
        int i,j;
	for(i=0;i<tb;i++)
	{
		x=0;
		for(j=i;j<tb;j++)
		{
			if(bitvector[j]==0)
			{
				x++;
			}
			else
			{
				break;
			}
		}
		if(x>=n)
		{
			break;
		}
	}
	if(i==tb)
	{
		printf("Memory full\n:");
		return;
	}
	for(j=i;j<(i+n);j++)
	{
		bitvector[j]=1;
	}
	struct FAT *temp,*q;
	temp=(struct FAT*)malloc(sizeof(struct FAT));
	if(start==NULL)
	{
		strcpy(temp->fname,str);
		temp->ib=i;
		temp->nb=n;
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
		temp->nb=n;
		temp->ib=i;
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

