#ifndef USB_INTERFACE
#define USB_INTERFACE
#include <cstdint>
#include "mbed.h"
#include "cmd/Command.h"

/*******************************************************************************
 * USBInterface
 * This file contains declarations for functions to read/write from the USB port.
 * Fetching data is done in threaded manner, but there are two options.
 * 1. Preemptive scheduling: This is supported by MBedOS. There's a decent
 *    amount of complexity involved. Threads can wait on data to be ready while
 *    the USB serial buffer is being filled, and the OS will context switch
 *    automatically. However, we'll be responsible for adding/verifying that
 *    sleeps properly cause threads to wait for their turn.
 * 2. Non-preemptive scheduling: This is not supported, but we can make it work
 *    ourselves. If usbPort is not ready with data, we'll do other things
 *    instead. For instance, sending GPS data to the FCB, or processing heart
 *    beats. Threads are "simulated" in this sense similarly to the preemptive
 *    scheduling method, but execution is managed manually.
 *
 * Design goal: Keep it simple until otherwise proven.
 * - Using a preemptive scheduling scheme, we will need to manage how to force 
 *   the thread to wait for data to become available. 
 * - Using a non-preemptive scheduling scheme, we will simply return from the
 *   read method if data is not available. However, the data
 * 
 * There are two types of data that will be read in from the serial port.
 * 1. GPS Data: This is read into the GPS buffer.
 * 2. Commands: These are read into the command buffer and must be processed at 
 *    a much higher priority than the GPS data (in fact immediately after we
 *    receive them). This could be achieved using ISR/interrupts.
 *
 * Author: Tyler Ng (2022)
 ******************************************************************************/

#define GPS_BUFFER_SIZE 1024
#define CMD_BUFFER_SIZE 64

extern BufferedSerial usbPort;



// GPS data stored here?
extern uint8_t gpsBuf[GPS_BUFFER_SIZE];

//Command data stored here?
extern uint8_t cmddBuf[CMD_BUFFER_SIZE];

/*
 * Returns whether there is raw GPS data ready for parsing.
 */
bool gpsReady();

/*
 * Returns whether there is raw command data ready for parsing.
 */
bool cmdReady();

/*
 * Reads the next data or command segment from the usb listener.
 * Using a preemptive scheduler, this is done on its own thread, and there is
 * the option to block until data is ready.
 */
void readData();

/*
 * Writes data to the serial buffer to be sent over USB at a later time. There
 * is no guarantee on when the data is actually sent (yet?).
 */
void writeData();


#endif