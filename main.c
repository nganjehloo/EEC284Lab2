//*****************************************************************************
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions -in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

//*****************************************************************************
//
// Application Name     - SPI Demo
// Application Overview - The demo application focuses on showing the required 
//                        initialization sequence to enable the CC3200 SPI 
//                        module in full duplex 4-wire master and slave mode(s).
// Application Details  -
// http://processors.wiki.ti.com/index.php/CC32xx_SPI_Demo
// or
// docs\examples\CC32xx_SPI_Demo.pdf
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup SPI_Demo
//! @{
//
//*****************************************************************************

// Standard includes
#include <string.h>

// Driverlib includes
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_ints.h"
#include "spi.h"
#include "rom.h"
#include "rom_map.h"
#include "utils.h"
#include "prcm.h"
#include "uart.h"
#include "interrupt.h"
#include "time.h"
#include "timer.h"

// Common interface includes
#include "uart_if.h"
#include "timer_if.h"
#include "pinmux.h"
#include "gpio.h"
#include "gpio_if.h"

#include "kiss_fftr.h"
#include <math.h>

#define APPLICATION_VERSION     "1.1.1"
//*****************************************************************************
//
// Application Master/Slave mode selector macro
//
// MASTER_MODE = 1 : Application in master mode
// MASTER_MODE = 0 : Application in slave mode
//
//*****************************************************************************

#define SPI_IF_BIT_RATE  100000
#define N 1024
#define Ts 10
//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
static unsigned char g_ucRxBuff2[2];
static kiss_fft_scalar buf[N];
static unsigned short idxX = 0;
unsigned short rxBuff;
static unsigned char doneColl = 0;

#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif
//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************



//*****************************************************************************
//
//! SPI Slave Interrupt handler
//!
//! This function is invoked when SPI slave has its receive register full or
//! transmit register empty.
//!
//! \return None.
//
//*****************************************************************************

void
TimerIntHandler(void)
{
    //
    // Clear the timer interrupt.
    //
    Timer_IF_InterruptClear(TIMERA0_BASE);

    MAP_SPITransfer(GSPI_BASE,0,g_ucRxBuff2,2,
                      SPI_CS_ENABLE|SPI_CS_DISABLE);

    rxBuff = (g_ucRxBuff2[0] << 8) | (g_ucRxBuff2[1]);
    rxBuff = rxBuff << 3;
    rxBuff = rxBuff >> 6;
    //Report("\n\r Measured: %i, Idx: %i", rxBuff, idxX);
    Report("\n\r %i", rxBuff);
    buf[idxX] = rxBuff;
    idxX++;
    if(idxX >= N){
        Report("\n\r *****Done Collecting*****");
        Timer_IF_DeInit(TIMERA0_BASE, TIMER_A);
        doneColl = 1;
    }

}

void discreteToFreqDomain(kiss_fft_cpx *bout, int n){
    float NC = n/2.0 + 1;
    while (n-- > 0) {
        bout->r /= NC;
        bout->i /= NC;
        bout++;
    }
}
void magnitude(kiss_fft_cpx *bout, int n){
    while (n-- > 0) {
        bout->r = sqrt(bout->r * bout->r + bout->i * bout->i);
        bout->i = 0;
        bout++;
    }
}


int getMaxIdx(kiss_fft_cpx *bout, int n, int start_idx) {
    int idx = 0;
    float max = 0;
    int i;
    for (i = start_idx; i < n/2; i++) {
        if ((bout[i].r - max) > 0.0001) {
            max = bout[i].r;
            idx = i;
        }
    }
    return idx;
}


float getMaxFreq(kiss_fft_cpx *bout, int n, float start_f, float sample_f){
    int start_idx = start_f * n / sample_f;
    return getMaxIdx(bout, n, start_idx)*sample_f/n;
}

