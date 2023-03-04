int data_pin = 11;
int clock_pin = 13;
int latch_pin = 12;
int transd1 = 3;
int transd2 = 4;
int transd3 = 5;
int transd4 = 6;
int a1325;
int ritardo = 50; //msec
int tempoEsec;
int cifra1, cifra2, cifra3, cifra4;
int digits [10][8]{
  {1,1,1,1,1,0,1,0}, // digit 0
  {0,1,1,0,0,0,0,0}, // digit 1
  {1,1,0,1,1,1,0,0}, // digit 2
  {1,1,1,1,0,1,0,0}, // digit 3
  {0,1,1,0,0,1,1,0}, // digit 4
  {1,0,1,1,0,1,1,0}, // digit 5
  {1,0,1,1,1,1,1,0}, // digit 6
  {1,1,1,0,0,0,0,0}, // digit 7
  {1,1,1,1,1,1,1,0}, // digit 8
  {1,1,1,1,0,1,1,0}  // digit 9
};
void mostraCifraSR(int cifra) {
  digitalWrite(latch_pin, LOW);
  for (int i = 7; i >= 0; i--) {
    digitalWrite(clock_pin, LOW);
    if (digits[cifra][i] == 0) {
      digitalWrite(data_pin, LOW);
    }
    if (digits[cifra][i] == 1) {
      digitalWrite(data_pin, HIGH);
    }
    digitalWrite(clock_pin, HIGH);
  }
  digitalWrite(latch_pin, HIGH);
}
void calcolaNumero4d(int numero) {
  if (numero > 0) {
    cifra4 = numero % 10; 
    numero = numero / 10; 
    if (numero > 0) {
      cifra3 = numero % 10;
      numero = numero / 10;
      if (numero > 0) {
        cifra2 = numero % 10;
        numero = numero / 10;
        if (numero > 0) {
          cifra1 = numero % 10;
        }
      }
    }
  }
}
void spegniTutto(){
  digitalWrite(transd1, HIGH);
  digitalWrite(transd2, HIGH);
  digitalWrite(transd3, HIGH);
  digitalWrite(transd4, HIGH);
}
void mostraCifre(){
  analogWrite(transd1, LOW);
  mostraCifraSR (cifra1);
  delay(ritardo);
  spegniTutto();
  delay(ritardo);
  analogWrite(transd2, LOW);
  mostraCifraSR (cifra2);
  delay(ritardo);
  spegniTutto();
  delay(ritardo);
  analogWrite(transd3, LOW);
  mostraCifraSR (cifra3);
  delay(ritardo);
  spegniTutto();
  delay(ritardo);
  analogWrite(transd4, LOW);
  mostraCifraSR (cifra4);
  delay(ritardo);
  spegniTutto();
  delay(ritardo);
}
void setup() {
  Serial.begin (9600);
  pinMode(data_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
  pinMode(transd1, OUTPUT);
  pinMode(transd2, OUTPUT);
  pinMode(transd3, OUTPUT);
  pinMode(transd4, OUTPUT);
  spegniTutto();
}

void loop() {
  cifra1 = 0; 
  cifra2 = 0;
  cifra3 = 0;
  cifra4 = 0;
  a1325 = 1325;
  Serial.println(a1325);
  calcolaNumero4d (a1325); 
  tempoEsec=millis();
  while((millis()-tempoEsec)<500){
    mostraCifre();
  }
}
