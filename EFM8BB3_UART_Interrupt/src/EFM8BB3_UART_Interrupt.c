//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB3_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]
// [Generated Includes]$
unsigned char received_byte;
//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main(void) {
	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();

	IE_EA = 1;

	SCON1_TI = 1;
	while (1);
	{
// $[Generated Run-time code]
//		SFRPAGE = 0x20;
//		if(SCON1_RI == 1)
//		{
//			received_byte = SBUF1;
//			SBUF1 = received_byte;
//			while(SCON1_TI != 1);
//			SCON1_TI = 0;
//		}

// [Generated Run-time code]$
	}
}
