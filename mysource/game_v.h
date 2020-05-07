//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#ifdef ENABLER
extern enablerst enabler;
#endif

#ifndef NO_FMOD
extern musicsoundst musicsound;
#endif

interfacest gview;

long basic_seed;

long version;
long min_load_version;
long movie_version;

long linelim;
short line[4][MAXLINELIM][6];
short linechar[2][MAXLINELIM];

gamest game;
graphicst gps;
initst init;

char manucomp[80000];
char manucomp2[80000];
char filecomp_buffer[20000];
char filecomp_buffer2[80000];
char filecomp_buffer_aux[20000];
char filecomp_buffer2_aux[80000];

int mt_index[MT_BUFFER_NUM];
short mt_cur_buffer;
short mt_virtual_buffer;
unsigned long mt_buffer[MT_BUFFER_NUM][MT_LEN];