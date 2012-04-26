#include "pca9535.h"

// Constructor
pca9535::pca9535()
{
    device_address = 0x27; // Default to the address on the breakout board with no address pins pulled down (the board has pull-ups for them)
}
