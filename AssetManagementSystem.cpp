//ASSET MANAGEMENT SYSTEM

/******************Header files****************/

#include<iostream>
#include<fstream>
#include <curses.h>
#include <stdlib.h>


// #include<conio.h>
// #include<process>
#include<stdio.h>
#include<string.h>
// #include<dos.h>
#include<time.h>

using namespace std;

/*********Declaration of prototype of functions*******************/

void welcome_screen();
void displayall();
void addition();
void modification(char);
int recordcount();
void search();
char check(char *);
void sortos(char *);
void checkstatus(char *);
void menu();
void submenu();

/************************Base Class***********************/

class  baseasset
{
	protected:
		char slno[50];
		int dd,mm,yy;
	public:
		void getbasicdata();
		void displaybasicdata();
};

/*****************Base Class definitions*********************/

void baseasset::getbasicdata()  // ENTERING THE DETAILS
{
      clear();
      cout<<"\tADDITION";
      cout<<" \n ENTER SERIAL NO : ";
      gets(slno);
      cout<<"\nENTER THE EXPIRY DATE  	format(dd mm yyyy)";
      cin>>dd>>mm>>yy;
}

void baseasset::displaybasicdata()
{
     cout<<"\n Serial No : "<<slno;
     cout<<"\t Warranty Date : "<<dd<<"/"<<mm<<"/"<<yy;
}

/********************Inherited Class*******************/

class  asset:public baseasset
{
            int ram;
	int hd;
            char pro[30];
  public:
	char os[30];
            char status[50];
             int code;
    
/******Basic functions******/
	
            void getdata();
	void display();
	void edit();
	int getcode();
    
/*****Report functions******/
           
           void warrantyexpired();
           void warrantynearing();
}obj;

/**************Inherited Class definitions*************/
 
void asset::getdata()  // ENTERING THE DETAILS
{
      clear();
      getbasicdata();
      cout<<" \n ENTER COMPUTER CODE : ";
      cin>>code;
      cout<<" \n ENTER RAM   : ";
      cin>>ram;
      cout<<"\n Enter hard disk  : ";
      cin>>hd;
      cout<<" \n ENTER THE OPERATING SYSTEM : ";
      gets(os);
      cout<<" \n ENTER 	PROCESSOR  : ";
      gets(pro);
      cout<<" \n ENTER STATUS  : ";
      gets(status);
}

void asset::display() //TO DISPLAY ALL THE RECORDS
{

     displaybasicdata();
     cout << "\n\nCODE"<<"\tRAM"<<"\tHARD DISK"<<"\tOPERATING      SYSTEM"<<"\tPROCESSOR";
    cout<<"\n\n"<<code;
    cout<<"\t"<<ram;
    cout<<"\t"<<hd;
    cout<<"\t\t"<<os;
    cout<<"\t\t"<<pro;
    cout<<"\nstatus:\t";
    puts(obj.status);
    cout<<"\t--------------------------------------------------------"<<endl;
}

void asset::edit()
{
     char ch;
     if(check("computer code")=='y')
     {
	    cout<<"\n ENTER NEW COMPUTER CODE  :";
	    cin>>code;
	    ch=cin.get();
     }
    if(check("ram")=='y')
    {
	   cout<<"\nEnter new ram";
	   cin>>ram;
               ch=cin.get();
    }
    if(check("hard disk")=='y')
    {
	   cout<<"\nEnter new hard disk";
	   cin>>hd;
	   ch=cin.get();
     }
   if(check("processor")=='y')
    {
	   cout<<"\n ENTER NEW PROCESSOR : ";
	   gets(pro);
     }
    if(check("operating system")=='y')
     {
	    cout<<"\n ENTER NEW OPERATING SYSTEM :";
	    gets(os);
      }
     if(check("STATUS")=='y')
     {
	    cout<<"\n ENTER NEW STATUS :";
	    gets(status);
      }
}

/******************User functions*****************/
 
void welcome_screen()
{
	clear();
	cout<<"\n\n\n\t\t**************** W E L C O M E *********************";
	cout<<"\n\n\n\t\t*** V I M A L A P U B L I C S C H O O L **** " ;
	cout<<"\n\n\n\n\t\t A S S E T  M A N A G E M E N T   S Y S T E M	  ";
	for(int i=0;i<17;i++)
	cout<<endl<<endl;
	cout<<"\t\t\t\t\t *** PRESS ANY KEY TO CONTINUE***";
	getch();
}

