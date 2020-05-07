//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

enum InterfaceKey
{
	INTERFACEKEY_SELECT,
	INTERFACEKEY_DESELECT,
	INTERFACEKEY_SELECT_ALL,
	INTERFACEKEY_DESELECT_ALL,
	INTERFACEKEY_LEAVESCREEN,
	INTERFACEKEY_LEAVESCREEN_TEXT,
	INTERFACEKEY_LEAVESCREEN_ALL,
	INTERFACEKEY_OPTIONS,
	INTERFACEKEY_OPTION_EXPORT,
	INTERFACEKEY_HELP,
	INTERFACEKEY_TOGGLE_FULLSCREEN,
	INTERFACEKEY_MOVIES,
	INTERFACEKEY_CHANGETAB,
	INTERFACEKEY_STANDARDSCROLL_UP,
	INTERFACEKEY_STANDARDSCROLL_DOWN,
	INTERFACEKEY_STANDARDSCROLL_LEFT,
	INTERFACEKEY_STANDARDSCROLL_RIGHT,
	INTERFACEKEY_STANDARDSCROLL_PAGEUP,
	INTERFACEKEY_STANDARDSCROLL_PAGEDOWN,
	INTERFACEKEY_SECONDSCROLL_UP,
	INTERFACEKEY_SECONDSCROLL_DOWN,
	INTERFACEKEY_SECONDSCROLL_PAGEUP,
	INTERFACEKEY_SECONDSCROLL_PAGEDOWN,
	INTERFACEKEY_CURSOR_UP,
	INTERFACEKEY_CURSOR_DOWN,
	INTERFACEKEY_CURSOR_LEFT,
	INTERFACEKEY_CURSOR_RIGHT,
	INTERFACEKEY_CURSOR_UPLEFT,
	INTERFACEKEY_CURSOR_UPRIGHT,
	INTERFACEKEY_CURSOR_DOWNLEFT,
	INTERFACEKEY_CURSOR_DOWNRIGHT,
	INTERFACEKEY_CURSOR_UP_FAST,
	INTERFACEKEY_CURSOR_DOWN_FAST,
	INTERFACEKEY_CURSOR_LEFT_FAST,
	INTERFACEKEY_CURSOR_RIGHT_FAST,
	INTERFACEKEY_CURSOR_UPLEFT_FAST,
	INTERFACEKEY_CURSOR_UPRIGHT_FAST,
	INTERFACEKEY_CURSOR_DOWNLEFT_FAST,
	INTERFACEKEY_CURSOR_DOWNRIGHT_FAST,
	INTERFACEKEY_CURSOR_UP_Z,
	INTERFACEKEY_CURSOR_DOWN_Z,
	INTERFACEKEY_CURSOR_UP_Z_AUX,
	INTERFACEKEY_CURSOR_DOWN_Z_AUX,
	INTERFACEKEY_MENU_CONFIRM,
	INTERFACEKEY_SAVE_BINDINGS,
	INTERFACEKEY_CHANGE_BINDINGS,
	INTERFACEKEY_MOVIE_RECORD,
	INTERFACEKEY_MOVIE_PLAY,
	INTERFACEKEY_MOVIE_SAVE,
	INTERFACEKEY_MOVIE_LOAD,
	INTERFACEKEY_STRING_A000,
	INTERFACEKEY_STRING_A001,
	INTERFACEKEY_STRING_A002,
	INTERFACEKEY_STRING_A003,
	INTERFACEKEY_STRING_A004,
	INTERFACEKEY_STRING_A005,
	INTERFACEKEY_STRING_A006,
	INTERFACEKEY_STRING_A007,
	INTERFACEKEY_STRING_A008,
	INTERFACEKEY_STRING_A009,
	INTERFACEKEY_STRING_A010,
	INTERFACEKEY_STRING_A011,
	INTERFACEKEY_STRING_A012,
	INTERFACEKEY_STRING_A013,
	INTERFACEKEY_STRING_A014,
	INTERFACEKEY_STRING_A015,
	INTERFACEKEY_STRING_A016,
	INTERFACEKEY_STRING_A017,
	INTERFACEKEY_STRING_A018,
	INTERFACEKEY_STRING_A019,
	INTERFACEKEY_STRING_A020,
	INTERFACEKEY_STRING_A021,
	INTERFACEKEY_STRING_A022,
	INTERFACEKEY_STRING_A023,
	INTERFACEKEY_STRING_A024,
	INTERFACEKEY_STRING_A025,
	INTERFACEKEY_STRING_A026,
	INTERFACEKEY_STRING_A027,
	INTERFACEKEY_STRING_A028,
	INTERFACEKEY_STRING_A029,
	INTERFACEKEY_STRING_A030,
	INTERFACEKEY_STRING_A031,
	INTERFACEKEY_STRING_A032,
	INTERFACEKEY_STRING_A033,
	INTERFACEKEY_STRING_A034,
	INTERFACEKEY_STRING_A035,
	INTERFACEKEY_STRING_A036,
	INTERFACEKEY_STRING_A037,
	INTERFACEKEY_STRING_A038,
	INTERFACEKEY_STRING_A039,
	INTERFACEKEY_STRING_A040,
	INTERFACEKEY_STRING_A041,
	INTERFACEKEY_STRING_A042,
	INTERFACEKEY_STRING_A043,
	INTERFACEKEY_STRING_A044,
	INTERFACEKEY_STRING_A045,
	INTERFACEKEY_STRING_A046,
	INTERFACEKEY_STRING_A047,
	INTERFACEKEY_STRING_A048,
	INTERFACEKEY_STRING_A049,
	INTERFACEKEY_STRING_A050,
	INTERFACEKEY_STRING_A051,
	INTERFACEKEY_STRING_A052,
	INTERFACEKEY_STRING_A053,
	INTERFACEKEY_STRING_A054,
	INTERFACEKEY_STRING_A055,
	INTERFACEKEY_STRING_A056,
	INTERFACEKEY_STRING_A057,
	INTERFACEKEY_STRING_A058,
	INTERFACEKEY_STRING_A059,
	INTERFACEKEY_STRING_A060,
	INTERFACEKEY_STRING_A061,
	INTERFACEKEY_STRING_A062,
	INTERFACEKEY_STRING_A063,
	INTERFACEKEY_STRING_A064,
	INTERFACEKEY_STRING_A065,
	INTERFACEKEY_STRING_A066,
	INTERFACEKEY_STRING_A067,
	INTERFACEKEY_STRING_A068,
	INTERFACEKEY_STRING_A069,
	INTERFACEKEY_STRING_A070,
	INTERFACEKEY_STRING_A071,
	INTERFACEKEY_STRING_A072,
	INTERFACEKEY_STRING_A073,
	INTERFACEKEY_STRING_A074,
	INTERFACEKEY_STRING_A075,
	INTERFACEKEY_STRING_A076,
	INTERFACEKEY_STRING_A077,
	INTERFACEKEY_STRING_A078,
	INTERFACEKEY_STRING_A079,
	INTERFACEKEY_STRING_A080,
	INTERFACEKEY_STRING_A081,
	INTERFACEKEY_STRING_A082,
	INTERFACEKEY_STRING_A083,
	INTERFACEKEY_STRING_A084,
	INTERFACEKEY_STRING_A085,
	INTERFACEKEY_STRING_A086,
	INTERFACEKEY_STRING_A087,
	INTERFACEKEY_STRING_A088,
	INTERFACEKEY_STRING_A089,
	INTERFACEKEY_STRING_A090,
	INTERFACEKEY_STRING_A091,
	INTERFACEKEY_STRING_A092,
	INTERFACEKEY_STRING_A093,
	INTERFACEKEY_STRING_A094,
	INTERFACEKEY_STRING_A095,
	INTERFACEKEY_STRING_A096,
	INTERFACEKEY_STRING_A097,
	INTERFACEKEY_STRING_A098,
	INTERFACEKEY_STRING_A099,
	INTERFACEKEY_STRING_A100,
	INTERFACEKEY_STRING_A101,
	INTERFACEKEY_STRING_A102,
	INTERFACEKEY_STRING_A103,
	INTERFACEKEY_STRING_A104,
	INTERFACEKEY_STRING_A105,
	INTERFACEKEY_STRING_A106,
	INTERFACEKEY_STRING_A107,
	INTERFACEKEY_STRING_A108,
	INTERFACEKEY_STRING_A109,
	INTERFACEKEY_STRING_A110,
	INTERFACEKEY_STRING_A111,
	INTERFACEKEY_STRING_A112,
	INTERFACEKEY_STRING_A113,
	INTERFACEKEY_STRING_A114,
	INTERFACEKEY_STRING_A115,
	INTERFACEKEY_STRING_A116,
	INTERFACEKEY_STRING_A117,
	INTERFACEKEY_STRING_A118,
	INTERFACEKEY_STRING_A119,
	INTERFACEKEY_STRING_A120,
	INTERFACEKEY_STRING_A121,
	INTERFACEKEY_STRING_A122,
	INTERFACEKEY_STRING_A123,
	INTERFACEKEY_STRING_A124,
	INTERFACEKEY_STRING_A125,
	INTERFACEKEY_STRING_A126,
	INTERFACEKEY_STRING_A127,
	INTERFACEKEY_STRING_A128,
	INTERFACEKEY_STRING_A129,
	INTERFACEKEY_STRING_A130,
	INTERFACEKEY_STRING_A131,
	INTERFACEKEY_STRING_A132,
	INTERFACEKEY_STRING_A133,
	INTERFACEKEY_STRING_A134,
	INTERFACEKEY_STRING_A135,
	INTERFACEKEY_STRING_A136,
	INTERFACEKEY_STRING_A137,
	INTERFACEKEY_STRING_A138,
	INTERFACEKEY_STRING_A139,
	INTERFACEKEY_STRING_A140,
	INTERFACEKEY_STRING_A141,
	INTERFACEKEY_STRING_A142,
	INTERFACEKEY_STRING_A143,
	INTERFACEKEY_STRING_A144,
	INTERFACEKEY_STRING_A145,
	INTERFACEKEY_STRING_A146,
	INTERFACEKEY_STRING_A147,
	INTERFACEKEY_STRING_A148,
	INTERFACEKEY_STRING_A149,
	INTERFACEKEY_STRING_A150,
	INTERFACEKEY_STRING_A151,
	INTERFACEKEY_STRING_A152,
	INTERFACEKEY_STRING_A153,
	INTERFACEKEY_STRING_A154,
	INTERFACEKEY_STRING_A155,
	INTERFACEKEY_STRING_A156,
	INTERFACEKEY_STRING_A157,
	INTERFACEKEY_STRING_A158,
	INTERFACEKEY_STRING_A159,
	INTERFACEKEY_STRING_A160,
	INTERFACEKEY_STRING_A161,
	INTERFACEKEY_STRING_A162,
	INTERFACEKEY_STRING_A163,
	INTERFACEKEY_STRING_A164,
	INTERFACEKEY_STRING_A165,
	INTERFACEKEY_STRING_A166,
	INTERFACEKEY_STRING_A167,
	INTERFACEKEY_STRING_A168,
	INTERFACEKEY_STRING_A169,
	INTERFACEKEY_STRING_A170,
	INTERFACEKEY_STRING_A171,
	INTERFACEKEY_STRING_A172,
	INTERFACEKEY_STRING_A173,
	INTERFACEKEY_STRING_A174,
	INTERFACEKEY_STRING_A175,
	INTERFACEKEY_STRING_A176,
	INTERFACEKEY_STRING_A177,
	INTERFACEKEY_STRING_A178,
	INTERFACEKEY_STRING_A179,
	INTERFACEKEY_STRING_A180,
	INTERFACEKEY_STRING_A181,
	INTERFACEKEY_STRING_A182,
	INTERFACEKEY_STRING_A183,
	INTERFACEKEY_STRING_A184,
	INTERFACEKEY_STRING_A185,
	INTERFACEKEY_STRING_A186,
	INTERFACEKEY_STRING_A187,
	INTERFACEKEY_STRING_A188,
	INTERFACEKEY_STRING_A189,
	INTERFACEKEY_STRING_A190,
	INTERFACEKEY_STRING_A191,
	INTERFACEKEY_STRING_A192,
	INTERFACEKEY_STRING_A193,
	INTERFACEKEY_STRING_A194,
	INTERFACEKEY_STRING_A195,
	INTERFACEKEY_STRING_A196,
	INTERFACEKEY_STRING_A197,
	INTERFACEKEY_STRING_A198,
	INTERFACEKEY_STRING_A199,
	INTERFACEKEY_STRING_A200,
	INTERFACEKEY_STRING_A201,
	INTERFACEKEY_STRING_A202,
	INTERFACEKEY_STRING_A203,
	INTERFACEKEY_STRING_A204,
	INTERFACEKEY_STRING_A205,
	INTERFACEKEY_STRING_A206,
	INTERFACEKEY_STRING_A207,
	INTERFACEKEY_STRING_A208,
	INTERFACEKEY_STRING_A209,
	INTERFACEKEY_STRING_A210,
	INTERFACEKEY_STRING_A211,
	INTERFACEKEY_STRING_A212,
	INTERFACEKEY_STRING_A213,
	INTERFACEKEY_STRING_A214,
	INTERFACEKEY_STRING_A215,
	INTERFACEKEY_STRING_A216,
	INTERFACEKEY_STRING_A217,
	INTERFACEKEY_STRING_A218,
	INTERFACEKEY_STRING_A219,
	INTERFACEKEY_STRING_A220,
	INTERFACEKEY_STRING_A221,
	INTERFACEKEY_STRING_A222,
	INTERFACEKEY_STRING_A223,
	INTERFACEKEY_STRING_A224,
	INTERFACEKEY_STRING_A225,
	INTERFACEKEY_STRING_A226,
	INTERFACEKEY_STRING_A227,
	INTERFACEKEY_STRING_A228,
	INTERFACEKEY_STRING_A229,
	INTERFACEKEY_STRING_A230,
	INTERFACEKEY_STRING_A231,
	INTERFACEKEY_STRING_A232,
	INTERFACEKEY_STRING_A233,
	INTERFACEKEY_STRING_A234,
	INTERFACEKEY_STRING_A235,
	INTERFACEKEY_STRING_A236,
	INTERFACEKEY_STRING_A237,
	INTERFACEKEY_STRING_A238,
	INTERFACEKEY_STRING_A239,
	INTERFACEKEY_STRING_A240,
	INTERFACEKEY_STRING_A241,
	INTERFACEKEY_STRING_A242,
	INTERFACEKEY_STRING_A243,
	INTERFACEKEY_STRING_A244,
	INTERFACEKEY_STRING_A245,
	INTERFACEKEY_STRING_A246,
	INTERFACEKEY_STRING_A247,
	INTERFACEKEY_STRING_A248,
	INTERFACEKEY_STRING_A249,
	INTERFACEKEY_STRING_A250,
	INTERFACEKEY_STRING_A251,
	INTERFACEKEY_STRING_A252,
	INTERFACEKEY_STRING_A253,
	INTERFACEKEY_STRING_A254,
	INTERFACEKEY_STRING_A255,
	INTERFACEKEYNUM,
	INTERFACEKEY_NONE=-1
};

