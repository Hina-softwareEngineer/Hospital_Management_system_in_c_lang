#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<ctype.h>
///////////////////////////////////////////// Declarations ////////////////////////////////////////////////////////////////////////
void title(void);
void welcome(void);
int login(void);
void mmenu(void);
void pentry(void);
void delrecord(void);
void precord(void);
void dr_info(void);
void time(void);
void ex_it(void);
/////////////////////////////////////////////Structure(info about patient)////////////////////////////////////////////////////////
struct patient
{
	char fname[10], lname[10], fathername[20], disease[20];
	char contact[15];
	int age;
	int z;
};

int main()
{
	int p;
	welcome();
	p=login();
	if(p==1)
	mmenu();
}


	///////////////////////////////////////////Title page///////////////////////////////////////////////////////

	void title(void)
{
	printf("\n\n\n_______________________________________________________________________________________________________________________\n");
	printf("\n\t\t\t\t\t\t   HOSPITAL MANAGEMENT SYSTEM\n");
	printf("_______________________________________________________________________________________________________________________");

}


/////////////////////////////////////////////////////////Welcome screen//////////////////////////////////////////////////////////////


	void welcome(void)
{
	system("cls");
	title();
	printf("\n\n\n \t\t\t\t\t\t   Welcome to the Hospital!!!!!!\n");
	printf(" \t\t\t\t\t\t ________________________________\n\n");
	printf("\n\t \t\t\t \t \tPress any key to access login page...");
	getch();
}

/////////////////////////////////////////////////////Login page//////////////////////////////////////////////////////////////////////////
int login(void)
{

    char username[]="Admin", password[]="12", id[89], p[3];
    int n=1, x, y,w;
    system("cls");
	title();
    do{
         printf("\n \n \n \n\t \t \t \t User_Name:");
         scanf("%s", &id);

         printf("\n \n \t \t \t \t Password:");
         scanf("%s", &p);

         x=strcmp(id, username);
         y=strcmp(p, password);

         if(x==0 && y==0){
           printf("\n\n\t\tSuccessfully Logged In!!!!!");
           w=1;
           break;
         }else {
           printf("\n\n\t\tWrong Password, try again!!!!", 5-n);
            getch();
            n++;}

         if(n>5){
          printf("\n\n\t\tAccess Denied");
          getch();
          }

       }while (n<=5);
    	system("cls");
		return(w);


}
//////////////////////////////////////////////////// Main Menu //////////////////////////////////////////////////////////////////////////////////
void mmenu()
{
	int a,b;
	system("cls");
	title();
	printf("\t \t \t \t WELCOME TO HOSPITAL MENU\n\n");
	printf("\t \t \t \t 1. Patient entry \t \t \t \t \n \t \t \t \t 2. Delete Patient Record \n \t \t \t \t 3. Search patient record \n \t \t \t \t 4. Hospital schedule \n \t \t \t \t 5. Doctor's information \n \t \t \t \t 6. Exit");
	printf("\n\n\t\t\tPlease select option from 1-6 from above: ");
	scanf("%d",&a);

	switch(a)
	{
	case 1:
		pentry();
		break;
	case 2:
		delrecord();
		break;
	case 3:
		precord();
		break;
	case 4:
		time();
		break;
	case 5:
		dr_info(); break;
    case 6:
        ex_it(); break;}
	getch();}

