#define PUMP5 5    //pin for turning transistor on/off
const byte numChars = 32;
char msg[numChars];



void setup()
{
  Serial.begin(9600,SERIAL_8N1);   // Debugging only
  Serial.println(msg[0]);
  pinMode(PUMP5, OUTPUT);
}


void loop()
{      
  digitalWrite(PUMP5, LOW);   
  read_msg();
  //sort_msg();
  command_pumps();          
}

void read_msg()
{
  char rc;
 if (Serial.available() > 0) {   
    rc = Serial.read();
    msg[0] = rc;
 }
 if(Serial.available() > 0) {
    rc = Serial.read();
    msg[1] = rc;
 }
    Serial.print("msg[0]: ");
    Serial.println(msg[0]);
    Serial.print("msg[1]: ");
    Serial.println(msg[1]);        
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
    msg[0]=msg[1];
    return;
  }
}

void command_pumps(){
   if (msg[0] == 'l'||msg[1]=='l')
  {  
    digitalWrite(PUMP5, LOW);       
  } 
  else if (msg[1] == 'h')
  {
    if(msg[0]=='0')  
      digitalWrite(PUMP5, HIGH);        
    else if (msg[0]=='1')
      digitalWrite(PUMP5, LOW);
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
    delay(20);
  }
}

