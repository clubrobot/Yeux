#include <Arduino.h>
#include "configuration.h"
#include "ledMatrix.h"
#include "utils.h"



// Variables
LedMatrix ledmatrix1;
LedMatrix ledmatrix2;
LedMatrix ledmatrix3;
LedMatrix ledmatrix4;



char test[11] = "TEST      ";
char **anim = stringToPatterns(test);

void setup(){
	// Variables initialisation


	ledmatrix1.attach(DATA_MATRIX1,CLOCK_MATRIX1,LATCH_MATRIX1,ROTATION_MATRIX_2);
	ledmatrix1.setTimestep(LED_MATRIX_TIMESTEP);
	ledmatrix1.enable();
	
	ledmatrix1.computeBuffer(anim, 10, 3);
	ledmatrix1.setMode(SLIDE_MODE);

	ledmatrix2.attach(DATA_MATRIX2,CLOCK_MATRIX2,LATCH_MATRIX2,ROTATION_MATRIX_1);
	ledmatrix2.setTimestep(LED_MATRIX_TIMESTEP);
	ledmatrix2.enable();

	ledmatrix2.computeBuffer(anim, 10, 2);
	ledmatrix2.setMode(SLIDE_MODE);

	ledmatrix3.attach(DATA_MATRIX3,CLOCK_MATRIX3,LATCH_MATRIX3,ROTATION_MATRIX_1);
	ledmatrix3.setTimestep(LED_MATRIX_TIMESTEP);
	ledmatrix3.enable();

	ledmatrix3.computeBuffer(anim, 10, 1);
	ledmatrix3.setMode(SLIDE_MODE);

	ledmatrix4.attach(DATA_MATRIX4,CLOCK_MATRIX4,LATCH_MATRIX4,ROTATION_MATRIX_1);
	ledmatrix4.setTimestep(LED_MATRIX_TIMESTEP);
	ledmatrix4.enable();

	ledmatrix4.computeBuffer(anim, 10, 4);
	ledmatrix4.setMode(SLIDE_MODE);

}

long LedUpdatePrevTime;
long SwitchAnimPrevTime;
long timeInABottle;

char animCounter=0;

void loop(){

    ledmatrix1.update();
	ledmatrix2.update();
	ledmatrix3.update();
	ledmatrix4.update();

  
  // if((timeInABottle-SwitchAnimPrevTime)>=3000){
  //   SwitchAnimPrevTime = timeInABottle;
  //
  //   ledmatrix1.computeBuffer(*(Animation[animCounter]), sizeof(*(Animation[animCounter])));
  //   ledmatrix2.computeBuffer(*(Animation[animCounter]), sizeof(*(Animation[animCounter])));
  //   animCounter++;
  //
  //   if(animCounter>2){
  //     animCounter=0;
  //   }
  // }
}
