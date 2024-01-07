#ifndef SNOW_PME_AUDIOOBJECT_H
#define SNOW_PME_AUDIOOBJECT_H 1
#include <sdl/SDL_mixer.h>
namespace SnowPME::Callback {
	typedef struct AudioObject{
		int channeNumber = NULL;
		Mix_Chunk* audioObject = nullptr;
	} AudioObject;
}
#endif