//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#define MAX_WORLD_X 60
#define MAX_WORLD_Y 25
#define MAX_BATTLE_X 200
#define MAX_BATTLE_Y 200

struct map_squarest
{
	long territory;

	map_squarest()
		{
		init();
		}
	void init()
		{
		territory=-1;
		}
};

struct map_territoryst
{
	unsigned char letter;
	long nation_id;
	long army_id[9];
	unsigned char sym;
	short f,br;
	short main_x,main_y;
	svector<long> neighbor;

	map_territoryst()
		{
		init();
		}
	void init()
		{
		letter='1';
		nation_id=-1;
		short a;
		for(a=0;a<9;a++)army_id[a]=-1;
		sym=219;
		f=1;
		br=0;
		}
};

struct mapst
{
	map_squarest **square;
	short dimx,dimy;
	map_territoryst territory[52];

	mapst()
		{
		square=NULL;
		}
	~mapst()
		{
		clean();
		}
	void allocate(short n_dimx,short n_dimy)
		{
		clean();

		dimx=n_dimx;
		dimy=n_dimy;

		square=new map_squarest *[dimx];

		short x;
		for(x=0;x<dimx;x++)square[x]=new map_squarest[dimy];
		}
	void clean()
		{
		short x;
		for(x=0;x<dimx;x++)delete[] square[x];
		delete[] square;

		square=NULL;
		}

	void create_new_map();
};