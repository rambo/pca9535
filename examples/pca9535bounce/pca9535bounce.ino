/**
 * Example sketch demoing the the use of the interrupt on the PCA9535 chip
 *
 * The INT pin is open collector and in case you're not using the board in this repo (which contains pull-up for the pin)
 * you will need to enable the Arduino internal pull-up (or provide external one), this sketch enables the Arduino pull-up as well
 *
 * Make sure you have no floating pins (or there will be interrupts coming in faster than you can handle them), one way is to define all pins
 * as outputs first and then reconfigure to input those that are connected to switches or something.
 */
#define I2C_DEVICE_DEBUG
// Get this from https://github.com/rambo/I2C
#include <I2C.h> // For some weird reason including this in the relevant .h file does not work
#include <i2c_device.h> // For some weird reason including this in the relevant .h file does not work
#define PCA9535_ENABLE_BOUNCE
#define PCA9535_BOUNCE_OPTIMIZEDREADS // Do not use the naive methods that will always read the device, handy when you have multiple pins to debounce, OTOH you must remember to call the read_data() method yourself
#include <pca9535.h>

// Container for the device (the default constructor will take care of the device address when using the board found in this repo)
pca9535 expander;
pca9535bounce bouncer;

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

    Serial.println("=== Dump ===");
    expander.dump_registers(0x0, 0x07);
    Serial.println("=== Done ===");

    bouncer.begin(&expander, 7, 50);


    Serial.println("Booted");
}

unsigned long last_millis;
void loop()
{
    if ((millis() - last_millis) > 1000)
    {
        Serial.println("Still alive");
        last_millis = millis();
    }
#ifdef PCA9535_BOUNCE_OPTIMIZEDREADS
    // Read only once
    expander.read_data();
#endif
    // This needs to be set before each update if it is to be used
    bouncer.rebounce(1000);
    if (bouncer.update())
    {
        Serial.print("Pin state changed to ");
        Serial.println(bouncer.read(), DEC);
    }
}



