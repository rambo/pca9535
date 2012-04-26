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

};



#endif
// *********** END OF CODE **********
