// Get this from https://github.com/rambo/I2C
#include <I2C.h> // For some weird reason including this in the relevant .h file does not work
#include <i2c_device.h> // For some weird reason including this in the relevant .h file does not work
#include <pca9535.h>
#define I2C_DEVICE_DEBUG
// Container for the device
pca9535 expander;

void setup()
{
    Serial.begin(115200);

    // Initialize I2C library manually
    I2c.begin();
    I2c.timeOut(500);
    I2c.pullup(true);

    // Scan the bus
    I2c.scan();

    Serial.println("Booted");
}

void loop()
{
    // Dump device registers and wait 15sek
    Serial.println("=== Dump ===");
    expander.dump_registers(0x0, 0x07);
    Serial.println("=== Done ===");

    delay(15000);
}
