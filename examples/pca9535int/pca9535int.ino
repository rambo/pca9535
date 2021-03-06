/**
 * Example sketch demoing the the use of the interrupt on the PCA9535 chip
 *
 * The INT pin is open collector and in case you're not using the board in this repo (which contains pull-up for the pin)
 * you will need to enable the Arduino internal pull-up (or provide external one), this sketch enables the Arduino pull-up as well
 *
 * Make sure you have no floating pins (or there will be interrupts coming in faster than you can handle them), one way is to define all pins
 * as outputs first and then reconfigure to input those that are connected to switches or something.
 */
// Get this from https://github.com/rambo/I2C
#include <I2C.h> // For some weird reason including this in the relevant .h file does not work
#include <i2c_device.h> // For some weird reason including this in the relevant .h file does not work
#include <pca9535.h>
// Get this from https://github.com/rambo/PinChangeInt_userData (or use the normal PinChangeInt from http://www.arduino.cc/playground/Main/PinChangeInt)
#include <PinChangeInt_userData.h>
#define I2C_DEVICE_DEBUG
// Container for the device (the default constructor will take care of the device address when using the board found in this repo)
pca9535 expander;


#define INT_PIN A0

// The variable we check in mainloop (doing I2C operations inside the interrupt will not work)
volatile boolean read_expander;
/**
 * With the standard variant
void expander_int_received()
 */
void expander_int_received(void* userData)
{
    // Enabling this may cause your device to end up in interrupt limbo (as UART uses interrupts too and re-entrant interrupts are dangerous)
    //Serial.println(F("expander_int_received"));
    read_expander = true;
}

void setup()
{
    Serial.begin(115200);
    // Initialize I2C library manually
    I2c.begin();
    I2c.timeOut(500);
    I2c.pullup(true);

    // Scan the bus (do this if you can't find your device address)
    //I2c.scan();
    
    // While strictly not neccessary for the 0th board it's good reminder    
    expander.begin(0x0, false);

    // Set all pins as outputs to avoid floating pins
    expander.set_port_mode(0, 0x0);
    expander.set_port_mode(1, 0x0);
    // And portA bit 7 as input
    expander.pinMode(7, INPUT);

    Serial.println(F("=== Dump ==="));
    expander.dump_registers(0x0, 0x07);
    Serial.println(F("=== Done ==="));


    /**
     * NOTE: remember to configure your outputs before enabling the interrupt handler to be sure not to have floating input pins
     */
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
     

    Serial.println(F("Booted"));
}

unsigned long last_millis;
void loop()
{
    if ((millis() - last_millis) > 1000)
    {
        Serial.println(F("Still alive"));
        last_millis = millis();
    }
    if (read_expander)
    {
        expander.read_data();
        Serial.print(F("expander.data[0]=0x"));
        Serial.println(expander.data[0], HEX);
        Serial.print(F("expander.data[1]=0x"));
        Serial.println(expander.data[1], HEX);
        read_expander = false;
        /*
        Serial.println(F("=== Dump ==="));
        expander.dump_registers(0x0, 0x07);
        Serial.println(F("=== Done ==="));
        */
    }
}



