# SV650 Digital Gauges

## Project description
This repo contains all resources that I've used to make a gauge cluster for a first generation Suzuki SV650 (1999-2002). Everything from wiring loom schematics, diagrams of my custom arduino "shield", the software that I run on it, the components and connectors that I've used, bitmap-icons, 3D-models of the case (for 3D-printing), etc. Basically all information that might be useful for others in some way.

![display in case](https://github.com/RobinWagenaar/motorcycle-gaugecluster/blob/master/casing/3.1%E2%80%9D%20oled%20case%20v17.png "display in case")

## Current status / changes
`21-11-2017`: 
Sent the model to the 3D-hub. Also, still waiting for the display to arrive. 

`19-11-2017`: 
Found a sheet containing dimensions of my OLED-display. So I've downloaded the trail version of Fusion360 and started mocking up a crude (but correctly sized) model of the display. Also tried to model some sort of a casing, but its ugly. Very. Ugly. But I want to just 3D-print anything simply to get a feel for the quality of the resulting object. And also what tolerances I need to use / accuracy issues I need to deal with. Used 3D-hubs to find a hub that will print for a reasonable price. 

`17-11-2017`: 
Still waiting for the bloody display to arrive. I'm fantasizing about what I will do with all them sixteen-thousand-threehundred-and-eightyfour pixels. I felt inspired and downloaded GIMP. Created some tiny, very pixelated, 16x16 icons. Hope they will be readable on the screen. Exported the image to byte-arrays in c-sourcecode format. No shit. Did I mention that GIMP rocks? No? Gimp rocks. And U8GLIB has this lovely function called drawXBMP(..). Theoretically, it should draw my byte-arrays. Fingers crossed.

`16-11-2017`: 
I found a neat little switched power supply from Traco, which accepts voltages up to 40v and outputs a very steady 4.99v. Will add in part numbers later.

`15-11-2017`: 
Soldered a ATMega328P to my proto-board. Hooked up I2C as well as some other signal wires. Decided that I trust these signals a little bit more than the dreaded spark plug signal, so I won't be using opto-couplers to shield the I/O pins on these lines. Insead went with 47k/100k voltage-dividers to tune voltage down from 12-15v to 4-5v. 

`12-11-2017`: 
Thought about all functions that these gauges must have. Turn left, turn right, neutral light, water temp, oil temp, high beam, speedo, tacho, distance, fuel sensors. Counted the I/O-pins that would be needed. Took into account that I will need 4 pins for SPI, 2 for IC2, 2 for external crystal, I came to the conclusion this must be doable with a regular ATMega328 as main processor.

`11-11-2017`: 
Decided that waiting for my OLED-display is even more stupid, so hooked up an I2C-connection from the ATTiny85 to another UNO. Made the painful mistake of miswiring the required pullup resistors as pulldown-resistors. Sadly it took a while before I found the culprit, but I2C is now operational. The ATTiny is a slave device with address #3. Used the TinyWire library.

`10-11-2017`: 
Decided that using two LEDs as a debugger is stupid, so I've ordered a monochrome graphical OLED-display with 256x64 pixels. These badboys are readable in direct/bright sunlight, not too expensive, and should also fairly be easy for an Arduino to drive over SPI using u8glib. 

`06-11-2017`: 
Cleaned up the ATTiny software a bit. This ATTiny85 will be counting the number of pulses on the speedo and tacho wires, but must also communicate with a "main" microprocessor every once in a while. Therefore decided to work with interrupts instead of polling for both signal wires.

`05-11-2017`: 
Wrote very crude software for the ATTiny, and programmed it on a breadboard with an Arduino Uno as ISP. It turns on leds when the signals are HIGH. The speedo led is flashing as expected but seems to me as if the tacho wire is normally high and gets pulled down on spark; unexpected but fine. 

`04-11-2017`: 
I've soldered a proto-board containing the tacho filter from D'Ecosse and TeeRiver, and connected it to an ATTiny85. I suspect that the pulses from the coil pack may harm the microcontroller, so for safety reasons I now run the signal through an opto-coupler. Did the same for the speedo signal.

## History
Ok, so, here is what happened.. A couple of months ago, my girlfriend bought her first motorcycle. A pitch black Suzuki SV650 from 1999. The naked bike of the so called "curvy" -first- generation. She had her mind set on getting this exact motorcycle, and literally scoured online marketplaces for weeks before finding one in good condition. When she finally found one that met her criteria, there was only one issue: she didn't have her license yet. So in the meanwhile, I drove it around. And I quite enjoyed the rides because it's a really easy handling little motorcycle. Unfortunately, not much later, I found out that even easy handling little motorcycles can crash. Hard. 

I will spare you the details of the crash, but as you might imagine, I wasn't too proud of my actions and decided to fix the bike as quickly as humanly possible. With the speed of light, I sourced all the nessesary parts and started the reparations. But fixing up one thing led to another, and another, and before I knew it, this project turned into a full bike rebuild. Lucky for me, this naked bike was easy enough to work on, and it took me less than a month to make the bike look and run like new. Except for one little part, that turns out to be impossibly hard to find. The asymmetric, ugly-as-hell, gauge cluster. 

In fact, I'm still searching eBay and other websites on a daily basis. But as long as I can't find an undamaged unit for a reasonable price, I will try to make my own. Sooo... _hello wiring loom from '99; meet my little friend Arduino over here._

