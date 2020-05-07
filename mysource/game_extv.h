//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#ifdef ENABLER
extern enablerst enabler;
#endif

#ifndef NO_FMOD
extern musicsoundst musicsound;
#endif

extern interfacest gview;

extern long basic_seed;

extern long version;
extern long min_load_version;
extern long movie_version;

extern long linelim;
extern short line[4][MAXLINELIM][6];
extern short linechar[2][MAXLINELIM];

extern gamest game;
extern graphicst gps;
extern initst init;

extern char manucomp[80000];
extern char manucomp2[80000];
extern char filecomp_buffer[20000];
extern char filecomp_buffer2[80000];
extern char filecomp_buffer_aux[20000];
extern char filecomp_buffer2_aux[80000];

extern int mt_index[MT_BUFFER_NUM];
extern short mt_cur_buffer;
extern short mt_virtual_buffer;
extern unsigned long mt_buffer[MT_BUFFER_NUM][MT_LEN];