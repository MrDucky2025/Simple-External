#pragma once
#include "instance.hpp"

namespace rbx {
    inline instance get_datamodel() {
        uintptr_t base = memory::get_module_base(L"RobloxPlayerBeta.exe");
        uintptr_t fake_dm = memory::read<uintptr_t>(base + offsets::fakedatamodel);
        uintptr_t real_dm = memory::read<uintptr_t>(fake_dm + offsets::fakedm_to_dm);
        return instance(real_dm);
    }

    inline instance get_service(const std::string& name) {
        instance dm = get_datamodel();
        return dm.find_first_child(name);
    }

    inline instance get_local_humanoid() {
        instance workspace = get_service("Workspace");
        instance players = get_service("Players");

        uintptr_t local_player_ptr = memory::read<uintptr_t>(players.address + offsets::localplayer);
        instance local_player(local_player_ptr);

        instance character = local_player.find_first_child("Character");
        if (!character.valid())
            character = workspace.find_first_child(local_player.get_name());

        return character.find_first_child("Humanoid");
    }

    inline void set_walkspeed(float speed) {
        instance humanoid = get_local_humanoid();
        memory::write<float>(humanoid.address + offsets::walkspeed, speed);
        memory::write<float>(humanoid.address + offsets::walkspeedcheck, speed);
    }

    inline void set_jumppower(float power) {
        instance humanoid = get_local_humanoid();
        memory::write<float>(humanoid.address + offsets::jumppower, power);
    }
}
