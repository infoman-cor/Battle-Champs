//some of this stuff is based on public domain code from nehe or opengl books over the years
//additions and modifications Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#define ENABLER

#if defined(__APPLE__)
#include <AGL/agl.h>
#endif

#ifndef BITS

#define BITS

#define BIT1 1
#define BIT2 2
#define BIT3 4
#define BIT4 8
#define BIT5 16
#define BIT6 32
#define BIT7 64
#define BIT8 128
#define BIT9 256
#define BIT10 512
#define BIT11 1024
#define BIT12 2048
#define BIT13 4096
#define BIT14 8192
#define BIT15 16384
#define BIT16 32768
#define BIT17 65536UL
#define BIT18 131072UL
#define BIT19 262144UL
#define BIT20 524288UL
#define BIT21 1048576UL
#define BIT22 2097152UL
#define BIT23 4194304UL
#define BIT24 8388608UL
#define BIT25 16777216UL
#define BIT26 33554432UL
#define BIT27 67108864UL
#define BIT28 134217728UL
#define BIT29 268435456UL
#define BIT30 536870912UL
#define BIT31 1073741824UL
#define BIT32 2147483648UL

#endif

#define GAME_TITLE_STRING "Battle Champs"

char get_slot_and_addbit_uchar(unsigned char &addbit,long &slot,long checkflag,long slotnum);

class pstringst
{
	public:
		string dat;
};

class stringvectst
{
	public:
		svector<pstringst *> str;

		void add_string(const string &st)
			{
			pstringst *newp=new pstringst;
				newp->dat=st;
			str.push_back(newp);
			}

		long add_unique_string(const string &st)
			{
			long i;
			for(i=(long)str.size()-1;i>=0;i--)
				{
				if(str[i]->dat==st)return i;
				}
			add_string(st);
			return (long)str.size()-1;
			}

		void add_string(const char *st)
			{
			if(st!=NULL)
				{
				pstringst *newp=new pstringst;
					newp->dat=st;
				str.push_back(newp);
				}
			}

		void insert_string(long k,const string &st)
			{
			pstringst *newp=new pstringst;
				newp->dat=st;
			if(str.size()>k)str.insert(k,newp);
			else str.push_back(newp);
			}

		~stringvectst()
			{
			clean();
			}

		void clean()
			{
			while(str.size()>0)
				{
				delete str[0];
				str.erase(0);
				}
			}

		void read_file(file_compressorst &filecomp,long loadversion)
			{
			long dummy;
			filecomp.read_file(dummy);
			str.resize(dummy);

			long s;
			for(s=0;s<dummy;s++)
				{
				str[s]=new pstringst;
				filecomp.read_file(str[s]->dat);
				}
			}
		void write_file(file_compressorst &filecomp)
			{
			long dummy=str.size();
			filecomp.write_file(dummy);

			long s;
			for(s=0;s<dummy;s++)
				{
				filecomp.write_file(str[s]->dat);
				}
			}
};

class flagarrayst
{
	public:
		flagarrayst()
			{
			slotnum=0;
			array=NULL;
			}
		~flagarrayst()
			{
			if(array!=NULL)delete[] array;
			array=NULL;
			slotnum=0;
			}

		void set_size_on_flag_num(long flagnum)
			{
			if(flagnum<=0)return;

			set_size(((flagnum-1)>>3)+1);
			}

		void set_size(long newsize)
			{
			if(newsize<=0)return;

			if(array!=NULL)delete[] array;
			array=new unsigned char[newsize];
			memset(array,0,sizeof(unsigned char)*newsize);

			slotnum=newsize;
			}

		void clear_all()
			{
			if(slotnum<=0)return;

			if(array!=NULL)memset(array,0,sizeof(unsigned char)*slotnum);
			}

		void copy_from(flagarrayst &src)
			{
			clear_all();

			if(src.slotnum>0)
				{
				set_size(src.slotnum);
				memmove(array,src.array,sizeof(unsigned char)*slotnum);
				}
			}

		bool has_flag(long checkflag)
			{
			long slot;
			unsigned char addbit;
			if(get_slot_and_addbit_uchar(addbit,slot,checkflag,slotnum))
				{
				return (array[slot]&addbit)!=0;
				}
			else return false;
			}

