    #include <stdio.h>
    #include <stdlib.h>
    #include <alsa/asoundlib.h>

    #define PCM_DEVICE "default"
    #define SAMPLE_RATE 44100
    #define CHANNELS 1
    #define BUFFER_SIZE 128
    #define DURATION 10   // Duration in seconds

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

        // Capture audio and write to file
        short buffer[BUFFER_SIZE];
        for (int i = 0; i < SAMPLE_RATE * DURATION / BUFFER_SIZE; i++) {
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
// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <alsa/asoundlib.h>

// #define PCM_DEVICE "default"
// #define SAMPLE_RATE 44100
// #define CHANNELS 1
// #define BUFFER_SIZE 128

// FILE *output_file;
// snd_pcm_t *pcm_handle;
// int running = 1;

// void write_wav_header(FILE *file, int sample_rate, int channels, int num_samples) {
//     int byte_rate = sample_rate * channels * 2;
//     int data_size = num_samples * channels * 2;

//     // Write WAV header
//     fwrite("RIFF", 1, 4, file);
//     int chunk_size = 36 + data_size;
//     fwrite(&chunk_size, 4, 1, file);
//     fwrite("WAVE", 1, 4, file);
//     fwrite("fmt ", 1, 4, file);
//     int subchunk1_size = 16;
//     fwrite(&subchunk1_size, 4, 1, file);
//     short audio_format = 1;
//     fwrite(&audio_format, 2, 1, file);
//     fwrite(&channels, 2, 1, file);
//     fwrite(&sample_rate, 4, 1, file);
//     fwrite(&byte_rate, 4, 1, file);
//     short block_align = channels * 2;
//     fwrite(&block_align, 2, 1, file);
//     short bits_per_sample = 16;
//     fwrite(&bits_per_sample, 2, 1, file);
//     fwrite("data", 1, 4, file);
//     fwrite(&data_size, 4, 1, file);
// }

// void update_wav_header(FILE *file) {
//     // Calculate and update the WAV header with the actual data size
//     fseek(file, 0, SEEK_END);
//     int data_size = ftell(file) - 44;
//     fseek(file, 4, SEEK_SET);
//     int chunk_size = 36 + data_size;
//     fwrite(&chunk_size, 4, 1, file);
//     fseek(file, 40, SEEK_SET);
//     fwrite(&data_size, 4, 1, file);
// }

// void handle_sigint(int sig) {
//     printf("Stopping recording...\n");
//     running = 0;
// }

// int main() {
//     signal(SIGINT, handle_sigint);  // Set up SIGINT (Ctrl+C) handler

//     output_file = fopen("recording.wav", "wb");
//     if (!output_file) {
//         fprintf(stderr, "Failed to open output file.\n");
//         return 1;
//     }

//     // Open PCM device
//     if (snd_pcm_open(&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_CAPTURE, 0) < 0) {
//         fprintf(stderr, "Error opening PCM device %s\n", PCM_DEVICE);
//         return 1;
//     }

//     snd_pcm_hw_params_t *params;
//     snd_pcm_hw_params_alloca(&params);
//     snd_pcm_hw_params_any(pcm_handle, params);
//     snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
//     snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE);
//     snd_pcm_hw_params_set_channels(pcm_handle, params, CHANNELS);
//     snd_pcm_hw_params_set_rate(pcm_handle, params, SAMPLE_RATE, 0);

//     if (snd_pcm_hw_params(pcm_handle, params) < 0) {
//         fprintf(stderr, "Error setting HW params.\n");
//         return 1;
//     }

//     // Write a placeholder WAV header
//     write_wav_header(output_file, SAMPLE_RATE, CHANNELS, 0);

//     // Start capturing audio
//     short buffer[BUFFER_SIZE];
//     while (running) {
//         int frames = snd_pcm_readi(pcm_handle, buffer, BUFFER_SIZE);
//         if (frames < 0) frames = snd_pcm_recover(pcm_handle, frames, 0);
//         if (frames < 0) {
//             fprintf(stderr, "Error capturing audio: %s\n", snd_strerror(frames));
//             break;
//         }
//         fwrite(buffer, sizeof(short), frames * CHANNELS, output_file);
//     }

//     // Update WAV header with actual data size
//     update_wav_header(output_file);

//     // Clean up
//     snd_pcm_drain(pcm_handle);
//     snd_pcm_close(pcm_handle);
//     fclose(output_file);

//     printf("Recording saved to 'recording.wav'.\n");
//     return 0;
// }
//  #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <alsa/asoundlib.h>

// #define PCM_DEVICE "default"
// #define SAMPLE_RATE 44100
// #define CHANNELS 1
// #define BUFFER_SIZE 128

// FILE *output_file;
// snd_pcm_t *pcm_handle;
// int running = 1;

// void write_wav_header(FILE *file, int sample_rate, int channels, int num_samples) {
//     int byte_rate = sample_rate * channels * 2;
//     int data_size = num_samples * channels * 2;

//     // Write WAV header
//     fwrite("RIFF", 1, 4, file);
//     int chunk_size = 36 + data_size;
//     fwrite(&chunk_size, 4, 1, file);
//     fwrite("WAVE", 1, 4, file);
//     fwrite("fmt ", 1, 4, file);
//     int subchunk1_size = 16;
//     fwrite(&subchunk1_size, 4, 1, file);
//     short audio_format = 1;
//     fwrite(&audio_format, 2, 1, file);
//     fwrite(&channels, 2, 1, file);
//     fwrite(&sample_rate, 4, 1, file);
//     fwrite(&byte_rate, 4, 1, file);
//     short block_align = channels * 2;
//     fwrite(&block_align, 2, 1, file);
//     short bits_per_sample = 16;
//     fwrite(&bits_per_sample, 2, 1, file);
//     fwrite("data", 1, 4, file);
//     fwrite(&data_size, 4, 1, file);
// }

// void update_wav_header(FILE *file) {
//     // Calculate and update the WAV header with the actual data size
//     fseek(file, 0, SEEK_END);
//     int data_size = ftell(file) - 44;
//     fseek(file, 4, SEEK_SET);
//     int chunk_size = 36 + data_size;
//     fwrite(&chunk_size, 4, 1, file);
//     fseek(file, 40, SEEK_SET);
//     fwrite(&data_size, 4, 1, file);
// }

// void handle_sigint(int sig) {
//     printf("\nStopping recording...\n");
//     running = 0;

//     // Clean up resources
//     if (pcm_handle) {
//         snd_pcm_drain(pcm_handle);
//         snd_pcm_close(pcm_handle);
//     }
//     if (output_file) {
//         update_wav_header(output_file);
//         fclose(output_file);
//     }

//     printf("Recording saved to 'recording.wav'.\n");
//     exit(0);  // Terminate the program
// }

// int main() {
//     signal(SIGINT, handle_sigint);  // Set up SIGINT (Ctrl+C) handler

//     output_file = fopen("recording.wav", "wb");
//     if (!output_file) {
//         fprintf(stderr, "Failed to open output file.\n");
//         return 1;
//     }

//     // Open PCM device
//     if (snd_pcm_open(&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_CAPTURE, 0) < 0) {
//         fprintf(stderr, "Error opening PCM device %s\n", PCM_DEVICE);
//         return 1;
//     }

//     snd_pcm_hw_params_t *params;
//     snd_pcm_hw_params_alloca(&params);
//     snd_pcm_hw_params_any(pcm_handle, params);
//     snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
//     snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE);
//     snd_pcm_hw_params_set_channels(pcm_handle, params, CHANNELS);
//     snd_pcm_hw_params_set_rate(pcm_handle, params, SAMPLE_RATE, 0);

//     if (snd_pcm_hw_params(pcm_handle, params) < 0) {
//         fprintf(stderr, "Error setting HW params.\n");
//         return 1;
//     }

//     // Write a placeholder WAV header
//     write_wav_header(output_file, SAMPLE_RATE, CHANNELS, 0);

//     // Start capturing audio
//     short buffer[BUFFER_SIZE];
//     while (running) {
//         int frames = snd_pcm_readi(pcm_handle, buffer, BUFFER_SIZE);
//         if (frames < 0) frames = snd_pcm_recover(pcm_handle, frames, 0);
//         if (frames < 0) {
//             fprintf(stderr, "Error capturing audio: %s\n", snd_strerror(frames));
//             break;
//         }
//         fwrite(buffer, sizeof(short), frames * CHANNELS, output_file);
//     }

//     return 0;
// }