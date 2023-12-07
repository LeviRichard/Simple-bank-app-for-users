#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <string.h>
#include <windows.h>
#include <time.h>
int menu();
void brokenlines();
void delete_account();
void login();
void set_account();
void forgot_password();
int login_menu();
void deposit();
void withdraw();
void check_balance();
void transfer();
void encrypt(char pass[], int key)// Using substitution cipher
{
    for(int i=0; i<strlen(pass); i++)
    {
        pass[i]=pass[i]-key;
    }

}
char* generate_transaction_id() {
    int counter=0;
    time_t t = time(NULL);
    counter++;
    static char id[20];
    sprintf(id, "%ld%04d", (long)t, counter);
    return id;
}
struct account
{
    char name[30];
    char DOB[20];
    char account_number[20];
    char phone_number[20];
    char pass1[20];
    char transfer_code[5];
    long int balance;
}a;





int main()
{
    while(1)
    {
        setaccount:
        switch(menu())
        {
            case 1:
                set_account();
                break;
            case 2:
                login();
                break;
            case 3:
                forgot_password();
                break;
            case 4:
                delete_account();
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("Invalid Option");
                break;
        }
    }
}

int menu()
{
    int choice;
    system("cls");
    system("color 0A");
    printf("---------------------------------WELCOME---------------------------------\n");
    printf("1.Set Account\n");
    printf("2.Login\n");
    printf("3.Forgort Password\n");
    printf("4.Delete Account\n");
    printf("5.Exit\n");
    brokenlines();
    printf("\nEnter Option: ");
    scanf("%d",&choice);
    return choice;
}

