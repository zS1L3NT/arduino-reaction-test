#define LED_1 D1
#define LED_2 D2
#define LED_3 D0
#define LED_4 D4
#define LED_5 D8
#define BUTTON D5

int pressed = LOW;
int seqIndex = 4;
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

void runSeqIndex(int index)
{
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  digitalWrite(LED_5, LOW);

  switch (index)
  {
  case 0:
    digitalWrite(LED_1, HIGH);
    break;
  case 1:
  case 7:
    digitalWrite(LED_2, HIGH);
    break;
  case 2:
  case 6:
    digitalWrite(LED_3, HIGH);
    break;
  case 3:
  case 5:
    digitalWrite(LED_4, HIGH);
    break;
  case 4:
    digitalWrite(LED_5, HIGH);
    break;
  }
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
    if (digitalRead(BUTTON) == HIGH)
    {
      runSeqIndex(0);
      delay(500);

      runSeqIndex(1);
      delay(500);

      runSeqIndex(2);
      delay(500);

      runSeqIndex(3);
      delay(500);

      pressed = LOW;
      seqIndex = 4;
      iter = 0;
      maxIter = 10;
    }

    return;
  }

  // When just got to a new LED
  if (iter == 0)
  {
    runSeqIndex(seqIndex);
  }

  pressed = max(digitalRead(BUTTON), pressed);

  // When about to move to the next LED
  if (iter == maxIter)
  {
    if (pressed == HIGH)
    {
      // When the LED is Green
      if (seqIndex == 0)
      {
        maxIter--;
        delay(500);
      }
      else
      {
        maxIter = -1;
        lose();
      }

      return;
    }

    seqIndex++;
    if (seqIndex == 8)
      seqIndex = 0;

    iter = 0;
    pressed = LOW;
  }
  else
  {
    iter++;
  }

  if (maxIter == -1)
  {
    win();
  }

  delay(50);
}