#include <Sce/PlayStation/Core/Graphics/GraphicsUpdate.hpp>

namespace Sce::PlayStation::Core::Graphics {
	GraphicsUpdate operator&(GraphicsUpdate l, GraphicsUpdate r) { return (GraphicsUpdate)((unsigned int)l & (unsigned int)r); };
	GraphicsUpdate operator&(GraphicsUpdate l, unsigned int r) { return (GraphicsUpdate)((unsigned int)l & (unsigned int)r); };
	GraphicsUpdate operator&(unsigned int l, GraphicsUpdate r) { return (GraphicsUpdate)((unsigned int)l & (unsigned int)r); };

	GraphicsUpdate operator|(GraphicsUpdate l, GraphicsUpdate r) { return (GraphicsUpdate)((unsigned int)l | (unsigned int)r); };
	GraphicsUpdate operator|(unsigned int l, GraphicsUpdate r) { return (GraphicsUpdate)((unsigned int)l | (unsigned int)r); };
	GraphicsUpdate operator|(GraphicsUpdate l, unsigned int r) { return (GraphicsUpdate)((unsigned int)l | (unsigned int)r); };
}