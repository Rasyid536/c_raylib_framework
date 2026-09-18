#include "audio_manager.h"
#include "walk_sfx.h"
#include <stdlib.h>
#include "raylib.h"

static Sound sounds[SFX_MAX];

static Sound GenerateDummySound(float frequency, float duration) {
    Wave wave;
    wave.sampleRate = 44100;
    wave.sampleSize = 16;
    wave.channels = 1;

    wave.frameCount = (unsigned int)(wave.sampleRate * duration);

    short *data = (short *)malloc(wave.frameCount * (sizeof(short)));

    int period = wave.sampleRate / (int)frequency;
    for (unsigned int i = 0; i < wave.frameCount; i++) {
        if ((i / period) % 2 == 0) {
            data[i] = 800;
        } else {
            data[i] = -800;
        }
    }

    wave.data = data;

    Sound snd = LoadSoundFromWave(wave);

    free(wave.data);

    return(snd);
}

static Sound LoadSoundEmbedded(const unsigned char *data, int  size) {
    Wave wave = LoadWaveFromMemory(".wav", data, size);
    if (wave.frameCount == 0) {
        return GenerateDummySound(400.0f, 0.1f);
    }
    Sound snd = LoadSoundFromWave(wave);
    UnloadWave(wave);
    return snd;
}

void Audio_Init(void) {
    sounds[SFX_JUMP] = GenerateDummySound(400.0f, 0.1f);
    
    // Suara Kena Hit: Frekuensi rendah 150Hz, durasi agak panjang
    sounds[SFX_HIT]  = GenerateDummySound(150.0f, 0.25f);
    
    // Suara Koin: Frekuensi tinggi melengking 1200Hz, durasi sangat singkat
    sounds[SFX_WALK] = LoadSoundEmbedded(walk_sfx, walk_sfx_size);
}

void AudioManager_Play(SfxID id) {
    if (id >= 0 && id < SFX_MAX && !IsSoundPlaying(sounds[id])) {
        PlaySound(sounds[id]);
    }
}

void AudioManager_Free(void) {
    for (int i = 0; i < SFX_MAX; i++) {
        UnloadSound(sounds[i]);
    }
} 
