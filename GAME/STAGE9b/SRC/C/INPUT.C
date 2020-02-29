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
#include <IKBD.H>
#include <ISR.H>
#include <MFP.H>
#include <UTIL.H>

uint8_t g_state = START;

int g_click = OFF;
int g_delta_x = 0;
int g_delta_y = 0;

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
    int sign;
    uint8_t sc = ReadScancode();

    if (sc != 0)
    {
        if (g_state == START && sc >= MOUSE_MOVE_SCAN_CODE) /* mouse */
        {
            if (sc == LEFT_CLICK_SCAN_CODE)
                g_click = ON;
            g_state = DELTA_X_STATE;
        }
        else if (g_state == DELTA_X_STATE)
        {
            g_delta_x += ((char)sc > 0) ? 1 : -1;
            g_state = DELTA_Y_STATE;
        }
        else if (g_state == DELTA_Y_STATE)
        {
            g_delta_y += ((char)sc > 0) ? 2 : -1;
            g_state = START;
        }
        else /* keyboard */
        {
            g_state = START;
            /* key was pressed handle */
        }
    }
    bit_clear_no_shift(*MFP_ISRB, MFP_VR_VECTOR_6);
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
    SCANCODE volatile sc = 0;

    if (RDR_FULL(*IKBD_status))
        sc = *IKBD_RDR;
    return sc;
}

/*-------------------------------------------- IsFull -----
|  Function IsFull
|
|  Purpose: Check if the queue is full
|  
|  Parameters:
|
|  Returns: 1 (true) 0 (false)
*-------------------------------------------------------------------*/

int IsFull(void)
{
}

/*-------------------------------------------- IsEmpty -----
|  Function IsEmpty
|
|  Purpose: Check if the queue is empty
|  
|  Parameters:
|
|  Returns: 1 (true) 0 (false)
*-------------------------------------------------------------------*/

int IsEmpty(void)
{
}

/*-------------------------------------------- AddToQ -----
|  Function AddToQ
|
|  Purpose: Add a new item (code) to the back of the queue
|  
|  Parameters: code the scancode to add 
|
|  Returns: 
*-------------------------------------------------------------------*/

void AddToQ(SCANCODE code)
{
}

/*-------------------------------------------- DeleteFromQ -----
|  Function DeleteFromQ
|
|  Purpose: Remove the front value from the queue
|  
|  Parameters: 
|
|  Returns: 
*-------------------------------------------------------------------*/

void DeleteFromQ(void)
{
}

/*-------------------------------------------- ClearQ -----
|  Function ClearQ
|
|  Purpose: Empty the queue
|  
|  Parameters: 
|
|  Returns: 
*-------------------------------------------------------------------*/

void ClearQ(void)
{
}