enum InterfaceBreakdownTypes
{
	INTERFACE_BREAKDOWN_NONE,
	INTERFACE_BREAKDOWN_QUIT,
	INTERFACE_BREAKDOWN_STOPSCREEN,
	INTERFACE_BREAKDOWN_TOFIRST,
	INTERFACE_BREAKDOWNNUM
};

#define MOVIEBUFFSIZE 800000
#define COMPMOVIEBUFFSIZE 1000000

class viewscreenst
{
	public:
		viewscreenst *child;
		viewscreenst *parent;
		char breakdownlevel;

		char option_key_pressed;

		virtual void view(){}

		virtual char is_legacy_screen(){return 1;}
		virtual void input(){}
		virtual void logic(){}
		virtual void render(){}

		virtual void help(){}
		virtual char movies_okay(){return 1;}
		virtual char is_option_screen(){return 0;}
		virtual char is_save_screen(){return 0;}
		virtual bool key_conflict(InterfaceKey test_key){return false;}

		viewscreenst()
			{
			child=NULL;
			parent=NULL;
			breakdownlevel=INTERFACE_BREAKDOWN_NONE;
			option_key_pressed=0;
			}
		virtual ~viewscreenst(){}
};

enum MainMenuOptionType
{
	MAINMENU_OPTION_KEYBINDINGS,
	MAINMENU_OPTION_RETURN,
	MAINMENU_OPTION_QUIT,
	MAINMENU_OPTIONNUM,
	MAINMENU_OPTION_NONE=-1
};
typedef short MainMenuOption;


