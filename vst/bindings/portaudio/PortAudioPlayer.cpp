//
// Created by Hannes Widmoser on 15/09/15.
//

#include "PortAudioPlayer.h"

int processAudioWrapper(const void* inputBuffer, void* outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void* userData) {
    PortAudioPlayer* audioPlayer = reinterpret_cast<PortAudioPlayer*>(userData);
    audioPlayer->processAudio(outputBuffer, framesPerBuffer);
    return 0;
}

PortAudioPlayer::PortAudioPlayer(double sampleRate, unsigned long frameSize, AudioProcessor* processor) : AudioPlayer(
    sampleRate,
    frameSize,
    processor) {
    Pa_Initialize();
}

PortAudioPlayer::~PortAudioPlayer() {
    Pa_Terminate();
}

void PortAudioPlayer::start() {
    AudioPlayer::start();
    initializeAudio();
}

void PortAudioPlayer::resume() {
    AudioPlayer::resume();
    Pa_StartStream(stream);
}

void PortAudioPlayer::suspend() {
    Pa_StopStream(stream);
}

void PortAudioPlayer::stop() {
    releaseAudio();
    AudioPlayer::stop();
}

void PortAudioPlayer::initializeAudio() {
    PaDeviceIndex device = Pa_GetDefaultOutputDevice();

    PaStreamParameters outputParameters;
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.device = device;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    Pa_OpenStream(&stream, nullptr, &outputParameters, sampleRate, frameSize, paClipOff, processAudioWrapper, this);
    // TODO: error handling
}

void PortAudioPlayer::releaseAudio() {
    Pa_CloseStream(stream);
}

void PortAudioPlayer::processAudio(void* outputBuffer, unsigned long framesPerBuffer) {
    float* o = (float*) outputBuffer;
    processor->processAudio(output);
    for (int i = 0; i < framesPerBuffer; ++i) {
        *o++ = output.get(0, i);
        *o++ = output.get(1, i);
    }
}
