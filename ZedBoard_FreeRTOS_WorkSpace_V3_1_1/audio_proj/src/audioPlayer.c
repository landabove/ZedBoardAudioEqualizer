/**
 *@file audioPlayer.c
 *
 *@brief
 *  - core module for audio player
 *
 * Target:   TLL6527v1-0      
 * Compiler: VDSP++     Output format: VDSP++ "*.dxe"
 *
 * @author:  Gunar Schirner
 *           Rohan Kangralkar
 * @date	03/08/2010
 *
 * LastChange:
 * $Id: audioPlayer.c 846 2014-02-27 15:35:54Z fengshen $
 *
 *******************************************************************************/

#include "audioPlayer.h"
#include "adau1761.h"
#include "zedboard_freertos.h"
#include "stdio.h"
#include "gpio_interrupt.h"
#include "display.h"

#define CHUNK_NUM 30
#define VOLUME_CHANGE_STEP (4)
#define VOLUME_MAX (0x7F)
#define VOLUME_MIN (0x2F)

static void gpio_task( void *pvParameters );
void display_task (void *arg);

static int gpio_setupInts(audioPlayer_t *pThis);
static void gpio_intrHandler(void *pRef);

display_t display;

/* Define QueueHandle */
QueueHandle_t gpio_queue;

/** initialize audio player 
 *@param pThis  pointer to own object 
 *
 *@return 0 success, non-zero otherwise
 **/
int audioPlayer_init(audioPlayer_t *pThis)
{
    int status = 0;
    
    printf("[AP]: Init start\r\n");
    
    pThis->volume 		= VOLUME_MIN; /*default volume */
    pThis->frequency 	= 48000; /* default frequency */
    

    /* init the codec */
	adau1761_init(&(pThis->codec));

	/* allocate rx buffer pool */
	status = bufferPool_d_init(&(pThis->rxbp), CHUNK_NUM, CHUNK_SIZE);
    if ( 1 != status ) {
        return FAIL;
    }
    
    /* Initialize the gpio ... (TBD) */
    /* TODO insert code for GPIO init here */

    /* Initialize the audio RX module*/
    status = audioRx_init(&pThis->rx, &pThis->rxbp) ;
    if ( 1 != status) {
        return FAIL;
    }

    /* Initialize the audio TX module */
    status = audioTx_init(&pThis->tx, &pThis->rxbp);
    if ( 1 != status ) {
        return FAIL;
    }   
    
    printf("[AP]: Init complete\r\n");

    return PASS;
}


/** startup phase after initialization 
 *@param pThis  pointer to own object 
 *
 *@return 0 success, non-zero otherwise
 **/
int audioPlayer_start(audioPlayer_t *pThis)
{
    printf("[AP]: startup \r\n");
    
    /* create the gpio task */
    xTaskCreate( gpio_task, ( signed char * ) "HW", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1 , NULL );

    /* create the display task */
    xTaskCreate( display_task, ( signed char * ) "HW", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1 , NULL );

	/* create the audio task */
	xTaskCreate( audioPlayer_task, ( signed char * ) "HW", configMINIMAL_STACK_SIZE, pThis, tskIDLE_PRIORITY + 1 , pThis );

    
    return PASS;
}

/* GPIO Task */
static void gpio_task( void *pvParameters )
{
	/* Create a queue capable of containing 10 unsigned long values. */
	gpio_queue = xQueueCreate( 10, sizeof(int));

	for(;;)
	{
		u32 value;
		/* Receive the counter value from Queue */
		if( xQueueReceive( gpio_queue, &value, 1000) )
		{
			vTaskDelay(1);
			u32 gpio_data = (*(volatile u32 *)GPIO_DATA_2);

			if ((gpio_data & BTN_LEFT) & (value & BTN_LEFT))
			{
				display_decSel(&display);
			}
			if ((gpio_data & BTN_CENTER) & (value & BTN_CENTER))
			{
				display_init(&display);
			}
			if ((gpio_data & BTN_DOWN) & (value & BTN_DOWN))
			{
				display_decBand(&display);
			}
			if ((gpio_data & BTN_RIGHT) & (value & BTN_RIGHT))
			{
				display_incSel(&display);
			}
			if ((gpio_data & BTN_UP) & (value & BTN_UP))
			{
				display_incBand(&display);
			}

			// Re-enable interrupts
			*(volatile u32 *)GPIO_INT_EN_2 = BTN_ALL;
		}
	}

	// suspend this task. All activities are in interrupts.
	vTaskSuspend(NULL);
}

