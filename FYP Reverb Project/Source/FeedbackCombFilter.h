/*
  ==============================================================================

    FeedbackCombFilter.h
    Created: 27 Feb 2021 12:58:01pm
    Author:  Bevan Salter

  ==============================================================================
*/

#pragma once


class FeedbackCombFilter
{
public:
    FeedbackCombFilter();
    ~FeedbackCombFilter();
    
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
