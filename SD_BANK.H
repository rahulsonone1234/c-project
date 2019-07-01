
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
//#include<graphics.h>

typedef struct account
{
long int acno;
char acnm[30];
long int bal;
char pass[10];
char Ano[13];
char add[50];
char gender;
char mobno[11];
}ACCT;


typedef struct node
{
   ACCT data;
   struct node *next;
}NODE;

typedef struct elist
{
	NODE *st;
}ELIST;

// fun to initialise list
void init(ELIST *p)
{
	p->st=NULL;
}

// fun to createnode
NODE* createNode(long int acno,char* ptr,long int bal,char *pass,char *Ano,char* add,char gen,char* mobno)
{
	NODE *a;
	a=(NODE *)malloc(sizeof(NODE));
	a->data.acno=acno;
	strcpy(a->data.acnm,ptr);
	a->data.bal=bal;
	strcpy(a->data.pass,pass);
	strcpy(a->data.Ano,Ano);
	strcpy(a->data.add,add);
	a->data.gender= gen;
	strcpy(a->data.mobno,mobno);

	a->next = NULL;
	return a;
}

// fun to get last node
NODE* getLastNode(ELIST *p)
{
	NODE *a=p->st;
	while(a->next!=NULL)
	       a=a->next;
	return a;
}
// fun to count node
int cntNode(ELIST *p)
{
	NODE *a=p->st;
	int cnt=0;
	while(a!=NULL)
	{
	       cnt++;
	       a=a->next;
	}
	return cnt;
}


//fn to add at End
void addEnd(ELIST *p,long int acno,char *ptr,long int bal,char *pass,char *Ano,char *add,char gen,char *mobno)
{
	NODE *a,*b;
	a=createNode(acno,ptr,bal,pass,Ano,add,gen,mobno);
	if(p->st==NULL)
		p->st = a;
	else
	{
		b=getLastNode(p);
		b->next=a;
	}
}

//fn to display
void display(ELIST *p,long int acno,char *pass)
{
	NODE *a=p->st;
	if(p->st==NULL)
	{
		printf("\nList is Empty");
		return;
	}
	else
	{
		while(a!=NULL)
		{
		    if(a->data.acno==acno&&(!strcmp(a->data.pass,pass)))
		    {
			printf("\nAccount No:%ld\nAccount holder's Name:%s\nBalance:%ld\nAddhar no:%s\nAddress:%s\ngender:%c\nmobile number:%s",a->data.acno,a->data.acnm,a->data.bal,a->data.Ano,a->data.add,a->data.gender,a->data.mobno);
			break;
		    }
			a=a->next;
		}
		if(a==NULL)
	    printf("\nRecord Not Found");
	}
	return;
}



//fn to search stu record by Account no
int searchAcc(ELIST *p,long int acno,char *pass)
{
  NODE *a=p->st;
  while(a!=NULL)
  {
    if(a->data.acno==acno&&(!strcmp(a->data.pass,pass)))
	break;
    a=a->next;
  }
  if(a==NULL)
     return 0;
  else
    return 1;

}


//fn to make list empty
void delAll(ELIST *p)
{
   NODE *a=p->st;
       if(p->st==NULL)
	  return;
       while(p->st!=NULL)
       {
	 p->st=a->next;
	 free(a);
	 a=p->st;
       }
}


// fun to delete data
void del(ELIST *p,long int acno,char *pass)
{
   NODE *a=p->st,*b;
   while(a!=NULL)
   {
     if(a->data.acno==acno&&(!strcmp(a->data.pass,pass)))
     {
       if(a==p->st)
       {
	p->st=a->next;
	free(a);
	break;
       }
       else
       {
	b->next=a->next;
	free(a);
	    break;
       }
     }
     else
     {
       b=a;
       a=a->next;
     }
   }
}


//file to list
void file2list(ELIST *p)
{
  FILE *flist;
  ACCT d;
  flist=fopen("list.dat","rb");
  if(flist==NULL)
    return;
  if(p->st!=NULL)
    delAll(p);
  while(1)
  {
    fread(&d,sizeof(ACCT),1,flist);
	 if(feof(flist))
	     break;
	  addEnd(p,d.acno,d.acnm,d.bal,d.pass,d.Ano,d.add,d.gender,d.mobno);
  }
  fclose(flist);
  return;
}


