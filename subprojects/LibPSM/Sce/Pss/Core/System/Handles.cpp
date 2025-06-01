#include <Sce/Pss/Core/System/Handles.hpp>

namespace Sce::Pss::Core::System {
    std::unordered_map<int, void*> Handles::handles;
    int Handles::lastHandle = 0;
}
