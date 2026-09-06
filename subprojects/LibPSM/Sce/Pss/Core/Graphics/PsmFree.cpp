#include <Sce/Pss/Core/Graphics/PsmFree.hpp>
#include <Sce/Pss/Core/Graphics/PsmFreeList.hpp>
#include <Sce/Pss/Core/Graphics/PsmObjectType.hpp>


namespace Sce::Pss::Core::Graphics {
	PsmObjectType PsmFree::Type()
	{
		return this->type;
	}
	int PsmFree::Handle()
	{
		return this->handle;
	}

	PsmFree::PsmFree(PsmObjectType type, int handle)
	{
		this->handle = handle;
		this->type = type;
	}
}