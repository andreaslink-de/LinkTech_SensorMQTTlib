/*
  Link-Technologies Sensor-Library to easy usage of code, when working with 433MHz receiver library
  16.06.2017 by Dipl.-Inform. (FH) Andreas Link - AndreasLink.de - link-technologies.de
*/

#include "Arduino.h"
#include "LinkTech_SensorMQTTlib.h"

SensorMQTT::SensorMQTT()
{
	_initSensor(0, "");
}

//SensorMQTT::SensorMQTT(String pMQTTName, unsigned long pButtonHoldValue, char* pMQTTTopicPrefix)
SensorMQTT::SensorMQTT(unsigned long pButtonHoldValue, String pFullMQTTtopic)
{
	_initSensor(pButtonHoldValue, pFullMQTTtopic);
}

SensorMQTT::~SensorMQTT()
{
	//Nothing to destuct
}

String SensorMQTT::getMQTTtopic()
{
	return _mqttFullTopic;
}

void SensorMQTT::setMQTTtopic(String pFullMQTTtopic)
{
	String newMQTTtopic = pFullMQTTtopic;
	newMQTTtopic.trim();

	if (newMQTTtopic == "")
		newMQTTtopic = "undefinedSensor";

	_mqttFullTopic = newMQTTtopic;
}

/* ------------------------------------------ */

unsigned long SensorMQTT::getButtonPressID()
{
	return _buttonPressIDValue;
}

unsigned long SensorMQTT::getButtonHoldID()
{
	return _buttonHoldIDValue;
}

unsigned long SensorMQTT::getOpenID()
{
	return _openIDValue;
}

unsigned long SensorMQTT::getCloseID()
{
	return _closeIDValue;
}

unsigned long SensorMQTT::getSabotageID()
{
	return _sabotageIDValue;
}

/* ------------------------------------------ */
 

void SensorMQTT::initSensor(unsigned long pButtonHoldValue, String pMQTTtopic)
{
	String newMQTTtopic = pMQTTtopic;
	newMQTTtopic.trim();

	if (newMQTTtopic == "")
		newMQTTtopic = "undefined-sensor";

	_initSensor(pButtonHoldValue, newMQTTtopic);
}

//Private
void SensorMQTT::_initSensor(unsigned long pButtonHoldValue, String pMQTTtopic)
{
	//Special case, like empty init
	if (pButtonHoldValue == 0)
	{
		_buttonHoldIDValue = 0;
		_buttonPressIDValue = 0;
		_sabotageIDValue = 0; 
		_openIDValue = 0;
		_closeIDValue = 0;

		_mqttFullTopic = "";
		_isDefined = false;
	} else { //Any other usual case
		/*
		Code-Berechnung, wenn Sabotage bekannt ist mit Bsp.:
		0 : '4194567' sabotage
		+3 : '4194570' open
		+4 : '4194574' close
		+58: '4194632' button hold
		+58: '4194690' button press
		*/

		_buttonHoldIDValue = pButtonHoldValue;
		_buttonPressIDValue = pButtonHoldValue +58;
		_sabotageIDValue = pButtonHoldValue -58-7; 
		_openIDValue = pButtonHoldValue -58-4;
		_closeIDValue = pButtonHoldValue -58;

		// Trim it and store it
		pMQTTtopic.trim();
		_mqttFullTopic = (pMQTTtopic == "") ? "undefined-sensor" : pMQTTtopic;

		_isDefined = true;
	}
}

uint8_t SensorMQTT::deleteSensor(unsigned long pButtonHoldValue)
{
	//Delete only, when value matches
	if (pButtonHoldValue == _buttonHoldIDValue)
	{
		_buttonHoldIDValue = 0;
		_buttonPressIDValue = 0;
		_sabotageIDValue = 0; 
		_openIDValue = 0;
		_closeIDValue = 0;

		_mqttFullTopic = "";
		_isDefined = false;

		return 1;
	}
	
	return 0;
}

/* ------------------------------------------ */

uint8_t SensorMQTT::isDefined()
{
	return _isDefined;
}


uint8_t SensorMQTT::validateSensorID(unsigned long pReceivedValue, String *returnTopic, SensorStatus *returnStatus)
{
	if (pReceivedValue == _openIDValue)
	{
		*returnStatus = SENSOR_OPEN;
		*returnTopic = _mqttFullTopic + "/status";
		return 1;
	} 

	if (pReceivedValue == _closeIDValue)
	{
		*returnStatus = SENSOR_CLOSED;
		*returnTopic = _mqttFullTopic + "/status";
		return 1;
	} 

	if (pReceivedValue == _buttonPressIDValue)
	{
		*returnStatus = SENSOR_BTNPRESSED;
		*returnTopic = _mqttFullTopic + "/button/pressed";
		return 1;
	}

	if (pReceivedValue == _buttonHoldIDValue)
	{
		*returnStatus = SENSOR_BTNHOLD;
		*returnTopic = _mqttFullTopic + "/button/hold";
		return 1;
	}

	if (pReceivedValue == _sabotageIDValue)
	{
		*returnStatus = SENSOR_SABOTAGE;
		*returnTopic = _mqttFullTopic + "/sabotage";
		return 1;
	}

	return 0;
}


/*
//Returns full path for this sensor per type: _mqttTopicPrefix + _mqttName + /status or /status/button or /status/sabotage
String SensorMQTT::getFullMQTTtopic(SensorEventType pSensorType)
{
	if (pSensorType == SENSOR_TYPE_UNKNOWN)
		return "";

	//Open/Close MQTT-Topic
	if (pSensorType == SENSOR_TYPE_STATUS)
	{
		String finalTopicString = _mqttTopicPrefix + _mqttName + "/status";
		return finalTopicString;
		
		//char charBuffer[finalTopicString.length()+1]; // Does not work
		/*
		char charBuffer[90];
		finalTopicString.toCharArray(charBuffer, finalTopicString.length()+1);
		return charBuffer;
		*/
/*	}

	//Button MQTT-Topic
	if (pSensorType == SENSOR_TYPE_BUTTON)
	{
		String finalTopicString = _mqttTopicPrefix + _mqttName + "/status/button";
		return finalTopicString;

		/*
		//char charBuffer[finalTopicString.length()+1]; // Does not work
		char charBuffer[90];
		finalTopicString.toCharArray(charBuffer, finalTopicString.length()+1);
		return charBuffer;
		*/
/*	}

	//Sabotage MQTT-Topic
	if (pSensorType == SENSOR_TYPE_SABOTAGE)
	{
		String finalTopicString = _mqttTopicPrefix + _mqttName + "/status/sabotage";
		return finalTopicString;

		/*
		//char charBuffer[finalTopicString.length()+1]; // Does not work
		char charBuffer[90];
		finalTopicString.toCharArray(charBuffer, finalTopicString.length()+1);
		return charBuffer;
		*/
/*	}

	return "";
}
*/