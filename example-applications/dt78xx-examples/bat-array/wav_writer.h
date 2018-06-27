/* 
 * File:   wav_writer.h
 * Author: Aidan Johnson
 * Email: johnsj96@uw.edu
 * 
 * Created on 26 June 2018, 14h29
 * 
 * Header for a .wav audio file writer based on modifications of the following:
 * 
 * Copyright (c) 2015-2017, Martin Roth (mhroth@gmail.com)
 * https://github.com/mhroth/tinywav
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 * 
 * --AND--
 * 
 * A simple sound library for CSE 20211 by Douglas Thain (dthain@nd.edu).
 * This work is made available under the Creative Commons Attribution license.
 * https://creativecommons.org/licenses/by/4.0/
 * https://www3.nd.edu/~dthain/courses/cse20211/fall2013/wavfile/
 * 
 * --AND--
 * 
 * Andrew Ippoliti (24 November 2013)
 * http://blog.acipo.com/generating-wave-files-in-c/
 * 
 */

#ifndef WAV_WRITER_H
#define WAV_WRITER_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct wavfile_header {
    uint32_t riff_tag;
    uint32_t riff_length;
    uint32_t wave_tag;
    uint32_t fmt_tag;
    uint32_t fmt_length;
    uint32_t audio_format;
    uint32_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint32_t block_align;
    uint32_t bits_per_sample;
    uint32_t data_tag;
    uint32_t data_length;
} wavfile_header;

typedef struct wavfile {
    FILE *file;
    wavfile_header header;
    uint32_t num_samples_writ;
    uint16_t bits_per_sample;
    uint16_t num_channels;
} wavfile;

void create_open_wavfile(wavfile *wav, int32_t sample_rate, 
                         int16_t num_channels, const char *path);

void close_wav(wavfile *file);

int write_file(wavfile *wav, int16_t data[], int file_length);

#endif /* WAV_WRITER_H */