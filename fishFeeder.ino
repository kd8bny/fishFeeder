unsigned int feedDelay = 12;   //Number of hours to delay feed 
unsigned int feedTime = 500;  //run feeder for xms
unsigned int sec = 0;
unsigned int mins = 0;
unsigned int hour = 0;

const int ondemand =7;
const int feed = 8;
const int led = 13;

void setup(){
    Serial.begin(9600);
    Serial.println("Up and Running");

    pinMode(ondemand, OUTPUT);
    pinMode(feed, INPUT);
    pinMode(led, OUTPUT);

    //timer init 16' timer
    noInterrupts();
    TCCR1A = 0;
    TCCR1B = 0;
  
    TCCR1B |= (1 << CS12);      //256 prescaler ~approx 1s
    TIMSK1 |= (1 << TOIE1);     //Overflow flag
    interrupts();
}

ISR(TIMER1_OVF_vect){
    sec=sec+1;
    digitalWrite(led, !digitalRead(led));
    TCNT1 = 0;
}

void loop(){
  while(digitalRead(ondemand)){
    if(sec==60){
        mins=mins+1;
        sec=0;
    }
    if(mins==60){
        hour=hour+1;
        mins=0;
    }
    if(hour==feedDelay){
      digitalWrite(feed, HIGH);
      delay(feedTime);
      Serial.println("Fishes Fed!!");
      digitalWrite(feed, LOW);
      hour=0;
    }
  digitalWrite(feed, HIGH);
  delay(feedTime);
  Serial.println("Fishes Fed!!");
  digitalWrite(feed, LOW);
  }
}

