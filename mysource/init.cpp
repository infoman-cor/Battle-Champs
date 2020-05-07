//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#include "game_g.h"
#include "game_extv.h"

init_displayst::init_displayst()
{
	flag.set_size_on_flag_num(INIT_DISPLAY_FLAGNUM);
	windowed=INIT_DISPLAY_WINDOW_PROMPT;

	dwarf_frame_rate.QuadPart=enabler.qpfr.QuadPart/100;

	partial_print_count=0;
}