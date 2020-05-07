//some of this stuff is based on public domain code from nehe or opengl books over the years
//additions and modifications Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>

//#include <vld.h>

#include "../zlib/zlib.h"

#include "resource.h"

#include "svector.h"

#include "random.h"

using std::string;

#include "basics.h"

#include <GL/gl.h>								// Header File For The OpenGL32 Library
#include <GL/glu.h>								// Header File For The GLu32 Library
//#include <GL/glaux.h>							// Header File For The GLaux Library

#pragma comment( lib, "opengl32.lib" )			// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )				// Search For GLu32.lib While Linking
//#pragma comment( lib, "glaux.lib" )				// Search For GLaux.lib While Linking

#ifndef CDS_FULLSCREEN							// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4						// Compilers. By Defining It This Way,
#endif											// We Can Avoid Errors

#define WM_TOGGLEFULLSCREEN (WM_USER+1)			// Application Define Message For Toggling

#include "endian.h"

#include "files.h"

#include "enabler.h"

#include "init.h"

extern initst init;

#ifdef ENABLER

//VSYNC STUFF (not mine)
//function pointer typdefs
typedef void (APIENTRY *PFNWGLEXTSWAPCONTROLPROC) (int);
typedef int (*PFNWGLEXTGETSWAPINTERVALPROC) (void);
 
//declare functions
PFNWGLEXTSWAPCONTROLPROC wglSwapIntervalEXT = NULL;
PFNWGLEXTGETSWAPINTERVALPROC wglGetSwapIntervalEXT = NULL;

//init VSync func
void InitVSync()
{
	//get extensions of graphics card
	char *extensions=(char *)glGetString(GL_EXTENSIONS);
  
	//is WGL_EXT_swap_control in the string? VSync switch possible?
	if(strstr(extensions,"WGL_EXT_swap_control"))
		{
		//get address's of both functions and save them
		wglSwapIntervalEXT=(PFNWGLEXTSWAPCONTROLPROC)wglGetProcAddress("wglSwapIntervalEXT");
		wglGetSwapIntervalEXT=(PFNWGLEXTGETSWAPINTERVALPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
		}
}
 
bool VSyncEnabled()
{
	if(wglGetSwapIntervalEXT==NULL)return 0;

   return(wglGetSwapIntervalEXT()>0);
}
 
void SetVSyncState(bool enable)
{
	if(wglSwapIntervalEXT!=NULL)
		{
		if(enable)wglSwapIntervalEXT(1); //set interval to 1 -> enable
		else wglSwapIntervalEXT(0); //disable
		}
}


enablerst enabler;

char beginroutine();
char mainloop();
void render_things();
void endroutine();
void ne_toggle_fullscreen();

void bitmap_class::clean()
{
	if(data!=NULL)
		{
		delete[] data;
		data=NULL;
		}
	glDeleteTextures(1,&gennum);
	gennum=0;
}

bitmap_class::~bitmap_class()
{
	clean();
}

void enablerst::add_input(enabler_inputst &ninput)
{
	long i;
	for(i=0;i<100;i++)
		{
		if(input[i].key==0)
			{
			input[i]=ninput;
			break;
			}
		}
}

enablerst::enablerst()
{
	buffer_draw=0;
	center_x=0;center_y=0;

	tracking_on=0;
	oldmouse_x=-1;oldmouse_y=-1;mouse_x=-1;mouse_y=-1;
	mouse_lbut=0;mouse_rbut=0;
	mouse_lbut_down=0;mouse_rbut_down=0;
	mouse_lbut_lift=0;mouse_rbut_lift=0;

	set_color(1,1,1);

	desired_windowed_width=640;
	desired_windowed_height=300;
	desired_fullscreen_width=640;
	desired_fullscreen_height=300;

	ccolor[0][0]=0;
	ccolor[0][1]=0;
	ccolor[0][2]=0;
	ccolor[1][0]=0;
	ccolor[1][1]=0;
	ccolor[1][2]=.5f;
	ccolor[2][0]=0;
	ccolor[2][1]=.5f;
	ccolor[2][2]=0;
	ccolor[3][0]=0;
	ccolor[3][1]=.5f;
	ccolor[3][2]=.5f;
	ccolor[4][0]=.5f;
	ccolor[4][1]=0;
	ccolor[4][2]=0;
	ccolor[5][0]=.5f;
	ccolor[5][1]=0;
	ccolor[5][2]=.5f;
	ccolor[6][0]=.5f;
	ccolor[6][1]=.5f;
	ccolor[6][2]=0;
	ccolor[7][0]=.75f;
	ccolor[7][1]=.75f;
	ccolor[7][2]=.75f;
	ccolor[8][0]=.5f;
	ccolor[8][1]=.5f;
	ccolor[8][2]=.5f;
	ccolor[9][0]=0;
	ccolor[9][1]=0;
	ccolor[9][2]=1;
	ccolor[10][0]=0;
	ccolor[10][1]=1;
	ccolor[10][2]=0;
	ccolor[11][0]=0;
	ccolor[11][1]=1;
	ccolor[11][2]=1;
	ccolor[12][0]=1;
	ccolor[12][1]=0;
	ccolor[12][2]=0;
	ccolor[13][0]=1;
	ccolor[13][1]=0;
	ccolor[13][2]=1;
	ccolor[14][0]=1;
	ccolor[14][1]=1;
	ccolor[14][2]=0;
	ccolor[15][0]=1;
	ccolor[15][1]=1;
	ccolor[15][2]=1;

	next_tile_slot=-1;

	next_gridrect_id=1;
	next_cursesrect_id=1;
	next_font_id=1;
	flag=0;
	QueryPerformanceFrequency(&qpfr);
	main_qprate.QuadPart=qpfr.QuadPart/100;
	qprate=main_qprate;
	g_qprate=main_qprate;
}

void enablerst::create_textures()
{
	long t;
	for(t=(long)font.size()-1;t>=0;t--)
		{
		font[t]->create_textures(font[t]->fontfile,font[t]->lx,font[t]->ly);
		}
	for(t=(long)texture.size()-1;t>=0;t--)
		{
		if(texture[t]==NULL)continue;

		texture[t]->create_texture();//THIS IS AN OVERLOADED FUNCTION THAT WILL HANDLE TEXTURE DATA CORRECTLY
		}
	for(t=(long)cursesrect.size()-1;t>=0;t--)
		{
		cursesrect[t]->adopt_textures(cursesrect[t]->font_id);
		}
}

int enablerst::loop(HINSTANCE hInstance)
{
	// Fill Out Application Data
	application.className = "OpenGL";									// Application Class Name
	application.hInstance = hInstance;									// Application Instance

	// Fill Out Window
	ZeroMemory (&window, sizeof (GL_Window));							// Make Sure Memory Is Zeroed
	window.keys					= &keys;								// Window Key Structure
	window.init.application		= &application;							// Window Application
	window.init.title			= GAME_TITLE_STRING;			// Window Title
	window.init.bitsPerPixel	= 32;									// Bits Per Pixel
	window.init.isFullScreen	= TRUE;									// Fullscreen? (Set To TRUE)

	ZeroMemory (&keys, sizeof (Keys));									// Zero keys Structure

	// Register A Class For Our Window To Use
	if (register_window_class (&application) == FALSE)					// Did Registering A Class Fail?
		{
		// Failure
		MessageBox (HWND_DESKTOP, "Error Registering Window Class!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return -1;														// Terminate Application
		}

	is_program_looping = TRUE;											// Program Looping Is Set To TRUE

	if(!beginroutine())is_program_looping=FALSE;

	QueryPerformanceCounter(&qpc);
	QueryPerformanceCounter(&qpc2);
	QueryPerformanceCounter(&g_qpc);

	current_render_count=0;
	secondary_render_count=0;

	while (is_program_looping)											// Loop Until WM_QUIT Is Received
		{
		// Create A Window
		window.init.isFullScreen = create_full_screen;					// Set Init Param Of Window Creation To Fullscreen?
		if (create_window_GL (&window) == TRUE)							// Was Window Creation Successful?
			{
			if(init.window.flag.has_flag(INIT_WINDOW_FLAG_VSYNC_ON))
				{
				InitVSync();
				SetVSyncState(1);
				}
			if(init.window.flag.has_flag(INIT_WINDOW_FLAG_VSYNC_OFF))
				{
				InitVSync();
				SetVSyncState(0);
				}

			// At This Point We Should Have A Window That Is Setup To Render OpenGL
			enabler.create_textures();

			// Initialize was a success
			isMessagePumpActive = TRUE;								// Set isMessagePumpActive To TRUE
			while (isMessagePumpActive == TRUE)						// While The Message Pump Is Active
				{
				// Success Creating Window.  Check For Window Messages
				if (PeekMessage (&msg, window.hWnd, 0, 0, PM_REMOVE) != 0)
					{
					// Check For WM_QUIT Message
					if (msg.message != WM_QUIT)						// Is The Message A WM_QUIT Message?
						{
						DispatchMessage (&msg);						// If Not, Dispatch The Message
						}
					else											// Otherwise (If Message Is WM_QUIT)
						{
						isMessagePumpActive = FALSE;				// Terminate The Message Pump
						}
					}
				else												// If There Are No Messages
					{
					if (window.isVisible == FALSE)					// If Window Is Not Visible
						{
						WaitMessage ();								// Application Is Minimized Wait For A Message
						}
					else											// If Window Is Visible
						{
						QueryPerformanceCounter(&qpc2);

						bool must_sleep=true;

						if(qpc.QuadPart+qprate.QuadPart<qpc2.QuadPart||(flag & ENABLERFLAG_MAXFPS))
							{
							qpc.QuadPart=qpc.QuadPart+qprate.QuadPart;
							//FALLEN 5 FRAMES BEHIND - RESYNC
							if(qpc.QuadPart+qprate.QuadPart*5<qpc2.QuadPart)qpc.QuadPart=qpc2.QuadPart-qprate.QuadPart;
							//KEEP IT SYNCHED UP IF YOU AREN'T TRACKING FOR WHEN YOU DO SWITCH BACK
								//THIS IS ESPECIALLY IMPORTANT FOR ADVENTURE MODE WHERE IT DOES SWITCHES
									//EVERY SINGLE TIME YOU PRESS A KEY
							if(flag & ENABLERFLAG_MAXFPS)qpc=qpc2;

							refresh_tiles();

							if(mainloop())
								{
								PostMessage(window.hWnd, WM_QUIT, 0, 0);	// Send A WM_QUIT Message
								is_program_looping = FALSE;					// Stop Looping Of The Program
								}

							must_sleep=false;
							}

						if(!is_program_looping)continue;

						if(g_qpc.QuadPart+g_qprate.QuadPart<qpc2.QuadPart)
							{
							g_qpc.QuadPart=g_qpc.QuadPart+g_qprate.QuadPart;
							//FALLEN 5 FRAMES BEHIND - RESYNC
							if(g_qpc.QuadPart+g_qprate.QuadPart*5<qpc2.QuadPart)g_qpc.QuadPart=qpc2.QuadPart-g_qprate.QuadPart;

							render(window);

							current_render_count++;
							secondary_render_count++;

							must_sleep=false;
							}

						if(must_sleep&&!(flag & ENABLERFLAG_MAXFPS))Sleep(1);
						}
					}
				}														// Loop While isMessagePumpActive == TRUE

			enabler.remove_textures();

			destroy_window_GL (&window);									// Destroy The Active Window
			}
		else															// If Window Creation Failed
			{
			// Error Creating Window
			MessageBox (HWND_DESKTOP, "Error Creating OpenGL Window", "Error", MB_OK | MB_ICONEXCLAMATION);
			is_program_looping = FALSE;									// Terminate The Loop
			}
		}																	// While (isProgramLooping)

	endroutine();

	UnregisterClass (application.className, application.hInstance);		// UnRegister Window Class

	return 0;
}

void enablerst::load_bitmap_header(const string &filename, BITMAPINFOHEADER &bitmapInfoHeader)
{
	FILE *filePtr;                        // the file pointer
	BITMAPFILEHEADER  bitmapFileHeader;   // bitmap file header

	// open filename in "read binary" mode
	filePtr = fopen(filename.c_str(), "rb");
	if (filePtr == NULL)return;

	// read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// verify that this is a bitmap by checking for the universal bitmap id
	if (bitmapFileHeader.bfType != BITMAP_ID)
		{
		fclose(filePtr);
		return;
		}

	// read the bitmap information header
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	bitmapInfoHeader.biSizeImage=bitmapInfoHeader.biWidth*bitmapInfoHeader.biHeight*3;

	// close the file
	fclose(filePtr);
}

//TARN: don't remember where this is from -- an OpenGL book probably
/*
 LoadBitmapFile()

 Returns a pointer to the bitmap image of the bitmap specified by filename.
 Also returns the bitmap header information. No support for 8-bit bitmaps.
*/
unsigned char *enablerst::load_bitmap_file(const string &filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
  FILE *filePtr;                        // the file pointer
  BITMAPFILEHEADER  bitmapFileHeader;   // bitmap file header
  unsigned char    *bitmapImage;        // bitmap image data
  unsigned int      imageIdx = 0;       // image index counter
  unsigned char     tempRGB;            // swap variable

  // open filename in "read binary" mode
  filePtr = fopen(filename.c_str(), "rb");
  if (filePtr == NULL)
    return NULL;

  // read the bitmap file header
  fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

  // verify that this is a bitmap by checking for the universal bitmap id
  if (bitmapFileHeader.bfType != BITMAP_ID)
  {
    fclose(filePtr);
    return NULL;
  }

  // read the bitmap information header
  fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
  bitmapInfoHeader->biSizeImage=bitmapInfoHeader->biWidth*bitmapInfoHeader->biHeight*3;

  // move file pointer to beginning of bitmap data
  fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// allocate enough memory for the bitmap image data
	if(bitmapInfoHeader->biSizeImage>0)
		{
		bitmapImage=new unsigned char[bitmapInfoHeader->biSizeImage];
		}
	else bitmapImage=NULL;

  // verify memory allocation
  if (!bitmapImage)
  {
    delete[] bitmapImage;
    fclose(filePtr);
    return NULL;
  }

  // read in the bitmap image data
  fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

  // make sure bitmap image data was read
  if (bitmapImage == NULL)
  {
    fclose(filePtr);
    return NULL;
  }

  // swap the R and B values to get RGB since the bitmap color format is in BGR
  for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3)
  {
    tempRGB = bitmapImage[imageIdx];
    bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
    bitmapImage[imageIdx + 2] = tempRGB;
  }

  // close the file and return the bitmap image data
  fclose(filePtr);
  return bitmapImage;
} // end LoadBitmapFile()


//TARN: don't remember where this is from -- an OpenGL book probably
/*
 LoadBitmapFileWithAlpha

 Loads a bitmap file normally, and then adds an alpha component to use for
 blending
*/
unsigned char *enablerst::load_bitmap_file_with_alpha(const string &filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
  unsigned char *bitmapImage = load_bitmap_file(filename, bitmapInfoHeader);

  if(bitmapImage==NULL)return NULL;

  unsigned char *bitmapWithAlpha=new unsigned char[bitmapInfoHeader->biSizeImage * 4 / 3];

  if (bitmapImage == NULL || bitmapWithAlpha == NULL)
    return NULL;

	for(unsigned int src=0,dst=0;src<bitmapInfoHeader->biSizeImage;src+=3,dst+=4)
		{
		//if the pixel is magenta, set the alpha to 0. Otherwise, set it to 255.
		if(bitmapImage[src]==255&&bitmapImage[src+1]==0&&bitmapImage[src+2]==255)
			{
			bitmapWithAlpha[dst]=0;
			bitmapWithAlpha[dst+1]=0;
			bitmapWithAlpha[dst+2]=0;
			bitmapWithAlpha[dst+3]=0;
			}
		else
			{
			bitmapWithAlpha[dst]=bitmapImage[src];
			bitmapWithAlpha[dst+1]=bitmapImage[src+1];
			bitmapWithAlpha[dst+2]=bitmapImage[src+2];
			bitmapWithAlpha[dst+3]=0xFF;
			}
		}

  delete[] bitmapImage;

  return bitmapWithAlpha;
} // end LoadBitmapFileWithAlpha()

void fontst::remove_textures()
{
	glDeleteTextures(256,gennum);
}

void texturest::remove_texture()
{
	old_gennum=gennum;
	glDeleteTextures(1,&gennum);
}

void fontst::create_textures(const string &filename,long letx,long lety)
{
	fontfile=filename;
	if(letx<=0||lety<=0)return;

	bitmap_class bmp;
		bmp.data=enabler.load_bitmap_file_with_alpha(filename,&bmp.info);

		letsizex=bmp.info.biWidth/letx;
		letsizey=bmp.info.biHeight/lety;
		powsizex=letsizex;
		powsizey=letsizey;
		int t=0;
		for(t=0;t<8;t++)
			{
			if(powsizex<=(1<<t)){powsizex=(1<<t);break;}
			}
		for(t=0;t<8;t++)
			{
			if(powsizey<=(1<<t)){powsizey=(1<<t);break;}
			}

		if(bmp.data!=NULL)
			{
			char *glyph=new char[powsizex*powsizey*4];

			memset(gennum,0,sizeof(unsigned int)*256);
			glGenTextures(256,gennum);

			int x,y,sx,sy;
			int g;
			int d;

			for(g=0;g<256;g++)
				{
				memset(glyph,0,powsizex*powsizey*4*sizeof(char));
				sx=(letx-1-(g%letx))*letsizex;
				sy=(g/letx)*letsizey;
				d=0;

				if(var_font)
					{
					letwidth[255-g]=1;
					}
				else letwidth[255-g]=letsizex;

				for(y=sy;y<sy+letsizey;y++)
					{
					for(x=sx;x<sx+letsizex;x++,d+=4)
						{
						glyph[d]=bmp.data[(x+y*bmp.info.biWidth)*4];
						glyph[d+1]=bmp.data[(x+y*bmp.info.biWidth)*4+1];
						glyph[d+2]=bmp.data[(x+y*bmp.info.biWidth)*4+2];
						glyph[d+3]=bmp.data[(x+y*bmp.info.biWidth)*4+3];
						if(glyph[d+3]!=0&&var_font&&x-sx+2>letwidth[255-g])
							{
							letwidth[255-g]=x-sx+2;
							}
						}
					d+=4*(powsizex-letsizex);
					}

				glBindTexture(GL_TEXTURE_2D,gennum[255-g]);
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,powsizex,powsizey,0,GL_RGBA,GL_UNSIGNED_BYTE,glyph);
				if(init.window.flag.has_flag(INIT_WINDOW_FLAG_TEXTURE_LINEAR))
					{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					}
				else
					{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
					}
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
				}

			//SPECIAL DISPENSATION FOR SPACE
			if(var_font)letwidth[' ']=letsizex>>1;
			else letwidth[' ']=letsizex;

			delete[] glyph;
			}
}