void displayall()
{
     ifstream fin;
     int n,j;
     fin.open("c:\\ams.dat");
     clear();
     n=recordcount();
     for(j=0;j<n;j++)
     {
           fin.read((char*)&obj,sizeof(obj));
           obj.display();
           getch();
     }
     fin.close();
}

int recordcount()    //FIND NO. OF RECORDS
{
      ifstream fin;
      fin.open("c:\\ams.dat");
      fin.seekg(0,ios::end);
      int n;
      n=fin.tellg()/sizeof(obj);
      cout<<" \n NUMBER OF RECORDS = "<<n<<endl ;
      return n ;
}

void search()  //SEARCHING FOR A PARTICULAR NUMBER
{
     ifstream fin;
     fin.open("c:\\ams.dat");
     if(fin.fail())
     {
             cout<<" \n FILE NOT FOUND ";
	 getch();
     }
     clear();
     cout<<"\t\t\t [SEARCHING] ";
     cout<<" \n ENTER THE COMPUTER CODE TO BE SEARCHED : ";
     int c;
     cin>>c;
     int n;
     n=recordcount();
     for(int i=0;i<n;i++)
     {
	  fin.read((char*)&obj,sizeof(obj));
	  if(c==obj.code)
	  {
	       obj.display();
               }
      }
     getch();
     if(fin.eof())
     cout<<" \n RECORD NOT FOUND ";
}

void addition()
{
     ofstream fout;
     fout.open("c:\\ams.dat",ios::out|ios::app);
     obj.getdata();
     fout.write((char*)&obj,sizeof(obj));
     fout.close();
}

char check(char *s)
{
     cout<<"\n MODIFY \t "<<s<<"\t"<<"Y/N";
     char ch;
     ch =getch();
     if((ch=='y')||(ch=='Y'))
          return 'y';
     else
          return 'n';
}

void modification(char option)
{
    clear();
    int c,n,i;
    fstream fin;
    ofstream fout;
    cout<<"\tMODIFICATION\n";
    n = recordcount();
    if(n==0)
    {
	cout<<"\n FILE IS EMPTY ! ";
	getch();
    }
    fin.open("c:\\ams.dat",ios::in);
    fout.open("c:\\temp.dat",ios::out); //saving all records to a temporary file
    while(fin.good())
    {
           fin.read((char*)&obj,sizeof(obj));
           fout.write((char*)&obj,sizeof(obj));
    }
    fin.close();
    fout.close();
    fout.open("c:\\ams.dat",ios::trunc);
    fin.open("c:\\temp.dat",ios::in);
    char ch;
    cout<<"\n ENTER COMPUTER CODE :";
    cin>>c;
    ch=cin.get();
    for(i=0;i<n;i++)
    {
	   fin.read((char*)&obj,sizeof(obj));
	   char d;
              if(c==obj.code)
              {
	      obj.display();
	      if (option=='D')//if Delete option selected
	     {
	         cout<<"Are you sure to delete this record (Y/N)? ";
	         ch = getch();
	         if ((ch != 'y') && (ch != 'Y')) //Does not write record if choice is 'YES'
	             fout.write((char*)&obj,sizeof(obj));
	      }
	     if (option=='E')//if Edit option selected
	     {
	         obj.edit();
	         fout.write((char*)&obj,sizeof(obj));
	     }
              }
	else
	    fout.write((char*)&obj,sizeof(obj));
    }
    fout.close();
    fin.close();
}

void sortos(char *b)
{
      int ptr,n;
      n=recordcount();
      ifstream fin;
      fin.open("c:\\ams.dat");
      for(int i=0;i<n;i++)
      {
          fin.read((char*)&obj,sizeof(obj));
          ptr=strcmp(b,obj.os);
          if(ptr==0)
         {
	  obj.display();
	  cout<<"\n\n";
          }
       }
      fin.close();
      getch();
}

void checkstatus(char *b)
{
      int ptr,n;
      n=recordcount();
      ifstream fin;
      fin.open("c:\\ams.dat");
      for(int i=0;i<n;i++)
      {
           fin.read((char*)&obj,sizeof(obj));
           ptr=strcmp(b,obj.status);
           if(ptr==0)
           {
	   obj.display();
	   cout<<"\n\n";
           }
       }
     fin.close();
     getch();
}

