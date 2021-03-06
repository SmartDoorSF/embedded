/*
 * MQTTClient.cpp
 *
 *  Created on: Mar 19, 2016
 *      Author: ianzhang
 */
#include "MQTTClient.h"
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

//using namespace std;
/*======================================================================
  Constructor/Destructor
========================================================================*/
MQTTClient::MQTTClient(){

}
MQTTClient::~MQTTClient(){
	close();
}
void MQTTClient::close()
{
	if (spipe) {
		fclose(spipe);
	}
}
/*========================================================================
  Initialization. Store variables to be used for subscribe/publish calls
==========================================================================*/
void MQTTClient::begin(char *broker, int port, security_mode smode,
						char* cafile, char *user, char *psk)
{
	strcpy(mqtt_broker, broker);
	serverPort = port;
	mode = smode;
	if (mode == SSL) {
		strcpy(certificate_file, cafile);
	}
	else if (mode == PSK) {
		strcpy(psk_identity, user);
		strcpy(psk_password, psk);
	}
	std::cout << "MQTTClient initialized" << std::endl;
	std::cout << "Broker: "<< mqtt_broker << std::endl;
	std::cout << "Port: " << serverPort << std::endl;
	std::cout << "Mode: " << mode << std::endl;
}


/*========================================================================
  Subscribe to a topic, (*callback) is a function to be called when client
  receive a message
==========================================================================*/
bool MQTTClient::subscribe(char* topic,
		void (*callback)(char* topic, char* message))
{
	char cmdString[256];

	if (mqtt_broker == NULL) {
		return false;
	}
	if (topic == NULL) {
		return false;
	}

	callback_function = callback;
	switch(mode) {
		case OPEN:
			sprintf(cmdString, "mosquitto_sub -h %s -p %d -t %s -v",
					mqtt_broker, serverPort, topic);
			break;
		case SSL:
			sprintf(cmdString, "mosquitto_sub -h %s -p %d -t %s -v --cafile %s",
			        mqtt_broker, serverPort, topic, certificate_file);
			break;
		case PSK:
			sprintf(cmdString, "mosquitto_sub -h %s -p %d -t %s -v --psk-identity %s --psk %s",
					mqtt_broker, serverPort, topic, psk_identity, psk_password);
			break;
		default:
			break;
	}
	if ((spipe = (FILE*)popen(cmdString, "r"))!= NULL) {
		// Set the pipe read mode to non-blocking
		int fd 		= fileno(spipe);
		int flags   = fcntl(fd, F_GETFL, 0);
		flags |= O_NONBLOCK;
		fcntl(fd, F_SETFL, flags);
		strcpy(topicString, topic);
		return true;
	}
	else {
		return false;
	}
}

/*====================================================================
  Check if there is data in the pipe,
  if true, parse topic and message and execute callback function
  return if pipe is empty
======================================================================*/
void MQTTClient::loop()
{
	if(fgets(dataBuffer, sizeof(dataBuffer), spipe)) {
		parseDataBuffer();
		callback_function(topic, message);
	}
}
/*====================================================================
  Publish a message on the given topic
======================================================================*/
bool MQTTClient::publish(char *topic, char *message)
{
	FILE* ppipe;
	char cmdString[256];
	bool retval = false;
	if (this->mqtt_broker == NULL) {
		return false;
	}
	if (topic == NULL) {
		return false;
	}
	switch (this->mode) {
		case OPEN:
			sprintf(cmdString,
					"mosquitto_pub -h %s -p %d -t %s -m \"%s\" %s",
					mqtt_broker, serverPort, topic, message, retain_flag?"-r":"");
			break;
		case SSL:
			sprintf(cmdString,
					"mosquitto_pub -h %s -p %d --cafile %s -t %s -m \"%s\" %s",
					mqtt_broker, serverPort, certificate_file,
					topic, message, retain_flag?"-r":"");
			break;
		case PSK:
			sprintf(cmdString,
					"mosquitto_pub -h %s -p %d --psk-identity %s --psk %s -t %s -m \"%s\" %s",
					 mqtt_broker, serverPort, psk_identity, psk_password,
					 topic, message, retain_flag?"-r":"");
			break;
	}
	if (!(ppipe = (FILE *)popen(cmdString, "w"))) {
	    retval = false;
	}
	if (fputs(cmdString, ppipe) != EOF) {
	    retval = true;
	}
	else {
	    retval = false;
	}
	fclose(ppipe);
	return retval;
}

/*======================================================================
  Parse data in the data buffer to topic and message buffer
  delimiter is the first space
  if there is only one recognizable string, it is assumed a message
  string and topic is set to NULL
========================================================================*/
void MQTTClient::parseDataBuffer()
{
  topic   = dataBuffer;
  message = dataBuffer;
  while((*message) != 0) {
    if ((*message) == 0x20) {
      // replace the first space with the NULL character
      (*message) = 0;
      message++;
      break;
    }
    else {
      message++;
    }
  }
  if (strlen(message) == 0) {
    topic   = NULL;
    message = dataBuffer;
  }
}

