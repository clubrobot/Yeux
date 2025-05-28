#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <Arduino.h>

//************************
// initialisation EEPROM *
//************************

//************
// Constants *
//************

// Time constants

#define LED_MATRIX_TIMESTEP 1e-4   // Execution step time in s
#define IP_DISPLAY_TIMESTEP 1e-4    // Execution step time in s
#define DEFAULT_PATTERN_TIMESTEP 100e-3    // Execution step time in s


//Weight of each segment
//                         a , b , c , d , e , f , g , dp
const byte DISP[4][8] = {{1, 128, 16, 4, 2, 64, 32, 8},
                         {1, 128, 32, 8, 4, 2, 64, 16},
                         {1, 128, 16, 4, 2, 64, 32, 8},		
                         {1, 128, 32, 8, 4, 2, 64, 16}};

#define SEG_A  (1 << 7)
#define SEG_B  (1 << 6)
#define SEG_C  (1 << 5)
#define SEG_D  (1 << 4)
#define SEG_E  (1 << 3)
#define SEG_F  (1 << 2)
#define SEG_G  (1 << 1)
#define SEG_DP (1 << 0)

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
#define DATA_IP	    5
#define CLOCK_IP    6
#define LATCH_IP	7
#define AFF1_IP 2
#define AFF2_IP 3
#define AFF3_IP 4

// general configuration

// IP_display constants
#define IP_DISPLAY_BUFFER_SIZE 25   // Size of the data buffer receiver
#define DISP_NUMBER 3               // Number of 7 seg common pin

#define ROTATION_MATRIX_1 0
#define ROTATION_MATRIX_2 270
#define ROTATION_MATRIX_3 270
#define NB_PATTERNS_MAX 20
enum {SLIDE_MODE,ANIMATION_MODE,RIGHT_ROTATION_MODE,LEFT_ROTATION_MODE,UPSIDEDOWN_MODE, STATIC_MODE};

// Weight of each dot
const unsigned int rows[] = {4, 16384, 8, 32768, 128, 1, 512, 16}; //Row1,Row2,...,Row8
const unsigned int cols[] = {256, 2048, 64, 2, 32, 4096, 8192, 1024}; //Col1,Col2,...,Col8



#endif