/*
 * 
 * hetpro-store.com/TUTORIALES/
 * Autor: Dr. Rubén Estrada Marmolejo
 * Fecha revisión: 29 de Enero de 2018
 * 
 */
int bullets = 0;
#define UP 10
#define DOWN 9
String cadenaCharEntrada = "";
String cadenaCharSalida = ""; 
char vectorChar[20];
char CaracterArriba;
char CaracterAbajo;
bool finCadena = false;
#define buzzer 11

byte oleadas[6][8] {
  { 1, 1, 1, 1, 1, 1, 0, 0 }, //0
  { 1, 0, 1, 0, 0, 0, 0, 0 }, //1
  { 1, 1, 0, 1, 1, 0, 1, 0 }, //2
  { 1, 1, 1, 0, 1, 0, 1, 0 }, //3
  { 1, 0, 1, 0, 0, 1, 1, 0 }, //4
  { 0, 1, 1, 0, 1, 1, 1, 0 }, //5
};

void setup() {
  Serial.begin(115200);
  cadenaCharEntrada.reserve(20);
  pinMode(LED_BUILTIN,OUTPUT);
  
  pinMode(UP, INPUT);

  pinMode(DOWN, INPUT);

  pinMode(buzzer, OUTPUT);
}

void loop() { 
  if(finCadena){                               //Se termino de recibir una cadena completa
    finCadena = false;                                  //Permitimos volver a recibir otra cadena
    cadenaCharEntrada.toCharArray(vectorChar,20);   //Convertimos el string a un vectorChar
    int numeroEntero = atoi(vectorChar);            //Convertimos un vectorChar a un entero
    
    //Serial.print("Se recibio ");
    //Serial.println(numeroEntero);
   
    if(numeroEntero == 1){
      digitalWrite(LED_BUILTIN,HIGH);
      for (int e = 0; e < 8; e++)
      {
        digitalWrite(e+2,oleadas[0][e]);
      }
      tone(11, 100, 500);
    }
    else if(numeroEntero == 2){
      digitalWrite(LED_BUILTIN,LOW);
    }
    else if(numeroEntero == 3){
      //bullets = analogRead(3);
      char CaracterPotenciometro = analogRead(3);
      if (digitalRead(UP) == HIGH){
        CaracterArriba = 1;
      }
      else {
        CaracterArriba = 0;
      }
      
      if (digitalRead(DOWN) == HIGH){
        CaracterAbajo = 1;
      }
      else {
        CaracterAbajo = 0;
      }

     cadenaCharSalida += String(analogRead(3));
     cadenaCharSalida += ",";
     cadenaCharSalida += String(digitalRead(UP));
     cadenaCharSalida += ",";
     cadenaCharSalida += String(digitalRead(DOWN));
     cadenaCharSalida += "\n"; // add a newline character to signal the end of the transmission
     Serial.print(cadenaCharSalida);
      
    }
    cadenaCharEntrada = "";
    cadenaCharSalida = "";
    
  }
}

void serialEvent(){
  //Recepción de datos Seriales
  
  while (Serial.available()) {              //Si existen datos seriales, leer a todos
    char CaracterEntrada = Serial.read();   //Leer 1 byte serial recibido
   
    cadenaCharEntrada += CaracterEntrada;   //Agregar el nuevo char a una cadena String 
    if (CaracterEntrada == '\n') {          //Si el char o byte recibido es un fin de linea, activa la bandera
      finCadena = true;                        //Si la bandera finCadena = 1, entonces la transmision esta completa
    }
    
  }
  
}