		void add_flag(long checkflag)
			{
			long slot;
			unsigned char addbit;
			if(get_slot_and_addbit_uchar(addbit,slot,checkflag,slotnum))
				{
				array[slot]|=addbit;
				}
			}

		void toggle_flag(long checkflag)
			{
			long slot;
			unsigned char addbit;
			if(get_slot_and_addbit_uchar(addbit,slot,checkflag,slotnum))
				{
				array[slot]^=addbit;
				}
			}

		void remove_flag(long checkflag)
			{
			long slot;
			unsigned char addbit;
			if(get_slot_and_addbit_uchar(addbit,slot,checkflag,slotnum))
				{
				array[slot]&=~addbit;
				}
			}

		void write_file(file_compressorst &filecomp)
			{
			filecomp.write_file(slotnum);
			if(slotnum>0)
				{
				long ind;
				for(ind=0;ind<slotnum;ind++)filecomp.write_file(array[ind]);
				}
			}

		void read_file(file_compressorst &filecomp,long loadversion)
			{
			long newsl;
			filecomp.read_file(newsl);
			if(newsl>0)
				{
				//AVOID UNNECESSARY DELETE/NEW
				if(array!=NULL&&slotnum!=newsl)
					{
					delete[] array;
					array=new unsigned char[newsl];
					}
				if(array==NULL)array=new unsigned char[newsl];

				long ind;
				for(ind=0;ind<newsl;ind++)filecomp.read_file(array[ind]);

				slotnum=newsl;
				}
			else if(array!=NULL)
				{
				delete[] array;
				array=NULL;
				}
			}

	private:
		unsigned char *array;
		long slotnum;
};

#ifdef ENABLER

#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_YELLOW 6
#define COLOR_WHITE	7

enum ColorData
{
	COLOR_DATA_WHITE_R,
	COLOR_DATA_WHITE_G,
	COLOR_DATA_WHITE_B,
	COLOR_DATA_RED_R,
	COLOR_DATA_RED_G,
	COLOR_DATA_RED_B,
	COLOR_DATA_GREEN_R,
	COLOR_DATA_GREEN_G,
	COLOR_DATA_GREEN_B,
	COLOR_DATA_BLUE_R,
	COLOR_DATA_BLUE_G,
	COLOR_DATA_BLUE_B,
	COLOR_DATA_YELLOW_R,
	COLOR_DATA_YELLOW_G,
	COLOR_DATA_YELLOW_B,
	COLOR_DATA_MAGENTA_R,
	COLOR_DATA_MAGENTA_G,
	COLOR_DATA_MAGENTA_B,
	COLOR_DATA_CYAN_R,
	COLOR_DATA_CYAN_G,
	COLOR_DATA_CYAN_B,
	COLOR_DATANUM
};

typedef struct {									// Structure For Keyboard Stuff
	BOOL keyDown [256];								// Holds TRUE / FALSE For Each Key
} Keys;												// Keys

typedef struct {									// Contains Information Vital To Applications
#if defined(__APPLE__)
	IBNibRef		mainNib;
#else
	HINSTANCE		hInstance;						// Application Instance
	const char*		className;						// Application ClassName
#endif
} Application;										// Application

typedef struct {									// Window Creation Info
	Application*		application;				// Application Structure
	char*				title;						// Window Title
	int					width;						// Width
	int					height;						// Height
	int					bitsPerPixel;				// Bits Per Pixel
	BOOL				isFullScreen;				// FullScreen?
} GL_WindowInit;									// GL_WindowInit

typedef struct {									// Contains Information Vital To A Window
	Keys*				keys;						// Key Structure
#if defined(__APPLE__)
	WindowRef			wnd;
	AGLContext			context;
#else
	HWND				hWnd;						// Window Handle
	HDC					hDC;						// Device Context
	HGLRC				hRC;						// Rendering Context
#endif
	GL_WindowInit		init;						// Window Init
	BOOL				isVisible;					// Window Visible?
	DWORD				lastTickCount;				// Tick Counter
} GL_Window;										// GL_Window

//THE BITMAP CLASS
#define BITMAP_ID   0x4D42    // the universal bitmap ID

class bitmap_class
{
	public:
		unsigned int gennum;
		BITMAPINFOHEADER info;
		unsigned char *data;

