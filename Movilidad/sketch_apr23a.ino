const int pinLed = 2;
const int pinZumba = 3;
const int pinPulsador = 4;
const int sensorIzquierdo = 5;
const int sensorDerecho = 6;
const int pinIN1 = 7;
const int pinIN2 = 8;
const int pinIN3 = 9;
const int pinIN4 = 10;
const int TriggerPin = 11; // Sensor delantero
const int EchoPin = 12;    // Sensor delantero
const int PIRPin = 13; // Sensor de luz total 
int contador = 0;



void setup() {
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(pinPulsador, INPUT);
  pinMode(PIRPin, INPUT);
  pinMode(pinLed, OUTPUT);
}

void parar() {
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, LOW);
}

void retroceder(int tiempo) {
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
  delay(tiempo); // Esperar el tiempo especificado
  parar();
}

void giroIzquierda(int tiempo) {
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
  delay(tiempo); // Esperar el tiempo especificado
  parar();
}

void giroDerecha(int tiempo) {
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  delay(tiempo); // Esperar el tiempo especificado
  parar();
}

void avanzar(int tiempo) {
  digitalWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW);
  delay(tiempo); // Esperar el tiempo especificado
  parar();
}

int medirDistancia(int TriggerPin, int EchoPin) {
  long duration, distanceCm;
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  duration = pulseIn(EchoPin, HIGH);
  distanceCm = duration * 10 / 292 / 2;
  return distanceCm;
}

void estadoBase(){
  
  int distanciaIzquierda = digitalRead(sensorIzquierdo);
  int distanciaDerecha = digitalRead(sensorDerecho);
  int distanciacm = medirDistancia(TriggerPin, EchoPin);

  if (distanciaIzquierda == HIGH && distanciaDerecha == HIGH && distanciacm > 40) {
    // No hay obstáculos, avanzar
    avanzar(1000);
  } else if (distanciaIzquierda == HIGH && distanciaDerecha == HIGH && distanciacm <= 40) {
    // Obstáculo detectado por el sensor delantero, retroceder y girar
    retroceder(500);
    giroDerecha(500); // Girar completamente hacia la derecha
  } else if (distanciaIzquierda == HIGH) {
    // Obstáculo detectado a la izquierda, girar hacia la derecha
    giroDerecha(500);
  } else if (distanciaDerecha == HIGH) {
    // Obstáculo detectado a la derecha, girar hacia la izquierda
    giroIzquierda(500);
  }

}

void perritoFaldero(){

  // Trabajar con rangos (menor de 25, entre 25 y 35 para que se pare, y mayor que 30)
  // estador de sensores infrarrojos
  int estadoIRderecha = digitalRead(sensorDerecho);
  int estadoIRizquierda = digitalRead(sensorIzquierdo);
  // distancia del sensor de ultrasonidos
  int distancia = medirDistancia(TriggerPin, EchoPin);

  if (distancia > 30) { // Si la distancia es mayor a 30 cm, avanzar hacia la persona
    avanzar(250);

    if (estadoIRizquierda == LOW && estadoIRderecha == HIGH) {
      // Si detecta a la izquierda, gira a la izquierda
      giroIzquierda(250);
    } else if (estadoIRizquierda == HIGH && estadoIRderecha == LOW) {
      // Si detecta a la derecha, gira a la derecha
      giroDerecha(250);
    }

  } else { // Si la distancia al objeto es menor a 30 cm, retroceder
    retroceder(250);
  }
}

void perritoVigilancia() {

  parar();
  noTone(pinZumba);
  int hayMovimiento = digitalRead(PIRPin);

  if (hayMovimiento) {
    // Acciones cuando se detecta movimiento
    tone(pinZumba, 200);
    digitalWrite(pinZumba, HIGH); // Enciende el zumbador (o buzzer)
    digitalWrite(pinLed, HIGH);   // Enciende el LED rojo como señal de advertencia
    delay(1000);                  // Duración del ladrido y del parpadeo del LED (1 segundo)
    digitalWrite(pinZumba, LOW);  // Apaga el zumbador
    digitalWrite(pinLed, LOW);    // Apaga el LED rojo
  } else {
    // No hay movimiento, la mascota permanece en reposo.
    noTone(pinZumba);
    digitalWrite(pinZumba, LOW); // Apaga el zumbador (si estaba encendido por alguna razón)
    digitalWrite(pinLed, LOW);   // Apaga el LED rojo (si estaba encendido por alguna razón)
  }
}

void perritoGuardian() {
  // Explorar el entorno
  avanzar(1000); // Avanzar lentamente
  parar();
  delay(2000); // Parar y evaluar la situación

  // Evaluar sensores
  int hayMovimiento = digitalRead(PIRPin);
  int distanciaIzquierda = digitalRead(sensorIzquierdo);
  int distanciaDerecha = digitalRead(sensorDerecho);
  int distanciacm = medirDistancia(TriggerPin, EchoPin);

  if (hayMovimiento) {
    // Acciones cuando se detecta movimiento
    tone(pinZumba, 200);
    digitalWrite(pinZumba, HIGH); // Enciende el zumbador (o buzzer)
    digitalWrite(pinLed, HIGH);   // Enciende el LED rojo como señal de advertencia
    delay(1000);                  // Duración del ladrido y del parpadeo del LED (1 segundo)
    digitalWrite(pinZumba, LOW);  // Apaga el zumbador
    digitalWrite(pinLed, LOW);    // Apaga el LED rojo
  } else {
    noTone(pinZumba);
    digitalWrite(pinZumba, LOW); // Apaga el zumbador (si estaba encendido por alguna razón)
    digitalWrite(pinLed, LOW);   // Apaga el LED rojo (si estaba encendido por alguna razón)

    // Continuar explorando según el estado de los sensores
    if (distanciaIzquierda == HIGH && distanciaDerecha == HIGH && distanciacm > 40) {
      // No hay obstáculos, avanzar
      avanzar(1000);
    } else if (distanciaIzquierda == HIGH && distanciaDerecha == HIGH && distanciacm <= 40) {
      // Obstáculo detectado por el sensor delantero, retroceder y girar
      retroceder(500);
      giroDerecha(500); // Girar completamente hacia la derecha
    } else if (distanciaIzquierda == HIGH) {
      // Obstáculo detectado a la izquierda, girar hacia la derecha
      giroDerecha(500);
    } else if (distanciaDerecha == HIGH) {
      // Obstáculo detectado a la derecha, girar hacia la izquierda
      giroIzquierda(500);
    }
  }

  delay(500);
}


void loop() {

  if (digitalRead(pinPulsador) == HIGH){
    contador++;
    delay(200);
  }

  if (contador %4 == 0){
    estadoBase();
  } else if (contador %4 == 1){
    perritoFaldero();
  } else if (contador %4 == 2){
    perritoVigilancia();
  } else if (contador %4 == 3){
    perritoGuardian();
  }

}

