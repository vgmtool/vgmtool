#ifndef __N_MIDI_CC_H__
#define __N_MIDI_CC_H__

#include <nall/platform.hpp>

#include "midi.cc.meta.hpp"

using namespace nall;

namespace MIDI {
	namespace Controller {
		const uint8_t OFF = 0;
		const uint8_t ON = 127;
		enum Pan : uint8_t {
			Left = 0,
			Center = 0x40,
			Right = 0x7F
		};
	}
	namespace Marker {
		const string LoopStart = "loopStart";
		const string LoopEnd = "loopEnd";
	}
	enum Pitch : unsigned {
		Center = 0x2000
	};
	enum CC : uint8_t {
		BankSelectCoarse = 0,
		ModWheelCoarse,	// GM LITE
		BreathControlCoarse,
		Continuous03Coarse,
		FootControllerCoarse,
		PortamentoTimeCoarse,
		DataEntryCoarse,	// GM LITE
		VolumeCoarse,	// GM LITE
		BalanceCoarse,
		Continuous09Coarse,
		PanCoarse,	// GM LITE
		ExpressionCoarse,	// GM LITE
		Effect1Coarse,
		Effect2Coarse,
		Continuous0ECoarse,
		Continuous0FCoarse,
		GeneralPurposeSlider1,
		GeneralPurposeSlider2,
		GeneralPurposeSlider3,
		GeneralPurposeSlider4,
		Continuous14Coarse,
		Continuous15Coarse,
		Continuous16Coarse,
		Continuous17Coarse,
		Continuous18Coarse,
		Continuous19Coarse,
		Continuous1ACoarse,
		Continuous1BCoarse,
		Continuous1CCoarse,
		Continuous1DCoarse,
		Continuous1ECoarse,
		Continuous1FCoarse,
		BankSelectFine,
		ModWheelFine,
		BreathControlFine,
		Continuous03Fine,
		FootControllerFine,
		PortamentoTimeFine,
		DataEntryFine,	// GM LITE
		VolumeFine,
		BalanceFine,
		Continuous09Fine,
		PanFine,
		ExpressionFine,
		Effect1Fine,
		Effect2Fine,
		Continuous0EFine,
		Continuous0FFine,
		Continuous_16,
		Continuous_17,
		Continuous_18,
		Continuous_19,
		Continuous14Fine,
		Continuous15Fine,
		Continuous16Fine,
		Continuous17Fine,
		Continuous18Fine,
		Continuous19Fine,
		Continuous1AFine,
		Continuous1BFine,
		Continuous1CFine,
		Continuous1DFine,
		Continuous1EFine,
		Continuous1FFine,
		PedalSustain,	// GM LITE, 0..63=off, 64..127=on
		Portamento,	// 0..63=off, 64..127=on
		PedalSostenuto,	// 0..63=off, 64..127=on
		PedalSoft,	// 0..63=off, 64..127=on
		PedalLegato,	// 0..63=off, 64..127=on
		PedalHold2,	// 0..63=off, 64..127=on
		SoundVariation,
		SoundTimbre,
		SoundReleaseTime,
		SoundAttackTime,
		SoundBrightness,
		SoundDecayTime,
		VibratoRate,
		VibratoDepth,
		VibratoDelay,
		SoundControl10,
		GeneralPurposeButton1,	// 0..63=off, 64..127=on
		GeneralPurposeButton2,	// 0..63=off, 64..127=on
		GeneralPurposeButton3,	// 0..63=off, 64..127=on
		GeneralPurposeButton4,	// 0..63=off, 64..127=on
		Undefined54,	// 0..63=off, 64..127=on
		Undefined55,	// 0..63=off, 64..127=on
		Undefined56,	// 0..63=off, 64..127=on
		Undefined57,	// 0..63=off, 64..127=on
		Undefined58,	// 0..63=off, 64..127=on
		Undefined59,	// 0..63=off, 64..127=on
		Undefined5A,	// 0..63=off, 64..127=on
		LevelReverb,
		LevelTremolo,
		LevelChorus,
		LevelCeleste,
		LevelPhaser,
		DataEntryIncr,
		DataEntryDecr,
		NRPN_LSB,
		NRPN_MSB,
		RPN_LSB,	// GM LITE
		RPN_MSB,	// GM LITE
		Undefined66,
		Undefined67,
		Undefined68,
		Undefined69,
		Undefined6A,
		Undefined6B,
		Undefined6C,
		Undefined6D,
		Undefined6E,
		Undefined6F,
		Undefined70,
		Undefined71,
		Undefined72,
		Undefined73,
		Undefined74,
		Undefined75,
		Undefined76,
		Undefined77,
		AllSoundsOff,	// GM LITE
		AllControllersOff,	// GM LITE
		LocalKeyboardToggle,	// 0..63=off, 64..127=on
		AllNotesOff,	// GM LITE
		OmniModeOff,
		OmniModeOn,
		PolyModeOff,	// mono on, value=# channels or zero if # channels=# voices in rcvr
		PolyModeOn	// mono off
	};
	enum RPN : unsigned {
		PitchBendRange,	// GM LITE
		ChannelTuningFine,
		ChannelTuningCoarse,
		TuningPatchSelect,
		TuningBankSelect,
		ModDepthRange,
		Reset = 0x3fff
	};
}

#endif