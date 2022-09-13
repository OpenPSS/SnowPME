#ifndef LIB_PSM_FONTMETRICS_H
#define LIB_PSM_FONTMETRICS_H

namespace Sce::PlayStation::Core::Imaging {
	typedef struct FontMetrics {
		int Ascent;
		int Descent;
		int Leading;
	} FontMetrics;
}

#endif