//
// Created by Hannes Widmoser on 11/09/15.
//

#include "AudioHost.h"

AudioHost::AudioHost(double sampleRate, int frameSize) : sampleRate(sampleRate), frameSize(frameSize) {
}

double AudioHost::getSampleRate() const {
    return sampleRate;
}

int AudioHost::getFrameSize() const {
    return frameSize;
}

AudioHost::~AudioHost() {
}
