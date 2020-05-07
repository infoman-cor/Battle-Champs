//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#include "game_g.h"
#include "game_extv.h"

nationst::nationst(char for_load)
{
	def=NULL;
	next_army_id=0;

	if(!for_load)
		{
		global_id=game.nation.next_global_id;game.nation.next_global_id++;
		add_to_global_id_vector(this,game.nation.global);
		}
}

nationst::~nationst()
{
	long t;
	for(t=(long)army.size()-1;t>=0;t--)delete army[t];
	army.clear();

	remove_from_global_id_vector(this,game.nation.global);
}

unitst *armyst::get_leader()
{
	long u;
	for(u=(long)unit.size()-1;u>=0;u--)
		{
		if(unit[u]->def->leader)return unit[u];
		}
	return NULL;
}

bool nationst::involved_in_conflict_in_territory(long t)
{
	bool have_you=false;
	bool have_other=false;
	long a;

	//ARMY STAYING IN THE TERRITORY
	nationst *nt=game.nation.get_nation_by_global_id(game.map.territory[t].nation_id);
	if(nt!=NULL)
		{
		for(a=0;a<9;a++)
			{
			armyst *arm=get_from_global_id_vector(game.map.territory[t].army_id[a],nt->army);
			if(arm!=NULL)
				{
				if(arm->destination_territory==-1)
					{
					if(arm->nation_id==0)have_you=true;
					else have_other=true;
					break;
					}
				}
			}
		}

	//ARMY ENTERING THE TERRITORY
	long n;
	for(n=0;n<game.nation.global.size();n++)
		{
		for(a=0;a<game.nation.global[n]->army.size();a++)
			{
			if(game.nation.global[n]->army[a]->destination_territory==t)
				{
				if(game.nation.global[n]->global_id==0)have_you=true;
				else have_other=true;
				break;
				}
			}
		if(have_you&&have_other)return true;
		}

	return false;
}

void nationst::add_points_to_army(armyst *arm,long points)
{
	long max=20000,cur=0;

	long u;
	for(u=0;u<arm->unit.size();u++)
		{
		if(!arm->unit[u]->def->leader)
			{
			cur+=arm->unit[u]->def->strength()*arm->unit[u]->num;
			}
		}

	if(points+cur>max)points=(max-cur);
	if(points<=0)return;

	bool added;
	
	do
		{
		added=false;

		long use_point;
		for(u=0;u<def->unit.size();u++)
			{
			if(!def->unit[u]->leader)
				{
				if(points>=def->unit[u]->strength())
					{
					use_point=points;
					if(use_point>1000&&def->unit[u]->strength()<=1000)use_point=1000;

					long i;
					for(i=0;i<arm->unit.size();i++)
						{
						if(arm->unit[i]->def==def->unit[u])
							{
							arm->unit[i]->num+=use_point/def->unit[u]->strength();
							break;
							}
						}
					if(i==arm->unit.size())
						{
						unitst *newu=new unitst;
							newu->def=def->unit[u];
							newu->level=1;
							newu->num=use_point/def->unit[u]->strength();
						arm->unit.push_back(newu);
						}

					points-=(use_point/def->unit[u]->strength())*def->unit[u]->strength();
					added=true;
					}
				}
			}
		}while(added&&points>0);
}