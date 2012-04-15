#include <node.h>
#include <v8.h>
//#include "rs232.h"
#include <stdio.h>    /* Standard input/output definitions */

#include <stdlib.h>
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>
#include <time.h>

using namespace v8;

int serialport_init(const char* serialport, int baud);
int serialport_writebyte(int fd, uint8_t b);
int serialport_write(int fd, const char* str);
int baudrate = 9600;
int fd = 0;
int toggle = 0;
int toggleLight(int value);
int serialport_read_until(int fd, char* buf, char until);

Handle<Value> Method(const Arguments& args) {
  //SendByte(bdrate,'1');
  HandleScope scope;
  toggleLight(toggle);
  if(toggle == 1){
     toggle = 0;
     return scope.Close(String::New("Light Turned On"));
  }
  else{
     toggle=1;
     return scope.Close(String::New("Light Turned Off"));
  }
}

void init(Handle<Object> target) {
  char buffer[255];
  fd = serialport_init("/dev/ttyACM0", baudrate);
  serialport_read_until(fd,buffer, '\n');
//  printf("Message Recieved: %s\n", buffer);
  //int rc = serialport_writebyte(fd, 1);
  //char buffer2[255];
  //serialport_read_until(fd,buffer2, '\n');
  //printf("Message Recieved: %s\n", buffer2);

  target->Set(String::NewSymbol("hello"),
      FunctionTemplate::New(Method)->GetFunction());
}
NODE_MODULE(helloworld, init)


int toggleLight(int value){
   int rc;
  // printf("The value: %d\n", value);
   if(value==0){
    // printf("%s\n", "Turning Off");
     rc = serialport_writebyte(fd, 0);
     char buffer[255];
     serialport_read_until(fd,buffer, '\n');
    // printf("Message Recieved: %s\n", buffer);
     if(rc==-1) return -1;
   }
   if(value==1){
     //printf("%s\n", "Turning On");
     rc = serialport_writebyte(fd, 1);
     char buffer[255];
     serialport_read_until(fd,buffer, '\n');
     //printf("Message Recieved: %s\n", buffer);
     if(rc==-1) return -1;
   }
   return rc;
}

int serialport_read_until(int fd, char* buf, char until)
{
    char b[1];
    int i=0;
    do { 
        int n = read(fd, b, 1);  // read a char at a time
        if( n==-1) {
	        buf[0] = 0;  // null terminate the string
		return -1;    // couldn't read
	}
        if( n==0 ) {
            usleep( 10 * 1000 ); // wait 10 msec try again
            continue;
        }
        buf[i] = b[0]; i++;
    } while( (b[0] != until) || (i>250));

    buf[i] = 0;  // null terminate the string
    return 0;
}

int serialport_writebyte( int fd, uint8_t b)

{
    printf("Sending %d",b);
    int n = write(fd,&b,1);

    if( n!=1)

	  return -1;

    return 0;

}



int serialport_write(int fd, const char* str)

{

    int len = strlen(str);

    int n = write(fd, str, len);

    if( n!=len )

	  return -1;

    return n;

}





// takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1")

// and a baud rate (bps) and connects to that port at that speed and 8N1.

// opens the port in fully raw mode so you can send binary data.

// returns valid fd, or -1 on error

int serialport_init(const char* serialport, int baud)

{

    struct termios toptions;

    int fd;

    //fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);

    fd = open(serialport, O_RDWR | O_NOCTTY);

    if (fd == -1)  {

	  perror("init_serialport: Unable to open port ");

	  return -1;

    }



    if (tcgetattr(fd, &toptions) < 0) {

	  perror("init_serialport: Couldn't get term attributes");

	  return -1;

    }

    speed_t brate = baud; // let you override switch below if needed

    switch(baud) {

    case 4800:   brate=B4800;   break;

    case 9600:   brate=B9600;   break;


    case 38400:  brate=B38400;  break;

    case 57600:  brate=B57600;  break;

    case 115200: brate=B115200; break;

    }

    cfsetispeed(&toptions, brate);

    cfsetospeed(&toptions, brate);



    // 8N1

    toptions.c_cflag &= ~PARENB;

    toptions.c_cflag &= ~CSTOPB;

    toptions.c_cflag &= ~CSIZE;

    toptions.c_cflag |= CS8;

    // no flow control

    toptions.c_cflag &= ~CRTSCTS;



    toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw



    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html

    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 20;



    if( tcsetattr(fd, TCSANOW, &toptions) < 0) {

	  perror("init_serialport: Couldn't set term attributes");

	  return -1;

    }
    return fd;
}
