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
