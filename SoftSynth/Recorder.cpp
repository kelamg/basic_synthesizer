#include "Recorder.h"
#include "WaveFileHeader.h"

Recorder::Recorder(int32_t sample_rate, int32_t num_channels, int32_t num_seconds)
	: m_sample_rate(sample_rate), m_num_channels(num_channels), m_num_seconds(num_seconds)
{ }

Recorder::~Recorder()
{ }

void Recorder::convert_to_audio_sample(float in, int16_t& out)
{
	// map to 16 bit value range -> –32,768 to 32,767
	in *= 32767.0f;
	CLAMP(in, -32768.0f, 32767.0f);
	out = (int16_t)in;
}

int Recorder::get_num_samples()
{
	return m_num_channels * m_sample_rate * m_num_seconds;
}

bool Recorder::record_to_wav(const char* filename, float* raw_data)
{
	/*
		Writes 16bit WAVE files
	*/
	FILE* wave_file; 
	errno_t err;
	if (err = fopen_s(&wave_file, filename, "w+b")) return false;

	int num_samples = get_num_samples();

	// calculate bits per sample and the data size
	int32_t num_bits_per_sample = sizeof(int16_t) * 8;
	int data_size = num_samples * sizeof(int16_t);

	SMinimalWaveFileHeader wave_header;

	// the main chunk
	memcpy(wave_header.m_sz_chunk_id, "RIFF", 4);
	wave_header.m_chunk_size = data_size + 36;
	memcpy(wave_header.m_sz_format, "WAVE", 4);

	// sub chunk 1 "fmt "
	memcpy(wave_header.m_sz_subchunk1_id, "fmt ", 4);
	wave_header.m_subchunk1_size = 16;
	wave_header.m_audio_format = 1;
	wave_header.m_num_channels = m_num_channels;
	wave_header.m_sample_rate = m_sample_rate;
	wave_header.m_byte_rate = m_sample_rate * m_num_channels * num_bits_per_sample / 8;
	wave_header.m_block_align = m_num_channels * num_bits_per_sample / 8;
	wave_header.m_bits_per_sample = num_bits_per_sample;

	// sub chunk 2 "data"
	memcpy(wave_header.m_sz_subchunk2_id, "data", 4);
	wave_header.m_subchunk2_size = data_size;

	// write header
	fwrite(&wave_header, sizeof(SMinimalWaveFileHeader), 1, wave_file);

	// write the WAVE data 
	int16_t* data = new int16_t[num_samples];
	for (int i = 0; i < num_samples; i++)
	{
		convert_to_audio_sample(raw_data[i], data[i]);
	}
	fwrite(data, data_size, 1, wave_file);
	delete[] data;

	fclose(wave_file);

	return true;
}
