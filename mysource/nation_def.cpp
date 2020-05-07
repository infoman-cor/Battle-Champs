//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#include "game_g.h"
#include "game_extv.h"

void nation_def_handlerst::adopt_new_lines(textlinesst &lines)
{
	//NOTE: START AT 1 TO SKIP FILE NAME
	long t,pos;
	char *curstr;

	nation_defst *nd=NULL;

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

				if(token=="NATION")
					{
					string token2;
					if(grab_token_string(token2,curstr,pos))
						{
						nd=nation_defst::create();
							nd->token=token2;
						}
					continue;
					}
				else if(nd!=NULL)
					{
					if(token=="LEADER_UNIT"||token=="UNIT")
						{
						string token1;
						string token2;
						string token3;
						string token4;
						string token5;
						string token6;
						string token7;
						string token8;
						string token9;
						if(!(grab_token_string(token1,curstr,pos)))continue;
						if(!(grab_token_string(token2,curstr,pos)))continue;
						if(!(grab_token_string(token3,curstr,pos)))continue;
						if(!(grab_token_string(token4,curstr,pos)))continue;
						if(!(grab_token_string(token5,curstr,pos)))continue;
						if(!(grab_token_string(token6,curstr,pos)))continue;
						if(!(grab_token_string(token7,curstr,pos)))continue;
						if(!(grab_token_string(token8,curstr,pos)))continue;
						if(!(grab_token_string(token9,curstr,pos)))continue;

						unit_defst *new_u=new unit_defst;
							new_u->name=token1;
							new_u->short_attack=convert_string_to_long(token2);
							new_u->life=convert_string_to_long(token3);
							new_u->range=convert_string_to_long(token4);
							new_u->range_attack=convert_string_to_long(token5);
							if(token6[0]=='\'')
								{
								if(token6.length()>=2)
									{
									new_u->sym=token6[1];
									}
								}
							else new_u->sym=(unsigned char)(convert_string_to_long(token6));
							new_u->f=convert_string_to_long(token7);
							new_u->b=convert_string_to_long(token8);
							new_u->br=convert_string_to_long(token9);
							if(token=="LEADER_UNIT")new_u->leader=true;
							else new_u->leader=false;
						nd->unit.push_back(new_u);
						continue;
						}
					if(token=="WORD_LIST")
						{
						string token1;
						if(!(grab_token_string(token1,curstr,pos)))continue;

						nd->word_list=token1;
						continue;
						}

					string str="Unrecognized Nation Token: ";
					str+=token;
					errorlog_string(str);
					}
				}
			}
		}
}

void nation_def_handlerst::finalize()
{
	long s;
	for(s=0;s<nation_def.size();s++)nation_def[s]->finalize(s);
}

void nation_defst::finalize(long nation_def_index)
{
	string file;
	file="data/text/"+word_list;
	enabler.text_system.register_file(file,game.next_text_id,'@',0);

	word_list_index=game.next_text_id;
	game.next_text_id++;
}

nation_defst::nation_defst()
{
	flag.set_size_on_flag_num(NATION_DEF_FLAGNUM);

	game.nation_def.nation_def.push_back(this);
}

nation_defst::~nation_defst()
{
	long t;
	for(t=(long)game.nation_def.nation_def.size()-1;t>=0;t--)
		{
		if(game.nation_def.nation_def[t]==this)
			{
			game.nation_def.nation_def.erase(t);
			break;
			}
		}

	for(t=(long)unit.size()-1;t>=0;t--)delete unit[t];
	unit.clear();
}

void nation_defst::adopt_new_texture(long unit_index,string tile_page_token,long x,long y)
{
	tile_pagest *tp=gps.get_tile_page_by_token(tile_page_token);

	if(tp!=NULL)
		{
		if(!tp->loaded)tp->load_graphics();

		long num=x+y*tp->page_dim_x;
		if(num>=0&&num<(long)tp->texpos.size()&&unit_index>=0&&unit_index<unit.size())
			{
			unit[unit_index]->texpos=tp->texpos[num];
			}
		}
}