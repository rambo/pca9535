# PCA9535 library

Used to control this I2C I/O expander

Note: default device addresses etc suppose that the adress lines are *pulled up* when not explicitly set, this is what the breakout board (pca9535bo.brd) does by default (user can then pull them down via solder jumpers)

The device has no internal pull-ups that could be enabled (bit of a shame for input purposes...) so I also made a "wing" board with pull-ups and also series resistors for driving LEDs (pca9535bowing.brd)

## Installing

Clone this repo to your arduino libraries folder, then clone the following repos as well

  * git://github.com/rambo/I2C.git
  * git://github.com/rambo/i2c_device.git