void texturest::create_texture_from_data(long data_pos)
{
	texture_data_pos=data_pos;
	texturefile.erase();

	if(enabler.texture_data.size()<=data_pos||data_pos==-1)return;

	texture_datast *td=enabler.texture_data[data_pos];

	if(td==NULL)return;

	width=td->width;
	height=td->height;
	alpha_texture=td->alpha_texture;

	glGenTextures(1,&gennum);
	glBindTexture(GL_TEXTURE_2D,gennum);

	if(td->alpha_texture)
		{
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,td->data);
		}
	else
		{
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,td->data);
		}

	if(init.window.flag.has_flag(INIT_WINDOW_FLAG_TEXTURE_LINEAR))
		{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		}
	else
		{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		}
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
}

void texturest::create_texture(const string &filename,char has_alpha_bit,char new_auto_alias)
{
	alpha_texture=has_alpha_bit;
	auto_alias=new_auto_alias;
	texturefile=filename;
	texture_data_pos=-1;

	bitmap_class bmp;

	if(alpha_texture)
		{
		bmp.data=enabler.load_bitmap_file_with_alpha(filename,&bmp.info);

		if(bmp.data!=NULL)
			{
			width=bmp.info.biWidth;
			height=bmp.info.biHeight;
			if(auto_alias)enabler.antialias(bmp.data,bmp.info.biWidth,bmp.info.biHeight);

			glGenTextures(1,&gennum);
			glBindTexture(GL_TEXTURE_2D,gennum);
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,bmp.info.biWidth,bmp.info.biHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,bmp.data);
			if(init.window.flag.has_flag(INIT_WINDOW_FLAG_TEXTURE_LINEAR))
				{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				}
			else
				{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
				}
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
			}
		}
	else
		{
		bmp.data=enabler.load_bitmap_file(filename,&bmp.info);

		if(bmp.data!=NULL)
			{
			width=bmp.info.biWidth;
			height=bmp.info.biHeight;

			glGenTextures(1,&gennum);
			glBindTexture(GL_TEXTURE_2D,gennum);
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,bmp.info.biWidth,bmp.info.biHeight,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.data);
			if(init.window.flag.has_flag(INIT_WINDOW_FLAG_TEXTURE_LINEAR))
				{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				}
			else
				{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
				}
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
			}
		}
}

void tilest::render()
{
	if(flag & TILEFLAG_LINE)
		{
		glDisable(GL_CULL_FACE);
		glDisable(GL_TEXTURE_2D);
		if(color_a!=1)
			{
			glEnable(GL_BLEND);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_NOTEQUAL,0);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
		else
			{
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);
			}

		glColor4f(color_r,color_g,color_b,color_a);

		glBegin(GL_LINES);
			glVertex2f(x,y);
			glVertex2f(force_dimx,force_dimy);
		glEnd();

		return;
		}

	if(flag & TILEFLAG_LINE_3D)
		{
		glDisable(GL_CULL_FACE);
		glDisable(GL_TEXTURE_2D);
		if(color_a!=1)
			{
			glEnable(GL_BLEND);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_NOTEQUAL,0);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
		else
			{
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);
			}

		glColor4f(color_r,color_g,color_b,color_a);

		glBegin(GL_LINES);
			glVertex3f(x,y,hor_stretch);
			glVertex3f(force_dimx,force_dimy,ver_stretch);
		glEnd();

		return;
		}

	if(flag & TILEFLAG_RECT)
		{
		glDisable(GL_CULL_FACE);
		glDisable(GL_TEXTURE_2D);
		if(color_a!=1)
			{
			glEnable(GL_BLEND);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_NOTEQUAL,0);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
		else
			{
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);
			}

		glColor4f(color_r,color_g,color_b,color_a);

		glBegin(GL_QUADS);
			glVertex2f(x,y);
			glVertex2f(x+force_dimx,y);
			glVertex2f(x+force_dimx,y+force_dimy);
			glVertex2f(x,y+force_dimy);
		glEnd();

		return;
		}

	long gennum;
	char alpha;
	double width,height;

	if(force_gennum>0)
		{
		gennum=force_gennum;
		alpha=force_alpha;
		width=force_dimx;
		height=force_dimy;
		}
	else
		{
		if(tex_pos<0||tex_pos>=enabler.texture.size())return;

		texturest *tx=enabler.texture[tex_pos];
		if(tx==NULL)return;
		if(tx->gennum==0)return;

		gennum=tx->gennum;
		alpha=tx->alpha_texture;
		width=tx->width;
		height=tx->height;
		}

	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	if(alpha||color_a!=1)
		{
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_NOTEQUAL,0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	else
		{
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		}

	glColor4f(color_r,color_g,color_b,color_a);
	glBindTexture(GL_TEXTURE_2D,gennum);

	float texminx=0;
	float texmaxx=1;
	float texminy=0;
	float texmaxy=1;
	if(flag & TILEFLAG_PIXRECT)
		{
		texminx=(float)pixmin_x/(float)width;
		texmaxx=(float)(pixmax_x+1)/(float)width;
		texminy=1-(float)(pixmax_y+1)/(float)height;
		texmaxy=1-(float)pixmin_y/(float)height;

		width=width*(pixmax_x-pixmin_x+1)/width;
		height=height*(pixmax_y-pixmin_y+1)/height;
		}

	if(flag & TILEFLAG_HORFLIP)
		{
		float swap=texminx;
		texminx=texmaxx;
		texmaxx=swap;
		}

	if(flag & TILEFLAG_VERFLIP)
		{
		float swap=texminy;
		texminy=texmaxy;
		texmaxy=swap;
		}

	if(hor_stretch!=1)width*=hor_stretch;
	if(ver_stretch!=1)height*=ver_stretch;

	glBegin(GL_QUADS);
		if(flag & TILEFLAG_ROTATE)
			{
			double cs,sn,cx,cy,ax,ay,nx,ny;

			cs=cos(rotate_angle);sn=sin(rotate_angle);
			cx=rotate_cenx+(double)width/2.0f;cy=rotate_ceny+(double)height/2.0f;

			glTexCoord2f(texminx,texmaxy);
			ax=x-cx;ay=y-cy;
			nx=cs*ax-sn*ay;ny=sn*ax+cs*ay;
			glVertex2f(cx+nx,cy+ny);

			glTexCoord2f(texmaxx,texmaxy);
			ax=x+(double)width-cx;ay=y-cy;
			nx=cs*ax-sn*ay;ny=sn*ax+cs*ay;
			glVertex2f(cx+nx,cy+ny);

			glTexCoord2f(texmaxx,texminy);
			ax=x+(double)width-cx;ay=y+(double)height-cy;
			nx=cs*ax-sn*ay;ny=sn*ax+cs*ay;
			glVertex2f(cx+nx,cy+ny);

			glTexCoord2f(texminx,texminy);
			ax=x-cx;ay=y+(double)height-cy;
			nx=cs*ax-sn*ay;ny=sn*ax+cs*ay;
			glVertex2f(cx+nx,cy+ny);
			}
		else
			{
			glTexCoord2f(texminx,texmaxy);
			glVertex2f(x,y);
			glTexCoord2f(texmaxx,texmaxy);
			glVertex2f(x+(double)width,y);
			glTexCoord2f(texmaxx,texminy);
			glVertex2f(x+(double)width,y+(double)height);
			glTexCoord2f(texminx,texminy);
			glVertex2f(x,y+(double)height);
			}
	glEnd();

	glDisable(GL_ALPHA_TEST);
}

