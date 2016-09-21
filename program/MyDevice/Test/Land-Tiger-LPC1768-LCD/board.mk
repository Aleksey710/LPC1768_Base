GFXINC	+= $(GFXLIB)/boards/base/Land-Tiger-LPC1768-LCD
GFXSRC	+=

include $(GFXLIB)/drivers/gdisp/SSD1289/gdisp_lld.mk
#include $(GFXLIB)/drivers/ginput/touch/ADS7843/ginput_lld.mk

