## Current status / changelog

### 21-11-2017: 
Sent the model to the 3D-hub. Also, still waiting for the display to arrive. 

### 19-11-2017: 
Found a sheet containing dimensions of my OLED-display. So I've downloaded the trail version of Fusion360 and started mocking up a crude (but correctly sized) model of the display. Also tried to model some sort of a casing, but its ugly. Very. Ugly. But I want to just 3D-print anything simply to get a feel for the quality of the resulting object. And also what tolerances I need to use / accuracy issues I need to deal with. Used 3D-hubs to find a hub that will print for a reasonable price. 

### 17-11-2017: 
Still waiting for the bloody display to arrive. I'm already fantasizing about what I will do with all those sixteen-thousand-threehundred-and-eightyfour pixels. I felt inspired and downloaded GIMP. Created some tiny, very pixelated, 16x16 icons. Hope they will be readable on the screen. I've [exported the icons to byte-arrays in c-sourcecode format](https://github.com/RobinWagenaar/motorcycle-gaugecluster/tree/master/software/graphics). Did I mention that GIMP rocks? No? Gimp rocks. And U8GLIB has this neat function called drawXBMP(..). Which, theoretically, should be able to draw these byte-arrays. Fingers crossed.

![icon set](https://github.com/RobinWagenaar/motorcycle-gaugecluster/blob/master/software/graphics/iconset.png "icon set")

I'm wondering... I will connect the display via SPI, which saves pins but is probably a fair bit slower than the alternative 8-bit parallel interface. So, reducing the number of commands sent to the display may be a way to compensate for this. I suspect that drawXBMP(..) will simply loop through all pixels in the image and draw them separately. But decomposing these simple images into rectangles and lines would result in less commands. Which might be a lot faster. On second thought, the refesh-rate/speed matters primarily on the stats that change often, like speed and rpm. Hmm.. food for thought.

### 16-11-2017: 
I bought a neat little switched power supply from Traco, which accepts voltages up to 40v and outputs a very steady 4.99v. Will add in part numbers later.

### 15-11-2017: 
Soldered a ATMega328P to my proto-board. Hooked up I2C as well as some other signal wires. Decided that I trust these signals a little bit more than the dreaded spark plug signal, so I won't be using opto-couplers to shield the I/O pins on these lines. Insead went with 47k/100k voltage-dividers to turn down the voltage from 12-15v to a more acceptable 4-5v.

### 12-11-2017: 
Pondered about all functions that these gauges must have. Turn indicators, neutral light, high beam indicator, water/oil warning,  speedo, tacho, distance, and then there are these darned thermistor fuel sensors which I don't quite understand yet. Tried to coun the number of I/O-pins that would be needed. Took into account that some pins are needed for communication and the external crystal. Finally came to the conclusion this must be doable with a regular ATMega328 as main processing unit. 

### 11-11-2017: 
Decided that waiting for my OLED-display is boring, so I've hooked up an I2C-connection from the ATTiny85 to another UNO. Made the painful mistake of miswiring the required pullup resistors as pulldown-resistors. Sadly it took a while before I found the culprit, but I2C is now operational. Used the TinyWire library to make the ATTiny a slave device with address #3. Three, because, reasons.

### 10-11-2017: 
Decided that using two LEDs as a debugger is stupid. Also, my girlfriend thinks I'm crazy for staring into flickering LEDs for hours. So I've ordered a monochrome graphical OLED-display with 256x64 pixels. These badboys are readable in direct/bright sunlight, not too expensive, can do 4-bit grayscale, and it should be fairly easy for an Arduino to drive the SSD1322 chip over SPI using u8glib.

A company called NewHaven produces the displays. But ofcourse I bought a chinese knockoff. This might bite me later. 

### 06-11-2017: 
Cleaned up the ATTiny software a bit. This ATTiny85 will be counting the number of pulses on the speedo and tacho wires, but must also communicate with a "main" microprocessor every once in a while. Therefore decided to work with interrupts instead of polling for both signal wires.

### 05-11-2017: 
Wrote very crude software for the ATTiny, and programmed it on a breadboard with an Arduino Uno as ISP. It turns on leds when the signals are HIGH. The speedo led is flashing as expected but seems to me as if the tacho wire is normally high and gets pulled down on spark; unexpected but fine. 

### 04-11-2017: 
I've soldered a proto-board containing the tacho filter from D'Ecosse and TeeRiver, and connected it to an ATTiny85. I suspect that the pulses from the coil pack may harm the microcontroller, so for safety reasons I now run the signal through an opto-coupler. Did the same for the speedo signal.

### How it all started:
Ok, so, here is what happened.. A couple of months ago, my girlfriend bought her first motorcycle. A pitch black Suzuki SV650 from 1999. The naked bike of the so called "curvy" -first- generation. She had her mind set on getting this exact motorcycle, and literally scoured online marketplaces for weeks before finding one in good condition. When she finally found one that met her criteria, there was only one issue: she didn't have her license yet. So in the meanwhile, I drove it around. And I quite enjoyed the rides because it's a really easy handling little motorcycle. Unfortunately, not much later, I found out that even easy handling little motorcycles can crash. Hard. 

I will spare you the details of the crash, but as you might imagine, I wasn't too proud of my actions and decided to fix the bike as quickly as humanly possible. With the speed of light, I sourced all the nessesary parts and started the reparations. But fixing up one thing led to another, and another, and before I knew it, this project turned into a full bike rebuild. Lucky for me, this naked bike was easy enough to work on, and it took me less than a month to make the bike look and run like new. Except for one little part, that turns out to be impossibly hard to find. The asymmetric, ugly-as-hell, gauge cluster. 

In fact, I'm still searching eBay and other websites on a daily basis. But as long as I can't find an undamaged unit for a reasonable price, I will try to make my own. Sooo... _hello wiring loom from '99; meet my little friend Arduino over here._