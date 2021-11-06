#include "threaded_uart.h"
#include "Callback.h"
#include "ConditionVariable.h"
#include "mbed_retarget.h"
#include <chrono>
#include <functional>

namespace RPL {

ThreadedUartTX::ThreadedUartTX(const PinName tx, const int baudRate) :
    serial(tx, NC, baudRate),
    workWait(workLock),
    taskWait(taskLock)
{
    serial.set_format(8, SerialBase::None, 1);
    serial.set_blocking(true);
    localBuf = NULL;
}

ThreadedUartTX::~ThreadedUartTX() {
    thread.terminate(); //If there's a problem need to add ISR context check.
}

void ThreadedUartTX::run() {
    while(running) {
        //Wait for work to come in
        workLock.lock();
        workWait.wait();
        if(!running) {
            break;
        }
        //If signalled to go
        serial.write(localBuf, write_len);
        taskLock.unlock();
        workLock.unlock();
    }
}
/*
 * Starts the thread listener/writer.
 */
Thread *ThreadedUartTX::start() {
    thread.start(callback(this, &ThreadedUartTX::run));
    return &thread;
}

ssize_t ThreadedUartTX::write(void *buf, const size_t len) {
    taskLock.lock();
    localBuf = buf;
    write_len = len;
    workWait.notify_one(); //notify worker thread to start
    workWait.   (); //wait for thread to finish writing.
    ssize_t result = writtenBits; //get the results
    taskLock.unlock();
    return result;
}

}