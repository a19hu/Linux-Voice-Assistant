#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <signal.h>
#include <unistd.h>

#define PCM_DEVICE "default"
#define SAMPLE_RATE 44100
#define CHANNELS 1
#define BUFFER_SIZE 128
#define DURATION 5  // Duration in seconds

void write_wav_header(FILE *file, int sample_rate, int channels, int num_samples) {
    int byte_rate = sample_rate * channels * 2;
    int data_size = num_samples * channels * 2;

    // Write WAV header
    fwrite("RIFF", 1, 4, file);
    int chunk_size = 36 + data_size;
    fwrite(&chunk_size, 4, 1, file);
    fwrite("WAVE", 1, 4, file);
    fwrite("fmt ", 1, 4, file);
    int subchunk1_size = 16;
    fwrite(&subchunk1_size, 4, 1, file);
    short audio_format = 1;
    fwrite(&audio_format, 2, 1, file);
    fwrite(&channels, 2, 1, file);
    fwrite(&sample_rate, 4, 1, file);
    fwrite(&byte_rate, 4, 1, file);
    short block_align = channels * 2;
    fwrite(&block_align, 2, 1, file);
    short bits_per_sample = 16;
    fwrite(&bits_per_sample, 2, 1, file);
    fwrite("data", 1, 4, file);
    fwrite(&data_size, 4, 1, file);
}

// Signal handler for alarm signal to force program exit
void handle_alarm(int sig) {
    printf("Recording duration reached. Exiting...\n");
    exit(0);
}

int main() {
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;
    FILE *output_file = fopen("recording.wav", "wb");

    if (!output_file) {
        fprintf(stderr, "Failed to open output file.\n");
        return 1;
    }

    // Initialize PCM device
    if (snd_pcm_open(&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_CAPTURE, 0) < 0) {
        fprintf(stderr, "Error opening PCM device %s\n", PCM_DEVICE);
        return 1;
    }

    // Allocate memory for hardware parameters
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcm_handle, params);
    snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(pcm_handle, params, CHANNELS);
    snd_pcm_hw_params_set_rate(pcm_handle, params, SAMPLE_RATE, 0);

    if (snd_pcm_hw_params(pcm_handle, params) < 0) {
        fprintf(stderr, "Error setting HW params.\n");
        return 1;
    }

    int num_samples = SAMPLE_RATE * DURATION;
    write_wav_header(output_file, SAMPLE_RATE, CHANNELS, num_samples);

    // Set up alarm to end the program after DURATION seconds
    signal(SIGALRM, handle_alarm);
    alarm(DURATION);

    // Capture audio and write to file
    short buffer[BUFFER_SIZE];
    while (1) { // Record until the alarm signal is received
        int frames = snd_pcm_readi(pcm_handle, buffer, BUFFER_SIZE);
        if (frames < 0) frames = snd_pcm_recover(pcm_handle, frames, 0);
        if (frames < 0) {
            fprintf(stderr, "Error capturing audio: %s\n", snd_strerror(frames));
            break;
        }
        fwrite(buffer, sizeof(short), frames * CHANNELS, output_file);
    }

    // Close PCM device and file
    snd_pcm_drain(pcm_handle);
    snd_pcm_close(pcm_handle);
    fclose(output_file);

    printf("Recording saved to 'recording.wav'.\n");
    return 0;
}
