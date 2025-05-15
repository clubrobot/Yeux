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
	_currentPattern = (_currentPattern+1) % (_nbPatterns);
}


void Pattern::slidePattern() 
{
	if(_endOfPreviousPattern-(9-_patternWidth[_currentPattern])<0){
		_currentPattern = (_currentPattern+1) % (_nbPatterns);
		_endOfPreviousPattern = 7;
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

