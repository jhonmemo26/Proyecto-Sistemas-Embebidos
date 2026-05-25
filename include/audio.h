#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>

void audio_init();

void record_audio();

int16_t* get_audio_buffer();

int get_audio_size();

#endif