//#include <iomanip>
#include <vector>
#include <random>
#include "tetrisGame.h"
#include "Arduino.h"
//byte LED = PC13; //STM32 built-in led
uint8_t serialData = 0;
uint8_t data = 0;

const uint8_t buttonPin1 = PA9;     // the number of the pushbutton pin
const uint8_t buttonPin2 = PA10;     // the number of the pushbutton pin
const uint8_t buttonPin3 = PA11;     // the number of the pushbutton 
const uint8_t buttonPin4 = PA12;     // the number of the pushbutton 

uint8_t buttonState1 = 0;         // variable for reading the pushbutton status
uint8_t buttonState2 = 0;         // variable for reading the pushbutton status
uint8_t buttonState3 = 0;         // variable for reading the pushbutton status
uint8_t buttonState4 = 0;         // variable for reading the pushbutton status


using std::vector;
uint8_t blockType = 0;
uint8_t rotateType = 0;

uint8_t score{};
bool gameover = false;
uint8_t x{ 4 };
uint8_t y{ 0 };

//size of the flip dot display: 9x28 "pixels"
constexpr uint8_t COLUMNS = 28;
constexpr uint8_t ROWS = 9;

vector<vector<uint8_t>> board(COLUMNS, vector<uint8_t>(ROWS, 0));
vector<vector<uint8_t>> new_board(COLUMNS, vector<uint8_t>(ROWS, 0));
vector<vector<uint8_t>> block(4, vector<uint8_t>(4, 0));

uint8_t block_types [7][4][4][4]= {
// Square
  {
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0}
    },
   {
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 1, 1, 0},
  {0, 1, 1, 0}
    },
   {
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 1, 1, 0},
  {0, 1, 1, 0}
    },
   {
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 1, 1, 0},
  {0, 1, 1, 0}
    }
   },
// I
  {
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 1}
    },
   {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 1}
    },
   {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    }
   }
  ,
// L
  {
   {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 0},
    {1, 0, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 1, 0},
    {1, 1, 1, 0}
    }
   },
// L mirrored
  {
   {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 1, 0}
    }
   },
// N
  {
   {
    {0, 0, 0, 0},
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0}
    }
   },
// N mirrored
  {
   {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0}
    }
   },
// T
  {
   {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 1, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0}
    },
   {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 1, 0}
    }
   }
};

uint8_t gameOverText[COLUMNS][ROWS] ={
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 1, 0},
    {1, 0, 1, 1, 0, 1, 1, 1, 0},
    {1, 0, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 1, 1, 1},
    {1, 1, 0, 1, 1, 0, 1, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 1, 0},
    {1, 0, 0, 0, 1, 0, 1, 0, 0},
    {1, 0, 0, 0, 1, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 0, 1, 0},
    {1, 0, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 1, 0},
    {1, 1, 0, 0, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 1, 0, 1, 0, 0},
    {1, 1, 1, 0, 1, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

uint8_t tetrisText[COLUMNS][ROWS] ={
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 1, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 1, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

uint8_t randomBlock() {
    return random(0, 7);
    //return rand()%7;
}

void clear_display(){
	for(int r = 0; r < ROWS; ++r) {
		for(int c = 0; c < COLUMNS; ++c) {
			set_pixel(c, r);
		}
	}

	delay(1000);

	for(int r = 0; r < ROWS; ++r) {
		for(int c = 0; c < COLUMNS; ++c) {
			clear_pixel(c, r);
		}
	}
}

void clear_all(){
	for(int r = 0; r < ROWS; ++r) {
		for(int c = 0; c < COLUMNS; ++c) {
			clear_pixel(c, r);
		}
	}
}

void game_over(){
	clear_display();
	delay(1000);
	Serial.println("GAME OVER");
	Serial.println("Your score:");
	Serial.println(score);
	for (uint8_t i = 0; i < COLUMNS; i++) {
		for (uint8_t j = 0; j < ROWS; j++) {
			switch (gameOverText[i][j]) {
			case 0:
				clear_pixel(i,j);
				break;
			case 1:
				set_pixel(i,j);
				break;
			}
		}
	}
	delay(100000);
}

bool new_block(){
    x = 4;
    y = 0;

    blockType = randomBlock();
    //blockType = 1;
    rotateType = 0;

    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            block[i][j] = 0;
            block[i][j] = block_types[blockType][rotateType][i][j];
        }
    }

    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            new_board[i][j + 4] = board[i][j + 4] + block[i][j]; //previous board + new block

            if (new_board[i][j + 4] > 1) { //when there is no place for the next block
                gameover = true;
                return true;
            }
        }
    }
    return false;
}

void init_game(){
	Serial.println("w - rotate;  a - move left;  d - move right;  s - speed up");
	clear_display();

    for (uint8_t i = 0; i < COLUMNS; i++) {
        for (uint8_t j = 0; j < ROWS; j++) {
            switch (tetrisText[i][j]) {
            case 0:
                clear_pixel(i,j);
                break;
            case 1:
                set_pixel(i,j);
                break;
            }
        }
	}
	
	delay(3000);
	clear_display();
	delay(1000);

	for (uint8_t i = 0; i < COLUMNS; i++) {
		for (uint8_t j = 0; j <  ROWS; j++) {
			if ((j == 0) || (j == ROWS-1) || (i == COLUMNS-1)) {
				new_board[i][j] = board[i][j] = 2;
			}
			else {
				new_board[i][j] = board[i][j] = 0;
			}
		}
	}

    new_block();
    display();
}

