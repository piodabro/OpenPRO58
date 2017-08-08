# ![Logo](Docs/DSC_0556.JPG)

OpenPRO58 is an alternative firmware for Eachine PRO58 5.8Ghz Diversity module

It is basicaly ported from RX5808PRO-Diversity project https://github.com/sheaivey/rx5808-pro-diversity

Major differnecies:

- PRO58 runs on STM32
- There is an external EEPROM memory on I2S( different one than OLED has)
- More buttons (3 on module, 3 additional from goggles)
- Two separated chip selects for RX5808
- Separated signal for switching multiplexers


ToDo
- clean-up EEPROM code - done in very dirty way
- ~~convert soft SPI for modules to hardware~~
- make code smaller, now it exceedes C8T6 64kByte limit.

How to setup development enviroment https://github.com/MartinLaza/OpenPRO58/blob/master/Docs/setup_enviroment.md
How to wire to the module https://github.com/MartinLaza/OpenPRO58/blob/master/Docs/how_to_wire.md
