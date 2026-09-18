#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

typedef enum {
    SFX_JUMP,
    SFX_HIT,
    SFX_WALK,
    SFX_MAX
} SfxID;

void AudioManager_Free(void);
void AudioManager_Play(SfxID id);
void Audio_Init(void);
#endif
