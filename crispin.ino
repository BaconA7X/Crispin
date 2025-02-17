#define DS 10 //DIO
#define STCP 12 //SCK
#define SHCP 11 //RCK
#define SPEED 500
#define TIME_TO_SHOW 500
#define TIME_TO_SCROLL 200

String TextoInicial = "Booting up";
unsigned long currentTime = 0;
boolean display_buffer[32];
bool recibido = false;
String fecha = "30122025";  // Cadena para almacenar la fecha en formato DDMMYYYY
String hora = "235953";     // Cadena para almacenar la hora en formato HHMMSS
String fechora = "";
int cinxuno = 0;

boolean numbersDef[10][8] = {
  { 1, 1, 1, 1, 1, 1, 0 },  //zero
  { 0, 1, 1, 0, 0, 0, 0 },  //one
  { 1, 1, 0, 1, 1, 0, 1 },  //two
  { 1, 1, 1, 1, 0, 0, 1 },  //three
  { 0, 1, 1, 0, 0, 1, 1 },  //four
  { 1, 0, 1, 1, 0, 1, 1 },  //five
  { 1, 0, 1, 1, 1, 1, 1 },  //six
  { 1, 1, 1, 0, 0, 0, 0 },  //seven
  { 1, 1, 1, 1, 1, 1, 1 },  //eight
  { 1, 1, 1, 1, 0, 1, 1 }   //nine
};
boolean digitsTable[8][8] = {
  { 0, 0, 0, 0, 1, 0, 0, 0 },  // first digit
  { 0, 0, 0, 0, 0, 1, 0, 0 },  // second
  { 0, 0, 0, 0, 0, 0, 1, 0 },  // third
  { 0, 0, 0, 0, 0, 0, 0, 1 },  // 8th
  { 1, 0, 0, 0, 0, 0, 0, 0 },  // forth
  { 0, 1, 0, 0, 0, 0, 0, 0 },  // fifth
  { 0, 0, 1, 0, 0, 0, 0, 0 },  // sixth
  { 0, 0, 0, 1, 0, 0, 0, 0 }   // 7th
};
void obtenerSegmentos(char c, bool segmentos[7]) {
  // Inicializa todos los segmentos a apagados (false)
  for (int i = 0; i < 7; i++) {
    segmentos[i] = false;
  }

  switch (c) {
    case '0':
      segmentos[0] = true;  // a
      segmentos[1] = true;  // b
      segmentos[2] = true;  // c
      segmentos[3] = true;  // d
      segmentos[4] = true;  // e
      segmentos[5] = true;  // f
      break;
    case '1':
      segmentos[1] = true;  // b
      segmentos[2] = true;  // c
      break;
    case '2':
      segmentos[0] = true;  // a
      segmentos[1] = true;  // b
      segmentos[3] = true;  // d
      segmentos[4] = true;  // e
      segmentos[6] = true;  // g
      break;
    case '3':
      segmentos[0] = true;  // a
      segmentos[1] = true;  // b
      segmentos[2] = true;  // c
      segmentos[3] = true;  // d
      segmentos[6] = true;  // g
      break;
    case '4':
      segmentos[1] = true;  // b
      segmentos[2] = true;  // c
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case '5':
      segmentos[0] = true;  // a
      segmentos[2] = true;  // c
      segmentos[3] = true;  // d
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case '6':
      segmentos[0] = true;  // a
      segmentos[2] = true;  // c
      segmentos[3] = true;  // d
      segmentos[4] = true;  // e
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case '7':
      segmentos[0] = true;  // a
      segmentos[1] = true;  // b
      segmentos[2] = true;  // c
      break;
    case '8':
      segmentos[0] = true;  // a
      segmentos[1] = true;  // b
      segmentos[2] = true;  // c
      segmentos[3] = true;  // d
      segmentos[4] = true;  // e
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case '9':
      segmentos[0] = true;  // a
      segmentos[1] = true;  // b
      segmentos[2] = true;  // c
      segmentos[3] = true;  // d
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case 'A':
      segmentos[0] = true;  // a
      segmentos[1] = true;  // b
      segmentos[2] = true;  // c
      segmentos[4] = true;  // e
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case 'B':
      segmentos[2] = true;  // c
      segmentos[3] = true;  // d
      segmentos[4] = true;  // e
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case 'C':
      segmentos[0] = true;  // a
      segmentos[3] = true;  // d
      segmentos[4] = true;  // e
      segmentos[5] = true;  // f
      break;
    case 'D':
      segmentos[1] = true;  // b
      segmentos[3] = true;  // d
      segmentos[4] = true;  // e
      segmentos[2] = true;  // f
      segmentos[6] = true;  // g
      break;
    case 'E':
      segmentos[0] = true;  // a
      segmentos[3] = true;  // d
      segmentos[4] = true;  // e
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case 'F':
      segmentos[0] = true;  // a
      segmentos[4] = true;  // e
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case 'G':
      segmentos[0] = true;  // a
      segmentos[1] = true;  // b
      segmentos[2] = true;  // c
      segmentos[3] = true;  // d
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case 'H':
      segmentos[1] = true;  // a
      segmentos[2] = true;  // e
      segmentos[4] = true;  // f
      segmentos[5] = true;  // g
      segmentos[6] = true;  // g
      break;
    case 'I':
      segmentos[1] = true;  // a
      segmentos[2] = true;  // e
      break;
    case 'J':
      segmentos[1] = true;  // d
      segmentos[2] = true;  // e
      segmentos[3] = true;  // f
      break;
    case 'K':
      segmentos[4] = true;  // d
      segmentos[5] = true;  // e
      segmentos[6] = true;  // f
      break;
    case 'L':
      segmentos[3] = true;  // d
      segmentos[4] = true;  // e
      segmentos[5] = true;  // f
      break;
    case 'M':
      segmentos[2] = true;  // d
      segmentos[4] = true;  // e
      segmentos[0] = true;  // f
      break;
    case 'N':
      segmentos[0] = true;  // d
      segmentos[1] = true;  // e
      segmentos[2] = true;  // f
      segmentos[4] = true;  // d
      segmentos[5] = true;  // e
      break;
    case 'O':
      segmentos[1] = true;  // a
      segmentos[2] = true;  // e
      segmentos[0] = true;  // f
      segmentos[3] = true;  // f
      segmentos[4] = true;  // f
      segmentos[5] = true;  // g
      break;
    case 'P':
      segmentos[1] = true;  // a
      segmentos[0] = true;  // f
      segmentos[4] = true;  // f
      segmentos[5] = true;  // g
      segmentos[6] = true;  // g
      break;
    case 'Q':
      segmentos[0] = true;  // a
      segmentos[1] = true;  // b
      segmentos[2] = true;  // c
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case 'R':
      segmentos[5] = true;  // a
      segmentos[4] = true;  // f
      segmentos[0] = true;  // g
      break;
    case 'S':
      segmentos[0] = true;  // a
      segmentos[2] = true;  // c
      segmentos[3] = true;  // d
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case 'T':
      segmentos[4] = true;  // c
      segmentos[3] = true;  // d
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case 'U':
      segmentos[4] = true;  // c
      segmentos[3] = true;  // d
      segmentos[5] = true;  // f
      segmentos[2] = true;  // g
      segmentos[1] = true;  // g
      break;
    case 'V':
      segmentos[4] = true;  // c
      segmentos[3] = true;  // d
      segmentos[2] = true;  // g
      break;
    case 'W':
      segmentos[5] = true;  // c
      segmentos[3] = true;  // d
      segmentos[1] = true;  // g
      break;
    case 'X':
      segmentos[6] = true;  // c
      segmentos[2] = true;  // d
      segmentos[1] = true;  // g
      break;
    case 'Y':
      segmentos[1] = true;  // b
      segmentos[2] = true;  // c
      segmentos[3] = true;  // d
      segmentos[5] = true;  // f
      segmentos[6] = true;  // g
      break;
    case 'Z':
      segmentos[0] = true;  // a
      segmentos[1] = true;  // b
      segmentos[3] = true;  // d
      segmentos[4] = true;  // e
      segmentos[6] = true;  // g
      break;
    default:
      break;  // Si el carácter no es válido, no encender ningún segmento
  }
}
void prepareDisplayBuffer(int number, int digit_order, boolean showDot) {
  for (int index = 7; index >= 0; index--) {
    display_buffer[index] = digitsTable[digit_order - 1][index];
  }
  for (int index = 14; index >= 8; index--) {
    display_buffer[index] = !numbersDef[number - 1][index];  //because logic is sanity, right?
  }
  if (showDot == true)
    display_buffer[15] = 0;
  else
    display_buffer[15] = 1;
}
void prepareDisplayBufferChar(char c, int digit_order, boolean showDot) {
  bool segmentos[7];
  obtenerSegmentos(c, segmentos);  // Obtiene los segmentos para el carácter

  for (int index = 7; index >= 0; index--) {
    display_buffer[index] = digitsTable[digit_order - 1][index];
  }

  for (int index = 14; index >= 8; index--) {
    display_buffer[index] = !segmentos[index - 8];  // Muestra los segmentos obtenidos
  }

  display_buffer[15] = showDot ? 0 : 1;
}
void writeLetter(char c, int order, bool showDot = false) {
  prepareDisplayBufferChar(c, order, showDot);
  digitalWrite(SHCP, LOW);
  for (int i = 15; i >= 0; i--) {
    digitalWrite(STCP, LOW);
    digitalWrite(DS, display_buffer[i]);
    digitalWrite(STCP, HIGH);
  }
  digitalWrite(SHCP, HIGH);
}
void displayWord(String word, bool last) {
  writeLetter(word[0], 1, false);
  writeLetter(word[1], 2, false);
  writeLetter(word[2], 3, false);
  writeLetter(word[3], 4, false);
  writeLetter(word[4], 5, false);
  writeLetter(word[5], 6, false);
  writeLetter(word[6], 7, false);
  writeLetter(word[7], 8, last);
  delay(1);
}
void scrollWord(String word) {
  int wordLength = word.length();
  word.toUpperCase();
  int millisAct = millis();
  while (millis() < millisAct + TIME_TO_SHOW)
    displayWord(word.substring(0, min(wordLength, 8)), false);
  int delay = TIME_TO_SCROLL;
  // Desplazar la palabra hacia la izquierda
  for (int offset = 1; offset <= wordLength - 8; offset++) {
    millisAct = millis();
    if (offset == wordLength - 8)  // Subcadena de 8 caracteres
      delay = TIME_TO_SHOW;
    while (millis() < millisAct + delay)
      displayWord(word.substring(offset, offset + 8), offset == wordLength - 8);
  }
}
void writeDigit(int number, int order, bool showDot = false) {
  prepareDisplayBuffer(number, order, showDot);
  digitalWrite(SHCP, LOW);
  for (int i = 15; i >= 0; i--) {
    digitalWrite(STCP, LOW);
    digitalWrite(DS, display_buffer[i]);  //output LOW - enable segments, HIGH - disable segments
    digitalWrite(STCP, HIGH);
  }
  digitalWrite(SHCP, HIGH);
}
void displayTime(String s) {
  if (s.length() == 6) {
    writeDigit(s.charAt(0) - '0', 2, false);
    writeDigit(s.charAt(1) - '0', 3, true);
    writeDigit(s.charAt(2) - '0', 4, false);
    writeDigit(s.charAt(3) - '0', 5, true);
    writeDigit(s.charAt(4) - '0', 6, false);
    writeDigit(s.charAt(5) - '0', 7, false);
  } else if (s.length() == 8) {
    writeDigit(s.charAt(0) - '0', 1, false);
    writeDigit(s.charAt(1) - '0', 2, true);
    writeDigit(s.charAt(2) - '0', 3, false);
    writeDigit(s.charAt(3) - '0', 4, true);
    writeDigit(s.charAt(4) - '0', 5, false);
    writeDigit(s.charAt(5) - '0', 6, false);
    writeDigit(s.charAt(6) - '0', 7, false);
    writeDigit(s.charAt(7) - '0', 8, false);
  }
}
void setup() {
  pinMode(DS, OUTPUT);
  pinMode(STCP, OUTPUT);
  pinMode(SHCP, OUTPUT);
  digitalWrite(DS, LOW);
  digitalWrite(STCP, LOW);
  digitalWrite(SHCP, LOW);
  currentTime = millis();
  Serial.begin(9600);
  while (!Serial) {
    ;  // Espera a que el puerto serial esté listo
  }
}
void loop() {
  if (Serial.available() > 0 || recibido) {
    // Lee el mensaje recibido
    if (!recibido) {
      String receivedMessage = Serial.readStringUntil('\n');
      receivedMessage.trim();  // Elimina espacios en blanco o saltos de línea
      if (receivedMessage.length() >= 19) {
        // Extrae las partes del mensaje
        String year = receivedMessage.substring(0, 4);
        String month = receivedMessage.substring(5, 7);
        String day = receivedMessage.substring(8, 10);
        String hour = receivedMessage.substring(11, 13);
        String minute = receivedMessage.substring(14, 16);
        String second = receivedMessage.substring(17, 19);

        // Forma las cadenas con los formatos requeridos
        fecha = day + month + year;     // DDMMYYYY
        hora = hour + minute + second;  // HHMMSS

        // Muestra los resultados en el monitor serial
        Serial.println("Fecha almacenada: " + fecha);
        Serial.println("Hora almacenada: " + hora);

        // Envía la respuesta "OK" al programa Python
        Serial.println("OK");  // Imprime el mensaje recibido
        Serial.println("Mensaje recibido: " + receivedMessage);
        recibido = true;
      } else {
        Serial.println("Error: Formato incorrecto");
      }      
    }
    if (fechora.length() < 8)
      displayTime(fecha);
    else
      displayTime(hora);
    if (currentTime + 1000 <= millis()) {  //actualizar hora
      currentTime = millis();
      cinxuno++;
      int hour = hora.substring(0, 2).toInt();
      int min = hora.substring(2, 4).toInt();
      int seg = hora.substring(4, 6).toInt();
      int dia = fecha.substring(0, 2).toInt();
      int mes = fecha.substring(2, 4).toInt();
      int anio = fecha.substring(4, 8).toInt();

      seg++;
      if (seg > 59) {
        seg = 0;
        min++;
      }
      if (min > 59) {
        min = 0;
        hour++;
      }
      if (hour > 23) {
        hour = 0;
        dia++;
      }
      if (dia > 30) {
        dia = 1;
        mes++;
      }
      if (mes > 12) {
        mes = 1;
        anio++;
      }

      hora = (hour < 10 ? "0" : "") + String(hour) + (min < 10 ? "0" : "") + String(min) + (seg < 10 ? "0" : "") + String(seg);
      fecha = (dia < 10 ? "0" : "") + String(dia) + (mes < 10 ? "0" : "") + String(mes) + String(anio);
      if (cinxuno > 5) {
        if (fechora.length() < 8)
          fechora = fecha;
        else
          fechora = hora;
        cinxuno = 0;
        displayTime(hora);
      }
    }
  } else {
    scrollWord(TextoInicial);
  }
}
