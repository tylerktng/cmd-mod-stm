#ifndef THREADED_UART
#define THREADED_UART

#include "ConditionVariable.h"
#include "Mutex.h"
#include "PinNames.h"
#include "Semaphore.h"
#include "SerialBase.h"
#include "mbed.h"
#include "BufferedSerial.h"
#include "mbed_retarget.h"
#include <chrono>
#include <utility>

namespace RPL {

/*
 * ThreadedUart Transmitter
 * This class provides UART functionality for sending UART signals and is
 * run by a separate thread.
 */
class ThreadedUartTX {
private:
    //Serial for I/O operations
    BufferedSerial serial;
    //Worker Thread
    Thread thread;

    //Lock for controlling the sleep
    Mutex workLock;

    //Lock for the task queue
    Mutex taskLock;

    //Condition for task
    ConditionVariable taskWait;

    //Condition for worker thread to wake up from sleep
    ConditionVariable workWait;

    volatile bool running = true;

    //Local buffer for writing and length.
    //NOTE: do not modify these without locking
    //on taskWait.
    void *localBuf;
    volatile size_t write_len;

    //Store the results in this variable.   
    volatile ssize_t writtenBits;

    //Worker thread runs entirely in this method.
    void run();
    
    //
    void signal();
    
public:

    /*
     * Constructs a ThreadedUart transmitter instance.
     */
    explicit ThreadedUartTX(const PinName tx, const int baudRate);

    /*
     * Clean up thread and buffers.
     */
    ~ThreadedUartTX();

    /*
     * Starts the transmitter. Immediately puts the thread to sleep.
     */
    Thread *start();

    /*
     * Writes the bits.
     */
    ssize_t write(void *buf, const size_t len);

};

/*
 * ThreadedUart Receiver
 * This class provides UART functionality for sending UART signals and is
 * run by a separate thread.
 */
class ThreadedUartRX {
private:
    //Serial for I/O operations
    BufferedSerial serial;
    //Worker Thread
    Thread thread;
    //Condition for worker thread to wake up
    ConditionVariable cv;
    //Local buffer for writing.
    volatile void *localBuf;
    //Lock for controlling cv
    Mutex lock;

    void run();
    
public:

    /*
     * Constructs a ThreadedUart transmitter instance.
     */
    explicit ThreadedUartRX(const PinName tx, const int baudRate);

    /*
     * Starts the receiver. Immediately puts the thread to sleep.
     */
    Thread *start();

    /*
     * Reads the bits.
     */
    ssize_t read(void *buf, const size_t len);

};

class ThreadedUartTXRX {
private:
    
    
public:
};

}

#endif