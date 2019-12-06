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

struct mdttab{
int count;
int data[4][20];
}mdt[30];

struct kpdtab{
char kname[30];
char kvalue[30];
}kpd[30];

int pnt[10][30];

void formalist();

char formal[10][30];

int mdtcnt=0;
int mntcnt=0;
int kpdcnt=0;
int pntcnt=0;

char str[80];

char s1[40],s2[40];

FILE *fp;

char fname[30];

void  addmnt();
void formallist();
void addpnt();
void addkpdt();
void addmdt();


void displaymnt();
void displaypnt();
void displaykpdt();
void displaymdt();
void Extract();
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("\nError:");
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
		formallist();
		addpnt();
		addkpdt();
		addmdt();
	}
	displaymnt();
	displaypnt();
	displaykpdt();
	displaymdt();
	fclose(fp);
}
void addmnt()
{
	int x=0;
	int i;
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
	int cnt=0;
	char *p;
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
void addkpdt()
{
	int i;
	char c[2][30];
	char *p;
	int k;
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
		strcpy(kpd[kpdcnt].name,c[0]);
		strcpy(kpd[kpdcnt].kvalue,c[1]);
		kpdcnt++;
	}
}
void addmdt()
{
	int i;
	int n;
        char str[80];
	char p[10][30];
	while(1)
	{
		fgets(str,80,fp);
		n=sscanf(str,"%s%s%s%s",p[0],p[1],p[2],p[3]);
		mdt[mdtcnt].count=n;
		if(strcmp(s1,"MEND")==0)
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
void displaymnt()
{
	int i;
	printf("\n\nMNTAB\n\n");
	printf("\nMname\tnopp\tnokp\tkpdptr\tmdtptr\n");
	for(i=0;i<mntcnt;i++)
	{
		printf("%s\t%d\t%d\t%d\t%d\n",mnt[i].name,mnt[i].pp,mnt[i].kp,mnt[i].kpdptr,mnt[i].mdtptr);
	}
}
void displaypnt()
{
	printf("\n\nPNTAB\n\n");
	int i;
	for(i=0;i<pntcnt;i++)
	{
		printf("p[%d] | %s\n",i,pnt[i]);
	}
}
void displaykpdt()
{
	printf("\n\nKPTAB\n\n");
	int i;
	printf("\nKname|Kvalue\n\n");
	for(i=0;i<kpdcnt;i++)
	{
		printtf("%s | %s\n",kpd[i].kname,kpd[i].kvalue);
	}
}
void displaymdt()
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
