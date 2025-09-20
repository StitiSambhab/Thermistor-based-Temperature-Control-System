const int ThermistorPin = A3;
const float SeriesResistor = 10000;
const float ThermistorNominal = 10000;
const float TemperatureNominal = 25;
const float BValue = 3950;
const float KelvinConversion = 273.15;
const int numReadings = 10;

int readingsIndex = 0;
float readingsSum = 0;
float readings[numReadings];
bool firstCycle = true;

void setup() {
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

// Function to calculate temperature from ADC value
float calculateTemperature(int ADCvalue) {
  float Resistance = SeriesResistor / ((1023.0 / ADCvalue) - 1);
  float Steinhart = Resistance / ThermistorNominal;
  Steinhart = log(Steinhart);
  Steinhart /= BValue;
  Steinhart += 1.0 / (TemperatureNominal + KelvinConversion);
  Steinhart = 1.0 / Steinhart;
  return Steinhart - KelvinConversion;
}

void loop() {
  int ADCvalue = analogRead(ThermistorPin);
  if (ADCvalue > 0) {
    float temperature = calculateTemperature(ADCvalue);
    readingsSum -= readings[readingsIndex];
    readings[readingsIndex] = temperature;
    readingsSum += readings[readingsIndex];
    readingsIndex++;
    if (readingsIndex >= numReadings) {
      readingsIndex = 0;
      firstCycle = false;
    }
    float averageTemperature = readingsSum / (firstCycle ? (readingsIndex + 1) : numReadings);
    Serial.print("Average Thermistor Temperature: ");
    Serial.print(averageTemperature);
    Serial.println(" C");
  } else {
    Serial.println("Invalid thermistor reading.");
  }
  delay(1000);
}
