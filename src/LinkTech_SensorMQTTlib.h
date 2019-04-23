/*
  Link-Technologies Sensor-Library to easy usage of code, when working with 433MHz receiver library
  16.06.2017 by Dipl.-Inform. (FH) Andreas Link - AndreasLink.de - link-technologies.de
*/

#ifndef LinkTech_SensorMQTTlib_h
#define LinkTech_SensorMQTTlib_h

#include "Arduino.h"


enum SensorStatus
{
	SENSOR_UNKNOWN = -1,
	SENSOR_OPEN = 1,
	SENSOR_CLOSED = 0,
	SENSOR_BTNPRESSED = 2,
	SENSOR_BTNHOLD = 3,
	SENSOR_SABOTAGE = 4
};

/*
enum SensorEventType
{
	SENSOR_TYPE_UNKNOWN = -1,
	SENSOR_TYPE_STATUS = 0,
	SENSOR_TYPE_BUTTON = 1,
	SENSOR_TYPE_SABOTAGE = 2
};
*/

class SensorMQTT
{
  public:
    //Default Constructor will initialize with all empty and uninitialised values (e.g. needed for creating arrays in advance)
    SensorMQTT();
    ~SensorMQTT();

  	/*
  	  Constructor with:
  	  pFullMQTTtopic 	 --> full topic of the sensor in the MQTT structure, example: "haus/kinderzimmer/tuer"
  	  pButtonHoldValue --> transmitted 433MHz ID, when holding button on sensor, example: 5505096  	  
  	*/
    SensorMQTT(unsigned long pButtonHoldValue, String pFullMQTTtopic);

    //Get full MQTT topic of the sensor, where all data is provided to
    String getMQTTtopic();

    //Set full MQTT topic of the sensor, where all data is provided to following the MQTT structure, example: "haus/kinderzimmer/tuer"
    void setMQTTtopic(String pFullMQTTtopic);

    // Returns IDs of sensor to corresponding action (calculated)
    unsigned long  getButtonPressID();
    unsigned long  getButtonHoldID();
    unsigned long  getOpenID();
    unsigned long  getCloseID();
    unsigned long  getSabotageID();


    //Initial setup or re-setup to define new sensor, dependencies and calculate events
    void initSensor(unsigned long pButtonHoldValue, String pMQTTtopic);

    //Removes sensor from being a valid object, returns 1, if found, else 0 --> initSensor needs to be called afterwards for reuse
    uint8_t deleteSensor(unsigned long pButtonHoldValue);

    //Returns 1, if object is already set up with initSensor function or 0, if e.g. just created by default constructor or deleted
    uint8_t isDefined();

    //Major validation function, to check if a received ID is one of the IDs of this sensor, returns 1, if ID is found, else 0
    uint8_t validateSensorID(unsigned long pReceivedValue, String *returnTopic, SensorStatus *returnStatus);

    
  private:
    uint8_t _isDefined;

    unsigned long _buttonHoldIDValue;
    unsigned long _buttonPressIDValue;
	  unsigned long _sabotageIDValue;
	  unsigned long _openIDValue;
	  unsigned long _closeIDValue;

    String _mqttFullTopic;
    //char* _mqttTopicPrefix;

    void _initSensor(unsigned long pButtonHoldValue, String pMQTTtopic);
};

#endif
