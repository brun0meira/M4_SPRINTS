int leds[4] = {4,5,6,7};
int button1 = 13;
int button2 = 14;
int buzzer = 8;
int armazenar[50] = {};
int aux = 0;
int ldr = 9;

void setup() {
  Serial.begin(115200);
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
  for(int i=0; i < 4; i++){
    pinMode(leds[i], OUTPUT);
  }
}

int leitura(){
  int valueLDR = analogRead(ldr);
  int convertido = map(valueLDR,32,4063,0,15);
  armazenar[aux] = convertido;
  aux += 1;
  Serial.println("Coversão:");
  Serial.println(convertido);
  Serial.println("Auxiliar");
  Serial.println(aux);
  return convertido;
}

void som(int convertido)
{
  tone(buzzer, (150 * convertido));
  delay(1000);
  noTone(buzzer);
}

void acendeLed(int convertido){
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(leds[i], (1 & convertido >> i));
  }
}

void loop() {
  if(digitalRead(button1) == 0){
    int lux = leitura();
    som(lux);
    acendeLed(lux);
  }
  if(digitalRead(button2) == 0){
    for (int i = 0; i <= aux; i++)
    {
      som(armazenar[i]);
      acendeLed(armazenar[i]);
      Serial.println(armazenar[i]);
      delay(1000);
    }
    armazenar[50] = {};
    aux = 0;
  }
}
