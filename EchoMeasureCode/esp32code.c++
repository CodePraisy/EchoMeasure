#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN 5
#define ECHO_PIN 6
#define BUZZER_PIN 10

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// inital settings on launch
int RefreshRate = 50;
int TrigDistance = 20;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Wire.begin(18, 46);  // SDA=18, SCL=46
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (1) {}
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
}

void loop() {
  // Read distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 40000);
  
  display.clearDisplay();
  display.setCursor(0, 0);

  if (duration == 0) {
    display.setTextSize(1);
    display.println("OUT OF RANGE");
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    float distance = (duration * 0.0343) / 2;

    display.setTextSize(2);
    display.println("Distance:");
    display.setTextSize(3);
    
    if (distance < 100) {
      display.print(distance, 1);
      display.println(" cm");      
    } else {
      display.println(distance, 1);
      display.print("cm");
    }
    
    if (distance < TrigDistance) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(RefreshRate / 2);
      digitalWrite(BUZZER_PIN, LOW);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
      delay(RefreshRate / 2);
    }
  }

  display.display();
  delay(RefreshRate / 2);
}