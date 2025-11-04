#ifndef LIB_PSS_IMPL_EMBEDDED_FONT_H
#define LIB_PSS_IMPL_EMBEDDED_FONT_H 1
#ifdef __cplusplus
extern "C" {
#endif
#define INCBIN_PREFIX font_
#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#include <incbin.h>
INCBIN(default, "OpenSans-Light.ttf");
#ifdef __cplusplus
}
#endif
#endif