# SENTSOR Uno Plus
## Introduction
<img src="https://github.com/adamalfath/sentsor-uno-plus/blob/main/media/unoplus-render2.png" width="600">  

Inspired from the well known Arduino Uno development board from Arduino, SENTSOR Uno Plus comes with ATmega328PB MCU bringing more GPIO and peripherals. Equips with DS1307M RTC and MicroSD slot to easing your datalogging needs, SK6812 addressable RGB LED to play around, and DC-DC buck converter ready to provide juice for your power hungry project.  

The CH340 USB-UART bridge communication line designed to be detachable from the main MCU, giving you ability to use it as an external programmer. It's 2-in-1 device! Either as a development board or a serial programmer, SENTSOR Uno Plus is here ready to serve you.

## Features
<img src="https://github.com/adamalfath/sentsor-uno-plus/blob/main/media/unoplus-pinoutposter.png" width="600">  

- **Arduino Uno Form Factor**, same pin layout ensuring compatibility with every existing shield or module.
- **ATmega328PB-AU** @16MHz running on MiniCore custom Optiboot bootloader, packing extra functionality. Fully supported by Arduino IDE.
- **CH340C UART to USB Bridge**, with switchable UART line designed to be modular. Data pin such as RX, TX, DTR, RTS is accessible via given pin header so you can use it as a standalone USB-UART device or as an external programmer for other board.
- **DS1307M RTC**, with replaceable CR1220 battery. Connected via I2C at address 0x68.
- **MT2492 DC-DC Converter**, set to +5V output. Delivering up to 2A with input range 6-16V, plenty enough for your power demanding project.
- **ME6211 LDO**, providing +3.3V power up to 500mA.
- **Built-in LED/RGB**, single color active-high LED connected to pin D22, and SK6812 addressable RGB LED connected to pin D23. SK6812 data out is exposed so you can chain it up with the rest of the LED circuit.
- **MicroSD socket**, connected via SPI with slave select (SS) at pin D10.
- **USB Type-C Connector**, no more hassle when connecting USB cable, plug it in anyway you want.
- **24 pin GPIO** @5V level with extra pin and peripheral: 16xDigital IO, 8x10bit ADC, 2xUART, 2xSPI, 2xI2C. Please refer to poster image above.  

### Peripheral comparison ATmega328PB vs. ATmega328P
|Feature|ATmega328PB|ATmega328PB|
|-|-|-|
|Digital IO|16 (usable)|14 (usable)|
|Analog Input|8|6|
|UART|2|1|
|I2C/TWI|2|1|
|SPI|2|1|
|PWM|10 (9 usable, PD2 double used)|6|
|Touch Controller|Yes|No|
|Device UID|Yes|No|

## How to Use
### Installing USB-UART Driver
The CH340 driver need to be installed, otherwise the board will be unrecognized by your OS nor the Arduino IDE software. Download the latest driver here http://www.wch-ic.com/downloads/CH341SER_ZIP.html. The step is straight forward, download the file and click the executable file to install the driver.  

After this, you should see the serial communication device (and port number) both on your system (device manager) or in the Arduino IDE software. You can skip this step if you already install the driver.

### Installing MiniCore Hardware Package
The Atmega328**PB** variant doesn't supported out-of-the-box by Arduino IDE so we need 3rd-party hardware package called MiniCore. The package installed using board manager, for detailed instruction on how to install MiniCore on Arduino IDE you can follow the step here
https://github.com/MCUdude/MiniCore#how-to-install.  

Once it's done, MiniCore should be listed on the board selection menu. Choose **ATmega328** and **328PB** variant, you can left the other option as default.  
<img src="https://github.com/adamalfath/sentsor-uno-plus/blob/main/media/unoplus-arduinoideinfo.png" width="600">  
Now your SENTSOR Uno Plus is ready to be use! Again, you can skip this step if you already install the MiniCore hardware package.  

### Dependency
To access on-board peripheral like RTC, MicroSD & RGB LED you may need to install related library below:
- RTCLib https://github.com/adafruit/RTClib
- SdFat https://github.com/greiman/SdFat
- NeoPixel https://github.com/adafruit/Adafruit_NeoPixel  

or any other library of your choice that have same functionality.

