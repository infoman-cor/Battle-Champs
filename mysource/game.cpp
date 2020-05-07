//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#include "game_g.h"
#include "game_v.h"

char mainloop()
{
	if(gview.loop())return 1;

	return 0;
}

void endroutine()
{
	#ifdef CURSES
		//deinitialize curses
		endwin();
	#endif
}

void ne_toggle_fullscreen()
{
	//ONLY CHANGE GRID IF MOVIE IS NOT PLAYING
	if(enabler.create_full_screen)
		{
		if(gps.original_rect)
			{
			init.display.grid_x=init.display.large_grid_x;
			init.display.grid_y=init.display.large_grid_y;
			gps.prepare_rect(1);
			}
		}
	else
		{
		if(gps.original_rect)
			{
			init.display.grid_x=init.display.small_grid_x;
			init.display.grid_y=init.display.small_grid_y;
			gps.prepare_rect(1);
			}
		}
	if(enabler.create_full_screen)
		{
		init.display.orig_grid_x=init.display.large_grid_x;
		init.display.orig_grid_y=init.display.large_grid_y;
		}
	else
		{
		init.display.orig_grid_x=init.display.small_grid_x;
		init.display.orig_grid_y=init.display.small_grid_y;
		}
}

char beginroutine()
{
	version=1267;
	min_load_version=1205;
	movie_version=10001;

	if(!enabler.command_line.empty())
		{
		string anstr="Command Line: ";
		anstr+=enabler.command_line;
		gamelog_string(anstr);

		game.command_line.init(enabler.command_line);
		}

	#ifdef ENABLER
	string small_font="data/art/curses.bmp";
	string large_font="data/art/curses.bmp";
	std::ifstream fseed("data/init/init.txt");
	if(fseed.is_open())
		{
		string str;

		while(std::getline(fseed,str))
			{
			if(str.length()>1)
				{
				string token;
				string token2;

				grab_token_string_pos(token,str,1);
				if(str.length()>=token.length()+2)
					{
					grab_token_string_pos(token2,str,token.length()+2);
					}

				if(!token.compare("FONT"))
					{
					small_font="data/art/";
					small_font+=token2;
					}
				if(!token.compare("FULLFONT"))
					{
					large_font="data/art/";
					large_font+=token2;
					}
				if(!token.compare("WINDOWEDX"))
					{
					enabler.desired_windowed_width=convert_string_to_long(token2);
					}
				if(!token.compare("WINDOWEDY"))
					{
					enabler.desired_windowed_height=convert_string_to_long(token2);
					}
				if(!token.compare("FULLSCREENX"))
					{
					enabler.desired_fullscreen_width=convert_string_to_long(token2);
					}
				if(!token.compare("FULLSCREENY"))
					{
					enabler.desired_fullscreen_height=convert_string_to_long(token2);
					}

				if(token=="PARTIAL_PRINT")
					{
					if(token2=="YES")
						{
						init.display.flag.add_flag(INIT_DISPLAY_FLAG_PARTIAL_PRINT);
						}
					string token3;
					if(str.length()>=token.length()+token2.length()+3)
						{
						grab_token_string_pos(token3,str,token.length()+token2.length()+3);
						}
					long l=convert_string_to_long(token3);
					if(l<0)l=0;
					if(l>100)l=100;
					init.display.partial_print_count=(char)l;
					}

				if(init.display.flag.has_flag(INIT_DISPLAY_FLAG_USE_GRAPHICS))
					{
					if(!token.compare("GRAPHICS_FONT"))
						{
						small_font="data/art/";
						small_font+=token2;
						}
					if(!token.compare("GRAPHICS_FULLFONT"))
						{
						large_font="data/art/";
						large_font+=token2;
						}
					if(!token.compare("GRAPHICS_WINDOWEDX"))
						{
						enabler.desired_windowed_width=convert_string_to_long(token2);
						}
					if(!token.compare("GRAPHICS_WINDOWEDY"))
						{
						enabler.desired_windowed_height=convert_string_to_long(token2);
						}
					if(!token.compare("GRAPHICS_FULLSCREENX"))
						{
						enabler.desired_fullscreen_width=convert_string_to_long(token2);
						}
					if(!token.compare("GRAPHICS_FULLSCREENY"))
						{
						enabler.desired_fullscreen_height=convert_string_to_long(token2);
						}
					if(!token.compare("GRAPHICS_BLACK_SPACE"))
						{
						if(token2=="YES")
							{
							init.display.flag.add_flag(INIT_DISPLAY_FLAG_BLACK_SPACE);
							}
						else init.display.flag.remove_flag(INIT_DISPLAY_FLAG_BLACK_SPACE);
						}
					}

				if(!token.compare("GRAPHICS"))
					{
					if(token2=="YES")
						{
						init.display.flag.add_flag(INIT_DISPLAY_FLAG_USE_GRAPHICS);
						}
					}

				if(!token.compare("BLACK_SPACE"))
					{
					if(token2=="YES")
						{
						init.display.flag.add_flag(INIT_DISPLAY_FLAG_BLACK_SPACE);
						}
					}

				if(token=="MOUSE")
					{
					if(token2=="NO")
						{
						init.input.flag.add_flag(INIT_INPUT_FLAG_MOUSE_OFF);
						}
					}
				if(token=="VSYNC")
					{
					if(token2=="ON")
						{
						init.window.flag.add_flag(INIT_WINDOW_FLAG_VSYNC_ON);
						}
					if(token2=="OFF")
						{
						init.window.flag.add_flag(INIT_WINDOW_FLAG_VSYNC_OFF);
						}
					}

#ifndef __APPLE__
				if(token=="PRIORITY")
					{
					if(token2=="REALTIME")
						{
						SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
						}
					if(token2=="HIGH")
						{
						SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);
						}
					if(token2=="ABOVE_NORMAL")
						{
						SetPriorityClass(GetCurrentProcess(),ABOVE_NORMAL_PRIORITY_CLASS);
						}
					if(token2=="NORMAL")
						{
						SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS);
						}
					if(token2=="BELOW_NORMAL")
						{
						SetPriorityClass(GetCurrentProcess(),BELOW_NORMAL_PRIORITY_CLASS);
						}
					if(token2=="IDLE")
						{
						SetPriorityClass(GetCurrentProcess(),IDLE_PRIORITY_CLASS);
						}
					}
#endif

				if(token=="TEXTURE_PARAM")
					{
					if(token2=="LINEAR")
						{
						init.window.flag.add_flag(INIT_WINDOW_FLAG_TEXTURE_LINEAR);
						}
					}
				if(token=="TOPMOST")
					{
					if(token2=="YES")
						{
						init.window.flag.add_flag(INIT_WINDOW_FLAG_TOPMOST);
						}
					}
				if(token=="FPS")
					{
					if(token2=="YES")
						{
						gps.display_frames=1;
						}
					}
				if(token=="MOUSE_PICTURE")
					{
					if(token2=="YES")
						{
						init.input.flag.add_flag(INIT_INPUT_FLAG_MOUSE_PICTURE);
						}
					}
				if(!token.compare("FPS_CAP"))
					{
					long fps=convert_string_to_long(token2);
					if(fps>10000)fps=10000;
					if(fps<1)fps=1;
					init.display.dwarf_frame_rate.QuadPart=enabler.qpfr.QuadPart/fps;
					}
				if(!token.compare("G_FPS_CAP"))
					{
					long fps=convert_string_to_long(token2);
					if(fps>10000)fps=10000;
					if(fps<1)fps=1;
					init.display.g_frame_rate.QuadPart=enabler.qpfr.QuadPart/fps;
					enabler.g_qprate=init.display.g_frame_rate;
					}
				if(token=="WINDOWED")
					{
					if(token2=="YES")
						{
						init.display.windowed=INIT_DISPLAY_WINDOW_TRUE;
						}
					if(token2=="NO")
						{
						init.display.windowed=INIT_DISPLAY_WINDOW_FALSE;
						}
					if(token2=="PROMPT")
						{
						init.display.windowed=INIT_DISPLAY_WINDOW_PROMPT;
						}
					}
				if(token=="GRID")
					{
					string token3;
					if(str.length()>=token.length()+token2.length()+3)
						{
						grab_token_string_pos(token3,str,token.length()+token2.length()+3);
						}

					init.display.small_grid_x=convert_string_to_long(token2);
					init.display.small_grid_y=convert_string_to_long(token3);
					if(init.display.small_grid_x<80)init.display.small_grid_x=80;
					if(init.display.small_grid_x>MAX_GRID_X)init.display.small_grid_x=MAX_GRID_X;
					if(init.display.small_grid_y<25)init.display.small_grid_y=25;
					if(init.display.small_grid_y>MAX_GRID_Y)init.display.small_grid_y=MAX_GRID_Y;
					}
				if(token=="FULLGRID")
					{
					string token3;
					if(str.length()>=token.length()+token2.length()+3)
						{
						grab_token_string_pos(token3,str,token.length()+token2.length()+3);
						}

					init.display.large_grid_x=convert_string_to_long(token2);
					init.display.large_grid_y=convert_string_to_long(token3);
					if(init.display.large_grid_x<80)init.display.large_grid_x=80;
					if(init.display.large_grid_x>MAX_GRID_X)init.display.large_grid_x=MAX_GRID_X;
					if(init.display.large_grid_y<25)init.display.large_grid_y=25;
					if(init.display.large_grid_y>MAX_GRID_Y)init.display.large_grid_y=MAX_GRID_Y;
					}
				if(token=="START_NATION")
					{
					init.feature.start_nation=convert_string_to_long(token2);
					if(init.feature.start_nation<2)init.feature.start_nation=2;
					if(init.feature.start_nation>52)init.feature.start_nation=52;
					}
				if(!token.compare("BLACK_R"))
					{
					enabler.ccolor[0][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("BLACK_G"))
					{
					enabler.ccolor[0][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("BLACK_B"))
					{
					enabler.ccolor[0][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("BLUE_R"))
					{
					enabler.ccolor[1][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("BLUE_G"))
					{
					enabler.ccolor[1][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("BLUE_B"))
					{
					enabler.ccolor[1][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("GREEN_R"))
					{
					enabler.ccolor[2][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("GREEN_G"))
					{
					enabler.ccolor[2][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("GREEN_B"))
					{
					enabler.ccolor[2][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("CYAN_R"))
					{
					enabler.ccolor[3][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("CYAN_G"))
					{
					enabler.ccolor[3][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("CYAN_B"))
					{
					enabler.ccolor[3][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("RED_R"))
					{
					enabler.ccolor[4][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("RED_G"))
					{
					enabler.ccolor[4][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("RED_B"))
					{
					enabler.ccolor[4][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("MAGENTA_R"))
					{
					enabler.ccolor[5][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("MAGENTA_G"))
					{
					enabler.ccolor[5][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("MAGENTA_B"))
					{
					enabler.ccolor[5][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("BROWN_R"))
					{
					enabler.ccolor[6][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("BROWN_G"))
					{
					enabler.ccolor[6][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("BROWN_B"))
					{
					enabler.ccolor[6][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LGRAY_R"))
					{
					enabler.ccolor[7][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LGRAY_G"))
					{
					enabler.ccolor[7][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LGRAY_B"))
					{
					enabler.ccolor[7][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("DGRAY_R"))
					{
					enabler.ccolor[8][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("DGRAY_G"))
					{
					enabler.ccolor[8][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("DGRAY_B"))
					{
					enabler.ccolor[8][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LBLUE_R"))
					{
					enabler.ccolor[9][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LBLUE_G"))
					{
					enabler.ccolor[9][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LBLUE_B"))
					{
					enabler.ccolor[9][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LGREEN_R"))
					{
					enabler.ccolor[10][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LGREEN_G"))
					{
					enabler.ccolor[10][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LGREEN_B"))
					{
					enabler.ccolor[10][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LCYAN_R"))
					{
					enabler.ccolor[11][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LCYAN_G"))
					{
					enabler.ccolor[11][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LCYAN_B"))
					{
					enabler.ccolor[11][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LRED_R"))
					{
					enabler.ccolor[12][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LRED_G"))
					{
					enabler.ccolor[12][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LRED_B"))
					{
					enabler.ccolor[12][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LMAGENTA_R"))
					{
					enabler.ccolor[13][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LMAGENTA_G"))
					{
					enabler.ccolor[13][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("LMAGENTA_B"))
					{
					enabler.ccolor[13][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("YELLOW_R"))
					{
					enabler.ccolor[14][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("YELLOW_G"))
					{
					enabler.ccolor[14][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("YELLOW_B"))
					{
					enabler.ccolor[14][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("WHITE_R"))
					{
					enabler.ccolor[15][0]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("WHITE_G"))
					{
					enabler.ccolor[15][1]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("WHITE_B"))
					{
					enabler.ccolor[15][2]=(float)convert_string_to_long(token2)/255.0f;
					}
				if(!token.compare("SOUND"))
					{
					if(token2!="ON")
						{
						init.media.flag.add_flag(INIT_MEDIA_FLAG_SOUND_OFF);
						}
					}
				if(!token.compare("VOLUME"))
					{
					init.media.volume=convert_string_to_long(token2);
					}
				if(!token.compare("KEY_HOLD_MS"))
					{
					init.input.hold_time=convert_string_to_long(token2);

					if(init.input.hold_time<100)init.input.hold_time=100;
					}
				}
			}
		}
	fseed.close();

	#ifdef _DEBUG
		enabler.window.init.isFullScreen = FALSE;
	#else
	//FULL SCREEN QUERY, UNLESS IT'S ALREADY SET IN INIT
	if(enabler.command_line.empty())
		{
		if(init.display.windowed==INIT_DISPLAY_WINDOW_TRUE)
			{
			enabler.window.init.isFullScreen = FALSE;
			}
		else if(init.display.windowed==INIT_DISPLAY_WINDOW_FALSE)
			{
			enabler.window.init.isFullScreen = TRUE;
			}
		else
			{
			if (MessageBox (HWND_DESKTOP, "Run in Fullscreen Mode?  You can set your preferences in data\\init\\init.txt.\rUnless you've changed your bindings, you can press F11 to toggle this setting any time.", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
				{
				enabler.window.init.isFullScreen = FALSE;								// If Not, Run In Windowed Mode
				}
			}
		}
	else enabler.window.init.isFullScreen = FALSE;
	#endif

	enabler.create_full_screen = enabler.window.init.isFullScreen;						// create_full_screen Is Set To User Default

	if(enabler.create_full_screen)
		{
		init.display.grid_x=init.display.large_grid_x;
		init.display.grid_y=init.display.large_grid_y;
		}
	else
		{
		init.display.grid_x=init.display.small_grid_x;
		init.display.grid_y=init.display.small_grid_y;
		}
	init.display.orig_grid_x=init.display.grid_x;
	init.display.orig_grid_y=init.display.grid_y;

	enabler.inactive_mode=0;

	enabler.texture_create_multi_pdim(small_font,1,init.font.small_font_texpos,init.font.small_font_datapos,16,16,
		init.font.small_font_adjx,init.font.small_font_adjy,init.font.small_font_dispx,init.font.small_font_dispy);
	enabler.texture_create_multi_pdim(large_font,1,init.font.large_font_texpos,init.font.large_font_datapos,16,16,
		init.font.large_font_adjx,init.font.large_font_adjy,init.font.large_font_dispx,init.font.large_font_dispy);

	gps.prepare_rect(1);
	#endif

	//SET UP SOUNDS
#ifndef NO_FMOD
	if(!init.media.flag.has_flag(INIT_MEDIA_FLAG_SOUND_OFF))
		{
		musicsound.initsound();

		string ms_file;

		ms_file="data/sound/song_title.ogg";
		musicsound.set_song(ms_file,SONG_TITLE);

		ms_file="data/sound/song_game.ogg";
		musicsound.set_song(ms_file,SONG_GAME);
		}
#endif

	srand(GetTickCount());
	basic_seed=GetTickCount();
	mt_init();

	//HANDLE GRAPHICS
	string tex;
		
	tex="data/art/mouse.bmp";
	gps.tex_pos[TEXTURE_MOUSE]=enabler.texture_create(tex,1,1);

	//HANDLE FILES
	svector<char *> processfilename;
	char *c;
	int f;
	textlinesst setuplines;

	//UPDATE THE INITIAL FILES IF NECESSARY

	//MAKE SURE THE ROOT AND OTHERS ARE THERE
	CreateDirectory("data",NULL);
	CreateDirectory("data/movies",NULL);
	CreateDirectory("data/save",NULL);
	CreateDirectory("data/save/current",NULL);

	game.clean_directory("data/save/current");

	char str[200];

	//MAKE THE DIRECTORY LIST
	svector<char *> dirlist;
	#ifdef DEBUG_PROCESS_ALL_RAWS
	c=new char[40];
		strcpy(c,"");
	dirlist.push_back(c);
	c=new char[40];
		strcpy(c,"/announcement");
	dirlist.push_back(c);
	c=new char[40];
		strcpy(c,"/dipscript");
	dirlist.push_back(c);
	c=new char[40];
		strcpy(c,"/dipscript/text");
	dirlist.push_back(c);
	c=new char[40];
		strcpy(c,"/help");
	dirlist.push_back(c);
	#endif
	c=new char[40];
		strcpy(c,"/objects");
	dirlist.push_back(c);

	//MAKE THE DIRECTORY STRUCTURE
	int fol;
	for(fol=0;fol<dirlist.size();fol++)
		{
		strcpy(str,"data/");
		strcat(str,dirlist[fol]);
		CreateDirectory(str,NULL);
		}

	//GRAB THE NAMES OF FILES TO BE CHANGED
	for(fol=0;fol<dirlist.size();fol++)
		{
		strcpy(str,"raw");
		strcat(str,dirlist[fol]);
		strcat(str,"/*.txt");

		svector<char *> processfilename2;
		find_files_by_pattern(str,processfilename2);

		long tr;
		for(tr=0;tr<processfilename2.size();tr++)
			{
			c=new char[strlen(processfilename2[tr])+strlen(dirlist[fol])+2];
				strcpy(c,dirlist[fol]);
				strcat(c,"/");
				strcat(c,processfilename2[tr]);
			delete[] processfilename2[tr];
			processfilename.push_back(c);
			}
		}

	//PROCESS FILES
	for(f=0;f<processfilename.size();f++)
		{
		strcpy(str,"raw");
		strcat(str,processfilename[f]);
		setuplines.load_raw_to_lines(str);

		strcpy(str,"data");
		strcat(str,processfilename[f]);
		str[strlen(str)-4]='\x0';//GET RID OF ".txt"

		setuplines.save_lines(str);
		}

	for(f=0;f<processfilename.size();f++)
		{
		delete[] processfilename[f];
		}
	for(fol=0;fol<dirlist.size();fol++)
		{
		delete[] dirlist[fol];
		}
	processfilename.clear();
	dirlist.clear();

	loadoptionfiles();

#ifdef __APPLE__
	find_files_by_pattern("raw/objects/*",processfilename);
#else
	find_files_by_pattern("raw/objects/*.*",processfilename);
#endif

	string chktype="NATION";
	for(f=0;f<processfilename.size();f++)
		{
		strcpy(str,"raw/objects/");
		strcat(str,processfilename[f]);
		setuplines.load_raw_to_lines(str);
		process_object_lines(setuplines,chktype);

		delete[] processfilename[f];
		}
	processfilename.clear();

	game.nation_def.finalize();
	gps.prepare_graphics();

	viewscreen_titlest::create(INTERFACE_PUSH_AT_BACK);

	//SET UP THE TEXT SYSTEM
	/*
	string file_name;
	file_name="data/speech/general.txt";
	enabler.text_system.register_file_fixed(file_name,TEXT_SPEECH_GENERAL,'@',0);
	*/
	enabler.text_system.initialize_system();

	return 1;
}

bool abstract_drawline(long sx,long sy,long sz,
						long ex,long ey,long ez)
{
	long xdelta,ydelta,zdelta,cycle,cycle2,xstep,ystep,zstep;
	xdelta=ex-sx;
	ydelta=ey-sy;
	zdelta=ez-sz;
	if(xdelta<0)
		{
		xdelta=-xdelta;
		xstep=-1;
		}
	else xstep=1;
	if(ydelta<0)
		{
		ydelta=-ydelta;
		ystep=-1;
		}
	else ystep=1;
	if(zdelta<0)
		{
		zdelta=-zdelta;
		zstep=-1;
		}
	else zstep=1;

	long *major=&sx;
	long *madelta=&xdelta;
	long *mastep=&xstep;
	long *minor=&sy;
	long *midelta=&ydelta;
	long *mistep=&ystep;
	long *minor2=&sz;
	long *midelta2=&zdelta;
	long *mistep2=&zstep;

	if(zdelta>xdelta&&zdelta>ydelta)
		{
		minor2=&sx;
		midelta2=&xdelta;
		mistep2=&xstep;
		major=&sz;
		madelta=&zdelta;
		mastep=&zstep;
		}
	else if(ydelta>xdelta)
		{
		minor=&sx;
		midelta=&xdelta;
		mistep=&xstep;
		major=&sy;
		madelta=&ydelta;
		mastep=&ystep;
		}

	long steps=*madelta;

	linelim=0;

	cycle=0;
	cycle2=0;
	while(steps>0)
		{
		line[0][linelim][0]=sx;
		line[0][linelim][1]=sy;
		line[0][linelim][2]=sz;
		linelim++;

		cycle+=*midelta;
		if(2*cycle>*madelta)
			{
			cycle-=*madelta;
			*minor+=*mistep;
			}
		cycle2+=*midelta2;
		if(2*cycle2>*madelta)
			{
			cycle2-=*madelta;
			*minor2+=*mistep2;
			}

		*major+=*mastep;steps--;
		}

	line[0][linelim][0]=ex;
	line[0][linelim][1]=ey;
	line[0][linelim][2]=ez;
	linelim++;

	return 1;
}

char standardstringentry(char *str,int maxlen,unsigned long flag)
{
	string str2;
	str2=str;
	char ret=standardstringentry(str2,maxlen,flag);
	strcpy(str,str2.c_str());
	return ret;
}

char standardstringentry(string &str,int maxlen,unsigned long flag)
{
	unsigned char entry=255;
	if(flag & STRINGENTRY_LETTERS)
		{
		if(gview.keypress(INTERFACEKEY_STRING_A097))entry='a';
		if(gview.keypress(INTERFACEKEY_STRING_A098))entry='b';
		if(gview.keypress(INTERFACEKEY_STRING_A099))entry='c';
		if(gview.keypress(INTERFACEKEY_STRING_A100))entry='d';
		if(gview.keypress(INTERFACEKEY_STRING_A101))entry='e';
		if(gview.keypress(INTERFACEKEY_STRING_A102))entry='f';
		if(gview.keypress(INTERFACEKEY_STRING_A103))entry='g';
		if(gview.keypress(INTERFACEKEY_STRING_A104))entry='h';
		if(gview.keypress(INTERFACEKEY_STRING_A105))entry='i';
		if(gview.keypress(INTERFACEKEY_STRING_A106))entry='j';
		if(gview.keypress(INTERFACEKEY_STRING_A107))entry='k';
		if(gview.keypress(INTERFACEKEY_STRING_A108))entry='l';
		if(gview.keypress(INTERFACEKEY_STRING_A109))entry='m';
		if(gview.keypress(INTERFACEKEY_STRING_A110))entry='n';
		if(gview.keypress(INTERFACEKEY_STRING_A111))entry='o';
		if(gview.keypress(INTERFACEKEY_STRING_A112))entry='p';
		if(gview.keypress(INTERFACEKEY_STRING_A113))entry='q';
		if(gview.keypress(INTERFACEKEY_STRING_A114))entry='r';
		if(gview.keypress(INTERFACEKEY_STRING_A115))entry='s';
		if(gview.keypress(INTERFACEKEY_STRING_A116))entry='t';
		if(gview.keypress(INTERFACEKEY_STRING_A117))entry='u';
		if(gview.keypress(INTERFACEKEY_STRING_A118))entry='v';
		if(gview.keypress(INTERFACEKEY_STRING_A119))entry='w';
		if(gview.keypress(INTERFACEKEY_STRING_A120))entry='x';
		if(gview.keypress(INTERFACEKEY_STRING_A121))entry='y';
		if(gview.keypress(INTERFACEKEY_STRING_A122))entry='z';
		if(gview.keypress(INTERFACEKEY_STRING_A065))entry='A';
		if(gview.keypress(INTERFACEKEY_STRING_A066))entry='B';
		if(gview.keypress(INTERFACEKEY_STRING_A067))entry='C';
		if(gview.keypress(INTERFACEKEY_STRING_A068))entry='D';
		if(gview.keypress(INTERFACEKEY_STRING_A069))entry='E';
		if(gview.keypress(INTERFACEKEY_STRING_A070))entry='F';
		if(gview.keypress(INTERFACEKEY_STRING_A071))entry='G';
		if(gview.keypress(INTERFACEKEY_STRING_A072))entry='H';
		if(gview.keypress(INTERFACEKEY_STRING_A073))entry='I';
		if(gview.keypress(INTERFACEKEY_STRING_A074))entry='J';
		if(gview.keypress(INTERFACEKEY_STRING_A075))entry='K';
		if(gview.keypress(INTERFACEKEY_STRING_A076))entry='L';
		if(gview.keypress(INTERFACEKEY_STRING_A077))entry='M';
		if(gview.keypress(INTERFACEKEY_STRING_A078))entry='N';
		if(gview.keypress(INTERFACEKEY_STRING_A079))entry='O';
		if(gview.keypress(INTERFACEKEY_STRING_A080))entry='P';
		if(gview.keypress(INTERFACEKEY_STRING_A081))entry='Q';
		if(gview.keypress(INTERFACEKEY_STRING_A082))entry='R';
		if(gview.keypress(INTERFACEKEY_STRING_A083))entry='S';
		if(gview.keypress(INTERFACEKEY_STRING_A084))entry='T';
		if(gview.keypress(INTERFACEKEY_STRING_A085))entry='U';
		if(gview.keypress(INTERFACEKEY_STRING_A086))entry='V';
		if(gview.keypress(INTERFACEKEY_STRING_A087))entry='W';
		if(gview.keypress(INTERFACEKEY_STRING_A088))entry='X';
		if(gview.keypress(INTERFACEKEY_STRING_A089))entry='Y';
		if(gview.keypress(INTERFACEKEY_STRING_A090))entry='Z';
		}
	if(flag & STRINGENTRY_SPACE)
		{
		if(gview.keypress(INTERFACEKEY_STRING_A032))entry=' ';
		}
	if(gview.keypress(INTERFACEKEY_STRING_A000))entry='\x0';
	if(flag & STRINGENTRY_NUMBERS)
		{
		if(gview.keypress(INTERFACEKEY_STRING_A048))entry='0';
		if(gview.keypress(INTERFACEKEY_STRING_A049))entry='1';
		if(gview.keypress(INTERFACEKEY_STRING_A050))entry='2';
		if(gview.keypress(INTERFACEKEY_STRING_A051))entry='3';
		if(gview.keypress(INTERFACEKEY_STRING_A052))entry='4';
		if(gview.keypress(INTERFACEKEY_STRING_A053))entry='5';
		if(gview.keypress(INTERFACEKEY_STRING_A054))entry='6';
		if(gview.keypress(INTERFACEKEY_STRING_A055))entry='7';
		if(gview.keypress(INTERFACEKEY_STRING_A056))entry='8';
		if(gview.keypress(INTERFACEKEY_STRING_A057))entry='9';
		}
	if(flag & STRINGENTRY_SYMBOLS)
		{
		if(gview.keypress(INTERFACEKEY_STRING_A000))entry=0;
		if(gview.keypress(INTERFACEKEY_STRING_A001))entry=1;
		if(gview.keypress(INTERFACEKEY_STRING_A002))entry=2;
		if(gview.keypress(INTERFACEKEY_STRING_A003))entry=3;
		if(gview.keypress(INTERFACEKEY_STRING_A004))entry=4;
		if(gview.keypress(INTERFACEKEY_STRING_A005))entry=5;
		if(gview.keypress(INTERFACEKEY_STRING_A006))entry=6;
		if(gview.keypress(INTERFACEKEY_STRING_A007))entry=7;
		if(gview.keypress(INTERFACEKEY_STRING_A008))entry=8;
		if(gview.keypress(INTERFACEKEY_STRING_A009))entry=9;
		if(gview.keypress(INTERFACEKEY_STRING_A010))entry=10;
		if(gview.keypress(INTERFACEKEY_STRING_A011))entry=11;
		if(gview.keypress(INTERFACEKEY_STRING_A012))entry=12;
		if(gview.keypress(INTERFACEKEY_STRING_A013))entry=13;
		if(gview.keypress(INTERFACEKEY_STRING_A014))entry=14;
		if(gview.keypress(INTERFACEKEY_STRING_A015))entry=15;
		if(gview.keypress(INTERFACEKEY_STRING_A016))entry=16;
		if(gview.keypress(INTERFACEKEY_STRING_A017))entry=17;
		if(gview.keypress(INTERFACEKEY_STRING_A018))entry=18;
		if(gview.keypress(INTERFACEKEY_STRING_A019))entry=19;
		if(gview.keypress(INTERFACEKEY_STRING_A020))entry=20;
		if(gview.keypress(INTERFACEKEY_STRING_A021))entry=21;
		if(gview.keypress(INTERFACEKEY_STRING_A022))entry=22;
		if(gview.keypress(INTERFACEKEY_STRING_A023))entry=23;
		if(gview.keypress(INTERFACEKEY_STRING_A024))entry=24;
		if(gview.keypress(INTERFACEKEY_STRING_A025))entry=25;
		if(gview.keypress(INTERFACEKEY_STRING_A026))entry=26;
		if(gview.keypress(INTERFACEKEY_STRING_A027))entry=27;
		if(gview.keypress(INTERFACEKEY_STRING_A028))entry=28;
		if(gview.keypress(INTERFACEKEY_STRING_A029))entry=29;
		if(gview.keypress(INTERFACEKEY_STRING_A030))entry=30;
		if(gview.keypress(INTERFACEKEY_STRING_A031))entry=31;
		if(gview.keypress(INTERFACEKEY_STRING_A032))entry=32;
		if(gview.keypress(INTERFACEKEY_STRING_A033))entry=33;
		if(gview.keypress(INTERFACEKEY_STRING_A034))entry=34;
		if(gview.keypress(INTERFACEKEY_STRING_A035))entry=35;
		if(gview.keypress(INTERFACEKEY_STRING_A036))entry=36;
		if(gview.keypress(INTERFACEKEY_STRING_A037))entry=37;
		if(gview.keypress(INTERFACEKEY_STRING_A038))entry=38;
		if(gview.keypress(INTERFACEKEY_STRING_A039))entry=39;
		if(gview.keypress(INTERFACEKEY_STRING_A040))entry=40;
		if(gview.keypress(INTERFACEKEY_STRING_A041))entry=41;
		if(gview.keypress(INTERFACEKEY_STRING_A042))entry=42;
		if(gview.keypress(INTERFACEKEY_STRING_A043))entry=43;
		if(gview.keypress(INTERFACEKEY_STRING_A044))entry=44;
		if(gview.keypress(INTERFACEKEY_STRING_A045))entry=45;
		if(gview.keypress(INTERFACEKEY_STRING_A046))entry=46;
		if(gview.keypress(INTERFACEKEY_STRING_A047))entry=47;
		if(gview.keypress(INTERFACEKEY_STRING_A048))entry=48;
		if(gview.keypress(INTERFACEKEY_STRING_A049))entry=49;
		if(gview.keypress(INTERFACEKEY_STRING_A050))entry=50;
		if(gview.keypress(INTERFACEKEY_STRING_A051))entry=51;
		if(gview.keypress(INTERFACEKEY_STRING_A052))entry=52;
		if(gview.keypress(INTERFACEKEY_STRING_A053))entry=53;
		if(gview.keypress(INTERFACEKEY_STRING_A054))entry=54;
		if(gview.keypress(INTERFACEKEY_STRING_A055))entry=55;
		if(gview.keypress(INTERFACEKEY_STRING_A056))entry=56;
		if(gview.keypress(INTERFACEKEY_STRING_A057))entry=57;
		if(gview.keypress(INTERFACEKEY_STRING_A058))entry=58;
		if(gview.keypress(INTERFACEKEY_STRING_A059))entry=59;
		if(gview.keypress(INTERFACEKEY_STRING_A060))entry=60;
		if(gview.keypress(INTERFACEKEY_STRING_A061))entry=61;
		if(gview.keypress(INTERFACEKEY_STRING_A062))entry=62;
		if(gview.keypress(INTERFACEKEY_STRING_A063))entry=63;
		if(gview.keypress(INTERFACEKEY_STRING_A064))entry=64;
		if(gview.keypress(INTERFACEKEY_STRING_A065))entry=65;
		if(gview.keypress(INTERFACEKEY_STRING_A066))entry=66;
		if(gview.keypress(INTERFACEKEY_STRING_A067))entry=67;
		if(gview.keypress(INTERFACEKEY_STRING_A068))entry=68;
		if(gview.keypress(INTERFACEKEY_STRING_A069))entry=69;
		if(gview.keypress(INTERFACEKEY_STRING_A070))entry=70;
		if(gview.keypress(INTERFACEKEY_STRING_A071))entry=71;
		if(gview.keypress(INTERFACEKEY_STRING_A072))entry=72;
		if(gview.keypress(INTERFACEKEY_STRING_A073))entry=73;
		if(gview.keypress(INTERFACEKEY_STRING_A074))entry=74;
		if(gview.keypress(INTERFACEKEY_STRING_A075))entry=75;
		if(gview.keypress(INTERFACEKEY_STRING_A076))entry=76;
		if(gview.keypress(INTERFACEKEY_STRING_A077))entry=77;
		if(gview.keypress(INTERFACEKEY_STRING_A078))entry=78;
		if(gview.keypress(INTERFACEKEY_STRING_A079))entry=79;
		if(gview.keypress(INTERFACEKEY_STRING_A080))entry=80;
		if(gview.keypress(INTERFACEKEY_STRING_A081))entry=81;
		if(gview.keypress(INTERFACEKEY_STRING_A082))entry=82;
		if(gview.keypress(INTERFACEKEY_STRING_A083))entry=83;
		if(gview.keypress(INTERFACEKEY_STRING_A084))entry=84;
		if(gview.keypress(INTERFACEKEY_STRING_A085))entry=85;
		if(gview.keypress(INTERFACEKEY_STRING_A086))entry=86;
		if(gview.keypress(INTERFACEKEY_STRING_A087))entry=87;
		if(gview.keypress(INTERFACEKEY_STRING_A088))entry=88;
		if(gview.keypress(INTERFACEKEY_STRING_A089))entry=89;
		if(gview.keypress(INTERFACEKEY_STRING_A090))entry=90;
		if(gview.keypress(INTERFACEKEY_STRING_A091))entry=91;
		if(gview.keypress(INTERFACEKEY_STRING_A092))entry=92;
		if(gview.keypress(INTERFACEKEY_STRING_A093))entry=93;
		if(gview.keypress(INTERFACEKEY_STRING_A094))entry=94;
		if(gview.keypress(INTERFACEKEY_STRING_A095))entry=95;
		if(gview.keypress(INTERFACEKEY_STRING_A096))entry=96;
		if(gview.keypress(INTERFACEKEY_STRING_A097))entry=97;
		if(gview.keypress(INTERFACEKEY_STRING_A098))entry=98;
		if(gview.keypress(INTERFACEKEY_STRING_A099))entry=99;
		if(gview.keypress(INTERFACEKEY_STRING_A100))entry=100;
		if(gview.keypress(INTERFACEKEY_STRING_A101))entry=101;
		if(gview.keypress(INTERFACEKEY_STRING_A102))entry=102;
		if(gview.keypress(INTERFACEKEY_STRING_A103))entry=103;
		if(gview.keypress(INTERFACEKEY_STRING_A104))entry=104;
		if(gview.keypress(INTERFACEKEY_STRING_A105))entry=105;
		if(gview.keypress(INTERFACEKEY_STRING_A106))entry=106;
		if(gview.keypress(INTERFACEKEY_STRING_A107))entry=107;
		if(gview.keypress(INTERFACEKEY_STRING_A108))entry=108;
		if(gview.keypress(INTERFACEKEY_STRING_A109))entry=109;
		if(gview.keypress(INTERFACEKEY_STRING_A110))entry=110;
		if(gview.keypress(INTERFACEKEY_STRING_A111))entry=111;
		if(gview.keypress(INTERFACEKEY_STRING_A112))entry=112;
		if(gview.keypress(INTERFACEKEY_STRING_A113))entry=113;
		if(gview.keypress(INTERFACEKEY_STRING_A114))entry=114;
		if(gview.keypress(INTERFACEKEY_STRING_A115))entry=115;
		if(gview.keypress(INTERFACEKEY_STRING_A116))entry=116;
		if(gview.keypress(INTERFACEKEY_STRING_A117))entry=117;
		if(gview.keypress(INTERFACEKEY_STRING_A118))entry=118;
		if(gview.keypress(INTERFACEKEY_STRING_A119))entry=119;
		if(gview.keypress(INTERFACEKEY_STRING_A120))entry=120;
		if(gview.keypress(INTERFACEKEY_STRING_A121))entry=121;
		if(gview.keypress(INTERFACEKEY_STRING_A122))entry=122;
		if(gview.keypress(INTERFACEKEY_STRING_A123))entry=123;
		if(gview.keypress(INTERFACEKEY_STRING_A124))entry=124;
		if(gview.keypress(INTERFACEKEY_STRING_A125))entry=125;
		if(gview.keypress(INTERFACEKEY_STRING_A126))entry=126;
		if(gview.keypress(INTERFACEKEY_STRING_A127))entry=127;
		if(gview.keypress(INTERFACEKEY_STRING_A128))entry=128;
		if(gview.keypress(INTERFACEKEY_STRING_A129))entry=129;
		if(gview.keypress(INTERFACEKEY_STRING_A130))entry=130;
		if(gview.keypress(INTERFACEKEY_STRING_A131))entry=131;
		if(gview.keypress(INTERFACEKEY_STRING_A132))entry=132;
		if(gview.keypress(INTERFACEKEY_STRING_A133))entry=133;
		if(gview.keypress(INTERFACEKEY_STRING_A134))entry=134;
		if(gview.keypress(INTERFACEKEY_STRING_A135))entry=135;
		if(gview.keypress(INTERFACEKEY_STRING_A136))entry=136;
		if(gview.keypress(INTERFACEKEY_STRING_A137))entry=137;
		if(gview.keypress(INTERFACEKEY_STRING_A138))entry=138;
		if(gview.keypress(INTERFACEKEY_STRING_A139))entry=139;
		if(gview.keypress(INTERFACEKEY_STRING_A140))entry=140;
		if(gview.keypress(INTERFACEKEY_STRING_A141))entry=141;
		if(gview.keypress(INTERFACEKEY_STRING_A142))entry=142;
		if(gview.keypress(INTERFACEKEY_STRING_A143))entry=143;
		if(gview.keypress(INTERFACEKEY_STRING_A144))entry=144;
		if(gview.keypress(INTERFACEKEY_STRING_A145))entry=145;
		if(gview.keypress(INTERFACEKEY_STRING_A146))entry=146;
		if(gview.keypress(INTERFACEKEY_STRING_A147))entry=147;
		if(gview.keypress(INTERFACEKEY_STRING_A148))entry=148;
		if(gview.keypress(INTERFACEKEY_STRING_A149))entry=149;
		if(gview.keypress(INTERFACEKEY_STRING_A150))entry=150;
		if(gview.keypress(INTERFACEKEY_STRING_A151))entry=151;
		if(gview.keypress(INTERFACEKEY_STRING_A152))entry=152;
		if(gview.keypress(INTERFACEKEY_STRING_A153))entry=153;
		if(gview.keypress(INTERFACEKEY_STRING_A154))entry=154;
		if(gview.keypress(INTERFACEKEY_STRING_A155))entry=155;
		if(gview.keypress(INTERFACEKEY_STRING_A156))entry=156;
		if(gview.keypress(INTERFACEKEY_STRING_A157))entry=157;
		if(gview.keypress(INTERFACEKEY_STRING_A158))entry=158;
		if(gview.keypress(INTERFACEKEY_STRING_A159))entry=159;
		if(gview.keypress(INTERFACEKEY_STRING_A160))entry=160;
		if(gview.keypress(INTERFACEKEY_STRING_A161))entry=161;
		if(gview.keypress(INTERFACEKEY_STRING_A162))entry=162;
		if(gview.keypress(INTERFACEKEY_STRING_A163))entry=163;
		if(gview.keypress(INTERFACEKEY_STRING_A164))entry=164;
		if(gview.keypress(INTERFACEKEY_STRING_A165))entry=165;
		if(gview.keypress(INTERFACEKEY_STRING_A166))entry=166;
		if(gview.keypress(INTERFACEKEY_STRING_A167))entry=167;
		if(gview.keypress(INTERFACEKEY_STRING_A168))entry=168;
		if(gview.keypress(INTERFACEKEY_STRING_A169))entry=169;
		if(gview.keypress(INTERFACEKEY_STRING_A170))entry=170;
		if(gview.keypress(INTERFACEKEY_STRING_A171))entry=171;
		if(gview.keypress(INTERFACEKEY_STRING_A172))entry=172;
		if(gview.keypress(INTERFACEKEY_STRING_A173))entry=173;
		if(gview.keypress(INTERFACEKEY_STRING_A174))entry=174;
		if(gview.keypress(INTERFACEKEY_STRING_A175))entry=175;
		if(gview.keypress(INTERFACEKEY_STRING_A176))entry=176;
		if(gview.keypress(INTERFACEKEY_STRING_A177))entry=177;
		if(gview.keypress(INTERFACEKEY_STRING_A178))entry=178;
		if(gview.keypress(INTERFACEKEY_STRING_A179))entry=179;
		if(gview.keypress(INTERFACEKEY_STRING_A180))entry=180;
		if(gview.keypress(INTERFACEKEY_STRING_A181))entry=181;
		if(gview.keypress(INTERFACEKEY_STRING_A182))entry=182;
		if(gview.keypress(INTERFACEKEY_STRING_A183))entry=183;
		if(gview.keypress(INTERFACEKEY_STRING_A184))entry=184;
		if(gview.keypress(INTERFACEKEY_STRING_A185))entry=185;
		if(gview.keypress(INTERFACEKEY_STRING_A186))entry=186;
		if(gview.keypress(INTERFACEKEY_STRING_A187))entry=187;
		if(gview.keypress(INTERFACEKEY_STRING_A188))entry=188;
		if(gview.keypress(INTERFACEKEY_STRING_A189))entry=189;
		if(gview.keypress(INTERFACEKEY_STRING_A190))entry=190;
		if(gview.keypress(INTERFACEKEY_STRING_A191))entry=191;
		if(gview.keypress(INTERFACEKEY_STRING_A192))entry=192;
		if(gview.keypress(INTERFACEKEY_STRING_A193))entry=193;
		if(gview.keypress(INTERFACEKEY_STRING_A194))entry=194;
		if(gview.keypress(INTERFACEKEY_STRING_A195))entry=195;
		if(gview.keypress(INTERFACEKEY_STRING_A196))entry=196;
		if(gview.keypress(INTERFACEKEY_STRING_A197))entry=197;
		if(gview.keypress(INTERFACEKEY_STRING_A198))entry=198;
		if(gview.keypress(INTERFACEKEY_STRING_A199))entry=199;
		if(gview.keypress(INTERFACEKEY_STRING_A200))entry=200;
		if(gview.keypress(INTERFACEKEY_STRING_A201))entry=201;
		if(gview.keypress(INTERFACEKEY_STRING_A202))entry=202;
		if(gview.keypress(INTERFACEKEY_STRING_A203))entry=203;
		if(gview.keypress(INTERFACEKEY_STRING_A204))entry=204;
		if(gview.keypress(INTERFACEKEY_STRING_A205))entry=205;
		if(gview.keypress(INTERFACEKEY_STRING_A206))entry=206;
		if(gview.keypress(INTERFACEKEY_STRING_A207))entry=207;
		if(gview.keypress(INTERFACEKEY_STRING_A208))entry=208;
		if(gview.keypress(INTERFACEKEY_STRING_A209))entry=209;
		if(gview.keypress(INTERFACEKEY_STRING_A210))entry=210;
		if(gview.keypress(INTERFACEKEY_STRING_A211))entry=211;
		if(gview.keypress(INTERFACEKEY_STRING_A212))entry=212;
		if(gview.keypress(INTERFACEKEY_STRING_A213))entry=213;
		if(gview.keypress(INTERFACEKEY_STRING_A214))entry=214;
		if(gview.keypress(INTERFACEKEY_STRING_A215))entry=215;
		if(gview.keypress(INTERFACEKEY_STRING_A216))entry=216;
		if(gview.keypress(INTERFACEKEY_STRING_A217))entry=217;
		if(gview.keypress(INTERFACEKEY_STRING_A218))entry=218;
		if(gview.keypress(INTERFACEKEY_STRING_A219))entry=219;
		if(gview.keypress(INTERFACEKEY_STRING_A220))entry=220;
		if(gview.keypress(INTERFACEKEY_STRING_A221))entry=221;
		if(gview.keypress(INTERFACEKEY_STRING_A222))entry=222;
		if(gview.keypress(INTERFACEKEY_STRING_A223))entry=223;
		if(gview.keypress(INTERFACEKEY_STRING_A224))entry=224;
		if(gview.keypress(INTERFACEKEY_STRING_A225))entry=225;
		if(gview.keypress(INTERFACEKEY_STRING_A226))entry=226;
		if(gview.keypress(INTERFACEKEY_STRING_A227))entry=227;
		if(gview.keypress(INTERFACEKEY_STRING_A228))entry=228;
		if(gview.keypress(INTERFACEKEY_STRING_A229))entry=229;
		if(gview.keypress(INTERFACEKEY_STRING_A230))entry=230;
		if(gview.keypress(INTERFACEKEY_STRING_A231))entry=231;
		if(gview.keypress(INTERFACEKEY_STRING_A232))entry=232;
		if(gview.keypress(INTERFACEKEY_STRING_A233))entry=233;
		if(gview.keypress(INTERFACEKEY_STRING_A234))entry=234;
		if(gview.keypress(INTERFACEKEY_STRING_A235))entry=235;
		if(gview.keypress(INTERFACEKEY_STRING_A236))entry=236;
		if(gview.keypress(INTERFACEKEY_STRING_A237))entry=237;
		if(gview.keypress(INTERFACEKEY_STRING_A238))entry=238;
		if(gview.keypress(INTERFACEKEY_STRING_A239))entry=239;
		if(gview.keypress(INTERFACEKEY_STRING_A240))entry=240;
		if(gview.keypress(INTERFACEKEY_STRING_A241))entry=241;
		if(gview.keypress(INTERFACEKEY_STRING_A242))entry=242;
		if(gview.keypress(INTERFACEKEY_STRING_A243))entry=243;
		if(gview.keypress(INTERFACEKEY_STRING_A244))entry=244;
		if(gview.keypress(INTERFACEKEY_STRING_A245))entry=245;
		if(gview.keypress(INTERFACEKEY_STRING_A246))entry=246;
		if(gview.keypress(INTERFACEKEY_STRING_A247))entry=247;
		if(gview.keypress(INTERFACEKEY_STRING_A248))entry=248;
		if(gview.keypress(INTERFACEKEY_STRING_A249))entry=249;
		if(gview.keypress(INTERFACEKEY_STRING_A250))entry=250;
		if(gview.keypress(INTERFACEKEY_STRING_A251))entry=251;
		if(gview.keypress(INTERFACEKEY_STRING_A252))entry=252;
		if(gview.keypress(INTERFACEKEY_STRING_A253))entry=253;
		if(gview.keypress(INTERFACEKEY_STRING_A254))entry=254;
		if(gview.keypress(INTERFACEKEY_STRING_A255))entry=255;
		}

	if(entry!=255)
		{
		if(entry=='\x0')
			{
			if(str.length()>0)str.resize(str.length()-1);
			}
		else
			{
			int cursor=str.length();
			if(cursor>=maxlen)cursor=maxlen-1;
			if(cursor<0)cursor=0;

			if(str.length()<cursor+1)str.resize(cursor+1);

			if(entry>='a'&&entry<='z'&&(flag & STRINGENTRY_CAPS))str[cursor]=entry+'A'-'a';
			else str[cursor]=entry;
			}

		gview.c=0;

		return 1;
		}

	return 0;
}

char standardscrolling(short &selection,long min,long max,long jump,unsigned long flag)
{
	short osel=selection;

	long seltemp=selection;
	standardscrolling(seltemp,min,max,jump,flag);
	selection=seltemp;

	if(osel!=selection)return 1;
	else return 0;
}

void finishscrolling(long &selection,long min,long max,long jump,unsigned long flag,char littlekey)
{
	if(flag & SCROLLING_NOSELECT)
		{
		if(selection>max-jump+1)selection=max-jump+1;
		if(selection<min)selection=min;
		}
	else
		{
		//WRAP ONLY IF YOU USED LITTLE KEYS OR IF YOU WERE AT THE END
		if((littlekey||selection==min-jump||selection==max+jump)&&!(flag & SCROLLING_NO_WRAP))
			{
			if(selection>max)selection=min;
			if(selection<min)selection=max;
			}
		//OTHERWISE JUST CLUNK AT THE BOTTOM
		else
			{
			if(selection>max)selection=max;
			if(selection<min)selection=min;
			}
		}
}

char standardscrolling(long &selection,long min,long max,long jump,unsigned long flag)
{
	short osel=selection;

	//NOTE: THIS CAN HANDLE max = -1, min = 0
	char littlekey=0;
	if(flag & SCROLLING_REVERSE)
		{
		if(gview.keypress(INTERFACEKEY_STANDARDSCROLL_DOWN)){selection--;littlekey=1;}
		if(gview.keypress(INTERFACEKEY_STANDARDSCROLL_UP)){selection++;littlekey=1;}
		if(gview.keypress(INTERFACEKEY_STANDARDSCROLL_PAGEDOWN))selection-=jump;
		if(gview.keypress(INTERFACEKEY_STANDARDSCROLL_PAGEUP))selection+=jump;
		}
	else
		{
		if(gview.keypress(INTERFACEKEY_STANDARDSCROLL_UP)){selection--;littlekey=1;}
		if(gview.keypress(INTERFACEKEY_STANDARDSCROLL_DOWN)){selection++;littlekey=1;}
		if(gview.keypress(INTERFACEKEY_STANDARDSCROLL_PAGEUP))selection-=jump;
		if(gview.keypress(INTERFACEKEY_STANDARDSCROLL_PAGEDOWN))selection+=jump;
		}

	finishscrolling(selection,min,max,jump,flag,littlekey);

	if(osel!=selection)return 1;
	else return 0;
}

char secondaryscrolling(short &selection,long min,long max,long jump,unsigned long flag)
{
	long temp=selection;
	char ret=secondaryscrolling(temp,min,max,jump,flag);
	selection=temp;
	return ret;
}

char secondaryscrolling(long &selection,long min,long max,long jump,unsigned long flag)
{
	short osel=selection;

	//NOTE: THIS CAN HANDLE max = -1, min = 0
	char littlekey=0;
	if(flag & SCROLLING_REVERSE)
		{
		if(gview.keypress(INTERFACEKEY_SECONDSCROLL_DOWN)){selection--;littlekey=1;}
		if(gview.keypress(INTERFACEKEY_SECONDSCROLL_UP)){selection++;littlekey=1;}
		if(gview.keypress(INTERFACEKEY_SECONDSCROLL_PAGEDOWN))selection-=jump;
		if(gview.keypress(INTERFACEKEY_SECONDSCROLL_PAGEUP))selection+=jump;
		}
	else
		{
		if(gview.keypress(INTERFACEKEY_SECONDSCROLL_UP)){selection--;littlekey=1;}
		if(gview.keypress(INTERFACEKEY_SECONDSCROLL_DOWN)){selection++;littlekey=1;}
		if(gview.keypress(INTERFACEKEY_SECONDSCROLL_PAGEUP))selection-=jump;
		if(gview.keypress(INTERFACEKEY_SECONDSCROLL_PAGEDOWN))selection+=jump;
		}

	finishscrolling(selection,min,max,jump,flag,littlekey);

	if(osel!=selection)return 1;
	else return 0;
}

void addtext(svector<char *> &text,const string &s,int length)
{
	addtext(text,s.c_str(),length);
}

void addtext(svector<char *> &text,const char *s,int length)
{
	char startstr[20];
	strcpy(startstr,"");

	int totalwidth;
	int curpos=0;

	int addstrcur;
	char addstring[500];

	char content;

	long s_len=strlen(s);

	while(curpos<s_len)
		{
		content=0;
		totalwidth=0;

		strcpy(addstring,startstr);
		addstrcur=strlen(addstring);

		unsigned int i;
		for(i=curpos;i<s_len;i++)
			{
			if(s[i]=='&'&&s[i+1]!='&')
				{
				i++;
				if(s[i]=='r')
					{
					content=1;
					i++;
					addstrcur+=1;
					addstring[addstrcur-1]=' ';
					addstring[addstrcur]='\x0';
					break;
					}
				}
			else
				{
				content=1;

				if(s[i]=='&')i++;
				addstring[addstrcur]=s[i];
				addstring[addstrcur+1]='\x0';
				totalwidth++;
				if(totalwidth>length)
					{
					while(s[i]!=' '){i--;addstrcur--;}
					while(s[i]==' ')i++;
					addstring[addstrcur]='\x0';
					break;
					}
				addstrcur++;
				}
			}

		if(i==s_len)addstring[addstrcur]='\x0';

		if(strlen(addstring)>0&&content)
			{
			char *news=new char[strlen(addstring)+1];
			strcpy(news,addstring);
			text.push_back(news);
			}

		curpos=i;
		}
}

void loadoptionfiles()
{
	//LOAD THE FILE
	std::ifstream fseed("data/init/interface.txt");
	if(fseed.is_open())
		{
		string str;

		while(std::getline(fseed,str))
			{
			long pos;
			for(pos=0;pos<str.length();pos++)
				{
				//SEE IF YOU ARE AT THE NEXT TOKEN
				if(str[pos]=='[')
					{
					string temptoken;
					string temptoken2;
					string temptoken3;

					pos++;if(pos>=str.length())continue;
					grab_token_string_pos(temptoken,str,pos);
					pos+=temptoken.length();
					pos++;if(pos>=str.length())continue;
					grab_token_string_pos(temptoken2,str,pos);
					pos+=temptoken2.length();
					if(temptoken=="DISPLAY_STRING")
						{
						pos++;if(pos>=str.length())continue;
						grab_token_string_pos(temptoken3,str,pos);
						pos+=temptoken3.length();

						interfacekeyst key;
						convertstring_interfacechar_save(temptoken2,key);

						if(key.binding!=0)
							{
							short ind=0;
							if(key.shift)ind++;
							if(key.ctrl)ind+=2;
							if(key.alt)ind+=4;
							gview.display_string[key.binding][ind]=temptoken3;
							}

						continue;
						}

					interfacekeyst key;
					convertstring_interfacechar_save(temptoken2,key);
				
					long i;
					for(i=0;i<INTERFACEKEYNUM;i++)
						{
						if(gview.interfacekey[i].tokenname==temptoken)
							{
							gview.interfacekey[i].binding=key.binding;
							gview.interfacekey[i].shift=key.shift;
							gview.interfacekey[i].ctrl=key.ctrl;
							gview.interfacekey[i].alt=key.alt;
							break;
							}
						}

					if(i==INTERFACEKEYNUM)
						{
						string str="Unknown Interface Token: ";
						str+=temptoken;
						errorlog_string(str);
						}
					}
				}
			}
		}
	fseed.close();
}

void process_object_lines(textlinesst &lines,string &chktype)
{
	//NOTE: START AT 1 TO SKIP FILE NAME
	long t,pos;
	char *curstr;

	for(t=1;t<lines.text.size();t++)
		{
		curstr=lines.text[t];

		for(pos=0;pos<strlen(curstr);pos++)
			{
			//SEE IF YOU ARE AT THE NEXT TOKEN
			if(curstr[pos]=='[')
				{
				char temptoken[MAX_GRID_X];
				pos++;if(pos>=strlen(curstr))continue;
				grab_token(temptoken,curstr+pos);
				pos+=strlen(temptoken);

				if(!strcmp(temptoken,"OBJECT"))
					{
					pos++;if(pos>=strlen(curstr))continue;
					grab_token(temptoken,curstr+pos);
					pos+=strlen(temptoken);

					if(!strcmp(temptoken,chktype.c_str()))
						{
						if(!strcmp(temptoken,"GRAPHICS"))
							{
							gps.texture.adopt_new_lines(lines);
							return;
							}
						if(!strcmp(temptoken,"NATION"))
							{
							game.nation_def.adopt_new_lines(lines);
							return;
							}
						}
					}
				}
			}
		}
}

void gamest::print_interface_token(InterfaceKey key)
{
	short o_screenf=gps.screenf,o_screenb=gps.screenb,o_screenbright=gps.screenbright;
	gps.changecolor(2,0,1);
	string tok;
	getstring_interfacechar(tok,gview.interfacekey[key]);
	gps.addst(tok);
	gps.changecolor(o_screenf,o_screenb,o_screenbright);
}

void gamest::clean_directory(const string &directory)
{
	stringvectst filelist;

	string str;

	string sch=directory;
#ifdef __APPLE__
	sch+="/*";
#else
	sch+="/*.*";
#endif

	find_files_by_pattern(sch.c_str(),filelist);

	string delr;
	long f;
	for(f=0;f<filelist.str.size();f++)
		{
		delr=directory+"/"+filelist.str[f]->dat;
		unlink(delr.c_str());
		}
}

void gamest::copy_file(const string &src,const string &dst)
{
	std::ifstream in_stream(src.c_str(),std::ios_base::binary);
	std::ofstream out_stream(dst.c_str(),std::ios_base::binary);
	if(in_stream.is_open()&&out_stream.is_open())
		{
		out_stream<<in_stream.rdbuf();
		}
	in_stream.close();
	out_stream.close();
}

void drawborder(const char *str,char style)
{
	//DRAW BORDER
	gps.erasescreen();

	if(str!=NULL)
		{
		string pstr=str;
		if(pstr.length()>init.display.grid_x-2)
			{
			pstr.resize(init.display.grid_x-2);
			//MAKE SOME OF THE SPACES EVEN
			if(pstr[0]==' ')pstr[init.display.grid_x-3]=' ';
			if(pstr[1]==' ')pstr[init.display.grid_x-4]=' ';
			}

		gps.locate(0,((init.display.grid_x-1)/2)-((pstr.length()-1)>>1));
		gps.changecolor(COLOR_WHITE,COLOR_BLACK,1);
		gps.addst(pstr);
		}

	//DISPLAY RECORDER STATUS
	if(gview.is_supermovie_on())
		{
		if(GetTickCount()%1000<500)
			{
			gps.setclipping(0,init.display.grid_x-1,0,init.display.grid_y-1);
			gps.locate(init.display.grid_y-1,init.display.grid_x-3);
			gps.changecolor(4,4,1);
			gps.addst("REC");
			}
		}
}

void grab_token(char *dest,const char *source,char compc)
{
	strcpy(dest,"");

	//GO UNTIL YOU HIT A :, ], or the end
	int s;
	for(s=0;s<strlen(source);s++)
		{
		if(source[s]==compc||source[s]==']')break;
		dest[s]=source[s];
		}
	dest[s]='\x0';
}

char grab_token_string(string &dest,const char *source,long &pos,char compc)
{
	dest.erase();

	pos++;if(pos>=strlen(source))return 0;
	grab_token_string(dest,source+pos,compc);
	pos+=dest.length();
	return 1;
}

void grab_token_string(string &dest,string &source,char compc)
{
	dest.erase();

	//GO UNTIL YOU HIT A :, ], or the end
	int s;
	for(s=0;s<source.length();s++)
		{
		if(source[s]==compc||source[s]==']')break;
		dest+=source[s];
		}
}

void grab_token_string_pos(string &dest,string &source,long pos,char compc)
{
	dest.erase();

	//GO UNTIL YOU HIT A :, ], or the end
	int s;
	for(s=pos;s<source.length();s++)
		{
		if(source[s]==compc||source[s]==']')break;
		dest+=source[s];
		}
}

void grab_token_string(string &dest,const char *source,char compc)
{
	dest.erase();

	//GO UNTIL YOU HIT A :, ], or the end
	int s;
	for(s=0;s<strlen(source);s++)
		{
		if(source[s]==compc||source[s]==']')break;
		dest+=source[s];
		}
}

void gamest::clean()
{
	map.clean();
	nation.clean();
	nation_def.clean();
}

void gamest::quick_resolve_conflict(long t)
{
	svector<battle_armyst *> battle_army;
	get_battle_armies(t,battle_army);

	//MOVEMENT
	if(battle_army.size()==1)
		{
		//CLEAR OUT STATIONARIES
		long a,a2;
		for(a=(long)battle_army[0]->army.size()-1;a>=0;a--)
			{
			if(battle_army[0]->army[a]->destination_territory!=t)battle_army[0]->army.erase(a);
			}

		for(a=0;a<9;a++)
			{
			if(map.territory[t].army_id[a]==-1)
				{
				if(battle_army[0]->army.size()==0)break;

				map.territory[t].nation_id=battle_army[0]->global_id;
				nationst *nt=game.nation.get_nation_by_global_id(battle_army[0]->global_id);
				if(nt!=NULL)
					{
					game.map.territory[t].sym=nt->sym;
					game.map.territory[t].f=nt->f;
					game.map.territory[t].br=nt->br;
					}

				map.territory[t].army_id[a]=battle_army[0]->army[0]->global_id;

				for(a2=0;a2<9;a2++)
					{
					if(map.territory[battle_army[0]->army[0]->current_territory].army_id[a2]==battle_army[0]->army[0]->global_id)
						{
						map.territory[battle_army[0]->army[0]->current_territory].army_id[a2]=-1;
						}
					}

				battle_army[0]->army[0]->current_territory=t;
				battle_army[0]->army[0]->destination_territory=-1;
				battle_army[0]->army.erase(0);
				}
			}
		}
	//AI FIGHTS
	else if(battle_army.size()>=2)
		{
		//******************************* RESOLVE AI FIGHTS
		}

	long a;
	for(a=(long)battle_army.size()-1;a>=0;a--)delete battle_army[a];
}

void gamest::prepare_fight(long t)
{
	svector<battle_armyst *> battle_army;
	get_battle_armies(t,battle_army);

	viewscreen_fightst::create(battle_army,INTERFACE_PUSH_AT_BACK);
}

void gamest::get_battle_armies(long t,svector<battle_armyst *> &battle_army)
{
	battle_armyst *ba;
	long a;

	//ARMY STAYING IN THE TERRITORY
	nationst *nt=game.nation.get_nation_by_global_id(game.map.territory[t].nation_id);
	if(nt!=NULL)
		{
		for(a=0;a<9;a++)
			{
			armyst *arm=get_from_global_id_vector(game.map.territory[t].army_id[a],nt->army);
			if(arm!=NULL)
				{
				if(arm->destination_territory==-1)
					{
					ba=get_from_global_id_vector(nt->global_id,battle_army);
					if(ba==NULL)
						{
						ba=new battle_armyst;
							ba->global_id=nt->global_id;
						add_to_global_id_vector(ba,battle_army);
						}
					ba->army.push_back(arm);
					}
				}
			}
		}

	//ARMY ENTERING THE TERRITORY
	long n;
	for(n=0;n<game.nation.global.size();n++)
		{
		for(a=0;a<game.nation.global[n]->army.size();a++)
			{
			if(game.nation.global[n]->army[a]->destination_territory==t)
				{
				ba=get_from_global_id_vector(game.nation.global[n]->global_id,battle_army);
				if(ba==NULL)
					{
					ba=new battle_armyst;
						ba->global_id=game.nation.global[n]->global_id;
					add_to_global_id_vector(ba,battle_army);
					}
				ba->army.push_back(game.nation.global[n]->army[a]);
				}
			}
		}
}