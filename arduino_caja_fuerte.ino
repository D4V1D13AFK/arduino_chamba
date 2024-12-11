#include <Keypad.h>
#include <Servo.h>

const byte FILAS = 4;
const byte COLUMNAS = 4;
int led = 13;

Servo servo;

char keys[FILAS][COLUMNAS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte pinesFilas[FILAS] = { 9, 8, 7, 6 };
byte pinesColumnas[COLUMNAS] = { 5, 4, 3, 2 };

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

const char clave[] = "1234";  // Cambia la clave aquí
char entradaUsuario[5];       // Para almacenar la entrada del usuario
byte indice = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Bienvenido introduzca la contraseña, usea # para confirmar o * par reiniciar la entrada de la contraseña");
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  servo.write(0);
  servo.attach(12);
}

void loop() {
  char tecla = teclado.getKey();

  if (tecla) {
    if (tecla == '#') {
      // Comprobación al presionar '#'
      entradaUsuario[indice] = '\0';  // Añadimos el terminador
      if (strcmp(entradaUsuario, clave) == 0) {
        Serial.println("Contraseña correcta. PUERTA ABIERTA");
        digitalWrite(led, LOW);
        servo.write(90);
      } else {
        Serial.println("Contraseña incorrecta.");
      }
      indice = 0;  // Reiniciamos el índice
    } else if (tecla == '*') {
      // Reinicio de la entrada al presionar '*'
      indice = 0;
      Serial.println("Entrada reiniciada. PUERTA CERRADA");
      Serial.println("Bienvenido introduzca la contraseña, usea # para confirmar o * par reiniciar la entrada de la contraseña");
      digitalWrite(led, HIGH);
      servo.write(0);

    } else {
      // Guardar tecla presionada si no se supera el tamaño
      if (indice < 4) {
        entradaUsuario[indice] = tecla;
        indice++;
        Serial.print(tecla);  // Mostramos la tecla presionada
      }
      if (indice == 4) {
        Serial.print(" ");
      }
    }
  }
}
