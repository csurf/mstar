# MSTAR LCD Controller Firmare

Working source code / firmware for the MST70*-lf series of MSTAR Video/LCD controller IC's:
This has currently been tested with the following IC's:
MST703-LF
MST705-LF
MST706-LF

Use google to find the appropriate datasheet for the chip you're using, i.e., for the pinouts, but the configuration register settings for all of these should be more/less the same.

The primary goal of this repo is to focus mainly on small controller boards w/ 4"-7" TTL TFT LCD's used in analog FPV video transmissions. Thus, I've modified the firmware for simplicity, stability, and full support for 'snow' static in low / no-signal conditions. I've also removed many of the extra features that aren't needed for this application.

FYI, this is all still a work in progress, so use at your own risk...

Help is wanted/welcome, for those interested in joining the effort.


## CONFIGURING
The proper PCB board & LCD types & options need to be configured before starting the build. 
The relevant config options can be found in the following files:
- board.h (where you can configure basic global board options & add new board definitions)
- panel.h (where you can add new LCD panel definitions)

Each board / LCD definition file will have various config options that can vary based on the specific board layout & LCD type.
Eventually, I plan to add templates & build images for the most common PCB board & LCD screen combinations.

## BUILDING
The source code is built via a Keil Compiler project in order to build the binary firmware image. Eventually, I might look into porting it over to [SDCC](http://sdcc.sourceforge.net/), but it's not worth the effort right now. I, myself, run Keil via 'wine' within a linux environment, but running Keil in Windows should work as well.

## FLASHING
The goal is to flash the 128K SPI flash chip with the binary image.
There are various ways to achieve this goal:
- removing / desoldering the SOIC-8 SPI flash chip and using an external programmer to flash it (Arduino, Bus Pirate, etc.)
- MSTAR programming tool & software 
- DIY programming dongle & MSTAR ISP software
- Raspberry Pi & 'flashrom' utility (My preferred method; see below)


## Using an RPi to flash 
The MSTAR chips expose an i2c bus for ISP programming that can be accessed over the UART pins. By connecting these pins to the native i2c bus on a Raspberry Pi, it's possible to use the [flashrom](https://flashrom.org/Flashrom) utility in order to program the flash chip.

The basic flashrom commands are as follows:
```
# read image
flashrom -p mstarddc_spi:dev=/dev/i2c-1:0x49 -r backup_image.bin

# verify a previously-read image
flashrom -p mstarddc_spi:dev=/dev/i2c-1:0x49 -v backup_image.bin

# write image
flashrom -p mstarddc_spi:dev=/dev/i2c-1:0x49 -w firmware_image.bin 
```
### MAKE SURE TO CREATE A BACKUP IMAGE OF YOUR STOCK FIRMARE & VERIFY IT BEFORE ATTEMPTING TO FLASH A CUSTOM IMAGE!!!

## BASIC WORKING CONCEPTS

The MSTAR ASICs have an embedded 8051 microcontroller that is used to configure various internal configuration registers. On startup, the configuration registers need to be correctly initialized based on the PCB layout, LCD type&size, and incoming signal type. Also, the configuration needs to be constantly monitored & adjusted based on the condition of the incoming video signal. Keypad inputs are also monitored for handling features such as the built-in OSD & 'input select' functionality.

The MSTAR chips expose GPIO & PWM functionality which can be used to control external devices such as an LCD backlight, video tuner/receiver, LED's, etc.

