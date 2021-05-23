#pragma once

#include "Common.h"

/*
	Map input data type value to Sine function range (-1 to 1)
*/
#define CLAMP(value, min, max) { if(value < min) { value = min; } else if (value > max) { value = max; }}

class Recorder
{
private:
	int32_t m_sample_rate;
	int32_t m_num_seconds;
	int32_t m_num_channels;

	void convert_to_audio_sample(float in, int16_t& out);

public:
	Recorder(int32_t sample_rate, int32_t num_channels, int32_t num_seconds);
	~Recorder();

	int get_num_samples();
	bool record_to_wav(const char* filename, float* raw_data);
};

