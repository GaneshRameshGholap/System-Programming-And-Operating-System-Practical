/*
Extended Shell(Toy Shell)
Shell is an interface between user and operating system. It is the command interpreter , which accept the command name(program name) from user and executes that command/program.
The command interpreter in Unix/Linux is called as shell.In unix  core operating system is also called as kernel.
Shell mostly accepts the commands given by user from keyboard , shell gets started automatically  when Operating System is successfully started.
There are various types of shell avialable on Linux viz.BASH(Bourn Again Shell), CSH( C Shell), KSH(Kourn Shell), TSH(it is enhanced C shell).
When shell is started successfully it generally display some prompt to indicate the user that it is ready to accept and execute the command.
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
char cmd[80],token1[20],token2[20],token3[20],token4[20];
void count();
int main()
{
	int pid;
	int n;
	while(1)
	{
		printf("\nMyshell$");
		gets(cmd);
		n=sscanf(cmd,"%s%s%s%s",token1,token2,token3,token4);
		if(strcmp(token1,"q")==0)
		{
			exit(0);
		}
		pid=fork();
		if(pid==-1)
		{
			printf("Error\n");
		}
		else if(pid>0)
		{
			wait(NULL);
		}
		else
		{
                       if(strcmp(token1,"list")==0)
                      {
                             list(token3,token2[0]);
                               exit(0);
                      }
                      if(strcmp(token1,"typeline")==0)
                      {
                             typeline(token3,token2);
                               exit(0);
                      }
                      if(strcmp(token1,"search")==0)
                      {
                             search(token3,token2[0],token4);
                             exit(0);
                      }
                      if(strcmp(token1,"count")==0)
                      {
                             count();
                             exit(0);
                      }
			switch(n)
			{
				case 1:execlp(token1,token1,NULL);
				       break;
				case 2:execlp(token1,token1,token2,NULL);
				       break;
				case 3:execlp(token1,token1,token2,token3,NULL);
				       break;
				case 4:execlp(token1,token1,token2,token3,token4,NULL);
				       break;
			}
		}
	}
}
void list(char *dn, char op)
{
	DIR *dp;
	struct dirent *entry;
	int dc=0,fc=0;

	dp = opendir(dn);
	if(dp==NULL)
	{
		printf("Dir %s not found.\n",dn);
		return;
	}

	switch(op)
	{
	case 'f':
		while(entry=readdir(dp))
		{
			if(entry->d_type==DT_REG)
				printf("%s\n",entry->d_name);
		}
		break;
	case 'n':
		while(entry=readdir(dp))
		{
			if(entry->d_type==DT_DIR) dc++;
			if(entry->d_type==DT_REG) fc++;
		}
	
		printf("%d Dir(s)\t%d File(s)\n",dc,fc);
		break;
	case 'i':
		while(entry=readdir(dp))
		{
			if(entry->d_type==DT_REG)
				printf("%s\t%d\n",entry->d_name,entry->d_fileno);
		}
                 break;
	}

	closedir(dp);
}
void search(char *fn, char op, char *pattern)
{
	int fh,count=0,i=0,j=0;
	char buff[255],c,*p;

	fh = open(fn,O_RDONLY);
	if(fh==-1)
	{
		printf("File %s Not Found\n",fn);
		return;
	}

	switch(op)
	{
	case 'f':
		while(read(fh,&c,1))
		{
			buff[j++]=c;
			if(c=='\n')
			{
				buff[j]='\0';
				j=0;
				i++;
				if(strstr(buff,pattern))
				{
					printf("%d: %s",i,buff);
					break;
				}
			}
		}
		break;
	case 'c':
		while(read(fh,&c,1))
		{
			buff[j++]=c;
			if(c=='\n')
			{
				buff[j]='\0';
				j=0;
				p = buff;
				while(p=strstr(p,pattern))
				{
					count++;
					p++;
				}
			}
		}
		printf("Total No.of Occurrences = %d\n",count);
		break;
	case 'a':
		while(read(fh,&c,1))
		{
			buff[j++]=c;
			if(c=='\n')
			{
				buff[j]='\0';
				j = 0;
				i++;
				if(strstr(buff,pattern))
					printf("%d: %s",i,buff);
			}
		}
	}//switch
	close(fh);
}//search

void typeline(char *fn, char *op)
{
	int fh,i,j,n;
	char c;

	fh = open(fn,O_RDONLY);
	if(fh==-1)
	{
		printf("File %s not found.\n",fn);
		return;
	}

	if(strcmp(op,"a")==0)
	{
		while(read(fh,&c,1)>0)
			printf("%c",c);
		close(fh);
		return;
	}

	n = atoi(op);
	if(n>0)
	{
		i=0;
		while(read(fh,&c,1)>0)
		{
			printf("%c",c);
			if(c=='\n') i++;
			if(i==n) break;
		}
	}

	if(n<0)
	{
		i=0;
		while(read(fh,&c,1)>0)
		{
			if(c=='\n') i++;
		}
		lseek(fh,0,SEEK_SET);
		j=1;
		while(read(fh,&c,1)>0)
		{
			if(c=='\n') j++;
			if(j==i+n) break;
		}
		while(read(fh,&c,1)>0)
		{
			printf("%c",c);
		}
	}

	close(fh);
}

void count()
{       
	int fd;
	char ch;
	int c=0,w=0,l=0;
	fd=open(token3,O_RDONLY);
	while(read(fd,&ch,1))
	{
		if(ch!='\n'&& ch!='\t'&&ch!=' ')
			c++;
		if(ch=='\n'||ch=='\t'||ch==' ')
			w++;
		if(ch=='\n')
			l++;
	}
	if(strcmp(token2,"c")==0)
		printf("\ncharacter count=%d",c);
	if(strcmp(token2,"w")==0)
		printf("\nwordcount=%d",w);
	if(strcmp(token2,"l")==0)
		printf("\nlinecount=%d",l);
}
