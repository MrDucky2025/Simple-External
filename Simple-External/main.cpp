#include <iostream>
#include "rbx.hpp"

int main() {
    if (!memory::attach(L"RobloxPlayerBeta.exe")) {
        std::cout << "Failed to attach to Roblox.\n";
        return 1;
    }

    std::cout << "Attached to Roblox successfully.\n";

    rbx::set_walkspeed(100.0f);
	std::cout << "Walkspeed set to 100.\n";

	rbx::set_jumppower(200.0f);
	std::cout << "Jump power set to 200.\n";

	rbx::set_gravity(50.0f);
	std::cout << "Gravity set to 50.\n";

    system("pause");
    return 0;
}
