#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char *mne[15]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT","DC","DS","START","END"};
char *reg[4]={"AREG","BREG","CREG","DREG"};
char *cc[6]={"LT","LE","EQ","GT","GE","ANY"};
struct symtab{
	char symbol[20];
	int add;
	int used;
	int defined;
}sym[50];
struct ictab{
	int address;
	int opcode;
	int regop;
	char optype;
	int value;
}ic[50];
struct errtab{
	int lineno;
	int errno;
}err[50];
char *errmsg[]={"Symbol used but not defined",
                "Symbol defined but not used",
        	"Redeclaration of symbol",
        	"invalid symbol",
        	"invalid mnemonic",
        	"wrong statement format"};
char fname[30];
int cnt=0;
int cnt1=0;
int cnt2=0;
int lno=0;
int lc;
void GetSymbolError()
{
	int i;
         printf("\n\n");
         printf("\nSymbols error:");
	for(i=0;i<cnt1;i++)
	{
		if(sym[i].used>=1 && sym[i].defined==0)
		{
			printf("\nSymbol:%s\tError:%s",sym[i].symbol,errmsg[0]);
		}
		if(sym[i].used==0&&sym[i].defined>=1)
		{
			printf("\nSymbol:%s\tError:%s",sym[i].symbol,errmsg[1]);
		}
		if(sym[i].defined>1)
		{
			printf("\nSymbol:%s\tError:%s",sym[i].symbol,errmsg[2]);
		}

	}
}
void passtwo()
{
	int i;
         printf("\nmachine code:\n");
	for(i=1;i<cnt;i++)
	{
		if(ic[i].optype=='S'||ic[i].optype=='s')
		{
			printf("%d%d%d\n",ic[i].opcode,ic[i].regop,sym[ic[i].value].add);
		}
		if(ic[i].optype=='C'||ic[i].optype=='c')
		{
			if(ic[i].opcode==12)
				printf("0\n");
			else
				printf("%d\n",ic[i].value);
		}
		if(ic[i].optype==' ')
		{
			printf("000000\n");
		}
	}
}
int getsymmentry(char str[40])
{
	int i;
	for(i=0;i<cnt1;i++)
	{
		if(strcmp(str,sym[i].symbol)==0)
		{
			return i;
		}
	}
}
void passone(char str[80])
{
        int p,q,sno,n;
	strcpy(fname,str);
	char str1[80];
	char s1[40],s2[40],s3[40],s4[40];
	FILE *fp;
	fp=fopen(fname,"r");
	while(fgets(str1,80,fp)!=NULL)
	{
		printf("%s\n",str1);
	}
	fclose(fp);
	printf("\n\n\n");
	fp=fopen(fname,"r");
	fgets(str1,80,fp);
        lno++;
         n=sscanf(str1,"%s%d",s1,&lc);
	addic(-1,checkm(s1),0,'C',lc);
	while(1)
	{
		fgets(str1,80,fp);
		lno++;
		n=sscanf(str1,"%s%s%s%s",s1,s2,s3,s4);
		switch(n)
		{
			case 4:addsymbol(s1,0,1);
			       if((p=checkm(s2))!=-1)
			       {
				       if(p>=1 && p<=8)
				       {
					       if(p==7)
					       {
						       if((q=checkcc(s3))==-1)
						       {
							       adderror(lno,5);
						       }
					       }
					       else
					       {
						       if((q=checkr(s3))==-1)
						       {
							       adderror(lno,5);
						       }
					       }
					       addsymbol(s4,1,0);
					       sno=getsymmentry(s4);
					       addic(lc,p,q+1,'S',sno);
				       }
				       else
				       {
					       adderror(lno,4);
				       }
			       }
			       else
			       {
				       adderror(lno,4);

			       }
			       break;
			case 3:if((p=checkm(s1))!=-1)
			       {
				       if(p>=1&&p<=8)
				       {
					       if(p==7)
					       {
						       if((q=checkcc(s2))==-1)
						       {
							       adderror(lno,5);
						       }

					       }
					       else
					       {
						       if((q=checkr(s2))==-1)
						       {
							       adderror(lno,5);
						       }
					       }
					       addsymbol(s3,1,0);
					       sno=getsymmentry(s3);
					       addic(lc,p,q+1,'S',sno);
				       }
				       else
				       {
					       adderror(lno,4);
				       }

			       }
			       else if((p=checkm(s2))!=-1)
			       {
				       if(p==11||p==12)
				       {
					       addsymbol(s1,0,1);
					       addic(lc,p,0,'C',atoi(s3));
				       }
				       else
				       {
					       adderror(lno,4);
				       }
			       }
			       else
			       {
				       adderror(lno,4);
			       }

			       break;

			case 2:if((p=checkm(s1))!=-1)
			       {
				       if(p>=9&&p<=10)
				       {
					       addsymbol(s2,1,0);
					       int sno=getsymmentry(s2);
					       addic(lc,p,0,'S',sno);
				       }
				       else
				       {
					       adderror(lno,4);
				       }
			       }
                               else
                               {
			       adderror(lno,4);
                              } 
			       break;
			case 1:if((p=checkm(s1))!=-1)
			       {
				       if(p==0)
				       {
					       addic(lc,0,0,' ',-1);
				       }
				       else if(p!=0&&p!=14)
				       {
					       adderror(lno,4);
				       }
			       }
			       else
			       {
				       adderror(lno,4);
			       }
			       break;
		}
		lc++;
		if(strcmp(s1,"END")==0)
			break;
	}
         GetSymbolError();
	display_symtab();
	display_ic();
	display_err();
}
void addsymbol(char *str,int u ,int d)
{
	int x,flag=0;
	int i;
	x=check(str);
	if(x==-1)
	{
		adderror(lno,3);
		return;
	}
	for(i=0;i<cnt1;i++)
	{
		if(strcmp(str,sym[i].symbol)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		strcpy(sym[cnt1].symbol,str);
		sym[cnt1].used=u;
		sym[cnt1].defined=d;
		if(d==1)
		{
			sym[cnt1].add=lc;
		}
		else
		{
			sym[cnt1].add=-1;
		}
              cnt1++;
	}
	else
	{
		if(d==1)
		{
			sym[i].defined++;
			sym[i].add=lc;
		}
		else
		{
			sym[i].used++;
		}
	}
}
void addic(int a,int o,int r,char c,int v)
{
	ic[cnt].address=a;
	ic[cnt].opcode=o;
	ic[cnt].regop=r;
	ic[cnt].optype=c;
	ic[cnt].value=v;
	cnt++;
}
void adderror(int x,int y)
{
err[cnt2].lineno=x;
err[cnt2].errno=y;
cnt2++;
}
int check(char *str)
{
	int i;
	if(checkm(str)==-1)
		return 1;
	else if(checkr(str)==-1)
		return 1;
	else if(checkcc(str)==-1)
		return 1;

		return -1;

}
int checkm(char *str)
{
	int i;
	for(i=0;i<15;i++)
	{
		if(strcmp(str,mne[i])==0)
		{
			return i;
		}
	}
	return -1;
}
int checkr(char *str)
{
	int i;
	for(i=0;i<4;i++)
	{
		if(strcmp(str,reg[i])==0)
		{
                   return i;
		}
	}
      return -1;
}
int checkcc(char *str)
{
	int i;
	for(i=0;i<6;i++)
	{
		if(strcmp(str,cc[i])==0)
		{
			return i;
		}
	}
         return -1;
}
void display_symtab()
{
	int i;
        printf("\nSymbol Table");
	printf("\nSymbol\t\tAddress\t\tUsed\t\tDefined");
	for(i=0;i<cnt1;i++)
	{
		printf("\n%s\t\t%d\t%d\t%d\n",sym[i].symbol,sym[i].add,sym[i].used,sym[i].defined);
	}
}
void display_ic()
{
	int i;
        printf("Intermediate code Table:");
	printf("\nAddress\topcode\tregop\toptype\tvalue");
	for(i=0;i<cnt;i++)
	{
		printf("\n%d\t%d\t%d\t%c\t%d\n",ic[i].address,ic[i].opcode,ic[i].regop,ic[i].optype,ic[i].value);
	}
}
void display_err()
{
	int i;
        printf("\nError Table:");
	printf("\nlineno\tError");
	for(i=0;i<cnt2;i++)
	{
		printf("\n\n%d\t\t\t%s",err[i].lineno,errmsg[err[i].errno]);
	}
}
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("\nError:");
		exit(0);
	}
	passone(argv[1]);
	passtwo();
}
