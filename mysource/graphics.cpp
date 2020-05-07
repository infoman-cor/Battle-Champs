//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#include "game_g.h"
#include "game_extv.h"

#if defined(__APPLE__)
#include <OpenGL/gl.h>								// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>								// Header File For The GLu32 Library
#else
#include <GL/gl.h>								// Header File For The OpenGL32 Library
#include <GL/glu.h>								// Header File For The GLu32 Library
//#include <GL/glaux.h>							// Header File For The GLaux Library
#endif

#pragma comment( lib, "opengl32.lib" )			// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )				// Search For GLu32.lib While Linking
//#pragma comment( lib, "glaux.lib" )				// Search For GLaux.lib While Linking

void graphicst::locate(long y,long x)
{
	if(x<0||x>=init.display.grid_x||y<0||y>=init.display.grid_y)
		{
		screenx=init.display.grid_x/2;
		screeny=init.display.grid_y/2;
		return;
		}

	screenx=x;
	screeny=y;
}

void graphicst::changecolor(short f,short b,char bright)
{
	screenf=f;
	screenb=b;
	screenbright=bright;
}

void graphicst::addchar(unsigned char c,char advance)
{
	if(screenx>=clipx[0]&&screenx<=clipx[1]&&
		screeny>=clipy[0]&&screeny<=clipy[1])
		{
		screen[screenx][screeny][0]=c;
		screen[screenx][screeny][1]=screenf;
		screen[screenx][screeny][2]=screenb;
		screen[screenx][screeny][3]=screenbright;

		screentexpos[screenx][screeny]=0;
		}
	if(advance)screenx++;
}

void graphicst::addcoloredst(const char *str,const char *colorstr)
{
	int s;
	for(s=0;s<strlen(str)&&screenx<init.display.grid_x;s++)
		{
		if(screenx<0)
			{
			s-=screenx;
			screenx=0;
			if(s>=strlen(str))break;
			}

		changecolor((colorstr[s] & 7),((colorstr[s] & 56))>>3,((colorstr[s] & 64))>>6);
		addchar(str[s]);
		}
}

void graphicst::addst(const string &str)
{
	int s;
	for(s=0;s<str.length()&&screenx<init.display.grid_x;s++)
		{
		if(screenx<0)
			{
			s-=screenx;
			screenx=0;
			if(s>=str.length())break;
			}

		addchar(str[s]);
		}
}

void graphicst::addst(const char *str)
{
	int s;
	for(s=0;s<strlen(str)&&screenx<init.display.grid_x;s++)
		{
		if(screenx<0)
			{
			s-=screenx;
			screenx=0;
			if(s>=strlen(str))break;
			}

		addchar(str[s]);
		}
}

void graphicst::erasescreen_clip()
{
	changecolor(0,0,0);
	short x2,y2;
	for(x2=clipx[0];x2<=clipx[1];x2++)
		{
		for(y2=clipy[0];y2<=clipy[1];y2++)
			{
			locate(y2,x2);
			addchar(' ');
			}
		}
}

void graphicst::erasescreen()
{
	changecolor(0,0,0);
	short x2,y2;
	for(x2=0;x2<init.display.grid_x;x2++)
		{
		for(y2=0;y2<init.display.grid_y;y2++)
			{
			locate(y2,x2);
			addchar(' ');
			}
		}

	gridrectst *rect=enabler.get_gridrect(rect_id);
	if(rect!=NULL)rect->trinum=0;
}

