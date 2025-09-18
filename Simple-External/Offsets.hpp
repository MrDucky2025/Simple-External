#pragma once
#include <Windows.h>

namespace offsets {

	// Instance
    inline uintptr_t This = 0x8;
    inline uintptr_t name = 0x88;
    inline uintptr_t parent = 0x58;
    inline uintptr_t children = 0x68;
    inline uintptr_t children_end = 0x8;
    inline uintptr_t Gravity = 0x1AC;
    inline uintptr_t GravityInfo = 0x3d8;

    // Player
    inline uintptr_t localplayer = 0x128;
    inline uintptr_t walkspeed = 0x1DC;
    inline uintptr_t walkspeedcheck = 0x3B8;
    inline uintptr_t jumppower = 0x1B8;

	// DataModel
    inline uintptr_t fakedatamodel = 0x70A86B8;
    inline uintptr_t fakedm_to_dm = 0x1C0;

}
