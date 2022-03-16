#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>

#define max_year 2100
#define min_year 1900
#define max_size_pass 20
#define student_pass_info_file_name "passandstudentinfo.bin"
#define max_name 30
#define max_address 200


typedef struct
{
    int year;
    int month;
    int day;
}date;

typedef struct
{
    unsigned int studentid;
    char studentname[max_name];
    date studentdob;
    char class[8];
    char fathername[max_name];
    char mothername[max_name];
    unsigned long contactnumber;
    char studentaddress[max_address];
    date joiningdate;
}studentinfo;

typedef struct
{
    unsigned int staffid;
    date staffdob;
    char staffname[max_name];
    char staffaddress[max_address];
    unsigned long phonenumber;
    date joiningdate;
}staffinfo;

typedef struct
{
    unsigned int studentid;
    short int term;
    short int status;
    date paiddate;

}studentfees;

typedef struct
{
    unsigned int staffid;
    short int term;
    short int status;
    date paiddate;
}staffsalary;

typedef struct
{char password[max_size_pass];}pass;

void printcentermessage(const char* message)
{
    int len,pos;
    len=(50-strlen(message))/2;
    printf("\t\t\t");
    for(pos=0;pos<len;pos++)
    printf(" ");
    printf("%s",message);
}

void title(const char* message)
{
    system("cls");
    printf("\t\t\t*************************************************\n");
    printf("\t\t\t~~~~~~~~~~~~~~~~~ SCHOOL NAME ~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\t\t***************** Since XXXX ********************\n");
    printf("\t\t\t-------------------------------------------------\n");
    printcentermessage(message);
    printf("\n\t\t\t-------------------------------------------------\n");

}

void welcomemessage()
{
    title("By-Prihik");
    printf("\n\t\t\t....................................................");
    printf("\n\t\t\t...........  Record Management System  .............");
    printf("\n\t\t\t....................................................\n");
    printf("\n\n\t\t\t Enter any key to continue");
    getch();
}

int isvalidname(const char* name)
{
    int validname=1,len,i;
    len=strlen(name);
    for(i=0;i<len;i++)
    {
        if(!isalpha(name[i])&&name[i]!='\n'&&name[i]!=' ')
        {
            validname=0;
            break;
        }
    }
    return validname;

}

int isleapyear(int year)
{
    return (year%4==0&&year%100!=0||year%400==0);
}

int isvaliddate(date validdate)
{
    if(validdate.year>max_year||validdate.year<min_year)
    return 0;
    if(validdate.month<1||validdate.month>12)
    return 0;
    if(validdate.day<1||validdate.month>31)
    return 0;
    if(validdate.month==2)
    {
        if(isleapyear(validdate.year))
        return (validdate.day<=29);
        else
        return(validdate.day<=28);
    }
    if(validdate.month==4||validdate.month==6||validdate.month==9||validdate.month==11)
    return (validdate.day<=30);
    //for the rest months
    return 1;
}

int validid(unsigned int a)
{
    int found=1,i,j;
    studentinfo vid={0};
    FILE *fp=NULL;
    fp=fopen(student_pass_info_file_name,"rb");
    if(fp==NULL)
    {
        printf("\n\t\t\tfile not opened.");
        exit(1);
    }
    if(fseek(fp,sizeof(pass),SEEK_SET)!=0)
    {
       fclose(fp);
        printf("\n\t\t\tproblem in reading file.");
        exit (1);
    }
    while(fread(&vid,sizeof(vid),1,fp))
    {
        if(vid.studentid==a)
        {
        found=0;
        break;
        }
    }
    fclose(fp);
    return found;


}


