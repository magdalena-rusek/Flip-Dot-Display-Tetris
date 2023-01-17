#include "SPI.h"
#include "SoftwareSPI.h"
#include "tetrisGame.h"

byte enablePin = PA7;  //enable
byte latchPin = PA6; //load
byte sckPin = PA5;   //clk
byte mosiPin = PA4;  //data
SoftwareSPI SSPI;

//size of the flip dot display: 9x28 "pixels"
constexpr uint8_t COLUMNS = 28;
constexpr uint8_t ROWS = 9;

uint8_t columns_to_address[COLUMNS] = {
  0b01100,
  0b01110,
  0b01011,
  0b01010,
  0b01001,
  0b01101,
  0b01111,
  0b10100,
  0b10011,
  0b10110,
  0b10010,
  0b10001,
  0b10101,
  0b10111,
  0b11111,
  0b11101,
  0b11110,
  0b11100,
  0b11011,
  0b11010,
  0b11001,
  0b00111,
  0b00101,
  0b00110,
  0b00100,
  0b00011,
  0b00010,
  0b00001,
};

uint8_t rows_set_to_address[ROWS] = {
  130,
  150,
  149,
  148,
  147,
  146,
  145,
  144,
  134
};

uint8_t rows_clear_to_address[ROWS] = {
  65,
  78,
  77,
  76,
  75,
  74,
  73,
  72,
  69
};

void send_bytes(uint8_t byteRows, uint8_t byteColumns) {
  byteColumns = ~byteColumns;

  //SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
  
  SSPI.transfer(byteColumns);
  SSPI.transfer(byteRows);
  //SPI.endTransaction();

  delayMicroseconds(100);
  digitalWrite(latchPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(latchPin, LOW);
  delayMicroseconds(100);

  digitalWrite(enablePin, LOW);
  delayMicroseconds(2000);
  digitalWrite(enablePin, HIGH);
}

void clear_pixel(uint8_t column, uint8_t row) {
  
  uint8_t byte_row = rows_clear_to_address[row];
  uint8_t byte_column = (1 << 6) + columns_to_address[column];

  send_bytes(byte_row, byte_column);
}

void set_pixel(uint8_t column, uint8_t row) {

  uint8_t byte_row = rows_set_to_address[row];
  uint8_t byte_column = (0 << 6) + columns_to_address[column];

  send_bytes(byte_row, byte_column);
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);

  pinMode(latchPin, OUTPUT);
  SSPI.begin(mosiPin, sckPin);
  //SSPI.begin();
  SSPI.setClockDivider(1);
  //randomSeed(analogRead(0));

  //"light up" and "turn off" welcome sequence
  init_game();
  init_buttons();
}

// the loop function runs over and over again forever
void loop() {   
  game_loop();
}    