		bitmap_class()
			{
			gennum=0;
			data=NULL;
			}

		void clean();

		~bitmap_class();
};

#define TILEFLAG_DEAD BIT1
#define TILEFLAG_ROTATE BIT2
#define TILEFLAG_PIXRECT BIT3
#define TILEFLAG_HORFLIP BIT4
#define TILEFLAG_VERFLIP BIT5
#define TILEFLAG_LINE BIT6
#define TILEFLAG_RECT BIT7
#define TILEFLAG_BUFFER_DRAW BIT8
#define TILEFLAG_MODEL_PERSPECTIVE BIT9
#define TILEFLAG_MODEL_ORTHO BIT10
#define TILEFLAG_MODEL_TRANSLATE BIT11
#define TILEFLAG_LINE_3D BIT12

class tilest
{
	friend class texturest;
	friend class enablerst;

	public:
		long tex_pos;
		double x,y;
		unsigned long flag;
		float color_r,color_g,color_b,color_a;
		long force_gennum;
		double force_dimx;
		double force_dimy;
		double hor_stretch;
		double ver_stretch;
		char force_alpha;

		long pixmin_x,pixmax_x,pixmin_y,pixmax_y;

		double rotate_cenx,rotate_ceny;
		double rotate_angle;
	
		void render();

		tilest()
			{
			flag=0;
			hor_stretch=1;
			ver_stretch=1;
			}
};

class texture_datast
{
	friend class enablerst;
	friend class texturest;

	static texture_datast *create(short width,short height,char has_alpha_bit);

	private:
		unsigned char *data;
		char alpha_texture;
		short width,height;

		void clean_texture_data()
			{
			if(data!=NULL)
				{
				delete[] data;
				data=NULL;
				}
			width=0;
			height=0;
			}

		texture_datast(short newwidth,short newheight,char newalpha)
			{
			long bitnum=3;
			if(newalpha)bitnum=4;

			data=new unsigned char[(long)newwidth*(long)newheight*bitnum];
			memset(data,0,sizeof(unsigned char)*(long)newwidth*(long)newheight*bitnum);

			width=newwidth;
			height=newheight;
			alpha_texture=newalpha;
			}
		~texture_datast()
			{
			clean_texture_data();
			}
};

class texturest
{
	friend class enablerst;
	friend class tilest;
	friend class gridrectst;

	public:
		long id;
		string texturefile;
		long texture_data_pos;
		static texturest *create(const string &filename,char has_alpha_bit,char new_auto_alias);
		static texturest *create_from_data(long data_pos,char has_alpha_bit);

		void create_texture()
			{
			if(texture_data_pos!=-1)create_texture_from_data(texture_data_pos);
			else create_texture(texturefile,alpha_texture,auto_alias);
			}

	private:
		char alpha_texture;
		char auto_alias;
		short width,height;

		void create_texture_from_data(long data_pos);
		void create_texture(const string &filename,char has_alpha_bit,char new_auto_alias);
		void remove_texture();
		unsigned int gennum;
		unsigned int old_gennum;

		texturest(const string &filename,char has_alpha_bit,char new_auto_alias);
		texturest(long data_pos,char has_alpha_bit);
		~texturest()
			{
			remove_texture();
			}
};

class fontst
{
	friend class enablerst;
	friend class cursesrectst;

	public:
		long id;
		string fontfile;
		long lx,ly;
		long letsizex,letsizey,powsizex,powsizey;
		char var_font;
		long letwidth[256];
		static fontst *create(const string &filename,long letx,long lety,char variable);

	private:
		void create_textures(const string &filename,long letx,long lety);
		void remove_textures();
		unsigned int gennum[256];

		fontst(const string &filename,long letx,long lety,char variable);
		~fontst()
			{
			remove_textures();
			}
};

class cursesrectst
{
	friend class enablerst;

	public:
		long id;

		//FUNCTIONS
		static cursesrectst *create(long newfont_id,long newx,long newy,long newdimx,long newdimy);
		void render();
		void setcolor(short newf,short newb,char newbright);
		void usebuffer(char *newb,long buffersize);
		void locate(int x,int y);
		void addchar(char c);
		void addstring(const string str);
		void setclipping(int x1,int x2,int y1,int y2);

