//----------------Variables de señales de sensor HCRS04-----------------------------
int trigger = 13;
int echo = 12;

//----------------Variables de control del motor------------------------------
int enable1 = 10;
int int1 = 9;
int int2 = 8;
double pwm = 0;

//-----------------------------Datos a enviar a C#---------------------------------
int timeHCSR04 = 0;


void setup() {
  //--------------Estableciendo velocidad de transmición de datos--------------
  Serial.begin(9600);
  //--------------Declarando pines de entrada y salida-------------------------
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
    String dataArrive = Serial.readStringUntil('\n');
    pwm = dataArrive.toDouble();
    
    turn(pwm);
  }
  
  //-------Preparando señal de disparo para activar el sensor HC-SR04----------
  digitalWrite(trigger, LOW);
  delayMicroseconds(4);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  //---------Midiendo tiempo de ida y retorno de pulso ultrasónico-------------
  timeHCSR04 = pulseIn(echo, HIGH);

  //---------Mandando datos del arduino a C#----------------------------------
  SentDatas(timeHCSR04);

  //-----------Activando motor con pwm----------------------------------------
  Motor(pwm);
}

void turn(double pwm)
{
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
    else if(pwm <0)
    {
      digitalWrite(int1,LOW);
      digitalWrite(int2,HIGH);
    }
}


void SentDatas(int timer)
{
  String pack = String(timer);
  Serial.println(pack); 
}

void Motor(double pwm)
{ 
  analogWrite(enable1, abs(pwm)); 
}