void graphicst::display()
{
	if(display_frames && !enabler.doing_buffer_draw())
		{
		long i;
		LONGLONG total_frames=0;
		LONGLONG total_time=0;
		for(i=1;i<print_index;i++)
			{
			total_time+=print_time[i].QuadPart-print_time[i-1].QuadPart;
			total_frames++;
			}
		for(i=print_index+1;i<100;i++)
			{
			total_time+=print_time[i].QuadPart-print_time[i-1].QuadPart;
			total_frames++;
			}
		if(print_index!=0)
			{
			total_time+=print_time[0].QuadPart-print_time[99].QuadPart;
			total_frames++;
			}
		if(total_time>0&&total_frames==99)
			{
			long fps=total_frames*100*enabler.main_qprate.QuadPart/total_time;
			string str="FPS: ";
			add_long_to_string(fps,str);
			changecolor(7,3,1);
			locate(0,0);
			addst(str);
			}
		}

	enabler.refresh_tiles();

	gridrectst *rect=enabler.get_gridrect(rect_id);

	if(init.display.flag.has_flag(INIT_DISPLAY_FLAG_BLACK_SPACE))rect->black_space=1;
	else rect->black_space=0;

	long localbufsize=rect->dimx*rect->dimy;
	long d=0;

	if(enabler.create_full_screen)
		{
		rect->adjx=init.font.large_font_adjx;
		rect->adjy=init.font.large_font_adjy;
		rect->dispx=init.font.large_font_dispx;
		rect->dispy=init.font.large_font_dispy;
		}
	else
		{
		rect->adjx=init.font.small_font_adjx;
		rect->adjy=init.font.small_font_adjy;
		rect->dispx=init.font.small_font_dispx;
		rect->dispy=init.font.small_font_dispy;
		}

	long *c_buffer_texpos;
	float *c_buffer_r;
	float *c_buffer_g;
	float *c_buffer_b;
	float *c_buffer_br;
	float *c_buffer_bg;
	float *c_buffer_bb;

	short x2,y2;
	for(x2=0;x2<init.display.grid_x;x2++)
		{
		for(y2=0;y2<init.display.grid_y;y2++,d++)
			{
			if(d>=localbufsize)break;

			c_buffer_texpos=&(rect->buffer_texpos[d]);
			c_buffer_r=&(rect->buffer_r[d]);
			c_buffer_g=&(rect->buffer_g[d]);
			c_buffer_b=&(rect->buffer_b[d]);
			c_buffer_br=&(rect->buffer_br[d]);
			c_buffer_bg=&(rect->buffer_bg[d]);
			c_buffer_bb=&(rect->buffer_bb[d]);

			//CONVERT COLORS
			convert_to_rgb(*c_buffer_br,*c_buffer_bg,*c_buffer_bb,screen[x2][y2][2],0);

			if(screentexpos[x2][y2]!=0)
				{
				if(screentexpos_grayscale[x2][y2])
					{
					convert_to_rgb(*c_buffer_r,*c_buffer_g,*c_buffer_b,screentexpos_cf[x2][y2],screentexpos_cbr[x2][y2]);
					}
				else if(screentexpos_addcolor[x2][y2])
					{
					convert_to_rgb(*c_buffer_r,*c_buffer_g,*c_buffer_b,screen[x2][y2][1],screen[x2][y2][3]);
					}
				else
					{
					*c_buffer_r=1;
					*c_buffer_g=1;
					*c_buffer_b=1;
					}
				*c_buffer_texpos=screentexpos[x2][y2];
				}
			else
				{
				convert_to_rgb(*c_buffer_r,*c_buffer_g,*c_buffer_b,screen[x2][y2][1],screen[x2][y2][3]);
				if(enabler.create_full_screen)*c_buffer_texpos=init.font.large_font_texpos[screen[x2][y2][0]];
				else *c_buffer_texpos=init.font.small_font_texpos[screen[x2][y2][0]];
				}

			if(force_full_display_count==0&&init.display.flag.has_flag(INIT_DISPLAY_FLAG_PARTIAL_PRINT))
				{
				if(*c_buffer_texpos==rect->s_buffer_texpos[d]&&
					*c_buffer_r==rect->s_buffer_r[d]&&
					*c_buffer_g==rect->s_buffer_g[d]&&
					*c_buffer_b==rect->s_buffer_b[d]&&
					*c_buffer_br==rect->s_buffer_br[d]&&
					*c_buffer_bg==rect->s_buffer_bg[d]&&
					*c_buffer_bb==rect->s_buffer_bb[d])
					{
					if(rect->s_buffer_count[d]<=0)*c_buffer_texpos=-1;
					else rect->s_buffer_count[d]--;
					}
				else rect->s_buffer_count[d]=init.display.partial_print_count;
				}
			else rect->s_buffer_count[d]=0;
			}
		}

	if(force_full_display_count>0)force_full_display_count--;
}

void graphicst::renewscreen()
{
	#ifdef ENABLER
		gps.display();
		enabler.flag|=ENABLERFLAG_RENDER;
	#endif

	#ifdef CURSES
		int x2,y2;
		for(x2=0;x2<init.display.grid_x;x2++)
			{
			for(y2=0;y2<init.display.grid_y;y2++)
				{
				move(y2,x2);
				set_color(screen[x2][y2][1],screen[x2][y2][2],screen[x2][y2][3]);
				addch(screen[x2][y2][0]);
				}
			}

		refresh();
	#endif
}

void graphicst::setclipping(long x1,long x2,long y1,long y2)
{
	if(x1<0)x1=0;
	if(x2>init.display.grid_x-1)x2=init.display.grid_x-1;
	if(y1<0)y1=0;
	if(y2>init.display.grid_y-1)y2=init.display.grid_y-1;

	clipx[0]=x1;
	clipx[1]=x2;
	clipy[0]=y1;
	clipy[1]=y2;
}

