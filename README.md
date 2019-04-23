# Link-Tech Sensor-MQTT Lib
Library to simplify handling of 433MHz door/window sensors (e.g. from Stabo) using MQTT for Arduino platforms.

**Version:** 1.0.0 (2019-04-20)

**Author:** Link-Technologies - [Dipl.-Inform. (FH) Andreas Link](http://www.AndreasLink.de)


## RF-Sensor MQTT Library for Arduino

With this library you can create objects for e.g. 433MHz Door/Window sensors - mainly created for Stabo sensors ([Stabo Funk-Tür-/Fensterkontakt 51126](https://stabo.de/hs-zubehoer/)) to easily send corresponding MQTT messages on predefind topics for radio detected events. Setup is done via MQTT based on button hold ID and all other events can automtically be handled.

### Usage
- Create sensor object with predefined constructor to create with initial ID and main MQTT topic _OR_
- Create sensor object with default constructor, then use init function later
- Optimal usage is to prepare an array of sensor objects and fill it later according to setup

### Todo
- Extend documentation
- Add simple examples


**_More documentation to come_**

