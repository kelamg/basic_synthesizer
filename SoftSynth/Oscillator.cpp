#include "Oscillator.h"

Oscillator::Oscillator(float sample_rate, int num_samples) 
	: m_sample_rate(sample_rate), m_num_samples(num_samples)
{ 
	m_data = new float[num_samples];
}

Oscillator::~Oscillator()
{ 
	delete[] m_data;
}

float* Oscillator::generate_sine()
{
	std::fill_n(m_data, m_num_samples, 0);
	for (int i = 0; i < m_num_samples; i++)
	{
		m_phase += 2 * (float)M_PI * m_frequency / m_sample_rate;

		while (m_phase >= 2 * (float)M_PI)
			m_phase -= 2 * (float)M_PI;

		while (m_phase < 0)
			m_phase += 2 * (float)M_PI;

		m_data[i] = sin(m_phase);
	}

	return m_data;
}

float* Oscillator::generate_square()
{
	std::fill_n(m_data, m_num_samples, 0);
	for (int i = 0; i < m_num_samples; i++)
	{
		m_phase += m_frequency / m_sample_rate;

		while (m_phase > 1.0f)
			m_phase -= 1.0f;

		while (m_phase < 0.0f)
			m_phase += 1.0f;

		if (m_phase <= 0.5f)
			m_data[i] = -1.0f;
		else
			m_data[i] = 1.0f;
	}

	return m_data;
}

float* Oscillator::generate_saw()
{
	std::fill_n(m_data, m_num_samples, 0);
	for (int i = 0; i < m_num_samples; i++)
	{
		m_phase += m_frequency / m_sample_rate;

		while (m_phase > 1.0f)
			m_phase -= 1.0f;

		while (m_phase < 0.0f)
			m_phase += 1.0f;

		m_data[i] = (m_phase * 2.0f) - 1.0f;
	}

	return m_data;
}

float* Oscillator::generate_triangle()
{
	std::fill_n(m_data, m_num_samples, 0);
	for (int i = 0; i < m_num_samples; i++)
	{
		m_phase += m_frequency / m_sample_rate;

		while (m_phase > 1.0f)
			m_phase -= 1.0f;

		while (m_phase < 0.0f)
			m_phase += 1.0f;

		float ret;
		if (m_phase <= 0.5f)
			ret = m_phase * 2;
		else
			ret = (1.0f - m_phase) * 2;

		m_data[i] = (ret * 2.0f) - 1.0f;
	}

	return m_data;
}


float* Oscillator::generate_noise()
{
	std::fill_n(m_data, m_num_samples, 0);
	for (int i = 0; i < m_num_samples; i++)
	{
		float previous_val = i > 0 ? m_data[i - 1] : 0.0f;
		unsigned int previous_seed = (unsigned int)m_phase;
		m_phase += m_frequency / m_sample_rate;
		unsigned int seed = (unsigned int)m_phase;

		while (m_phase > 2.0f)
			m_phase -= 1.0f;

		if (seed != previous_seed)
		{
			float val = ((float)rand()) / ((float)RAND_MAX);
			val = (val * 2.0f) - 1.0f;

			m_data[i] = val;
		}
		else
		{
			m_data[i] = previous_val;
		}
	}

	return m_data;
}
