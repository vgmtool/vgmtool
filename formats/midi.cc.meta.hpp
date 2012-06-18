#ifndef __N_MIDI_CC_META_H__
#define __N_MIDI_CC_META_H__

#include <nall/platform.hpp>

using namespace nall;

namespace MIDI {
	enum Meta : uint8_t {
		Sequence = 0,
		Text,
		Copyright,
		TrackName,
		InstrumentName,
		Lyric,
		Marker,
		CuePoint,
		PatchName,
		PortName,
		ChannelPrefix = 0x20,
		TrackEnd = 0x2f,
		Tempo = 0x51,
		OffsetSMPTE = 0x54,
		TimeSignature = 0x58,
		KeySignature,
		Proprietary = 0x7f
	};
	const string MetaEvent[] = {
		"Sequence Number",
		"Text",
		"Copyright",
		"Sequence/Track Name",
		"Instrument Name",
		"Lyric",
		"Marker",
		"Cue Point",
		"Patch Name",
		"Port Name",
		"","","","","","","","","","","",
		"","","","","","","","","","","",
		"Channel Prefix",
		"","","","","","","","","","",
		"","","","",
		"Track End",
		"","","","","","","","","",
		"","","","","","","","","",
		"","","","","","","","","",
		"","","","","","","","","",
		"",
		"Tempo",
		"","",
		"SMPTE Offset",
		"","","",
		"Time Signature",
		"Key Signature"
	};
}

#endif