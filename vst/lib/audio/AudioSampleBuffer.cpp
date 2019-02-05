//
// Created by Hannes Widmoser on 09/09/15.
//

#include <cstddef>
#include <cstdlib>
#include <algorithm>

#include "AudioSampleBuffer.h"

AudioSampleBuffer::AudioSampleBuffer(int maxNumChannels, int frameSize)
    : maxNumChannels(maxNumChannels), frameSize(frameSize), numChannels(maxNumChannels) {
    allocate();
}

AudioSampleBuffer::AudioSampleBuffer(int maxNumChannels, int frameSize, float** buffer)
    : maxNumChannels(maxNumChannels), frameSize(frameSize), numChannels(maxNumChannels), channels(buffer) {

}

void AudioSampleBuffer::allocate() {
    const size_t channelListSize = sizeof(float*) * (size_t) (maxNumChannels + 1);
    allocatedBytes = (size_t) maxNumChannels * (size_t) frameSize * sizeof(float) + channelListSize + 32;
    data = (char*) std::malloc(allocatedBytes);

    originalChannels = reinterpret_cast<float**>(data);

    float* chan = (float*) (data + channelListSize);
    for (int i = 0; i < maxNumChannels; ++i) {
        originalChannels[i] = chan;
        chan += frameSize;
    }

    originalChannels[maxNumChannels] = nullptr;
    channels = new float* [maxNumChannels];
    resetChannelPointers();
}

AudioSampleBuffer::~AudioSampleBuffer() {
    if (allocatedBytes > 0) {
        // Don't delete when we are only wrapping a buffer.
        std::free(data);
        delete channels;
    }
}

float** AudioSampleBuffer::getChannels() {
    return channels;
}

void AudioSampleBuffer::set(int channel, int sample, float value) {
    channels[channel][sample] = value;
}

float AudioSampleBuffer::get(int channel, int sample) {
    return channels[channel][sample];
}

void AudioSampleBuffer::clear() {
    for (int channel = 0; channel < maxNumChannels; ++channel) {
        for (long frame = 0; frame < frameSize; ++frame) {
            originalChannels[channel][frame] = 0.0f;
        }
    }
}

int AudioSampleBuffer::getNumChannels() const {
    return numChannels;
}

int AudioSampleBuffer::getFrameSize() const {
    return frameSize;
}

void AudioSampleBuffer::setNumChannels(int c) {
    resetChannelPointers();
    for (int i = c; i < maxNumChannels; ++i) {
        channels[i] = nullptr;
    }
    numChannels = c;
}

int AudioSampleBuffer::getMaxNumChannels() const {
    return maxNumChannels;
}

void AudioSampleBuffer::copy(float** target) const {
    std::copy(channels, channels + maxNumChannels*frameSize, target);
}

void AudioSampleBuffer::resetChannelPointers() {
    for (int i = 0; i < maxNumChannels; ++i) {
        channels[i] = originalChannels[i];
    }
    numChannels = maxNumChannels;
}
