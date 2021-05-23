#include "Common.h"
#include "Recorder.h"
#include "Oscillator.h"

int main()
{
	// samples of audio data per second
	// also defines the maximum storable frequency (half the sample rate)
	int sample_rate = 44100; 
	int num_seconds = 4; // duration in secs
	int num_channels = 2; // 1 for mono, 2 for stereo
	int num_samples = num_channels * sample_rate * num_seconds;

	Recorder recorder(sample_rate, num_channels, num_seconds);
	Oscillator oscillator((float)sample_rate, num_samples);

	float* sine_wave = oscillator.generate_sine();
	recorder.record_to_wav("sine.wav", sine_wave);

	float* square_wave = oscillator.generate_square();
	recorder.record_to_wav("square.wav", square_wave);

	float* saw_wave = oscillator.generate_saw();
	recorder.record_to_wav("saw.wav", saw_wave);

	float* triangle_wave = oscillator.generate_triangle();
	recorder.record_to_wav("triangle.wav", triangle_wave);

	float* noise_wave = oscillator.generate_noise();
	recorder.record_to_wav("noise.wav", noise_wave);

	return 0;
}