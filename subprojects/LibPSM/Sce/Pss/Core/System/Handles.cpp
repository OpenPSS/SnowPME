#include <Sce/Pss/Core/System/Handles.hpp>
#include <cstdint>

namespace Sce::Pss::Core::System {
    std::unordered_map<int, uintptr_t> Handles::handles;
    int Handles::lastHandle = 0;
}
