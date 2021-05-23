#pragma once

#include <stdint.h>

// for more information on WAVE file format: http://www.piclist.com/techref/io/serial/midi/wave.html
struct SMinimalWaveFileHeader
{
	// main chunk
	unsigned char m_sz_chunk_id[4];
	uint32_t	  m_chunk_size;
	unsigned char m_sz_format[4];

	// sub chunk 1 "fmt "
	unsigned char m_sz_subchunk1_id[4];
	uint32_t	  m_subchunk1_size;
	uint16_t	  m_audio_format;
	uint16_t	  m_num_channels;
	uint32_t	  m_sample_rate;
	uint32_t	  m_byte_rate;
	uint16_t	  m_block_align;
	uint16_t	  m_bits_per_sample;

	// sub chunk 2 "data"
	unsigned char m_sz_subchunk2_id[4];
	uint32_t	  m_subchunk2_size;
};
