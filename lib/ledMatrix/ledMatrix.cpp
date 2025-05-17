#include "ledMatrix.h"


void LedMatrix::attach(byte dataPin, byte clockPin, byte latchPin, int rotation)
{
	_DATAPIN = dataPin;
	_CLOCKPIN = clockPin;
	_LATCHPIN = latchPin;
	_pattern._rotation = rotation;
	_pattern._defaultRotation = rotation;
	pinMode(_DATAPIN, OUTPUT);
	pinMode(_CLOCKPIN, OUTPUT);
	pinMode(_LATCHPIN, OUTPUT);
	_actualColumn = 0;
	initMatrix();
	_pattern.init(0);
	changePatternSpeed(DEFAULT_PATTERN_TIMESTEP);
	char initMessage[1][8];
	for(int i = 0;i<8;i++){
		initMessage[0][i] = 0xFF;
	}
	computeBuffer((char**) initMessage, 1);
	setMode(ANIMATION_MODE);

}



void LedMatrix::changePatternSpeed(float timeStep){
	_pattern._timeStep = timeStep;
	_pattern.setTimestep(_pattern._timeStep);
}

void LedMatrix::changeBannerPatternSpeed(LedMatrix* banner[], float timeStep, int16_t bannerSize){
	for(int i = 0;i<bannerSize;i++){
		banner[i]->_pattern._timeStep = timeStep;
		banner[i]->_pattern.setTimestep(banner[i]->_pattern._timeStep);
	}

}

char** LedMatrix::stringToPatterns(char *str){
	uint16_t size = strlen(str);
	char **ret = (char**)malloc(size * sizeof(char*));
	for(uint16_t i = 0;i<size;i++){
		switch (str[i]){
		case ' ': ret[i] = (char*) SPACE; break;
		case '0': ret[i] = (char*)NUM_0; break;
		case '1': ret[i] = (char*)NUM_1; break;
		case '2': ret[i] = (char*)NUM_2; break;
		case '3': ret[i] = (char*)NUM_3; break;
		case '4': ret[i] = (char*)NUM_4; break;
		case '5': ret[i] = (char*)NUM_5; break;
		case '6': ret[i] = (char*)NUM_6; break;
		case '7': ret[i] = (char*)NUM_7; break;
		case '8': ret[i] = (char*)NUM_8; break;
		case '9': ret[i] = (char*)NUM_9; break;
		case 'a': ret[i]= (char*)A;break;
		case 'A': ret[i]= (char*)A;break;
		case 'b': ret[i] = (char*) B; break;
		case 'B': ret[i] = (char*) B; break;
		case 'c': ret[i] = (char*) C; break;
		case 'C': ret[i] = (char*) C; break;
		case 'd': ret[i] = (char*) D; break;
		case 'D': ret[i] = (char*) D; break;
		case 'e': ret[i] = (char*) E; break;
		case 'E': ret[i] = (char*) E; break;
		case 'f': ret[i] = (char*) F; break;
		case 'F': ret[i] = (char*) F; break;
		case 'g': ret[i] = (char*) G; break;
		case 'G': ret[i] = (char*) G; break;
		case 'h': ret[i] = (char*) H; break;
		case 'H': ret[i] = (char*) H; break;
		case 'i': ret[i] = (char*) I; break;
		case 'I': ret[i] = (char*) I; break;
		case 'j': ret[i] = (char*) J; break;
		case 'J': ret[i] = (char*) J; break;
		case 'k': ret[i] = (char*) K; break;
		case 'K': ret[i] = (char*) K; break;
		case 'l': ret[i] = (char*) L; break;
		case 'L': ret[i] = (char*) L; break;
		case 'm': ret[i] = (char*) M; break;
		case 'M': ret[i] = (char*) M; break;
		case 'n': ret[i] = (char*) N; break;
		case 'N': ret[i] = (char*) N; break;
		case 'o': ret[i] = (char*) O; break;
		case 'O': ret[i] = (char*) O; break;
		case 'p': ret[i] = (char*) P; break;
		case 'P': ret[i] = (char*) P; break;
		case 'q': ret[i] = (char*) Q; break;
		case 'Q': ret[i] = (char*) Q; break;
		case 'r': ret[i] = (char*) R; break;
		case 'R': ret[i] = (char*) R; break;
		case 's': ret[i] = (char*) S; break;
		case 'S': ret[i] = (char*) S; break;
		case 't': ret[i] = (char*) T; break;
		case 'T': ret[i] = (char*) T; break;
		case 'u': ret[i] = (char*) U; break;
		case 'U': ret[i] = (char*) U; break;
		case 'v': ret[i] = (char*) V; break;
		case 'V': ret[i] = (char*) V; break;
		case 'w': ret[i] = (char*) W; break;
		case 'W': ret[i] = (char*) W; break;
		case 'x': ret[i] = (char*) X; break;
		case 'X': ret[i] = (char*) X; break;
		case 'y': ret[i] = (char*) Y; break;
		case 'Y': ret[i] = (char*) Y; break;
		case 'z': ret[i] = (char*) Z; break;
		case 'Z': ret[i] = (char*) Z; break;
		}
	}
	return ret;
}

