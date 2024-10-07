#define BLYNK_TEMPLATE_ID "TMPL2K6_akL5L"
#define BLYNK_TEMPLATE_NAME "base"
#define BLYNK_AUTH_TOKEN "3GY2SWAkIDLYw9tuNt45FVNnhAk-ZzVK"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "AFRICA BROADCAST STORE";  // Your WiFi name
char pass[] = "1234567890";  // Your WiFi password

int relaypin = D1; // GPIO pin for relay control

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting Blynk...");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Blynk.config(auth);
  Blynk.connect();

  pinMode(relaypin, OUTPUT);
  digitalWrite(relaypin, LOW); // Ensure the relay is off initially
}

void loop()
{
  if (Blynk.connected()) {
    Blynk.run();
  } else {
    Serial.println("Blynk not connected");
  }
}

// Blynk virtual write function to control the relay
BLYNK_WRITE(V0) // Assuming V0 is the virtual pin connected to a button in the Blynk app
{
  int pinValue = param.asInt(); // Get the value from the Blynk app (0 or 1)
  digitalWrite(relaypin, pinValue);
  Serial.print("Relay state changed to: ");
  Serial.println(pinValue ? "ON" : "OFF");
}
