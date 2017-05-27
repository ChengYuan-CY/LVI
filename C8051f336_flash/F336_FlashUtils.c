//-----------------------------------------------------------------------------
// F336_FlashUtils.c
//-----------------------------------------------------------------------------
// Copyright 2008 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program contains several useful utilities for writing and updating
// FLASH memory.
//
// Target:         C8051F336, 'F337, 'F338, 'F339
// Tool chain:     Keil C51 8.00
// Command Line:   None
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <compiler_defs.h>
#include <c8051F336_defs.h>
#include <F336_FlashUtils.h>




//-----------------------------------------------------------------------------
// FLASH_ByteWrite
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters:
//   1) U16 addr - Flash address to write
//         Range - 0x0000 to 0x3DFF (15.5k user accessible flash)
//   2) U8 byte  - Byte to write
//         Range - 0x00 to 0xFF
//
// This routine writes "byte" at flash address "addr"; Adapted from AN201.
//
//-----------------------------------------------------------------------------
void FLASH_ByteWrite (U16 addr, U8 byte)
{
   U8 EA_Save = IE;                    // Preserve EA
   SEGMENT_VARIABLE_SEGMENT_POINTER (pwrite, U8, xdata, data); 
   //unsigned char xdata * data pwrite;// FLASH write pointer

   EA = 0;                             // Disable interrupts

   VDM0CN = 0x80;                      // Enable VDD monitor


   RSTSRC = 0x02;                      // Enable VDD monitor as a reset source

   pwrite = (char xdata *) addr;

   FLKEY  = 0xA5;                      // Key Sequence 1
   FLKEY  = 0xF1;                      // Key Sequence 2
   PSCTL |= 0x01;                      // PSWE = 1


   VDM0CN = 0x80;                      // Enable VDD monitor


   RSTSRC = 0x02;                      // Enable VDD monitor as a reset source

   *pwrite = byte;                     // Write the byte

   PSCTL &= ~0x01;                     // PSWE = 0

   if ((EA_Save & 0x80) != 0)          // Restore EA
      EA = 1;
}



U8 FLASH_ByteRead (U16 addr)
{
   bit EA_SAVE = EA;                   // Preserve EA
   U8 code * data pread;               // FLASH read pointer
   U8 byte;

   EA = 0;                             // Disable interrupts

   pread = (U8 code *) addr;

   byte = *pread;                      // Read the byte

   EA = EA_SAVE;                       // Restore interrupts

   return byte;
}


//-----------------------------------------------------------------------------
// FLASH_Read
//-----------------------------------------------------------------------------
//
// Return Value :
//   1) U8 *dest - pointer to destination bytes
// Parameters   :
//   1) U8 *dest - pointer to destination bytes
//   2) FLADDR src - address of source bytes in Flash
//                    valid range is 0x0000 to 0x3BFF for 16K Flash devices
//                    valid range is 0x0000 to 0x1FFF for  8K Flash devices
//   3) U16 numbytes - the number of bytes to read
//                              valid range is range of integer
//
// This routine copies <numbytes> from the linear FLASH address <src> to
// <dest>. 
// <dest> + <numbytes> must be less than 0xFBFF/0x7FFF
//
//-----------------------------------------------------------------------------

void FLASH_Read (U8 *dest, U16 src, U16 numbytes)
{
   U16 i;

   for (i = 0; i < numbytes; i++) {
      *dest++ = FLASH_ByteRead (src+i);
   }
   //return dest;
}

//-----------------------------------------------------------------------------
// FLASH_Fill
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) FLADDR addr - starting address of bytes to fill in Flash
//                    valid range is 0x0000 to 0x3BFF for 16K Flash devices
//                    valid range is 0x0000 to 0x1FFF for  8K Flash devices
//   2) ULONG length - number of bytes to fill
//                     range is total Flash size
//   3) U8 fill - the character used the Flash should be filled with
//
// This routine fills the FLASH beginning at <addr> with <length> bytes.
// The target bytes must be erased before writing to them.
// <addr> + <length> must be less than 0xFBFF/0x7FFF.
//
//-----------------------------------------------------------------------------

void FLASH_Fill (U16 addr, U16 length, U8 fill)
{
   U16 i;

   for (i = 0; i < length; i++) {
      FLASH_ByteWrite (addr+i, fill);
   }
}