void graphicst::dim_colors(long x,long y,char dim)
{
	if(x>=clipx[0]&&x<=clipx[1]&&
		y>=clipy[0]&&y<=clipy[1])
		{
		switch(dim)
			{
			case 4:
				switch(screen[x][y][2])
					{
					case 4:
					case 5:
					case 6:
						screen[x][y][2]=1;
						break;
					case 2:
					case 7:
						screen[x][y][2]=3;
						break;
					}
				switch(screen[x][y][1])
					{
					case 4:
					case 5:
					case 6:
						screen[x][y][1]=1;
						break;
					case 2:
					case 7:
						screen[x][y][1]=3;
						break;
					}
				if(screen[x][y][1]==screen[x][y][2])screen[x][y][1]=0;
				screen[x][y][3]=0;
				if(screen[x][y][1]==0&&screen[x][y][2]==0&&screen[x][y][3]==0)screen[x][y][3]=1;
				break;
			case 3:
				switch(screen[x][y][2])
					{
					case 4:
					case 5:
						screen[x][y][2]=6;
						break;
					case 2:
					case 7:
						screen[x][y][2]=3;
						break;
					}
				switch(screen[x][y][1])
					{
					case 1:
						screen[x][y][3]=0;
						break;
					case 4:
					case 5:
						screen[x][y][1]=6;
						break;
					case 2:
						screen[x][y][1]=3;
						break;
					case 7:
						screen[x][y][1]=3;
						break;
					}
				if(screen[x][y][1]!=7)screen[x][y][3]=0;
				if(screen[x][y][1]==screen[x][y][2]&&
					screen[x][y][3]==0)screen[x][y][1]=0;
				if(screen[x][y][1]==0&&screen[x][y][2]==0&&screen[x][y][3]==0)screen[x][y][3]=1;
				break;
			case 2:
				switch(screen[x][y][2])
					{
					case 4:
					case 5:
						screen[x][y][2]=6;
						break;
					}
				switch(screen[x][y][1])
					{
					case 4:
					case 5:
						screen[x][y][1]=6;
						break;
					}
				if(screen[x][y][1]!=7)screen[x][y][3]=0;
				if(screen[x][y][1]==screen[x][y][2]&&
					screen[x][y][3]==0)screen[x][y][1]=0;
				if(screen[x][y][1]==0&&screen[x][y][2]==0&&screen[x][y][3]==0)screen[x][y][3]=1;
				break;
			case 1:
				if(screen[x][y][1]!=7)screen[x][y][3]=0;
				if(screen[x][y][1]==screen[x][y][2]&&
					screen[x][y][3]==0)screen[x][y][1]=0;
				if(screen[x][y][1]==0&&screen[x][y][2]==0&&screen[x][y][3]==0)screen[x][y][3]=1;
				break;
			}
		}
}

void graphicst::rain_color_square(long x,long y)
{
	if(x>=clipx[0]&&x<=clipx[1]&&
		y>=clipy[0]&&y<=clipy[1])
		{
		screen[x][y][1]=1;
		screen[x][y][2]=0;
		screen[x][y][3]=1;
		}
}

void graphicst::snow_color_square(long x,long y)
{
	if(x>=clipx[0]&&x<=clipx[1]&&
		y>=clipy[0]&&y<=clipy[1])
		{
		screen[x][y][1]=7;
		screen[x][y][2]=0;
		screen[x][y][3]=1;
		}
}

void graphicst::color_square(long x,long y,unsigned char f,unsigned char b,unsigned char br)
{
	if(x>=clipx[0]&&x<=clipx[1]&&
		y>=clipy[0]&&y<=clipy[1])
		{
		screen[x][y][1]=f;
		screen[x][y][2]=b;
		screen[x][y][3]=br;
		}
}