## Bill of Materials
|Designator|Qty|Name/Value|Footprint|
|-|-|-|-|
|U1|1|CH340C|SOP-16_L10.0-W3.9-P1.27|
|U2|1|MT2492|SOT-23-6_L2.9-W1.6-P0.95|
|U3|1|ME6211C33M5G-N|SOT-23-5_L3.0-W1.7-P0.95|
|U4|1|ATMEGA328PB-AU|TQFP-32_L7.0-W7.0-P0.80|
|U5|1|DS1307M/TR|SOIC-8_L4.9-W3.9-P1.27|
|U6|1|MC74VHC125DTR2G|TSSOP-14_L5.0-W4.4-P0.65|
|R1|1|1M|R0402|
|R10|1|110k|R0402|
|R11,R15|2|1k|R0402|
|R2,R3|2|5.1k|R0402|
|R4,R5,R6,R7|4|1k|R0402|
|R8,R12,R13,R14|4|10k|R0402|
|R9|1|15k|R0402|
|C1,C11,C12,C13,C14,C15|6|100n|C0402|
|C17|1|100n|C0402|
|C2,C3|2|100n|C0402|
|C4,C7|2|22u|C0805|
|C5|1|22n|C0402|
|C6|1|22p|C0402|
|C8|1|100u, 10V|CAP-SMD_BD5.0-L5.3-W5.3|
|C9,C10|2|1u|C0402|
|F1|1|550mA, 9V|F0603|
|L1|1|10u, 3A|IND-SMD_L6.6-W6.6|
|L2|1|10uH|L0603|
|D1|1|B5819WS|SOD-323_L1.8-W1.3-LS2.5|
|D2|1|USBLC6-2SC6|SOT-23-6_L2.9-W1.6-P0.95-LS2.8|
|LED1,LED2|2|Blue|LED0402|
|LED3,LED4|2|White|LED0402|
|LED5|1|EC20-SK6812|LED2020|
|X1|1|16MHz|OSC-SMD_3P-L3.2-W1.3-P0.95|
|X2|1|32.768kHz|OSC-SMD_4P-8032|
|BTN1|1|4.5x4.5x3|SW-SMD_4P-L4.5-W4.5-P3.00|
|SW1|1|HAD-02HWA-R|SW-SMD_2SPST-P2.54|
|CN1|1|TYPEC-304-BCP16|USB-C-SMD-TH|
|CN2|1|5.5-2.0MM|DC-IN-TH_5.5x2.1|
|CARD1|1|HYC80-TF08-375|HYC80-TF08-XXX|
|J1,J4|2|1x8P Female|HDR-F-P2.54|
|J2|1|1x10P Female|HDR-F-P2.54|
|J3|1|1x6P Female|HDR-F-P2.54|
|J5|1|1x4P Male|HDR-M-P2.54|
|J6|1|2x3P Male|HDR-M-P2.54|
|J7|1|1x6P Male|HDR-M-P2.54|
|J8|1|1x3P Male|HDR-M-P2.54|
|BAT1|1|CR1220|BAT_CR1220_SMD|


## Design 
<img src="https://github.com/adamalfath/sentsor-uno-plus/blob/main/media/unoplus-pcb-ss.png" width="600">  

SENTSOR Uno Plus is an open source hardware, please use it wisely. The project files is hosted on online based EDA called EasyEDA, you can access it via link below:  

Link: https://easyeda.com/sentsor-project/sentsor-uno-plus

The back silkscreen artwork <a href="https://www.vecteezy.com/vector-art/665571-megamendung-batik-gold-sketch-pattern">"Megamendung Batik Gold Sketch Pattern" by nightwolfdezines</a> is taken from <a href="https://www.vecteezy.com/">www.vecteezy.com</a> under Free License.

## Gallery
_Render View:_  
<img src="https://github.com/adamalfath/sentsor-uno-plus/blob/main/media/unoplus-render0.png" width="400"> <img src="https://github.com/adamalfath/sentsor-uno-plus/blob/main/media/unoplus-render1.png" width="400">  
<img src="https://github.com/adamalfath/sentsor-uno-plus/blob/main/media/unoplus-render2.png" width="400"> <img src="https://github.com/adamalfath/sentsor-uno-plus/blob/main/media/unoplus-render3.png" width="400">

## Support Open Source Hardware & SENTSOR!
If you are interested in our product, you can buy them in the marketplace or by giving donation using this link below:

[![Store](https://img.shields.io/badge/marketplace-Tokopedia-brightgreen.svg)](https://www.tokopedia.com/gerai-sagalarupa/etalase/sentsor-product)  [![Store](https://img.shields.io/badge/marketplace-Tindie-lightgrey.svg)](https://www.tindie.com/)  [![Donate](https://img.shields.io/badge/donate-PayPal-blue.svg)](https://www.paypal.me/adamalfath)  

Your support will be very helpful for the next development of open source hardware from SENTSOR.

## Information
SENTSOR  
Author: Adam Alfath  
Contact: adam.alfath23@gmail.com  
Web: [sentsor.net](http://www.sentsor.net)  
Repo: [SENTSOR Main Repo](http://github.com/adamalfath/sentsor)

<a href="https://certification.oshwa.org/id000006.html"><img src="https://github.com/adamalfath/sentsor-uno-plus/blob/main/media/OSHW_ID000006.png" width="80"><br/><a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png"/></a><br/>
SENTSOR Uno Plus is a certified open source hardware project UID <a rel="certification" href="https://certification.oshwa.org/id000006.html">ID000006</a> and licensed under <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.