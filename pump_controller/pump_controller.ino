#define PUMP5 5    //pin for turning transistor on/offz
#define PUMP6 6    //pin for turning transistor on/offz
const byte numChars = 2;
char msg[numChars];



void setup()
{
  Serial.begin(9600,SERIAL_8N1);   // Debugging only
  Serial.println(msg[0]);
  pinMode(PUMP5, OUTPUT);
  pinMode(PUMP6, OUTPUT);
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
    digitalWrite(PUMP5, LOW);  
    digitalWrite(PUMP6, LOW);       
  } 
  else if (msg[1] == 'm')
  {
     if(msg[0]=='0'){
      digitalWrite(PUMP5, HIGH);
      delay(50);
      digitalWrite(PUMP5, LOW);
      delay(800);
     }           
    else if (msg[0]=='1'){
      digitalWrite(PUMP6, HIGH);
      delay(50);
      digitalWrite(PUMP6, LOW);
      delay(800);
     }
    else if (msg[0]=='2'){
      digitalWrite(PUMP5, HIGH); 
      delay(20);
      digitalWrite(PUMP5, LOW);
     }
    else if (msg[0]=='3'){
      digitalWrite(PUMP5, HIGH); 
      delay(20);
      digitalWrite(PUMP5, LOW);
     }
    else if (msg[0]=='4'){
      digitalWrite(PUMP5, HIGH); 
      delay(20);
      digitalWrite(PUMP5, LOW);
     }
    else if (msg[0]=='5'){
      digitalWrite(PUMP5, HIGH); 
      delay(20);
      digitalWrite(PUMP5, LOW);
     }
    else if (msg[0]=='6'){
      digitalWrite(PUMP5, HIGH); 
      delay(20);
      digitalWrite(PUMP5, LOW);
     }
    else if (msg[0]=='7'){
      digitalWrite(PUMP5, HIGH); 
      delay(20);
      digitalWrite(PUMP5, LOW);
     }
    else if (msg[0]=='8'){
      digitalWrite(PUMP5, HIGH); 
      delay(20);
      digitalWrite(PUMP5, LOW);
     }
    else if (msg[0]=='9'){
      digitalWrite(PUMP5, HIGH); 
      delay(20);
      digitalWrite(PUMP5, LOW);
     }
  }
  else if (msg[1] == 'h')
  {
    if(msg[0]=='0')  
      digitalWrite(PUMP5, HIGH);
      //Serial.println("HI");             
    else if (msg[0]=='1')
      digitalWrite(PUMP6, HIGH);
    else if (msg[0]=='2')
      digitalWrite(PUMP5, HIGH); 
    else if (msg[0]=='3')
      digitalWrite(PUMP5, HIGH); 
    else if (msg[0]=='4')
      digitalWrite(PUMP5, HIGH); 
    else if (msg[0]=='5')
      digitalWrite(PUMP5, HIGH); 
    else if (msg[0]=='6')
      digitalWrite(PUMP5, HIGH); 
    else if (msg[0]=='7')
      digitalWrite(PUMP5, HIGH); 
    else if (msg[0]=='8')
      digitalWrite(PUMP5, HIGH); 
    else if (msg[0]=='9')
      digitalWrite(PUMP5, HIGH); 
  }
  return;
}

