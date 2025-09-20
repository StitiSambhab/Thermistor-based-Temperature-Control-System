#include <math.h>

const int ThermistorPin = A3;
const int LEDPin1 = 9;  // Green LED (20°C - 30°C)
const int LEDPin2 = 10; // Yellow LED (30°C - 40°C)
const int LEDPin3 = 11; // Red LED (40°C - 50°C)
const int FanPin = 5;   // PWM pin for controlling fan

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
  pinMode(LEDPin1, OUTPUT);
  pinMode(LEDPin2, OUTPUT);
  pinMode(LEDPin3, OUTPUT);
  pinMode(FanPin, OUTPUT);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

float calculateTemperature(int ADCvalue) {
  if (ADCvalue == 0) ADCvalue = 1;
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

    // Control LEDs
    digitalWrite(LEDPin1, LOW);
    digitalWrite(LEDPin2, LOW);
    digitalWrite(LEDPin3, LOW);
    if (averageTemperature >= 20 && averageTemperature < 30) {
      digitalWrite(LEDPin1, HIGH);
    } else if (averageTemperature >= 30 && averageTemperature < 40) {
      digitalWrite(LEDPin2, HIGH);
    } else if (averageTemperature >= 40 && averageTemperature <= 50) {
      digitalWrite(LEDPin3, HIGH);
    }

    // Fan speed control
    int pwmValue = map(averageTemperature, 20, 50, 0, 255);
    analogWrite(FanPin, pwmValue);

    Serial.print("Average Thermistor Temperature: ");
    Serial.print(averageTemperature);
    Serial.println(" C");
  } else {
    Serial.println("Invalid thermistor reading.");
  }
  delay(1000);
}
