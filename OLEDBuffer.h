//
//  OLEDBuffer.h
//
//  Created by Dan LaBove on 4/20/16.
//

#ifndef __OLEDBuffer__
#define __OLEDBuffer__

#include <stdio.h>

#define BYTE_LENGTH             8
#define OLED_LENGTH             128
#define OLED_HEIGHT             32
#define NUM_BANDS               8

#define BUFFER_COLUMN           128
#define BUFFER_LINE             4

#define CEILING_DIVIDER_HEIGHT	((unsigned char)0x01) 
#define COLUMN_SELECTOR_HEIGHT	((unsigned char)0x03)
#define COLUMN_HEIGHT 			OLED_HEIGHT - CEILING_DIVIDER_HEIGHT - COLUMN_SELECTOR_HEIGHT
#define FREQ_COLUMN_BYTE        ((unsigned char)((0x01 << COLUMN_SELECTOR_HEIGHT) - 1) << (BYTE_LENGTH - COLUMN_SELECTOR_HEIGHT))

#define ALL_BLACK               ((unsigned char)0X00)
#define ALL_WHITE               ((unsigned char)0XFF)

//#define COLUMN_DIVIDER_WIDTH	((unsigned char)0x01) //will add functionality to take this as a parameter, for now, code assumes it's 1 pixel wide


/* OLEDClearBuffer clears the entire display buffer by writing 0x00 to each byte of the buffer */
void OLEDClearBuffer(void);

/* OLEDClearSelector clears the top 3 bits of each byte in the first line (where the column selector is). Called in OLEDUpdateSelectedFrequencyBand */
void OLEDClearSelector(void);

/* Called when user presses right or left button to select new frequency column */
void OLEDUpdateSelectedFrequencyBand(int column);

/* Called when user pressed up or down button to increase or decrease height of relative scaling for that frequency band */
void OLEDUpdateFrequencyBandHeight(int column, int height);

/* Called when in real-time display mode to update frequency content in each band of audio signal  */
void OLEDUpdateFrequencyBands(int heights[NUM_BANDS]);


#endif /* defined(__OLEDBuffer__) */
