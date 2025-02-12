//-----------------------------------------------------------------------------
// F338_flash_test.c
//-----------------------------------------------------------------------------
// Copyright (C) 2007 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program lights up the green LED on the C8051F338 target board when
// the capacitive touch sense (contactless) switch (SW3) is touched. 
//
// A relaxation oscillator is implemented using an on-chip analog comparator 
// and external resistors R15 through R19. The high-to-low transitions of the 
// relaxation oscillator are counted by Timer0. The relaxation oscillator 
// frequency depends on the capacitance of the touch sense trace capacitor. 
// The count of Timer0 is periodically checked on every Timer2 overflow. 
// Depending on the count, it can be determined whether SW3 is being touched
// or not. 
//
//
// How To Test:
//
// Setup:
// 1) Download code to the 'F338 target board
// 2) Ensure that pins 1 and 2 are shorted together on the J3 header
// 3) Ensure that pins 1-2, 3-4, 5-6, and 7-8 are shorted on the J11 header
//
// One Time Calibration (stored in non-volatile flash):
// 1) The P1.3 LED will be lit. Place a finger on the touch switch SW3, and 
//    hold it there. Do not remove this finger till step 3.
// 2) Press and hold switch SW2 (P0.7). Release the switch after holding 
//    down for more than a second. 
// 3) The P1.3 LED will continue to be lit. Remove finger from SW3. The LED 
//    should switch off.
//
// Usage:
// 1) Touch SW3. The LED (P1.3) should light up in response.
//
// Target:         C8051F336, 'F337, 'F338, 'F339
// Tool chain:     Generic
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (PKC)
//    -29 AUG 2007
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <compiler_defs.h>             // Compiler-specific macros
#include <C8051F336_defs.h>            // SFR declarations
#include <F336_FlashUtils.h>

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define SYSCLK             24500000UL  // SYSCLK frequency in Hz

#define T2_OVERFLOW_RATE   20          // Timer2 overflow rate in ms

#define SW3_SENSITIVITY    3000        // Higher number means more sensitive
                                       // This value is added to the cal value

#define FLASH_TEST_START_ADDR	0x200
#define FLASH_TEST_LENGTH		0x3B00


SBIT (LED, SFR_P1, 3);                 // LED==1 means ON
SBIT (SW2, SFR_P0, 7);                 // SW1==0 means switch depressed

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
void Init_Device (void);
void PCA_Init (void);
void OSCILLATOR_Init (void);
void PORT_Init (void);
void COMPARATOR0_Init (void);


void FLASH_ByteWrite (U16 addr, U8 byte);
U8 FLASH_ByteRead (U16 addr);
void Parity_Check(U8 arg, U8 *Parity);




//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------

void main (void)
{
   U16 R_add = FLASH_TEST_START_ADDR;
   U32 Test_count = 0;
   U8 R_Data;
   U8 Init_parity = 0;
   Init_Device ();

   LED = 1;                     // Initialize switch to not sensed

   EA = 1;                             // Enable global interrupts

   //start_add = FLASH_TEST_START_ADDR;
   FLASH_Fill(FLASH_TEST_START_ADDR, FLASH_TEST_LENGTH, 0x7A);
   //FLASH_ByteWrite(start_add, 0xAA);
   
   while (1) {

		for(R_add = FLASH_TEST_START_ADDR; R_add<(FLASH_TEST_START_ADDR+FLASH_TEST_LENGTH); R_add++)
		{
			FLASH_Read(&R_Data, R_add, 1);
			Parity_Check(R_Data, &Init_parity);
		}

		Test_count++;
	   if(Init_parity == 1)
	   {
	   		LED = 0;
			while(1);
	   }

   }

}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Init_Device
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function calls all peripheral initialization funtions.
//-----------------------------------------------------------------------------
void Init_Device (void)
{
   PCA_Init ();
   OSCILLATOR_Init ();
   PORT_Init ();
}

//-----------------------------------------------------------------------------
// PCA_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the PCA; disables the watchdog timer.
//-----------------------------------------------------------------------------
void PCA_Init (void)
{
   PCA0MD    &= ~0x40;                // WDTE = 0 (disable watchdog timer)
   PCA0MD    = 0x00;
}

//-----------------------------------------------------------------------------
// OSCILLATOR_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the Internal Oscillator.
//-----------------------------------------------------------------------------
void OSCILLATOR_Init (void)
{
   OSCICN    = 0x83;                   // Sets SYSCLK to 24.5 MHz
}

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Configure the Crossbar and GPIO ports.
// P1.3 - LED (push-pull output)
//
void PORT_Init (void)
{
   P1SKIP   = 0x08;                       // skip the LED pin from crossbar
   P1MDOUT |= 0x08;                       // enable LED as a push-pull output
   XBR0     = 0x00;                       // no digital peripherals selected
   XBR1     = 0x40;                       // Enable crossbar and weak pull-ups
}



void Parity_Check(U8 arg, U8 *Parity)
{
	U8 CK;
	//U8 parity = 0;
	CK = arg;
	while (CK)
	{
	  if(*Parity == 0)
	  	*Parity = 1;
	  else
		*Parity = 0;

	  CK = CK & (CK - 1);
	}
	//return parity;
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------