#include <Arduino.h>
#include "IPDisplay.h"
#include "configuration.h"

void Ipdisplay::attach(byte dataPin, byte clockPin, byte latchPin){
	clearDisplay();
	m_DATA = dataPin;
	m_CLOCK = clockPin;
	m_LATCH = latchPin;
	m_disp_number = 0;

	// sets the pins as output
	pinMode(m_DATA, OUTPUT);
	pinMode(m_CLOCK, OUTPUT);
	pinMode(m_LATCH, OUTPUT);

	pinMode(AFF1_IP, OUTPUT);
	pinMode(AFF2_IP, OUTPUT);
	pinMode(AFF3_IP, OUTPUT);
	digitalWrite(AFF1_IP, LOW);
	digitalWrite(AFF2_IP, LOW);
	digitalWrite(AFF3_IP, LOW);
}

void setDisp(byte disp, bool on){
	switch(disp){
		case 0:
			digitalWrite(AFF1_IP, on);
			break;
		case 1:
			digitalWrite(AFF2_IP, on);
			break;
		case 2:
			digitalWrite(AFF3_IP, on);
		break;
	}
}

// Function to remap standard 7-seg byte to 4 displays
char map_segments(char standard, byte disp) {
	// Mapping arrays for each display (bit index → segment name)
	char out = 0;
	if (disp==0 || disp==2){
		out |= (standard & SEG_B)  ? (1 << 7) : 0;
		out |= (standard & SEG_F)  ? (1 << 6) : 0;
		out |= (standard & SEG_G)  ? (1 << 5) : 0;
		out |= (standard & SEG_C) ? (1 << 4) : 0;
		out |= (standard & SEG_DP)  ? (1 << 3) : 0;
		out |= (standard & SEG_D)  ? (1 << 2) : 0;
		out |= (standard & SEG_E)  ? (1 << 1) : 0;
		out |= (standard & SEG_A)  ? (1 << 0) : 0;
	}else{
		out |= (standard & SEG_B)  ? (1 << 7) : 0;
		out |= (standard & SEG_G)  ? (1 << 6) : 0;
		out |= (standard & SEG_C)  ? (1 << 5) : 0;
		out |= (standard & SEG_DP)  ? (1 << 4) : 0;
		out |= (standard & SEG_D) ? (1 << 3) : 0;
		out |= (standard & SEG_E)  ? (1 << 2) : 0;
		out |= (standard & SEG_F)  ? (1 << 1) : 0;
		out |= (standard & SEG_A)  ? (1 << 0) : 0;
	}
	return out;
}

void Ipdisplay::process(float timestep){
	setDisp(m_disp_number, LOW);
	m_disp_number++;
	if (m_disp_number >= 3) m_disp_number = 0;

	digitalWrite(m_LATCH, LOW);
	shiftOut(m_DATA, m_CLOCK, MSBFIRST, map_segments(m_toSend[2][m_disp_number], 2));
	shiftOut(m_DATA, m_CLOCK, MSBFIRST, map_segments(m_toSend[3][m_disp_number], 3));
	shiftOut(m_DATA, m_CLOCK, MSBFIRST, map_segments(m_toSend[0][m_disp_number], 0));
	shiftOut(m_DATA, m_CLOCK, MSBFIRST, map_segments(m_toSend[1][m_disp_number], 1));
	digitalWrite(m_LATCH, HIGH);

	setDisp(m_disp_number, HIGH);

}


void Ipdisplay::clearDisplay(){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 3; j++){
			m_toSend[i][j] = 0;
		}
	}
}

void Ipdisplay::setDP(bool dp, byte position){
	if (dp)	m_toSend[position/3][position%3] |= m_toSend[position/3][position%3]|1;
	else m_toSend[position/3][position%3] &= ~(m_toSend[position/3][position%3]&1);
}
/**
 Buffer is composed of array of bytes:
   abcdefgp
 0b01101010 Digit1 \
 0b01101010 Digit2 | DISPLAY 0
 0b01101010 Digit3 /
 0b01101010 Digit4\
 0b01101010 Digit5| DISPLAY 1
 0b01101010 Digit6/
 0b01101010 Digit7\
 0b01101010 Digit8| DISPLAY 2
 0b01101010 Digit9/
 0b01101010 Digit10\
 0b01101010 Digit11| DISPLAY3
 0b01101010 Digit12/
 */
void Ipdisplay::computeBuffer(char buffer[], byte nbDigits){
	clearDisplay();
	//Seperate digit and display
	for (int i = 0; i < nbDigits; i++){
		m_toSend[i/3][2-i%3] = buffer[i];
	}
}


void Ipdisplay::displayString(char* str){
	int size=strlen(str);

	if (str[0]=='.') return; //NO
	char buffer[12] = {0};
	int segment = -1;
	for (int i = 0; i < size; i++){
		setDP(false, i);
		if (str[i]!='.') segment++;
		switch (toUpperCase(str[i])){
			case '.': buffer[segment]= buffer[segment] |1;break;
			case '0': buffer[segment] = IP_0; break;
			case '1': buffer[segment] = IP_1; break;
			case '2': buffer[segment] = IP_2; break;
			case '3': buffer[segment] = IP_3; break;
			case '4': buffer[segment] = IP_4; break;
			case '5': buffer[segment] = IP_5; break;
			case '6': buffer[segment] = IP_6; break;
			case '7': buffer[segment] = IP_7; break;
			case '8': buffer[segment] = IP_8; break;
			case '9': buffer[segment] = IP_9; break;

			case 'A': buffer[segment] = IP_A; break;
			case 'B': buffer[segment] = IP_B; break;
			case 'C': buffer[segment] = IP_C; break;
			case 'D': buffer[segment] = IP_D; break;
			case 'E': buffer[segment] = IP_E; break;
			case 'F': buffer[segment] = IP_F; break;
			case 'G': buffer[segment] = IP_G; break;
			case 'H': buffer[segment] = IP_H; break;
			case 'I': buffer[segment] = IP_I; break;
			case 'J': buffer[segment] = IP_J; break;
			case 'K': buffer[segment] = IP_K; break;
			case 'L': buffer[segment] = IP_L; break;
			case 'M': buffer[segment] = IP_M; break;
			case 'N': buffer[segment] = IP_N; break;
			case 'O': buffer[segment] = IP_O; break;
			case 'P': buffer[segment] = IP_P; break;
			case 'Q': buffer[segment] = IP_Q; break;
			case 'R': buffer[segment] = IP_R; break;
			case 'S': buffer[segment] = IP_S; break;
			case 'T': buffer[segment] = IP_T; break;
			case 'U': buffer[segment] = IP_U; break;
			case 'V': buffer[segment] = IP_V; break;
			case 'W': buffer[segment] = IP_W; break;
			case 'X': buffer[segment] = IP_X; break;
			case 'Y': buffer[segment] = IP_Y; break;
			case 'Z': buffer[segment] = IP_Z; break;

			case ' ': buffer[segment] = IP_SPACE; break;
			case '-': buffer[segment] = IP_HYPHEN; break;

			default:  buffer[segment] = IP_SPACE; break; // fallback
		}
	}
	computeBuffer(buffer, 12);
}
