#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

#include <termcap.h>

void print_bars(int bars[8], int selected)
{
    int i, j, k;
    int display[8][8];
    for (i = 0; i < 8; i++)
    {
        j = 0;
        k = 0;

        for (j = 0; j < bars[i]; j++)
            display[7-j][i] = 1;

        display[7-j][i] = 0;
        
        for (k = bars[i]+1; k < 8; k++)
            display[7-k][i] = -1;  
    }

    for (i = 0; i < 8; i++)
    {
        if (selected == i)
            printf(" v  ");
        else
            printf("    ");
    }
    printf("\n");

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (display[i][j] == 1)
                printf("| | ");
            else if (display[i][j] == 0)
                printf("___ ");
            else
                printf("    ");
        }
        printf("\n");
    }
}

void get_garbage(int USB)
{
    /* get good part */
    int n = 0,
        spot = 0;
    char buf = '\0';

    char response[1024];
    memset(response, '\0', sizeof response);
    do 
    {
        n = read( USB, &buf, 1 );
        sprintf( &response[spot], "%c", buf );
        spot += n;
    } 
    while( buf != 'S' && n > 0);

    if (n < 0) 
    {
        printf("Error reading: %s\n", strerror(errno));
    }
    else if (n == 0) 
    {
        printf("Read nothing!\n");
    }
    else 
    {
        //printf("Garbage: %s\n", response);
    }
}

int get_msg(int USB)
{
    /* get good part */
    int n = 0,
        spot = 0;
    char buf = '\0';

    char response[1024];
    memset(response, '\0', sizeof response);
    do 
    {
        n = read( USB, &buf, 1 );
        sprintf( &response[spot], "%c", buf );
        spot += n;
    } 
    while( buf != 'E' && n > 0);

    if (n < 0) 
    {
        printf("Error reading: %s\n", strerror(errno));
    }
    else if (n == 0) 
    {
        printf("Read nothing!\n");
    }
    else 
    {
        //printf("Response: %s, %d\n", response, (int)strlen(response));
        if (strlen(response) < 10)
            return 1;
        response[spot-1] = '\0';
        int i, bars[8];
        int selected = response[0] - '0';
        for (i = 1; i <= 8; i++)
        {
            bars[i-1] = response[i] - '0';
        }
        print_bars(bars, selected);
        return 0;
    }
}

int main()
{
    int USB = open( "/dev/ttyACM0", O_RDWR| O_NOCTTY );

    struct termios tty;
    struct termios tty_old;
    memset (&tty, 0, sizeof tty);

    /* Error Handling */
    if ( tcgetattr ( USB, &tty ) != 0 ) 
    {
       printf("Error %d from tcgetattr: %s\n", errno, strerror(errno));
    }

    /* Save old tty parameters */
    tty_old = tty;

    /* Set Baud Rate */
    cfsetospeed (&tty, (speed_t)B115200);
    cfsetispeed (&tty, (speed_t)B115200);

    /* Setting other Port Stuff */
    tty.c_cflag     &=  ~PARENB;            // Make 8n1
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;

    tty.c_cflag     &=  ~CRTSCTS;           // no flow control
    tty.c_cc[VMIN]   =  1;                  // read doesn't block
    tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

    /* Make raw */
    cfmakeraw(&tty);

    /* Flush Port, then applies attributes */
    tcflush( USB, TCIFLUSH );
    if ( tcsetattr ( USB, TCSANOW, &tty ) != 0) 
    {
       printf("Error %d from tcsetattr\n", errno);
    }

    do 
    {
        get_garbage(USB);
    }
    while (get_msg(USB) == 1);
}
