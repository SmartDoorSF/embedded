/*
 * MQTTClient.h
 *
 *  Created on: Mar 19, 2016
 *      Author: ianzhang
 */

/*
 * Minimalist MQTT Client using mosquitto_sub and mosquitto_pub
 * Assume Mosquitto MQTT server already installed and mosquitto_pub/sub
 * are in search path
 */

#ifndef MQTTCLIENT_H_
#define MQTTCLIENT_H_

#include <stdio.h>

enum security_mode {OPEN = 0, SSL = 1, PSK = 2};

class MQTTClient {

	public:
		MQTTClient();
		~MQTTClient();
		void begin(char *broker, int port, security_mode mode,
				char *certificate_file, char *psk_identity, char *psk);
		bool publish(char *topic, char *message);
		bool subscribe(char *topic, void (*callback)(char *topic, char* messa));
		bool loop();
		bool available();
		void close();

	private:
		void 			parseDataBuffer();
		FILE* 			spipe;
		char 			mqtt_broker[32];
		security_mode 	mode;
		char 			topicString[64];
		char 			certificate_file[64];
		char 			psk_identity[32];
		char 			psk_password[32];
		int 			serverPort;
		char 			*topic;
		char			*message;
		bool			retain_flag;
		void 			(*callback_function)(char* topic, char* message);
		char 			dataBuffer[256];
};
#endif /* MQTTCLIENT_H_ */
