// Get this from https://github.com/rambo/I2C
#include <I2C.h> // For some weird reason including this in the relevant .h file does not work
#include <i2c_device.h> // For some weird reason including this in the relevant .h file does not work
#include <pca9535.h>
// Get this from https://github.com/rambo/PinChangeInt_userData (or use the normal PinChangeInt from http://www.arduino.cc/playground/Main/PinChangeInt)
#include <PinChangeInt_userData.h>
#define I2C_DEVICE_DEBUG
// Container for the device
pca9535 expander;


#define INT_PIN 7

// The variable we check in mainloop (doing I2C operations inside the interrupt will not work)
volatile boolean read_expander;
/**
 * With the standard variant
void expander_int_received()
 */
void expander_int_received(void* userData)
{
    Serial.println("expander_int_received");
    read_expander = true;
}

void setup()
{
    Serial.begin(115200);
    /*
    Serial.print("INPUT=B");
    Serial.println(INPUT, BIN);
    Serial.print("OUTPUT=B");
    Serial.println(OUTPUT, BIN);
    Serial.print("(byte)_BV(3)=B");
    Serial.println((byte)_BV(3), BIN);
    Serial.print("(byte)~_BV(3)=B");
    Serial.println((byte)~_BV(3), BIN);
    */

    // Initialize I2C library manually
    I2c.begin();
    I2c.timeOut(500);
    I2c.pullup(true);

    // Scan the bus
    I2c.scan();

    Serial.println("=== Dump ===");
    expander.dump_registers(0x0, 0x07);
    Serial.println("=== Done ===");


    // Use INT_PIN as the interrup pin, set it as input and enable the pull-up (since the int-signal is open-collector to ground)
    pinMode(INT_PIN, INPUT);
    digitalWrite(INT_PIN, HIGH);
    /**
     * With the _userdata variant of the PinChangeInt lib
     */
    byte foodata;
    PCintPort::attachInterrupt(INT_PIN, expander_int_received, FALLING, &foodata);
    /**
     * With the standard variant
    PCintPort.attachInterrupt(INT_PIN, expander_int_received, FALLING);
     */
     

    Serial.println("Booted");
}


void loop()
{
    if (read_expander)
    {
        expander.read_data();
        Serial.print("expander.data[0]=0x");
        Serial.println(expander.data[0], HEX);
        Serial.print("expander.data[1]=0x");
        Serial.println(expander.data[1], HEX);
        read_expander = false;
        Serial.println("=== Dump ===");
        expander.dump_registers(0x0, 0x07);
        Serial.println("=== Done ===");
    }
}



