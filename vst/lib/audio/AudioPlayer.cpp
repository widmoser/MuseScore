//
// Created by Hannes Widmoser on 15/09/15.
//

#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(double sampleRate,
                         unsigned long frameSize,
                         AudioProcessor *processor)
    : sampleRate(sampleRate), frameSize(frameSize), output(128, frameSize),
      processor(processor),
      bufferSize(frameSize * (int) sizeof(float) * 2) {
}

AudioPlayer::~AudioPlayer() {
    stop();
}

void AudioPlayer::start() {
    isStarted = true;

    if (processor != nullptr) {
        processor->start();
    }

    resume();
}

void AudioPlayer::stop() {
    suspend();

    isStarted = false;

    if (processor != nullptr) {
        processor->stop();
    }
}

void AudioPlayer::resume() {
    isResumed = true;
    if (processor != nullptr) {
        processor->resume();
    }
}

void AudioPlayer::suspend() {
    isResumed = false;
    if (processor != nullptr) {
        processor->suspend();
    }
}

bool AudioPlayer::isRunning() const {
    return isResumed;
}

void AudioPlayer::setProcessor(AudioProcessor *processor) {
    if (this->processor != nullptr) {
        if (isResumed) {
            processor->suspend();
        }
        if (isStarted) {
            processor->stop();
        }
    }
    this->processor = processor;
    if (isStarted) {
        processor->start();
    }
    if (isResumed) {
        processor->resume();
    }
}

AudioProcessor *AudioPlayer::getProcessor() const {
    return processor;
}

double AudioPlayer::getSampleRate() const {
    return sampleRate;
}

int AudioPlayer::getFrameSize() const {
    return frameSize;
}

int AudioPlayer::getBufferSize() const {
    return bufferSize;
}
