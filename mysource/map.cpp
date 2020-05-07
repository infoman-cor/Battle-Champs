//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#include "game_g.h"
#include "game_extv.h"

void mapst::create_new_map()
{
	short x,y;
	for(x=0;x<dimx;x++)
		{
		for(y=0;y<dimy;y++)
			{
			square[x][y].init();
			}
		}

	long curplacelim=0;
	long curchecklim=0;
	short curplace=1;
	short curcheck=0;
	long l;
	short lx,ly,lx2,ly2;

	long start_territory=0;
	long cur_territory=0;
	unsigned char cur_letter='a';
	while(start_territory<init.feature.start_nation)
		{
		territory[start_territory].init();

		do
			{
			lx=trandom(dimx);
			ly=trandom(dimy);
			}while(square[lx][ly].territory!=-1||
				((lx>0&&ly>0)?(square[lx-1][ly-1].territory!=-1):false)||
				((lx>0)?(square[lx-1][ly].territory!=-1):false)||
				((lx>0&&ly<dimy-1)?(square[lx-1][ly+1].territory!=-1):false)||
				((ly>0)?(square[lx][ly-1].territory!=-1):false)||
				((ly<dimy-1)?(square[lx][ly+1].territory!=-1):false)||
				((lx<dimx-1&&ly>0)?(square[lx+1][ly-1].territory!=-1):false)||
				((lx<dimx-1)?(square[lx+1][ly].territory!=-1):false)||
				((lx<dimx-1&&ly<dimy-1)?(square[lx+1][ly+1].territory!=-1):false));

		territory[start_territory].letter=cur_letter;
		territory[start_territory].main_x=lx;
		territory[start_territory].main_y=ly;

		start_territory++;
		square[lx][ly].territory=cur_territory;
		cur_territory++;

		cur_letter++;
		if(cur_letter=='z'+1)cur_letter='A';

		line[curcheck][curchecklim][0]=lx;
		line[curcheck][curchecklim][1]=ly;
		curchecklim++;
		}

	short cand_x[4],cand_y[4],cand_num;

	while(curchecklim>0)
		{
		for(l=0;l<curchecklim;l++)
			{
			lx=line[curcheck][l][0];
			ly=line[curcheck][l][1];
			if(square[lx][ly].territory!=-1)
				{
				cand_num=0;
				if(lx>0)
					{
					if(square[lx-1][ly].territory==-1)
						{
						cand_x[cand_num]=lx-1;
						cand_y[cand_num]=ly;
						cand_num++;
						}
					}
				if(lx<dimx-1)
					{
					if(square[lx+1][ly].territory==-1)
						{
						cand_x[cand_num]=lx+1;
						cand_y[cand_num]=ly;
						cand_num++;
						}
					}
				if(ly>0)
					{
					if(square[lx][ly-1].territory==-1)
						{
						cand_x[cand_num]=lx;
						cand_y[cand_num]=ly-1;
						cand_num++;
						}
					}
				if(ly<dimy-1)
					{
					if(square[lx][ly+1].territory==-1)
						{
						cand_x[cand_num]=lx;
						cand_y[cand_num]=ly+1;
						cand_num++;
						}
					}
				if(cand_num!=0)
					{
					if(cand_num>1)
						{
						line[curplace][curplacelim][0]=lx;
						line[curplace][curplacelim][1]=ly;
						curplacelim++;
						}
					cand_num=trandom(cand_num);
					lx2=cand_x[cand_num];
					ly2=cand_y[cand_num];
					square[lx2][ly2].territory=square[lx][ly].territory;
					line[curplace][curplacelim][0]=lx2;
					line[curplace][curplacelim][1]=ly2;
					curplacelim++;
					}
				}
			}

		curplace=1-curplace;
		curcheck=1-curcheck;
		curchecklim=curplacelim;
		curplacelim=0;
		}

	//RECORD NEIGHBORS
	for(x=0;x<dimx;x++)
		{
		for(y=0;y<dimy;y++)
			{
			if(x>0)
				{
				if(square[x-1][y].territory!=square[x][y].territory)
					{
					binary_add_unique_to_vector(square[x][y].territory,territory[square[x-1][y].territory].neighbor);
					binary_add_unique_to_vector(square[x-1][y].territory,territory[square[x][y].territory].neighbor);
					}
				}
			if(y>0)
				{
				if(square[x][y-1].territory!=square[x][y].territory)
					{
					binary_add_unique_to_vector(square[x][y].territory,territory[square[x][y-1].territory].neighbor);
					binary_add_unique_to_vector(square[x][y-1].territory,territory[square[x][y].territory].neighbor);
					}
				}
			}
		}
}

void nation_handlerst::create_new_nations()
{
	svector<nation_defst *> cur_def;

	long num=0;
	while(num<init.feature.start_nation)
		{
		nationst *newn=nationst::create();
			switch(num/15)
				{
				case 0:newn->sym=219;break;
				case 1:newn->sym=178;break;
				case 2:newn->sym=177;break;
				case 3:newn->sym=176;break;
				}
			newn->f=((num%15)+1)%8;
			newn->br=((num%15)+1)/8;

		game.map.territory[num].nation_id=newn->global_id;
		game.map.territory[num].sym=newn->sym;
		game.map.territory[num].f=newn->f;
		game.map.territory[num].br=newn->br;

		//PICK A NATION DEFINITION
		if(cur_def.size()==0)
			{
			cur_def=game.nation_def.nation_def;
			}

		long ind=trandom(cur_def.size());
		newn->def=cur_def[ind];
		cur_def.erase(ind);

		//SET UP NAME
		string str;
		text_infost ti;
		enabler.text_system.get_text(newn->def->word_list_index,ti);
		str+=ti.get_string(0);
		enabler.text_system.get_text(newn->def->word_list_index,ti);
		str+=ti.get_string(0);
		capitalize_string_first_word(str);
		newn->name+=str;

		//SET UP INITIAL ARMY
		armyst *arm=new armyst;
			arm->global_id=newn->next_army_id;
			newn->next_army_id++;
			arm->nation_id=newn->global_id;
			arm->current_territory=num;

			unitst *newu=new unitst;
				newu->def=newn->def->grab_leader_unit_def();
				newu->level=1;
				newu->num=1;
				enabler.text_system.get_text(newn->def->word_list_index,ti);
				newu->name+=ti.get_string(0);
				enabler.text_system.get_text(newn->def->word_list_index,ti);
				newu->name+=ti.get_string(0);
				capitalize_string_first_word(newu->name);
			arm->unit.push_back(newu);

			newn->add_points_to_army(arm,10000);

		add_to_global_id_vector(arm,newn->army);

		game.map.territory[num].army_id[0]=arm->global_id;

		num++;
		}
}