#ifndef FPROF_H
#define FPROF_H

#define NUM_BANDS       (8)
#define MAX_BAND_VAL    (9)
#define MIN_BAND_VAL    (0)

// frequency profile struct
typedef struct
{
    int bands[NUM_BANDS];
    int selected;
} fprof_t;

void fprof_init(fprof_t* this)
{
    int i;
    //for (i = 0; i < NUM_BANDS; i++)
    //  this->bands[i] = 4;

    this->bands[0] = 4;
    this->bands[1] = 3;
    this->bands[2] = 5;
    this->bands[3] = 4;
    this->bands[4] = 6;
    this->bands[5] = 5;
    this->bands[6] = 7;
    this->bands[7] = 6;

    this->selected = 3;
}

void fprof_incSel(fprof_t* this)
{
    if (this->selected < NUM_BANDS-1)
        this->selected++;
}

void fprof_decSel(fprof_t* this)
{
    if (this->selected > 0)
        this->selected--;
}

void fprof_incBand(fprof_t* this)
{
    if (this->bands[this->selected] < MAX_BAND_VAL-1)
        this->bands[this->selected]++;
}

void fprof_decBand(fprof_t* this)
{
    if (this->bands[this->selected] > MIN_BAND_VAL)
        this->bands[this->selected]--;
}

void fprof_getBands(fprof_t* this, char buffer[12])
{
    int i;
    buffer[0] = 'S';
    buffer[1] = this->selected + '0';
    for (i = 2; i < 2+NUM_BANDS; i++)
        buffer[i] = this->bands[i-2] + '0';
    buffer[NUM_BANDS+2] = 'E';
    buffer[NUM_BANDS+3] = '\0';
}


#endif