void takepassword(char pass1[20]) //to mask the password
{
    char ch;
    int i=0;
    while(1)
        {
            ch=getch();

            if(ch==13) //if user presses "enter" it will end the command
            {
                pass1[i] = '\0';// adding a non character to the end of the string
                break;
            }
            else if(ch==8) //if user makes a mistake and wants to erase
            {
                if(i>0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else if(ch==9 ||  ch==32)  //if user uses tab or space bar, it will continue and not add a character
            {
                break;
                getch();
            }
            else if(ch==27)//if escape key is pressed, it will make the first array '0' a null value
            {
                pass1[0]='\0';
                return;
            }
            else
            {
                pass1[i++] = ch;
                printf("*");
            }


        }
}

void confirmpassword(char pass2[20]) //to mask the password
{
    char ch;
    int i=0;
    while(1)
        {
            ch=getch();

            if(ch==13) //if user presses "enter" it will end the command
            {
                pass2[i] = '\0';// adding a non character to the end of the string
                break;
            }
            else if(ch==8) //if user makes a mistake and wants to erase
            {
                if(i>0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else if(ch==9 ||  ch==32)  //if user uses tab or space bar, it will continue and not add a character
            {
                continue;
            }
            else
            {
                pass2[i++] = ch;
                printf("*");
            }


        }
}





void set_account()
{
    system("cls");
    char pass2[20];
    struct account a;
    FILE *fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","w");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    int c;
   
    printf("....................ACCOUNT SET UP.........................");
    printf("\nEnter Name:  ");
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%s", a.name);
    printf("\nEnter PhoneNumber: ");
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%s",a.phone_number);
    printf("\nEnter Date of Birth:  ");
    scanf("%s",a.DOB);
    printf("\nEnter Account number: ");
    scanf("%s",a.account_number);
    printf("\nInitial Deposit: ");
    scanf("%d",&a.balance);
    printf("\nEnter Transaction Code: ");
    takepassword(a.transfer_code);
    encrypt(a.transfer_code,0XAED);
    
    printf("\nEnter Password: ");
    takepassword(a.pass1);
    encrypt(a.pass1,0XAED);
    
    system("cls");
    confirm:
    printf("\nConfirm Password: ");
    confirmpassword(pass2);
    encrypt(pass2,0XAED);
    while ((c = getchar()) != '\n' && c != EOF);
    
    if(strcmp(a.pass1,pass2)==0)
    {
        system("cls");
        fwrite(&a,sizeof(struct account),1,fp);
        fclose(fp);
        
        fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","r");
        if(fp == NULL)
        {
            printf("Error opening file\n");
            return;
        }
        fread(&a, sizeof(struct account),1,fp);
        printf("\nACCOUNT CREATED SUCCESSFULLY!\n");
        brokenlines();
        printf("\nName: %s\n", a.name);
        brokenlines();
        printf("\nAccount Number: %s\n", a.account_number);
        getch();
    }
    else
    {
        system("cls");
        printf("\nINCOORECT PASSWORD\n");
        goto confirm;
    }
    fclose(fp); 
}

void login()
{
    system("cls");
    system("color 0A");
    char pass3[20];
    struct account a;
    FILE *fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    fread(&a, sizeof(struct account),1,fp);
    /*i used this for error checking, because this function was fucking me up, but it has been fixed! C is Frustrating
    printf("Name: %s\n", a.name);
    printf("Phone Number: %s\n", a.phone_number);
    printf("DOB: %s\n", a.DOB);
    printf("Account Number: %s\n", a.account_number);
    printf("Password: %s\n", a.pass1);*/

    int attempts =0;
    printf("\n------------------------------LOGIN----------------------------\n");
    printf("press the ESCAPE key to go back to main menu\n");
    password:
    brokenlines();
    printf("\nEnter password: ");
    takepassword(pass3);
    if(pass3[0]=='\0')
    {
        return;
    }
    encrypt(pass3,0XAED);
    
    /*this was for error checking too 
    printf("Encrypted Password: %s\n", pass3);
    int result = strcmp(a.pass1, pass3);
    printf("strcmp Result: %d\n", result);*/

    if(strcmp(a.pass1,pass3)==0)
    {
        fclose(fp);
        while(1)
        {
            switch(login_menu())
            {
                case 1:
                  check_balance();
                  break;
                case 2:
                  deposit();
                  break;
                case 3:
                  withdraw();
                  break;
                case 4:
                  transfer();
                  break;
                case 5:
                  return;
                  break;
                case 6:
                   exit(0);
                   break;
                default:
                  printf("\nINVALID OPTION");
                  break;
            }
        }
    }
    else 
    {
       attempts++;
       if (attempts>=5)
       {
           system("cls");
           system("color 0A");
           printf("\nACCOUNT BLOCKED\n");
           getch();
        
       }
       else
       {
            printf("\nINCORRECT PASSWORD\n");
            goto password;
       }
    }
}


void forgot_password()
{
   
    system("cls");
    system("Color 0A");
    char confirm_pass[20];
    int num1,num2;
    srand(time(0));//initiate the random number function
    num1=rand()%10000;// generate random numbers and make it = num1
    printf(" PASSWORD CODE: %d\n",num1);
    brokenlines();
    code:
    printf("\nEnter code: ");//this code is usaully send to an email or SMS, but for educational purposes it will be displayed on our terminal
    scanf("%d",&num2);
    brokenlines();
    if(num1==num2)
    {
        struct account a;
        FILE *fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt", "r");
        fread(&a,sizeof(struct  account),1,fp);

        printf("\nEnter new password: ");
        takepassword(a.pass1);
        encrypt(a.pass1,0XAED);
        printf("\n");
        brokenlines();

        confirm:
        printf("\nConfirm new password: ");
        takepassword(confirm_pass);
        encrypt(confirm_pass,0XAED);
        if(strcmp(a.pass1,confirm_pass)==0)
        {
            printf("\n---------------------PASSWORD CHANGED SUCCESSFULLY------------------------\n");
            fp= fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt", "w");//to edit just one value and not the whole file
            fwrite(&a, sizeof(struct account), 1, fp);
            getch();

        }
        else
        {
            printf("\nINCORRECT PASSWORD\n");
            goto confirm;
        }
        fclose(fp);
    }
    else
    {
        printf("\nINCORRECT CODE\n");
        goto code;
    }
}


int login_menu()
{
    system("cls");
    int option;
    printf("..........................MENU.........................\n");
    printf("1.Check Balance\n");
    printf("2.Deposit\n");
    printf("3.Withdraw\n");
    printf("4.Transfer\n");
    printf("5.Back\n");
    printf("6.Exit\n");
    brokenlines();
    printf("\nEnter option: ");
    scanf("%d",&option);
    return option;
}
void check_balance()
{
    system("cls");
    system("color 0A");
    struct account a;
    FILE *fp = fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","r");
    
    fread(&a,sizeof(struct account),1,fp);
    printf("\nAccount Balance: %d",a.balance);
    fclose(fp);
    getch();
}


void deposit()
{
    system("cls");
    system("color 0A");
    time_t tm;
    time(&tm);
    struct account a;
    int amt;
    char transfer_code[20];
    FILE *fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","r");
    fread(&a,sizeof(struct account),1,fp);
    fclose(fp);
    drop:
    printf("\nAmount to be Deposited: ");
    scanf("%d",&amt);
    brokenlines();
    printf("\nEnter Transaction Code: ");
    takepassword(transfer_code);
    encrypt(transfer_code,0XAED);
    if(strcmp(a.transfer_code,transfer_code)==0)
    {
        if(amt<0)
        {
          printf("\nInvalid amount!");
          goto drop;
        }
        else if(a.balance>LONG_MAX-amt){
          printf("\nDeposite amount is too large!");
          goto drop;
        }
        else
        {
         a.balance += amt;
         fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","w");
         fseek(fp, 0, SEEK_SET);
         fwrite(&a, sizeof(struct account), 1, fp);
         fclose(fp);
         printf("\n-----------------------Amount Deposited Successfully!-----------------------------------");
         fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","r");
         fread(&a,sizeof(struct account),1,fp);
     
         printf("\nNew balance: %d\n",a.balance);
         brokenlines();
          printf("\nDate and Time of Deposit: %s",ctime(&tm));
         fclose(fp);
         getch();
        }
    }
    else
    {
        printf("\nInvalid code\n");
        goto drop;
    }
    
}
void withdraw()
{
    system("cls");
    system("color 0A");
    time_t tm;
    time(&tm);
    struct account a;
    int amt;
    char withdrawcode[5];
    FILE *fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","r");
    fread(&a,sizeof(struct account),1,fp);
    fclose(fp);
    drop:
    printf("\nAmount to be Withdrawn: ");
    scanf("%d",&amt);
    brokenlines();
    printf("\nEnter Transcation Code: ");
    takepassword(withdrawcode);
    encrypt(withdrawcode,0XAED);
    if(strcmp(a.transfer_code, withdrawcode) == 0)
    {
        if(amt<0)
        {
          printf("\nInvalid amount!");
          goto drop;
        }
        else if(amt > a.balance)
        {
          printf("\nWithdraw amount is too large!");
        }
        else
        {
         a.balance -= amt;
         fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","w");
         fseek(fp, 0, SEEK_SET);
         fwrite(&a, sizeof(struct account), 1, fp);
         fclose(fp);
         printf("\n-----------------------Withdrawal Successfull!--------------------------------");
         fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","r");
         fread(&a,sizeof(struct account),1,fp);
       
         printf("\nNew balance: %d\n",a.balance);
          brokenlines();
         printf("\nDate and Time of Withdrawal: %s",ctime(&tm));
         fclose(fp);
         getch();
        }
    }
    else
    {
        printf("\nInvalid Code!\n");
        goto drop;
    }
}


   

void transfer()
{
    system("cls");
    system("color 0A");
    time_t tm;
    time(&tm);
    char recipient[20], bankname[20], recipient_name[20];
    struct account a;
    int amt;
    char moneycode[5];
    FILE *fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","r");
    fread(&a,sizeof(struct account),1,fp);
    fclose(fp);
    printf("\nEnter Account Name of Recipient: ");
    scanf("%s",recipient_name);
    printf("\nEnter Account Number of Recipient: ");
    scanf("%s",recipient);
    printf("\nEnter Bank Name of Recipient: ");
    scanf("%s",bankname);

    drop:
    printf("\nAmount to be Transfered: \n");
    scanf("%d",&amt);
    brokenlines();
    printf("\nEnter transaction Code: ");
    takepassword(moneycode);
    encrypt(moneycode,0XAED);
    if(strcmp(moneycode, a.transfer_code) == 0)
    {
        if(amt<0)
        {
         printf("\nInvalid amount!");
         goto drop;
        }
        else if(amt > a.balance)
        {
          printf("\nAmount is too large!");
        }
        else
        {
          a.balance -= amt;
          fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","w");
          fseek(fp, 0, SEEK_SET);
          fwrite(&a, sizeof(struct account), 1, fp);
          fclose(fp);
          printf("\n-----------------------TRANSFER SUCCESSFUL!--------------------------------");
          fp=fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt","r");
          fread(&a,sizeof(struct account),1,fp);
       
          printf("\nNew balance: %d\n",a.balance);
          brokenlines();
          printf("\nAccount Name of Recipient: %s\n",recipient_name);
          brokenlines();
          printf("\nAccount Number of Recipient: %s\n",recipient);
          brokenlines();
          printf("\nBank Name of Recipient: %s\n",bankname);
          brokenlines();
          printf("\nTransaction ID: %s\n",generate_transaction_id());
          brokenlines();
          printf("\nDate and Time of Transfer: %s",ctime(&tm));
          fclose(fp);
          getch();
        }
    }
    else
    {
        printf("\nInvalid Code!\n");
        goto drop;
    }
}
void delete_account()
{
    system("cls");
    system("color 0A");
    struct account a;
    FILE *fp = fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt", "r");
    if (fp == NULL)
    {
        printf("\nERROR OPENING THE FILE\n");
        getch();
        return;
    }

    char ch = fgetc(fp);//check if file is empty
    if (ch == EOF)//if file is empty it will return -1(EOF)
    {
        printf("\nNO ACCOUNT TO DELETE\n");
        getch();
    }
    else
    {
        char n;
        printf("\nDO YOU WANT TO DELETE [Y|N]: ");
        scanf(" %c", &n); // Notice the added space before %c to consume newline character
        if (n == 'Y' || n == 'y')
        {
            fclose(fp); // Close the file pointer before opening it in write mode
            fp = fopen("C:\\Users\\HP\\Documents\\Education\\Programming\\C PROGRMING\\C projects\\Bank management screen\\Bankmanagement.txt", "w");
            if (fp == NULL)
            {
                printf("\nERROR OPENING THE FILE\n");
                getch();
                return;
            }

            fprintf(fp, " ");//print empty spaces in the file
            fclose(fp); // Close the file pointer after overwriting the file
            printf("\nACCOUNT SUCCESSFULLY DELETED");
            getch();
        }
        else if (n == 'N' || n == 'n')
        {
            printf("\nACCOUNT DELETION STOPPED");
            getch();
        }
        else
        {
            printf("\nINVALID INPUT. PLEASE TRY AGAIN.");
            getch();
        }
    }
    fclose(fp); // Close the file pointer after the operations are done
    getch();
}

void brokenlines()
{
    for(int i=0; i<60; i++)
    {
        printf("-");
    }
}
