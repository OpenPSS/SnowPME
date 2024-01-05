#ifndef LIB_PSS_FONTMETRICS_H
#define LIB_PSS_FONTMETRICS_H

namespace Sce::Pss::Core::Imaging {
	typedef struct FontMetrics {
		int Ascent;
		int Descent;
		int Leading;
	} FontMetrics;
}

#endif