//fn to build list from file data
void list2file(ELIST *p)
{
   FILE *flist;
   NODE *a=p->st;
   ACCT d;
   if(p->st==NULL)
      return;
   flist = fopen("list.dat","wb");
   while(a!=NULL)
   {
      d.acno=a->data.acno;
      strcpy(d.acnm,a->data.acnm);
      d.bal=a->data.bal;
      strcpy(d.pass,a->data.pass);
      strcpy(d.Ano,a->data.Ano);
      strcpy(d.add,a->data.add);
      d.gender=a->data.gender;
      strcpy(d.mobno,a->data.mobno);
      fwrite(&d,sizeof(ACCT),1,flist);
      a=a->next;
   }
   fclose(flist);
   return;
}

// fun to withdraw amount
void withdraw(ELIST *p,long int acno,char *pass ,long int amt)
{
    NODE *a=p->st;
    while(a!=NULL)
    {
	if(a->data.acno==acno&&(!strcmp(a->data.pass,pass)))
	{
	    textcolor(RED);
	    if((a->data.bal-amt)<500)
		cprintf("\nInsufficient Balance");

	    else
		a->data.bal -= amt;

	    break;
	}
	a=a->next;
    }
}

//fn to deposite amount
void deposite(ELIST *p,long int acno,char *pass ,long int amt)
{
    NODE *a=p->st;
    while(a!=NULL)
    {
	if(a->data.acno==acno&&(!strcmp(a->data.pass,pass)))
	{
		a->data.bal += amt;
		break;
	}
	a=a->next;
    }
}

// fun to transfer money
void transfer(ELIST *p,long int acno,char *pass,long int amt,long int acno1)
{
    NODE *a=p->st,*b=p->st;
    while(a!=NULL)
    {
	   if(a->data.acno==acno&&(!strcmp(a->data.pass,pass)))
	   {
	      textcolor(RED);
	      if((a->data.bal-amt)<500)
	      {
	       cprintf("\nInsufficient Balance");
	       break;
	      }

	      while(b!=NULL)
	     {
		 if(b->data.acno==acno1)
		{
			a->data.bal -= amt;
			b->data.bal += amt;
			break;
		}
		 b=b->next;
	      }
	      textcolor(RED);
	      if(b==NULL)
		cprintf("\nRecord is not found...");
	      break;
	   }
	 a=a->next;
    }
}


// fun to modify record
void mod(ELIST *p,long int acno,char *pass)
{
    NODE *a=p->st;
    int i=0;
    char tmp,ch;
    char q[10];

    while(a!=NULL)
    {
	if(a->data.acno==acno&&(!strcmp(a->data.pass,pass)))
	{
	    printf("\nEnter Account Holder's Name:");
		    gets(a->data.acnm);
		    gets(a->data.acnm);
	    printf("\nEnter your current address:");
	    gets(a->data.add);
	    while(1)
	    {
		printf("\nEnter your mobile number which is currently linked with Aaddhar card:");
		while(1)
		{
		   ch=getch();
		   if(ch==13)
			break;
		   printf("%c",ch);
		   if(i>9&&ch!=13)
			break;
		   if(ch>=48&&ch<=57)
			;
		   else
			break;
		   a->data.mobno[i++]=ch;
		}
		textcolor(RED);
		if(i==10&&ch==13)
		{
		    a->data.mobno[i]='\0';i=0;
		    break;
		}
		else
		{
		    printf("\n\t");
		    cprintf("Invalid Mobile Number");
		    i=0;
		    continue;
		}
       }
	    printf("\nDo you want to change password??\nPress 1 if Yes\tElse any\nOption:");
	    scanf("%c",&tmp);
	    if(tmp==49)
	    {
	       printf("\nEnter New password:");
	       while(1)
		    {
			if((ch=getch())==13)
			    break;
			if(ch==8)
			{
			     printf("Set password:");
			     i=0;
			     continue;
			}
			q[i]=ch;
			textcolor(BLUE);
			cprintf("*");
			i++;
		    }
	       q[i]='\0';i=0;
	       strcpy(a->data.pass,q);
	    }
	    break;
	}
	a=a->next;
    }
}

