/*
Macro Processor
Software Description-
An assembly language macro is a facility for extending the set of operations provided in an assembly language. A programmer can define his own set of macros only once and can use them many times.

A macro definition consists of a name, a set of formal parameters and a body of code. When a macro name along with a set of actual parameters is used,
it is replaced by body of macro and it is called macro expansion.

Macro processor is a software that takes as input  a program containing macro definitions and calls and generates  an assembly language program which 
is free of macro definitions and where macro calls have been properly expanded. Macro processor has two main steps.
i)Processing macro definitions
ii)macro expansion

In The first step each macro definition is processed to extract information and is stored in well defined data structures. In macro expansion each macro call is expanded using appropriate information from the tables.

Data Structure Design-
Macro Name Table
Parameter Name Table
Keyword Parameter Default Value Table
Macro Definition Table
Actual Parameter Table
Pointers to Various Tables
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct mnttab{
	char name[30];
	int pp;
	int kp;
	int kpdptr;
	int mdtptr;
}mnt[30];
struct kpdtab{
	char kname[30];
	char kvalue[30];
}kpd[10];
char pnt[10][30];
struct MDT
{
	int count;
	char data[4][10];
}mdt[10];
int mdtcnt=0;
int kpdcnt=0;
int pntcnt=0;
int mntcnt=0;
char fname[30];
FILE *fp;
char str[80];
char s1[40],s2[40];
void Extract();
void addmnt();
void formallist();
void addpnt();
void addkpdt();
void addmdt();
void Displaymnt();
void Displaypnt();
void Displaykptd();
void  Displaymdt();
char formal[10][20];
main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("Invalid Argument");
		return;
	}
	strcpy(fname,argv[1]); 
	fp=fopen(fname,"r");
	while(fgets(str,80,fp)!=NULL)
	{
		printf("%s\n",str);
	}
	fclose(fp);
        Extract();
}
void Extract()
{       
        
	fp=fopen(fname,"r");
	fgets(str,80,fp);
	sscanf(str,"%s%s",s1,s2);
	if(strcmp(s1,"MACRO")==0)
	{
		fgets(str,80,fp);
		sscanf(str,"%s%s",s1,s2);
		addmnt();
                formallist();
                addpnt();
                addkpdt();
                addmdt();
	}
       Displaymnt();
       Displaypnt();
       Displaykptd();
       Displaymdt();
       fclose(fp);
}
void addmdt()
{         
           char str[80];
           char p[10][30];
           int n;
           int i;
	  while(1)
	  {
		  fgets(str,80,fp);
		  n=sscanf(str,"%s%s%s%s",p[0],p[1],p[2],p[3]);
                  printf("count=%d\n",n);
		  mdt[mdtcnt].count=n;
                  if(strcmp("MEND",p[0])==0)
		  {


			  strcpy(mdt[mdtcnt].data[0],p[0]);
			  mdtcnt++;
			  break;
		  }
		  else
		  {
			  for(i=0;i<n;i++)
			  {
				  strcpy(mdt[mdtcnt].data[i],p[i]);
			  }
			  mdtcnt++;
		  }
	  }
        
}
void Displaymdt()
{
	int i,j;
	printf("\n Count\t\t data\n");
	for(i=0;i<mdtcnt;i++)
	{
		printf("%d\t",mdt[i].count);
                for(j=0;j<mdt[i].count;j++)
                {
		printf("%s\t",mdt[i].data[j]);
                }
                printf("\n");
	}
}
void  addkpdt()
{
        char *p;
	char c[2][20];
	int i,k=0;
	for(i=mnt[mntcnt-1].pp;i<(mnt[mntcnt-1].pp+mnt[mntcnt-1].kp);i++)
	{
		p=strtok(formal[i],"=");
		while(p!=NULL)
		{
			strcpy(c[k],p);
			p=strtok(NULL,"=");
			k++;
		}
		strcpy(kpd[kpdcnt].kname,c[0]);
		strcpy(kpd[kpdcnt].kvalue,c[1]);
		kpdcnt++;
                k=0;
	}
}
void Displaykptd()
{
	int i;
        printf("\n Kname \t Kvalue \n");
	for(i=0;i<kpdcnt;i++)
	{
         printf("\n%s\t%s\n",kpd[i].kname,kpd[i].kvalue);
	}
}
void addpnt()
{
	int i,j;
	for(i=0;i<mnt[mntcnt-1].pp;i++)
	{
		strcpy(pnt[pntcnt],formal[i]);
		pntcnt++;
	}
	for(i=mnt[mntcnt-1].pp;i<(mnt[mntcnt-1].pp+mnt[mntcnt-1].kp);i++)
	{
		for(j=0;formal[i][j]!='=';j++)
		{
			pnt[pntcnt][j]=formal[i][j];
		}
		pntcnt++;
	}
}
void addmnt()
{
	int x=0,i;
	strcpy(mnt[mntcnt].name,s1);
	for(i=0;s2[i]!='\0';i++)
	{
        if(s2[i]=='&')
	x++;
        if(s2[i]=='=')
         mnt[mntcnt].kp++;
	}
       mnt[mntcnt].pp=x-mnt[mntcnt].kp;
       mnt[mntcnt].kpdptr=kpdcnt;
       mnt[mntcnt].mdtptr=mdtcnt;
       mntcnt++;
}
void formallist()
{
	/*int i,j=0,k=0;
	for(i=0;s2[i]!='\0';i++)
	{
		if(s2[i]!=',')
		{
			formal[j][k]=s2[i];
			k++;
		}
		else
		{
			formal[j][k]='\0';
			j++;
			k=0;
		}
	}*/
		char *p;
		int cnt=0;
	p = strtok(s2,",");
	while (p!= NULL)
	{
		strcpy(formal[cnt],p);
		p=strtok(NULL,",");
		cnt++;
	}
}
void Displaymnt()
{
	int i;
        printf("\n\tMNTTAB IS:\n");
	printf("Name\tNopp\tNokp\tkpdptr\tmdtptr\n");
        printf("--------------------------------------\n");
	for(i=0;i<mntcnt;i++)
	{
		printf("%s\t  %d\t  %d\t  %d\t  %d\n\n",mnt[i].name,mnt[i].pp,mnt[i].kp,mnt[i].kpdptr,mnt[i].mdtptr);
	}
}
void Displaypnt()
{
	int i;
	printf("\nPNTAB IS:\n");
	for(i=0;i<pntcnt;i++)
	{
		printf("pnt[%d] | %s\n",i,pnt[i]);
	}
}