void enablerst::print_string(const string &str,char centered,short length_lim,char crammed_lets)
{
	fontst *fnt=get_font(active_font_id);

	if(fnt==NULL)return;

	long s;
	long totalwidth=0;
	for(s=0;s<str.size();s++)
		{
		if(s>=length_lim)break;
		totalwidth+=fnt->letwidth[str[s]];
		if(s<(long)str.size()-1)
			{
			if(crammed_lets&&((str[s]>='A'&&str[s]<='Z')||(str[s]>='a'&&str[s]<='z'))&&
				((str[s+1]>='A'&&str[s+1]<='Z')||(str[s+1]>='a'&&str[s+1]<='z')))
				{
				totalwidth--;
				}
			}
		}

	//CENTER TEXT IF NECESSARY
	if(centered)
		{
		locx-=(totalwidth>>1);
		}

	//ADD TILES FOR EACH OF THE CHARS IN THE STRING
	for(s=0;s<str.size();s++)
		{
		if(s>=length_lim)break;
		add_gennum_tile(fnt->gennum[str[s]],fnt->powsizex,fnt->powsizey,fnt->letwidth[str[s]]-1,fnt->letsizey,1);
		locate(locx+fnt->letwidth[str[s]],locy);
		if(s<(long)str.size()-1)
			{
			if(crammed_lets&&((str[s]>='A'&&str[s]<='Z')||(str[s]>='a'&&str[s]<='z'))&&
				((str[s+1]>='A'&&str[s+1]<='Z')||(str[s+1]>='a'&&str[s+1]<='z')))
				{
				locate(locx-1,locy);
				}
			}
		}
}

void gridrectst::render()
{
	float apletsizex=dispx,apletsizey=dispy;
	float totalsizex=dispx*dimx;
	float totalsizey=dispy*dimy;
	float translatex=0,translatey=0;
	if(totalsizex>enabler.window_width||!black_space)apletsizex=(float)enabler.window_width/dimx;
	else translatex=(enabler.window_width-totalsizex)/2.0f;
	if(totalsizey>enabler.window_height||!black_space)apletsizey=(float)enabler.window_height/dimy;
	else translatey=(enabler.window_height-totalsizey)/2.0f;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(translatex,translatey,0);

	if(trinum>0)
		{
		glEnable(GL_FOG);
		glFogf(GL_FOG_START,0);
		glFogf(GL_FOG_END,1000);
		glFogf(GL_FOG_MODE,GL_LINEAR);
		float fcolor[4]={0,0,0,0};
		glFogfv(GL_FOG_COLOR,fcolor);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluPerspective(54.0f, enabler.window_width/enabler.window_height, 2.0f, 1000.0f);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		gluLookAt(115+160.0f*(float)sin(view_angle),-115-160.0f*(float)cos(view_angle),view_z,115,-115,150,0,0,1);

		glEnable(GL_DITHER);
		glShadeModel(GL_SMOOTH);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glBegin(GL_TRIANGLES);
			long t;
			for(t=0;t<trinum;t++)
				{
				glColor4fv(tricol[t]);
				glVertex3fv(tri[t]);
				}
		glEnd();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		}

	glDisable(GL_DITHER);
	glShadeModel(GL_FLAT);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	//BACKGROUND COLORS
	long tex_pos;
	float edge_l=0,edge_r=apletsizex,edge_u,edge_d;
	long px,py;
	long d=0;
	glBegin(GL_QUADS);
	for(px=0;px<dimx;px++,edge_l+=apletsizex,edge_r+=apletsizex)
		{
		edge_u=0;
		edge_d=apletsizey;
		for(py=0;py<dimy;py++,d++,edge_u+=apletsizey,edge_d+=apletsizey)
			{
			if(trinum>0)
				{
				if(py>=1&&py<=init.display.grid_y-2&&px>=init.display.grid_x-55&&px<=init.display.grid_x-26)continue;
				}

			tex_pos=buffer_texpos[d];
			if(tex_pos==-1)continue;//FOR DIRTY RECTANGLE

			glColor3f(buffer_br[d],buffer_bg[d],buffer_bb[d]);

			glVertex2f(edge_l,edge_u);
			glVertex2f(edge_r,edge_u);
			glVertex2f(edge_r,edge_d);
			glVertex2f(edge_l,edge_d);

			s_buffer_texpos[d]=buffer_texpos[d];
			s_buffer_r[d]=buffer_r[d];
			s_buffer_g[d]=buffer_g[d];
			s_buffer_b[d]=buffer_b[d];
			s_buffer_br[d]=buffer_br[d];
			s_buffer_bg[d]=buffer_bg[d];
			s_buffer_bb[d]=buffer_bb[d];
			}
		}
	glEnd();

	//FOREGROUND
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL,0);

	texturest *txt;
	d=0;
	edge_l=0;
	edge_r=apletsizex;
	for(px=0;px<dimx;px++,edge_l+=apletsizex,edge_r+=apletsizex)
		{
		edge_u=0;
		edge_d=apletsizey;
		for(py=0;py<dimy;py++,d++,edge_u+=apletsizey,edge_d+=apletsizey)
			{
			if(trinum>0)
				{
				if(py>=1&&py<=init.display.grid_y-2&&px>=init.display.grid_x-55&&px<=init.display.grid_x-26)continue;
				}

			glColor3f(buffer_r[d],buffer_g[d],buffer_b[d]);

			tex_pos=buffer_texpos[d];

			if(tex_pos<0||tex_pos>=enabler.texture.size())continue;
			txt=enabler.texture[tex_pos];
			if(txt==NULL)continue;
			if(txt->gennum==0)continue;

			glBindTexture(GL_TEXTURE_2D,txt->gennum);

			glBegin(GL_QUADS);
				glTexCoord2f(0,adjy);
				glVertex2f(edge_l,edge_u);
				glTexCoord2f(adjx,adjy);
				glVertex2f(edge_r,edge_u);
				glTexCoord2f(adjx,0);
				glVertex2f(edge_r,edge_d);
				glTexCoord2f(0,0);
				glVertex2f(edge_l,edge_d);
			glEnd();
			}
		}

	glDisable(GL_ALPHA_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void cursesrectst::render()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	//BACKGROUND COLORS
	float apletsizex=(float)enabler.window_width/dimx;
	float apletsizey=(float)enabler.window_height/dimy;

	int px,py;
	int d=0;
	for(px=0;px<dimx;px++)
		{
		for(py=0;py<dimy;py++,d++)
			{
			glColor3f(buffer_br[d],buffer_bg[d],buffer_bb[d]);

			glBegin(GL_QUADS);
				glVertex2f(px*apletsizex,py*apletsizey);
				glVertex2f((px+1)*apletsizex,py*apletsizey);
				glVertex2f((px+1)*apletsizex,(py+1)*apletsizey);
				glVertex2f(px*apletsizex,(py+1)*apletsizey);
			glEnd();
			}
		}

	//FOREGROUND
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL,0);

	d=0;

	float tx=letsizex/powsizex;
	float ty=letsizey/powsizey;

	for(px=0;px<dimx;px++)
		{
		for(py=0;py<dimy;py++,d++)
			{
			if(gennum[buffer_char[d]]==0)continue;

			glColor3f(buffer_r[d],buffer_g[d],buffer_b[d]);
			glBindTexture(GL_TEXTURE_2D,gennum[buffer_char[d]]);

			glBegin(GL_QUADS);
				glTexCoord2f(0,ty);
				glVertex2f(px*apletsizex,py*apletsizey);
				glTexCoord2f(tx,ty);
				glVertex2f((px+1)*apletsizex,py*apletsizey);
				glTexCoord2f(tx,0);
				glVertex2f((px+1)*apletsizex,(py+1)*apletsizey);
				glTexCoord2f(0,0);
				glVertex2f(px*apletsizex,(py+1)*apletsizey);
			glEnd();
			}
		}

	glDisable(GL_ALPHA_TEST);
}

void cursesrectst::setcolor(short newf,short newb,char newbright)
{
	convert_to_rgb(r,g,b,newf,newbright);
	convert_to_rgb(br,bg,bb,newb,0);
}

void convert_to_rgb(float &r,float &g,float &b,char col,char bright)
{
	short ci=col+(bright!=0)*8;
	if(ci>=0&&ci<16)
		{
		r=enabler.ccolor[ci][0];
		g=enabler.ccolor[ci][1];
		b=enabler.ccolor[ci][2];
		}
}

void cursesrectst::usebuffer(char *newb,long buffersize)
{
	long localbufsize=dimx*dimy;

	int i,bi;
	for(i=0,bi=0;bi<buffersize&&i<localbufsize;i++,bi+=4)
		{
		buffer_char[i]=newb[bi];
		convert_to_rgb(buffer_r[i],buffer_g[i],buffer_b[i],newb[bi+1],newb[bi+3]);
		convert_to_rgb(buffer_br[i],buffer_bg[i],buffer_bb[i],newb[bi+2],0);
		}
}

cursesrectst::~cursesrectst()
{
	delete[] buffer_char;
	delete[] buffer_r;
	delete[] buffer_g;
	delete[] buffer_b;
	delete[] buffer_br;
	delete[] buffer_bg;
	delete[] buffer_bb;
}

gridrectst *gridrectst::create(long dimx,long dimy)
{
	gridrectst *newrect=new gridrectst(dimx,dimy);
	return newrect;
}

gridrectst::~gridrectst()
{
	clean();
}

cursesrectst *cursesrectst::create(long font_id,long x,long y,long dimx,long dimy)
{
	cursesrectst *newrect=new cursesrectst(font_id,x,y,dimx,dimy);
	return newrect;
}

fontst *fontst::create(const string &filename,long letx,long lety,char variable)
{
	fontst *newfont=new fontst(filename,letx,lety,variable);
	return newfont;
}

texturest *texturest::create(const string &filename,char has_alpha_bit,char new_auto_alias)
{
	texturest *newtex=new texturest(filename,has_alpha_bit,new_auto_alias);
	return newtex;
}

texturest *texturest::create_from_data(long data_pos,char has_alpha_bit)
{
	texturest *newtex=new texturest(data_pos,has_alpha_bit);
	return newtex;
}

texture_datast *texture_datast::create(short width,short height,char has_alpha_bit)
{
	texture_datast *newtexd=new texture_datast(width,height,has_alpha_bit);
	return newtexd;
}

void cursesrectst::setclipping(int x1,int x2,int y1,int y2)
{
	clipx[0]=x1;
	clipx[1]=x2;
	clipy[0]=y1;
	clipy[1]=y2;
}

fontst::fontst(const string &filename,long letx,long lety,char variable)
{
	fontfile=filename;
	lx=letx;
	ly=lety;
	var_font=variable;
}

texturest::texturest(const string &filename,char has_alpha_bit,char new_auto_alias)
{
	alpha_texture=has_alpha_bit;
	auto_alias=new_auto_alias;
	texturefile=filename;
	texture_data_pos=-1;
	gennum=0;
}

texturest::texturest(long data_pos,char has_alpha_bit)
{
	alpha_texture=has_alpha_bit;
	auto_alias=0;
	texturefile.erase();
	texture_data_pos=data_pos;
	gennum=0;
}

