#include "BufferedSerial.h"
#include "Callback.h"
#include "DigitalOut.h"
#include "PinNameAliases.h"
#include "mbed.h"

/*






 */



// #define MBED_CONF_PLATFORM_ERROR_FILENAME_CAPTURE_ENABLED

// Maximum number of element the application buffer can contain
#define BUFFER_SIZE 64
#define BAUD_RATE 9600

static DigitalOut led(LED3);

//USB
static BufferedSerial usbPort(USBTX, USBRX, BAUD_RATE);

//Send GPS
static BufferedSerial gps(PB_6, NC, BAUD_RATE);


    

int main() {
    char buf[BUFFER_SIZE];
    while(true) {
        memset(buf, 0, BUFFER_SIZE);
        ssize_t sz = usbPort.read(buf, BUFFER_SIZE);
        if(sz > 0) {
            led = !led;
            // usbPort.write(buf, sz);
        }
    }
}