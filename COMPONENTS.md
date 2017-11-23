# Component list

## Display

The display was a hard choice. I wanted something that was not too expensive, easily readable in direct sunlight, with a reasonable resolution. Also, it needs to have a decent refresh-rate so there won't be noticable lag in speed and rpm numbers. If you're looking for the cheapest option; don't buy the slightly cheaper 3.3v version as it isn't compatible with the 5v ATMega I/O-pins

| Specs 		|				 |
| ------------- | -------------- |
|Brand			| East Rising	 |
|Type			| 3.2" OLED		 |
|Resolution 	| 256x64 		 |
| Colors 		| 4bit grayscale |
|Logic level 	| 5v 			 | 
|Interface 		| 4 wire SPI 	 |
|Controller  	| SSD1322 		 |

*Alternatives:* I've also seriously considered the iTead Nextion and NewHaven 4.3" TFT touch panels. The former can only be programmed with and IDE that requires Windows and the latter was very expensive. I didn't require a touchpanel because it wouldn't work with gloves anyway, so I went with the OLED option.

![display pic](https://i.imgur.com/RoUMzf0.jpg)

## Connectors

I didn't want to cut the wiring loom on the motorcycle, so I've sourced the original connectors (or at least ones that are compatible). These are, however, not so easy to find online. But eventually I found them. They can be ordered through AliExpress, EasternBeaver and CycleTerminal. You will need both the 6-pin and 10-pin connectors. And if you buy from a Chinese store: often the pins are sold separately..

| Connector | Brand			| Model 	|
| --------- | ------------- | --------- |
| 6-pin  	| Sumitomo  	| HM 090	|
| 10-pin  	| Sumitomo  	| MT 090 	|

*Alternatives:* Just remove the old connectors from the motorcycle, and replace them with molex-connectors. Just as good, but easier to come by and also cheaper. 

![10 pin connector](https://i.imgur.com/bfKbpeI.jpg)

## Power supply (DC-DC step down converter)

This unit is not cheap compared to a linear voltage regulator (for example an LM7805). It can be bought at any local radioshack for about eight euros. But it doesn't get hot, it takes any input up to 32v, it can deliver up to 1Amp, and it's relatively insensitive to voltage spikes. Also, it has a reasonably small form-factor. 

| Specs 			| 														|
| ----------------- | ----------------------------------------------------- |
| Brand				| TracoPower											|
| Type				| TSR-1 2450   											|
| Input voltage 	| up to 32v 											|
| Output voltage 	| 5v													|
| Datasheet 		| [link](https://www.tracopower.com/products/tsrn1.pdf) |

Alternatives: I believe an LM7805 with heatsink would work fine as well, considering the fact that this OLED-screen doesn't consume much power at all. But if you (like me) would like to coat the PCBs in some kind of epoxy for water-resistance, then heatsinks are a no-go.

![traco power supply](https://i.imgur.com/KNg53gt.jpg)

## Microcontrollers

The microcontroller will need to monitor speed and engine rpm continuously while also updating a display with a decent refresh rate. To prevent flickering the display-loop must not be interrupted. But at the same time, the sensor-interrupts may not be ignored for this will cause inaccuracies. So I decided to go with 2 microprocessors. A dedicated "core" for each task. 

Also, I'd like to use Arduino's, mainly because of the wide variety of available examples, tutorials and FAQs. But I don't like these huge proto-boards, so I decided to go for a minimal setup. I picked an ATMega328 as "main" processor, with plenty of pins for connecting a display and some other inputs. And a cute little ATTiny85 for counting pulses from the sparkplug and wheel-rotation sensor.

| Processor  | Datasheet | 
| ---------- | --------- |
| ATMega328p | [link](http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf) |
| ATTiny85   | [link](http://www.atmel.com/images/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf) |

*Alternatives:* If you're willing to spend a bit more money, you might want to go with a faster, single processing unit. Especially if you want to connect more sensors or need to push more pixels to a bigger (full color?) display. I can personally recommend a Teensy 3.x for this purpose. It's 32bit 180MHz core is brutally fast, but beware: is has 3.3v I/O-pins so make sure this is compatible with the display you're using.

![atmega328](https://i.imgur.com/JX0FIZT.png)
