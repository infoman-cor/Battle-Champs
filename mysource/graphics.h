//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

enum Texture
{
	TEXTURE_MOUSE,
	TEXTURENUM
};

struct tile_pagest
{
	string token;

	string filename;
	short tile_dim_x;
	short tile_dim_y;
	short page_dim_x;
	short page_dim_y;

	svector<long> texpos;
	svector<long> datapos;
	svector<long> texpos_gs;
	svector<long> datapos_gs;

	char loaded;



	tile_pagest()
		{
		loaded=0;
		}

	void load_graphics();
};

class texture_handlerst
{
	public:
		svector<tile_pagest *> page;

		svector<long> texpos;
		svector<long> datapos;

		void clean();
		void adopt_new_lines(textlinesst &lines);

		~texture_handlerst()
			{
			clean();
			}
};

#define MAX_GRID_X 200
#define MAX_GRID_Y 200

class graphicst
{
	public:
		texture_handlerst texture;

		long screenx,screeny;
		short screenf,screenb;
		char screenbright;
		long screentexpos[MAX_GRID_X][MAX_GRID_Y];
		char screentexpos_addcolor[MAX_GRID_X][MAX_GRID_Y];
		unsigned char screentexpos_grayscale[MAX_GRID_X][MAX_GRID_Y];
		unsigned char screentexpos_cf[MAX_GRID_X][MAX_GRID_Y];
		unsigned char screentexpos_cbr[MAX_GRID_X][MAX_GRID_Y];
		unsigned char screen[MAX_GRID_X][MAX_GRID_Y][4];
		long clipx[2],clipy[2];
		long tex_pos[TEXTURENUM];

		long rect_id;

		LARGE_INTEGER print_time[100];
		long print_index;
		char display_frames;

		short force_full_display_count;

		char original_rect;




		graphicst::graphicst()
			{
			print_index=0;
			display_frames=0;
			rect_id=-1;
			force_full_display_count=4;
			original_rect=1;
			}

		void locate(long y,long x);
		void changecolor(short f,short b,char bright);
		void addchar(unsigned char c,char advance=1);
		void addcoloredst(const char *str,const char *colorstr);
		void addst(const string &str);
		void addst(const char *str);
		void erasescreen_clip();
		void erasescreen();
		void renewscreen();
		void setclipping(long x1,long x2,long y1,long y2);

		void add_tile(long texp,char addcolor);
		void add_tile_grayscale(long texp,char cf,char cbr);

		void display();

		void prepare_graphics();

		void prepare_rect(char n_orig);

		void gray_out_rect(long sx,long ex,long sy,long ey)
			{
			long x,y;
			for(x=sx;x<=ex;x++)
				{
				for(y=sy;y<=ey;y++)
					{
					screen[x][y][1]=0;
					screen[x][y][2]=7;
					screen[x][y][3]=0;
					}
				}
			}
		void dim_colors(long x,long y,char dim);

		void rain_color_square(long x,long y);
		void snow_color_square(long x,long y);
		void color_square(long x,long y,unsigned char f,unsigned char b,unsigned char br);

		long border_start_x(){return 1;}
		long border_start_y(){return 1;}
		long border_end_x(){return 78;}
		long border_end_y(){return 23;}
		long text_width(){return 1;}
		long text_height(){return 1;}
		long window_element_height(long minus,char border)
			{
			long height=25;
			if(border)height-=2;
			height-=text_height()*minus;
			return height;
			}

		void get_mouse_text_coords(long &mx,long &my);

		tile_pagest *get_tile_page_by_token(string &tk)
			{
			long t;
			for(t=0;t<texture.page.size();t++)
				{
				if(texture.page[t]->token==tk)return texture.page[t];
				}
			return NULL;
			}
};