class viewscreen_optionst : viewscreenst
{
	public:
		static viewscreen_optionst *create(char pushtype,viewscreenst *scr=NULL);
		virtual void view();
		virtual char is_option_screen(){return 1;}

	protected:
		long selected;

		viewscreen_optionst();
};

class viewscreen_keybindingsst : viewscreenst
{
	public:
		static viewscreen_keybindingsst *create(char pushtype,viewscreenst *scr=NULL);
		virtual void view();
		virtual char movies_okay(){return 0;}
		virtual bool key_conflict(InterfaceKey test_key);

	protected:
		svector<long> allowed_key;

		long selected;
		char binding;
		viewscreen_keybindingsst();
};

struct cursesmovie_headerst
{
	long dimx,dimy;
	long delayrate;
};

class viewscreen_movieplayerst : viewscreenst
{
	public:
		static viewscreen_movieplayerst *create(char pushtype,viewscreenst *scr=NULL);
		virtual void view();
		virtual char movies_okay(){return 0;}
		void clearfilelist();
		void force_play(string &file);

		virtual char is_option_screen(){if(is_playing)return 2;else return 0;}

	protected:
		char saving;
		char loading;
		char editing;
		char text_mode;
		unsigned char editing_char;
		long editing_copy_from;
		short editing_screenf;
		short editing_screenb;
		short editing_screenbright;
		long editing_selected_sound;
		char editing_menu;
		string savename;
		string force_file;
		char is_playing;
		char is_forced_play;
		char quit_if_no_play;
		long maxmoviepos;
		long end_frame_pos;