//////////////////////////////////////////////////////Patient Entry/////////////////////////////////////////////////////////////////////////////
	void pentry(void)
	{
	struct patient p[100];
	int n,z,j,i,k,m,valid;
	FILE *pE;
	system("cls");
	title();
	pE= fopen("pEntry.dat","a");
	printf("\n\n \t \t \t \t !!!!!!!!!!!!!! Add Patients Record !!!!!!!!!!!!!\n");
	printf("\n\t\t\t\tEnter number of patients you have:");
	scanf("%d",&n);
    for(j=0 ; j<n ; j++)
		{for(k=0 ; k<1 ; k++)
				{ A:
					printf("\n \t \t \t \t First name:");
					scanf(" %s",p[j].fname);
					if(strlen(p[j].fname)<3||strlen(p[j].fname)>20)
					{printf("\n \t \t \t \t Invalid length. Please enter again...");
					goto A;}
					else
					{for(m=0 ; m<strlen(p[j].fname) ; m++)
					{{if(isalpha(p[j].fname[m]))
							{valid=0;}
							else
							{valid=1;}}
							if(valid==1)
							{printf("\n\n\t\t\t\tName has invalid character. Please enter your original name.");
							goto A;}}}
	                printf("\n \t \t \t \t Last name:");
	                scanf(" %s",p[j].lname);
					printf("\n \t \t \t \t Father name:");
					scanf(" %s",p[j].fathername);
					printf("\n \t \t \t \t Disease:");
					scanf("%s",p[j].disease);
					printf("\n \t \t \t \tContact number(11 digits only):");
					scanf("%s",p[j].contact);
					printf("\n \t \t \t \tage:",p[j].age);
					scanf("%i",&p[j].age);}
     fprintf (pE,"%s %s %s %s %s %i",p[j].fname,p[j].lname,p[j].fathername,p[j].disease, p[j].contact,p[j].age);
					fclose(pE);
					if(j<n-1)
					printf("\n \n \t \t \t \t Please enter details of another patient...");

	}mmenu();
	}
	/////////////////////////////////////////////////////////  Delete Record ////////////////////////////////////////////////////////////////////////////////////
	void delrecord(void)
{
	int c,j;
	struct patient pat;
	char name[10];
	FILE *pE,*tE;
	pE=fopen("pentry.dat","r+");
	tE=fopen("tentry.dat","wb");
	printf("\n \n \t \t \t \t Delete patient record");
	printf("\n \nPlease enter patient name whose records u want to remove...");
	scanf("%s",name);
	rewind(pE);
	while(fread(&pat,sizeof(pat),1,pE)==1)
		{
		if(strcmp(pat.fname,name)==0)
		{
			fwrite(&pat,sizeof(pat),1,tE);
		}
	}
		fclose(pE);
		fclose(tE);

		remove("pentry.dat");
		rename("tentry.dat","pentry.dat");
		for(j=1 ; j<=1 ; j++)
		{
		printf("\t\t\t\tDeleted successfully!!!!\n");
		printf("\n\t\t\t\tPress any key to go to main menu");
		}
		getch();
		mmenu();
	}
	////////////////////////////////////////////////Search Record /////////////////////////////////////////////////////
	void precord(void)
{
	char name[10];
	struct patient p;
	int i;
	FILE *pE;
	system("cls");
	title();
	pE=fopen("pentry.dat","r");
	printf("\n\n\t\t\t\t\t!!!!!!!!!!!!!! Search Patients Record !!!!!!!!!!!!!\n");
	printf("\n \n \t\t\t\tEnter Patient Name to be viewed:");
	scanf("%s",name);
	while(fscanf(pE,"%s %s %s %s %s %i\n", p.fname,p.lname, p.fathername,p.disease,p.contact,&p.age)!=EOF)
	{
		if(strcmp(p.fname,name)==0)
		{
			printf("\n\n\t\t\t\tFull name: %s %s\n",p.fname,p.lname);
			printf("\t\t\t\tFather name: %s\n",p.fathername);
			printf("\t\t\t\tDisease: %s\n",p.disease);
			printf("\t\t\t\tContact no: %s\n",p.contact);
			printf("\t\t\t\tAge: %i\n",p.age);
			printf(" \n\n\t\tPress any key to go back to main menu...");
			//break;
		}getch(); mmenu();}
	if(strcmp(p.fname,name)!=0)
	{for(i=1 ; i<=1 ; i++)
		{
		printf("\n\n\n \t\t\t\t\t Patient not listed here");
		printf("\n\n\t\t\t Press any key to go to the main menu.");
		}getch(); mmenu();
	}
		fclose(pE);

}
/////////////////////////////////////////////////////////Doctors Information/////////////////////////////////////////////////////////////////////////
void dr_info(void)
{
int i,j=1;
system("cls");
title();
for(j=1 ; j<=1 ; j++)
{
printf("\n \t\t\t\t \t \t ********doctor's information********\n");
printf("\n \t\t\t\t \t \t1. Orthopedics\n\t\t\t \t  \t \t2. Dermatologist \n  \t\t\t\t \t \t3. Cardiologist\n  \t\t\t\t \t \t4. General Physician\n\t \t \t \t \t \t5. ENT Specialist\n\t\t\t \t \t \t6. Neurologist");
printf("\n \n\t\t \t \t \t \t Select from 1 to 6:\t");
scanf("%d",&i);
switch(i)
{case 1:
printf("\n\n\t \t\t\t \t \tDr. Romana Khan is available."); break;
case 2:
printf("\n\n\t \t\t\t\t \tDr. Farhat Jabeen is available."); break;
case 3:
printf("\n\n\t \t  \t\t\t\tDr. Tariq Shiryan is available."); break;
case 4:
printf("\n\n\t \t\t\t \t \tDr. Nasar Alam is available."); break;
case 5:
printf("\n\n\t \t \t\t\t \tDr. Sidra Mumtaz is available."); break;
case 6:
printf("\n\n\t \t  \t\t\t \tDr. Qamar-un-Nisa is available."); break;
default:
printf("\n\n\t \t \t\t\tSorry input is not valid. ");}
printf("\n\n \t \t \tPress any key to return to main menu...");
}
getch();
mmenu();

}
void time(void)
{
	int i;
for(i=1 ; i<=1 ; i++)
{
system("cls");
title();
printf("\n\n \t \t \t \t\t  \t ********HOSPITAL TIMING********\n");
printf(" \n\n\n\t \t \t \t \t\t     *****OPD TIMING***** \n\t \t \t \t \t \t(Monday to Wednesday all fields) ");
printf(" \n\n\t \t \t \t \t \t 8:30 A.M     to     12:00 P.M");
printf(" \n\n\n\t \t \t \t \t \t  ****WARD'S ROUND TIMING****\n\t \t \t \t \t \t \t    (Daily)");
printf(" \n\n\t \t \t \t \t \t  12:20 P.M    to    2:00 P.M");
printf(" \n\n\n\t \t \t \t \t \t     ***SUNDAY TIMING***\n\t \t \t \t \t \t    (Private Check-ups only)");
printf(" \n\n\t \t \t \t \t \t 10:00 A.M     to     12:00 P.M");
printf(" \n\n\t\t\t\tPress any key to go back to main menu...");
}
getch();
mmenu();}
//////////////////////////////////////////////////     Exit     ////////////////////////////////////////////////////////////////
void ex_it(void)//function to exit
{
	system("cls");
	title();// call Title function
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\tTHANK YOU FOR VISITING :)");}

