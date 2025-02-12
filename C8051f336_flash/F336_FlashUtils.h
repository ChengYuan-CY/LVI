//-----------------------------------------------------------------------------
// F540_FlashUtils.h
//-----------------------------------------------------------------------------
// Copyright 2008 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program contains several useful utilities for writing and updating
// FLASH memory.
//
// Target:         C8051F54x
// Tool chain:     Keil C51 8.00
// Command Line:   None
//
//
// Release 1.1 / 10 MAR 2010 (GP)
//    -Tested with Raisonance
//
// Release 1.0 / 05 NOV 2008 (GP)
//    -Initial Revision
//

//-----------------------------------------------------------------------------
// Open Header #define
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Exported Function Prototypes
//-----------------------------------------------------------------------------

// FLASH read/write/erase routines
void FLASH_Read (U8 *dest, U16 src, U16 numbytes);

// FLASH test routines
void FLASH_Fill (U16 addr, U16 length, U8 fill);

void FLASH_ByteWrite (U16 addr, U8 byte);
U8 FLASH_ByteRead (U16 addr);

//-----------------------------------------------------------------------------
// Close Header #define
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------