#pragma once

namespace variables {
	
	// Legitbot
	inline bool aimbot_bool = false;
	inline float aimbot_fov = 0.f;
	inline float aimbot_smoothing = 2.f;
	inline bool aimbot_isvisiblecheck = true;

	// Visuals
	inline bool showteamesp = false;
	inline bool boxesp = false;
	
	inline bool noflash_bool  = false;
	
	// Misc
	inline bool bhop_bool = true;
	inline bool crosshair_bool = false;
	inline bool spectator_list_bool = true;

	namespace menu {
		inline bool opened = false;
		inline int x = 140, y = 140;
		inline int w = 300, h = 200;
	}
}