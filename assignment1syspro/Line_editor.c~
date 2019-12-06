/*
Line Editor
Software Description-Editors are used to create digital copies of source program.Tha main functions supported by an editor is editing,viewing and navigating
through the text.A line editor limits all operations to a line of text. The line is indicated positionally by giving line number i.e. its serial number in the text or contextually by specifying a context which uniquely identifies the position.

The file to be edited is taken as command line argument. An empty file is opened for editing if no argument is supplied

The editor has two modes
1)The Command mode
2)input mode

In command mode it displays '?' as prompt and accepts single-line commands.If 'i' for insert or 'a' for append command is given, it goes into input mode and accepts lines as text. When a line containing a single '.' is given back to command mode.

The program at the start displays 'lines:' followed by number of lines(0 if file is empty or not specified) and goes into command mode.
The command format is a single character indicating the action followed by three optional integers separated by spaces.
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node
{
	char info[20];
	struct node *link;
}NODE; 
NODE *start=NULL;
void nodeFile();
char fname[20];
void Append(char [80]);
void print(int,int);
void insert(int);
void delete(int,int);
void Del(int);
void copy(int,int);
void move(int,int);
void save();
void find();
int main(int argc,char *argv[])
{       
        char cmd[20];
	char ch;
	int n1,n2,n3;
	int x;
        char str[20];
	if(argc!=2)
	{
		printf("\n Error in arguments:");
		exit(0);
	}
	strcpy(fname,argv[1]);
	nodeFile();
	int n=count();
	printf("\n Number of Lines=%d\n",n);
	while(1)
	{
		printf("\nEnter command$:");
		fgets(cmd,20,stdin);
		x=sscanf(cmd,"%c%d%d%d",&ch,&n1,&n2,&n3);
		switch(ch)
		{
			case 'p':if(x==1)
				 {
					 print(1,1);
				 }
				 if(x==2)
				 {
					 print(n1,n1);
				 }
				 if(x==3)
				 {
					 print(n1,n2);
				 }
				 break;
                        case 'f':if(x==1)
                                 {
                                  find();
                                 }
                                  break;
			case 'i':if(x==2)
				 {
					 insert(n1);
				 } 
				 break;
			case 'd':if(x==2)
				 {
					 delete(n1,n1);
				 }
				 if(x==3)
				 {
					 delete(n1,n2);
				 }
				 break;
                        case 'c':if(x==3)
                                   {
                                    copy(n1,n2);
                                   }
                                  break;
			case 'm':if(x==3)
				 {
					 move(n1,n2);
				 }
				 break;
                        case 's':if(x==1)
                                 save();
                                 break;
			case 'a':printf("\n enter line:");
				 fgets(str,80,stdin);
				 Append(str);
				 break;
			case 'q':exit(0);
		}
	}
}
void find()
{
int i;
char str[80];
printf("\nEnter the data to search:");
fgets(str,80,stdin);
int pos=1;
NODE *q;
q=start;
while(q!=NULL)
{
if(strcmp(q->info,str)==0)
{
printf("\nLine %s is found at %d position:",str,pos);
}
q=q->link;
pos++;
}
}
void save()
{
	FILE *fp;
	fp=fopen("data","w");
	NODE *q;
	q=start;
	while(q!=NULL)
	{
		fputs(q->info,fp);
		q=q->link;
	}
        fclose(fp);
}
void move(int m,int n)
{
	int c;
        c=count();
        if((m>c) || (n>c) || (m<1) || (n<1))
        {
                printf("\n Invalid operation:");
                return;
        }
        copy(m,n);
        Del(m);
}
void copy(int m,int n)
{
        int c;
        c=count();

        if((m>c) || (n>c) || (m<1) || (n<1))
        {
                printf("\n Invalid operation:");
                return;
        }

	NODE *q1,*q2;
	q1=start;
	q2=start;
	int i;
	for(i=1;i<m;i++)
	{
		q1=q1->link;
	}
	for(i=1;i<n-1;i++)
	{
		q2=q2->link;
	}
	NODE *tmp;
         tmp=malloc(sizeof(NODE));
	strcpy(tmp->info,q1->info);
	tmp->link=q2->link;  
	q2->link=tmp;
}
void delete(int m,int n)
{        
	int i,c,j;
	c=count();
	if((m>c) || (n>c) || (m<1) || (n<1)||(m>n))
	{
		printf("\n Invalid operation:");
		return;
	}
	if(start==NULL)
	{
		printf("\n list empty:");
		return;
	}
	for(i=m;i<=n;i++)
	{
		Del(i);
	} 
}
void Del(int x)
{
       int i;
	NODE *ptr,*temp;
	if(x==1)
	{
		temp=start;
		start=start->link;
		free(temp);
	}
	else
	{
		temp=start;
		for(i=1;i<x;i++)
		{
			ptr=temp;
			temp=temp->link;
		}
                ptr->link=temp->link;
                 free(temp);
	}
}
void insert(int m)
{        
	int i;
	char str[80];
	NODE *q,*tmp;
	q=start;
	tmp=malloc(sizeof(NODE));
	printf("\n enter the line:");
	fgets(str,80,stdin);
	strcpy(tmp->info,str);
	if(m==1)
	{
		tmp->link=start;
		start=tmp;
	}
	else
	{
		for(i=1;i<m-1;i++)
		{
			q=q->link;
		}
		tmp->link=q->link;
		q->link=tmp;
	}
}
void print(int m,int n)
{
	NODE *q;
	q=start;
	int i,j,c;
	c=count();
	if((m>c) || (n>c) || (m<1) || (n<1)||(m>n))
	{
		printf("\n Invalid operation:");
		return;
	}
	if(start==NULL)
	{
		printf("\n list is empty:");
		return;
	}
	for(i=1;i<m;i++)
	{
		q=q->link;
	}
	for(i=m;i<=n;i++)
	{
		printf("%s\n",q->info);
		q=q->link;
	}
}
void nodeFile()
{       char str[80];
	FILE *fp;
	fp=fopen(fname,"r");
	while(fgets(str,80,fp)!=NULL)
	{
		Append(str);
	}
	fclose(fp);
}
void Append(char s[80])
{
	NODE *tmp,*q;
	tmp=malloc(sizeof(NODE));
	strcpy(tmp->info,s);
	tmp->link=NULL;
	if(start==NULL)
	{
		start=tmp;
	}
	else
	{
		q=start;
		while(q->link!=NULL)
		{
			q=q->link;
		}
		q->link=tmp;
	}
}
int count()
{
	int count=0;
	NODE *q;
	q=start;
	while(q!=NULL)
	{
		count++;
		q=q->link;
	}
	return (count);
}