void LedMatrix::displayText(char* str, byte mode, byte starting_pattern){
	int16_t size = strlen(str);
	char** paternToApply = stringToPatterns(str);
	this->computeBuffer(paternToApply, size, starting_pattern);
	this->setMode(mode);
	free(paternToApply);
}

void LedMatrix::displayBannerText(LedMatrix* banner[], char* str, byte mode, int16_t bannerSize){
	for (int16_t i = 0; i < bannerSize; i++){
		banner[i]->displayText(str, mode, i);
	}
}

/**
 * @brief
 * @param banner
 * @param buffer
 * @param sizeAnim
 * @param bannerSize
 * @param mode

  each frame is composed of a 64bit (4*8) representation of on or off leds:
	0b01101100 01101100 01101100 01101100
	0b01101100 01101100 01101100 01101100
	0b01101100 01101100 01101100 01101100
	0b01101100 01101100 01101100 01101100
	0b01101100 01101100 01101100 01101100
	0b01101100 01101100 01101100 01101100
	0b01101100 01101100 01101100 01101100
	0b01101100 01101100 01101100 01101100
	0b01101100 01101100 01101100 01101100
		LED1	LED2      LED3	   LED4
 */
void LedMatrix::computeBufferBanner(LedMatrix* banner[], int **buffer, int16_t sizeAnim, byte mode, int16_t bannerSize){
	if (bannerSize > 4) return; //NO
	byte starting_pos = 0;
	for (int16_t matrixNum = 0; matrixNum < bannerSize; matrixNum++){
		char **bufferMat = (char**) malloc(sizeAnim * sizeof(char*));

		for (int16_t frame = 0; frame < sizeAnim; frame++){
			bufferMat[frame] = (char*) malloc(8 * sizeof(char));
			for (byte row = 0; row < 8; row++){
				//Pour chaque ligne de chaque frame, on décale le bufferBanner pour avoir un buffer classique
				bufferMat[frame][row] = (char) ((buffer[frame][row]>>(8-matrixNum*8))&0xFF);
			}
		}
		//On applique la frame
		banner[matrixNum]->computeBuffer(bufferMat, sizeAnim, starting_pos);
		banner[matrixNum]->setMode(mode);
		if (mode==SLIDE_MODE)starting_pos++;//Pour appliquer le slide, on décale le début de chaque frame
		for (int16_t frame = 0; frame < sizeAnim; frame++){free(bufferMat[frame]);}
		free(bufferMat);
	}
}

void LedMatrix::enable()
{
	PeriodicProcess::enable();
	_pattern.enable();
}

void LedMatrix::disable()
{
	PeriodicProcess::disable();
	_pattern.disable();
}

void LedMatrix::update()
{
	PeriodicProcess::update();
	_pattern.update();
}

void LedMatrix::setMode(byte mode)
{
	_pattern._mode = mode;
	_pattern._rotation = _pattern._defaultRotation;		// Reset of the rotation 
}

void LedMatrix::process(float timestep)
{
	Clock clk;
	_data|=_maskColumns;  // Turn all column off
	_actualColumn++;
	if (_actualColumn >= 8) {
		_actualColumn = 0;
	}
	switch(_pattern._rotation){
		case 90 : 				// 90° rotation
					for (int row = 0; row < 8; row++) {
						if (_pattern._patternToDisplay[_actualColumn]&(0x01<<(row))) {
							_data|=rows[row];  // Turn on this led
						}
						else {
							_data&=~(rows[row]); // Turn off this led
						}
					}
					break;
		case 180 :				// 180° rotation
					for (int row = 0; row < 8; row++) {
						if (_pattern._patternToDisplay[7-row]&(0x01<<(_actualColumn))) {
							_data|=rows[row];  // Turn on this led
						}
						else {
							_data&=~(rows[row]); // Turn off this led
						}
					}
					break;
		case 270 : 				// 270° rotation
					for (int row = 0; row < 8; row++) {
						if (_pattern._patternToDisplay[7-_actualColumn]&(0x01<<(7-row))) {
							_data|=rows[row];  // Turn on this led
						}
						else {
							_data&=~(rows[row]); // Turn off this led
						}
					}
					break;
		default :				// 0° rotation 
					for (int row = 0; row < 8; row++) {
						if (_pattern._patternToDisplay[row]&(0x01<<(7-_actualColumn))) {
							_data|=rows[row];  // Turn on this led
						}
						else {
							_data&=~(rows[row]); // Turn off this led
						}
					}

	}
	_data&= ~(cols[_actualColumn]); // Turn whole column on at once
	updateMatrix();
}


