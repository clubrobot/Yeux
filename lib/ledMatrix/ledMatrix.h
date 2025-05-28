

#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <Arduino.h>
#include "PeriodicProcess.h"
#include "configuration.h"
#include "alphabet.h"

/** class Pattern
 *  \brief Gère les motifs à afficher
 *
 *  permet de gérer les messages / animations à afficher sur une LedMatrix. 
 * 
 */
class Pattern : public PeriodicProcess
{
	friend class LedMatrix;

public:

	void init(byte starting_pattern);			// init the pattern
	void clearPatternToDisplay();				// Clear pattern to display array
	void clearPatterns();						// Clear _patterns array
	void setPattern();							// Set the current pattern into the patternToDisplay array
	void slidePattern();						// Slide the patternToDisplay array

private:

	byte _patternToDisplay[8];					// Pattern to display = {Row1,Row2,...,Row8}
	byte _patterns[NB_PATTERNS_MAX][8];			// Array of all the message to display
	byte _currentPattern;						// The position of the current pattern in the array _patterns
	byte _endOfPreviousPattern;					// Separation between 2 consecutive patterns being sliding
	byte _nbPatterns;							// Number of patterns having to be displayed
	byte _mode;									// mode of the matrix {SLIDE_MODE, ANIMATION_MODE}
	byte _patternWidth[NB_PATTERNS_MAX];		// The width of each pattern
	int _rotation;								// rotation of the pattern {0,90,180,270}
	int _defaultRotation;						// The default rotation of the pattern
	float _timeStep;

	virtual void process(float timestep);
	
};


class LedMatrix : public PeriodicProcess{

  public:

    void attach(byte dataPin, byte clockPin, byte latchPin, int rotation);							// Attach a matrix to its pin
	void updateMatrix();																			// Send data to the registers
	void initMatrix();																				// Init the matrix data + update data into registers
	void computeBuffer(char **buffer, int16_t sizeAnim, byte starting_pattern=0, bool progmem=false);					// Compute Serial input
	void enable();
	void disable();
	void update();
	void setMode(byte mode);		// Set mode of the matrix {SLIDE_MODE, ANIMATION_MODE}
	void changePatternSpeed(float timeStep);
    char** stringToPatterns(char *str);			//Convert a string to a Patern
	void displayText(char *str, byte mode=SLIDE_MODE, byte starting_pattern=0);

	static void displayBannerText(LedMatrix* banner[], char* str, byte mode=SLIDE_MODE, int16_t bannerSize=4);
	static void computeBufferBanner(LedMatrix* banner[], uint32_t **buffer, int16_t sizeAnim, bool progmem=false, byte mode=ANIMATION_MODE, int16_t bannerSize=4);
	static void changeBannerPatternSpeed(LedMatrix* banner[], float timestep, int16_t bannerSize=4);
  private:

    byte _DATAPIN;					// Matrix register data pin
    byte _CLOCKPIN;					// Matrix register clock pin
    byte _LATCHPIN;					// Matrix register latch pin
	int _data;						// Data to send to the registers
	int _maskColumns;				// Mask to identify Columns into _data
	byte _actualColumn;				// Column to be updated
	Pattern _pattern;
	

    virtual void process(float timestep);
    void display();
};



#endif //LEDMATRIX_H