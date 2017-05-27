#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_cryotimer.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_rmu.h"

void setupCryo(CRYOTIMER_Presc_TypeDef tPeriod);
void em_EM1_Hfxo(void);
static void disableHFClocks(void);
static void disableLFClocks(void);
void gpioSetup(void);


///*
// * Setup PF6 to read BTN0 and PF[5:4] to drive LED[1:0].
// */
void gpioSetup(void)
{
	// Enable GPIO clock
	CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure PF[5:4] as push pull for LED drive, initially low (LEDs off)
  GPIO_PinModeSet(gpioPortF, 4, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortF, 5, gpioModePushPull, 0);

  // Configure PF6 as an input for button 0 with pull-up and filter enabled
  GPIO_PinModeSet(gpioPortF, 6, gpioModeInputPullFilter, 1);

  /* Enable GPIO_EVEN interrupt */
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);
  GPIO_IntConfig(gpioPortF, 6, false, true, true);
}


/*
 * Note: No need to enable ULFRCO since it is always on and cannot be
 * shut off under software control.
 */
void setupCryo(CRYOTIMER_Presc_TypeDef tPeriod)
{
	CRYOTIMER_IntDisable(CRYOTIMER_IEN_PERIOD);
	CRYOTIMER_Enable(false);

	// Enable CRYOTIMER clock
	CMU_ClockEnable(cmuClock_CRYOTIMER, true);

	// Clear CRYOTIMER_IF PERIOD flag; it will be set upon EM4 wake
	CRYOTIMER_IntClear(CRYOTIMER_IF_PERIOD);

	/*
	* Set CRYOTIMER parameters.  Note that disabling the CRYOTIMER is
	* necessary after EM4 wake in order to reset the counter, otherwise
	* the next delay before wake won't be the full 2K periods.
	*/
	CRYOTIMER_Init_TypeDef init = CRYOTIMER_INIT_DEFAULT;
	init.enable = false;
	init.em4Wakeup = true;
	init.osc = cryotimerOscULFRCO;
	init.presc = cryotimerPresc_1;
	//  init.period = cryotimerPeriod_2k;	// nominally 2 seconds
	init.period = tPeriod;

	CRYOTIMER_Init(&init);

	CRYOTIMER_IntEnable(CRYOTIMER_IEN_PERIOD);
	CRYOTIMER_Enable(true);
}



void CRYOTIMER_IRQHandler(void)
{
	uint32_t interruptMask = CRYOTIMER_IntGet();
	CRYOTIMER_IntClear(interruptMask);

//	GPIO_PinOutToggle(gpioPortF, 4);
//	GPIO_PinOutToggle(gpioPortF, 5);
}

#if 0
/**************************************************************************//**
 * @brief   Disable high frequency clocks
 *****************************************************************************/
static void disableHFClocks(void)
{
  // Disable High Frequency Peripheral Clocks
//  CMU_ClockEnable(cmuClock_HFPER, false);
  CMU_ClockEnable(cmuClock_USART0, false);
  CMU_ClockEnable(cmuClock_USART1, false);
  CMU_ClockEnable(cmuClock_TIMER0, false);
  CMU_ClockEnable(cmuClock_TIMER1, false);
//  CMU_ClockEnable(cmuClock_CRYOTIMER, false);
  CMU_ClockEnable(cmuClock_ACMP0, false);
  CMU_ClockEnable(cmuClock_ACMP1, false);
  CMU_ClockEnable(cmuClock_IDAC0, false);
  CMU_ClockEnable(cmuClock_ADC0, false);
  CMU_ClockEnable(cmuClock_I2C0, false);

  // Disable High Frequency Bus Clocks
  CMU_ClockEnable(cmuClock_CRYPTO, false);
  CMU_ClockEnable(cmuClock_LDMA, false);
  CMU_ClockEnable(cmuClock_GPCRC, false);
//  CMU_ClockEnable(cmuClock_GPIO, false);
  CMU_ClockEnable(cmuClock_HFLE, false);
  CMU_ClockEnable(cmuClock_PRS, false);
}

