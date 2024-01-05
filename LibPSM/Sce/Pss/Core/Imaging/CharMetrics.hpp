#ifndef LIB_PSS_CHARMETRICS_H
#define LIB_PSS_CHARMETRICS_H

namespace Sce::Pss::Core::Imaging {
	typedef struct CharMetrics {
		float X;
		float Y;
		float Width;
		float Height;
		float HorizontalBearingX;
		float HorizontalBearingY;
		float HorizontalAdvance;
		int reserved0;
		int reserved1;
		int reserved2;
		int reserved3;
	} CharMetrics;
}

#endif