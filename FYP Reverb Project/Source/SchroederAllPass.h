/*
  ==============================================================================

    SchroederAllPass.h
    Created: 27 Feb 2021 11:58:49am
    Author:  Bevan Salter

  ==============================================================================
*/

#pragma once


class SchroederAllPass
{
public:
    SchroederAllPass();
    ~SchroederAllPass();
    
    float getDelayTime() const;
    
    void setDelayTime (float delayTime);
    
    float getFilterCoeff() const;
    
    void setFilterCoeff(float newFilterCoeffValue);
    
    void initialise ();
    
    void reset();
    
    float processSample(float input);
    
private:
    
    float *pfCircularBuffer;
    float fSR;
    int iBufferSize;
    int iBufferWritePos;
    int iBufferReadPos;
    
    float filterCoeff;
    float fDelayTime;
    
    float fOut;
    float fVN;
    float fIn;
    float delayedSignal;
};