void LedMatrix::updateMatrix()
{
	byte octet1 = _data&0x00FF;
	byte octet2 = (_data&0xFF00)>>8;
	digitalWrite(_LATCHPIN,LOW);
	shiftOut(_DATAPIN,_CLOCKPIN,MSBFIRST,octet1);
	shiftOut(_DATAPIN,_CLOCKPIN,MSBFIRST,octet2);
	digitalWrite(_LATCHPIN,HIGH);
}


void LedMatrix::initMatrix() 
{
	//col à 0 pour allumer row à 1 pour allumer
	_data = 0;
	for(int i = 0;i<8;i++){
		_data+=cols[i];
	}
	_maskColumns = _data;
	updateMatrix();
}

void LedMatrix::computeBuffer(char **buffer, int16_t sizeAnim, byte starting_pattern)
{
  //On copie chaque frame de l'anim dans leurs paterns respectifs.
	_pattern.clearPatterns();
	int i;
	for (i = 0; i < NB_PATTERNS_MAX && i <sizeAnim; i++) {
		for (int j = 0; j < 8; j++) {
			_pattern._patterns[i][j] = buffer[i][j];
			_pattern._patternWidth[i] = 8;
		}
	}
	_pattern.init(starting_pattern);
	_pattern._nbPatterns = sizeAnim;
}

void Pattern::init(byte starting_pattern)
{
	_endOfPreviousPattern = 7;
	_currentPattern = starting_pattern;
	_nbPatterns = 9;
	clearPatternToDisplay();
}

void Pattern::clearPatternToDisplay() 
{
	// Clear pattern to display array
	for (int i = 0; i < 8; i++) {
		_patternToDisplay[i] = 0;
	}
}

void Pattern::clearPatterns()
{
	// Clear patterns message
	for (int i = 0; i<NB_PATTERNS_MAX; i++){
		for (int j = 0; j<8; j++){
			_patterns[i][j] = 0;
		}
	}
}


void Pattern::setPattern()
{
	for (int i = 0; i < 8; i++) {
		_patternToDisplay[i] = _patterns[_currentPattern][i] ;
		_patternToDisplay[i] = _patternToDisplay[i]>>((8-_patternWidth[_currentPattern])/2);	// Centering of the pattern

	}
	if (_mode != STATIC_MODE) _currentPattern = (_currentPattern+1) % (_nbPatterns);
}


void Pattern::slidePattern() 
{
	if(_endOfPreviousPattern-(9-_patternWidth[_currentPattern])<0){
		_currentPattern = (_currentPattern+1) % (_nbPatterns);
		_endOfPreviousPattern = 8;
	}
	_endOfPreviousPattern--;	
    for (int row = 0; row < 8; row++) {
        _patternToDisplay[row] = _patternToDisplay[row]<<1;
		if ((_patterns[_currentPattern][row] & 0x01 <<  (_endOfPreviousPattern+1)%8) >= 1)
    		_patternToDisplay[row] |= 0x01 ;
	}
}

void Pattern::process(float timestep)
{
	switch(_mode){
		case SLIDE_MODE:
			slidePattern();
			break;
		case ANIMATION_MODE:
			setPattern();
			break;
		case STATIC_MODE:
			setPattern();
			break;
		case RIGHT_ROTATION_MODE:
			_rotation+=90;
			if(_rotation>270)
				_rotation = 0;
			setPattern();
			break;
		case LEFT_ROTATION_MODE:
			_rotation-=90;
			if(_rotation<0)
				_rotation = 270;
			setPattern();
			break;
		case UPSIDEDOWN_MODE:
			_rotation+=180;
			if(_rotation>270)
				_rotation = _defaultRotation%180;
			setPattern();
			break;
	}
}

