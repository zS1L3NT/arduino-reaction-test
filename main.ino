#define LED_1 D1
#define LED_2 D2
#define LED_3 D0
#define LED_4 D4
#define LED_5 D8
#define BUTTON D5

int pressed = LOW;
int led = 5;
int iter = 0;
int maxIter = 10;

void setup()
{
  Serial.begin(9600);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void lose()
{
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  digitalWrite(LED_5, LOW);
  delay(500);

  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    delay(500);

    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    delay(500);
  }
}

void win()
{
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  digitalWrite(LED_5, LOW);
  delay(500);

  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED_1, HIGH);
    delay(500);

    digitalWrite(LED_1, LOW);
    delay(500);
  }
}

void loop()
{
  if (maxIter == -1)
  {
    if (digitalRead(BUTTON) == HIGH) {
      digitalWrite(LED_1, HIGH);
      delay(500);
      
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, HIGH);
      delay(500);
      
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, HIGH);
      delay(500);
      
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, HIGH);
      delay(500);
      
      digitalWrite(LED_4, LOW);

      pressed = LOW;
      led = 5;
      iter = 0;
      maxIter = 10;
    }

    return;
  }

  // When just got to a new LED
  if (iter == 0)
  {
    switch (led)
    {
    case 5:
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_5, HIGH);
      break;
    case 4:
      digitalWrite(LED_5, LOW);
      digitalWrite(LED_4, HIGH);
      break;
    case 3:
      digitalWrite(LED_4, LOW);
      digitalWrite(LED_3, HIGH);
      break;
    case 2:
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_2, HIGH);
      break;
    case 1:
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_1, HIGH);
      break;
    }
  }

  pressed = max(digitalRead(BUTTON), pressed);

  // When about to move to the next LED
  if (iter == maxIter)
  {
    // When the LED is Green
    if (led == 1)
    {
      led = 5;
      maxIter--;

      if (pressed == LOW)
      {
        maxIter = -1;
        lose();
        return;
      }

      delay(500);
    }
    else
    {
      led--;

      if (pressed == HIGH)
      {
        maxIter = -1;
        lose();
        return;
      }
    }
    iter = 0;
    pressed = LOW;
  }
  else
  {
    iter++;
  }

  if (maxIter == -1) {
    win();
  }

  delay(50);
}