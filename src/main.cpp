#include <Arduino.h>

#include "animations.h"
#include "configuration.h"
#include "ledMatrix.h"
#include "IPDisplay.h"

// Variables
LedMatrix ledmatrix1;
LedMatrix ledmatrix2;
LedMatrix ledmatrix3;
LedMatrix ledmatrix4;

LedMatrix *banner[4] = {&ledmatrix2, &ledmatrix1, &ledmatrix4, &ledmatrix3};

Ipdisplay ipdisplay;



//TODO: EMOJI and lowercase letter
void setup() {
    // Variables initialisation
    Serial.begin(115200);
    Serial.setTimeout(250);
    ipdisplay.attach(DATA_IP, CLOCK_IP, LATCH_IP);
    ipdisplay.setTimestep(IP_DISPLAY_TIMESTEP);
    ipdisplay.enable();

    ipdisplay.displayString("ouga bouga");


    ledmatrix1.attach(DATA_MATRIX1, CLOCK_MATRIX1, LATCH_MATRIX1, ROTATION_MATRIX_3);
    ledmatrix1.setTimestep(LED_MATRIX_TIMESTEP);
    ledmatrix1.enable();

    ledmatrix2.attach(DATA_MATRIX2, CLOCK_MATRIX2, LATCH_MATRIX2, ROTATION_MATRIX_3);
    ledmatrix2.setTimestep(LED_MATRIX_TIMESTEP);
    ledmatrix2.enable();

    ledmatrix3.attach(DATA_MATRIX3, CLOCK_MATRIX3, LATCH_MATRIX3, ROTATION_MATRIX_3);
    ledmatrix3.setTimestep(LED_MATRIX_TIMESTEP);
    ledmatrix3.enable();

    ledmatrix4.attach(DATA_MATRIX4, CLOCK_MATRIX4, LATCH_MATRIX4, ROTATION_MATRIX_3);
    ledmatrix4.setTimestep(LED_MATRIX_TIMESTEP);
    ledmatrix4.enable();

    //LedMatrix::displayBannerText(banner, "AISPRID    ", SLIDE_MODE);
    LedMatrix::changeBannerPatternSpeed(banner, 0.5);

    LedMatrix::computeBufferBanner(banner, (uint32_t **) animations::animationTwTCry, 9, true);

}

long LedUpdatePrevTime;
long SwitchAnimPrevTime;
long timeInABottle;

bool animCounter = 0;
String BannerText;

void loop() {

    if (Serial.available() > 0) {
        String incomingData = Serial.readStringUntil('\n');
        int ip_separator = incomingData.indexOf('$');
        int time_seperator = incomingData.indexOf('*');
        char mode = incomingData.charAt(0);

        if (time_seperator) {
            BannerText = incomingData.substring(1, time_seperator);
            float time = incomingData.substring(time_seperator + 1, ip_separator).toInt() / 1000.0;
            LedMatrix::changeBannerPatternSpeed(banner, time);
        } else if (ip_separator != 0) BannerText = incomingData.substring(1, ip_separator);

        switch (mode) {
            case 'S':
                //Slide Mode
                LedMatrix::displayBannerText(banner, (char *) BannerText.c_str(), SLIDE_MODE);
                break;
            case 'T':
                //sTatic Mode
                LedMatrix::displayBannerText(banner, (char *) BannerText.c_str(), STATIC_MODE);
                break;
            case 'A':
                switch (BannerText.charAt(0)) {
                    case '0':
                        LedMatrix::computeBufferBanner(banner, (uint32_t **) animations::anim32Bit, 2, true);
                        break;
                    case '1':
                        LedMatrix::computeBufferBanner(banner,(uint32_t **) animations::animationEyes, 4, true);
                        break;
                    case '2':
                        LedMatrix::computeBufferBanner(banner, (uint32_t **) animations::animationUwU, 4, true);
                        break;
                    case '3':
                        LedMatrix::computeBufferBanner(banner, (uint32_t **) animations::animationTwTCry, 9, true);
                        break;
                    case '4':
                        LedMatrix::computeBufferBanner(banner, (uint32_t **) animations::animationStarEyes, 8, true);
                        break;
                    case '5':
                        LedMatrix::computeBufferBanner(banner, (uint32_t **) animations::tortueWalkRight, 4, true);
                        break;
                    case '6':
                        LedMatrix::computeBufferBanner(banner, (uint32_t **) animations::tortueWalkLeft, 4, true);
                        break;

                }
                break;
            default:
                break;
        }


        if (ip_separator != -1) {
            String IPText = incomingData.substring(ip_separator + 1);

            String lenOfString = IPText;
            lenOfString.replace(".", "");
            if (lenOfString.length() <= 12) {
                ipdisplay.displayString((char *) IPText.c_str());
            }
        }


        while (Serial.available() > 0) Serial.read();
    }

    ledmatrix1.update();
    ledmatrix2.update();
    ledmatrix3.update();
    ledmatrix4.update();
    ipdisplay.update();


    timeInABottle = millis();
    if ((timeInABottle - SwitchAnimPrevTime) >= 1000) {
        SwitchAnimPrevTime = timeInABottle;
        ipdisplay.setDP(animCounter, 9);
        animCounter = !animCounter;
    }
}