		long selfile;
		svector<char *> filelist;

		viewscreen_movieplayerst();
		virtual ~viewscreen_movieplayerst(){clearfilelist();};
};

class viewscreen_titlest : viewscreenst
{
	public:
		static viewscreen_titlest *create(char pushtype,viewscreenst *scr=NULL);

		virtual char is_legacy_screen(){return 0;}
		virtual void input();
		virtual void logic();
		virtual void render();

		viewscreen_titlest();
		virtual ~viewscreen_titlest();


		long selected;
		svector<long> choice;
};

class viewscreen_mapst : viewscreenst
{
	public:
		static viewscreen_mapst *create(char pushtype,viewscreenst *scr=NULL);

		virtual char is_legacy_screen(){return 0;}
		virtual void input();
		virtual void logic();
		virtual void render();

		viewscreen_mapst();
		virtual ~viewscreen_mapst();



		long selected;
		long selected_aid;
		bool moving;
		bool advance;
		long advancing_territory;
		long advance_countdown;
};

class viewscreen_fightst : viewscreenst
{
	public:
		static viewscreen_fightst *create(svector<battle_armyst *> &ba,char pushtype,viewscreenst *scr=NULL);

		svector<battle_armyst *> battle_army;
		battle_armyst *side[2];
		svector<battle_unitst *> unit;

