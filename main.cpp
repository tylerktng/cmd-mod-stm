#include "BufferedSerial.h"
#include "Callback.h"
#include "DigitalOut.h"
#include "PinNameAliases.h"
#include "Semaphore.h"
#include "ThisThread.h"
#include "Thread.h"
#include "mbed.h"
#include "mbed_debug.h"
#include <cstdio>
#include <vector>

// #define MBED_CONF_PLATFORM_ERROR_FILENAME_CAPTURE_ENABLED

// Maximum number of element the application buffer can contain
#define MAXIMUM_BUFFER_SIZE 10

static DigitalOut led(LED3);

//OUT PORT
static BufferedSerial outPort(PB_6, NC, 9600);
//IN PORT
static BufferedSerial inPort(NC, PC_7, 9600);
//USB
static BufferedSerial usbPort(USBTX, USBRX, 9600);

void broadcast() {
    int count = 1;
    while(true) {
        outPort.write(&count, sizeof(count));
        count++;
        ThisThread::sleep_for(std::chrono::seconds(count + 2));
    }
}

void listen() {
    while(true) {
        int count = 0;
        inPort.read(&count, sizeof(count));
        usbPort.write("Read!", 6);
        for(int i = 0; i < count; ++i) {
            led = !led;
            ThisThread::sleep_for(500ms);
            led = !led;
            ThisThread::sleep_for(500ms);
        }
    }
}


int main() {
    inPort.set_format(
        8,
        SerialBase::None,
        1
    );
    outPort.set_format(
        8,
        SerialBase::None,
        1
    );
    usbPort.set_format(
        8,
        SerialBase::None,
        1
    );
    Thread writeThread, readThread;

    writeThread.start(callback(broadcast));
    readThread.start(callback(listen));
    while(true){
        
    }
}