	private:
		//THE FONT
		unsigned int gennum[256];
		long font_id;
		float letsizex,letsizey,powsizex,powsizey;

		//THE DIMENSIONS AND POSITION
		long x,y,dimx,dimy;

		//THE BUFFER
		unsigned char *buffer_char;
		float *buffer_r;
		float *buffer_g;
		float *buffer_b;
		float *buffer_br;
		float *buffer_bg;
		float *buffer_bb;

		//THE CURRENT COLOR AND POSITION AND CLIPPING
		float r,g,b;
		float br,bg,bb;
		long cursorx,cursory;
		int clipx[2],clipy[2];

		//FUNCTIONS
		void adopt_textures(long newfont_id);
		cursesrectst(long newfont_id,long newx,long newy,long newdimx,long newdimy);
		~cursesrectst();
};

#define TRIMAX 9999

class gridrectst
{
	friend class enablerst;

	public:
		long id;

		//FUNCTIONS
		static gridrectst *create(long newdimx,long newdimy);
		void render();

		//THE DIMENSIONS
		long dimx,dimy;

		//THE BUFFER
		long *buffer_texpos;
		float *buffer_r;
		float *buffer_g;
		float *buffer_b;
		float *buffer_br;
		float *buffer_bg;
		float *buffer_bb;
		long *s_buffer_texpos;
		float *s_buffer_r;
		float *s_buffer_g;
		float *s_buffer_b;
		float *s_buffer_br;
		float *s_buffer_bg;
		float *s_buffer_bb;
		char *s_buffer_count;

		float adjx,adjy;
		long dispx,dispy;
		char black_space;

		//THREE-DIMENSIONAL DISPLAY
		float tri[TRIMAX][3];
		float tricol[TRIMAX][4];
		long trinum;
		float view_z,view_angle;

		void add_triangle(float t11,float t12,float t13,float tc1r,float tc1g,float tc1b,float tc1a,
						  float t21,float t22,float t23,float tc2r,float tc2g,float tc2b,float tc2a,
						  float t31,float t32,float t33,float tc3r,float tc3g,float tc3b,float tc3a);
		void allocate(long newdimx,long newdimy);
		void clean();

	private:
		//FUNCTIONS
		gridrectst(long newdimx,long newdimy);
		~gridrectst();
};

struct enabler_inputst
{
	long key;
	bool shift;
	bool caps;
	bool alt;
	bool ctrl;

	enabler_inputst()
		{
		key=0;
		ctrl=0;
		alt=0;
		shift=0;
		caps=0;
		}
};

class text_info_elementst
{
	public:
		virtual string get_string()
			{
			string empty;
			return empty;
			}
		virtual long get_long()
			{
			return 0;
			}

		virtual ~text_info_elementst(){}
};

class text_info_element_stringst : public text_info_elementst
{
	public:
		virtual string get_string()
			{
			return str;
			}
		text_info_element_stringst(const string &newstr)
			{
			str=newstr;
			}

	protected:
		string str;
};

class text_info_element_longst : public text_info_elementst
{
	public:
		virtual long get_long()
			{
			return val;
			}
		text_info_element_longst(long nval)
			{
			val=nval;
			}

	protected:
		long val;
};

class text_infost
{
	public:
		svector<text_info_elementst *> element;

		void clean()
			{
			while(element.size()>0)
				{
				delete element[0];
				element.erase(0);
				}
			}

		string get_string(int e)
			{
			if(e<0||e>=element.size())
				{
				string empty;
				return empty;
				}
			if(element[e]==NULL)
				{
				string empty;
				return empty;
				}
			return element[e]->get_string();
			}

		long get_long(int e)
			{
			if(e<0||e>=element.size())
				{
				return 0;
				}
			if(element[e]==NULL)
				{
				return 0;
				}
			return element[e]->get_long();
			}

		~text_infost()
			{
			clean();
			}
};

class text_system_file_infost
{
	public:
		long index;
		string filename;

		static text_system_file_infost *add_file_info(const string &newf,long newi,char newft)
			{
			return new text_system_file_infost(newf,newi,newft);
			}

		void initialize_info();
		void get_text(text_infost &text);
		void get_specific_text(text_infost &text,long num);

