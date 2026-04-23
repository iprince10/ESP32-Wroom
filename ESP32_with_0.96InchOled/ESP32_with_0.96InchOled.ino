#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1        // No reset pin on most modules
#define OLED_ADDRESS  0x3C      // Change to 0x3D if not working

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA=GPIO21, SCL=GPIO22

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED not found! Check wiring or address.");
    while (true); // Stop here if OLED not detected
  }

  display.clearDisplay();

  // Line 1 — Normal size text
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello, Prince!");

  // Line 2 — Bigger text
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println("ESP32");

  // Line 3 — Normal size
  display.setTextSize(1);
  display.setCursor(0, 50);
  display.println("OLED Working OK!");

  display.display(); // Push to screen — required!
}

void loop() {
}