void cursesrectst::adopt_textures(long newfont_id)
{
	font_id=newfont_id;
	fontst *font=enabler.get_font(font_id);
	if(font!=NULL)
		{
		memmove(gennum,font->gennum,sizeof(unsigned int)*256);

		letsizex=font->letsizex;
		letsizey=font->letsizey;
		powsizex=font->powsizex;
		powsizey=font->powsizey;
		}
	else memset(gennum,0,sizeof(unsigned int)*256);
}

cursesrectst::cursesrectst(long newfont_id,long newx,long newy,long newdimx,long newdimy)
{
	r=0;g=0;b=0;
	br=0;bg=0;bb=0;
	cursorx=0;cursory=0;
	setclipping(0,dimx-1,0,dimy-1);

	font_id=newfont_id;

	x=newx;
	y=newy;
	dimx=newdimx;
	dimy=newdimy;
	buffer_char=new unsigned char[dimx*dimy];
	buffer_r=new float[dimx*dimy];
	buffer_g=new float[dimx*dimy];
	buffer_b=new float[dimx*dimy];
	buffer_br=new float[dimx*dimy];
	buffer_bg=new float[dimx*dimy];
	buffer_bb=new float[dimx*dimy];
}

gridrectst::gridrectst(long newdimx,long newdimy)
{
	buffer_texpos=NULL;
	buffer_r=NULL;
	buffer_g=NULL;
	buffer_b=NULL;
	buffer_br=NULL;
	buffer_bg=NULL;
	buffer_bb=NULL;
	s_buffer_texpos=NULL;
	s_buffer_r=NULL;
	s_buffer_g=NULL;
	s_buffer_b=NULL;
	s_buffer_br=NULL;
	s_buffer_bg=NULL;
	s_buffer_bb=NULL;
	s_buffer_count=NULL;

	allocate(newdimx,newdimy);
	trinum=0;
}

void gridrectst::allocate(long newdimx,long newdimy)
{
	if(buffer_texpos==NULL||dimx!=newdimx||dimy!=newdimy)
		{
		clean();

		dimx=newdimx;
		dimy=newdimy;
		buffer_texpos=new long[dimx*dimy];
		buffer_r=new float[dimx*dimy];
		buffer_g=new float[dimx*dimy];
		buffer_b=new float[dimx*dimy];
		buffer_br=new float[dimx*dimy];
		buffer_bg=new float[dimx*dimy];
		buffer_bb=new float[dimx*dimy];
		long dm=dimx*dimy,d;
		s_buffer_texpos=new long[dimx*dimy];
		s_buffer_r=new float[dimx*dimy];
		s_buffer_g=new float[dimx*dimy];
		s_buffer_b=new float[dimx*dimy];
		s_buffer_br=new float[dimx*dimy];
		s_buffer_bg=new float[dimx*dimy];
		s_buffer_bb=new float[dimx*dimy];
		s_buffer_count=new char[dimx*dimy];
		for(d=0;d<dm;d++)
			{
			s_buffer_texpos[d]=-1;
			s_buffer_count[d]=0;
			}
		}
}

void gridrectst::clean()
{
	if(buffer_texpos!=NULL)delete[] buffer_texpos;
	if(buffer_r!=NULL)delete[] buffer_r;
	if(buffer_g!=NULL)delete[] buffer_g;
	if(buffer_b!=NULL)delete[] buffer_b;
	if(buffer_br!=NULL)delete[] buffer_br;
	if(buffer_bg!=NULL)delete[] buffer_bg;
	if(buffer_bb!=NULL)delete[] buffer_bb;
	if(s_buffer_texpos!=NULL)delete[] s_buffer_texpos;
	if(s_buffer_r!=NULL)delete[] s_buffer_r;
	if(s_buffer_g!=NULL)delete[] s_buffer_g;
	if(s_buffer_b!=NULL)delete[] s_buffer_b;
	if(s_buffer_br!=NULL)delete[] s_buffer_br;
	if(s_buffer_bg!=NULL)delete[] s_buffer_bg;
	if(s_buffer_bb!=NULL)delete[] s_buffer_bb;
	if(s_buffer_count!=NULL)delete[] s_buffer_count;
	buffer_texpos=NULL;
	buffer_r=NULL;
	buffer_g=NULL;
	buffer_b=NULL;
	buffer_br=NULL;
	buffer_bg=NULL;
	buffer_bb=NULL;
	s_buffer_texpos=NULL;
	s_buffer_r=NULL;
	s_buffer_g=NULL;
	s_buffer_b=NULL;
	s_buffer_br=NULL;
	s_buffer_bg=NULL;
	s_buffer_bb=NULL;
	s_buffer_count=NULL;
}

long enablerst::gridrect_create(long dimx,long dimy)
{
	gridrectst *rect=gridrectst::create(dimx,dimy);
		rect->id=next_gridrect_id;next_gridrect_id++;
	gridrect.push_back(rect);

	return rect->id;
}

long enablerst::cursesrect_create(long font_id,long x,long y,long dimx,long dimy)
{
	cursesrectst *rect=cursesrectst::create(font_id,x,y,dimx,dimy);
		rect->id=next_cursesrect_id;next_cursesrect_id++;
	cursesrect.push_back(rect);

	return rect->id;
}

long enablerst::font_create(const string &filename,long letx,long lety,char variable)
{
	fontst *nfont=fontst::create(filename,letx,lety,variable);
		nfont->id=next_font_id;next_font_id++;
	font.push_back(nfont);

	return nfont->id;
}

long enablerst::texture_data_create(short newwidth,short newheight,char has_alpha_bit)
{
	texture_datast *ntexd=texture_datast::create(newwidth,newheight,has_alpha_bit);

	long slot;
	for(slot=(long)texture_data.size()-1;slot>=0;slot--)
		{
		if(texture_data[slot]==NULL)
			{
			texture_data[slot]=ntexd;
			return slot;
			}
		}

	texture_data.push_back(ntexd);
	return (long)texture_data.size()-1;
}

long enablerst::texture_create(const string &filename,char has_alpha_bit,char new_auto_alias)
{
	texturest *ntex=texturest::create(filename,has_alpha_bit,new_auto_alias);

	long slot;
	for(slot=(long)texture.size()-1;slot>=0;slot--)
		{
		if(texture[slot]==NULL)
			{
			texture[slot]=ntex;
			return slot;
			}
		}

	texture.push_back(ntex);
	return (long)texture.size()-1;
}

void enablerst::texture_create_multi_pdim(const string &filename,char has_alpha_bit,long *tex_pos,long *data_pos,long picx,long picy,
										  float &adjx,float &adjy,long &dispx,long &dispy)
{
	if(picx<=0||picy<=0)return;

	bitmap_class bmp;

	if(has_alpha_bit)bmp.data=enabler.load_bitmap_file_with_alpha(filename,&bmp.info);
	else bmp.data=enabler.load_bitmap_file(filename,&bmp.info);

	if(bmp.data!=NULL)
		{
		long sx,sy;
		long ndimx=bmp.info.biWidth/picx;
		long ndimy=bmp.info.biHeight/picy;
		dispx=ndimx;
		dispy=ndimy;
		long ind=0;
		long powsizex=ndimx;
		long powsizey=ndimy;
		int t=0;
		for(t=0;t<8;t++)
			{
			if(powsizex<=(1<<t)){powsizex=(1<<t);break;}
			}
		for(t=0;t<8;t++)
			{
			if(powsizey<=(1<<t)){powsizey=(1<<t);break;}
			}

		adjx=(float)ndimx/(float)powsizex;
		adjy=(float)ndimy/(float)powsizey;

		for(sy=0;sy<picy;sy++)
			{
			for(sx=0;sx<picx;sx++)
				{
				//MAKE DATA
				data_pos[ind]=texture_data_create(powsizex,powsizey,has_alpha_bit);
				long dp=data_pos[ind];
				unsigned char *buff=texture_data[dp]->data;

				long bitnum=3;
				if(has_alpha_bit)bitnum=4;

				long dind=(picy-sy-1)*ndimy*bmp.info.biWidth*bitnum+sx*ndimx*bitnum,dind2=0;
				long dx,dy;
				for(dy=ndimy-1;dy>=0;dy--)
					{
					for(dx=0;dx<ndimx;dx++)
						{
						buff[dind2]=bmp.data[dind];
						buff[dind2+1]=bmp.data[dind+1];
						buff[dind2+2]=bmp.data[dind+2];
						if(bitnum==4)buff[dind2+3]=bmp.data[dind+3];
						dind+=bitnum;
						dind2+=bitnum;
						}
					dind2+=bitnum*(powsizex-ndimx);
					dind+=bmp.info.biWidth*bitnum-ndimx*bitnum;
					}

				//MAKE TEXTURE
				tex_pos[ind]=texture_create_from_data(data_pos[ind],has_alpha_bit);
				ind++;
				}
			}
		}
}

void enablerst::texture_create_multi(const string &filename,char has_alpha_bit,long *tex_pos,long *data_pos,long ndimx,long ndimy)
{
	if(ndimx<=0||ndimy<=0)return;

	bitmap_class bmp;

	if(has_alpha_bit)bmp.data=enabler.load_bitmap_file_with_alpha(filename,&bmp.info);
	else bmp.data=enabler.load_bitmap_file(filename,&bmp.info);

	if(bmp.data!=NULL)
		{
		long sx,sy;
		long picx=bmp.info.biWidth/ndimx;
		long picy=bmp.info.biHeight/ndimy;
		long ind=0;
		for(sx=0;sx<picx;sx++)
			{
			for(sy=0;sy<picy;sy++)
				{
				//MAKE DATA
				data_pos[ind]=texture_data_create(ndimx,ndimy,has_alpha_bit);
				long dp=data_pos[ind];
				unsigned char *buff=texture_data[dp]->data;

				long bitnum=3;
				if(has_alpha_bit)bitnum=4;

				long dind=(picy-sy-1)*ndimy*bmp.info.biWidth*bitnum+sx*ndimx*bitnum,dind2=0;
				long dx,dy;
				for(dy=ndimy-1;dy>=0;dy--)
					{
					for(dx=0;dx<ndimx;dx++)
						{
						buff[dind2]=bmp.data[dind];
						buff[dind2+1]=bmp.data[dind+1];
						buff[dind2+2]=bmp.data[dind+2];
						if(bitnum==4)buff[dind2+3]=bmp.data[dind+3];
						dind+=bitnum;
						dind2+=bitnum;
						}
					dind+=bmp.info.biWidth*bitnum-ndimx*bitnum;
					}

				//MAKE TEXTURE
				tex_pos[ind]=texture_create_from_data(data_pos[ind],has_alpha_bit);
				ind++;
				}
			}
		}
}

long enablerst::texture_create_from_data(long data_pos,char has_alpha_bit)
{
	texturest *ntex=texturest::create_from_data(data_pos,has_alpha_bit);

	long slot;
	for(slot=(long)texture.size()-1;slot>=0;slot--)
		{
		if(texture[slot]==NULL)
			{
			texture[slot]=ntex;
			return slot;
			}
		}

	texture.push_back(ntex);
	return (long)texture.size()-1;
}

void cursesrectst::locate(int x,int y)
{
	cursorx=x;
	cursory=y;
}

void cursesrectst::addchar(char c)
{
	if(cursorx>=clipx[0]&&cursorx<=clipx[1]&&
		cursory>=clipy[0]&&cursory<=clipy[1])
		{
		int index=cursory+dimy*cursorx;
		buffer_char[index]=c;
		buffer_r[index]=r;
		buffer_g[index]=g;
		buffer_b[index]=b;
		buffer_br[index]=br;
		buffer_bg[index]=bg;
		buffer_bb[index]=bb;
		}
	cursorx++;
}

void cursesrectst::addstring(const string str)
{
	int s;
	for(s=0;s<str.length()&&cursorx<dimx;s++)
		{
		if(cursorx<0)
			{
			s-=cursorx;
			cursorx=0;
			if(s>=str.length())break;
			}

		addchar(str[s]);
		}
}

gridrectst *enablerst::get_gridrect(long rect_id)
{
	int r;
	for(r=0;r<gridrect.size();r++)
		{
		if(gridrect[r]->id==rect_id)return gridrect[r];
		}

	return NULL;
}

cursesrectst *enablerst::get_rect(long rect_id)
{
	int r;
	for(r=0;r<cursesrect.size();r++)
		{
		if(cursesrect[r]->id==rect_id)return cursesrect[r];
		}

	return NULL;
}

fontst *enablerst::get_font(long font_id)
{
	int r;
	for(r=0;r<font.size();r++)
		{
		if(font[r]->id==font_id)return font[r];
		}

	return NULL;
}

