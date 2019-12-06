/*
Assembler
Software Description-
An assembler is a software processor that takes as input an assembly language program and translates it into machine code if it is error free otherwise
provides a list of errors. we will design an assembler for the hypothetical simple instruction computer and  its assembly language.

Apart from imperative statements an assembly langauge contains Assembler directives and declaration statements. The assembler shold be able to handle programs containing assembler directives 'START' and 'END'.Declaration statements 'DS' and 'DC' and the imperative statements.

The Assembler will have two passes. In the first pass it will generate intermediate code and create symbol table. In the second pass intermediate code
will be converted to machine code.

Data Structure Design
Mnemonic table
Register Table
Condition code table
Symbol Table
Intermediate Code Table
Error Table
Error Message Table
*/
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
		"Invalid symbol",
		"Invalid Mnemonic",
		"wrong statement format"}; 
int lc;
char fname[30];
int cnt=0;
int cnt1=0;
int cnt2=0;
int lno=0;
int check(char *);
void passone(char []);
void addic(int a,int o, int r, char c,int v);
void adderror(int x ,int y);
void addsymbol(char *str,int u,int d);
void  display_Symtab();
void  display_IC();
void display_error();
void GetSymbolError();
void passtwo();
main(int argc,char *argv[])
{
	if(argc==2)
		passone(argv[1]);
                passtwo();
}
void passtwo()
{
	int i;
        printf("\nmachine code is:\n");
	for(i=1;i<cnt;i++)
	{
		if(ic[i].optype=='S'||ic[i].optype=='s')
			printf("%d%d%d\n",ic[i].opcode,ic[i].regop,sym[ic[i].value].add);
		if(ic[i].optype=='C'||ic[i].optype=='c')
		{
			if(ic[i].opcode==12)
				printf("0\n");
			else
				printf("%d\n",ic[i].value);
		}
		if(ic[i].optype==' ')
			printf("000000\n");
	}
}
void GetSymbolError()
{
	int i;
	for(i=0;i<cnt1;i++)
	{
		if(sym[i].used>=1&& sym[i].defined==0)
			printf("symbol:%s\t Error:%s\n",sym[i].symbol,errmsg[0]);
		if(sym[i].used==0&&sym[i].defined>=1)
			printf("symbol:%s\t Error:%s\n",sym[i].symbol,errmsg[1]);
		if(sym[i].defined>1)
			printf("Symbol:%s\t Error:%s\n",sym[i].symbol,errmsg[2]);
	}
}
int getsymentry(char str[30])
{
	int i;
	for(i=0;i<cnt1;i++)
	{
         if(strcmp(str,sym[i].symbol)==0)
          return i;
	}
}
void passone(char str[80])
{       int p,q;
	strcpy(fname,str);
	int n;
	char s1[30],s2[30],s3[30],s4[30];
	char str1[80];
	FILE *fp;
	fp=fopen(fname,"r");
	while(fgets(str1,80,fp)!=NULL)
	{
		printf("\n%s",str1);
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
				       if(p>=1&&p<=8)
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
                                               int sno=getsymentry(s4);
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
					       int sno=getsymentry(s3);
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
				       {       addsymbol(s2,1,0);
					       int sno=getsymentry(s2);
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
                display_Symtab();
                display_IC();
                display_error();
}
void addic(int a,int o, int r, char c,int v)
{
	ic[cnt].address=a;
	ic[cnt].opcode=o;
	ic[cnt].regop=r;
	ic[cnt].optype=c;
	ic[cnt].value=v;
	cnt++;
}
void adderror(int x ,int y)
{
	err[cnt2].lineno=x;
	err[cnt2].errno=y;
	cnt2++;
}
void addsymbol(char *str,int u,int d)
{         
	int x,flag=0,i;
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
int check(char *str)
{
	if(checkm(str)==-1)
		return 1;
	else if(checkr(str)==-1)
		return 1;
	else if(checkcc(str)==-1)
		return 1;
	else
		return -1;
}
int checkm(char *str)
{
	int i;
	for(i=0;i<15;i++)
		if(strcmp(str,mne[i])==0)return i;
	return -1;
}
int checkr(char *str)
{
	int i;
	for(i=0;i<4;i++)
		if(strcmp(str,reg[i])==0)return i;
	return -1;
}
int checkcc(char *str)
{
	int i;
	for(i=0;i<6;i++)
		if(strcmp(str,cc[i])==0)return i;
	return -1;
}
void display_Symtab()
{        
      printf("\n");
	int i;
	printf("Symbol table is\n");
	printf("Symbol Name\tadd\tused\tdefined\n");
	printf("-------------------------------------------------------\n"); 
	for(i=0;i<cnt1;i++)
	{
		printf("%s  %d  %d  %d\n",sym[i].symbol,sym[i].add,sym[i].used,sym[i].defined);
	}
}
void display_IC()
{      
         printf("\n");
	int i;
	printf("\n\nIntermediate table is\n");
	for(i=0;i<cnt;i++)
	{
		printf("%d %d %d %c %d\n",ic[i].address,ic[i].opcode,ic[i].regop,ic[i].optype,ic[i].value);
	}
}
void display_error()
{       
         printf("Error in program are:\n");
	int i;
	for(i=0;i<cnt2;i++)
	{
	       printf("\nLine no=%d\t",err[i].lineno);
               printf("\nError is:%s",errmsg[err[i].errno]);
	}
}
