int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;

int temps = 3; // temps de luminescence retinienne

void allumer(int segment){
  digitalWrite(segment, HIGH);
  delay(temps);
  digitalWrite(segment, LOW);
}

void afficher(int n){
  int i;
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  //for(i=0;i<100;i++){
    if((n != 1) && (n != 4))
      allumer(a);
    if((n != 5) && (n != 6))
      allumer(b);
    if(n != 2)
      allumer(c);
    if((n != 1) && (n != 4) && (n != 7))
      allumer(d);
    if(((n % 2) == 0) && (n != 4))
      allumer(e);
    if((n > 3) && (n != 7) || (n == 0))
      allumer(f);
    if((n != 0) && (n != 1) && (n != 7))
      allumer(g);
  //}
}

void setup() {
  // put your setup code here, to run once:
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  //Serial.begin(9600);
}

void loop() {
  int i = 0;
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  //Serial.println(sensorValue);
  delay(1);
  int n = sensorValue * 9 / 800;
  //Serial.println(n);
  delay(1);
  afficher(n);
}
