#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<string.h>

int days_in_month[]=
{
    0,31,28,31,30,31,30,31,31,30,31,30,31
};
char *months[]=
{
	" ",
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

DWORD screenwidth=GetSystemMetrics(SM_CXSCREEN);
DWORD screenheight=GetSystemMetrics(SM_CYSCREEN);
int window1=initwindow(screenwidth,screenheight,"",-3,-3);

char present_date[100],present_month[100],present_year[100];

int year=0;

void calender(int year,int daycode);
void print_calender();
void single_month_calender(int year,int month,int daycode);
void print_single_month_calender();
int leap_year(int);
int days(int year);
int days_month(int month,int year);
void present_data();
void print_time_date();
void print_conditions_year(int year);
void print_conditons_month(int month);
void month_head(int month,int year);
int month_number();

int leap_year(int year)
{
    if( (year%4==0 && year%100!=0) || year%400==0 )
    {
        days_in_month[2]=29;
        return 0;
    }
    else
    {
        days_in_month[2]=28;
        return 0;
    }
}
int days(int year)
{
    int daycode,d1,d2,d3;

    d1=(year-1)/4;
    d2=(year-1)/100;
    d3=(year-1)/400;
    daycode=(year+d1-d2+d3)%7;
    return daycode;
}
int days_month(int month,int year)
{
    int daycode=0,d1,d2,d3,mon;

    d1=(year-1)/4;
    d2=(year-1)/100;
    d3=(year-1)/400;
    daycode=(year+d1-d2+d3)%7;
    for(mon=1;mon<month;mon++)
    {
        daycode=(daycode+days_in_month[mon])%7;
    }
    return daycode;
}
void present_data()
{
    time_t rawTime;
    struct tm *currentTime;
    rawTime =time(NULL);
    currentTime = localtime(&rawTime);
    strftime(present_year,100,"%Y",currentTime);
    strftime(present_date,100,"%d",currentTime);
    strftime(present_month,100,"%b",currentTime);
}
void print_time_date()
{
    time_t rawTime;
    struct tm *currentTime;
    char a[100];

    while(1)
    {
        rawTime =time(NULL);
        currentTime = localtime(&rawTime);
        strftime(a,100,"%I:%M:%S %p",currentTime);

        setcolor(11);
        settextstyle(0,HORIZ_DIR,5);
        outtextxy(40,50,a);

        strftime(a,100,"%a, %d %b, %Y",currentTime);
        settextstyle(0,HORIZ_DIR,0);
        outtextxy(130,10,a);

        delay(1000);
        if(kbhit())
            break;
    }
}

void print_conditions_year( int year)
{
    setcurrentwindow(window1);

    while(1)
    {

        char ch;
        if(kbhit())
        {
            ch=getch();
            if (ch==75)
            {
                year--;
                int daycode=days(year);
                cleardevice();
                calender(year,daycode);
            }
            if(ch==77)
            {
                year++;
                int daycode=days(year);
                cleardevice();
                calender(year,daycode);
            }
            if(ch==27||ch==48)
            {
                exit(0);
            }
            if(ch==109)
            {
                print_single_month_calender();
            }
            if(ch>27&&ch<48||ch>48&&ch<75||ch==76||ch>77&&ch<109||ch>109&&ch<127)
            {
                int points_error[8]={1170,10,1150,30,1190,30,1170,10};
                settextstyle(10,HORIZ_DIR,1);
                setcolor(15);
                outtextxy(1180,10,"!!");
                outtextxy(1200,10,"Click on correct key");
            }
        }
    }
}
void calender(int year,int daycode)
{
	int month,day,i;
    setcurrentwindow(window1);
    cleardevice();
    char year1[50];
    sprintf(year1,"Year %d",year);
    settextstyle(3,HORIZ_DIR,8);
    setcolor(8);
    int width=textwidth(year1);
	outtextxy(getmaxx()/2-width/2,20,year1);

    settextstyle(0,HORIZ_DIR,0);

    int c=2;//C for color of text and rectangle
    int a,b=110;//for Month print
    int p1,p2=105,p3,p4=275;//for rectangle points
    int m,n=130;//for days
    int x,x1,y=150,y1=150;// for date
	for(month=1;month<=12;)
	{
	    p1=80,p3=450;
	    a=250;
	    x=100;
	    x1=100;
	    m=100;
	    for(i=1;i<=3;i++)
        {
            setcolor(c);
            rectangle(p1,p2,p3,p4);
            outtextxy(a,b,months[month]);
            outtextxy(m,n,"Sun" );
            outtextxy(m+50,n,"Mon" );
            outtextxy(m+100,n,"Tue" );
            outtextxy(m+150,n,"Wed" );
            outtextxy(m+200,n,"Thu" );
            outtextxy(m+250,n,"Fri" );
            outtextxy(m+300,n,"Sat" );

            for(day=1;day<=1+daycode*5;day++)
            {
                x=x+10;
            }
            for(day=1;day<=days_in_month[month];day++ )
            {
                char arr[50];
                sprintf(arr,"%d",day);
                outtextxy(x,y,arr);
                x=x+50;
                if((day+daycode)%7==0)
                {
                    x=x1;
                    y=y+20;
                }
            }
            daycode=(daycode+days_in_month[month])%7;
            p1=p1+460;
            p3=p3+460;
            c++;
            a=a+450;
            m=m+460;
            x=x1+460;
            x1=x1+460;
            month++;
            y=y1;
        }
	    p2=p2+180,p4=p4+180;
        b=b+180;
        n=n+180;
        y=y1+180;
        y1=y1+180;
	}

    settextstyle(10,HORIZ_DIR,1);
    setcolor(15);
    fillellipse(80,830,5,5);
    outtextxy(90,820,"Press m to view calender in a single month view.");
    fillellipse(80,850,5,5);
    outtextxy(90,840,"Press left or right arrow keys to change year.");
    fillellipse(1000,830,5,5);
    outtextxy(1010,820,"Press Esc or 0 to close the screen.");


    print_time_date();

    print_conditions_year(year);

	getch();
    closegraph();
}
void print_conditons_month(int month)
{
    while(1)
    {
        char ch;
        if(kbhit())
        {
            ch=getch();
            if(ch==75)
            {
                cleardevice();
                if(month==1)
                {
                    month=12;
                    year--;
                    leap_year(year);
                    int daycode1=days_month(month,year);
                    single_month_calender(year,month,daycode1);
                }
                else
                {
                    month--;
                    int daycode1=days_month(month,year);
                    single_month_calender(year,month,daycode1);
                }
            }
            if(ch==77)
            {
                cleardevice();
                if(month==12)
                {
                    month=1;
                    year++;
                    int daycode1=days_month(month,year);
                    single_month_calender(year,month,daycode1);
                }
                else
                {
                    month++;
                    leap_year(year);
                    int daycode1=days_month(month,year);
                    single_month_calender(year,month,daycode1);
                }
            }
            if(ch==72)
            {
                 year++;
                 leap_year(year);
                 int daycode1=days_month(month,year);
                 single_month_calender(year,month,daycode1);
            }
            if(ch==80)
            {
                 year--;
                 leap_year(year);
                 int daycode1=days_month(month,year);
                 single_month_calender(year,month,daycode1);
            }
            if(ch==89||ch==121)
            {
                print_calender();
            }
            if(ch==27||ch==48)
            {
                exit(0);
            }
            if(ch>27&&ch<48||ch>48&&ch<72||ch>72&&ch<75||ch==76||ch==78||ch==79||ch>80&&ch<89||ch>89&&ch<109||ch>109&&ch<121||ch>121&&ch<127)
            {
                int points_error[8]={1170,10,1150,30,1190,30,1170,10};
                settextstyle(10,HORIZ_DIR,1);
                setcolor(15);
                outtextxy(1180,10,"!!");
                outtextxy(1200,10,"Click on correct key");
            }
        }
    }
}
void month_head(int month,int year)
{
    char head[50];
    sprintf(head,"%s %d",months[month],year);
    settextstyle(10,HORIZ_DIR,10);

    int width=textwidth(head);
    int c=1;
    while(1)
    {
        setcolor(c);
        outtextxy(getmaxx()/2-width/2,20,head);
        c++;
        if(c==15)
        {
            c=1;
        }
        delay(300);
        if(kbhit())
            break;
    }
}
void single_month_calender(int year,int month, int daycode)
{
    int day,i;
    cleardevice();
    setcurrentwindow(window1);

    leap_year(year);
    settextstyle(0,HORIZ_DIR,6);
    int x=100,y=300;
    setcolor(7);
    rectangle(50,180,1500,780);
    outtextxy(100,220,"Sun" );
    outtextxy(300,220,"Mon" );
    outtextxy(500,220,"Tue" );
    outtextxy(700,220,"Wed" );
    outtextxy(900,220,"Thu" );
    outtextxy(1100,220,"Fri" );
    outtextxy(1300,220,"Sat" );
    for(day=1;day<=1+daycode*5;day++)
    {
        x=x+39;
    }
    for(day=1;day<=days_in_month[month];day++ )
    {
        char arr[50];
        sprintf(arr,"%d",day);
        outtextxy(x,y,arr);
        x=x+200;
        if((day+daycode)%7==0)
        {
            x=100;
            y=y+80;
        }
    }

    settextstyle(10,HORIZ_DIR,1);
    setcolor(15);
    fillellipse(80,830,5,5);
    outtextxy(90,820,"Press Y to view calender in a whole year view.");
    fillellipse(80,850,5,5);
    outtextxy(90,840,"Press left or right arrow keys to change months.");
    fillellipse(1000,830,5,5);
    outtextxy(1010,820,"Press Esc or 0 to close the screen.");
    fillellipse(1000,850,5,5);
    outtextxy(1010,840,"Press up or down to change year.");

    month_head(month,year);

    print_conditons_month(month);
}
int month_number()
{
    int month=0;
    if(present_month[0]=='J'&&present_month[1]=='a'&&present_month[2]=='n'&&present_month[3]=='u'&&present_month[4]=='a'&&present_month[5]=='r'&&present_month[6]=='y')
        month=1;
    else if(present_month[0]=='F'&&present_month[1]=='e'&&present_month[2]=='b'&&present_month[3]=='u'&&present_month[4]=='a'&&present_month[5]=='r'&&present_month[6]=='y')
        month=2;
    else if(present_month[0]=='M'&&present_month[1]=='a'&&present_month[2]=='r'&&present_month[3]=='c'&&present_month[4]=='h')
        month=3;
    else if(present_month[0]=='A'&&present_month[1]=='p'&&present_month[2]=='r'&&present_month[3]=='i'&&present_month[4]=='l')
        month=4;
    else if(present_month[0]=='M'&&present_month[1]=='a'&&present_month[2]=='y')
        month=5;
    else if(present_month[0]=='J'&&present_month[1]=='u'&&present_month[2]=='n'&&present_month[3]=='e')
        month=6;
    else if(present_month[0]=='J'&&present_month[1]=='u'&&present_month[2]=='l'&&present_month[3]=='y')
        month=7;
    else if(present_month[0]=='A'&&present_month[1]=='u'&&present_month[2]=='g'&&present_month[3]=='u'&&present_month[4]=='s'&&present_month[5]=='t')
        month=8;
    else if(present_month[0]=='S'&&present_month[1]=='e'&&present_month[2]=='p'&&present_month[3]=='t'&&present_month[4]=='e'&&present_month[5]=='m'&&present_month[6]=='b'&&present_month[7]=='e'&&present_month[8]=='r')
        month=9;
    else if(present_month[0]=='O'&&present_month[1]=='c'&&present_month[2]=='t'&&present_month[3]=='o'&&present_month[4]=='b'&&present_month[5]=='e'&&present_month[6]=='r')
        month=10;
    else if(present_month[0]=='N'&&present_month[1]=='o'&&present_month[2]=='v'&&present_month[3]=='e'&&present_month[4]=='m'&&present_month[5]=='b'&&present_month[6]=='e'&&present_month[7]=='r')
        month=11;
    else if(present_month[0]=='D'&&present_month[1]=='e'&&present_month[2]=='c'&&present_month[3]=='e'&&present_month[4]=='m'&&present_month[5]=='b'&&present_month[6]=='e'&&present_month[7]=='r')
        month=12;

    return month;
}
void print_single_month_calender()
{
    int month=month_number();
    int daycode=days_month(month,year);
    single_month_calender(year,month,daycode);
}
void print_calender()
{
    present_data();
    year=atoi(present_year);
    int daycode=days(year);
    leap_year(year);
    calender(year, daycode);
}
int main(void)
{
    print_calender();
    return 0;
}

