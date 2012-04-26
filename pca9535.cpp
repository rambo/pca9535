#include "pca9535.h"

// Constructor
pca9535::pca9535()
{
    device_address = 0x27; // Default to the address on the breakout board with no address pins pulled down (the board has pull-ups for them)
}

/**
 * Sets the mode bits for given port (0/1), a low bit means output, default is all inputs (0xff)
 */
boolean pca9535::set_port_mode(byte port, byte mode)
{
    return this->write(0x6 + port, mode);
}

/**
 * Sets the invert bits for given port (0/1), a high bit means inverted input, default is all normal (0x0)
 */
boolean pca9535::set_port_invert(byte port, byte mode)
{
    return this->write(0x4 + port, mode);
}

/**
 * Reads the input bits
 */
boolean pca9535::read_input()
{
    return this->read_many(0x0, 2, this->input);
}

/**
 * Writes the output bits
 */
boolean pca9535::write_output()
{
    return this->write_many(0x2, 2, this->output);
}

/**
 * calls read_input and write_output, returns true if both succeed false if one fails
 */
boolean pca9535::sync()
{
    boolean ret;
    ret = this->read_input();
    ret = ret & this->write_output();
    return ret;
}