void enablerst::set_color(float r,float g,float b,float a)
{
	if(fade_t==0)
		{
		color_r=r;color_g=g;color_b=b;color_a=a;
		}
	else
		{
		color_r=r*(1.0f-fade_t)+fade_r*fade_t;
		color_g=g*(1.0f-fade_t)+fade_g*fade_t;
		color_b=b*(1.0f-fade_t)+fade_b*fade_t;
		color_a=a*(1.0f-fade_t)+fade_a*fade_t;
		}
}

void enablerst::cursesrect_set_font_id(long rect_id,long nfont_id)
{
	if(rect_id==0)return;

	cursesrectst *rect=get_rect(rect_id);

	if(rect!=NULL)
		{
		rect->font_id=nfont_id;
		}
}

void enablerst::cursesrect_setcolor(long rect_id,short f,short b,char bright)
{
	if(rect_id==0)return;

	cursesrectst *rect=get_rect(rect_id);

	if(rect!=NULL)
		{
		rect->setcolor(f,b,bright);
		}
}

void enablerst::cursesrect_usebuffer(long rect_id,char *b,long buffersize)
{
	if(rect_id==0)return;

	cursesrectst *rect=get_rect(rect_id);

	if(rect!=NULL)
		{
		rect->usebuffer(b,buffersize);
		}
}

void enablerst::locate(double fx,double fy,double fz)
{
	locx=fx;
	locy=fy;
	locz=fz;
}

void enablerst::add_line(double endx,double endy)
{
	tilest *newt;
	if(next_tile_slot==-1)
		{
		newt=new tilest;
		tile.push_back(newt);
		}
	else
		{
		newt=tile[next_tile_slot];

		next_tile_slot++;
		if(next_tile_slot>=tile.size())next_tile_slot=-1;
		}

	newt->flag=0;
	newt->x=locx;newt->y=locy;
	newt->force_dimx=endx;
	newt->force_dimy=endy;
	newt->flag|=TILEFLAG_LINE;
	newt->color_r=color_r;
	newt->color_g=color_g;
	newt->color_b=color_b;
	newt->color_a=color_a;
	if(buffer_draw)newt->flag|=TILEFLAG_BUFFER_DRAW;

	locx=endx;
	locy=endy;
}

void enablerst::add_line_3D(double endx,double endy,double endz)
{
	tilest *newt;
	if(next_tile_slot==-1)
		{
		newt=new tilest;
		tile.push_back(newt);
		}
	else
		{
		newt=tile[next_tile_slot];

		next_tile_slot++;
		if(next_tile_slot>=tile.size())next_tile_slot=-1;
		}

	newt->flag=0;
	newt->x=locx;newt->y=locy;newt->hor_stretch=locz;
	newt->force_dimx=endx;
	newt->force_dimy=endy;
	newt->ver_stretch=endz;
	newt->flag|=TILEFLAG_LINE_3D;
	newt->color_r=color_r;
	newt->color_g=color_g;
	newt->color_b=color_b;
	newt->color_a=color_a;
	if(buffer_draw)newt->flag|=TILEFLAG_BUFFER_DRAW;

	locx=endx;
	locy=endy;
	locz=endz;
}

void enablerst::add_rect(double endx,double endy)
{
	tilest *newt;
	if(next_tile_slot==-1)
		{
		newt=new tilest;
		tile.push_back(newt);
		}
	else
		{
		newt=tile[next_tile_slot];

		next_tile_slot++;
		if(next_tile_slot>=tile.size())next_tile_slot=-1;
		}

	newt->flag=0;
	newt->hor_stretch=1;
	newt->ver_stretch=1;
	newt->x=locx;newt->y=locy;
	newt->force_dimx=endx;
	newt->force_dimy=endy;
	newt->flag|=TILEFLAG_RECT;
	newt->color_r=color_r;
	newt->color_g=color_g;
	newt->color_b=color_b;
	newt->color_a=color_a;
	if(buffer_draw)newt->flag|=TILEFLAG_BUFFER_DRAW;
}

void enablerst::add_tile(long tex_pos,double rotate_cenx,double rotate_ceny,double rotate_angle,
						 long pixmin_x,long pixmax_x,long pixmin_y,long pixmax_y,
						 double hor_stretch,double ver_stretch)
{
	tilest *newt;
	if(next_tile_slot==-1)
		{
		newt=new tilest;
		tile.push_back(newt);
		}
	else
		{
		newt=tile[next_tile_slot];

		next_tile_slot++;
		if(next_tile_slot>=tile.size())next_tile_slot=-1;
		}

	newt->tex_pos=tex_pos;
	newt->x=locx;newt->y=locy;
	newt->color_r=color_r;
	newt->color_g=color_g;
	newt->color_b=color_b;
	newt->color_a=color_a;
	newt->flag=0;
	newt->force_gennum=-1;
	newt->force_dimx=0;
	newt->force_dimy=0;
	newt->force_alpha=0;
	if(pixmin_x!=-1)
		{
		newt->pixmin_x=pixmin_x;
		newt->pixmax_x=pixmax_x;
		newt->pixmin_y=pixmin_y;
		newt->pixmax_y=pixmax_y;
		newt->flag|=TILEFLAG_PIXRECT;
		}
	if(rotate_angle!=0)
		{
		newt->rotate_cenx=locx+rotate_cenx;
		newt->rotate_ceny=locy+rotate_ceny;
		newt->rotate_angle=rotate_angle;
		newt->flag|=TILEFLAG_ROTATE;
		}
	if(hor_stretch<0)
		{
		newt->flag|=TILEFLAG_HORFLIP;
		newt->hor_stretch=hor_stretch*-1;
		}
	else newt->hor_stretch=hor_stretch;
	if(ver_stretch<0)
		{
		newt->flag|=TILEFLAG_VERFLIP;
		newt->ver_stretch=ver_stretch*-1;
		}
	else newt->ver_stretch=ver_stretch;
	if(buffer_draw)newt->flag|=TILEFLAG_BUFFER_DRAW;
}

void enablerst::add_gennum_tile(long gennum,double dimx,double dimy,double letx,double lety,char alpha)
{
	tilest *newt;
	if(next_tile_slot==-1)
		{
		newt=new tilest;
		tile.push_back(newt);
		}
	else
		{
		newt=tile[next_tile_slot];

		next_tile_slot++;
		if(next_tile_slot>=tile.size())next_tile_slot=-1;
		}

	newt->tex_pos=-1;
	newt->x=locx;
	newt->y=locy+(dimy-lety);
	newt->flag=0;
	newt->color_r=color_r;
	newt->color_g=color_g;
	newt->color_b=color_b;
	newt->color_a=color_a;
	newt->force_gennum=gennum;
	newt->force_dimx=dimx;
	newt->force_dimy=dimy;

	newt->pixmin_x=0;
	newt->pixmax_x=letx;
	newt->pixmin_y=dimy-lety;
	newt->pixmax_y=dimy;
	newt->flag|=TILEFLAG_PIXRECT;

	newt->force_alpha=alpha;
	newt->hor_stretch=1;
	newt->ver_stretch=1;
	if(buffer_draw)newt->flag|=TILEFLAG_BUFFER_DRAW;
}