		bool stage_fight;

		battle_unitst *tile_ptr[MAX_BATTLE_X][MAX_BATTLE_Y];
		long row_count[MAX_BATTLE_Y][2];



		virtual char is_legacy_screen(){return 0;}
		virtual void input();
		virtual void logic();
		virtual void render();

		viewscreen_fightst(svector<battle_armyst *> &ba);
		virtual ~viewscreen_fightst();
};

enum InterfacePushType
{
	INTERFACE_PUSH_AS_PARENT,
	INTERFACE_PUSH_AS_CHILD,
	INTERFACE_PUSH_AT_BACK,
	INTERFACE_PUSH_AT_FRONT,
	INTERFACE_PUSHNUM
};

struct interfacekeyst
{
	string name;
	string tokenname;
	unsigned char binding;
	long last_used_for_held;//IN WINDOWS TICKS
	short held;
	bool shift;
	bool ctrl;
	bool alt;
	
	interfacekeyst()
		{
		//SET THEM ALL TO CTRL + F10 IN CASE LOAD IS CIRCUMVENTED
		binding=VK_F10;
		last_used_for_held=0;
		held=0;
		shift=false;
		ctrl=true;
		alt=false;
		}
};

#define INTERFACEFLAG_RETAIN_NONZERO_INPUT BIT1

