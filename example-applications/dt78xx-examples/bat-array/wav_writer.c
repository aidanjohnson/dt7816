/* 
 * File:   wav_writer.c
 * Author: Aidan Johnson
 * Email: johnsj96@uw.edu
 * 
 * Created on 26 June 2018, 14h29
 * 
 * A .wav audio file writer based on modifications of the following:
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

#include "wav_writer.h"

#include <string.h>
#include <assert.h>
#include <alloca.h>
#include <netinet/in.h>

void create_open_wavfile(wavfile *wav, int32_t sample_rate, 
                         int16_t num_channels, const char *path) {
    
    int bits_per_sample = 2; // 16-bit resolution, two byte signed integer
    wav->file = fopen(path, "wb+");
    assert(wav->file != NULL);
    wav->num_samples_writ = 0;
    wav->bits_per_sample = bits_per_sample;
    wav->num_channels = num_channels;
    wavfile_header file_header;
    file_header.riff_tag = htonl(0x52494646); // "RIFF"
    file_header.wave_tag = htonl(0x57415645); // "WAVE"
    file_header.fmt_tag = htonl(0x666d7420); // "fmt "
    file_header.data_tag = htonl(0x64617461); // "data"
    
    file_header.fmt_length = 16; // PCM
    file_header.audio_format = wav->bits_per_sample - 1; // 1 for PCM
    file_header.num_channels = wav->num_channels;
    file_header.sample_rate = sample_rate;
    file_header.byte_rate = sample_rate * wav->num_channels * wav->bits_per_sample / 8;
    file_header.block_align = wav->num_channels * wav->bits_per_sample / 8;
    file_header.bits_per_sample = wav->bits_per_sample;
    file_header.data_length = 0;
    file_header.riff_length = 0;
    
    fwrite(&file_header, sizeof(wavfile_header), 1, wav->file);
    wav->header = file_header;
}

void close_wav(wavfile *file) {
    uint32_t data_length = file->num_samples_writ * 
                           file->header.num_channels * 
                           file->bits_per_sample;
    fseek(file->file, 4, SEEK_SET);
    uint32_t size_length = 36 + data_length;
    fwrite(&size_length, sizeof(uint32_t), 1, file->file);
    
    fseek(file->file, 40, SEEK_SET);
    fwrite(&data_length, sizeof(uint32_t), 1, file->file);
    
    fclose(file->file);
    file->file = NULL;
}

int write_file(wavfile *wav, int16_t *data, int file_length) {
//    fprintf(stderr, "%s\n", wav->header.riff_tag);
    int16_t *z = (int16_t *) alloca(wav->header.num_channels*file_length*sizeof(int16_t));
    int i, j, k;
    for (i = 0, k = 0; i < file_length; ++i) {
        for (j = 0; j < wav->header.num_channels; ++j) {
            z[k++] = (int16_t) (data[j*file_length+i] * 32767.0f); // 2^15 - 1
        }
    }
    
    wav->num_samples_writ += file_length;
    return (int) fwrite(z, sizeof(int16_t), 
                        wav->header.num_channels * file_length, wav->file);
}
