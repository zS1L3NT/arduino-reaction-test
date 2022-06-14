#define LED_1 D1
#define LED_2 D2
#define LED_3 D0
#define LED_4 D4
#define LED_5 D8
#define BUTTON D5

#define MIN_ITERS 5
#define MAX_ITERS 10
#define LOOP_DELAY 20

int pressed = LOW;
int seqIndex = 4;

int iter = 0;
int totalIters = MAX_ITERS;

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
  delay(MAX_ITERS * LOOP_DELAY);

  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    delay(MAX_ITERS * LOOP_DELAY);

    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    delay(MAX_ITERS * LOOP_DELAY);
  }
}

void win()
{
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  digitalWrite(LED_5, LOW);
  delay(MAX_ITERS * LOOP_DELAY);

  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED_1, HIGH);
    delay(MAX_ITERS * LOOP_DELAY);

    digitalWrite(LED_1, LOW);
    delay(MAX_ITERS * LOOP_DELAY);
  }
}

void loop()
{
  if (totalIters == MIN_ITERS)
  {
    if (digitalRead(BUTTON) == HIGH)
    {
      for (int i = 0; i < 4; i++)
      {
        runSeqIndex(i);
        delay(MAX_ITERS * LOOP_DELAY);
      }

      pressed = LOW;
      seqIndex = 4;
      iter = 0;
      totalIters = MAX_ITERS;
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
  if (iter == totalIters)
  {
    if (pressed == HIGH)
    {
      // When the LED is Green
      if (seqIndex == 0)
      {
        totalIters--;
        iter = 0;
        delay(MAX_ITERS * LOOP_DELAY);
      }
      else
      {
        totalIters = MIN_ITERS;
        lose();
        return;
      }
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

  if (totalIters == MIN_ITERS)
  {
    win();
  }

  delay(LOOP_DELAY);
}