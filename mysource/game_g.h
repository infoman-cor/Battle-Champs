//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#if defined(__APPLE__)
#include "platform.h"
#else
#include <windows.h>
#endif
#include <string.h>
#include <math.h>
#include <iosfwd>
#include <iostream>
#include <ios>
#include <streambuf>
#include <istream>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <fstream>
#if defined(__APPLE__)
#include <zlib.h>
#else
#include "../zlib/zlib.h"
#endif

#include "svector.h"
using std::string;

#include "random.h"

#include "endian.h"

#include "files.h"

#include "enabler.h"

#include "find_files.h"

#ifndef ENABLER
	#define CURSES
#endif

#ifdef CURSES
	#include "..\curses.h"
	#undef clear
	#undef erase

	#define CHECK_ERR(err, msg) { \
		if (err != Z_OK) { \
			nodelay(stdscr,FALSE); \
			drawborder(NULL,-1);\
			changecolor(7,0,1); \
			locate(0,0);\
			addst(msg);\
			addst(" error: ");\
			char num[20];\
			itoa(err,num,10);\
			addst(num);\
			renewscreen();\
			getch();\
			exit(1); \
		} \
	}
#endif

inline void CHECK_ERR(int err, const char* msg)
{
	if (err != Z_OK)
		{
		MessageBox(NULL, "One of the compressed files on disk has errors in it.  Restore from backup if you are able.", 0, 0);
		exit(1);
		}
}

//#pragma warning( 3 : 4189 )

#include "textlines.h"

#include "basics.h"

#include "graphics.h"

#include "music_and_sound_g.h"

#include "map.h"

#include "nation_def.h"

#include "nation.h"

#include "compat.h"

#include "interface.h"

#include "init.h"

#include "command_line.h"

class gamest
{
	public:
		command_linest command_line;
		mapst map;
		nation_handlerst nation;
		nation_def_handlerst nation_def;

		long next_text_id;


		gamest()
			{
			next_text_id=TEXTNUM;
			}

		void clean();

		void print_interface_token(InterfaceKey key);

		void clean_directory(const string &directory);
		void copy_file(const string &src,const string &dst);

		void get_battle_armies(long t,svector<battle_armyst *> &battle_army);

		void quick_resolve_conflict(long t);
		void prepare_fight(long t);
};

void addtext(svector<char *> &text,const char *s,int length);
void addtext(svector<char *> &text,const string &s,int length);

bool abstract_drawline(long sx,long sy,long sz,
					long ex,long ey,long ez);

void loadoptionfiles();

void grab_token(char *dest,const char *source,char compc=':');
void grab_token_string(string &dest,const char *source,char compc=':');
void grab_token_string(string &dest,string &source,char compc=':');
char grab_token_string(string &dest,const char *source,long &pos,char compc=':');
void grab_token_string_pos(string &dest,string &source,long pos,char compc=':');
void replace_token_string(string &token,string &str,long pos,char compc,string &nw,char repc);

#define SCROLLING_NOSELECT BIT1
#define SCROLLING_NO_WRAP BIT2
#define SCROLLING_REVERSE BIT3
void finishscrolling(long &selection,long min,long max,long jump,unsigned long flag,char littlekey);
char standardscrolling(short &selection,long min,long max,long jump,unsigned long flag=0);
char standardscrolling(long &selection,long min,long max,long jump,unsigned long flag=0);
char secondaryscrolling(short &scroll,long min,long max,long jump,unsigned long flag=0);
char secondaryscrolling(long &scroll,long min,long max,long jump,unsigned long flag=0);
#define STRINGENTRY_LETTERS BIT1
#define STRINGENTRY_SPACE BIT2
#define STRINGENTRY_NUMBERS BIT3
#define STRINGENTRY_CAPS BIT4
#define STRINGENTRY_SYMBOLS BIT5
char standardstringentry(char *str,int maxlen,unsigned long flag);
char standardstringentry(string &str,int maxlen,unsigned long flag);

void getstring_interfacechar(string &str,interfacekeyst &key);
void getstring_interfacechar_save(string &str,interfacekeyst &key);
void convertstring_interfacechar_save(string &str,interfacekeyst &key);

void process_object_lines(textlinesst &lines,string &chktype);

void drawborder(const char *str,char style=-1);