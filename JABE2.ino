// Version 1.1

////////////////////
// USER INTERFACE //
////////////////////

// Set the length of measurement and flush phases (in seconds)
int FLUSH = 180;       // 4 minutes (pumps ON)
int MEASUREMENT = 48; // 15 minutes (pumps OFF)

/////////////////////////
// IMPLEMENTATION CODE //
/////////////////////////

int LED = 13;

int RELAY1 = 3;
int RELAY2 = 4;
int RELAY3 = 5;
int RELAY4 = 6;

int PERIOD = 1;

void setup()
{
   pinMode(RELAY1, OUTPUT);
   pinMode(RELAY2, OUTPUT);
   pinMode(RELAY3, OUTPUT);
   pinMode(RELAY4, OUTPUT);
   pinMode(LED, OUTPUT);  
   Serial.begin(9600);
   Serial.println("CLEARRANGE,A,2,E,1000000"); // to get rid of AM-PM
   Serial.println((String) "LABEL, Date,Time,Phase,Millis");
}

void loop()
{
   // FLUSH Phase: Pumps ON (relays OFF)
   digitalWrite(RELAY1, HIGH);
   digitalWrite(RELAY2, HIGH); 
   digitalWrite(RELAY3, HIGH); 
   digitalWrite(RELAY4, HIGH); 

   for (int counter = 0; counter < FLUSH; counter++) {
      Serial.println((String) "DATA,DATE,TIME," + "F" + PERIOD + "," + millis());
      digitalWrite(LED, HIGH);
      delay(5000); // 1 second delay
   }

   // MEASUREMENT Phase: Pumps OFF (relays ON)
   digitalWrite(RELAY1, LOW); 
   digitalWrite(RELAY2, LOW);
   digitalWrite(RELAY3, LOW);
   digitalWrite(RELAY4, LOW); 

   for (int counter = 0; counter < MEASUREMENT; counter++) {
      Serial.println((String) "DATA,DATE,TIME," + "M" + PERIOD + "," + millis());
      digitalWrite(LED, HIGH);
      delay(1000);
      digitalWrite(LED, LOW);
      delay(1000); // total 1 second per loop
      digitalWrite(LED, HIGH);
      delay(1000);
      digitalWrite(LED, LOW);
      delay(2000);
   }

   PERIOD++;
}
