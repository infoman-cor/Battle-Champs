//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

struct unit_defst
{
	string name;
	long short_attack,life,range,range_attack;
	unsigned char sym;
	short f,b,br;
	bool leader;
	long texpos;

	unit_defst()
		{
		texpos=-1;
		}

	long strength()
		{
		return short_attack+life+range+range_attack;
		}
};

enum NationDefFlag
{
	NATION_DEF_FLAG_UNUSED1,
	NATION_DEF_FLAG_UNUSED2,
	NATION_DEF_FLAG_UNUSED3,
	NATION_DEF_FLAG_UNUSED4,
	NATION_DEF_FLAG_UNUSED5,
	NATION_DEF_FLAG_UNUSED6,
	NATION_DEF_FLAG_UNUSED7,
	NATION_DEF_FLAG_UNUSED8,
	NATION_DEF_FLAGNUM,
	NATION_DEF_FLAG_NONE=-1
};

class nation_defst
{
	friend class nation_def_handlerst;

	public:
		static nation_defst *create(){return new nation_defst;}

		string token;
		flagarrayst flag;
		string word_list;
		long word_list_index;

		svector<unit_defst *> unit;

		void finalize(long nation_def_index);

		unit_defst *grab_leader_unit_def()
			{
			svector<unit_defst *> cand;
			long u;
			for(u=0;u<unit.size();u++)
				{
				if(unit[u]->leader)cand.push_back(unit[u]);
				}

			if(cand.size()==0)exit(1);

			return cand[trandom(cand.size())];
			}

		void adopt_new_texture(long unit_index,string tile_page_token,long x,long y);

	protected:
		nation_defst();
		~nation_defst();
};

class nation_def_handlerst
{
	public:
		svector<nation_defst *> nation_def;

		void clean()
			{
			while(nation_def.size()>0)delete nation_def[nation_def.size()-1];
			}

		void adopt_new_lines(textlinesst &lines);

		~nation_def_handlerst()
			{
			clean();
			}

		void finalize();

		long get_nation_def_index_by_token(const string &token)
			{
			long w;
			for(w=0;w<nation_def.size();w++)
				{
				if(nation_def[w]->token==token)return w;
				}
			return -1;
			}

		nation_defst *get_nation_def_by_token(const string &token)
			{
			long w;
			for(w=0;w<nation_def.size();w++)
				{
				if(nation_def[w]->token==token)return nation_def[w];
				}
			return NULL;
			}
};