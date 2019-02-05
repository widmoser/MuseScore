//
// Created by Hannes Widmoser on 15/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_PORTAUDIOPLAYER_H
#define ORCHESTRALINTERFACECMAKE_PORTAUDIOPLAYER_H

#include <portaudio.h>
#include <vst/lib/audio/AudioSampleBuffer.h>
#include <vst/lib/audio/AudioProcessor.h>
#include <vst/lib/audio/AudioPlayer.h>

/**
 * Connects an audio processor
 */
class PortAudioPlayer : public AudioPlayer {
public:
    PortAudioPlayer(double sampleRate, unsigned long frameSize, AudioProcessor* processor = nullptr);

    ~PortAudioPlayer();

    void start() override;

    void stop() override;

    void resume() override;

    void suspend() override;

    void processAudio(void* outputBuffer, unsigned long framesPerBuffer);

private:
    void initializeAudio();

    void releaseAudio();

    PaStream* stream;
};

#endif //ORCHESTRALINTERFACECMAKE_PORTAUDIOPLAYER_H
