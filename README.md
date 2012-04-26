# PCA9535 library

Used to control this I2C I/O expander

## Installing

Clone this repo to your arduino libraries folder, then clone the following repos as well

  * git://github.com/rambo/I2C.git
  * git://github.com/rambo/i2c_device.git

# TODO

Draw a pull-up & LED resistor "wing" PCB, something like:

             ^ 5V
             |
             R=100k
             |
    IO_pin<--o-R=150--->pin_header (LED or switch)

This way the each I/O pin can be used with the pull-up to sense a switch position (switch would be closing to ground) and driving LEDs by sinking current in output mode is not affected.
