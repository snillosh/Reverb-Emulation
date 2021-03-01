/*
  ==============================================================================

    FeedbackCombFilter.cpp
    Created: 27 Feb 2021 12:58:01pm
    Author:  Bevan Salter

  ==============================================================================
*/

#include "FeedbackCombFilter.h"

FeedbackCombFilter::FeedbackCombFilter()
{
    
}

FeedbackCombFilter::~FeedbackCombFilter()
{
    
}

float FeedbackCombFilter::getDelayTime() const
{
    return fDelayTime;
}

void FeedbackCombFilter::setDelayTime(float delayTime)
{
    fDelayTime = delayTime;
}

float FeedbackCombFilter::getFilterCoeff() const
{
    return filterCoeff;
}

void FeedbackCombFilter::setFilterCoeff(float newFilterCoeffValue)
{
    filterCoeff = newFilterCoeffValue;
}

void FeedbackCombFilter::initialise()
{
    fSR = 44100;
    iBufferSize = (int)(4.0f * fSR); // set a 2 second buffer
    pfCircularBuffer = new float[iBufferSize];
    for (int x = 0; x<iBufferSize; x++)
        pfCircularBuffer[x] = 0;
    iBufferWritePos = 0;
    fDelayTime = 0.0;
    filterCoeff = 0.0;
}

void FeedbackCombFilter::reset()
{
    
}


float FeedbackCombFilter::processSample(float input)
{
    delayedSignal = pfCircularBuffer[iBufferReadPos];
    
    fVN = input - (filterCoeff * delayedSignal);
    
    fOut = (filterCoeff * fVN);
    

    //Circular Buffer setup and execution
    //---------------------------------------------------------------------------------------------
    pfCircularBuffer[iBufferWritePos] = fVN;
    iBufferWritePos++;
    if (iBufferWritePos > (iBufferSize -1))
        iBufferWritePos = 0;
    
    iBufferReadPos = iBufferWritePos - (fDelayTime * fSR);
    if (iBufferReadPos < 0){
        iBufferReadPos = (iBufferSize - (fDelayTime * fSR)) + iBufferWritePos;
    }
    else
    {
        iBufferReadPos = iBufferWritePos - (fDelayTime * fSR);
    }

    if (iBufferReadPos > (iBufferSize -1 ))
        iBufferReadPos = 0;
    //---------------------------------------------------------------------------------------------
    //delayedSignal = pfCircularBuffer[iBufferReadPos];
    
    return fOut;
}
