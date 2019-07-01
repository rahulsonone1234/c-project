#include"SD_BANK.h"
#include<conio.h>
int main()
{
	ELIST p;
	int opt,i=0,cnt,pno;
	long int acc=612345654,acno,acno1,bal,amt;
	char ch;
	char acnm[30],pass[10],pass1[10];
	char Ano[13];
	char add[50];
	char gen;
	char mobno[11];
	clrscr();
	init(&p);
	welcome();
	system("cls");
	textcolor(BLUE);
	cprintf("                        \n\nCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
	printf("\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	while(1)
	{
		printf("\n1.Add new account\n2.Display Records.\n3.Delete Account\n4.Withdraw\n5.Deposite\n6.Transfer Money\n7.Modify\n8.Play Game And Earn Money ;)\n9.Exit\nOption:");
		scanf("%d",&opt);
		system("cls");
		if(opt>9 || opt<1)
		{
			textcolor(RED);
			cprintf("\nInvalid Input");
			continue;
		}
		if(opt==9)
			break;
		switch(opt)
		{
		 case 1:
			file2list(&p);
			cnt=cntNode(&p);
			acc = acc + 10*cnt;
			acno = acc;
			printf("\nEnter Account Holder's Name:");
			gets(acnm);
			while(1)
			{
				printf("\nEnter Your Aaddhar no:");
				while(1)
				{
				   ch=getch();
				   if(ch==13)
					break;
				   printf("%c",ch);
				   if(i>11&&ch!=13)
					  break;
				   if(ch>=48&&ch<=57)
					;
				   else
					break;
				   Ano[i++]=ch;
				}
				textcolor(RED);
				if(i==12&&ch==13)
				{
				    Ano[i]='\0';i=0;
				    break;
				}
				else
				{
				    cprintf("\nInvalid Aadhar Number");
				    i=0;
				    continue;
				}
			}
			printf("\nEnter your current address:");
			gets(add);
			while(1)
			{
			   printf("\nEnter your gender\n1.Male:M \t 2.Female:F \t 3.Other:O\n");
			   ch=getch();
			   printf("%c",ch);
			   getch();
			   if(ch=='M'||ch=='F'||ch=='O')
				break;
			   else
			   {
				textcolor(RED);
				cprintf("Invalid input...");
			   }
			}
			gen=ch;
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
				   mobno[i++]=ch;
				}
				textcolor(RED);
				if(i==10&&ch==13)
				{
				    mobno[i]='\0';i=0;
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
			do
			{
				printf("\nMinimum Amount For Opening Account:500");
				printf("\nAccount Opening Balance:");
				scanf("%ld",&bal);
			}while(bal<500);
			printf("\nSet password:");
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
				pass[i]=ch;
				textcolor(BLUE);
				cprintf("*");
				i++;
			}
			pass[i]='\0';i=0;
			printf("\nYour Account Number is : %ld",acno);
			printf("\n Account created successfully...\n");
			addEnd(&p,acno,acnm,bal,pass,Ano,add,gen,mobno);

			list2file(&p);
			break;

		case 2:
			file2list(&p);
			printf("\nEnter Your Account No:");
			scanf("%ld",&acno);
			printf("\nEnter Your Password:");
			while(1)
			{
				if((ch=getch())==13)
				    break;
				if(ch==8)
				{
				    printf("\n Enter Your password:");
				    i=0;
				    continue;
				}
				pass[i]=ch;
				textcolor(BLUE);
				cprintf("*");
				i++;
			}
			pass[i]='\0';i=0;
			textcolor(RED);
			if(searchAcc(&p,acno,pass))
				display(&p,acno,pass);
			else
				cprintf("\n Record is not found...\n");
			break;

		case 3:
			file2list(&p);
			printf("\nEnter Account no:");
			scanf("%ld",&acno);
			printf("\nEnter Your Password:");
			while(1)
			{
				if((ch=getch())==13)
				     break;
				if(ch==8)
				{
				    printf("\nEnter Your password:");
				    i=0;
				    continue;
				}
				pass[i]=ch;
				textcolor(BLUE);
				cprintf("*");
				i++;
			}
			pass[i]='\0';i=0;
			textcolor(RED);
			if(searchAcc(&p,acno,pass))
			{
				del(&p,acno,pass);
				cprintf("\n Account deleted successfully\n ");
			}
			else
				cprintf("\n Record is not found...\n");

			list2file(&p);
			break;

		case 4:
			file2list(&p);
			printf("\nEnter Your Account No:");
			scanf("%ld",&acno);
			printf("\nEnter Your Password:");
			while(1)
			{
				if((ch=getch())==13)
				      break;
				if(ch==8)
				{
				    printf("\nEnter Your password:");
				    i=0;
				    continue;
				}
				pass[i]=ch;
				textcolor(BLUE);
				printf("*");
				i++;
			}
			pass[i]='\0';i=0;
			textcolor(RED);
			if(searchAcc(&p,acno,pass))
			{
				printf("\nEnter Amount:");
				scanf("%ld",&amt);
				withdraw(&p,acno,pass,amt);
				cprintf("\n Record updated\n");
			}
			else
				cprintf("\n Record is not found\n");

			list2file(&p);
			break;

		case 5:
			file2list(&p);
			printf("\nEnter Your Account No:");
			scanf("%ld",&acno);
			printf("\nEnter Your Password:");
			while(1)
			{
				if((ch=getch())==13)
				      break;
				if(ch==8)
				{
				    printf("Enter Your password:");
				    i=0;
				    continue;
				}
				pass[i]=ch;
				textcolor(BLUE);
				cprintf("*");
				i++;
			}
			pass[i]='\0';i=0;
			textcolor(RED);
			if(searchAcc(&p,acno,pass))
			{
				printf("\nEnter Amount:");
				scanf("%ld",&amt);
				deposite(&p,acno,pass,amt);
				cprintf("\n Record updated\n");
			}
			else
				cprintf("\n Record is not found\n");

			list2file(&p);
			break;

		case 6:
			file2list(&p);
			printf("\nEnter Your Account No:");
			scanf("%ld",&acno);
			printf("\nEnter Your Password:");
			while(1)
			{
				if((ch=getch())==13)
				      break;
				if(ch==8)
				{
				    printf("Enter Your password:");
				    i=0;
				    continue;
				}
				pass[i]=ch;
				textcolor(BLUE);
				cprintf("*");
				i++;
			}
			pass[i]='\0';i=0;
			textcolor(RED);
			if(searchAcc(&p,acno,pass))
			{
				printf("\nEnter Amount:");
				scanf("%ld",&amt);
				printf("\nEnter Receiver's Account no:");
				scanf("%ld",&acno1);
				transfer(&p,acno,pass,amt,acno1);
			}
			else
				cprintf("\n Record is not found\n");

			list2file(&p);
			break;

		case 7:
			file2list(&p);
			printf("\nEnter Your Account No:");
			scanf("%ld",&acno);
			printf("\nEnter Your Password:");
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
				pass[i]=ch;
				textcolor(BLUE);
				cprintf("*");
				i++;
			}
			pass[i]='\0';i=0;
			textcolor(RED);
			if(searchAcc(&p,acno,pass))
			{
				mod(&p,acno,pass);
				cprintf("\n Record updated\n");
			}
			else
				cprintf("\n Record is not found\n");

			list2file(&p);
			break;

		case 8:
			file2list(&p);
			printf("\nEnter Account No of player1:");
			scanf("%ld",&acno);
			printf("\nEnter Password:");
			while(1)
			{
				if((ch=getch())==13)
				    break;
				if(ch==8)
				{
				    printf("\n Enter password:");
				    i=0;
				    continue;
				}
				pass[i]=ch;
				textcolor(BLUE);
				cprintf("*");
				i++;
			}
			pass[i]='\0';i=0;
			textcolor(RED);
			if(searchAcc(&p,acno,pass))
			{
				amt=500;
				withdraw(&p,acno,pass,amt);
			}
			else
			{
				cprintf("\n Record is not found...\n");
				break;
			}
			printf("\nEnter Account No of player2:");
			scanf("%ld",&acno1);
			printf("\nEnter Password:");
			while(1)
			{
				if((ch=getch())==13)
				    break;
				if(ch==8)
				{
				    printf("\n Enter password:");
				    i=0;
				    continue;
				}
				pass1[i]=ch;
				textcolor(BLUE);
				cprintf("*");
				i++;
			}
			pass1[i]='\0';i=0;
			textcolor(RED);
			if(searchAcc(&p,acno1,pass1))
			{
				withdraw(&p,acno1,pass1,500);
			}
			else
			{
				cprintf("\n Record is not found...\n");
				break;
			}
			pno=game();
			if(pno==1)
			{
			    deposite(&p,acno,pass,1000);
			}
			else if(pno==2)
			{
			    deposite(&p,acno1,pass1,1000);
			}
			else
			{
			    deposite(&p,acno,pass,500);
			    deposite(&p,acno1,pass1,500);
			}
			list2file(&p);
			break;
		}
		printf("\nPress esc to exit or any else:");
		ch=getch();
		if(ch==27)
			break;
		else
			system("cls");

	}
	return 0;
}

