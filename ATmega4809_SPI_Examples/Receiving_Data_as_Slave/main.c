/**
* \file main.c
*
* \brief Main source file.
*
(c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*
*/

#include <avr/io.h>
#include <avr/interrupt.h>

void SPI0_init(void);

volatile uint8_t receiveData = 0;
volatile uint8_t writeData = 0;

void SPI0_init(void)
{
    PORTA.DIR &= ~PIN4_bm; /* Set MOSI pin direction to input */
    PORTA.DIR |= PIN5_bm; /* Set MISO pin direction to output */
    PORTA.DIR &= ~PIN6_bm; /* Set SCK pin direction to input */
    PORTA.DIR &= ~PIN7_bm; /* Set SS pin direction to input */

    SPI0.CTRLA = SPI_DORD_bm        /* LSB is transmitted first */
               | SPI_ENABLE_bm      /* Enable module */
               & (~SPI_MASTER_bm);     /* SPI module in Slave mode */

    SPI0.INTCTRL = SPI_IE_bm; /* SPI Interrupt enable */
}

ISR(SPI0_INT_vect)
{
    receiveData = SPI0.DATA;

    SPI0.DATA = writeData;

    SPI0.INTFLAGS = SPI_IF_bm; /* Clear the Interrupt flag by writing 1 */
}

int main(void)
{    
    SPI0_init();

    sei(); /* Enable Global Interrupts */

    while (1)
    {
        ;
    }
}
