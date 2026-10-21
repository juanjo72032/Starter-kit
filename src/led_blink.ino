#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Definición de pines según tu diagram.json actual
const int RELAY_IZQ_SUP = 18; // LED Verde (Izq Sup)
const int RELAY_DER_SUP = 19; // LED Amarillo (Der Sup)
const int RELAY_IZQ_INF = 16; // LED Cian (Izq Inf)
const int RELAY_DER_INF = 17; // LED Azul (Der Inf)

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_IZQ_SUP, OUTPUT);
  pinMode(RELAY_IZQ_INF, OUTPUT);
  pinMode(RELAY_DER_SUP, OUTPUT);
  pinMode(RELAY_DER_INF, OUTPUT);

  apagarTodos();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo al asignar SSD1306"));
    while(1);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  // 1. DOS LEDS DE ARRIBA (Verde y Amarillo) -> FLECHA ARRIBA
  apagarTodos();
  digitalWrite(RELAY_IZQ_SUP, HIGH);
  digitalWrite(RELAY_DER_SUP, HIGH);
  mostrarFlecha("ARRIBA");
  delay(2000);

  // 2. DOS DE LA DERECHA (Amarillo y Azul) -> FLECHA DERECHA
  apagarTodos();
  digitalWrite(RELAY_DER_SUP, HIGH);
  digitalWrite(RELAY_DER_INF, HIGH);
  mostrarFlecha("DERECHA");
  delay(2000);

  // 3. DOS DE LA IZQUIERDA (Verde y Cian) -> FLECHA IZQUIERDA
  apagarTodos();
  digitalWrite(RELAY_IZQ_SUP, HIGH);
  digitalWrite(RELAY_IZQ_INF, HIGH);
  mostrarFlecha("IZQUIERDA");
  delay(2000);

  // 4. DOS LEDS DE ABAJO (Cian y Azul) -> FLECHA ABAJO
  apagarTodos();
  digitalWrite(RELAY_IZQ_INF, HIGH);
  digitalWrite(RELAY_DER_INF, HIGH);
  mostrarFlecha("ABAJO");
  delay(2000);
}

// Funciones con lógica invertida (HIGH = Encendido, LOW = Apagado para este montaje)
void apagarTodos() {
  digitalWrite(RELAY_IZQ_SUP, LOW);
  digitalWrite(RELAY_IZQ_INF, LOW);
  digitalWrite(RELAY_DER_SUP, LOW);
  digitalWrite(RELAY_DER_INF, LOW);
}

void mostrarFlecha(String direccion) {
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 0);
  display.print(direccion);

  if (direccion == "ARRIBA") {
    display.fillTriangle(64, 15, 44, 45, 84, 45, SSD1306_WHITE);
  } 
  else if (direccion == "DERECHA") {
    display.fillTriangle(94, 32, 64, 15, 64, 50, SSD1306_WHITE);
  } 
  else if (direccion == "IZQUIERDA") {
    display.fillTriangle(34, 32, 64, 15, 64, 50, SSD1306_WHITE);
  } 
  else if (direccion == "ABAJO") {
    display.fillTriangle(64, 50, 44, 20, 84, 20, SSD1306_WHITE);
  }

  display.display();
}
