#define PUMP1 1    //pin for turning transistor on/offz
#define PUMP2 2    //pin for turning transistor on/offz
#define PUMP3 3    //pin for turning transistor on/offz
#define PUMP4 4    //pin for turning transistor on/offz
#define PUMP5 5    //pin for turning transistor on/offz
#define PUMP6 6    //pin for turning transistor on/offz
#define PUMP7 7    //pin for turning transistor on/offz
#define PUMP8 8    //pin for turning transistor on/offz
#define PUMP9 9    //pin for turning transistor on/offz
#define PUMP10 10    //pin for turning transistor on/offz
const byte numChars = 2;
char msg[numChars];



void setup()
{
  Serial.begin(9600,SERIAL_8N1);   // Debugging only
  Serial.println(msg[0]);
  pinMode(PUMP1, OUTPUT);
  pinMode(PUMP2, OUTPUT);
  pinMode(PUMP3, OUTPUT);
  pinMode(PUMP4, OUTPUT);
  pinMode(PUMP5, OUTPUT);
  pinMode(PUMP6, OUTPUT);
  pinMode(PUMP7, OUTPUT);
  pinMode(PUMP8, OUTPUT);
  pinMode(PUMP9, OUTPUT);
  pinMode(PUMP10, OUTPUT);
}


void loop()
{      
if (Serial.available() >= 2)
  {   
    read_msg();
    sort_msg();
    command_pumps();
  }         
}


void read_msg()
{ 
    while(Serial.available())
    {
      msg[0] = Serial.read();
      msg[1] =  Serial.read();   
    }    
}


void sort_msg()
{
  if(!isalpha(msg[0])&&isalpha(msg[1]))
  {
    return;
  }
  else
  {
    char temp_char = msg[1];
    msg[1]=msg[0];
    msg[0]=temp_char;
    return;
  }
}


void command_pumps(){
   Serial.print("msg[0]: ");
   Serial.println(msg[0]);
   Serial.print("msg[1]: ");
   Serial.println(msg[1]); 
   if (msg[0] == 'l'||msg[1]=='l')
  {  
    digitalWrite(PUMP1, LOW);  
    digitalWrite(PUMP2, LOW); 
    digitalWrite(PUMP3, LOW);  
    digitalWrite(PUMP4, LOW); 
    digitalWrite(PUMP5, LOW);  
    digitalWrite(PUMP6, LOW); 
    digitalWrite(PUMP7, LOW);  
    digitalWrite(PUMP8, LOW); 
    digitalWrite(PUMP9, LOW);  
    digitalWrite(PUMP10, LOW);       
  } 
  else if (msg[1] == 'm')
  {
     if(msg[0]=='0'){
      digitalWrite(PUMP1, HIGH);
      delay(50);
      digitalWrite(PUMP1, LOW);
      delay(800);
     }           
    else if (msg[0]=='1'){
      digitalWrite(PUMP2, HIGH);
      delay(50);
      digitalWrite(PUMP2, LOW);
      delay(800);
     }
    else if (msg[0]=='2'){
      digitalWrite(PUMP3, HIGH); 
      delay(20);
      digitalWrite(PUMP3, LOW);
     }
    else if (msg[0]=='3'){
      digitalWrite(PUMP4, HIGH); 
      delay(20);
      digitalWrite(PUMP4, LOW);
     }
    else if (msg[0]=='4'){
      digitalWrite(PUMP5, HIGH); 
      delay(20);
      digitalWrite(PUMP5, LOW);
     }
    else if (msg[0]=='5'){
      digitalWrite(PUMP6, HIGH); 
      delay(20);
      digitalWrite(PUMP6, LOW);
     }
    else if (msg[0]=='6'){
      digitalWrite(PUMP7, HIGH); 
      delay(20);
      digitalWrite(PUMP7, LOW);
     }
    else if (msg[0]=='7'){
      digitalWrite(PUMP8, HIGH); 
      delay(20);
      digitalWrite(PUMP8, LOW);
     }
    else if (msg[0]=='8'){
      digitalWrite(PUMP9, HIGH); 
      delay(20);
      digitalWrite(PUMP9, LOW);
     }
    else if (msg[0]=='9'){
      digitalWrite(PUMP10, HIGH); 
      delay(20);
      digitalWrite(PUMP10, LOW);
     }
  }
  else if (msg[1] == 'h')
  {
    if(msg[0]=='0')  
      digitalWrite(PUMP1, HIGH);
      //Serial.println("HI");             
    else if (msg[0]=='1')
      digitalWrite(PUMP2, HIGH);
    else if (msg[0]=='2')
      digitalWrite(PUMP3, HIGH); 
    else if (msg[0]=='3')
      digitalWrite(PUMP4, HIGH); 
    else if (msg[0]=='4')
      digitalWrite(PUMP5, HIGH); 
    else if (msg[0]=='5')
      digitalWrite(PUMP6, HIGH); 
    else if (msg[0]=='6')
      digitalWrite(PUMP7, HIGH); 
    else if (msg[0]=='7')
      digitalWrite(PUMP8, HIGH); 
    else if (msg[0]=='8')
      digitalWrite(PUMP9, HIGH); 
    else if (msg[0]=='9')
      digitalWrite(PUMP10, HIGH); 
  }
  return;
}


