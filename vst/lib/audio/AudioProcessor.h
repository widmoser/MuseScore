//
// Created by Hannes Widmoser on 15/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_AUDIOPROCESSOR_H
#define ORCHESTRALINTERFACECMAKE_AUDIOPROCESSOR_H

#include <vst/lib/audio/AudioSampleBuffer.h>
#include <vst/lib/midi/MidiMessageBuffer.h>

/**
 * Component that processes or generates audio.
 *
 * Note that an audio processor should not perform any long running resource allocation or deallocation in its constructor/destructor. Instead use the provided life-cycle methods for that.
 */
class AudioProcessor {
public:
    /**
     * Called before audio processing starts.
     *
     * Sub-classes should use this callback to allocate all needed resources.
     */
    virtual void start() = 0;

    /**
     * Called when processing is resumed after being temporarily suspended.
     */
    virtual void resume() = 0;

    /**
     * Called when processing is temporarily suspended.
     *
     * It is guaranteed, that there will be no call to processAudio, until resume is called.
     */
    virtual void suspend() = 0;

    /**
     * Called when audio processing is finished.
     *
     * After this method it is guaranteed that no more calls to processAudio will follow.
     *
     * Sub-classes should use this callback to releases all allocated resources.
     */
    virtual void stop() = 0;

    /**
     * Process or fill the provided audio buffer.
     *
     * A generator will fill the buffer and a processor will modify it.
     */
    virtual void processAudio(AudioSampleBuffer& buffer) = 0;
};


#endif //ORCHESTRALINTERFACECMAKE_AUDIOPROCESSOR_H
