//----------------Variables de señales de sensores-----------------------------
int trigger = 13;
int echo = 12;
int enable1 = 10;
int int1 = 9;
int int2 = 8;
int sharp = A1;
String datamotor[2];
double pwm = 0;
int sentido;


//-----------------------------Datos a enviar---------------------------------
int timeHCSR04;


void setup() {
  //--------------Estableciendo velocidad de transmición de datos--------------
  Serial.begin(9600);
  //--------------Declarando pines de entrada y salida-------------------------
  pinMode(sharp, INPUT);
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(int1, OUTPUT);
  pinMode(int2, OUTPUT);
}

void loop() 
{
  //-----------Leyendo datos del buffer de entrada del arduino-------------------
  if(Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');
    pwm = data.toDouble();
    
    if(pwm > 0)
    {
      digitalWrite(int1,HIGH);
      digitalWrite(int2,LOW);
    }
  
    else if(pwm == 0)
    {
      digitalWrite(int1,LOW);
      digitalWrite(int2,LOW);
    }
    else
    {
      digitalWrite(int1,LOW);
      digitalWrite(int2,HIGH);
    }
  }
  
  //-------Preparando señal de disparo para activar el sensor HC-SR04----------
  digitalWrite(trigger, LOW);
  delayMicroseconds(4);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  //---------Midiendo tiempo de ida y retorno de pulso ultrasónico-------------
  timeHCSR04 = pulseIn(echo, HIGH);
  
  SentDatas();
  Motor();
}



void SentDatas()
{
  String pack = String(String(sharp)+','+String(timeHCSR04));
  Serial.println(pack); 
}

void Motor()
{ 
  analogWrite(enable1, abs(pwm)); 
}

