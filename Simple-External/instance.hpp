#pragma once
#include "memory.hpp"
#include "offsets.hpp"
#include <vector>

class instance {
public:
    uintptr_t address;

    instance(uintptr_t addr) : address(addr) {}

    std::string get_name() const { 
        uintptr_t name_ptr = memory::read<uintptr_t>(address + offsets::name);
        if (!name_ptr) return "";
        return memory::read_string(name_ptr);
    }

    std::vector<instance> get_children() const {
        std::vector<instance> children;
        uintptr_t start = memory::read<uintptr_t>(address + offsets::children);
        uintptr_t end = memory::read<uintptr_t>(start + offsets::children_end);

        for (uintptr_t ptr = memory::read<uintptr_t>(start); ptr != end; ptr += 0x10) {
            uintptr_t child_addr = memory::read<uintptr_t>(ptr);
            children.emplace_back(child_addr);
        }

        return children;
    }

    instance find_first_child(const std::string& target) const {
        for (const auto& child : get_children()) {
            if (child.get_name() == target)
                return child;
        }
        return instance(0);
    }

    bool valid() const {
        return address != 0;
    }
};
