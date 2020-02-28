/*
 * Michael S. Walker <mwalk762@mtroyal.ca>
 *         _    _
 *        | |  | |	OUTLAW. 
 *       -| |  | |- 
 *   _    | |- | |
 * -| |   | |  | |- 	
 *  |.|  -| ||/  |
 *  | |-  |  ___/ 
 * -|.|   | | |
 *  |  \_|| |
 *   \____  |
 *    |   | |- 
 *        | |
 *       -| |
 *        |_| Copyleft !(c) 2020 All Rights Unreserved in all Federations, including Alpha Centauris.
 */

#include <stdio.h>
#include <osbind.h>

#include <INPUT.H>
#include <ISR.H>

/* CONTROL REGISTER 6850: RIE | TC2 | TC1 | WS3 | WS2 | WS1 | CDS2 | CDS1 */
volatile uint8_t *const IKBD_control = 0xfffffc00;

/* STATUS REGISTER 6850: IRQ | PE | OVRN | PE | CTS | DCD | TxDRE | RxDRF 						     */
/* bit 7: interupt request: 			set to 1 when pin is activated 							  	 */
/* bit 6: Parity error: 				when parity of received word != parity bit 				 	 */
/* bit 5: overrun error: 				processor did not read previous input reset when rectified   */
/* bit 4: framing error: 				set when no stop bit is observed reset when rectified		 */
/* bit 3: state of clear: 				to send input pin											 */
/* bit 2: state of data carrier: 		detect input pin											 */
/* bit 1: transmitter data register:	is empty when flag = 1										 */
/* bit 0: receive data register: 		is full when flag = 1										 */

volatile const uint8_t *const IKBD_status = 0xfffffc00;
volatile const SCANCODE *const IKBD_RDR = 0xfffffc02;

SCANCODE g_action = 0;
volatile signed int g_mouse_delta_x = 0;
volatile signed int g_mouse_delta_y = 0;

/*-------------------------------------------- CheckInputStatus -----
|  Function CheckInputStatus
|
|  Purpose: Check the status of the console input device. 
|
|  Parameters:
|
|  Returns: -1 if a character is waiting, 0 if none is available
*-------------------------------------------------------------------*/

int CheckInputStatus(void)
{
    return Cconis();
}

/*-------------------------------------------- ReadCharNoEcho -----
|  Function ReadCharNoEcho
|
|  Purpose: Read a character from the console with no echo. 
|
|  Parameters:
|
|  Returns:
*-------------------------------------------------------------------*/

int ReadCharNoEcho(void)
{
    return Cnecin();
}

/*-------------------------------------------- do_IKBD_ISR -----
|  Function do_IKBD_ISR
|
|  Purpose: IKBD Driver. 
|
|  Parameters:
|
|  Returns:
*-------------------------------------------------------------------*/

void do_IKBD_ISR(void)
{
    int temp;
    g_action = g_mouse_delta_x = g_mouse_delta_y = 0;

    ReadScancode();
    if (g_action >= 0xf8)
    {
        temp = g_action;
        ReadScancode();
        g_mouse_delta_x = g_action;
        ReadScancode();
        g_mouse_delta_y = g_action;
        g_action = temp;
    }
}

/*-------------------------------------------- ReadScancode -----
|  Function ReadScancode
|
|  Purpose: Read a ScanCode if RDR_FULL == true
|  
|  Parameters:
|
|  Returns: The scancode
*-------------------------------------------------------------------*/

SCANCODE ReadScancode(void)
{
    while (!RDR_FULL(*IKBD_status)) /* busy wait */
        ;
    g_action = *IKBD_RDR;
}