void display(){ //display new_board
    for (uint8_t i = 0; i < COLUMNS; i++) {
        for (uint8_t j = 0; j < ROWS; j++) {
            switch (new_board[i][j]) {
            case 0:
                clear_pixel(i,j);
                break;
            case 1:
                set_pixel(i,j);
                break;
            }
        }
    }


    if (gameover) {
        game_over();
    }
}

void move_block(uint8_t x2, uint8_t y2){ //update the whole board
    //remove block
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            new_board[y + i][x + j] -= block[i][j];
        }
    }

    x = x2;
    y = y2;

    //assign a block with the updated value
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
           new_board[y + i][x + j] += block[i][j];
        }
    }

    display();
}

void copy_board(){ //save game state
    for (uint8_t i = 0; i < COLUMNS; i++) {
        for (uint8_t j = 0; j < ROWS; j++) {
            board[i][j] = new_board[i][j];
        }
    }
}

bool check_collide(uint8_t x2, uint8_t y2){ //check if the block touched the bottom/other blocks
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            if (block[i][j] && board[y2 + i][x2 + j] != 0) {
                return true;
            }
        }
    }
    return false;
}

bool rotate_block(){
	rotateType = rotateType + 1;
	if(rotateType >3 ){rotateType = 0;}
	vector<vector<uint8_t>> tmp(4, vector<uint8_t>(4, 0));

    //save temporarily block
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            tmp[i][j] = block[i][j];
        }
    }

    //rotate
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
			// block[i][j] = tmp[3 - j][i];
            block[i][j] = block_types[blockType][rotateType][i][j];
        }
    }

    //if it collide, stop rotate
    if (check_collide(x, y)) {
        for (uint8_t i = 0; i < 4; i++) {
            for (uint8_t j = 0; j < 4; j++) {
                block[i][j] = tmp[i][j];
            }
        }
        return true;
    }

    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            new_board[y + i][x + j] -= tmp[i][j];
            new_board[y + i][x + j] += block[i][j];
        }
    }

    display();
    return false;
}

void init_buttons(){
	// pinMode(LED, OUTPUT);
	pinMode(buttonPin1, INPUT);
	pinMode(buttonPin2, INPUT);
	pinMode(buttonPin3, INPUT);
	pinMode(buttonPin4, INPUT);
}

void buttons_control(){
	// read the state of the pushbutton value:
	buttonState1 = digitalRead(buttonPin1);
	buttonState2 = digitalRead(buttonPin2);
	buttonState3 = digitalRead(buttonPin3);
	buttonState4 = digitalRead(buttonPin4);

	// check if the pushbutton is pressed. If it is, the buttonState is LOW:
	if (buttonState1 == LOW && !check_collide(x+1,y)) {
		move_block(x+1,y);
	}

    if (buttonState2 == LOW && !check_collide(x-1,y)) {
		move_block(x-1,y);
	}
	
	if (buttonState3 == LOW) {
		rotate_block();
	}
	
    //if (buttonState4 == LOW && !check_collide(x,y+2)) {
    //	move_block(x,y+2);
	//}
}

void serial_control(){
	if (Serial.available()>0) {
		serialData = Serial.read();
		Serial.println(serialData);
		data = data+1;
	}

	if(data>0 && serialData=='d' && !check_collide(x+1,y)) {
		move_block(x+1,y);
		data = 0;
	}
	
    if(data>0 && serialData=='a' && !check_collide(x-1,y)) {
		move_block(x-1,y);
		data = 0;
    }
	
    if(data>0 && serialData=='s' && !check_collide(x,y+2)) {
		move_block(x,y+2);
		data = 0;
    }
	
    if(data>0 && serialData=='w') {
		rotate_block();
		data = 0;
    }
}

void line_check(){
	uint8_t line_element{};

    //if number of elements in line = width, erase this line
    for (uint8_t i = COLUMNS-2; i > 0; i--) {
        line_element = 0;
        for (uint8_t j = 1; j < ROWS-1; j++) {
            if (new_board[i][j] != 0) {
                line_element++;
            }
        }

        if (line_element == ROWS-2) {
            line_erase(i);
            i+=1;
        }
    }
}

void line_erase(uint8_t line){
	score++;
  
    for (uint8_t i = line; i > 0; i--) {
        for (uint8_t j = 1; j <ROWS-1; j++) {
            new_board[i][j] = new_board[i - 1][j];
        }
    }
}

void game(){ //lasts until the block falls

	//if block cant move to down anymore, make new block
	if (!check_collide(x, y+1)) {
		move_block(x, y + 1);
	}
	else {
		line_check();
		copy_board(); //save state
		new_block(); //new block
		display(); //clear and display 
    }
}
  
void game_loop(){
	//serial_control();
    game();
    buttons_control();

    delay(300);
}