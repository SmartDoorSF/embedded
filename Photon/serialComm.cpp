/**
 * Particle Photon WebIDE version
 * with internal linked libraries
 * Code is not executable for GCC-ARM toolchain
 */
/* My own utility function  -------------------------------------------------*/
int listeningKey(int pin);
bool debounce(int pin);
void servoDrive(void);
/* Global status variable   -------------------------------------------------*/
bool D7Status;
bool D6Status;

Servo myservo;
int pos = 0;

IPAddress localIP;
char addr[16];

TCPServer Server(80);
TCPClient Client;
// byte server[] = { 74, 125, 224, 72 }; // google
byte server[] = {10, 0, 0, 20};
/* This function is called once at start up ----------------------------------*/
void setup()
{
	  //Setup the Tinker application here
    pinMode(D7, OUTPUT);
    pinMode(D6, INPUT);
    D7Status = LOW;
    D6Status = LOW;
    
    // Use the pins that has PWM on the Photon: 
    // D0, D1, D2, D3, A4, A5, WKP, RX, and TX
    myservo.attach(D0);
    
    // TCPIP
    localIP = WiFi.localIP();
    Server.begin();
    
    // Serial
    // Serial.begin(9600);
    
    while(!Serial.available()) { Particle.process(); }
    Serial.println("Connecting... with IP:");
    Serial.println(localIP);
    
    // if (Client.connect(server, 80))
    if (Client.connect(server, 8000))
    {
        Serial.println("connected");
        Client.println("GET /search?q=unicorn HTTP/1.0");
        Client.println("Host: www.google.com");
        Client.println("Content-Length: 0");
        Client.println();
    }
    else
    {
        Serial.println("connection failed");
    }
	//Register all the Tinker functions
	Particle.function("digitalread", tinkerDigitalRead);
	Particle.function("digitalwrite", tinkerDigitalWrite);
	Particle.function("analogread", tinkerAnalogRead);
	Particle.function("analogwrite", tinkerAnalogWrite);
}

/* This function loops forever --------------------------------------------*/
void loop()
{
	//This will run in a loop
	
    listeningKey(D6);
    
    if (Client.available())
    {
        char c = Client.read();
        Serial.print(c);
    }

    if (!Client.connected())
    {
        Serial.println();
        Serial.println("disconnecting.");
        Client.stop();
        for(;;);
    }
    // servoDrive();
    // Serial.println(myIP);
}

/*******************************************************************************
 * Function Name  : servoDrive
 * Description    : Listen native key input
 * Input          : Pin
 * Output         : None.
 * Return         : Value of the pin (0 or 1) in INT type
                    Returns a negative number on failure
 *******************************************************************************/
 void servoDrive()
 {
    // for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees
    // {                                  // in steps of 1 degree
    //     myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //     delay(15);                       // waits 15ms for the servo to reach the position
    // }
    // for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
    // {
    //     myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //     delay(15);                       // waits 15ms for the servo to reach the position
    // }
 }

/*******************************************************************************
 * Function Name  : listeningKey
 * Description    : Listen native key input
 * Input          : Pin
 * Output         : None.
 * Return         : Value of the pin (0 or 1) in INT type
                    Returns a negative number on failure
 *******************************************************************************/
int listeningKey(int pin)
{
    // bool inputStatus = digitalRead(pin);
    if (debounce(pin)) {
        D7Status = !D7Status;
    }
    digitalWrite(D7, D7Status);
}

/*******************************************************************************
 * Function Name  : debounce
 * Description    : Software key debounce
 * Input          : Pin
 * Output         : None.
 * Return         : Value of the pin (0 or 1) in INT type
                    Returns a negative number on faliure
 *******************************************************************************/
 bool debounce(int pin) 
 {
    bool newStatus = digitalRead(pin);
    if (newStatus == HIGH) {
        return false;
    }
    delay(100);
    newStatus = digitalRead(pin); 
    if (newStatus != HIGH) {
        return false;
    }
    return true;
 }

/*******************************************************************************
 * Function Name  : tinkerDigitalRead
 * Description    : Reads the digital value of a given pin
 * Input          : Pin
 * Output         : None.
 * Return         : Value of the pin (0 or 1) in INT type
 Returns a negative number on failure
 *******************************************************************************/
int tinkerDigitalRead(String pin)
{
    //convert ascii to integer
    int pinNumber = pin.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits
    if (pinNumber< 0 || pinNumber >7) return -1;
    
    if(pin.startsWith("D"))
    {
        pinMode(pinNumber, INPUT_PULLDOWN);
        return digitalRead(pinNumber);
    }
    else if (pin.startsWith("A"))
    {
        pinMode(pinNumber+10, INPUT_PULLDOWN);
        return digitalRead(pinNumber+10);
    }
    return -2;
}

/*******************************************************************************
 * Function Name  : tinkerDigitalWrite
 * Description    : Sets the specified pin HIGH or LOW
 * Input          : Pin and value
 * Output         : None.
 * Return         : 1 on success and a negative number on failure
 *******************************************************************************/
int tinkerDigitalWrite(String command)
{
    bool value = 0;
    //convert ascii to integer
    int pinNumber = command.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits
    if (pinNumber< 0 || pinNumber >7) return -1;
    
    if(command.substring(3,7) == "HIGH") value = 1;
    else if(command.substring(3,6) == "LOW") value = 0;
    else return -2;
    
    if(command.startsWith("D"))
    {
        pinMode(pinNumber, OUTPUT);
        digitalWrite(pinNumber, value);
        return 1;
    }
    else if(command.startsWith("A"))
    {
        pinMode(pinNumber+10, OUTPUT);
        digitalWrite(pinNumber+10, value);
        return 1;
    }
    else return -3;
}

/*******************************************************************************
 * Function Name  : tinkerAnalogRead
 * Description    : Reads the analog value of a pin
 * Input          : Pin
 * Output         : None.
 * Return         : Returns the analog value in INT type (0 to 4095)
 Returns a negative number on failure
 *******************************************************************************/
int tinkerAnalogRead(String pin)
{
    //convert ascii to integer
    int pinNumber = pin.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits
    if (pinNumber< 0 || pinNumber >7) return -1;
    
    if(pin.startsWith("D"))
    {
        return -3;
    }
    else if (pin.startsWith("A"))
    {
        return analogRead(pinNumber+10);
    }
    return -2;
}

/*******************************************************************************
 * Function Name  : tinkerAnalogWrite
 * Description    : Writes an analog value (PWM) to the specified pin
 * Input          : Pin and Value (0 to 255)
 * Output         : None.
 * Return         : 1 on success and a negative number on failure
 *******************************************************************************/
int tinkerAnalogWrite(String command)
{
    //convert ascii to integer
    int pinNumber = command.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits
    if (pinNumber< 0 || pinNumber >7) return -1;
    
    String value = command.substring(3);
    
    if(command.startsWith("D"))
    {
        pinMode(pinNumber, OUTPUT);
        analogWrite(pinNumber, value.toInt());
        return 1;
    }
    else if(command.startsWith("A"))
    {
        pinMode(pinNumber+10, OUTPUT);
        analogWrite(pinNumber+10, value.toInt());
        return 1;
    }
    else return -2;
}