	protected:
		char file_token;
		long number;

		text_system_file_infost(const string &newf,long newi,char newft)
			{
			filename=newf;
			file_token=newft;
			index=newi;
			number=0;
			}
};

class text_systemst
{
	public:
		void register_file_fixed(const string &file_name,long index,char token,char initialize)
			{
			text_system_file_infost *tsfi=text_system_file_infost::add_file_info(file_name,index,token);
				if(initialize)tsfi->initialize_info();
			file_info.push_back(tsfi);
			}
		void register_file(const string &file_name,long &index,char token,char initialize)
			{
			long t;
			for(t=(long)file_info.size()-1;t>=0;t--)
				{
				if(file_info[t]->filename==file_name)
					{
					//RESET CALLING INDEX AND BAIL IF THIS FILE IS ALREADY IN THE SYSTEM
					index=file_info[t]->index;
					return;
					}
				}

			text_system_file_infost *tsfi=text_system_file_infost::add_file_info(file_name,index,token);
				if(initialize)tsfi->initialize_info();
			file_info.push_back(tsfi);
			}
		void initialize_system()
			{
			long t;
			for(t=(long)file_info.size()-1;t>=0;t--)file_info[t]->initialize_info();
			}
		void get_text(long index,text_infost &text)
			{
			long t;
			for(t=(long)file_info.size()-1;t>=0;t--)
				{
				if(file_info[t]->index==index)
					{
					file_info[t]->get_text(text);
					return;
					}
				}
			}
		void get_text(const string &file_name,text_infost &text)
			{
			long t;
			for(t=(long)file_info.size()-1;t>=0;t--)
				{
				if(file_info[t]->filename==file_name)
					{
					file_info[t]->get_text(text);
					return;
					}
				}
			}
		void get_specific_text(long index,text_infost &text,long num)
			{
			long t;
			for(t=(long)file_info.size()-1;t>=0;t--)
				{
				if(file_info[t]->index==index)
					{
					file_info[t]->get_specific_text(text,num);
					return;
					}
				}
			}

		~text_systemst()
			{
			while(file_info.size()>0)
				{
				delete file_info[0];
				file_info.erase(0);
				}
			}

	protected:
		svector<text_system_file_infost *> file_info;
};

class text_boxst
{
	public:
		stringvectst text;

		void add_paragraph(stringvectst &src,long para_width);
		void add_paragraph(const string &src,long para_width);

		void read_file(file_compressorst &filecomp,long loadversion)
			{
			text.read_file(filecomp,loadversion);
			}
		void write_file(file_compressorst &filecomp)
			{
			text.write_file(filecomp);
			}
		void clean()
			{
			text.clean();
			}
};

class curses_text_boxst
{
	public:
		stringvectst text;

		void add_paragraph(stringvectst &src,long para_width);
		void add_paragraph(const string &src,long para_width);

		void read_file(file_compressorst &filecomp,long loadversion)
			{
			text.read_file(filecomp,loadversion);
			}
		void write_file(file_compressorst &filecomp)
			{
			text.write_file(filecomp);
			}
		void clean()
			{
			text.clean();
			}
};

#define COPYTEXTUREFLAG_HORFLIP BIT1
#define COPYTEXTUREFLAG_VERFLIP BIT2

#define ENABLERFLAG_RENDER BIT1
#define ENABLERFLAG_MAXFPS BIT2

class enablerst
{
	friend class gridrectst;
	friend class cursesrectst;
	friend class fontst;
	friend class texturest;
	friend class texture_datast;
	friend class tilest;
	friend class text_boxst;

	public:
		Application			application;									// Application Structure
		GL_Window			window;											// Window Structure
		Keys				keys;											// Key Structure
		BOOL				isMessagePumpActive;							// Message Pump Active?
		MSG					msg;											// Window Message Structure

		int desired_windowed_width,desired_windowed_height;
		int desired_fullscreen_width,desired_fullscreen_height;
		unsigned long flag;
		char tracking_on;

		string command_line;


