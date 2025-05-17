#include <Arduino.h>
#include <time.h>

#include "configuration.h"
#include "ledMatrix.h"
#include "IPDisplay.h"


// Variables
LedMatrix ledmatrix1;
LedMatrix ledmatrix2;
LedMatrix ledmatrix3;
LedMatrix ledmatrix4;

LedMatrix* banner[4] = {&ledmatrix3, &ledmatrix2, &ledmatrix1, &ledmatrix4};

Ipdisplay ipdisplay;


char test[NB_PATTERNS_MAX] = "Club Robot INSA  ";
char **anim = ledmatrix1.stringToPatterns(test);

int frame1[8]= {
	(int) 0b01101100011011000110110001101100,
	(int) 0b11111110111111101111111011111110,
	(int) 0b11111110111111101111111011111110,
	(int) 0b11111110111111101111111011111110,
	(int) 0b01111100011111000111110001111100,
	(int) 0b00111000001110000011100000111000,
	(int) 0b00010000000100000001000000010000,
	(int) 0b00000000000000000000000000000000,
};

int frame2[8]= {
	(int) 0b0,
	(int) 0b0,
	(int) 0b0,
	(int) 0b0,
	(int) 0b0,
	(int) 0b0,
	(int) 0b0,
	(int) 0b0,
};

int *anim32Bit[2] = {frame1, frame2};

char zero = (char) 0b11111100;

char buffer[12] = {zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero};

//TODO: EMOJI and lowercase letter
void setup(){
	// Variables initialisation
	ipdisplay.attach(DATA_IP, CLOCK_IP, LATCH_IP);
	ipdisplay.setTimestep(IP_DISPLAY_TIMESTEP);
	ipdisplay.enable();

	ipdisplay.displayString("club robot");


	ledmatrix1.attach(DATA_MATRIX1,CLOCK_MATRIX1,LATCH_MATRIX1,ROTATION_MATRIX_2);
	ledmatrix1.setTimestep(LED_MATRIX_TIMESTEP);
	ledmatrix1.enable();

	ledmatrix2.attach(DATA_MATRIX2,CLOCK_MATRIX2,LATCH_MATRIX2,ROTATION_MATRIX_1);
	ledmatrix2.setTimestep(LED_MATRIX_TIMESTEP);
	ledmatrix2.enable();

	ledmatrix3.attach(DATA_MATRIX3,CLOCK_MATRIX3,LATCH_MATRIX3,ROTATION_MATRIX_1);
	ledmatrix3.setTimestep(LED_MATRIX_TIMESTEP);
	ledmatrix3.enable();

	ledmatrix4.attach(DATA_MATRIX4,CLOCK_MATRIX4,LATCH_MATRIX4,ROTATION_MATRIX_1);
	ledmatrix4.setTimestep(LED_MATRIX_TIMESTEP);
	ledmatrix4.enable();

	LedMatrix::displayBannerText(banner, "INSA", STATIC_MODE);
	LedMatrix::changeBannerPatternSpeed(banner,0.1);
	//LedMatrix::computeBufferBanner(banner, anim32Bit, 2);

}

long LedUpdatePrevTime;
long SwitchAnimPrevTime;
long timeInABottle;

bool animCounter=0;

void loop(){

    ledmatrix1.update();
	ledmatrix2.update();
	ledmatrix3.update();
	ledmatrix4.update();
	ipdisplay.update();


  timeInABottle = millis();
  if((timeInABottle-SwitchAnimPrevTime)>=1000){
    SwitchAnimPrevTime = timeInABottle;
  	ipdisplay.setDP(animCounter, 8);
  	animCounter=!animCounter;
  }
}
