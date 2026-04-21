#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

// DHT settings
#define DHTPIN 4
#define DHTTYPE DHT11

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL

  // Init OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED not found!");
    while (true);
  }

  // Init DHT
  dht.begin();

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 16);
  display.println("Hii Prince :)");
  display.println("System Ready");
  display.display();
  delay(2000);
}

void loop() {
  float temperature = dht.readTemperature(); // Celsius
  float humidity    = dht.readHumidity();

  // Check if reading failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 read failed!");
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 25);
    display.println("  Sensor Error!");
    display.display();
    
    delay(2000);
    return;
  }

  // Print to Serial Monitor
  Serial.print("Temp: "); Serial.print(temperature); Serial.println(" C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");

  // Display on OLED
  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.println("DHT11 Monitor");

  // Divider line
  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  // Temperature
  display.setTextSize(1);
  display.setCursor(0, 16);
  display.println("Temperature:");
  display.setTextSize(2);
  display.setCursor(0, 26);
  display.print(temperature, 2); // 2 decimal place
  display.println(" C");

  // Humidity
  display.setTextSize(1);
  display.setCursor(0, 48);
  display.println("Humidity:");
  display.setTextSize(2);  
  display.setCursor(60, 48);
  display.print(humidity, 0);
  display.println("%");

  display.display();
  delay(2000); // Update every 2 seconds
}