//Tic Tac Toe Game
int game()
{
int a[3][3],i,j,k,x,y,t,c_obj=0,flg=0;
int gd=DETECT,gm;
clrscr();
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
setbkcolor(RED);
line(100,200,400,200);
line(100,300,400,300);
line(200,100,200,400);
line(300,100,300,400);
gotoxy(20,2);
printf("\tTIC TAC TOE");
gotoxy(20,3);
printf("_____________________");
gotoxy(10,5);printf(" BOX NO ");
gotoxy(15,7);printf("0");
gotoxy(30,7);printf("1");
gotoxy(45,7);printf("2");
gotoxy(15,14);printf("3");
gotoxy(30,14);printf("4");
gotoxy(45,14);printf("5");
gotoxy(15,21);printf("6");
gotoxy(30,21);printf("7");
gotoxy(45,21);printf("8");
gotoxy(55,22);printf("RESULT");
gotoxy(55,23);printf("*************************");
for(i=0;i<=2;i++)
{
  for(j=0;j<=2;j++)
   {
     re:gotoxy(65,4);
     k=((i+j)%2+1);
     printf("Enter player %d",k);
     gotoxy(60,5);
     printf(" Box no from 0 to 8   ");
     gotoxy(60,6);
     t=getch();
     t=t-48;
     if(t==0){x=0;y=0;goto play;}
     if(t==1){x=1;y=0;goto play;}
     if(t==2){x=2;y=0;goto play;}
     if(t==3){x=0;y=1;goto play;}
     if(t==4){x=1;y=1;goto play;}
     if(t==5){x=2;y=1;goto play;}
     if(t==6){x=0;y=2;goto play;}
     if(t==7){x=1;y=2;goto play;}
     if(t==8){x=2;y=2;goto play;}
     else
	goto re ;
play:
	if((a[x][y]==1)||(a[x][y]==2))
	  goto re;
	if((a[x][y]!=1)&&(a[x][y]!=2))
	{
	 if(k==1)
	  {
	   circle(100*x+100+50,100*y+100+50,45);
	   a[x][y]=k;
	   c_obj++;
	  }
	 if(k==2)
	 {
	   line(x*100+100,y*100+100,x*100+200,y*100+200);
	   line(x*100+100,y*100+200,x*100+200,y*100+100);
	   a[x][y]=k;
	   c_obj++;
	 }
}
gotoxy(60,23);
	if((a[0][0]==a[1][0])&&(a[1][0]==a[2][0]))
	{
	  printf("Player %d wins ",k);
	  flg=1;
	  break;
	}
	if((a[0][0]==a[0][1])&&(a[0][1]==a[0][2]))
	{
	  printf("Player %d wins ",k);
	  flg=1;
	   break;
	}
	if((a[0][0]==a[1][1])&&(a[1][1]==a[2][2]))
	{
	  printf("Player %d wins ",k);
	  flg=1;
	  break;
	}
	if((a[1][0]==a[1][1])&&(a[1][1]==a[1][2]))
	{
	  printf("Player %d wins ",k);
	  flg=1;
	   break;
	}
	if((a[2][0]==a[2][1])&&(a[2][1]==a[2][2]))
	{
	  printf("Player %d wins ",k);
	  flg=1;
	   break;
	}
	if((a[2][0]==a[1][1])&&(a[1][1]==a[0][2]))
	{
	  printf("Player %d wins ",k);
	  flg=1;
	   break;
	}
	if((a[0][2]==a[1][2])&&(a[1][2]==a[2][2]))
	{
	  printf("Player %d wins",k);
	  flg=1;
	   break;
	}
	if((a[0][1]==a[1][1])&&(a[1][1]==a[2][1]))
	{
	  printf("Player %d wins ",k);
	  flg=1;
	   break;
	}
if(c_obj==9)
  {
    gotoxy(62,23);
    k=0;
    printf("DRAW");
  }
}
if(flg)
break;
}
getch();
closegraph();
return k;
}


int welcome()
{
   textcolor(GREEN);
   gotoxy(7,4);
   cprintf("                   *********************************                      ");
   gotoxy(7,5);
   cprintf("                   =================================                      ");
   gotoxy(7,6);
   cprintf("                   *********************************                      ");
   gotoxy(7,7);
   cprintf("                   *                               *                      ");
   gotoxy(7,8);
   cprintf("                   *                               *                      ");
   gotoxy(7,9);
   cprintf("                   *          WELCOME TO           *                      ");
   gotoxy(7,11);
   cprintf("                   *          ACSES BANK           *                      ");
   gotoxy(7,13);
   cprintf("                   *                               *                      ");
   gotoxy(7,14);
   cprintf("                   *                               *                      ");
   gotoxy(7,15);
   cprintf("                   *                               *                      ");
   gotoxy(7,16);
   cprintf("                   *********************************                      ");
   gotoxy(7,17);
   cprintf("                   =================================                      ");
   gotoxy(7,18);
   cprintf("                   *********************************                      ");

   getch();
   return 0;
}


