#include "pca9535.h"

// Constructor
pca9535::pca9535()
{
    device_address = 0x4F; // Default to the address on the breakout board with no address pins pulled down
}
