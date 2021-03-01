/*
  ==============================================================================

    SchroederAllPass.cpp
    Created: 27 Feb 2021 11:58:49am
    Author:  Bevan Salter

  ==============================================================================
*/

#include "SchroederAllPass.h"

SchroederAllPass::SchroederAllPass()
{
    
}

SchroederAllPass::~SchroederAllPass()
{
    
}


float SchroederAllPass::getDelayTime() const
{
    return fDelayTime;
}

void SchroederAllPass::setDelayTime(float delayTime)
{
    fDelayTime = delayTime;
}

float SchroederAllPass::getFilterCoeff() const
{
    return filterCoeff;
}

void SchroederAllPass::setFilterCoeff(float newFilterCoeffValue)
{
    filterCoeff = newFilterCoeffValue;
}

void SchroederAllPass::initialise()
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

void SchroederAllPass::reset()
{
    
}


float SchroederAllPass::processSample(float input)
{
    fOut = fDelSig + input;
    thirdSignal = fOut * filterCoeff;
    iBufferWritePos++;
    if (iBufferWritePos > (iBufferSize -1))
        iBufferWritePos = 0;
    pfCircularBuffer[iBufferWritePos] = fOut;
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
    fDelSig = pfCircularBuffer[iBufferReadPos];
    fDelSig = fDelSig * (filterCoeff * -1.f);
    return fOut + thirdSignal;
}

