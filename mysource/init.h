//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

class init_fontst
{
	public:
		long small_font_texpos[256];
		long large_font_texpos[256];
		long small_font_datapos[256];
		long large_font_datapos[256];
		float small_font_adjx;
		float small_font_adjy;
		float large_font_adjx;
		float large_font_adjy;
		long small_font_dispx;
		long small_font_dispy;
		long large_font_dispx;
		long large_font_dispy;
};

enum InitDisplayFlag
{
	INIT_DISPLAY_FLAG_UNUSED1,//
	INIT_DISPLAY_FLAG_UNUSED2,//
	INIT_DISPLAY_FLAG_USE_GRAPHICS,
	INIT_DISPLAY_FLAG_BLACK_SPACE,
	INIT_DISPLAY_FLAG_UNUSED5,//
	INIT_DISPLAY_FLAG_UNUSED6,//
	INIT_DISPLAY_FLAG_PARTIAL_PRINT,
	INIT_DISPLAY_FLAG_UNUSED8,//
	INIT_DISPLAY_FLAGNUM
};

enum InitDisplayWindow
{
	INIT_DISPLAY_WINDOW_TRUE,
	INIT_DISPLAY_WINDOW_FALSE,
	INIT_DISPLAY_WINDOW_PROMPT,
	INIT_DISPLAY_WINDOWNUM
};

class init_displayst
{
	public:
		flagarrayst flag;
		InitDisplayWindow windowed;
		LARGE_INTEGER dwarf_frame_rate;
		LARGE_INTEGER g_frame_rate;
		unsigned char sky_tile;
		short sky_f,sky_b,sky_br;
		unsigned char chasm_tile;
		short chasm_f,chasm_b,chasm_br;

		long grid_x,grid_y;
		long orig_grid_x,orig_grid_y;
		long small_grid_x,small_grid_y;
		long large_grid_x,large_grid_y;

		char partial_print_count;

		init_displayst();
};

enum InitMediaFlag
{
	INIT_MEDIA_FLAG_SOUND_OFF,
	INIT_MEDIA_FLAGNUM
};

class init_mediast
{
	public:
		flagarrayst flag;
		long volume;

		init_mediast()
			{
			flag.set_size_on_flag_num(INIT_MEDIA_FLAGNUM);
			volume=255;
			}
};

enum InitInputFlag
{
	INIT_INPUT_FLAG_MOUSE_OFF,
	INIT_INPUT_FLAG_MOUSE_PICTURE,
	INIT_INPUT_FLAGNUM
};

class init_inputst
{
	public:
		long hold_time;
		long pause_zoom_no_interface_ms;
		flagarrayst flag;

		init_inputst()
			{
			hold_time=150;
			pause_zoom_no_interface_ms=0;
			flag.set_size_on_flag_num(INIT_INPUT_FLAGNUM);
			}
};

enum InitFeatureFlag
{
	INIT_FEATURE_FLAG_UNUSED1,
	INIT_FEATURE_FLAG_UNUSED2,
	INIT_FEATURE_FLAG_UNUSED3,
	INIT_FEATURE_FLAG_UNUSED4,
	INIT_FEATURE_FLAG_UNUSED5,
	INIT_FEATURE_FLAG_UNUSED6,
	INIT_FEATURE_FLAG_UNUSED7,
	INIT_FEATURE_FLAG_UNUSED8,
	INIT_FEATURE_FLAGNUM,
	INIT_FEATURE_FLAG_NONE=-1
};

class init_featurest
{
	public:
		flagarrayst flag;

		long world_map_x,world_map_y;
		long start_nation;

		init_featurest()
			{
			flag.set_size_on_flag_num(INIT_FEATURE_FLAGNUM);
			world_map_x=50;
			world_map_y=25;
			start_nation=52;
			}
};

enum InitWindowFlag
{
	INIT_WINDOW_FLAG_TOPMOST,
	INIT_WINDOW_FLAG_VSYNC_ON,
	INIT_WINDOW_FLAG_VSYNC_OFF,
	INIT_WINDOW_FLAG_TEXTURE_LINEAR,
	INIT_WINDOW_FLAGNUM
};

class init_windowst
{
	public:
		flagarrayst flag;

		init_windowst()
			{
			flag.set_size_on_flag_num(INIT_WINDOW_FLAGNUM);
			}
};

class initst
{
	public:
		init_displayst display;
		init_mediast media;
		init_inputst input;
		init_fontst font;
		init_featurest feature;
		init_windowst window;
};