void addstudent()
{
    studentinfo addstudentinfo={0};
    FILE *fp=NULL;
    int status=0;
    
    title("Add New Students");
    printf("\n\t\t\tEnter the details below:");
    printf("\n\t\t\t_______________________________________________________");
    do
    {
    printf("\n\t\t\tStudent ID:");
    fflush(stdin);
    scanf("%u",&addstudentinfo.studentid);
    status=validid(addstudentinfo.studentid);
    if(!status)
    printf("\n\t\t\tid already exists");
    }
    while(!status);
    do
    {
        printf("\n\t\t\tEnter name of the student:");
        fflush(stdin);
        fgets(addstudentinfo.studentname,max_name,stdin);
        status=isvalidname(addstudentinfo.studentname);
        if(!status)
        printf("\n\t\t\tPlease enter valid name.");
    }
    while(!status);
    do
    {
        printf("\n\t\t\tEnter the date of birth(dd/mm/yy):");
        fflush(stdin);
        scanf("%d/%d/%d",&addstudentinfo.studentdob.day,&addstudentinfo.studentdob.month,&addstudentinfo.studentdob.year);
        status=isvaliddate(addstudentinfo.studentdob);
        if(!status)
        printf("\n\t\t\tPlease enter valid date.");
    }
    while(!status);
     do
    {
        printf("\n\t\t\tEnter the Class:");
        fflush(stdin);
        fgets(addstudentinfo.class,8,stdin);
        status=isvalidname(addstudentinfo.class);
        if(!status)
        printf("\n\t\t\tPlease enter valid class name.");
    }
    while(!status);

    do
    {
        printf("\n\t\t\tEnter name of the father:");
        fflush(stdin);
        fgets(addstudentinfo.fathername,max_name,stdin);
        status=isvalidname(addstudentinfo.fathername);
        if(!status)
        printf("\n\t\t\tPlease enter valid name.");
    }
    while(!status);
    do
    {
        printf("\n\t\t\tEnter name of the mother:");
        fflush(stdin);
        fgets(addstudentinfo.mothername,max_name,stdin);
        status=isvalidname(addstudentinfo.mothername);
        if(!status)
        printf("\n\t\t\tPlease enter valid name.");
    }
    while(!status);
    do
    {
    printf("\n\t\t\tEnter the contact number:");
    fflush(stdin);
    scanf("%lu",&addstudentinfo.contactnumber);
    if(addstudentinfo.contactnumber==0)
    {
        status=0;
        printf("\n\t\t\tenter valid no");
    }
    else status=1;
    }
    while(!status);
    printf("\n\t\t\tEnter the address:");
    fflush(stdin);
    fgets(addstudentinfo.studentaddress,max_address,stdin);
        
    
    do
    {
        printf("\n\t\t\tEnter the date of joining(dd/mm/yy):");
        fflush(stdin);
        scanf("%d/%d/%d",&addstudentinfo.joiningdate.day,&addstudentinfo.joiningdate.month,&addstudentinfo.joiningdate.year);
        status=isvaliddate(addstudentinfo.joiningdate);
        if(!status)
        printf("\n\t\t\tPlease enter valid date.");
    }
    while(!status);
    fp=fopen(student_pass_info_file_name,"ab+");
     if(fp==NULL)
    {
        printf("\n\t\t\tFile not opened");
        exit (1);
    }
    fwrite(&addstudentinfo,sizeof(addstudentinfo),1,fp);
    fclose(fp);
    printf("\n\t\t\tstudent added sucessfully.\n\t\t\tpress any key to go to the last menu.....");
    fflush(stdin);
    getch();

}

void searchstudent()
{
    int found=0,studentid=0;
    studentinfo datasearchstudent={0};
    FILE *fp=NULL;
    title("Search Students");
    fp=fopen(student_pass_info_file_name,"rb");
    if(fp==NULL)
    {
        printf("\n\t\t\tflie is not opened");
        exit(1);
    }
    
    if(fseek(fp,sizeof(pass),SEEK_SET)!=0)
    {
        fclose(fp);
        printf("\n\t\t\tproblem in reading file.");
        exit (1);
    }
    printf("\n\n\t\t\tStudent id no to search:");
    fflush(stdin);
    scanf("%u",&studentid);
    while (fread(&datasearchstudent,sizeof(datasearchstudent),1,fp))
    {
        if(datasearchstudent.studentid==studentid)
        {
            found=1;
            break;
        }
    }
    if(found)
    {
        printf("\n\n\t\t\tStudent id = %u",datasearchstudent.studentid);
        printf("\n\n\n\t\t\tStudent name = %s",datasearchstudent.studentname);
        printf("\n\t\t\tDate of birth = %d/%d/%d",datasearchstudent.studentdob.day,datasearchstudent.studentdob.month,datasearchstudent.studentdob.year);
        printf("\n\n\t\t\tClass = %s",datasearchstudent.class);
        printf("\n\t\t\tFather's name = %s",datasearchstudent.fathername);
        printf("\n\t\t\tMother's name = %s",datasearchstudent.mothername);
        printf("\n\t\t\tContact number = %lu",datasearchstudent.contactnumber);
        printf("\n\n\t\t\tAddress = %s",datasearchstudent.studentaddress);
        printf("\n\t\t\tJoining date = %d/%d/%d",datasearchstudent.joiningdate.day,datasearchstudent.joiningdate.month,datasearchstudent.joiningdate.year);

    }
    else
    printf("\n\n\t\t\tNo record found.");
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to last menu.....");
    fflush(stdin);
    getch();


}