void computeHeartRate(){
    Report("\n\r *****Computing FFT*****");
        //set up buffers
        kiss_fft_cpx bufout[N];
        kiss_fftr_cfg cfg;
        //allocate scratch space for fft
        if((cfg = kiss_fftr_alloc(N, 0, 0, 0))){
            //compute fft
            kiss_fftr(cfg, (kiss_fft_scalar*)buf, (kiss_fft_cpx*)bufout);
            free(cfg);
        }else{
            //lol
            Report("\n\rERROR: OUT OF MEMORY");
            exit(-1);
        }
        //print fft
        int i = 0;
        for (i = 0; i < N; ++i){
            Report("\n\r in[%i] = %+f     "
                   "\n\r out[%i] = %+f , %+f\n\r",
                     i, buf[i],
                     i, bufout[i].r, bufout[i].i);
            //Report("\n\r %f", sqrt((bufout[i].r * bufout[i].r) + (bufout[i].i*bufout[i].i)));
        }
        discreteToFreqDomain(bufout, N);
        magnitude(bufout, N);
        float Fs = 1/((float)Ts/(float)1000);
        Report("\n\r Max Heart Rate: %f",getMaxFreq(bufout, N, 1, Fs)*60);

}
void sequence(unsigned char seq){
    GPIOPinWrite(GPIOA0_BASE, 0x40, (seq << 3)& 0x40); //61
    GPIOPinWrite(GPIOA1_BASE, 0x1, (seq >> 2) & 0x1);  //63
    GPIOPinWrite(GPIOA0_BASE, 0x80, (seq << 6) & 0x80); //62
    GPIOPinWrite(GPIOA0_BASE, 0x20, (seq << 5) & 0x20); //60
}

void runMotor(){
    Message("\n\r *****Running Motor*****");
    int speed = 8000000;
       int numRevo = 2; //Number of revolutions per second required
       speed = (int)(speed/(numRevo*0.3*48));
        while(1){
            sequence(0xa);
            UtilsDelay(speed);
            sequence(0x6);
            UtilsDelay(speed);
            sequence(0x5);
            UtilsDelay(speed);
            sequence(0x9);
            UtilsDelay(speed);
        }

}
//*****************************************************************************
//
//! SPI Master mode main loop
//!
//! This function configures SPI modelue as master and enables the channel for
//! communication
//!
//! \return None.
//
//*****************************************************************************
void SPIInit()
{
    //
    // Reset SPI
    //
    MAP_SPIReset(GSPI_BASE);

    //
    // Configure SPI interface
    //
    MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
                     SPI_IF_BIT_RATE,SPI_MODE_MASTER,SPI_SUB_MODE_0,
                     (SPI_SW_CTRL_CS |
                     SPI_4PIN_MODE |
                     SPI_TURBO_OFF |
                     SPI_CS_ACTIVELOW |
                     SPI_WL_8));

    //
    // Enable SPI for communication
    //
    MAP_SPIEnable(GSPI_BASE);

}

//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void
BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
  //
  // Set vector table base
  //
#if defined(ccs)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}

//****************************************************************************
//
//! Main function for spi demo application
//!
//! \param none
//!
//! \return None.
//
//*****************************************************************************
void main(){
    //
    // Initialize Board configurations
    //
    BoardInit();

    //    // Muxing UART and SPI lines.
    //
    PinMuxConfig();

    //
    // Enable the SPI module clock
    //
    MAP_PRCMPeripheralClkEnable(PRCM_GSPI,PRCM_RUN_MODE_CLK);

    //
    // Initialising the Terminal.
    //
    InitTerm();

    //
    // Clearing the Terminal.
    //
    ClearTerm();

    GPIO_IF_LedConfigure(LED1|LED2|LED3);

    GPIO_IF_LedOff(MCU_ALL_LED_IND);

    Timer_IF_Init(PRCM_TIMERA0, TIMERA0_BASE, TIMER_CFG_PERIODIC, TIMER_A, 0);
    Timer_IF_IntSetup(TIMERA0_BASE, TIMER_A, TimerIntHandler);
    Timer_IF_Start(TIMERA0_BASE, TIMER_A, Ts);
    //
    // Display the Banner
    //

    //
    // Reset the peripheral
    //
    MAP_PRCMPeripheralReset(PRCM_GSPI);

    SPIInit();


    //wait while we collect data
    while(!doneColl)
    {
    }

    //do FFT
   computeHeartRate();

   //spin motor

   runMotor();

}

