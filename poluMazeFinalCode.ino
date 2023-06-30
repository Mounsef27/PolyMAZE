#define RM1 6
#define RM2 5
#define LM1 7
#define LM2 8
#define LLL 4
#define LL A3
#define L A2
#define C A4
#define R A1
#define RR A0
#define RRR 12
#define PMWR 9
#define PMWL 3
#define PushButton 2
int R1,R2,L1,L2,x,y,left,right,center,IRR,IR,ILL,IL;
int mn0=1023;
int mx0=0;
int mn1=1023;
int mx1=0;
int mn2=1023;
int mx2=0;
int mn3=1023;
int mx3=0;
int i,x0,x1,x2,x3;
int N=20;
float Vin ; 
int x_pr=0;

float filtre(int A){
  float sum=0,R;
  for(i=0;i<N;i++){
    sum+=analogRead(A);
  }
  R=sum/20;
  return R ;
  
  }

  
void setup() {
pinMode(LM1,OUTPUT);
pinMode(LM2,OUTPUT);
pinMode(RM1,OUTPUT);
pinMode(RM2,OUTPUT);
pinMode(PMWR,OUTPUT);
pinMode(PMWL,OUTPUT);
pinMode(LLL,INPUT);
pinMode(LL,INPUT);
pinMode(L,INPUT);
pinMode(C,INPUT);
pinMode(R,INPUT);
pinMode(RR,INPUT);
pinMode(RRR,INPUT);
pinMode(PushButton,INPUT);
Serial.begin(9600);
    while(millis()<7000){
    x0=filtre(A0);
    x1=filtre(A1);
    x2=filtre(A2);
    x3=filtre(A3);
    
    mx0=max(mx0,x0);
    mn0=min(mn0,x0);
    mx1=max(mx1,x1);
    mn1=min(mn1,x1);
    mx2=max(mx2,x2);
    mn2=min(mn2,x2);
    mx3=max(mx3,x3);
    mn3=min(mn3,x3);
  }
}

char path[100] = "";
unsigned char path_length = 0; // the length of the path
void simplify_path()
{
  // only simplify the path if the second-to-last turn was a 'B'
  if(path_length < 3 || path[path_length-2] != 'B')
    return;

  int total_angle = 0;
  int i;
  for(i=1;i<=3;i++)
  {
    switch(path[path_length-i])
    {
      case 'R':
        total_angle += 90;
  break;
      case 'L':
  total_angle += 270;
  break;
      case 'B':
  total_angle += 180;
  break;
    }
  }

  // Get the angle as a number between 0 and 360 degrees.
  total_angle = total_angle % 360;

  // Replace all of those turns with a single one.
  switch(total_angle)
  {
    case 0:
  path[path_length - 3] = 'S';
  break;
    case 90:
  path[path_length - 3] = 'R';
  break;
    case 180:
  path[path_length - 3] = 'B';
  break;
    case 270:
  path[path_length - 3] = 'L';
  break;
  }

  // The path is now two steps shorter.
  path_length -= 2;
  
} // end simplify_path

char select_turn(unsigned char found_left, unsigned char found_straight, unsigned char found_right)
{
  if(found_left)
    return 'L';
  else if(found_straight)
    return 'S';
  else if(found_right)
    return 'R';
  else
    return 'B';
}

void loop() {
mazeSolve();
}

void stop(){
digitalWrite(LM1,LOW);
digitalWrite(LM2,LOW);
digitalWrite(RM1,LOW);
digitalWrite(RM2,LOW);
}


void turn(char dir)
{
  switch(dir)
  {
    case 'L':    
       turn_left();
       stop();      
    break;
    
    case 'R':        
       turn_right();
       stop();      
    break;
    
    case 'B':    
      back();
      stop();         
    break;

    case 'S':
    break;
  }} 


void speed(){
int Kp=1.2,Kd=0.08;
x=(2*ILL+0.8*IL)-(2*IRR+0.8*IR);
y=Kp*x+Kd*(x-x_pr);
x_pr=x;
Vin=map(y,-200,200,-50,50);
digitalWrite(LM1,HIGH);
digitalWrite(LM2,LOW);
digitalWrite(RM1,HIGH);
digitalWrite(RM2,LOW);
analogWrite(PMWR,100-Vin);
analogWrite(PMWL,100+Vin);
}
void turn_left() {
    delay(60);
    stop();
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(PMWR, 80);
    analogWrite(PMWL, 80);
    delay(50);

    while (analogRead(A3) < mn3 + 30) {
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PMWR, 125);
      analogWrite(PMWL, 90);
    }

    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(PMWR, 80);
    analogWrite(PMWL, 80);
    delay(50);
  }
}

void turn_right() {
  
    delay(60);
    stop();
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(PMWR, 80);
    analogWrite(PMWL, 80);
    delay(50);

    while (analogRead(A0) < mn0 + 30) {
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PMWL, 125);
      analogWrite(PMWR, 90);
    }
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    analogWrite(PMWR, 80);
    analogWrite(PMWL, 80);
    delay(50);
  }
}


void back() {
 
    stop();
    delay(100);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    analogWrite(PMWR, 80);
    analogWrite(PMWL, 100);
    delay(100);

    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    analogWrite(PMWR, 100);
    analogWrite(PMWL, 100);
    delay(50);
    while ((analogRead(A0) < 100)) {
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PMWL, 105);
      analogWrite(PMWR, 105);
    }


    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    analogWrite(PMWL, 95);
    analogWrite(PMWR, 95);

    delay(100);
    stop();
  //}
}



void readSensors(){
L2=analogRead(LL);
ILL=map(L2,mn3,mx3,0,100);
L1 =analogRead(L);
IL=map(L1,mn2,mx2,0,100);
R1=analogRead(R);
IR=map(R1,mn1,mx1,0,100);
R2=analogRead(RR);
IRR=map(R2,mn0,mx0,0,100);
}
void readMap(){
left=digitalRead(LLL);
right=digitalRead(RRR);
center=analogRead(C);  
}
void mazeSolve(){
  while(1)
  { readSensors();
    readMap();
    speed();
    unsigned char found_left=0;
    unsigned char found_straight=0;
    unsigned char found_right=0;
    
    if(right == 1){found_right = 1;}
    if(left == 1){found_left = 1;}
 
    
    if((found_right == 0) && (found_left == 0 )){
    if(analogRead(A5) > 600 ){ found_straight = 1;}}  // speed et back
    if((found_right == 1) || (found_left == 1 )){
    if(analogRead(A5) > 600 ){ found_straight = 1;}}  // croisement et T

    if((analogRead(C) > 300)  && (digitalRead(RRR) == 1) && (digitalRead(LLL) == 1))
  break;
  
unsigned char dir = select_turn(found_left, found_straight, found_right);
    turn(dir);
    path[path_length] = dir;
    path_length ++;
    simplify_path();
    
}


  while(1){
  
    int Click=digitalRead(PushButton);
    while(Click == 0){
      stop();
      if(digitalRead(PushButton)==1)
      break;
      }
     delay(2000);
     break;
     
   int i;
    for(i=0;i<path_length;i++)
    {
      speed();
      turn(path[i]);
    }
    while((center>300)&&(L1<mn2+50)&&(L2<mn3+50)&&(R1<mn1+50)&&(R2<mn0+50)){
   speed();
    }
  }
}