void arangeid()
{
    int found=0;
    unsigned int id,j;
    pass spass={0};
    studentinfo dataarangestudent={0};
    FILE *fp=NULL,*tmfp=NULL;
    unsigned int count=1;
    fp=fopen(student_pass_info_file_name,"rb");
    
    if(fp==NULL)
    {
        printf("\n\t\t\tFile not opened.");
        exit (1);
    }
    tmfp=fopen("temp.bin","wb");
    if(tmfp==NULL)
    {
        printf("\n\t\t\tFile not opened.");
        exit (1);
    }
     if(fseek(fp,sizeof(pass),SEEK_SET)!=0)
    {
        fclose(fp);
        printf("\n\t\t\tCan't read file.");
        exit (1);
    }
    while(fread(&dataarangestudent,sizeof(dataarangestudent),1,fp))
    {
        if(count<dataarangestudent.studentid)
        count=dataarangestudent.studentid;
    }
    rewind(fp);
    fread(&spass,sizeof(pass),1,fp);
    fwrite(&spass,sizeof(pass),1,tmfp);
    for(id=1;id<=count;id++)
    {
        for(j=1;j<=count;j++)
        {
        fread(&dataarangestudent,sizeof(dataarangestudent),1,fp);
        if(id==dataarangestudent.studentid)
        {
        fwrite(&dataarangestudent,sizeof(dataarangestudent),1,tmfp);
        break;
        }
        }
        rewind(fp);
        fseek(fp,sizeof(pass),SEEK_SET);
    }
    fclose(fp);
    fclose(tmfp);
    remove(student_pass_info_file_name);
    rename("temp.bin",student_pass_info_file_name);

}

void viewstudent()
{
    int found=0;
    studentinfo dataviewstudent={0};
    FILE *fp=NULL;
    unsigned int studentcount=0;
    arangeid();
    title("All Student's Details");
    fp=fopen(student_pass_info_file_name,"rb");
    if(fp==NULL)
    {
        printf("\n\t\t\tFile not opened.");
        exit (1);
    }
    if(fseek(fp,sizeof(pass),SEEK_SET)!=0)
    {
        fclose(fp);
        printf("\n\t\t\tCan't read file.");
        exit (1);
    }
    while(fread(&dataviewstudent,sizeof(dataviewstudent),1,fp))
    {
        printf("\n\n\t\t\tStudent id = %u\n",dataviewstudent.studentid);
        printf("\n\n\t\t\tStudent name = %s",dataviewstudent.studentname);
        printf("\n\t\t\tDate of birth = %d/%d/%d",dataviewstudent.studentdob.day,dataviewstudent.studentdob.month,dataviewstudent.studentdob.year);
        printf("\n\n\t\t\tClass = %s",dataviewstudent.class);
        printf("\n\t\t\tFather's name = %s",dataviewstudent.fathername);
        printf("\n\t\t\tMother's name = %s",dataviewstudent.mothername);
        printf("\n\t\t\tContact number = %lu",dataviewstudent.contactnumber);
        printf("\n\n\t\t\tAddress = %s",dataviewstudent.studentaddress);
        printf("\n\n\t\t\tJoining date = %d/%d/%d",dataviewstudent.joiningdate.day,dataviewstudent.joiningdate.month,dataviewstudent.joiningdate.year);
        printf("\n\n\t\t\t-----------------------------------------------------------------");
        found=1;
        studentcount++;
    }
    printf("\n\n\t\t\tTotal Students = %u",studentcount);
    fclose(fp);
    if(!found)
    printf("\n\t\t\tNo records.");
    printf("\n\t\t\tPress any key to go to previous menu");
    fflush(stdin);
    getch();
    
}

void deletestudent()
{
  int found=0,studentdelete=0;
  pass spass={0};
  studentinfo datadeletestudent={0};
  FILE *fp=NULL,*tmfp=NULL;
  title("Delete Students");
  fp=fopen(student_pass_info_file_name,"rb");
  if(fp==NULL)
  {
      printf("\n\t\t\tFile not opened.");
      exit (1);
  }
  tmfp=fopen("temp.bin","wb");
  if(fp==NULL)
  {
      printf("\n\t\t\tFile not opened");
      exit(1);
  }
  fread(&spass,sizeof(pass),1,fp);
  fwrite(&spass,sizeof(pass),1,tmfp);
  printf("\n\t\t\tEnter the id of student to delete:");
  scanf("%u",&studentdelete);
  while(fread(&datadeletestudent,sizeof(datadeletestudent),1,fp))
  {
      if(datadeletestudent.studentid != studentdelete)
      fwrite(&datadeletestudent,sizeof(datadeletestudent),1,tmfp);
      else
      found=1;
  }
  if(found)
  printf("\n\t\t\tRecord deleted sucessfully.");
  else
  printf("\n\t\t\tRecord not found.");
  fclose(fp);
  fclose(tmfp);
  remove(student_pass_info_file_name);
  rename("temp.bin",student_pass_info_file_name);
  printf("\n\t\t\tPress any key to continue....");
  fflush(stdin);
  getch();


}