		int loop(HINSTANCE hInstance);
		enabler_inputst getinput();
		void terminate_application(GL_Window* window);
		char create_full_screen;
		char inactive_mode;
		void reshape_GL(int width,int height);
		void add_input(enabler_inputst &ninput);
		void render(GL_Window &window);
		void render_tiles();
		void graphicsinit();
		long gridrect_create(long dimx,long dimy);
		long cursesrect_create(long font_id,long x,long y,long dimx,long dimy);
		long font_create(const string &filename,long letx,long lety,char variable=0);
		long texture_data_create(short newwidth,short newheight,char has_alpha_bit);
		void texture_create_multi(const string &filename,char has_alpha_bit,long *tex_pos,long *data_pos,long ndimx,long ndimy);
		void texture_create_multi_pdim(const string &filename,char has_alpha_bit,long *tex_pos,long *data_pos,long ndimx,long ndimy,float &adjx,float &adjy,long &dispx,long &dispy);
		long texture_create(const string &filename,char has_alpha_bit,char new_auto_alias=0);
		long texture_create_from_data(long data_pos,char has_alpha_bit);
		void cursesrect_setcolor(long rect_id,short f,short b,char bright);
		void cursesrect_set_font_id(long rect_id,long nfont_id);
		void cursesrect_usebuffer(long rect_id,char *b,long buffersize);
		cursesrectst *get_rect(long rect_id);
		gridrectst *get_gridrect(long rect_id);
		fontst *get_font(long font_id);
		void toggle_fullscreen()
			{
			toggle_fullscreen(&window);
			}
		void locate(double fx,double fy,double fz=0);
		void add_perspective(float sx,float sy,float sz,
								float gx,float gy,float gz,
								float nx,float ny,float nz);
		void add_translate(float sx,float sy,float sz);
		void add_ortho();
		void add_line(double endx,double endy);
		void add_line_3D(double endx,double endy,double endz);
		void add_rect(double endx,double endy);
		void add_tile(long tex_pos,double rotate_cenx=0,double rotate_ceny=0,double rotate_angle=0,
						 long pixmin_x=-1,long pixmax_x=-1,long pixmin_y=-1,long pixmax_y=-1,
						 double hor_stretch=1,double ver_stretch=1);
		void add_gennum_tile(long gennum,double dimx,double dimy,double letx,double lety,char alpha);
		void set_color(float r,float g,float b,float a=1);
		void enable_fade(float r,float g,float b,float a,float t);
		void disable_fade();
		void set_font(long font_id)
			{
			active_font_id=font_id;
			}
		void print_string(const string &str,char centered=0,short length_lim=1000,char crammed_lets=0);
		void set_center(double newx,double newy)
			{
			center_x=newx;
			center_y=newy;
			}
		void set_clear_color(float newr,float newg,float newb,float newa)
			{
			if(fade_t==0)
				{
				clear_r=newr;clear_g=newg;clear_b=newb;clear_a=newa;
				}
			else
				{
				clear_r=newr*(1.0f-fade_t)+fade_r*fade_t;
				clear_g=newg*(1.0f-fade_t)+fade_g*fade_t;
				clear_b=newb*(1.0f-fade_t)+fade_b*fade_t;
				clear_a=newa*(1.0f-fade_t)+fade_a*fade_t;
				}
			}
		unsigned long get_timer()
			{
			if(main_qprate.QuadPart==0)return timer;
			else return qpc.QuadPart;
			}
		unsigned char *get_texture_data(long pos);
		void refresh_texture_data(long pos);
		unsigned char *load_bitmap_file(const string &filename, BITMAPINFOHEADER *bitmapInfoHeader);
		unsigned char *load_bitmap_file_with_alpha(const string &filename, BITMAPINFOHEADER *bitmapInfoHeader);
		void load_bitmap_header(const string &filename, BITMAPINFOHEADER &bitmapInfoHeader);
		void copy_texture_data(long dest,long src,long offx=0,long offy=0,
			float rmult=1,float gmult=1,float bmult=1,char use_trans=1,long *color_data=NULL,unsigned long flag=0);
		void copy_texture_data(long dest,unsigned char *src,long srcx,long srcy,char srcalpha,
			long offx=0,long offy=0,
			float rmult=1,float gmult=1,float bmult=1,char use_trans=1,long *color_data=NULL,unsigned long flag=0);
		void grayscale_texture_data(long pos);
		void antialias(unsigned char *dat,long srcx,long srcy,char border=0);
		void flip_texture_data(long pos,unsigned long flag);
		void flip_uchar_array(unsigned char *buff,long dimx,long dimy,long bytes_per_pixel,unsigned long flag);
		void get_texture_data_dims(long pos,short &width,short &height,char &alpha)
			{
			if(pos<0||pos>=texture_data.size())return;

			if(texture_data[pos]==NULL)return;

			width=texture_data[pos]->width;
			height=texture_data[pos]->height;
			alpha=texture_data[pos]->alpha_texture;
			}
		void remove_texture(long pos);
		void remove_texture_data(long pos);
		void force_texture_create(long pos)
			{
			if(pos<0||pos>=texture.size())return;

			if(texture[pos]==NULL)return;

			texture[pos]->remove_texture();
			texture[pos]->create_texture();
			}

