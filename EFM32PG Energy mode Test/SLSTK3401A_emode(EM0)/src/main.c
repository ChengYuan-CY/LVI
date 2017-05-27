/**************************************************************************//**
 * @file main.c
 * @brief Demo for energy mode current consumption testing.
 * @version 5.1.3
 ******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include "lcd_setup.h"
#include "emodes.h"
#include "coremark/core_main.h"
#include "bsp.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_assert.h"
#include <stdint.h>


typedef enum
{
  T_EM0_HFXO_40MHZ_WHILE_DCDC_DCM,     /**< EM0 with HFXO at 38.4MHz with DCDC in Low Noise DCM mode (while loop)        */
  T_EM0_HFXO_20MHZ_WHILE_DCDC_DCM,     /**< EM0 with HFXO at 19.2MHz with DCDC in Low Noise DCM mode (while loop)        */
  T_EM0_HFXO_10MHZ_WHILE_DCDC_DCM,     /**< EM0 with HFXO at 9.6MHz with DCDC in Low Noise DCM mode (while loop)        */
  T_EM0_HFRCO_38MHZ_WHILE_DCDC_DCM,    /**< EM0 with HFRCO at 38MHz with DCDC in Low Noise DCM mode (while loop)         */
  T_EM0_HFRCO_26MHZ_WHILE_DCDC_DCM,    /**< EM0 with HFRCO at 26MHz with DCDC in Low Noise DCM mode (while loop)         */
  T_EM0_HFRCO_13MHZ_WHILE_DCDC_DCM,    /**< EM0 with HFRCO at 13MHz with DCDC in Low Noise DCM mode (while loop)         */
  T_EM0_HFRCO_7MHZ_WHILE_DCDC_DCM,    /**< EM0 with HFRCO at 7MHz with DCDC in Low Noise DCM mode (while loop)         */

} T_Energy_Mode_TypeDef;



/**************************************************************************//**
 * @brief  Main function
 *
 * @note Hard reset must occur to enter energy mode correctly.
 *****************************************************************************/
int main(void)
{
  /* Use default settings for DCDC, EM23, and HFXO */
  EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_STK_DEFAULT;
  EMU_EM23Init_TypeDef em23Init = EMU_EM23INIT_DEFAULT;
  CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;

  uint32_t frequency = 0;
  uint32_t clockPresc = 0;

#if defined(ADVANCED_LOWPOWER_FEATURES)
  EMU_EM01Init_TypeDef em01Init = EMU_EM01INIT_DEFAULT;
  EMU_EM4Init_TypeDef em4Init = EMU_EM4INIT_DEFAULT;

  /* Enable voltage downscaling in EM0 to 4. */
  em01Init.vScaleEM01LowPowerVoltageEnable = true;
  em23Init.vScaleEM23Voltage = emuVScaleEM23_LowPower;
  em4Init.vScaleEM4HVoltage = emuVScaleEM4H_LowPower;
#endif

  /* Chip errata */
  CHIP_Init();

  /* Unlatch EM4 pin retention */
  EMU_UnlatchPinRetention();

  /* Initialize DCDC. Always start in low-noise mode. */
  dcdcInit.dcdcMode = emuDcdcMode_LowNoise;
  EMU_DCDCInit(&dcdcInit);

  /* Initialize EM23 and HFXO with default parameters */
//  EMU_EM23Init(&em23Init);
  CMU_HFXOInit(&hfxoInit);


  /* Sets "mode" variable to user desired energy mode enum,
   * and reconfigures chip to initial state.
   * See files for "lcd_setup" for more information. */
  T_Energy_Mode_TypeDef mode = 0;

  /* Start the selected energy mode setup (See Data Sheet Table 4.5-4.7).
   * See files for "emodes" for more information.
   * Copy and paste DCDC configuration and emode function definition to replicate setup.*/

  switch(mode)
  {
	case T_EM0_HFXO_40MHZ_WHILE_DCDC_DCM:
		em_EM0_Hfxo();
		frequency = CMU_ClockFreqGet(cmuClock_HF);
		while(1);
	case T_EM0_HFXO_20MHZ_WHILE_DCDC_DCM:
		em_EM0_Hfxo();
		CMU_ClockPrescSet(cmuClock_HF, 1);
		frequency = CMU_ClockFreqGet(cmuClock_CORE);
		while(1);
	case T_EM0_HFXO_10MHZ_WHILE_DCDC_DCM:
		em_EM0_Hfxo();
//		frequency = CMU_ClockFreqGet(cmuClock_HF);
//		frequency = CMU_ClockFreqGet(cmuClock_CORE);
//
//		clockPresc = CMU_ClockPrescGet(cmuClock_HF);
//		clockPresc = CMU_ClockPrescGet(cmuClock_CORE);
		CMU_ClockPrescSet(cmuClock_HF, 3);
//		CMU_ClockPrescSet(cmuClock_CORE, 1);
//		clockPresc = CMU_ClockPrescGet(cmuClock_HF);
//		clockPresc = CMU_ClockPrescGet(cmuClock_CORE);
//
//		frequency = CMU_ClockFreqGet(cmuClock_HF);
		frequency = CMU_ClockFreqGet(cmuClock_CORE);
		while(1);

    case T_EM0_HFRCO_38MHZ_WHILE_DCDC_DCM:
		em_EM0_Hfrco(cmuHFRCOFreq_38M0Hz);
//		frequency = CMU_ClockFreqGet(cmuClock_HF);
//		frequency = CMU_ClockFreqGet(cmuClock_CORE);
		while(1);
    case T_EM0_HFRCO_26MHZ_WHILE_DCDC_DCM:
		em_EM0_Hfrco(cmuHFRCOFreq_26M0Hz);
//		frequency = CMU_ClockFreqGet(cmuClock_HF);
//		frequency = CMU_ClockFreqGet(cmuClock_CORE);
		while(1);
    case T_EM0_HFRCO_13MHZ_WHILE_DCDC_DCM:
		em_EM0_Hfrco(cmuHFRCOFreq_13M0Hz);
//		frequency = CMU_ClockFreqGet(cmuClock_HF);
//		frequency = CMU_ClockFreqGet(cmuClock_CORE);
		while(1);
    case T_EM0_HFRCO_7MHZ_WHILE_DCDC_DCM:
		em_EM0_Hfrco(cmuHFRCOFreq_7M0Hz);
//		frequency = CMU_ClockFreqGet(cmuClock_HF);
//		frequency = CMU_ClockFreqGet(cmuClock_CORE);
		while(1);

    default:
      EFM_ASSERT(false);
      break;

  }

  /* Should not be reached. */
  EFM_ASSERT(false);
}