void updatepass()
{
    pass cpass={0};
    char password[max_size_pass]={0};
    FILE *fp;
    title("Change Password");
    fp=fopen(student_pass_info_file_name,"rb+");
    if(fp==NULL)
    {
        printf("\n\t\t\tFile not opened.");
        exit (1);
    }
    printf("\n\t\t\tNew password:");
    fflush(stdin);
    fgets(password,max_size_pass,stdin);
    strcpy(cpass.password,password);
    fwrite(&cpass,sizeof(pass),1,fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\tLogin Again :)");
    fflush(stdin);
    getch();
    exit(0);


}

void mainmenu();

void studentsmenu()
{
    int choice=0;
    do
    {
        title("Students Menu");
        printf("\n\n\t\t\t1 - Add Student");
        printf("\n\t\t\t2 - Search Student");
        printf("\n\t\t\t3 - View All Students");
        printf("\n\t\t\t4 - Remove Student");
        printf("\n\t\t\t5 - Go to Main Menu");
        printf("\n\n\t\t\tYour Choice -> ");
        fflush(stdin);
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            addstudent();
            break;
            case 2:
            searchstudent();
            break;
            case 3:
            viewstudent();
            break;
            case 4:
            deletestudent();
            break;
            case 5:
            mainmenu();
            break;
            default:
            printf("\n\n\t\t\tInvalid input try again");
            
        }
        


    }
    while(choice!=5);
}

void mainmenu()
{
    int choice=0;
    do
    {
        title("Main Menu");
        printf("\n\n\t\t\t1 - Students");
        printf("\n\t\t\t2-  Staffs");
        printf("\n\t\t\t3 - Payment Info");
        printf("\n\t\t\t4 - Change Password");
        printf("\n\t\t\t5 - Exit");
        printf("\n\n\t\t\tYour Choice -> ");
        fflush(stdin);
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            studentsmenu();
            break;
            case 2:
            printf("\n\t\t\tsry not coded yet :(");
             printf("\n\t\t\tPress any key to go to main menu");
            fflush(stdin);
            getch();
            break;
            case 3:
            printf("\n\t\t\tsry not coded yet :(");
            printf("\n\t\t\tPress any key to go to main menu");
            fflush(stdin);
            getch();
            break;
            case 4:
            updatepass();
            case 5:
            exit(0);
            break;
            default:
            printf("\n\n\t\t\tInvalid input try again");
        }
        
    }
    while(choice!=5);

}

void login()
{
    char password[max_size_pass];
    int l=0;
    pass cpass={0};
    FILE *fp=NULL;
    title("Login");
    fp=fopen(student_pass_info_file_name,"rb");
    if(fp==NULL)
    {
        printf("\n\t\t\tFile not oppened.");
        exit(1);
    }
    fread(&cpass,sizeof(pass),1,fp);
    fclose(fp);
    do
    {
        printf("\n\t\t\tEnter password:");
        fflush(stdin);
        fgets(password,max_size_pass,stdin);
        if(!strcmp(password,cpass.password))
        mainmenu();
        else
        {
            printf("\n\n\t\t\tWrong password,try again\n\t\t\tOnly 3 wrong atempts allowed\n\n");
            l++;
        }
        

        
    }
    while(l<=3);
    if(l<3)
    {
        title("Login Failed");
        printf("\n\n\t\t\tUnknown user");
        fflush(stdin);
        getch();
        exit(0);
    }
}

int isfileexits(const char *path)
{
    FILE *fp=fopen(path,"rb");
    int status=0;
    if(fp!=NULL)
    status=1;
    fclose(fp);
    return status;
}

void start()
{
    FILE *fp=NULL;
    char defpass[]="sample\n";
    pass cpass={0};
    int status=0;
    status=isfileexits(student_pass_info_file_name);
    if(!status)
    {
        fp=fopen(student_pass_info_file_name,"wb");
        if(fp!=NULL)
        {
            strncpy(cpass.password,defpass,sizeof(defpass));
            fwrite(&cpass,sizeof(pass),1,fp);
            fclose(fp);
        }
    }
}

int main()
{
    start();
    welcomemessage();
    login();
    return 0;
}

