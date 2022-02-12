

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdint.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <getopt.h>

void main_menu();
void name();
void open_communication();
void set_communication();//The settings about termios.h 
void operation_result_menu();//It is used after operation completed in many function.

//Variables needed by many functions.
struct termios options;//for communication settings
int port=0;//the port number required for every operation between pc and arduino

int main(){

	open_communication(); 
	main_menu();
	close(port);
	return 0;
}
void main_menu(){

	// I created options as enum.
	enum operations{NAME=1,EXIT=0}; 

	enum operations operation;

	int input=0;

	printf("MENU :     \n"
		"(1)ENTER NAME \n"
		"(0) EXIT \n"
		"PLEASE SELECT:");
	int check=scanf("%d",&input);

	//According to the input ,it takes the user to the correct option.
	if(check!=0)
	{	
		switch(input){

			case NAME:
			name();
			break;
			
			case EXIT:
			close(port);
			exit(0);
			break;
			default:
			main_menu();
			break;
		}
	}

}

void open_communication()
{
	char checkport[12]="/dev/ttyUSB0";
	char portnumbers[10]={'0','1','2','3','4','5','6','7','8','9'};
	int nextport=1;
	int condition=0;
	//"open" function  returns the port number.In addition,it will cause the arduino to reset.
	//It will check the port numbers starting from 0.
	// If there is a ready port,it is completed, if not get next portnumber and continue.
	while(nextport<10)

	{
		port = open(checkport, O_RDWR | O_NOCTTY | O_NDELAY);
		if(port==-1)
		{	
			checkport[11]=portnumbers[nextport];
			nextport++;
		}
		else{
			
			nextport=10;
		}
	}
	if(port!=-1)
	{
		//wait for arduino to get ready 
		sleep(2);
		//settings 
		set_communication(port);
	}
	else{
		printf("%s,\n,run by sudo ",strerror(errno));
	}
	//Clear the serial port data if there is any.
	tcflush(port, TCOFLUSH);
	
}

void set_communication()
{

	//I set baud rate to 9600 for both this side and arduino side to prevent data loss.
	//and some setting details about termios.h.
	tcgetattr(port, &options);
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	options.c_cflag |= (CLOCAL | CREAD);
	tcsetattr(port, TCSANOW, &options);
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CRTSCTS;
	options.c_cflag |= CREAD | CLOCAL;
	options.c_iflag &= ~(IXON | IXOFF | IXANY); 
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 
	options.c_oflag &= ~OPOST; 
	options.c_cc[VMIN]  = 0;
	options.c_cc[VTIME] = 0;
}

void operation_result_menu()
{
	//Standard menu for many operations,to ask user where they want to go.
	int router=0;
	printf("\nOperation completed.\n");
	printf("PLEASE SELECT FROM THE FOLLOWING\n");
	printf("(1)MAIN MENU\n");
	printf("(2)REPEAT\n");
	printf("(3)EXIT\n");
	printf("PLEASE SELECT:");
	int check=scanf("%d",&router);
	if(check!=0){
		switch(router)
		{
			case 1:
			main_menu();	
			break;
			case 2:
			name();
			break;
			case 3:
			close(port);
			exit(0);
			break;
			default:
			main_menu();
			break;
		}
	}
	

}
void name()
{

	char name[50]={""};
	scanf("%s",name);
	char startsign[1]={'1'};
	char endsign[1]={'0'};
	int length=strlen(name);
	printf("%s\n",name);
	write(port,startsign,1);
	write(port,name,length);
	write(port,endsign,1);
	usleep(10000);//some delay for data and precision
	operation_result_menu();


}