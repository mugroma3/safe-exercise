enum StatiCassaforte {ROSSO, VERDE, BLU};
enum StatiManopola {UNO, DUE, TRE, QUATTRO};
StatiCassaforte stato = ROSSO;
StatiManopola manopola = UNO;

int pinPotenziometro = A0;
int pinRosso = 7;
int pinVerde = 8;
int pinBlu = 9;

int pinBuzzer = 6;
int pinBottone = 10;
boolean premuto = false;

void setup() {
  pinMode(pinRosso, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinBlu, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinBottone, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {


  StatiManopola newManopola = aggiornaManopola(analogRead(pinPotenziometro));

  if (newManopola != manopola)
    tone(pinBuzzer, 700, 50);
  manopola = newManopola;
  Serial.println(analogRead(pinPotenziometro));
  switch (stato)
  {
    case ROSSO:
      digitalWrite(pinRosso, HIGH);
      digitalWrite(pinVerde, LOW);
      digitalWrite(pinBlu, LOW);
      if (leggi_bottone())
      {
        if (manopola == TRE)
          stato = VERDE;
      }


      break;
      
    case VERDE:
      digitalWrite(pinRosso, LOW);
      digitalWrite(pinVerde, HIGH);
      digitalWrite(pinBlu, LOW);
      if (leggi_bottone())
      {
        if (manopola == UNO)
          stato = BLU;
        else
          stato = ROSSO;
      }
      break;
      
    case BLU:
      digitalWrite(pinRosso, LOW);
      digitalWrite(pinVerde, LOW);
      digitalWrite(pinBlu, HIGH);
      if (leggi_bottone())
      {
        if (manopola == QUATTRO)
        {
          stato = ROSSO;
          youWin();
        }
        else
          stato = ROSSO;
      }
      break;
      
    default:
      Serial.println("Se sei entrato qui è successo qualcosa di molto strano");
      break;
  }
  delay(50);
}

StatiManopola aggiornaManopola(int potenz)
{
  if (potenz < 256)
    return UNO;
  if (potenz < 512)
    return DUE;
  if (potenz < 768)
    return TRE;
  return QUATTRO;
}

boolean leggi_bottone()
{

  if (digitalRead(pinBottone) == LOW)
  {
    if (!premuto)
    {
      premuto = true;
      tone(pinBuzzer, 200, 50);
      return true;
    }
  }
  else
  {
    premuto = false;
  }

  return false;
}

void youWin()
{
  tone(pinBuzzer, 700);
  digitalWrite(pinBlu, LOW);
  digitalWrite(pinRosso, HIGH);
  delay(550);
  tone(pinBuzzer, 860);
  digitalWrite(pinVerde, HIGH);
  digitalWrite(pinRosso, LOW);
  delay(550);
  tone(pinBuzzer, 900);
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinBlu, HIGH);
  delay(1580);
  noTone(pinBuzzer);
}

