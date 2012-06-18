#ifndef __VGM_TYPES_H__
#define __VGM_TYPES_H__

namespace VGM {
	namespace ID {
		const char VGM[4] = {'V','g','m',' '};
		const char GD3[4] = {'G','d','3',' '};
	}
	namespace Wait {
		const uint32_t NTSC = 735;
		const uint32_t PAL = 882;
	}
	namespace Addr {
		const uint32_t GD3 = 0x00000014;
		const uint32_t Loop = 0x0000001c;
		const uint32_t Data = 0x00000034;
	}
	namespace AY8910 {
		enum Type : uint8_t {
			AY8910 = 0,
			AY8912,
			AY8913,
			AY8930,
			YM2149 = 0x10,
			YM3439,
			YMZ284,
			YMZ294
		};
		const string Types[] = {
			"AY-3-8910A",
			"AY-3-8912A",
			"AY-3-8913A",
			"AY8930",
			"","","","","","","","","","","","",
			"YM2149",
			"YM3439",
			"YMZ284",
			"YMZ294"
		};
	}
}

#endif