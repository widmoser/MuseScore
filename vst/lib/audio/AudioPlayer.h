//
// Created by Hannes Widmoser on 15/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_PLAYER_H
#define ORCHESTRALINTERFACECMAKE_PLAYER_H

#include <portaudio.h>
#include <audio/AudioSampleBuffer.h>
#include <midi/MidiMessageBuffer.h>
#include <audio/AudioProcessor.h>

/**
 * Connects an audio processor
 */
class AudioPlayer {
public:
    AudioPlayer(double sampleRate, unsigned long frameSize, AudioProcessor *processor = nullptr);

    virtual ~AudioPlayer();

    virtual void start();

    virtual void stop();

    virtual void resume();

    virtual void suspend();

    bool isRunning() const;

    void setProcessor(AudioProcessor *processor);

    AudioProcessor *getProcessor() const;

    double getSampleRate() const;

    int getFrameSize() const;

    int getBufferSize() const;

protected:
    AudioSampleBuffer output;
    AudioProcessor *processor;

    const double sampleRate;
    const unsigned long frameSize;
    const unsigned long bufferSize;

    bool isStarted;
    bool isResumed;
};;

#endif //ORCHESTRALINTERFACECMAKE_PLAYER_H
