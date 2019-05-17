int anodPins[] = {A1, A2, A3, A4}; // Задаем пины для кажого разряда
int segmentsPins[] = {5, 6, 7, 8, 9, 10, 11, 12}; //Задаем пины для каждого сегмента (из 7 + 1(точка))
                   //{A, B, C, D, E, F,  G,  DP} - распиновка сегментов

unsigned long lastTime = 0;
int globalDigits[4] = {0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < 4; i++) {
    pinMode(anodPins[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(segmentsPins[i], OUTPUT);
  }
}

int seg[11][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, //Цифра 0
  {0, 1, 1, 0, 0, 0, 0, 0}, //Цифра 1
  {1, 1, 0, 1, 1, 0, 1, 0}, //Цифра 2
  {1, 1, 1, 1, 0, 0, 1, 0}, //Цифра 3
  {0, 1, 1, 0, 0, 1, 1, 0}, //Цифра 4
  {1, 0, 1, 1, 0, 1, 1, 0}, //Цифра 5
  {1, 0, 1, 1, 1, 1, 1, 0}, //Цифра 6
  {1, 1, 1, 0, 0, 0, 0, 0}, //Цифра 7
  {1, 1, 1, 1, 1, 1, 1, 0}, //Цифра 8
  {1, 1, 1, 1, 0, 1, 1, 0}, //Цифра 9
  {0, 0, 0, 0, 0, 0, 0, 1}  //Точка
};

int t = 0;
int digid = 0;

void loop() {
  if (millis() - lastTime > 1000) {
    timeSort(millis() / 1000);
    lastTime = millis();
  }
  
  t += 1;
  if (t > 9999) t = 0;
  if ((t % 1000) == 0) {
    digid = t / 1000; //Каждую секунду отображаем цифры подряд
  }
  for (int i = 0; i < 4; i++) { // Каждый разряд по очереди
    for (int k = 0; k < 8; k++) {// Каждый сегмент по очереди - исходя из заданной карты
      digitalWrite(segmentsPins[k], ((seg[globalDigits[i]][k] == 1) ? HIGH : LOW));
    }
    
    digitalWrite(segmentsPins[7], ((i == 1) ? HIGH : LOW));
    digitalWrite(anodPins[i], LOW);
    delay(1); 
    digitalWrite(anodPins[i], HIGH); 
  }
}

void timeSort(int secs) {
  //int hours = secs / 3600;
  int minutes = secs % 3600 / 60;
  int seconds = secs % 3600 % 60;

  Serial.print("minutes: ");
  Serial.println(minutes);
  Serial.print("seconds: ");
  Serial.println(seconds);
  
  sortedTimeToDigits(seconds, minutes);
}

void sortedTimeToDigits(int seconds, int minutes) {
  int digits[4] = {0, 0, 0, 0};
   
  if (seconds / 10 > 0) {
    digits[2] = seconds / 10;
  }
  digits[3] = seconds % 10;
   
  if (minutes / 10 > 0) {
    digits[0] = minutes / 10;
  }
  digits[1] = minutes % 10;

  Serial.print(digits[0]);    Serial.print(", ");
  Serial.print(digits[1]);    Serial.print(", ");
  Serial.print(digits[2]);    Serial.print(", ");
  Serial.println(digits[3]);  Serial.println();

  globalDigits[0] = digits[0];
  globalDigits[1] = digits[1];
  globalDigits[2] = digits[2];
  globalDigits[3] = digits[3];
}
