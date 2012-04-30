// safety againts double-include
#ifndef pca9535_h
#define pca9535_h
#include <Arduino.h> 
#include <i2c_device.h>

class pca9535 : public i2c_device
{
    public:
        pca9535(); // We need this so we can set default address

        // Initialize the object and chip        
        void begin(byte board_num, boolean wire_begin);
        // A funky way to handle optional arguments
        void begin(byte board_num);
        void begin();

        boolean set_port_mode(byte port, byte mode); // Sets the input/ouput bits on portA/portB
        boolean set_port_invert(byte port, byte mode); // Sets the input inversion bits on portA/portB
        boolean sync(); // Shortcut to write_data() and read_data()
        boolean read_data(); // Updates the local data from device 
        boolean write_data(); // Updates the local data to device
        boolean port_read_modify_write(byte port, byte mask, byte value); // This bypasses the read_data method to do a direct RMW
        boolean pinInvert(byte pin, boolean invert); // Arduino style pin input inversion setter
        boolean pinMode(byte pin, byte mode); // Arduino style pin mode setter
        boolean digitalWrite(byte pin, byte state); // Arduino style pin write
        boolean digitalRead(byte pin); // Arduino style pin read

        byte data[2]; // registers 0 and 1
};

#ifdef PCA9535_ENABLE_BOUNCE
#include "pca9535bounce.h"
#endif



#endif
// *********** END OF CODE **********