void display_task (void *arg)
{
	display_init(&display);

	char buffer[NUM_BANDS+4];
	while(1)
	{
		display_getBands(&display, buffer);
		printf("%s", buffer);
		vTaskDelay(1);
	}
}

/** main loop of audio player does not terminate
 *@param pThis  pointer to own object 
 *
 *@return 0 success, non-zero otherwise
 **/
void audioPlayer_task (void *pArg) {
    
	int                      status = FAIL;
	audioPlayer_t *pThis = (audioPlayer_t *)  pArg;

	/* setup gpio */
	gpio_init();
	gpio_setupInts(pThis);

	/* startup sub components */
    /* Start the audio RX module */
    status = audioRx_start(&pThis->rx);
    if ( 1 != status) {
    	/* how to indicate startup failure ?*/
        return;
    }

    /* Start the audio TX module */
    status = audioTx_start(&pThis->tx);
	if ( 1 != status) {
    	/* how to indicate startup failure ?*/
        return;
    }

	/* main loop */
	while(1)
	{
		/** get audio chunk */
		//printf("test\n");
		status = audioRx_get(&pThis->rx, &pThis->chunk);

		/** If we have chunks that can be played then we provide them
		 * to the audio TX */
		if ( 1 == status ) {
		  /** play audio chunk through speakers */
		  audioTx_put(&pThis->tx, pThis->chunk);
		}
	}
}

static int gpio_setupInts(audioPlayer_t *pThis) {
	// pointer to driver structure
	XScuGic *pGIC;
	// get pointer to GIC (already initialized at OS startup
	pGIC = prvGetInterruptControllerInstance();
	// connect own interrupt handler to GIC handler
	XScuGic_Connect(pGIC, GPIO_INTERRUPT_ID,
	(Xil_ExceptionHandler) gpio_intrHandler,(void *) pThis);
	// Enable interrupt at GIC
	XScuGic_Enable(pGIC, GPIO_INTERRUPT_ID);
	/* Enable IRQ at core (should be enabled anyway)*/
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);

	/* Enable IRQ in processor core  */

	return XST_SUCCESS;
}

static void gpio_intrHandler(void *pRef)
{
	// read interrupt status
	u32 int_assert = (*(volatile u32 *)GPIO_INT_STAT_2) & ~(*(volatile u32 *)GPIO_INT_MASK_2);

	// clear interrupts
	(*(volatile u32 *)GPIO_INT_STAT_2) = int_assert;

	// send interrupt status to queue
	xQueueSendFromISR( gpio_queue,( void * ) &int_assert, NULL);

	// temporarily disable interrupts
	*(volatile u32 *)GPIO_INT_DIS_2 = 0xFFFFFFFF;

	/*
	unsigned int n;
	for ( n=0; n < 5000000; n++ )
	{
		asm("nop;");
	}
	*/
}

void gpio_init(void) {

    /* OutEnable for LEDs which is top 8 bits need to be set to 1 */
	*(volatile u32 *)GPIO_DIRM_2 = 0x00000000;
    *(volatile u32 *)GPIO_OEN_2 =  0x00000000;

    /* disable interrupts before configuring new ints */
    *(volatile u32 *)GPIO_INT_DIS_2 = 0xFFFFFFFF;

    *(volatile u32 *)GPIO_INT_TYPE_2 = BTN_ALL;
    *(volatile u32 *)GPIO_INT_POLARITY_2 = BTN_ALL;
    *(volatile u32 *)GPIO_INT_ANY_2 = BTN_ALL; // or 0x00000000

    /* enable input bits */
    *(volatile u32 *)GPIO_INT_EN_2 = BTN_ALL;
}
