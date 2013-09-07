int ledPin = 13;
volatile char hitflag=0;
long hittime=0;
int irbuffbits;
int irbuffbit;
long irbitstarttime;
char irbuff[4];
void setup() {                
  TCCR2A = _BV(WGM21) | _BV(COM2A0);
  TCCR2B = _BV(CS20);
  OCR2A = (F_CPU/(38000*2L)-1);
  pinMode(11, OUTPUT); 
  attachInterrupt(0, exinterupt, FALLING);
  Serial.begin(9600);
}

void startblink()
{
    hittime=millis();
    digitalWrite(ledPin, HIGH);
    Serial.println("hit");
    hitflag=2;
}
void endblink()
{
    digitalWrite(ledPin, LOW);
    Serial.println("unhit");
    hitflag=0;
}
void sendirbits()
{
  if(millis()%1000 == 0)
    TCCR2B = 0;
  if(millis()%1000 == 500)
    TCCR2B = _BV(CS20);
}
void loop() {
  if(hitflag==1)
      startblink();
  if(millis()-hittime>400 && hitflag==2)
     endblink();
   sendirbits();   
}
void exinterupt() 
{
  hitflag=1;
}
