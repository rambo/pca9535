// safety againts double-include
#ifndef pca9535_h
#define pca9535_h
#include <Arduino.h> 
#include <i2c_device.h>

// Stub extension for now
class pca9535 : public i2c_device
{
    public:
        pca9535(); // We need this so we can set default address
        boolean set_port_mode(byte port, byte mode); // Sets the input/ouput bits on portA/portB
        boolean set_port_invert(byte port, byte mode); // Sets the input inversion bits on portA/portB
        boolean sync(); // Shortcut to read_input() and write_output()
        boolean read_input(); // Updates the local input data from device 
        boolean write_output(); // Updates the local output data to device

        // TODO: We might be able to live with only one array for both i/o but then the sync method is useless (or at least it needs to write first and read then)
        byte input[2]; // registers 0 and 1
        byte output[2]; // registers 2 and 3
};



#endif
// *********** END OF CODE **********
