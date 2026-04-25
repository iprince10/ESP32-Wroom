// ESP32 Soil Moisture Sensor — AO (GPIO34) + DO (GPIO35)
// GPIO34 and GPIO35 are both input-only ADC pins — perfect for this

const int AO_PIN     = 34;   // Analog output → continuous moisture value
const int DO_PIN     = 35;   // Digital output → HIGH = dry, LOW = wet (threshold via pot)

const int DRY_VALUE  = 3500; // Calibrate: raw ADC in completely dry air
const int WET_VALUE  = 1200; // Calibrate: raw ADC submerged in water

void setup() {
  Serial.begin(115200);
  pinMode(DO_PIN, INPUT);
  analogReadResolution(12);       // 12-bit ADC → 0 to 4095
  analogSetAttenuation(ADC_11db); // Full 0–3.3V range

  Serial.println("========================================");
  Serial.println("  ESP32 Soil Moisture Monitor");
  Serial.println("  AO = GPIO34  |  DO = GPIO35");
  Serial.println("========================================");
}

void loop() {
  // --- Analog read ---
  int raw      = analogRead(AO_PIN);
  int moisture = map(raw, DRY_VALUE, WET_VALUE, 0, 100);
  moisture     = constrain(moisture, 0, 100);

  // --- Digital read ---
  int doState  = digitalRead(DO_PIN);
  // Most sensors: LOW = soil is wet (crosses threshold), HIGH = soil is dry
  bool isWetDO = (doState == LOW);

  // --- Moisture label from AO ---
  String aoStatus;
  if      (moisture < 20) aoStatus = "DRY";
  else if (moisture < 60) aoStatus = "MOIST";
  else                    aoStatus = "WET";

  // --- Serial Monitor output ---
  Serial.println("----------------------------------------");
  Serial.print("Raw ADC     : "); Serial.println(raw);
  Serial.print("Moisture    : "); Serial.print(moisture); Serial.println(" %");
  Serial.print("AO Status   : "); Serial.println(aoStatus);
  Serial.print("DO Pin      : "); Serial.println(doState == LOW ? "LOW  (wet — threshold crossed)" : "HIGH (dry — below threshold)");
  Serial.print("DO Status   : "); Serial.println(isWetDO ? "WET" : "DRY");

  if (moisture < 20 && !isWetDO) {
    Serial.println(">> Both sensors agree: WATER YOUR PLANT!");
  } else if (isWetDO != (moisture >= 20)) {
    Serial.println(">> Note: AO and DO disagree — adjust pot on sensor.");
  }

  delay(1000);
}