/**************************************************************************//**
 * @brief   Disable low frequency clocks
 *****************************************************************************/
static void disableLFClocks(void)
{
  // Enable LFXO for Low Frequency Clock Disables
  CMU_OscillatorEnable(cmuOsc_LFXO, true, true);

  // Disable Low Frequency A Peripheral Clocks
  // Note: LFA clock must be sourced before modifying peripheral clock enables
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);
  CMU_ClockEnable(cmuClock_LETIMER0, false);
  CMU_ClockEnable(cmuClock_PCNT0, false);
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_Disabled);

  // Disable Low Frequency B Peripheral Clocks
  // Note: LFB clock must be sourced before modifying peripheral clock enables
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);
  CMU_ClockEnable(cmuClock_LEUART0, false);
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_Disabled);

  // Disable Low Frequency E Peripheral Clocks
  // Note: LFE clock must be sourced before modifying peripheral clock enables
  CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_LFXO);
  CMU_ClockEnable(cmuClock_RTCC, false);
  CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_Disabled);

  // Disable Low Frequency Oscillator
  CMU_OscillatorEnable(cmuOsc_LFXO, false, true);
}

#endif

/***************************************************************************//**
 * @brief
 *   Enter EM1 with HFXO running at 38.4MHz.
 *
 * @details
 *   Parameter:
 *     EM1. Sleep Mode. All peripherals disabled.@n
 *   Condition:
 *     38.4 MHz HFXO, all peripheral clocks disabled.@n
 *
 * @note
 *   To better understand disabling clocks and oscillators for specific modes,
 *   see Reference Manual section EMU-Energy Management Unit and Table 9.2.
 ******************************************************************************/
void em_EM1_Hfxo(void)
{
  // Make sure clocks are disabled.
  // Disable High Frequency Clocks
//  disableHFClocks();

  // Disable Low Frequency Clocks
//  disableLFClocks();

  // Set HFXO for HF clock.
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);

  // Make sure unwanted oscillators are disabled specifically for EM1 and HFXO.
  CMU_OscillatorEnable(cmuOsc_HFRCO, false, true);
  CMU_OscillatorEnable(cmuOsc_LFXO, false, true);
  CMU_OscillatorEnable(cmuOsc_LFRCO, false, true);
  CMU_OscillatorEnable(cmuOsc_AUXHFRCO, false, true);

  // Enter EM1.
  EMU_EnterEM1();
}


int main(void)
{
	/* Use default settings for DCDC, EM23, and HFXO */
	EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;
	CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;

	/* Chip errata */
	CHIP_Init();

	/* Initialize DCDC. Always start in low-noise mode. */
	dcdcInit.dcdcMode = emuDcdcMode_LowNoise;
	EMU_DCDCInit(&dcdcInit);

	CMU_HFXOInit(&hfxoInit);

//	gpioSetup();
//	GPIO_PinOutClear(gpioPortF, 4);
//	GPIO_PinOutClear(gpioPortF, 5);

#if 0	// case 3 test
//	NVIC_EnableIRQ(CRYOTIMER_IRQn);
	setupCryo(cryotimerPeriod_2k);
	EMU_EnterEM3(false);
#endif


#if 1	// case 4 test
//	// Configure EM4 behavior
//	EMU_EM4Init_TypeDef init = EMU_EM4INIT_DEFAULT;
//	init.em4State = emuEM4Hibernate;
//	init.retainUlfrco = true;
//	init.pinRetentionMode = emuPinRetentionEm4Exit;
//	EMU_EM4Init(&init);
	NVIC_EnableIRQ(CRYOTIMER_IRQn);

	while(1)
	{
		NVIC_ClearPendingIRQ(CRYOTIMER_IRQn);
		setupCryo(cryotimerPeriod_2k);
		EMU_EnterEM3(false);

		NVIC_ClearPendingIRQ(CRYOTIMER_IRQn);
		setupCryo(cryotimerPeriod_1);
		em_EM1_Hfxo();
	}
#endif



}