void enablerst::render_tiles()
{
	//SET UP MATRICES
	glMatrixMode (GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();											// Reset The Modelview Matrix
	glTranslatef(-center_x,-center_y,0);

	//DRAW EVERYTHING
	int r;
	for(r=0;r<gridrect.size();r++)
		{
		gridrect[r]->render();
		}

	for(r=0;r<cursesrect.size();r++)
		{
		cursesrect[r]->render();
		}

	int t;
	for(t=0;t<tile.size();t++)
		{
		if(!(tile[t]->flag & TILEFLAG_BUFFER_DRAW)&&buffer_draw)continue;
		if((tile[t]->flag & TILEFLAG_BUFFER_DRAW)&&!buffer_draw)continue;

		if(tile[t]->flag & TILEFLAG_MODEL_TRANSLATE)
			{
			glTranslatef(tile[t]->color_r,tile[t]->color_g,tile[t]->color_b);
			continue;
			}

		if(tile[t]->flag & TILEFLAG_MODEL_PERSPECTIVE)
			{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(54.0f, 640.0f/300.0f, 2.0f, 1000.0f);
			glMatrixMode (GL_MODELVIEW);								// Select The Modelview Matrix
			glLoadIdentity ();											// Reset The Modelview Matrix
			gluLookAt(tile[t]->color_r,tile[t]->color_g,tile[t]->color_b,
				tile[t]->x,tile[t]->y,tile[t]->hor_stretch,
				tile[t]->force_dimx,tile[t]->force_dimy,tile[t]->ver_stretch);
			continue;
			}

		if(tile[t]->flag & TILEFLAG_MODEL_ORTHO)
			{
			glMatrixMode (GL_PROJECTION);								// Select The Projection Matrix
			glLoadIdentity ();											// Reset The Projection Matrix
			glOrtho(0.0f, 640, 300, 0, -1.0, 1.0);
			glMatrixMode (GL_MODELVIEW);								// Select The Modelview Matrix
			glLoadIdentity ();											// Reset The Modelview Matrix
			continue;
			}

		if(!(tile[t]->flag & TILEFLAG_DEAD))
			{
			tile[t]->render();
			tile[t]->flag|=TILEFLAG_DEAD;
			}
		}

	//RESET THE NEXT SLOT
	if(!buffer_draw)
		{
		if(tile.size()>0)next_tile_slot=0;
		else next_tile_slot=-1;
		}
}

#ifdef CHOPPY
char var=0;
#endif

void enablerst::render(GL_Window &window)
{
	#ifdef CHOPPY
	var=(var+1)%8;
	if(var%8!=0)
		{
		int t;
		for(t=0;t<tile.size();t++)
			{
			if(!(tile[t]->flag & TILEFLAG_DEAD))
				{
				tile[t]->flag|=TILEFLAG_DEAD;
				}
			}

		//RESET THE NEXT SLOT
		if(!buffer_draw)
			{
			if(tile.size()>0)next_tile_slot=0;
			else next_tile_slot=-1;
			}

		flag&=~ENABLERFLAG_RENDER;
		return;
		}
	#endif

	if(flag & ENABLERFLAG_RENDER)
		{
		//DO THE APP SPECIFIC DISPLAY STUFF
		render_things();

		//DO BUFFERS
		SwapBuffers(window.hDC);

		//DON'T PRINT AGAIN UNTIL ASKED
		flag&=~ENABLERFLAG_RENDER;
		}
}

enabler_inputst enablerst::getinput()
{
	if(input[0].key!=0)
		{
		enabler_inputst ret=input[0];

		long i;
		for(i=1;i<100;i++)
			{
			input[i-1]=input[i];
			}
		input[99].key=0;

		return ret;
		}

	enabler_inputst ret;
		ret.key=0;
	return ret;
}

void enablerst::terminate_application(GL_Window* window)
{
	PostMessage(window->hWnd, WM_QUIT, 0, 0);	// Send A WM_QUIT Message
	is_program_looping = FALSE;					// Stop Looping Of The Program
}

void enablerst::toggle_fullscreen(GL_Window* window)
{
	PostMessage (window->hWnd, WM_TOGGLEFULLSCREEN, 0, 0);	// Send A WM_TOGGLEFULLSCREEN Message
}

void enablerst::reshape_GL(int width,int height)				// Reshape The Window When It's Moved Or Resized
{
	glDisable(GL_ALPHA_TEST); glDisable(GL_BLEND); glDisable(GL_DEPTH_TEST);
	glDisable(GL_DITHER); glDisable(GL_FOG); glDisable(GL_LIGHTING);
	glDisable(GL_LOGIC_OP); glDisable(GL_STENCIL_TEST);
	glDisable(GL_TEXTURE_1D);glShadeModel(GL_FLAT);
	glDisable(GL_TEXTURE_2D); glPixelTransferi(GL_MAP_COLOR, GL_FALSE);
	glPixelTransferi(GL_RED_SCALE, 1); glPixelTransferi(GL_RED_BIAS, 0);
	glPixelTransferi(GL_GREEN_SCALE, 1); glPixelTransferi(GL_GREEN_BIAS, 0);
	glPixelTransferi(GL_BLUE_SCALE, 1); glPixelTransferi(GL_BLUE_BIAS, 0);
	glPixelTransferi(GL_ALPHA_SCALE, 1); glPixelTransferi(GL_ALPHA_BIAS, 0);

	window_width=width;
	window_height=height;

	glViewport (0, 0, (GLsizei)(width), (GLsizei)(height));		// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f,enabler.window_width,enabler.window_height,0,-1.0,1.0);
	glMatrixMode (GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity ();											// Reset The Modelview Matrix
}

char enablerst::change_screen_resolution (int width, int height, int bitsPerPixel)	// Change The Screen Resolution
{
	DEVMODE dmScreenSettings;											// Device Mode
	ZeroMemory (&dmScreenSettings, sizeof (DEVMODE));					// Make Sure Memory Is Cleared
	dmScreenSettings.dmSize				= sizeof (DEVMODE);				// Size Of The Devmode Structure
	dmScreenSettings.dmPelsWidth		= width;						// Select Screen Width
	dmScreenSettings.dmPelsHeight		= height;						// Select Screen Height
	dmScreenSettings.dmBitsPerPel		= bitsPerPixel;					// Select Bits Per Pixel
	dmScreenSettings.dmFields			= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	if (ChangeDisplaySettings (&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		return FALSE;													// Display Change Failed, Return False
	}
	return TRUE;														// Display Change Was Successful, Return True
}

char enablerst::create_window_GL (GL_Window* window)									// This Code Creates Our OpenGL Window
{
	//DWORD windowStyle = WS_OVERLAPPEDWINDOW;							// Define Our Window Style
	DWORD windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	DWORD windowExtendedStyle = WS_EX_APPWINDOW;						// Define The Window's Extended Style

	PIXELFORMATDESCRIPTOR pfd =											// pfd Tells Windows How We Want Things To Be
	{
		sizeof (PIXELFORMATDESCRIPTOR),									// Size Of This Pixel Format Descriptor
		1,																// Version Number
		PFD_DRAW_TO_WINDOW |											// Format Must Support Window
		PFD_SUPPORT_OPENGL |											// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,												// Must Support Double Buffering
		PFD_TYPE_RGBA,													// Request An RGBA Format
		window->init.bitsPerPixel,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,												// Color Bits Ignored
		0,																// No Alpha Buffer
		0,																// Shift Bit Ignored
		0,																// No Accumulation Buffer
		0, 0, 0, 0,														// Accumulation Bits Ignored
		16,																// 16Bit Z-Buffer (Depth Buffer)  
		0,																// No Stencil Buffer
		0,																// No Auxiliary Buffer
		PFD_MAIN_PLANE,													// Main Drawing Layer
		0,																// Reserved
		0, 0, 0															// Layer Masks Ignored
	};

	if (window->init.isFullScreen == TRUE)								// Fullscreen Requested, Try Changing Video Modes
	{
		window->init.width=desired_fullscreen_width;
		window->init.height=desired_fullscreen_height;
	}
	else
	{
		window->init.width=desired_windowed_width;
		window->init.height=desired_windowed_height;
	}

	RECT windowRect = {0, 0, window->init.width, window->init.height};	// Define Our Window Coordinates

	GLuint PixelFormat;													// Will Hold The Selected Pixel Format

	if (window->init.isFullScreen == TRUE)								// Fullscreen Requested, Try Changing Video Modes
	{
		if (change_screen_resolution (window->init.width, window->init.height, window->init.bitsPerPixel) == FALSE)
		{
			// Fullscreen Mode Failed.  Run In Windowed Mode Instead
			MessageBox (HWND_DESKTOP, "Mode Switch Failed.\nRunning In Windowed Mode.", "Error", MB_OK | MB_ICONEXCLAMATION);
			window->init.isFullScreen = FALSE;							// Set isFullscreen To False (Windowed Mode)
		}
		else															// Otherwise (If Fullscreen Mode Was Successful)
		{
			windowStyle = WS_POPUP;										// Set The WindowStyle To WS_POPUP (Popup Window)
			windowExtendedStyle |= WS_EX_TOPMOST;						// Set The Extended Window Style To WS_EX_TOPMOST
		}																// (Top Window Covering Everything Else)
	}
	else																// If Fullscreen Was Not Selected
	{
		// Adjust Window, Account For Window Borders
		AdjustWindowRectEx (&windowRect, windowStyle, 0, windowExtendedStyle);
	}

	if(init.window.flag.has_flag(INIT_WINDOW_FLAG_TOPMOST))windowExtendedStyle|=WS_EX_TOPMOST;

	// Create The OpenGL Window
	window->hWnd = CreateWindowEx (windowExtendedStyle,					// Extended Style
								   window->init.application->className,	// Class Name
								   window->init.title,					// Window Title
								   windowStyle,							// Window Style
								   0, 0,								// Window X,Y Position
								   windowRect.right - windowRect.left,	// Window Width
								   windowRect.bottom - windowRect.top,	// Window Height
								   HWND_DESKTOP,						// Desktop Is Window's Parent
								   0,									// No Menu
								   window->init.application->hInstance, // Pass The Window Instance
								   window);

	if (window->hWnd == 0)												// Was Window Creation A Success?
	{
		return FALSE;													// If Not Return False
	}

	window->hDC = GetDC (window->hWnd);									// Grab A Device Context For This Window
	if (window->hDC == 0)												// Did We Get A Device Context?
	{
		// Failed
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	PixelFormat = ChoosePixelFormat (window->hDC, &pfd);				// Find A Compatible Pixel Format
	if (PixelFormat == 0)												// Did We Find A Compatible Format?
	{
		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	if (SetPixelFormat (window->hDC, PixelFormat, &pfd) == FALSE)		// Try To Set The Pixel Format
	{
		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	window->hRC = wglCreateContext (window->hDC);						// Try To Get A Rendering Context
	if (window->hRC == 0)												// Did We Get A Rendering Context?
	{
		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	// Make The Rendering Context Our Current Rendering Context
	if (wglMakeCurrent (window->hDC, window->hRC) == FALSE)
	{
		// Failed
		wglDeleteContext (window->hRC);									// Delete The Rendering Context
		window->hRC = 0;												// Zero The Rendering Context
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	ShowWindow (window->hWnd, SW_NORMAL);								// Make The Window Visible
	window->isVisible = TRUE;											// Set isVisible To True

	reshape_GL (window->init.width, window->init.height);				// Reshape Our GL Window

	ZeroMemory (window->keys, sizeof (Keys));							// Clear All Keys

	window->lastTickCount = GetTickCount ();							// Get Tick Count

	return TRUE;														// Window Creating Was A Success
																		// Initialization Will Be Done In WM_CREATE
}

char enablerst::destroy_window_GL (GL_Window* window)								// Destroy The OpenGL Window & Release Resources
{
	if (window->hWnd != 0)												// Does The Window Have A Handle?
	{	
		if (window->hDC != 0)											// Does The Window Have A Device Context?
		{
			wglMakeCurrent (window->hDC, 0);							// Set The Current Active Rendering Context To Zero
			if (window->hRC != 0)										// Does The Window Have A Rendering Context?
			{
				wglDeleteContext (window->hRC);							// Release The Rendering Context
				window->hRC = 0;										// Zero The Rendering Context

			}
			ReleaseDC (window->hWnd, window->hDC);						// Release The Device Context
			window->hDC = 0;											// Zero The Device Context
		}
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
	}

	if (window->init.isFullScreen)										// Is Window In Fullscreen Mode
	{
		ChangeDisplaySettings (NULL,0);									// Switch Back To Desktop Resolution
	}	
	return TRUE;														// Return True
}

// Process Window Message Callbacks
LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Get The Window Context
	GL_Window* window = (GL_Window*)(GetWindowLong (hWnd, GWL_USERDATA));

	switch (uMsg)														// Evaluate Window Message
	{
		case WM_ACTIVATE:
			{
			switch(wParam)
				{
				case WA_ACTIVE:
				case WA_CLICKACTIVE:
					if (window->init.isFullScreen)
						{
						enabler.change_screen_resolution (window->init.width, window->init.height, window->init.bitsPerPixel);
						}
					break;
				case WA_INACTIVE:
					if (window->init.isFullScreen)
						{
						ChangeDisplaySettings (NULL,0);									// Switch Back To Desktop Resolution
						CloseWindow(hWnd);
						}
					break;
				}
			break;
			}

		case WM_SYSCOMMAND:												// Intercept System Commands
		{
			switch (wParam)												// Check System Calls
			{
				case SC_SCREENSAVE:										// Screensaver Trying To Start?
				case SC_MONITORPOWER:									// Monitor Trying To Enter Powersave?
				case SC_MAXIMIZE:										// Trying to maximize?
				return 0;												// Prevent From Happening
			}
			break;														// Exit
		}
		return 0;														// Return

		case WM_CREATE:													// Window Creation
		{
			CREATESTRUCT* creation = (CREATESTRUCT*)(lParam);			// Store Window Structure Pointer
			window = (GL_Window*)(creation->lpCreateParams);
			SetWindowLong (hWnd, GWL_USERDATA, (LONG)(window));
		}
		return 0;														// Return

		case WM_CLOSE:													// Closing The Window
			{
			enabler_inputst newi;
				newi.key=27;//LIKE PRESSING ESCAPE
				newi.shift=false;
				newi.caps=false;
				newi.ctrl=false;
				newi.alt=false;
			enabler.add_input(newi);
			}
		return 0;														// Return

		case WM_SIZE:													// Size Action Has Taken Place
			switch (wParam)												// Evaluate Size Action
			{
				case SIZE_MINIMIZED:									// Was Window Minimized?
					window->isVisible = FALSE;							// Set isVisible To False
				return 0;												// Return

				case SIZE_MAXIMIZED:									// Was Window Maximized?
					window->isVisible = TRUE;							// Set isVisible To True
					enabler.reshape_GL (LOWORD (lParam), HIWORD (lParam));		// Reshape Window - LoWord=Width, HiWord=Height
				return 0;												// Return

				case SIZE_RESTORED:										// Was Window Restored?
					window->isVisible = TRUE;							// Set isVisible To True
					enabler.reshape_GL (LOWORD (lParam), HIWORD (lParam));		// Reshape Window - LoWord=Width, HiWord=Height
				return 0;												// Return
			}
		break;															// Break

		case WM_KEYDOWN:												// Update Keyboard Buffers For Keys Pressed
		case WM_SYSKEYDOWN:
			{
			if ((wParam >= 0) && (wParam <= 255))						// Is Key (wParam) In A Valid Range?
			{
				if(!(lParam & BIT31))
					{
					enabler_inputst newi;
						newi.key=wParam;
						newi.shift=((GetKeyState(VK_SHIFT)>>1)!=0);
						newi.caps=(GetKeyState(VK_CAPITAL)!=0);
						newi.ctrl=((GetKeyState(VK_CONTROL)>>1)!=0);
						newi.alt=((GetKeyState(VK_MENU)>>1)!=0);
					enabler.add_input(newi);
					}

				window->keys->keyDown [wParam] = TRUE;					// Set The Selected Key (wParam) To True
				return 0;												// Return
			}
			}
		break;															// Break

		case WM_KEYUP:													// Update Keyboard Buffers For Keys Released
		case WM_SYSKEYUP:
			if ((wParam >= 0) && (wParam <= 255))						// Is Key (wParam) In A Valid Range?
			{
				window->keys->keyDown [wParam] = FALSE;					// Set The Selected Key (wParam) To False
				return 0;												// Return
			}
		break;															// Break

		case WM_LBUTTONDOWN:enabler.mouse_lbut=1;enabler.mouse_lbut_down=1;return 0;
		case WM_LBUTTONUP:enabler.mouse_lbut=0;enabler.mouse_lbut_down=0;enabler.mouse_lbut_lift=1;return 0;
		case WM_RBUTTONDOWN:enabler.mouse_rbut=1;enabler.mouse_rbut_down=1;return 0;
		case WM_RBUTTONUP:enabler.mouse_rbut=0;enabler.mouse_rbut_down=0;enabler.mouse_rbut_lift=1;return 0;
		case WM_MOUSEMOVE:
			{
			enabler.oldmouse_x=enabler.mouse_x;
			enabler.oldmouse_y=enabler.mouse_y;
			enabler.mouse_x=LOWORD(lParam);
			enabler.mouse_y=HIWORD(lParam);

			if(!enabler.tracking_on)
				{
				TRACKMOUSEEVENT tme;
				tme.cbSize = sizeof(TRACKMOUSEEVENT);
				tme.dwFlags = TME_LEAVE;
				tme.hwndTrack = enabler.window.hWnd;

				if(TrackMouseEvent(&tme))
					{
					enabler.tracking_on=1;
					}
				else enabler.tracking_on=2;
				}

			return 0;
			}
		case WM_MOUSELEAVE:
			{
			enabler.oldmouse_x=-1;
			enabler.oldmouse_y=-1;
			enabler.mouse_x=-1;
			enabler.mouse_y=-1;
			enabler.mouse_lbut=0;
			enabler.mouse_rbut=0;
			enabler.mouse_lbut_down=0;
			enabler.mouse_rbut_down=0;
			enabler.mouse_lbut_lift=0;
			enabler.mouse_rbut_lift=0;
			enabler.tracking_on=0;
			return 0;
			}
		case WM_KILLFOCUS:
		case WM_SETFOCUS:
			{
			ZeroMemory(window->keys,sizeof(Keys));
			break;
			}

		case WM_TOGGLEFULLSCREEN:										// Toggle FullScreen Mode On/Off
			{
			enabler.create_full_screen = (enabler.create_full_screen == TRUE) ? FALSE : TRUE;

			ne_toggle_fullscreen();

			PostMessage (hWnd, WM_QUIT, 0, 0);
			}
		break;															// Break
	}

	return DefWindowProc (hWnd, uMsg, wParam, lParam);					// Pass Unhandled Messages To DefWindowProc
}

char enablerst::register_window_class (Application* application)						// Register A Window Class For This Application.
{																		// TRUE If Successful
	// Register A Window Class
	WNDCLASSEX windowClass;												// Window Class
	ZeroMemory (&windowClass, sizeof (WNDCLASSEX));						// Make Sure Memory Is Cleared
	windowClass.cbSize			= sizeof (WNDCLASSEX);					// Size Of The windowClass Structure
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraws The Window For Any Movement / Resizing
	windowClass.lpfnWndProc		= (WNDPROC)(WindowProc);				// WindowProc Handles Messages
	windowClass.hInstance		= application->hInstance;				// Set The Instance
	windowClass.hbrBackground	= (HBRUSH)COLOR_WINDOW+1;				// Class Background Brush Color
	windowClass.hIcon			= (HICON)LoadImage(application->hInstance,MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
	windowClass.hIconSm			= (HICON)LoadImage(application->hInstance,MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,16,16,LR_DEFAULTCOLOR);
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	windowClass.lpszClassName	= application->className;				// Sets The Applications Classname
	if (RegisterClassEx (&windowClass) == 0)							// Did Registering The Class Fail?
	{
		// NOTE: Failure, Should Never Happen
		MessageBox (HWND_DESKTOP, "RegisterClassEx Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													// Return False (Failure)
	}
	return TRUE;														// Return True (Success)
}

// Program Entry (WinMain)
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	enabler.command_line=lpCmdLine;

	int ret=enabler.loop(hInstance);

	return ret;
}																		// End Of WinMain()

char get_slot_and_addbit_uchar(unsigned char &addbit,long &slot,long checkflag,long slotnum)
{
	if(checkflag<0)return 0;

	//FIND PROPER SLOT
	slot=checkflag>>3;
	if(slot>=slotnum)return 0;

	//FIND PROPER BIT IN THAT SLOT
	addbit=1<<(checkflag%8);

	return 1;
}

unsigned char *enablerst::get_texture_data(long pos)
{
	if(pos<0||pos>=texture_data.size())return NULL;

	if(texture_data[pos]==NULL)return NULL;

	return texture_data[pos]->data;
}

void enablerst::refresh_texture_data(long pos)
{
	if(pos<0||pos>=texture_data.size())return;

	long t;
	for(t=(long)texture.size()-1;t>=0;t--)
		{
		if(texture[t]==NULL)continue;

		if(texture[t]->texture_data_pos==pos)
			{
			texture[t]->remove_texture();
			texture[t]->create_texture_from_data(pos);
			}
		}
}

void enablerst::enable_fade(float r,float g,float b,float a,float t)
{
	fade_r=r;fade_g=g;fade_b=b;fade_a=a;fade_t=t;
}

void enablerst::disable_fade()
{
	fade_t=0;
}

void enablerst::copy_texture_data(long dest,long src,
								  long offx,long offy,
								  float rmult,float gmult,float bmult,
								  char use_trans,long *color_data,unsigned long flag)
{
	unsigned char *buff2=get_texture_data(src);
	if(buff2==NULL)return;

	copy_texture_data(dest,buff2,texture_data[src]->width,texture_data[src]->height,
			texture_data[src]->alpha_texture,offx,offy,rmult,gmult,bmult,use_trans,color_data,flag);
}

void enablerst::copy_texture_data(long dest,unsigned char *src,long srcx,long srcy,char srcalpha,
			long offx,long offy,
			float rmult,float gmult,float bmult,char use_trans,long *color_data,unsigned long flag)
{
	//GET BUFFERS
	unsigned char *buff1=get_texture_data(dest);
	unsigned char *buff2=src;

	if(buff1==NULL||buff2==NULL)return;

	//COMPUTE THE PARAMETERS
	long starty,endy,startx,endx,dstartx,dstarty;
	long dind,dind2,dincx,dincx2,dincy,dincy2;

		//START AND END
	startx=offx;endx=offx+srcx-1;
	starty=offy;endy=offy+srcy-1;

		//BOUND START AND END TO DESTINATION BUFFER
	dstartx=0;dstarty=0;
	if(startx<0){dstartx=startx*-1;startx=0;}
	if(starty<0){dstarty=starty*-1;starty=0;}
	if(endx>=texture_data[dest]->width)endx=texture_data[dest]->width-1;
	if(endy>=texture_data[dest]->height)endy=texture_data[dest]->height-1;

		//SET INCREMENTS BASED ON ALPHA BIT
	if(texture_data[dest]->alpha_texture)dincx=4;
	else dincx=3;
	if(srcalpha)dincx2=4;
	else dincx2=3;
	dincy=(texture_data[dest]->width+(endx-startx+1))*dincx;
	dincy2=(srcx+(endx-startx+1))*dincx2;

		//SET THE INITIAL POSITION IN THE BUFFER
	dind=startx*dincx+(texture_data[dest]->height-starty-1)*texture_data[dest]->width*dincx;
	dind2=dstartx*dincx2+(srcy-dstarty-1)*srcx*dincx2;

	//NOTE: these flip commands can't handle the src over-running off the side of the dest buffer
	if(flag & COPYTEXTUREFLAG_VERFLIP)
		{
		dind2-=(endy-starty)*srcx*dincx2;
		if(!(flag & COPYTEXTUREFLAG_HORFLIP))dincy2=0;
		}

	if(flag & COPYTEXTUREFLAG_HORFLIP)
		{
		dind2+=(endx-startx)*dincx2;
		dincx2*=-1;
		if(!(flag & COPYTEXTUREFLAG_VERFLIP))dincy2=0;
		else dincy2*=-1;
		}

		//SET UP MULTIPLITERS
	long rmult_l=(long)(256.0f*rmult);//THE 256 IS NOT A PROBLEM SINCE IT IS A FLOAT ANYWAY
	long gmult_l=(long)(256.0f*gmult);
	long bmult_l=(long)(256.0f*bmult);

	//DO THE COPY
	long place_r,place_g,place_b,place_dist;
	long dx,dy;
	for(dy=starty;dy<=endy;dy++)
		{
		for(dx=startx;dx<=endx;dx++)
			{
			//RESPECT TRANSPARENCY
			if(use_trans)
				{
				if(srcalpha)
					{
					if(buff2[dind2+3]==0)
						{
						dind+=dincx;
						dind2+=dincx2;
						continue;
						}
					}
				}

			place_r=buff2[dind2];
			place_g=buff2[dind2+1];
			place_b=buff2[dind2+2];

			if(color_data!=NULL)
				{
				short slot=-1;

				if(place_r==place_g&&place_g==place_b&&place_r!=0){slot=COLOR_DATA_WHITE_R;place_dist=place_r;}
				if(place_r!=0&&place_g==0&&place_b==0){slot=COLOR_DATA_RED_R;place_dist=place_r;}
				if(place_g!=0&&place_b==0&&place_r==0){slot=COLOR_DATA_GREEN_R;place_dist=place_g;}
				if(place_b!=0&&place_r==0&&place_g==0){slot=COLOR_DATA_BLUE_R;place_dist=place_b;}
				if(place_r==place_g&&place_b==0&&place_r!=0){slot=COLOR_DATA_YELLOW_R;place_dist=place_r;}
				if(place_r==place_b&&place_g==0&&place_b!=0){slot=COLOR_DATA_MAGENTA_R;place_dist=place_r;}
				if(place_g==place_b&&place_r==0&&place_g!=0){slot=COLOR_DATA_CYAN_R;place_dist=place_g;}

				if(slot!=-1)
					{
					if(color_data[slot]!=-1)
						{
						place_r=(place_dist*color_data[slot])>>8;
						place_g=(place_dist*color_data[slot+1])>>8;
						place_b=(place_dist*color_data[slot+2])>>8;
						}
					}
				}

			//COPY IN DATA
			if(srcalpha)
				{
				if(use_trans&&buff2[dind2+3]!=255)
					{
					place_r=((place_r*(long)buff2[dind2+3]+(long)buff1[dind]*(long)(255-buff2[dind2+3]))>>8);
					place_g=((place_g*(long)buff2[dind2+3]+(long)buff1[dind+1]*(long)(255-buff2[dind2+3]))>>8);
					place_b=((place_b*(long)buff2[dind2+3]+(long)buff1[dind+2]*(long)(255-buff2[dind2+3]))>>8);
					}
				}
			if(texture_data[dest]->alpha_texture&&srcalpha)
				{
				if(!use_trans||buff2[dind2+3]==255)buff1[dind+3]=buff2[dind2+3];
				}

			if(rmult_l!=256)
				{
				buff1[dind]=(place_r*rmult_l)>>8;
				}
			else
				{
				buff1[dind]=place_r;
				}
			if(gmult_l!=256)
				{
				buff1[dind+1]=(place_g*gmult_l)>>8;
				}
			else
				{
				buff1[dind+1]=place_g;
				}
			if(bmult_l!=256)
				{
				buff1[dind+2]=(place_b*bmult_l)>>8;
				}
			else
				{
				buff1[dind+2]=place_b;
				}

			dind+=dincx;
			dind2+=dincx2;
			}
		dind-=dincy;
		dind2-=dincy2;
		}
}

void enablerst::remove_texture(long pos)
{
	if(pos>=0&&pos<texture.size())
		{
		if(texture[pos]==NULL)return;

		if(pos<650)
			{
			long a;
			a=0;
			}

		delete texture[pos];
		texture[pos]=NULL;
		}
}

void enablerst::remove_texture_data(long pos)
{
	if(pos>=0&&pos<texture_data.size())
		{
		if(texture_data[pos]==NULL)return;

		delete texture_data[pos];
		texture_data[pos]=NULL;
		}
}

void enablerst::read_pixels(int x,int y,int width,int height,unsigned char *buffer)
{
	glReadBuffer(GL_BACK);
	glReadPixels(x,y,width,height,GL_RGBA,GL_UNSIGNED_BYTE,buffer);
}

void enablerst::grayscale_texture_data(long pos)
{
	unsigned char *buff=get_texture_data(pos);
	if(buff==NULL)return;

	long bytes_per_pixel;
	if(texture_data[pos]->alpha_texture)bytes_per_pixel=4;
	else bytes_per_pixel=3;

	long dimx=texture_data[pos]->width;
	long dimy=texture_data[pos]->height;
	long ind=0,x,y;
	float norm=sqrt(3.0);
	float gx;
	long gr,gg,gb;
	for(x=0;x<dimx;x++)
		{
		for(y=0;y<dimy;y++)
			{
			gr=buff[ind];
			gg=buff[ind+1];
			gb=buff[ind+2];
			gx=(float)sqrt((float)(gr*gr+gg*gg+gb*gb))/norm;
			if(gx<0)gx=0;
			if(gx>255)gx=255;
			buff[ind]=(unsigned char)gx;

			ind+=bytes_per_pixel;
			}
		}
}

void enablerst::flip_texture_data(long pos,unsigned long flag)
{
	unsigned char *buff=get_texture_data(pos);
	if(buff==NULL)return;

	long bytes_per_pixel;
	if(texture_data[pos]->alpha_texture)bytes_per_pixel=4;
	else bytes_per_pixel=3;
	
	flip_uchar_array(buff,texture_data[pos]->width,texture_data[pos]->height,bytes_per_pixel,flag);
}

void enablerst::flip_uchar_array(unsigned char *buff,long dimx,long dimy,long bytes_per_pixel,unsigned long flag)
{
	unsigned char swap;
	long x,y,ind,incy,ind2,dimmult;

	if(flag & COPYTEXTUREFLAG_VERFLIP)
		{
		ind=0;
		incy=dimx*bytes_per_pixel;
		dimmult=(dimy-1)*incy;
		for(x=0;x<dimx;x++)
			{
			ind2=0;
			for(y=0;y<dimy>>1;y++)
				{
				swap=buff[ind+ind2];
				buff[ind+ind2]=buff[dimmult-ind2+ind];
				buff[dimmult-ind2+ind]=swap;

				if(bytes_per_pixel>1)
					{
					swap=buff[ind+1+ind2];
					buff[ind+1+ind2]=buff[dimmult-ind2+ind+1];
					buff[dimmult-ind2+ind+1]=swap;
					}
				if(bytes_per_pixel>2)
					{
					swap=buff[ind+2+ind2];
					buff[ind+2+ind2]=buff[dimmult-ind2+ind+2];
					buff[dimmult-ind2+ind+2]=swap;
					}
				if(bytes_per_pixel>3)
					{
					swap=buff[ind+3+ind2];
					buff[ind+3+ind2]=buff[dimmult-ind2+ind+3];
					buff[dimmult-ind2+ind+3]=swap;
					}
				ind2+=incy;
				}
			ind+=bytes_per_pixel;
			}
		}
	if(flag & COPYTEXTUREFLAG_HORFLIP)
		{
		ind=0;
		incy=dimx*bytes_per_pixel;
		dimmult=(dimx-1)*bytes_per_pixel;
		for(y=0;y<dimy;y++)
			{
			ind2=0;
			for(x=0;x<dimx>>1;x++)
				{
				swap=buff[ind+ind2];
				buff[ind+ind2]=buff[ind+dimmult-ind2];
				buff[ind+dimmult-ind2]=swap;

				if(bytes_per_pixel>1)
					{
					swap=buff[ind+ind2+1];
					buff[ind+ind2+1]=buff[ind+dimmult-ind2+1];
					buff[ind+dimmult-ind2+1]=swap;
					}
				if(bytes_per_pixel>2)
					{
					swap=buff[ind+ind2+2];
					buff[ind+ind2+2]=buff[ind+dimmult-ind2+2];
					buff[ind+dimmult-ind2+2]=swap;
					}
				if(bytes_per_pixel>3)
					{
					swap=buff[ind+ind2+3];
					buff[ind+ind2+3]=buff[ind+dimmult-ind2+3];
					buff[ind+dimmult-ind2+3]=swap;
					}
				ind2+=bytes_per_pixel;
				}
			ind+=incy;
			}
		}
}

void enablerst::add_perspective(float sx,float sy,float sz,
						float gx,float gy,float gz,
						float nx,float ny,float nz)
{
	tilest *newt;
	if(next_tile_slot==-1)
		{
		newt=new tilest;
		tile.push_back(newt);
		}
	else
		{
		newt=tile[next_tile_slot];

		next_tile_slot++;
		if(next_tile_slot>=tile.size())next_tile_slot=-1;
		}

	newt->color_r=sx;
	newt->color_g=sy;
	newt->color_b=sz;
	newt->x=gx;
	newt->y=gy;
	newt->hor_stretch=gz;
	newt->force_dimx=nx;
	newt->force_dimy=ny;
	newt->ver_stretch=nz;

	newt->flag=0;
	newt->flag|=TILEFLAG_MODEL_PERSPECTIVE;
}

void enablerst::add_translate(float sx,float sy,float sz)
{
	tilest *newt;
	if(next_tile_slot==-1)
		{
		newt=new tilest;
		tile.push_back(newt);
		}
	else
		{
		newt=tile[next_tile_slot];

		next_tile_slot++;
		if(next_tile_slot>=tile.size())next_tile_slot=-1;
		}

	newt->color_r=sx;
	newt->color_g=sy;
	newt->color_b=sz;

	newt->flag=0;
	newt->flag|=TILEFLAG_MODEL_TRANSLATE;
}

void enablerst::add_ortho()
{
	tilest *newt;
	if(next_tile_slot==-1)
		{
		newt=new tilest;
		tile.push_back(newt);
		}
	else
		{
		newt=tile[next_tile_slot];

		next_tile_slot++;
		if(next_tile_slot>=tile.size())next_tile_slot=-1;
		}

	newt->flag=0;
	newt->flag|=TILEFLAG_MODEL_ORTHO;
}

void text_system_file_infost::initialize_info()
{
	std::ifstream fseed(filename.c_str());
	if(fseed.is_open())
		{
		string str;

		while(std::getline(fseed,str))
			{
			if(str.length()>0)number++;
			}
		}
	else
		{
		string str;
		str="Error Initializing Text: ";
		str+=filename;
		errorlog_string(str);
		}
	fseed.close();
}

void text_system_file_infost::get_specific_text(text_infost &text,long num)
{
	text.clean();

	std::ifstream fseed(filename.c_str());
	if(fseed.is_open())
		{
		string str;

		//SKIP AHEAD TO THE RIGHT SPOT
		while(num>0)
			{
			std::getline(fseed,str);
			num--;
			}

		//PROCESS THE STRING INTO TEXT ELEMENTS
		if(std::getline(fseed,str))
			{
			long curpos;
			string nextstr;
			char doing_long=0;

			text_info_elementst *newel;
			long end=str.length();

			for(curpos=0;curpos<end;curpos++)
				{
				//HANDLE TOKEN OR ENDING
					//TWO FILE TOKENS IN A ROW MEANS LONG
					//ONE MEANS STRING
				if(str[curpos]==file_token || curpos==end-1)
					{
					if(str[curpos]!=file_token)nextstr+=str[curpos];

					//HAVE SOMETHING == SAVE IT
					if(!nextstr.empty())
						{
						if(doing_long)
							{
							newel=new text_info_element_longst(atoi(nextstr.c_str()));
							text.element.push_back(newel);
							doing_long=0;
							}
						else
							{
							newel=new text_info_element_stringst(nextstr);
							text.element.push_back(newel);
							}

						nextstr.erase();
						}
					//STARTING A LONG
					else
						{
						doing_long=1;
						}
					}
				//JUST ADD IN ANYTHING ELSE
				else
					{
					nextstr+=str[curpos];
					}
				}
			}
		}
	fseed.close();
}

void text_system_file_infost::get_text(text_infost &text)
{
	text.clean();

	if(number==0)return;

	get_specific_text(text,trandom(number));
}

void text_boxst::add_paragraph(const string &src,long para_width)
{
	stringvectst sp;
	sp.add_string(src);
	add_paragraph(sp,para_width);
}

void text_boxst::add_paragraph(stringvectst &src,long para_width)
{
	//USE THE WIDTH OF THE CURRENT FONT
	fontst *fnt=enabler.get_font(enabler.active_font_id);

	if(fnt==NULL)return;

	bool skip_leading_spaces=false;

	//ADD EACH OF THE STRINGS ON IN TURN
	string curstr;
	long strlength=0;
	long s,pos;
	for(s=0;s<src.str.size();s++)
		{
		//GRAB EACH WORD, AND SEE IF IT FITS, IF NOT START A NEW LINE
		for(pos=0;pos<src.str[s]->dat.size();pos++)
			{
			if(skip_leading_spaces)
				{
				if(src.str[s]->dat[pos]==' ')continue;
				else skip_leading_spaces=false;
				}

			//ADD TO WORD
			curstr+=src.str[s]->dat[pos];
			strlength+=fnt->letwidth[src.str[s]->dat[pos]];

			//IF TOO LONG, CUT BACK TO FIRST SPACE
			if(strlength>para_width)
				{
				long opos=pos;

				long minus=0;
				do
					{
					pos--;
					minus++;
					}while(src.str[s]->dat[pos]!=' '&&pos>0);

				//IF WENT ALL THE WAY BACK, INTRODUCE A SPACE
				if(minus==curstr.size())
					{
					src.str[s]->dat.insert(opos-1," ");
					}
				else
					{
					curstr.resize(curstr.size()-minus);
					text.add_string(curstr);
					skip_leading_spaces=true;
					}
				curstr.erase();
				strlength=0;
				}
			}
		}

	//FLUSH FINAL BIT
	if(!curstr.empty())text.add_string(curstr);
}

void curses_text_boxst::add_paragraph(const string &src,long para_width)
{
	stringvectst sp;
	sp.add_string(src);
	add_paragraph(sp,para_width);
}

void curses_text_boxst::add_paragraph(stringvectst &src,long para_width)
{
	bool skip_leading_spaces=false;

	//ADD EACH OF THE STRINGS ON IN TURN
	string curstr;
	long strlength=0;
	long s,pos;
	for(s=0;s<src.str.size();s++)
		{
		//GRAB EACH WORD, AND SEE IF IT FITS, IF NOT START A NEW LINE
		for(pos=0;pos<src.str[s]->dat.size();pos++)
			{
			if(skip_leading_spaces)
				{
				if(src.str[s]->dat[pos]==' ')continue;
				else skip_leading_spaces=false;
				}

			//ADD TO WORD
			curstr+=src.str[s]->dat[pos];

			//IF TOO LONG, CUT BACK TO FIRST SPACE
			if(curstr.length()>para_width)
				{
				long opos=pos;

				long minus=0;
				do
					{
					pos--;
					minus++;
					}while(src.str[s]->dat[pos]!=' '&&pos>0);

				//IF WENT ALL THE WAY BACK, INTRODUCE A SPACE
				if(minus==curstr.size())
					{
					src.str[s]->dat.insert(opos-1," ");
					}
				else
					{
					curstr.resize(curstr.size()-minus);
					text.add_string(curstr);
					skip_leading_spaces=true;
					}
				curstr.erase();
				}
			}
		}

	//FLUSH FINAL BIT
	if(!curstr.empty())text.add_string(curstr);
}

void enablerst::antialias(unsigned char *dat,long srcx,long srcy,char border)
{
	long pos=3,x,y;
	for(y=0;y<srcy;y++)
		{
		for(x=0;x<srcx;x++,pos+=4)
			{
			if(dat[pos]!=0)
				{
				if(x>0&&y>0&&x<srcx-1&&y<srcy-1)
					{
					if(dat[pos-4]==0||
						dat[pos+4]==0||
						dat[pos-4*srcx]==0||
						dat[pos+4*srcx]==0)
						{
						dat[pos]=128;
						}
					}
				else if(border)dat[pos]=128;
				}
			}
		}
}

void enablerst::save_texture_data_to_bmp(long pos,string &filename)
{
	if(pos<0&&pos>=texture_data.size())return;

  FILE *filePtr;
  BITMAPFILEHEADER bitmapFileHeader;
  BITMAPINFOHEADER bitmapInfoHeader;
  unsigned char    *bitmapImage=enabler.get_texture_data(pos);
  unsigned int      imageIdx=0;       // image index counter
  unsigned char     tempRGB;            // swap variable

  // open filename in "write binary" mode
  filePtr = fopen(filename.c_str(), "wb");
  if (filePtr == NULL)
    return;

  bitmapFileHeader.bfReserved1=0;
  bitmapFileHeader.bfReserved2=0;
  bitmapFileHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
  bitmapFileHeader.bfSize=sizeof(BITMAPFILEHEADER);
  bitmapFileHeader.bfType=BITMAP_ID;

  // write the bitmap file header
  fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

  bitmapInfoHeader.biBitCount=24+((long)texture_data[pos]->alpha_texture)*8;
  bitmapInfoHeader.biClrImportant=0;
  bitmapInfoHeader.biClrUsed=0;
  bitmapInfoHeader.biCompression=0;
  bitmapInfoHeader.biWidth=texture_data[pos]->width;
  bitmapInfoHeader.biHeight=texture_data[pos]->height;
  long bytes=bitmapInfoHeader.biBitCount/8;
  bitmapInfoHeader.biPlanes=1;
  bitmapInfoHeader.biSize=sizeof(BITMAPINFOHEADER);
  bitmapInfoHeader.biSizeImage=bitmapInfoHeader.biHeight*bitmapInfoHeader.biWidth*bytes;
  bitmapInfoHeader.biXPelsPerMeter=1;
  bitmapInfoHeader.biYPelsPerMeter=1;

  // write the bitmap information header
  fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

  // swap the R and B values to get RGB since the bitmap color format is in BGR
  for (imageIdx = 0; imageIdx < bitmapInfoHeader.biSizeImage; imageIdx+=bytes)
  {
    tempRGB = bitmapImage[imageIdx];
    bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
    bitmapImage[imageIdx + 2] = tempRGB;
  }

  // read in the bitmap image data
  fwrite(bitmapImage, 1, bitmapInfoHeader.biSizeImage, filePtr);

  // close the file
  fclose(filePtr);
}

void enablerst::refresh_tiles()
{
	long t;
	for(t=(long)tile.size()-1;t>=0;t--)tile[t]->flag|=TILEFLAG_DEAD;
	if(tile.size()>0)next_tile_slot=0;
	else next_tile_slot=-1;
}
#endif