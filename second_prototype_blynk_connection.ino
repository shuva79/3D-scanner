// note: this shit works as I wanted to but for some reason anything beyond 1000 index causes a stack overflow
// this is most probably cause of the malloc that I used and gave it a size of 1000*size of float
// array isnt dynamically sized in c so it tends to happen
// I'll try to fix it in later iterations
// for now this works and that's that

// update: fixed the array thing by removing it :)
// Array stuff will be handled by matlab script

#include <Servo.h>           
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include "WiFiClient.h"    // to make http requests  update: this shit isnt required, remove it later thanks :)

WiFiClient client;

Servo myservo;
Servo myservo_2nd;

// for wifi connectivity

// WiFi parameters to be configured
const char* ssid = "5525";
const char* password = "7634Hy?6"; 

// for ultrasonic
const int trigPin = 12;
const int echoPin = 14;
int pos = 0;

// for data storage



// for thingspeak connection
unsigned long myChannelNumber = 2515968;
const char* myWriteAPIKey = "60CBR19VCSE0EVBY";

// depricated code not in use
const char* host = "api.thingspeak.com";
const char* hostPort = "80";
int thingspeak_counter = 0;

// for distances and ranges
float theta = 0.0; // Initial angle for theta // top to bottom
float phi;// left to right scan 
float dist;


//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200); // Starts the serial communication between the USB and node mcu
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  myservo.attach(2);  // connected to D4, GPIO pin 2 // left to right
  myservo_2nd.attach(0);  // connected to D3, GPIO pin 1

  // Connect to WiFi
   connectToWiFi();

  // Thingspeak setup
  ThingSpeak.begin(client);
}

void loop() {
  

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
  // Serial.print("Distance (cm): ");
  // Serial.println(distanceCm);
  // Serial.print("Distance (inch): ");
  // Serial.println(distanceInch);
  
  delay(1000);
  // this code adds to the delay


  // for (pos=0;pos<=180;pos++)
  // {
  //   myservo.write(pos);
  //   delay(50);
  // }

  // for (pos=180;pos>=0;pos--)
  // {
  //   myservo.write(pos);
  //   delay(50);
  // }

  while (theta <= 160.0 / 180.0) {
    
    theta += 1.0 / 180.0;
    for (phi = 1.0 / 180.0; phi <= 130.0 / 180.0; phi += 2.0 / 180.0) {
      myservo.write(map(phi * 180.0, 0, 180, 0, 180)); // Convert angle to servo position
      myservo_2nd.write(map(theta * 180.0, 0, 180, 0, 180)); // Convert angle to servo position
      delay(100); // Wait for servos to reach position
      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      
      // Calculate the distance
      distanceCm = duration * SOUND_VELOCITY/2;
      printData(distanceCm, phi, theta); // Store data in arrays
    }
    ThingSpeak.writeField(myChannelNumber, 1, distanceCm, myWriteAPIKey); // transfer the value to the cloud
     
    ThingSpeak.writeField(myChannelNumber, 2, phi, myWriteAPIKey);
    
    ThingSpeak.writeField(myChannelNumber, 3, theta, myWriteAPIKey);
    Serial.println("Coccblocc");
    theta += 1.0 / 180.0;
    for (phi = 130.0 / 180.0; phi >= 0.0; phi -= 2.0 / 180.0) {
      myservo.write(map(phi * 180.0, 0, 180, 0, 180)); // Convert angle to servo position
      myservo_2nd.write(map(theta * 180.0, 0, 180, 0, 180)); // Convert angle to servo position
      delay(100); // Wait for servos to reach position
      
      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      
      // Calculate the distance
      distanceCm = duration * SOUND_VELOCITY/2;
      
      printData(distanceCm, phi, theta); // Store data in arrays
      //printData(); // Print data to Serial Monitor

          
     

    }
  }
      // thingspeak
      
     
}



void printData(float distanceCm,float phi, float theta) {
    Serial.print(distanceCm);
    Serial.print(",");
    // // Serial.print(", Phi = ");
    Serial.print(phi);
    Serial.print(",");
    // // Serial.print(", Theta = ");
    Serial.println(theta);
}

void connectToWiFi() {
  //Connect to WiFi Network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to WiFi");
    Serial.println("...");
    WiFi.begin(ssid, password);
    int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 15)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  if (retries > 14) {
      Serial.println(F("WiFi connection FAILED"));
  }
  if (WiFi.status() == WL_CONNECTED) {
      Serial.println(F("WiFi connected!"));
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
  }
      Serial.println(F("Setup ready"));
}
