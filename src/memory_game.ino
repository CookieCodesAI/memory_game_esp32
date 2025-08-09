#include <Wire.h>
#include <Adafruit_MPR121.h>
#include <vector>
#include <random>

Adafruit_MPR121 cap = Adafruit_MPR121();
std::vector<int> lights;
String gameStatus;
const int bluepin = 23;
const int redpin = 19;
const int greenpin = 18; 
const int yellowpin = 5;
const int rightanswer = 15;
const int wronganswer = 2;
const int spamLimit = 3;   
int playerIndex = 0;          
int ledpins[4] = {bluepin, redpin, greenpin, yellowpin};   
const unsigned long cooldownTime = 2000; 

int touchCount[12] = {0};
unsigned long lastTouchTime[12] = {0};
bool lastTouched[12] = {false};
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 3);
std::random_device rd;

void flashLED(int pin){
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(1000);
}

String setGame(){
  lights.clear();
  for (int i = 0; i < 5; i++){
    int randomNumber = distribution(generator);
    lights.push_back(randomNumber);
  }
  Serial.println("The Sequence is");
  for (int val : lights) {
    Serial.print(val);
    Serial.print(" ");
  }
  Serial.println();
  gameStatus = "Flash Pattern";
  return gameStatus;
}

String flashPattern(){
  for (int i = 0; i< 5; i++){
    int pin = ledpins[lights[i]];
    flashLED(pin);
  }
  gameStatus = "User Input";
  return gameStatus;
}

String userInput(){
  uint16_t touched = cap.touched();
  unsigned long now = millis();
  for (int i = 0; i <= 3; i++) {
    bool isTouched = touched & (1 << i);

    if (isTouched && !lastTouched[i]) {
      if (touchCount[i] < spamLimit) {
        if (i == lights[playerIndex]) {
          flashLED(ledpins[i]); 
          Serial.print("Correct! Index: ");
          Serial.println(playerIndex);
          playerIndex++;

          if (playerIndex >= lights.size()) {
            flashLED(rightanswer);
            gameStatus = "Setting Up Game";
            playerIndex = 0;
            return gameStatus;
          }
        } 
        else {
          flashLED(ledpins[i]); 
          Serial.println("Wrong! Game Over");
          flashLED(wronganswer);
          gameStatus = "Game Over";
          playerIndex = 0;
          return gameStatus;
        }

        touchCount[i]++;
        lastTouchTime[i] = now;
      }
    }

    if (!isTouched && (now - lastTouchTime[i] > cooldownTime)) {
      touchCount[i] = 0;
    }

    lastTouched[i] = isTouched;
  }
  return gameStatus;
}

String gameOver(){
  Serial.println("You lost");
  gameStatus = "Setting Up Game";
  return gameStatus;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA and SCL pins respectively
  Wire.setClock(1000000);
  generator.seed(rd());
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(yellowpin, OUTPUT);
  pinMode(rightanswer, OUTPUT);
  pinMode(wronganswer, OUTPUT);
  while (!Serial);

  if (!cap.begin(0x5A, &Wire)) {
    Serial.println("MPR121 not found");
    while (1);
  }

  Serial.println("MPR121 found!");
  cap.setThresholds(0, 0); 
  gameStatus = "Setting Up Game";
}

void loop() {
  if (gameStatus == "Setting Up Game"){
    setGame();
  }
  else if (gameStatus == "Flash Pattern"){
    flashPattern();
  }
  else if (gameStatus == "User Input"){
    userInput();
  }
  else if (gameStatus == "Game Over"){
    gameOver();
  }
}

