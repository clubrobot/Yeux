#ifndef CONFIGURATION_H
#define CONFIGURATION_H


//************************
// initialisation EEPROM *
//************************

//************
// Constants *
//************

// Time constants

#define LED_MATRIX_TIMESTEP 2e-4   // Execution step time in s
#define DEFAULT_PATTERN_TIMESTEP 100e-3    // Execution step time in s


//Weight of each segment
//                         a , b , c , d , e , f , g , dp
const byte DISP[4][8] = {{1, 128, 16, 4, 2, 64, 32, 8},
                         {1, 128, 32, 8, 4, 2, 64, 16},
                         {1, 128, 16, 4, 2, 64, 32, 8},		
                         {1, 128, 32, 8, 4, 2, 64, 16}};

//***************************
// LED Matrix Configuration *
//***************************

// shift register pins (Matrix 1)
#define DATA_MATRIX1 	8
#define CLOCK_MATRIX1 	9
#define LATCH_MATRIX1 	10

// shift register pins (Matrix 2)
#define DATA_MATRIX2	11
#define CLOCK_MATRIX2	12
#define LATCH_MATRIX2	13

// shift register pins (Matrix 3)
#define DATA_MATRIX3	A0
#define CLOCK_MATRIX3	A1
#define LATCH_MATRIX3	A2

// shift register pins (Matrix 4)
#define DATA_MATRIX4	A3
#define CLOCK_MATRIX4	A4
#define LATCH_MATRIX4	A5

// shift register pins (IP)
#define DATA_IP	    D5
#define CLOCK_IP    D6
#define LATCH_IP	D7
#define AFF1_IP D2
#define AFF2_IP D3
#define AFF3_IP D4

// general configuration

#define ROTATION_MATRIX_1 0
#define ROTATION_MATRIX_2 270
#define ROTATION_MATRIX_3 270
#define NB_PATTERNS_MAX 20
enum {SLIDE_MODE,ANIMATION_MODE,RIGHT_ROTATION_MODE,LEFT_ROTATION_MODE,UPSIDEDOWN_MODE, STATIC_MODE};

// Weight of each dot
const unsigned int rows[] = {4, 16384, 8, 32768, 128, 1, 512, 16}; //Row1,Row2,...,Row8
const unsigned int cols[] = {256, 2048, 64, 2, 32, 4096, 8192, 1024}; //Col1,Col2,...,Col8

/*
const unsigned int rows[] = {4, 16384, 8, 32768, 128, 1, 512, 16}; //Row1,Row2,...,Row8
const unsigned int cols[] = {256, 2048, 64, 2, 32, 4096, 8192, 1024}; //Col1,Col2,...,Col8
*/


#endif