#ifndef SNOW_PME_IMPL_H
#define SNOW_PME_IMPL_H 1
namespace SnowPME::Callback {
#define CHECKINIT() \

	class Impl {
	protected:
		static bool isInitalized;
	public:
		static void ErrorOnNotInit();
	};
}
#endif