//
// Created by Hannes Widmoser on 09/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_AUDIOSAMPLEBUFFER_H
#define ORCHESTRALINTERFACECMAKE_AUDIOSAMPLEBUFFER_H

#include <stddef.h>

/**
 * An audio sample buffer that can be used to exchange audio information.
 */
class AudioSampleBuffer {
public:
    AudioSampleBuffer(int maxNumChannels, int frameSize);
    explicit AudioSampleBuffer(int maxNumChannels, int frameSize, float** buffer);

    ~AudioSampleBuffer();

    void set(int channel, int sample, float value);

    float get(int channel, int sample);

    float** getChannels();

    void setNumChannels(int channels);

    void clear();

    int getNumChannels() const;

    int getFrameSize() const;

    int getMaxNumChannels() const;

    void copy(float** target) const;

private:
    void resetChannelPointers();

    void allocate();

    int maxNumChannels;
    int numChannels;
    int frameSize;

    size_t allocatedBytes;
    char* data;
    float** channels;
    float** originalChannels;
};


#endif //ORCHESTRALINTERFACECMAKE_AUDIOSAMPLEBUFFER_H
