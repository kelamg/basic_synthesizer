#pragma once

#define _USE_MATH_DEFINES
#include<math.h>

#include "Common.h"

class Oscillator
{
private:
	float  m_phase = 0;
	float  m_sample_rate;
	float  m_frequency = 261.62f; // middle C
	float* m_data;
	int    m_num_samples;
	
public:
	Oscillator(float sample_rate, int num_samples);
	~Oscillator();

	float* generate_sine();
	float* generate_square();
	float* generate_saw();
	float* generate_triangle();
	float* generate_noise();
	float calculate_frequency(float octave, float note);
};

