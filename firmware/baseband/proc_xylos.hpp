/*
 * Copyright (C) 2015 Jared Boone, ShareBrained Technology, Inc.
 * Copyright (C) 2016 Furrtek
 * 
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __PROC_XYLOS_H__
#define __PROC_XYLOS_H__

#include "baseband_processor.hpp"
#include "baseband_thread.hpp"

//#include "audio_output.hpp"

#define CCIR_TONELENGTH (15360*2)-1		// 1536000/10/10
#define CCIR_PHASEINC (436.91/2)		// (65536*1024)/1536000*10
#define CCIR_SILENCE (122880)-1			// 400ms

class XylosProcessor : public BasebandProcessor {
public:
	void execute(const buffer_c8_t& buffer) override;
	
	void on_message(const Message* const p) override;

private:
	bool configured = false;
	
	BasebandThread baseband_thread { 1536000, this, NORMALPRIO + 20, baseband::Direction::Transmit };
	
	const uint32_t ccir_phases[16] = {
								(uint32_t)(1981*CCIR_PHASEINC),
								(uint32_t)(1124*CCIR_PHASEINC),
								(uint32_t)(1197*CCIR_PHASEINC),
								(uint32_t)(1275*CCIR_PHASEINC),
								(uint32_t)(1358*CCIR_PHASEINC),
								(uint32_t)(1446*CCIR_PHASEINC),
								(uint32_t)(1540*CCIR_PHASEINC),
								(uint32_t)(1640*CCIR_PHASEINC),
								(uint32_t)(1747*CCIR_PHASEINC),
								(uint32_t)(1860*CCIR_PHASEINC),
								(uint32_t)(2400*CCIR_PHASEINC),
								(uint32_t)(930*CCIR_PHASEINC),
								(uint32_t)(2247*CCIR_PHASEINC),
								(uint32_t)(991*CCIR_PHASEINC),
								(uint32_t)(2110*CCIR_PHASEINC),
								(uint32_t)(1055*CCIR_PHASEINC)
							};

	char xylosdata[21];
	int8_t re, im;
	uint8_t s, as = 0, ai;
    uint8_t byte_pos = 0;
    uint8_t digit = 0;
    uint32_t sample_count = CCIR_TONELENGTH;
	uint32_t tone_phase, phase, sphase;
	int32_t tone_sample, frq;
	bool silence = true;
	TXDoneMessage message;
	
	//AudioOutput audio_output;
};

#endif