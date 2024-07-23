#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// BMP180
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

// DHT11
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// OLED Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// WiFi
const char* ssid = "Ohayooo";
const char* password = "09876543";

// ThingSpeak
unsigned long myChannelNumber = 2605084;
const char* myWriteAPIKey = "9J5TIMDGS32WDRTP";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  // BMP180
  if(!bmp.begin()) {
    Serial.print("Could not find a valid BMP180 sensor, check wiring!");
    while (1);
  }

  // DHT11
  dht.begin();

  // OLED Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(1);
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  // WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  sensors_event_t event;
  bmp.getEvent(&event);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float pressure = event.pressure;

  if (isnan(temperature) || isnan(humidity) || isnan(pressure)) {
    Serial.println("Failed to read from sensors!");
    return;
  }

  // Display data on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Temp: ");
  display.print(temperature);
  display.print(" C");
  display.setCursor(0,10);
  display.print("Humidity: ");
  display.print(humidity);
  display.print(" %");
  display.setCursor(0,20);
  display.print("Pressure: ");
  display.print(pressure);
  display.print(" hPa");
  display.display();

  // Send data to ThingSpeak
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, pressure);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  delay(20000); // Update every 20 seconds
}