class interfacest
{
	friend class viewscreen_movieplayerst;

	public:
		unsigned char c;
		bool shift,caps,ctrl,alt;

		string display_string[256][8];
		

		viewscreenst view;
		unsigned long time;
		svector<unsigned char> inputbuffer;
		svector<bool> inputbuffer_shift;
		svector<bool> inputbuffer_caps;
		svector<bool> inputbuffer_ctrl;
		svector<bool> inputbuffer_alt;
		unsigned long flag;
		interfacekeyst interfacekey[INTERFACEKEYNUM];

		long shutdown_interface_tickcount;
		long shutdown_interface_for_ms;






		char loop();
		void remove_to_first();
		void removescreen(viewscreenst *scr);
		void addscreen(viewscreenst *scr,char pushtype,viewscreenst *relate);
		char is_supermovie_on()
			{
			return supermovie_on;
			}
		char keypress(short key);
		char valid_held_key(unsigned char c);

		void print_mega_announcement();

		interfacest();
		~interfacest();

	protected:
		unsigned char keyboardstate[256];
		char supermovie_on;
		long supermovie_pos;
		long supermovie_delayrate;
		long supermovie_delaystep;
		stringvectst supermovie_sound;
		long supermovie_sound_time[200][SOUND_CHANNELNUM];
		unsigned char supermoviebuffer[MOVIEBUFFSIZE];
		unsigned char supermoviebuffer_comp[COMPMOVIEBUFFSIZE];
		long currentblocksize;
		long nextfilepos;
		char first_movie_write;
		string movie_file;

		void insertscreen_as_parent(viewscreenst *scr,viewscreenst *child);
		void insertscreen_as_child(viewscreenst *scr,viewscreenst *parent);
		void insertscreen_at_back(viewscreenst *scr);
		void insertscreen_at_front(viewscreenst *scr);
		void handlemovie(char flushall);
		void finish_movie();
		void use_movie_input();

		long write_movie_chunk();
		void read_movie_chunk(long &maxmoviepos,char &is_playing);
};