		void read_pixels(int x,int y,int width,int height,unsigned char *buffer);

		void save_texture_data_to_bmp(long pos,string &filename);

		enablerst();
		~enablerst()
			{
			long t;
			for(t=(long)tile.size()-1;t>=0;t--)
				{
				delete tile[t];
				}
			tile.clear();
			for(t=(long)cursesrect.size()-1;t>=0;t--)
				{
				delete cursesrect[t];
				}
			cursesrect.clear();
			for(t=(long)gridrect.size()-1;t>=0;t--)
				{
				delete gridrect[t];
				}
			gridrect.clear();
			for(t=(long)font.size()-1;t>=0;t--)
				{
				delete font[t];
				}
			font.clear();
			for(t=(long)texture.size()-1;t>=0;t--)
				{
				if(texture[t]!=NULL)delete texture[t];
				}
			texture.clear();
			for(t=(long)texture_data.size()-1;t>=0;t--)
				{
				if(texture_data[t]!=NULL)delete texture_data[t];
				}
			texture_data.clear();
			}
		void enable_buffer_draw(){buffer_draw=1;}
		void disable_buffer_draw(){buffer_draw=0;}
		char doing_buffer_draw(){return buffer_draw;}

		LARGE_INTEGER qpfr;
		LARGE_INTEGER main_qprate,qprate,g_qprate;
		LARGE_INTEGER qpc,qpc2,g_qpc;
		unsigned long timer;
		unsigned long current_render_count;
		unsigned long secondary_render_count;

		long oldmouse_x,oldmouse_y,mouse_x,mouse_y;
		char mouse_lbut,mouse_rbut;
		char mouse_lbut_down,mouse_rbut_down;
		char mouse_lbut_lift,mouse_rbut_lift;

		text_systemst text_system;
		char change_screen_resolution (int width, int height, int bitsPerPixel);

		void refresh_tiles();

		float ccolor[16][3];
		int window_width,window_height;

		void clear_input()
			{
			long i;
			for(i=0;i<100;i++)input[i].key=0;
			}

		#if defined(__APPLE__)
		void do_frame();
		#endif

	private:
		svector<tilest *> tile;
		long next_tile_slot;
		long active_font_id;

		enabler_inputst input[100];
		char is_program_looping;
		svector<cursesrectst *> cursesrect;
		svector<gridrectst *> gridrect;
		svector<fontst *> font;
		svector<texturest *> texture;
		svector<texture_datast *> texture_data;
		long next_cursesrect_id;
		long next_gridrect_id;
		long next_font_id;
		long next_texture_id;
		long next_texture_data_id;
		double locx,locy,locz;
		double center_x,center_y;
		float color_r,color_g,color_b,color_a;
		float clear_r,clear_g,clear_b,clear_a;
		float fade_r,fade_g,fade_b,fade_a,fade_t;
		char buffer_draw;



		char create_window_GL (GL_Window* window);
		char destroy_window_GL (GL_Window* window);
		char register_window_class (Application* application);
		void toggle_fullscreen(GL_Window* window);
		void create_textures();
		void remove_textures()
			{
			long t;
			for(t=(long)font.size()-1;t>=0;t--)
				{
				font[t]->remove_textures();
				}
			for(t=(long)texture.size()-1;t>=0;t--)
				{
				if(texture[t]==NULL)continue;

				texture[t]->remove_texture();
				}
			}
};

void convert_to_rgb(float &r,float &g,float &b,char col,char bright);
#endif