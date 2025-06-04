for MSVC, we want to build SDL2 from source (as windows doesn't include it normally-) however,
i also want to change the build folder, and the runtime library to be /MT instead of /MD, 

because the only way to do that is by changing the MSVC project file itself,
i have included a seperate one outside the main SDL source tree, that is a copy of the SDL one
but with those settings changed.