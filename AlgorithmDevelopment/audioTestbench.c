/*  Project:  ZedboardAudioEqualizer
    Authors:  Luke Jaffe, Sean Kerr, Dan Labove
   
    Test code for running the frequency scaling code on a PC
    */

#include <stdlib.h>

#include "audioTestbench.h"
#include "frequencyScaling.h"

// ARRAY_SIZE

void fullSystemTest()
{
    SNDFILE *sf;
    SF_INFO info;
    int num_channels;
    int num, num_items;
    short *buf;
    short *outBuf;
    int f,sr,c;
    int i,j;
    FILE *out;
    
    /* Open the WAV file. */
    info.format = 0;
    sf = sf_open("resistance.wav",SFM_READ,&info);
    if (sf == NULL)
        {
        printf("Failed to open the file.\n");
        exit(-1);
        }
    /* Print some of the info, and figure out how much data to read. */
    f = info.frames;
    sr = info.samplerate;
    c = info.channels;
    printf("frames=%d\n",f);
    printf("samplerate=%d\n",sr);
    printf("channels=%d\n",c);
    num_items = f*c;
    printf("num_items=%d\n",num_items);
    /* Allocate space for the data to be read, then read it. */
    buf = (short *) malloc(num_items*sizeof(short));
    num = sf_read_short(sf,buf,num_items);
    sf_close(sf);
    printf("Read %d items\n",num);

    /* Buffer for processed data */
    outBuf = (short *) malloc(num_items*sizeof(short));

    /* Initialize everything in frequencyScaling.c */
    configureFft();
    configureWindow();


    for (i = 0; i < num / ARRAY_SIZE; i++)
    {
        processInput(buf + (i * ARRAY_SIZE), outBuf + (i * ARRAY_SIZE));
    }

    sf = sf_open("resistanceOutput.wav", SFM_WRITE, &info);
    sf_write_short(sf, outBuf, num_items);
    sf_close(sf);
}

void frequencyScalingUnitTest()
{
    configureFft();
    configureScalars();
    configureWindow();

    srand(12345);

    float inputArray[ARRAY_SIZE];
    float outputArray[ARRAY_SIZE];
    float scalars[ARRAY_SIZE];

    int i;
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        inputArray[i] = 1.0 * rand();
        scalars[i] = 1.0;
    }

    frequencyScale(inputArray, outputArray, ARRAY_SIZE, scalars);

    for (i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%2.4f %2.4f\n", inputArray[i], outputArray[i]);
    }
}

void configureAllPassTest()
{

    float frequencyScalars[ARRAY_SIZE];
    int i;

    for (i = 0; i < ARRAY_SIZE; i++)
    {
        frequencyScalars[i] = 1.0;
    }

    configureScalars(frequencyScalars);
}

void configureLowPassTest()
{

    float frequencyScalars[ARRAY_SIZE];
    int i;

    for (i = 0; i < ARRAY_SIZE; i++)
    {
        frequencyScalars[i] = 1.0 - (1.0 * i / ARRAY_SIZE);
    }

    configureScalars(frequencyScalars);
}

void configureHighPassTest()
{

    float frequencyScalars[ARRAY_SIZE];
    int i;

    for (i = 0; i < ARRAY_SIZE; i++)
    {
        frequencyScalars[i] = (1.0 * i / ARRAY_SIZE);
    }

    configureScalars(frequencyScalars);
}

void configureCrazyHighPassTest()
{
    float frequencyScalars[ARRAY_SIZE];
    int i;

    for (i = 0; i < 2048; i++)
    {
        frequencyScalars[i] = 0.0;
    }

    for (i = 2048; i < ARRAY_SIZE; i++)
    {
        frequencyScalars[i] = 1.0;
    }

    configureScalars(frequencyScalars);
}

void configureCrazyLowPassTest()
{
    float frequencyScalars[ARRAY_SIZE];
    int i;

    for (i = 0; i < 50; i++)
    {
        frequencyScalars[i] = 1.0;
    }

    for (i = 50; i < ARRAY_SIZE; i++)
    {
        frequencyScalars[i] = 0.0;
    }

    configureScalars(frequencyScalars);
}


int main()
{
    //configureAllPassTest();
    configureCrazyLowPassTest();
    fullSystemTest();
}