void graphicst::get_mouse_text_coords(long &mx,long &my)
{
	if(enabler.tracking_on)
		{
		float dispx,dispy;
		if(enabler.create_full_screen)
			{
			dispx=init.font.large_font_dispx;
			dispy=init.font.large_font_dispy;
			}
		else
			{
			dispx=init.font.small_font_dispx;
			dispy=init.font.small_font_dispy;
			}
		float totalsizex=dispx*init.display.grid_x;
		float totalsizey=dispy*init.display.grid_y;
		float translatex=0,translatey=0;
		if(init.display.flag.has_flag(INIT_DISPLAY_FLAG_BLACK_SPACE))
			{
			if(totalsizex<=enabler.window_width)translatex=(enabler.window_width-totalsizex)/2.0f;
			if(totalsizey<=enabler.window_height)translatey=(enabler.window_height-totalsizey)/2.0f;
			}

		if(enabler.mouse_x>=translatex&&enabler.mouse_x<enabler.window_width-translatex&&
			enabler.mouse_y>=translatey&&enabler.mouse_y<enabler.window_height-translatey)
			{
			mx=(enabler.mouse_x-translatex)*init.display.grid_x/(enabler.window_width-translatex*2.0f);
			my=(enabler.mouse_y-translatey)*init.display.grid_y/(enabler.window_height-translatey*2.0f);
			}
		}
}

void graphicst::prepare_rect(char n_orig)
{
	if(rect_id!=-1)
		{
		gridrectst *gr=enabler.get_gridrect(rect_id);
		if(gr!=NULL)gr->allocate(init.display.grid_x,init.display.grid_y);
		else rect_id=-1;
		}

	if(rect_id==-1)
		{
		rect_id=enabler.gridrect_create(init.display.grid_x,init.display.grid_y);
		}

	original_rect=n_orig;

	setclipping(0,init.display.grid_x-1,0,init.display.grid_y-1);

	erasescreen();

	force_full_display_count=4;
}

void texture_handlerst::clean()
{
	long t;
	for(t=0;t<page.size();t++)delete page[t];
	page.clear();
	for(t=0;t<texpos.size();t++)enabler.remove_texture(texpos[t]);
	for(t=0;t<datapos.size();t++)enabler.remove_texture(datapos[t]);
	texpos.clear();
	datapos.clear();
}

void texture_handlerst::adopt_new_lines(textlinesst &lines)
{
	if(!init.display.flag.has_flag(INIT_DISPLAY_FLAG_USE_GRAPHICS))return;

	//NOTE: START AT 1 TO SKIP FILE NAME
	long t,pos;
	char *curstr;

	nation_defst *nd=NULL;
	tile_pagest *tp=NULL;

	for(t=1;t<lines.text.size();t++)
		{
		curstr=lines.text[t];

		for(pos=0;pos<strlen(curstr);pos++)
			{
			//SEE IF YOU ARE AT THE NEXT TOKEN
			if(curstr[pos]=='[')
				{
				string token;
				if(!grab_token_string(token,curstr,pos))continue;

				if(!token.compare("TILE_PAGE"))
					{
					string token2;
					if(!grab_token_string(token2,curstr,pos))continue;

					if(!token2.empty())
						{
						tp=new tile_pagest;
							tp->token=token2;
						gps.texture.page.push_back(tp);

						nd=NULL;
						}
					}
				else if(!token.compare("CREATURE_GRAPHICS"))
					{
					string token2;
					if(!grab_token_string(token2,curstr,pos))continue;

					if(!token2.empty())
						{
						nd=game.nation_def.get_nation_def_by_token(token2);
						tp=NULL;
						}
					}
				else if(nd!=NULL)
					{
					string token1;
					string token2;
					string token3;
					if(!grab_token_string(token1,curstr,pos))continue;
					if(!grab_token_string(token2,curstr,pos))continue;
					if(!grab_token_string(token3,curstr,pos))continue;

					long x=convert_string_to_long(token2);
					long y=convert_string_to_long(token3);

					nd->adopt_new_texture(convert_string_to_long(token),token1,x,y);
					continue;
					}
				else if(tp!=NULL)
					{
					if(!token.compare("FILE"))
						{
						string token1;
						if(!grab_token_string(token1,curstr,pos))continue;

						tp->filename=token1;
						continue;
						}

					if(!token.compare("TILE_DIM"))
						{
						string token1;
						string token2;
						if(!grab_token_string(token1,curstr,pos))continue;
						if(!grab_token_string(token2,curstr,pos))continue;

						tp->tile_dim_x=convert_string_to_long(token1);
						tp->tile_dim_y=convert_string_to_long(token2);
						continue;
						}

					if(!token.compare("PAGE_DIM"))
						{
						string token1;
						string token2;
						if(!grab_token_string(token1,curstr,pos))continue;
						if(!grab_token_string(token2,curstr,pos))continue;

						tp->page_dim_x=convert_string_to_long(token1);
						tp->page_dim_y=convert_string_to_long(token2);
						continue;
						}

					string str="Unrecognized Tile Page Token: ";
					str+=token;
					errorlog_string(str);
					}
				}
			}
		}
}