void asset::warrantyexpired() {
       time_t t = time(NULL);
       struct tm d = *localtime(&t);
       int m,day,y,n;
       day=d.tm_mday;
       m=d.tm_mon;
       y=d.tm_year;
       ifstream fin;
       fin.open("c:\\ams.dat");
       n=recordcount();
       if(n==0)
       {
	cout<<"\n FILE IS EMPTY ! ";
	getch();
       }
      for(int i=0;i<n;i++)
      {
	fin.read((char*)&obj,sizeof(obj));
             if(yy<y)
	    obj.display();
             else if(yy==y)
	 {
	        if(mm<m)
	            obj.display();
	        else if(mm==m)
	        {
	             if(dd<day)
	                 obj.display();
	         }
	  }
      }
    fin.close();
}

void asset::warrantynearing()
  {
       time_t t = time(NULL);
       struct tm d = *localtime(&t);
       int m,day,y,n;
       day=d.tm_mday;
       m=d.tm_mon;
       y=d.tm_year;
       ifstream fin;
       fin.open("c:\\ams.dat");
       n=recordcount();
       if(n==0)
       {
	cout<<"\n FILE IS EMPTY ! ";
	getch();

       }
       for(int i=0;i<n;i++)
      {
	fin.read((char*)&obj,sizeof(obj));
            if(yy>y)
	   obj.display();
	else if(yy==y)
	{
	     if(mm>m)
	        obj.display();
	     else if(mm==m)
	     {
	          if(dd>=day)
		  obj.display();
	      }
	}
       }
    fin.close();
}

void submenu()
      {
              char ch;
	  cout<<"\t\t\t\t REPORTS MENU";
	  cout<<"\n\n\t\t\t1.   sort according to operating system";
	  cout<<"\n\n\t\t\t2.   status";
	  cout<<"\n\n\t\t\t3.   list of warranty expired computers";
	  cout<<"\n\n\t\t\t4.   list of computers nearing expiry";
	  cout<<"\n\n\t\t\t5.   Back to the main menu";
	  ch=getch();
	  switch(ch)
	  {
	      case '1'        :clear();
			   cout<<"\t\t Operating system  menu";
			   cout<<" \n\n\t1. windows xp professional ";
			   cout<<"\n\t2. windows 98";
			   cout<<"\n\t3. windows 2000";
			   cout<<"\n\t4.  return to report menu";
			   char cha;
			   cha=getch();
			   switch(cha)
			   {
			        case '1'     : clear();
					       sortos("windows xp");
					       break;
			        case  '2'    : clear();
			 		       sortos("windows 98");
					       break;
			        case  '3'     :clear();
					       sortos("windows 2000");
					       break;
			        case '4'     : clear();
					       submenu();
					       break;

			     }
			    break;


	         case '2'       :clear();
			       cout<<"\n\n\t\t STATUS MENU";
			       char x;
			       cout<<"\n\n\t\t1. list of working computers";
			       cout<<"\n\n\t\t2. list of non working computers";
			       cout<<"\n\n\t\t3.  back to report menu";
			       x=getch();
			       switch(x)
			       {
			          case '1'  : clear();
					     checkstatus("working");
					     break;
                                              case '2'   : clear();
					     checkstatus("not working");
					     break;
			         case '3'   : clear();
					     submenu();
					     break;
			    }
			    break;
	   case '3'    : clear();
			    cout<<"\n\n\t\tWARRANTY EXPIRED COMPUTERS";
			    obj.warrantyexpired();
			    getch();
			    break;
	   case '4'    : clear();
			    cout<<"\n\n\t\t COMPUTERS NEARING EXPIRY";
			    obj.warrantynearing();
			    getch();
			    break;
	   case '5'    : clear();
			    menu();
			    break;
		    }
}

void menu()
    {
       char ch;
       do
        {
            clear();
            cout<<"\n\n\t\t***MENU****";
            cout<<"\n\n\t\t 1:  ADD NEW ASSET";
            cout<<"\n\n\t\t 2:  DELETE AN ASSET    ";
            cout<<"\n\n\t\t 3:  EDIT AN ASSET   ";
            cout<<"\n\n\t\t 4:  VIEW ALL ASSETS ";
            cout<<"\n\n\t\t 5:  REPORTS  ";
            cout<<"\n\n\t\t 6:  SEARCH ";
            cout<<"\n\n\t\t 7:  EXIT  ";
            ch=getch();
            switch(ch)
	   {
	      case '1':	addition();
				break;
	      case '2' :	modification('D');
				break;
	      case '3' :	modification('E');
		                        break;
	      case '4':     displayall();
			            break;
	      case '5':     clear();
			submenu();
			       break;
	      case '6': search();
			      break;
	   }
       }while (ch != '7');
 }

int main()
{
   initscr();
   // clear();
   welcome_screen();
   menu();
   endwin();
   return 0;
}
