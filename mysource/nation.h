//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

struct unitst
{
	unit_defst *def;
	string name;
	long level,num;

	unitst()
		{
		def=NULL;
		}
};

struct armyst
{
	svector<unitst *> unit;
	long nation_id;
	long global_id;
	long destination_territory;
	long current_territory;

	armyst()
		{
		destination_territory=-1;
		}

	~armyst()
		{
		long u;
		for(u=(long)unit.size()-1;u>=0;u--)delete unit[u];
		unit.clear();
		}

	unitst *get_leader();
};

struct battle_armyst
{
	svector<armyst *> army;
	long global_id;//this is nation_id, but use global_id templates
};

struct battle_unitst
{
	long side;
	long life,delay;
	short x,y;
	armyst *army;
	unitst *unit;
};

class nationst
{
	friend class nation_handlerst;

	public:
		static nationst *create(){return new nationst(0);}
		static nationst *create_for_load(){return new nationst(1);}

		//VARS
		long global_id;
		unsigned char sym;
		short f,br;
		nation_defst *def;
		string name;
		long next_army_id;
		svector<armyst *> army;

		//FUNCTIONS
		bool involved_in_conflict_in_territory(long t);
		void add_points_to_army(armyst *arm,long points);

	protected:
		nationst(char for_load);
		~nationst();
};

class nation_handlerst
{
	public:
		svector<nationst *> global;
		
		svector<nationst *> temp_save;

		long next_global_id;




		void clean()
			{
			while(global.size()>0)remove_nation(global.size()-1);
			}

		void remove_nation(long e){delete global[e];}
		void remove_nation(nationst *ptr){delete ptr;}

		nationst *get_nation_by_global_id(long id)
			{
			if(global.size()==0||id==-1)return NULL;

			return get_from_global_id_vector(id,global);
			}

		nation_handlerst()
			{
			next_global_id=0;
			}
		
		~nation_handlerst()
			{
			clean();
			}

		void create_new_nations();
};