void graphicst::prepare_graphics()
{
	if(!init.display.flag.has_flag(INIT_DISPLAY_FLAG_USE_GRAPHICS))return;

	texture.clean();

	//GET READY TO LOAD
	svector<char *> processfilename;
	long f;
	textlinesst setuplines;
	char str[200];

	//LOAD THE OBJECT FILES UP INTO MEMORY
		//MUST INSURE THAT THEY ARE LOADED IN THE PROPER ORDER, IN CASE THEY REFER TO EACH OTHER
#ifdef __APPLE__
	find_files_by_pattern_with_exception("raw/graphics/graphics_*",processfilename,"text");
#else
	find_files_by_pattern_with_exception("raw/graphics/graphics_*.*",processfilename,"text");
#endif

	string chktype="GRAPHICS";
	for(f=0;f<processfilename.size();f++)
		{
		strcpy(str,"raw/graphics/");
		strcat(str,processfilename[f]);
		setuplines.load_raw_to_lines(str);
		process_object_lines(setuplines,chktype);

		delete[] processfilename[f];
		}
	processfilename.clear();
}

void tile_pagest::load_graphics()
{
	float d1,d2;long d3,d4;

	long texp[1000];
	long datap[1000];

	string fl="raw/graphics/";
	fl+=filename;
	enabler.texture_create_multi_pdim(fl,1,texp,datap,page_dim_x,page_dim_y,d1,d2,d3,d4);

	long num=page_dim_x*page_dim_y;
	texpos.resize(num);
	datapos.resize(num);
	texpos_gs.resize(num);
	datapos_gs.resize(num);
	short ds_width,ds_height;
	char ds_alpha;
	long t;
	for(t=0;t<num;t++)
		{
		texpos[t]=texp[t];
		datapos[t]=datap[t];

		//CREATE GRAY SCALE TEXTURE DATA
		enabler.get_texture_data_dims(datapos[t],ds_width,ds_height,ds_alpha);
		datapos_gs[t]=enabler.texture_data_create(ds_width,ds_height,ds_alpha);
		enabler.copy_texture_data(datapos_gs[t],datapos[t]);
		enabler.grayscale_texture_data(datapos_gs[t]);

		//CREATE GRAY SCALE TEXTURE
		texpos_gs[t]=enabler.texture_create_from_data(datapos_gs[t],1);

		//FORCE TEXTURE UPDATE
		enabler.force_texture_create(texp[t]);
		enabler.force_texture_create(texpos_gs[t]);

		//PUT THEM IN THE CLEANING VECTORS
		gps.texture.texpos.push_back(texp[t]);
		gps.texture.datapos.push_back(datap[t]);
		gps.texture.texpos.push_back(texpos_gs[t]);
		gps.texture.datapos.push_back(datapos_gs[t]);
		}

	loaded=1;
}

void graphicst::add_tile(long texp,char addcolor)
{
	if(screenx>=clipx[0]&&screenx<=clipx[1]&&
		screeny>=clipy[0]&&screeny<=clipy[1])
		{
		screentexpos[screenx][screeny]=texp;
		screentexpos_addcolor[screenx][screeny]=addcolor;
		screentexpos_grayscale[screenx][screeny]=0;
		}
}

void graphicst::add_tile_grayscale(long texp,char cf,char cbr)
{
	if(screenx>=clipx[0]&&screenx<=clipx[1]&&
		screeny>=clipy[0]&&screeny<=clipy[1])
		{
		screentexpos[screenx][screeny]=texp;
		screentexpos_addcolor[screenx][screeny]=0;
		screentexpos_grayscale[screenx][screeny]=1;
		screentexpos_cf[screenx][screeny]=cf;
		screentexpos_cbr[screenx][screeny]=cbr;
		}
}

void render_things()
{
	//CLEAR
	if(gps.force_full_display_count>0||!init.display.flag.has_flag(INIT_DISPLAY_FLAG_PARTIAL_PRINT))
	//NOTE: NEED TO CLEAR NO MATTER WHAT IN CASE THEY ARE DOING BLACKSPACE, ETC.
		{
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		}

	//SET UP MATRICES
	glMatrixMode (GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();											// Reset The Modelview Matrix
	glTranslatef(0,0,0);

	//GRAB CURRENT SCREEN AT THE END OF THE LIST
	viewscreenst *currentscreen=&gview.view;
	while(currentscreen->child!=NULL)currentscreen=currentscreen->child;

	//NO INTERFACE LEFT, LEAVE
	if(currentscreen==&gview.view)return;

	currentscreen->render();

	//DRAW EVERYTHING TO BACK BUFFER
	enabler.render_tiles();
}