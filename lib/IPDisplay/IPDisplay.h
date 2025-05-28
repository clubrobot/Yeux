#include <Arduino.h>
#include "PeriodicProcess.h"
#include "configuration.h"
#include "alphabet.h"

#ifndef IPDISPLAY_H
#define IPDISPLAY_H


class Ipdisplay : public PeriodicProcess
{

  public:
    Ipdisplay() : PeriodicProcess(), m_nb_ips(0) {}
    void attach(byte dataPin, byte clockPin, byte latchPin);
    void clearDisplay();
    void computeBuffer(char buffer[], byte nbDigits);
    void displayString(char * str);
    void setDP(bool dp, byte position);
  private:
    char m_toSend[4][3];
    byte m_DATA;
    byte m_CLOCK;
    byte m_LATCH;
    byte m_disp_number; // Number of the effective 7 seg display
    float m_acc_time;
    byte m_nb_ips;
    byte m_current_ip;

    virtual void process(float timestep);
    void display();
};

#endif