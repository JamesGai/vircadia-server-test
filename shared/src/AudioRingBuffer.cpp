//
//  AudioRingBuffer.cpp
//  interface
//
//  Created by Stephen Birarda on 2/1/13.
//  Copyright (c) 2013 HighFidelity, Inc. All rights reserved.
//

#include <cstring>
#include "AudioRingBuffer.h"

AudioRingBuffer::AudioRingBuffer(int ringSamples, int bufferSamples) {
    ringBufferLengthSamples = ringSamples;
    bufferLengthSamples = bufferSamples;
    
    started = false;
    addedToMix = false;
    
    endOfLastWrite = NULL;
    
    buffer = new int16_t[ringBufferLengthSamples];
    nextOutput = buffer;
};

AudioRingBuffer::AudioRingBuffer(const AudioRingBuffer &otherRingBuffer) {
    ringBufferLengthSamples = otherRingBuffer.ringBufferLengthSamples;
    bufferLengthSamples = otherRingBuffer.bufferLengthSamples;
    started = otherRingBuffer.started;
    addedToMix = otherRingBuffer.addedToMix;
    
    buffer = new int16_t[ringBufferLengthSamples];
    memcpy(buffer, otherRingBuffer.buffer, sizeof(int16_t) * ringBufferLengthSamples);
    
    nextOutput = buffer + (otherRingBuffer.nextOutput - otherRingBuffer.buffer);
    endOfLastWrite = buffer + (otherRingBuffer.endOfLastWrite - otherRingBuffer.buffer);
}

AudioRingBuffer::~AudioRingBuffer() {
    delete[] buffer;
};

AudioRingBuffer* AudioRingBuffer::clone() const {
    return new AudioRingBuffer(*this);
}

int16_t* AudioRingBuffer::getNextOutput() {
    return nextOutput;
}

void AudioRingBuffer::setNextOutput(int16_t *newPointer) {
    nextOutput = newPointer;
}

int16_t* AudioRingBuffer::getEndOfLastWrite() {
    return endOfLastWrite;
}

void AudioRingBuffer::setEndOfLastWrite(int16_t *newPointer) {
    endOfLastWrite = newPointer;
}

int16_t* AudioRingBuffer::getBuffer() {
    return buffer;
}

bool AudioRingBuffer::isStarted() {
    return started;
}

void AudioRingBuffer::setStarted(bool status) {
    started = status;
}

bool AudioRingBuffer::wasAddedToMix() {
    return addedToMix;
}

void AudioRingBuffer::setAddedToMix(bool added) {
    addedToMix = added;
}

float* AudioRingBuffer::getPosition() {
    return position;
}

void AudioRingBuffer::setPosition(float *newPosition) {
    position[0] = newPosition[0];
    position[1] = newPosition[1];
    position[2] = newPosition[2];
}

void AudioRingBuffer::parseData(void *data, int size) {
    unsigned char *audioDataStart = (unsigned char *) data;
    
    if (size > (bufferLengthSamples * sizeof(int16_t))) {
        
        for (int p = 0; p < 3; p ++) {
            memcpy(&position[p], audioDataStart + 1 + (sizeof(float) * p), sizeof(float));
        }
        
        audioDataStart += (1 + (sizeof(float) * 3));
    }

    if (endOfLastWrite == NULL) {
        endOfLastWrite = buffer;
    } else if (diffLastWriteNextOutput() > ringBufferLengthSamples - bufferLengthSamples) {
        endOfLastWrite = buffer;
        nextOutput = buffer;
        started = false;
    }
    
    memcpy(endOfLastWrite, audioDataStart, bufferLengthSamples * sizeof(int16_t));
    
    endOfLastWrite += bufferLengthSamples;
    
    addedToMix = false;
    
    if (endOfLastWrite >= buffer + ringBufferLengthSamples) {
        endOfLastWrite = buffer;
    }    
}

short AudioRingBuffer::diffLastWriteNextOutput()
{
    if (endOfLastWrite == NULL) {
        return 0;
    } else {
        short sampleDifference = endOfLastWrite - nextOutput;
        
        if (sampleDifference < 0) {
            sampleDifference += ringBufferLengthSamples;
        }
        
        return sampleDifference;
    }
}
