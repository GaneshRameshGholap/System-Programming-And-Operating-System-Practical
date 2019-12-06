#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
}kpd[30];

struct mdttab{
	int count;
	char data[4][30];
}mdt[30];

char pnt[10][30];

char str[80];
char fname[30];

char s1[40],s2[40];

void Extract();
void addmdt();
void addkpd();
void addpnt();
void addmnt();

FILE *fp;
int mntcnt=0;
int kpdcnt=0;
int pntcnt=0;
int mdtcnt=0;
char formal[10][30];
int main(int argc,char *argv[])
{
	int i;
	if(argc!=2)
	{
		printf("\nInvalid argument:");
		exit(0);
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
		formalist();
		addpnt();
		addkpd();
		addmdt();
	}
//	display_mdt();
//	display_pnt();
//	display_kpd();
//	display_mnt();
	fclose(fp);
}
void addmdt()
{
	int n;
	char p[10][30];
	int i,j;
	while(1)
	{
		fgets(str,80,fp);
		n=sscanf(str,"%s%s%s%s",p[0],p[1],p[2],p[3]);
		printf("\nCount=%d",n);
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
		}
		mdtcnt++;
	}
}
void formalist()
{
	char *p;
	int cnt=0;
	p=strtok(s2,",");
	while(p!=NULL)
	{
		strcpy(formal[cnt],p);
		p=strtok(NULL,",");
		cnt++;
	}
}
void addpnt()
{
	int i,j;
	for(i=0;i<(mnt[mntcnt-1].pp);i++)
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
void addkpd()
{
	char c[2][30];
	int k;
       char *p;
       int i,j;
       for(i=mnt[mntcnt-1].pp;i<(mnt[mntcnt-1].pp+mnt[mntcnt-1].kp);i++)
       {
	       k=0;
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
       }

}
void addmnt()
{
	int i,x=0;
	strcpy(mnt[mntcnt].name,s1);
	for(i=0;s2[i]!='\0';i++)
	{
		if(s2[i]=='&')
		{
			x++;
		}
		if(s2[i]=='=')
		{
			mnt[mntcnt].kp++;
		}
	}
       mnt[mntcnt].pp=x-mnt[mntcnt].kp;
       mnt[mntcnt].kpdptr=kpdcnt;
       mnt[mntcnt].mdtptr=mdtcnt;
       mntcnt++;
}

