//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

#include "game_g.h"
#include "game_extv.h"

using std::fstream;
using std::ios;

interfacest::interfacest()
{
	shutdown_interface_for_ms=0;
	shutdown_interface_tickcount=0;
	c=0;
	caps=0;
	shift=0;
	flag=0;
	supermovie_on=0;
	supermovie_pos=0;
	supermovie_delayrate=0;

	interfacekey[INTERFACEKEY_SELECT].name="Select";
	interfacekey[INTERFACEKEY_DESELECT].name="Deselect";
	interfacekey[INTERFACEKEY_SELECT_ALL].name="Select all";
	interfacekey[INTERFACEKEY_DESELECT_ALL].name="Deselect All";
	interfacekey[INTERFACEKEY_LEAVESCREEN].name="Leave screen";
	interfacekey[INTERFACEKEY_LEAVESCREEN_TEXT].name="Leave text entry screen";
	interfacekey[INTERFACEKEY_LEAVESCREEN_ALL].name="Leave all screens";
	interfacekey[INTERFACEKEY_TOGGLE_FULLSCREEN].name="Toggle Fullscreen";
	interfacekey[INTERFACEKEY_OPTIONS].name="Main menu";
	interfacekey[INTERFACEKEY_OPTION_EXPORT].name="Options, Export Local Image";
	interfacekey[INTERFACEKEY_HELP].name="Help";
	interfacekey[INTERFACEKEY_MOVIES].name="Movies";
	interfacekey[INTERFACEKEY_CHANGETAB].name="Change tab or highlight selection";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_UP].name="Move selector up";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_DOWN].name="Move selector down";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_LEFT].name="Move selector left";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_RIGHT].name="Move selector right";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_PAGEUP].name="Page selector up";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_PAGEDOWN].name="Page selector down";
	interfacekey[INTERFACEKEY_SECONDSCROLL_UP].name="Move secondary selector up";
	interfacekey[INTERFACEKEY_SECONDSCROLL_DOWN].name="Move secondary selector down";
	interfacekey[INTERFACEKEY_SECONDSCROLL_PAGEUP].name="Page secondary selector up";
	interfacekey[INTERFACEKEY_SECONDSCROLL_PAGEDOWN].name="Page secondary selector down";
	interfacekey[INTERFACEKEY_CURSOR_UP].name="Move view/cursor up";
	interfacekey[INTERFACEKEY_CURSOR_DOWN].name="Move view/cursor down";
	interfacekey[INTERFACEKEY_CURSOR_LEFT].name="Move view/cursor left";
	interfacekey[INTERFACEKEY_CURSOR_RIGHT].name="Move view/cursor right";
	interfacekey[INTERFACEKEY_CURSOR_UPLEFT].name="Move view/cursor up and left";
	interfacekey[INTERFACEKEY_CURSOR_UPRIGHT].name="Move view/cursor up and right";
	interfacekey[INTERFACEKEY_CURSOR_DOWNLEFT].name="Move view/cursor down and left";
	interfacekey[INTERFACEKEY_CURSOR_DOWNRIGHT].name="Move view/cursor down and right";
	interfacekey[INTERFACEKEY_CURSOR_UP_FAST].name="Move view/cursor up, fast";
	interfacekey[INTERFACEKEY_CURSOR_DOWN_FAST].name="Move view/cursor down, fast";
	interfacekey[INTERFACEKEY_CURSOR_LEFT_FAST].name="Move view/cursor left, fast";
	interfacekey[INTERFACEKEY_CURSOR_RIGHT_FAST].name="Move view/cursor right, fast";
	interfacekey[INTERFACEKEY_CURSOR_UPLEFT_FAST].name="Move view/cursor up and left, fast";
	interfacekey[INTERFACEKEY_CURSOR_UPRIGHT_FAST].name="Move view/cursor up and right, fast";
	interfacekey[INTERFACEKEY_CURSOR_DOWNLEFT_FAST].name="Move view/cursor down and left, fast";
	interfacekey[INTERFACEKEY_CURSOR_DOWNRIGHT_FAST].name="Move view/cursor down and right, fast";
	interfacekey[INTERFACEKEY_CURSOR_UP_Z].name="Move view/cursor up (z)";
	interfacekey[INTERFACEKEY_CURSOR_DOWN_Z].name="Move view/cursor down (z)";
	interfacekey[INTERFACEKEY_CURSOR_UP_Z_AUX].name="Move view/cursor up (z), aux";
	interfacekey[INTERFACEKEY_CURSOR_DOWN_Z_AUX].name="Move view/cursor down (z), aux";
	interfacekey[INTERFACEKEY_MENU_CONFIRM].name="Menu Confirm";
	interfacekey[INTERFACEKEY_SAVE_BINDINGS].name="Save Bindings";
	interfacekey[INTERFACEKEY_CHANGE_BINDINGS].name="Change Bindings";
	interfacekey[INTERFACEKEY_MOVIE_RECORD].name="Movie: Record";
	interfacekey[INTERFACEKEY_MOVIE_PLAY].name="Movie: Play";
	interfacekey[INTERFACEKEY_MOVIE_SAVE].name="Movie: Save";
	interfacekey[INTERFACEKEY_MOVIE_LOAD].name="Movie: Load";
	interfacekey[INTERFACEKEY_STRING_A000].name="String: Backspace";
	interfacekey[INTERFACEKEY_STRING_A001].name="String: Character 001";
	interfacekey[INTERFACEKEY_STRING_A002].name="String: Character 002";
	interfacekey[INTERFACEKEY_STRING_A003].name="String: Character 003";
	interfacekey[INTERFACEKEY_STRING_A004].name="String: Character 004";
	interfacekey[INTERFACEKEY_STRING_A005].name="String: Character 005";
	interfacekey[INTERFACEKEY_STRING_A006].name="String: Character 006";
	interfacekey[INTERFACEKEY_STRING_A007].name="String: Character 007";
	interfacekey[INTERFACEKEY_STRING_A008].name="String: Character 008";
	interfacekey[INTERFACEKEY_STRING_A009].name="String: Character 009";
	interfacekey[INTERFACEKEY_STRING_A010].name="String: Character 010";
	interfacekey[INTERFACEKEY_STRING_A011].name="String: Character 011";
	interfacekey[INTERFACEKEY_STRING_A012].name="String: Character 012";
	interfacekey[INTERFACEKEY_STRING_A013].name="String: Character 013";
	interfacekey[INTERFACEKEY_STRING_A014].name="String: Character 014";
	interfacekey[INTERFACEKEY_STRING_A015].name="String: Character 015";
	interfacekey[INTERFACEKEY_STRING_A016].name="String: Character 016";
	interfacekey[INTERFACEKEY_STRING_A017].name="String: Character 017";
	interfacekey[INTERFACEKEY_STRING_A018].name="String: Character 018";
	interfacekey[INTERFACEKEY_STRING_A019].name="String: Character 019";
	interfacekey[INTERFACEKEY_STRING_A020].name="String: Character 020";
	interfacekey[INTERFACEKEY_STRING_A021].name="String: Character 021";
	interfacekey[INTERFACEKEY_STRING_A022].name="String: Character 022";
	interfacekey[INTERFACEKEY_STRING_A023].name="String: Character 023";
	interfacekey[INTERFACEKEY_STRING_A024].name="String: Character 024";
	interfacekey[INTERFACEKEY_STRING_A025].name="String: Character 025";
	interfacekey[INTERFACEKEY_STRING_A026].name="String: Character 026";
	interfacekey[INTERFACEKEY_STRING_A027].name="String: Character 027";
	interfacekey[INTERFACEKEY_STRING_A028].name="String: Character 028";
	interfacekey[INTERFACEKEY_STRING_A029].name="String: Character 029";
	interfacekey[INTERFACEKEY_STRING_A030].name="String: Character 030";
	interfacekey[INTERFACEKEY_STRING_A031].name="String: Character 031";
	interfacekey[INTERFACEKEY_STRING_A032].name="String: Character 032";
	interfacekey[INTERFACEKEY_STRING_A033].name="String: Character 033";
	interfacekey[INTERFACEKEY_STRING_A034].name="String: Character 034";
	interfacekey[INTERFACEKEY_STRING_A035].name="String: Character 035";
	interfacekey[INTERFACEKEY_STRING_A036].name="String: Character 036";
	interfacekey[INTERFACEKEY_STRING_A037].name="String: Character 037";
	interfacekey[INTERFACEKEY_STRING_A038].name="String: Character 038";
	interfacekey[INTERFACEKEY_STRING_A039].name="String: Character 039";
	interfacekey[INTERFACEKEY_STRING_A040].name="String: Character 040";
	interfacekey[INTERFACEKEY_STRING_A041].name="String: Character 041";
	interfacekey[INTERFACEKEY_STRING_A042].name="String: Character 042";
	interfacekey[INTERFACEKEY_STRING_A043].name="String: Character 043";
	interfacekey[INTERFACEKEY_STRING_A044].name="String: Character 044";
	interfacekey[INTERFACEKEY_STRING_A045].name="String: Character 045";
	interfacekey[INTERFACEKEY_STRING_A046].name="String: Character 046";
	interfacekey[INTERFACEKEY_STRING_A047].name="String: Character 047";
	interfacekey[INTERFACEKEY_STRING_A048].name="String: Character 048";
	interfacekey[INTERFACEKEY_STRING_A049].name="String: Character 049";
	interfacekey[INTERFACEKEY_STRING_A050].name="String: Character 050";
	interfacekey[INTERFACEKEY_STRING_A051].name="String: Character 051";
	interfacekey[INTERFACEKEY_STRING_A052].name="String: Character 052";
	interfacekey[INTERFACEKEY_STRING_A053].name="String: Character 053";
	interfacekey[INTERFACEKEY_STRING_A054].name="String: Character 054";
	interfacekey[INTERFACEKEY_STRING_A055].name="String: Character 055";
	interfacekey[INTERFACEKEY_STRING_A056].name="String: Character 056";
	interfacekey[INTERFACEKEY_STRING_A057].name="String: Character 057";
	interfacekey[INTERFACEKEY_STRING_A058].name="String: Character 058";
	interfacekey[INTERFACEKEY_STRING_A059].name="String: Character 059";
	interfacekey[INTERFACEKEY_STRING_A060].name="String: Character 060";
	interfacekey[INTERFACEKEY_STRING_A061].name="String: Character 061";
	interfacekey[INTERFACEKEY_STRING_A062].name="String: Character 062";
	interfacekey[INTERFACEKEY_STRING_A063].name="String: Character 063";
	interfacekey[INTERFACEKEY_STRING_A064].name="String: Character 064";
	interfacekey[INTERFACEKEY_STRING_A065].name="String: Character 065";
	interfacekey[INTERFACEKEY_STRING_A066].name="String: Character 066";
	interfacekey[INTERFACEKEY_STRING_A067].name="String: Character 067";
	interfacekey[INTERFACEKEY_STRING_A068].name="String: Character 068";
	interfacekey[INTERFACEKEY_STRING_A069].name="String: Character 069";
	interfacekey[INTERFACEKEY_STRING_A070].name="String: Character 070";
	interfacekey[INTERFACEKEY_STRING_A071].name="String: Character 071";
	interfacekey[INTERFACEKEY_STRING_A072].name="String: Character 072";
	interfacekey[INTERFACEKEY_STRING_A073].name="String: Character 073";
	interfacekey[INTERFACEKEY_STRING_A074].name="String: Character 074";
	interfacekey[INTERFACEKEY_STRING_A075].name="String: Character 075";
	interfacekey[INTERFACEKEY_STRING_A076].name="String: Character 076";
	interfacekey[INTERFACEKEY_STRING_A077].name="String: Character 077";
	interfacekey[INTERFACEKEY_STRING_A078].name="String: Character 078";
	interfacekey[INTERFACEKEY_STRING_A079].name="String: Character 079";
	interfacekey[INTERFACEKEY_STRING_A080].name="String: Character 080";
	interfacekey[INTERFACEKEY_STRING_A081].name="String: Character 081";
	interfacekey[INTERFACEKEY_STRING_A082].name="String: Character 082";
	interfacekey[INTERFACEKEY_STRING_A083].name="String: Character 083";
	interfacekey[INTERFACEKEY_STRING_A084].name="String: Character 084";
	interfacekey[INTERFACEKEY_STRING_A085].name="String: Character 085";
	interfacekey[INTERFACEKEY_STRING_A086].name="String: Character 086";
	interfacekey[INTERFACEKEY_STRING_A087].name="String: Character 087";
	interfacekey[INTERFACEKEY_STRING_A088].name="String: Character 088";
	interfacekey[INTERFACEKEY_STRING_A089].name="String: Character 089";
	interfacekey[INTERFACEKEY_STRING_A090].name="String: Character 090";
	interfacekey[INTERFACEKEY_STRING_A091].name="String: Character 091";
	interfacekey[INTERFACEKEY_STRING_A092].name="String: Character 092";
	interfacekey[INTERFACEKEY_STRING_A093].name="String: Character 093";
	interfacekey[INTERFACEKEY_STRING_A094].name="String: Character 094";
	interfacekey[INTERFACEKEY_STRING_A095].name="String: Character 095";
	interfacekey[INTERFACEKEY_STRING_A096].name="String: Character 096";
	interfacekey[INTERFACEKEY_STRING_A097].name="String: Character 097";
	interfacekey[INTERFACEKEY_STRING_A098].name="String: Character 098";
	interfacekey[INTERFACEKEY_STRING_A099].name="String: Character 099";
	interfacekey[INTERFACEKEY_STRING_A100].name="String: Character 100";
	interfacekey[INTERFACEKEY_STRING_A101].name="String: Character 101";
	interfacekey[INTERFACEKEY_STRING_A102].name="String: Character 102";
	interfacekey[INTERFACEKEY_STRING_A103].name="String: Character 103";
	interfacekey[INTERFACEKEY_STRING_A104].name="String: Character 104";
	interfacekey[INTERFACEKEY_STRING_A105].name="String: Character 105";
	interfacekey[INTERFACEKEY_STRING_A106].name="String: Character 106";
	interfacekey[INTERFACEKEY_STRING_A107].name="String: Character 107";
	interfacekey[INTERFACEKEY_STRING_A108].name="String: Character 108";
	interfacekey[INTERFACEKEY_STRING_A109].name="String: Character 109";
	interfacekey[INTERFACEKEY_STRING_A110].name="String: Character 110";
	interfacekey[INTERFACEKEY_STRING_A111].name="String: Character 111";
	interfacekey[INTERFACEKEY_STRING_A112].name="String: Character 112";
	interfacekey[INTERFACEKEY_STRING_A113].name="String: Character 113";
	interfacekey[INTERFACEKEY_STRING_A114].name="String: Character 114";
	interfacekey[INTERFACEKEY_STRING_A115].name="String: Character 115";
	interfacekey[INTERFACEKEY_STRING_A116].name="String: Character 116";
	interfacekey[INTERFACEKEY_STRING_A117].name="String: Character 117";
	interfacekey[INTERFACEKEY_STRING_A118].name="String: Character 118";
	interfacekey[INTERFACEKEY_STRING_A119].name="String: Character 119";
	interfacekey[INTERFACEKEY_STRING_A120].name="String: Character 120";
	interfacekey[INTERFACEKEY_STRING_A121].name="String: Character 121";
	interfacekey[INTERFACEKEY_STRING_A122].name="String: Character 122";
	interfacekey[INTERFACEKEY_STRING_A123].name="String: Character 123";
	interfacekey[INTERFACEKEY_STRING_A124].name="String: Character 124";
	interfacekey[INTERFACEKEY_STRING_A125].name="String: Character 125";
	interfacekey[INTERFACEKEY_STRING_A126].name="String: Character 126";
	interfacekey[INTERFACEKEY_STRING_A127].name="String: Character 127";
	interfacekey[INTERFACEKEY_STRING_A128].name="String: Character 128";
	interfacekey[INTERFACEKEY_STRING_A129].name="String: Character 129";
	interfacekey[INTERFACEKEY_STRING_A130].name="String: Character 130";
	interfacekey[INTERFACEKEY_STRING_A131].name="String: Character 131";
	interfacekey[INTERFACEKEY_STRING_A132].name="String: Character 132";
	interfacekey[INTERFACEKEY_STRING_A133].name="String: Character 133";
	interfacekey[INTERFACEKEY_STRING_A134].name="String: Character 134";
	interfacekey[INTERFACEKEY_STRING_A135].name="String: Character 135";
	interfacekey[INTERFACEKEY_STRING_A136].name="String: Character 136";
	interfacekey[INTERFACEKEY_STRING_A137].name="String: Character 137";
	interfacekey[INTERFACEKEY_STRING_A138].name="String: Character 138";
	interfacekey[INTERFACEKEY_STRING_A139].name="String: Character 139";
	interfacekey[INTERFACEKEY_STRING_A140].name="String: Character 140";
	interfacekey[INTERFACEKEY_STRING_A141].name="String: Character 141";
	interfacekey[INTERFACEKEY_STRING_A142].name="String: Character 142";
	interfacekey[INTERFACEKEY_STRING_A143].name="String: Character 143";
	interfacekey[INTERFACEKEY_STRING_A144].name="String: Character 144";
	interfacekey[INTERFACEKEY_STRING_A145].name="String: Character 145";
	interfacekey[INTERFACEKEY_STRING_A146].name="String: Character 146";
	interfacekey[INTERFACEKEY_STRING_A147].name="String: Character 147";
	interfacekey[INTERFACEKEY_STRING_A148].name="String: Character 148";
	interfacekey[INTERFACEKEY_STRING_A149].name="String: Character 149";
	interfacekey[INTERFACEKEY_STRING_A150].name="String: Character 150";
	interfacekey[INTERFACEKEY_STRING_A151].name="String: Character 151";
	interfacekey[INTERFACEKEY_STRING_A152].name="String: Character 152";
	interfacekey[INTERFACEKEY_STRING_A153].name="String: Character 153";
	interfacekey[INTERFACEKEY_STRING_A154].name="String: Character 154";
	interfacekey[INTERFACEKEY_STRING_A155].name="String: Character 155";
	interfacekey[INTERFACEKEY_STRING_A156].name="String: Character 156";
	interfacekey[INTERFACEKEY_STRING_A157].name="String: Character 157";
	interfacekey[INTERFACEKEY_STRING_A158].name="String: Character 158";
	interfacekey[INTERFACEKEY_STRING_A159].name="String: Character 159";
	interfacekey[INTERFACEKEY_STRING_A160].name="String: Character 160";
	interfacekey[INTERFACEKEY_STRING_A161].name="String: Character 161";
	interfacekey[INTERFACEKEY_STRING_A162].name="String: Character 162";
	interfacekey[INTERFACEKEY_STRING_A163].name="String: Character 163";
	interfacekey[INTERFACEKEY_STRING_A164].name="String: Character 164";
	interfacekey[INTERFACEKEY_STRING_A165].name="String: Character 165";
	interfacekey[INTERFACEKEY_STRING_A166].name="String: Character 166";
	interfacekey[INTERFACEKEY_STRING_A167].name="String: Character 167";
	interfacekey[INTERFACEKEY_STRING_A168].name="String: Character 168";
	interfacekey[INTERFACEKEY_STRING_A169].name="String: Character 169";
	interfacekey[INTERFACEKEY_STRING_A170].name="String: Character 170";
	interfacekey[INTERFACEKEY_STRING_A171].name="String: Character 171";
	interfacekey[INTERFACEKEY_STRING_A172].name="String: Character 172";
	interfacekey[INTERFACEKEY_STRING_A173].name="String: Character 173";
	interfacekey[INTERFACEKEY_STRING_A174].name="String: Character 174";
	interfacekey[INTERFACEKEY_STRING_A175].name="String: Character 175";
	interfacekey[INTERFACEKEY_STRING_A176].name="String: Character 176";
	interfacekey[INTERFACEKEY_STRING_A177].name="String: Character 177";
	interfacekey[INTERFACEKEY_STRING_A178].name="String: Character 178";
	interfacekey[INTERFACEKEY_STRING_A179].name="String: Character 179";
	interfacekey[INTERFACEKEY_STRING_A180].name="String: Character 180";
	interfacekey[INTERFACEKEY_STRING_A181].name="String: Character 181";
	interfacekey[INTERFACEKEY_STRING_A182].name="String: Character 182";
	interfacekey[INTERFACEKEY_STRING_A183].name="String: Character 183";
	interfacekey[INTERFACEKEY_STRING_A184].name="String: Character 184";
	interfacekey[INTERFACEKEY_STRING_A185].name="String: Character 185";
	interfacekey[INTERFACEKEY_STRING_A186].name="String: Character 186";
	interfacekey[INTERFACEKEY_STRING_A187].name="String: Character 187";
	interfacekey[INTERFACEKEY_STRING_A188].name="String: Character 188";
	interfacekey[INTERFACEKEY_STRING_A189].name="String: Character 189";
	interfacekey[INTERFACEKEY_STRING_A190].name="String: Character 190";
	interfacekey[INTERFACEKEY_STRING_A191].name="String: Character 191";
	interfacekey[INTERFACEKEY_STRING_A192].name="String: Character 192";
	interfacekey[INTERFACEKEY_STRING_A193].name="String: Character 193";
	interfacekey[INTERFACEKEY_STRING_A194].name="String: Character 194";
	interfacekey[INTERFACEKEY_STRING_A195].name="String: Character 195";
	interfacekey[INTERFACEKEY_STRING_A196].name="String: Character 196";
	interfacekey[INTERFACEKEY_STRING_A197].name="String: Character 197";
	interfacekey[INTERFACEKEY_STRING_A198].name="String: Character 198";
	interfacekey[INTERFACEKEY_STRING_A199].name="String: Character 199";
	interfacekey[INTERFACEKEY_STRING_A200].name="String: Character 200";
	interfacekey[INTERFACEKEY_STRING_A201].name="String: Character 201";
	interfacekey[INTERFACEKEY_STRING_A202].name="String: Character 202";
	interfacekey[INTERFACEKEY_STRING_A203].name="String: Character 203";
	interfacekey[INTERFACEKEY_STRING_A204].name="String: Character 204";
	interfacekey[INTERFACEKEY_STRING_A205].name="String: Character 205";
	interfacekey[INTERFACEKEY_STRING_A206].name="String: Character 206";
	interfacekey[INTERFACEKEY_STRING_A207].name="String: Character 207";
	interfacekey[INTERFACEKEY_STRING_A208].name="String: Character 208";
	interfacekey[INTERFACEKEY_STRING_A209].name="String: Character 209";
	interfacekey[INTERFACEKEY_STRING_A210].name="String: Character 210";
	interfacekey[INTERFACEKEY_STRING_A211].name="String: Character 211";
	interfacekey[INTERFACEKEY_STRING_A212].name="String: Character 212";
	interfacekey[INTERFACEKEY_STRING_A213].name="String: Character 213";
	interfacekey[INTERFACEKEY_STRING_A214].name="String: Character 214";
	interfacekey[INTERFACEKEY_STRING_A215].name="String: Character 215";
	interfacekey[INTERFACEKEY_STRING_A216].name="String: Character 216";
	interfacekey[INTERFACEKEY_STRING_A217].name="String: Character 217";
	interfacekey[INTERFACEKEY_STRING_A218].name="String: Character 218";
	interfacekey[INTERFACEKEY_STRING_A219].name="String: Character 219";
	interfacekey[INTERFACEKEY_STRING_A220].name="String: Character 220";
	interfacekey[INTERFACEKEY_STRING_A221].name="String: Character 221";
	interfacekey[INTERFACEKEY_STRING_A222].name="String: Character 222";
	interfacekey[INTERFACEKEY_STRING_A223].name="String: Character 223";
	interfacekey[INTERFACEKEY_STRING_A224].name="String: Character 224";
	interfacekey[INTERFACEKEY_STRING_A225].name="String: Character 225";
	interfacekey[INTERFACEKEY_STRING_A226].name="String: Character 226";
	interfacekey[INTERFACEKEY_STRING_A227].name="String: Character 227";
	interfacekey[INTERFACEKEY_STRING_A228].name="String: Character 228";
	interfacekey[INTERFACEKEY_STRING_A229].name="String: Character 229";
	interfacekey[INTERFACEKEY_STRING_A230].name="String: Character 230";
	interfacekey[INTERFACEKEY_STRING_A231].name="String: Character 231";
	interfacekey[INTERFACEKEY_STRING_A232].name="String: Character 232";
	interfacekey[INTERFACEKEY_STRING_A233].name="String: Character 233";
	interfacekey[INTERFACEKEY_STRING_A234].name="String: Character 234";
	interfacekey[INTERFACEKEY_STRING_A235].name="String: Character 235";
	interfacekey[INTERFACEKEY_STRING_A236].name="String: Character 236";
	interfacekey[INTERFACEKEY_STRING_A237].name="String: Character 237";
	interfacekey[INTERFACEKEY_STRING_A238].name="String: Character 238";
	interfacekey[INTERFACEKEY_STRING_A239].name="String: Character 239";
	interfacekey[INTERFACEKEY_STRING_A240].name="String: Character 240";
	interfacekey[INTERFACEKEY_STRING_A241].name="String: Character 241";
	interfacekey[INTERFACEKEY_STRING_A242].name="String: Character 242";
	interfacekey[INTERFACEKEY_STRING_A243].name="String: Character 243";
	interfacekey[INTERFACEKEY_STRING_A244].name="String: Character 244";
	interfacekey[INTERFACEKEY_STRING_A245].name="String: Character 245";
	interfacekey[INTERFACEKEY_STRING_A246].name="String: Character 246";
	interfacekey[INTERFACEKEY_STRING_A247].name="String: Character 247";
	interfacekey[INTERFACEKEY_STRING_A248].name="String: Character 248";
	interfacekey[INTERFACEKEY_STRING_A249].name="String: Character 249";
	interfacekey[INTERFACEKEY_STRING_A250].name="String: Character 250";
	interfacekey[INTERFACEKEY_STRING_A251].name="String: Character 251";
	interfacekey[INTERFACEKEY_STRING_A252].name="String: Character 252";
	interfacekey[INTERFACEKEY_STRING_A253].name="String: Character 253";
	interfacekey[INTERFACEKEY_STRING_A254].name="String: Character 254";
	interfacekey[INTERFACEKEY_STRING_A255].name="String: Character 255";

	interfacekey[INTERFACEKEY_SELECT].tokenname="SELECT";
	interfacekey[INTERFACEKEY_DESELECT].tokenname="DESELECT";
	interfacekey[INTERFACEKEY_SELECT_ALL].tokenname="SELECT_ALL";
	interfacekey[INTERFACEKEY_DESELECT_ALL].tokenname="DESELECT_ALL";
	interfacekey[INTERFACEKEY_LEAVESCREEN].tokenname="LEAVESCREEN";
	interfacekey[INTERFACEKEY_LEAVESCREEN_TEXT].tokenname="LEAVESCREEN_TEXT";
	interfacekey[INTERFACEKEY_LEAVESCREEN_ALL].tokenname="LEAVESCREEN_ALL";
	interfacekey[INTERFACEKEY_TOGGLE_FULLSCREEN].tokenname="TOGGLE_FULLSCREEN";
	interfacekey[INTERFACEKEY_HELP].tokenname="HELP";
	interfacekey[INTERFACEKEY_MOVIES].tokenname="MOVIES";
	interfacekey[INTERFACEKEY_OPTIONS].tokenname="OPTIONS";
	interfacekey[INTERFACEKEY_OPTION_EXPORT].tokenname="OPTION_EXPORT";
	interfacekey[INTERFACEKEY_CHANGETAB].tokenname="CHANGETAB";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_LEFT].tokenname="STANDARDSCROLL_LEFT";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_RIGHT].tokenname="STANDARDSCROLL_RIGHT";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_UP].tokenname="STANDARDSCROLL_UP";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_DOWN].tokenname="STANDARDSCROLL_DOWN";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_PAGEUP].tokenname="STANDARDSCROLL_PAGEUP";
	interfacekey[INTERFACEKEY_STANDARDSCROLL_PAGEDOWN].tokenname="STANDARDSCROLL_PAGEDOWN";
	interfacekey[INTERFACEKEY_SECONDSCROLL_UP].tokenname="SECONDSCROLL_UP";
	interfacekey[INTERFACEKEY_SECONDSCROLL_DOWN].tokenname="SECONDSCROLL_DOWN";
	interfacekey[INTERFACEKEY_SECONDSCROLL_PAGEUP].tokenname="SECONDSCROLL_PAGEUP";
	interfacekey[INTERFACEKEY_SECONDSCROLL_PAGEDOWN].tokenname="SECONDSCROLL_PAGEDOWN";
	interfacekey[INTERFACEKEY_CURSOR_UP].tokenname="CURSOR_UP";
	interfacekey[INTERFACEKEY_CURSOR_DOWN].tokenname="CURSOR_DOWN";
	interfacekey[INTERFACEKEY_CURSOR_LEFT].tokenname="CURSOR_LEFT";
	interfacekey[INTERFACEKEY_CURSOR_RIGHT].tokenname="CURSOR_RIGHT";
	interfacekey[INTERFACEKEY_CURSOR_UPLEFT].tokenname="CURSOR_UPLEFT";
	interfacekey[INTERFACEKEY_CURSOR_UPRIGHT].tokenname="CURSOR_UPRIGHT";
	interfacekey[INTERFACEKEY_CURSOR_DOWNLEFT].tokenname="CURSOR_DOWNLEFT";
	interfacekey[INTERFACEKEY_CURSOR_DOWNRIGHT].tokenname="CURSOR_DOWNRIGHT";
	interfacekey[INTERFACEKEY_CURSOR_UP_FAST].tokenname="CURSOR_UP_FAST";
	interfacekey[INTERFACEKEY_CURSOR_DOWN_FAST].tokenname="CURSOR_DOWN_FAST";
	interfacekey[INTERFACEKEY_CURSOR_LEFT_FAST].tokenname="CURSOR_LEFT_FAST";
	interfacekey[INTERFACEKEY_CURSOR_RIGHT_FAST].tokenname="CURSOR_RIGHT_FAST";
	interfacekey[INTERFACEKEY_CURSOR_UPLEFT_FAST].tokenname="CURSOR_UPLEFT_FAST";
	interfacekey[INTERFACEKEY_CURSOR_UPRIGHT_FAST].tokenname="CURSOR_UPRIGHT_FAST";
	interfacekey[INTERFACEKEY_CURSOR_DOWNLEFT_FAST].tokenname="CURSOR_DOWNLEFT_FAST";
	interfacekey[INTERFACEKEY_CURSOR_DOWNRIGHT_FAST].tokenname="CURSOR_DOWNRIGHT_FAST";
	interfacekey[INTERFACEKEY_CURSOR_UP_Z].tokenname="CURSOR_UP_Z";
	interfacekey[INTERFACEKEY_CURSOR_DOWN_Z].tokenname="CURSOR_DOWN_Z";
	interfacekey[INTERFACEKEY_CURSOR_UP_Z_AUX].tokenname="CURSOR_UP_Z_AUX";
	interfacekey[INTERFACEKEY_CURSOR_DOWN_Z_AUX].tokenname="CURSOR_DOWN_Z_AUX";
	interfacekey[INTERFACEKEY_MENU_CONFIRM].tokenname="MENU_CONFIRM";
	interfacekey[INTERFACEKEY_SAVE_BINDINGS].tokenname="SAVE_BINDINGS";
	interfacekey[INTERFACEKEY_CHANGE_BINDINGS].tokenname="CHANGE_BINDINGS";
	interfacekey[INTERFACEKEY_MOVIE_RECORD].tokenname="MOVIE_RECORD";
	interfacekey[INTERFACEKEY_MOVIE_PLAY].tokenname="MOVIE_PLAY";
	interfacekey[INTERFACEKEY_MOVIE_SAVE].tokenname="MOVIE_SAVE";
	interfacekey[INTERFACEKEY_MOVIE_LOAD].tokenname="MOVIE_LOAD";
	interfacekey[INTERFACEKEY_STRING_A000].tokenname="STRING_A000";
	interfacekey[INTERFACEKEY_STRING_A001].tokenname="STRING_A001";
	interfacekey[INTERFACEKEY_STRING_A002].tokenname="STRING_A002";
	interfacekey[INTERFACEKEY_STRING_A003].tokenname="STRING_A003";
	interfacekey[INTERFACEKEY_STRING_A004].tokenname="STRING_A004";
	interfacekey[INTERFACEKEY_STRING_A005].tokenname="STRING_A005";
	interfacekey[INTERFACEKEY_STRING_A006].tokenname="STRING_A006";
	interfacekey[INTERFACEKEY_STRING_A007].tokenname="STRING_A007";
	interfacekey[INTERFACEKEY_STRING_A008].tokenname="STRING_A008";
	interfacekey[INTERFACEKEY_STRING_A009].tokenname="STRING_A009";
	interfacekey[INTERFACEKEY_STRING_A010].tokenname="STRING_A010";
	interfacekey[INTERFACEKEY_STRING_A011].tokenname="STRING_A011";
	interfacekey[INTERFACEKEY_STRING_A012].tokenname="STRING_A012";
	interfacekey[INTERFACEKEY_STRING_A013].tokenname="STRING_A013";
	interfacekey[INTERFACEKEY_STRING_A014].tokenname="STRING_A014";
	interfacekey[INTERFACEKEY_STRING_A015].tokenname="STRING_A015";
	interfacekey[INTERFACEKEY_STRING_A016].tokenname="STRING_A016";
	interfacekey[INTERFACEKEY_STRING_A017].tokenname="STRING_A017";
	interfacekey[INTERFACEKEY_STRING_A018].tokenname="STRING_A018";
	interfacekey[INTERFACEKEY_STRING_A019].tokenname="STRING_A019";
	interfacekey[INTERFACEKEY_STRING_A020].tokenname="STRING_A020";
	interfacekey[INTERFACEKEY_STRING_A021].tokenname="STRING_A021";
	interfacekey[INTERFACEKEY_STRING_A022].tokenname="STRING_A022";
	interfacekey[INTERFACEKEY_STRING_A023].tokenname="STRING_A023";
	interfacekey[INTERFACEKEY_STRING_A024].tokenname="STRING_A024";
	interfacekey[INTERFACEKEY_STRING_A025].tokenname="STRING_A025";
	interfacekey[INTERFACEKEY_STRING_A026].tokenname="STRING_A026";
	interfacekey[INTERFACEKEY_STRING_A027].tokenname="STRING_A027";
	interfacekey[INTERFACEKEY_STRING_A028].tokenname="STRING_A028";
	interfacekey[INTERFACEKEY_STRING_A029].tokenname="STRING_A029";
	interfacekey[INTERFACEKEY_STRING_A030].tokenname="STRING_A030";
	interfacekey[INTERFACEKEY_STRING_A031].tokenname="STRING_A031";
	interfacekey[INTERFACEKEY_STRING_A032].tokenname="STRING_A032";
	interfacekey[INTERFACEKEY_STRING_A033].tokenname="STRING_A033";
	interfacekey[INTERFACEKEY_STRING_A034].tokenname="STRING_A034";
	interfacekey[INTERFACEKEY_STRING_A035].tokenname="STRING_A035";
	interfacekey[INTERFACEKEY_STRING_A036].tokenname="STRING_A036";
	interfacekey[INTERFACEKEY_STRING_A037].tokenname="STRING_A037";
	interfacekey[INTERFACEKEY_STRING_A038].tokenname="STRING_A038";
	interfacekey[INTERFACEKEY_STRING_A039].tokenname="STRING_A039";
	interfacekey[INTERFACEKEY_STRING_A040].tokenname="STRING_A040";
	interfacekey[INTERFACEKEY_STRING_A041].tokenname="STRING_A041";
	interfacekey[INTERFACEKEY_STRING_A042].tokenname="STRING_A042";
	interfacekey[INTERFACEKEY_STRING_A043].tokenname="STRING_A043";
	interfacekey[INTERFACEKEY_STRING_A044].tokenname="STRING_A044";
	interfacekey[INTERFACEKEY_STRING_A045].tokenname="STRING_A045";
	interfacekey[INTERFACEKEY_STRING_A046].tokenname="STRING_A046";
	interfacekey[INTERFACEKEY_STRING_A047].tokenname="STRING_A047";
	interfacekey[INTERFACEKEY_STRING_A048].tokenname="STRING_A048";
	interfacekey[INTERFACEKEY_STRING_A049].tokenname="STRING_A049";
	interfacekey[INTERFACEKEY_STRING_A050].tokenname="STRING_A050";
	interfacekey[INTERFACEKEY_STRING_A051].tokenname="STRING_A051";
	interfacekey[INTERFACEKEY_STRING_A052].tokenname="STRING_A052";
	interfacekey[INTERFACEKEY_STRING_A053].tokenname="STRING_A053";
	interfacekey[INTERFACEKEY_STRING_A054].tokenname="STRING_A054";
	interfacekey[INTERFACEKEY_STRING_A055].tokenname="STRING_A055";
	interfacekey[INTERFACEKEY_STRING_A056].tokenname="STRING_A056";
	interfacekey[INTERFACEKEY_STRING_A057].tokenname="STRING_A057";
	interfacekey[INTERFACEKEY_STRING_A058].tokenname="STRING_A058";
	interfacekey[INTERFACEKEY_STRING_A059].tokenname="STRING_A059";
	interfacekey[INTERFACEKEY_STRING_A060].tokenname="STRING_A060";
	interfacekey[INTERFACEKEY_STRING_A061].tokenname="STRING_A061";
	interfacekey[INTERFACEKEY_STRING_A062].tokenname="STRING_A062";
	interfacekey[INTERFACEKEY_STRING_A063].tokenname="STRING_A063";
	interfacekey[INTERFACEKEY_STRING_A064].tokenname="STRING_A064";
	interfacekey[INTERFACEKEY_STRING_A065].tokenname="STRING_A065";
	interfacekey[INTERFACEKEY_STRING_A066].tokenname="STRING_A066";
	interfacekey[INTERFACEKEY_STRING_A067].tokenname="STRING_A067";
	interfacekey[INTERFACEKEY_STRING_A068].tokenname="STRING_A068";
	interfacekey[INTERFACEKEY_STRING_A069].tokenname="STRING_A069";
	interfacekey[INTERFACEKEY_STRING_A070].tokenname="STRING_A070";
	interfacekey[INTERFACEKEY_STRING_A071].tokenname="STRING_A071";
	interfacekey[INTERFACEKEY_STRING_A072].tokenname="STRING_A072";
	interfacekey[INTERFACEKEY_STRING_A073].tokenname="STRING_A073";
	interfacekey[INTERFACEKEY_STRING_A074].tokenname="STRING_A074";
	interfacekey[INTERFACEKEY_STRING_A075].tokenname="STRING_A075";
	interfacekey[INTERFACEKEY_STRING_A076].tokenname="STRING_A076";
	interfacekey[INTERFACEKEY_STRING_A077].tokenname="STRING_A077";
	interfacekey[INTERFACEKEY_STRING_A078].tokenname="STRING_A078";
	interfacekey[INTERFACEKEY_STRING_A079].tokenname="STRING_A079";
	interfacekey[INTERFACEKEY_STRING_A080].tokenname="STRING_A080";
	interfacekey[INTERFACEKEY_STRING_A081].tokenname="STRING_A081";
	interfacekey[INTERFACEKEY_STRING_A082].tokenname="STRING_A082";
	interfacekey[INTERFACEKEY_STRING_A083].tokenname="STRING_A083";
	interfacekey[INTERFACEKEY_STRING_A084].tokenname="STRING_A084";
	interfacekey[INTERFACEKEY_STRING_A085].tokenname="STRING_A085";
	interfacekey[INTERFACEKEY_STRING_A086].tokenname="STRING_A086";
	interfacekey[INTERFACEKEY_STRING_A087].tokenname="STRING_A087";
	interfacekey[INTERFACEKEY_STRING_A088].tokenname="STRING_A088";
	interfacekey[INTERFACEKEY_STRING_A089].tokenname="STRING_A089";
	interfacekey[INTERFACEKEY_STRING_A090].tokenname="STRING_A090";
	interfacekey[INTERFACEKEY_STRING_A091].tokenname="STRING_A091";
	interfacekey[INTERFACEKEY_STRING_A092].tokenname="STRING_A092";
	interfacekey[INTERFACEKEY_STRING_A093].tokenname="STRING_A093";
	interfacekey[INTERFACEKEY_STRING_A094].tokenname="STRING_A094";
	interfacekey[INTERFACEKEY_STRING_A095].tokenname="STRING_A095";
	interfacekey[INTERFACEKEY_STRING_A096].tokenname="STRING_A096";
	interfacekey[INTERFACEKEY_STRING_A097].tokenname="STRING_A097";
	interfacekey[INTERFACEKEY_STRING_A098].tokenname="STRING_A098";
	interfacekey[INTERFACEKEY_STRING_A099].tokenname="STRING_A099";
	interfacekey[INTERFACEKEY_STRING_A100].tokenname="STRING_A100";
	interfacekey[INTERFACEKEY_STRING_A101].tokenname="STRING_A101";
	interfacekey[INTERFACEKEY_STRING_A102].tokenname="STRING_A102";
	interfacekey[INTERFACEKEY_STRING_A103].tokenname="STRING_A103";
	interfacekey[INTERFACEKEY_STRING_A104].tokenname="STRING_A104";
	interfacekey[INTERFACEKEY_STRING_A105].tokenname="STRING_A105";
	interfacekey[INTERFACEKEY_STRING_A106].tokenname="STRING_A106";
	interfacekey[INTERFACEKEY_STRING_A107].tokenname="STRING_A107";
	interfacekey[INTERFACEKEY_STRING_A108].tokenname="STRING_A108";
	interfacekey[INTERFACEKEY_STRING_A109].tokenname="STRING_A109";
	interfacekey[INTERFACEKEY_STRING_A110].tokenname="STRING_A110";
	interfacekey[INTERFACEKEY_STRING_A111].tokenname="STRING_A111";
	interfacekey[INTERFACEKEY_STRING_A112].tokenname="STRING_A112";
	interfacekey[INTERFACEKEY_STRING_A113].tokenname="STRING_A113";
	interfacekey[INTERFACEKEY_STRING_A114].tokenname="STRING_A114";
	interfacekey[INTERFACEKEY_STRING_A115].tokenname="STRING_A115";
	interfacekey[INTERFACEKEY_STRING_A116].tokenname="STRING_A116";
	interfacekey[INTERFACEKEY_STRING_A117].tokenname="STRING_A117";
	interfacekey[INTERFACEKEY_STRING_A118].tokenname="STRING_A118";
	interfacekey[INTERFACEKEY_STRING_A119].tokenname="STRING_A119";
	interfacekey[INTERFACEKEY_STRING_A120].tokenname="STRING_A120";
	interfacekey[INTERFACEKEY_STRING_A121].tokenname="STRING_A121";
	interfacekey[INTERFACEKEY_STRING_A122].tokenname="STRING_A122";
	interfacekey[INTERFACEKEY_STRING_A123].tokenname="STRING_A123";
	interfacekey[INTERFACEKEY_STRING_A124].tokenname="STRING_A124";
	interfacekey[INTERFACEKEY_STRING_A125].tokenname="STRING_A125";
	interfacekey[INTERFACEKEY_STRING_A126].tokenname="STRING_A126";
	interfacekey[INTERFACEKEY_STRING_A127].tokenname="STRING_A127";
	interfacekey[INTERFACEKEY_STRING_A128].tokenname="STRING_A128";
	interfacekey[INTERFACEKEY_STRING_A129].tokenname="STRING_A129";
	interfacekey[INTERFACEKEY_STRING_A130].tokenname="STRING_A130";
	interfacekey[INTERFACEKEY_STRING_A131].tokenname="STRING_A131";
	interfacekey[INTERFACEKEY_STRING_A132].tokenname="STRING_A132";
	interfacekey[INTERFACEKEY_STRING_A133].tokenname="STRING_A133";
	interfacekey[INTERFACEKEY_STRING_A134].tokenname="STRING_A134";
	interfacekey[INTERFACEKEY_STRING_A135].tokenname="STRING_A135";
	interfacekey[INTERFACEKEY_STRING_A136].tokenname="STRING_A136";
	interfacekey[INTERFACEKEY_STRING_A137].tokenname="STRING_A137";
	interfacekey[INTERFACEKEY_STRING_A138].tokenname="STRING_A138";
	interfacekey[INTERFACEKEY_STRING_A139].tokenname="STRING_A139";
	interfacekey[INTERFACEKEY_STRING_A140].tokenname="STRING_A140";
	interfacekey[INTERFACEKEY_STRING_A141].tokenname="STRING_A141";
	interfacekey[INTERFACEKEY_STRING_A142].tokenname="STRING_A142";
	interfacekey[INTERFACEKEY_STRING_A143].tokenname="STRING_A143";
	interfacekey[INTERFACEKEY_STRING_A144].tokenname="STRING_A144";
	interfacekey[INTERFACEKEY_STRING_A145].tokenname="STRING_A145";
	interfacekey[INTERFACEKEY_STRING_A146].tokenname="STRING_A146";
	interfacekey[INTERFACEKEY_STRING_A147].tokenname="STRING_A147";
	interfacekey[INTERFACEKEY_STRING_A148].tokenname="STRING_A148";
	interfacekey[INTERFACEKEY_STRING_A149].tokenname="STRING_A149";
	interfacekey[INTERFACEKEY_STRING_A150].tokenname="STRING_A150";
	interfacekey[INTERFACEKEY_STRING_A151].tokenname="STRING_A151";
	interfacekey[INTERFACEKEY_STRING_A152].tokenname="STRING_A152";
	interfacekey[INTERFACEKEY_STRING_A153].tokenname="STRING_A153";
	interfacekey[INTERFACEKEY_STRING_A154].tokenname="STRING_A154";
	interfacekey[INTERFACEKEY_STRING_A155].tokenname="STRING_A155";
	interfacekey[INTERFACEKEY_STRING_A156].tokenname="STRING_A156";
	interfacekey[INTERFACEKEY_STRING_A157].tokenname="STRING_A157";
	interfacekey[INTERFACEKEY_STRING_A158].tokenname="STRING_A158";
	interfacekey[INTERFACEKEY_STRING_A159].tokenname="STRING_A159";
	interfacekey[INTERFACEKEY_STRING_A160].tokenname="STRING_A160";
	interfacekey[INTERFACEKEY_STRING_A161].tokenname="STRING_A161";
	interfacekey[INTERFACEKEY_STRING_A162].tokenname="STRING_A162";
	interfacekey[INTERFACEKEY_STRING_A163].tokenname="STRING_A163";
	interfacekey[INTERFACEKEY_STRING_A164].tokenname="STRING_A164";
	interfacekey[INTERFACEKEY_STRING_A165].tokenname="STRING_A165";
	interfacekey[INTERFACEKEY_STRING_A166].tokenname="STRING_A166";
	interfacekey[INTERFACEKEY_STRING_A167].tokenname="STRING_A167";
	interfacekey[INTERFACEKEY_STRING_A168].tokenname="STRING_A168";
	interfacekey[INTERFACEKEY_STRING_A169].tokenname="STRING_A169";
	interfacekey[INTERFACEKEY_STRING_A170].tokenname="STRING_A170";
	interfacekey[INTERFACEKEY_STRING_A171].tokenname="STRING_A171";
	interfacekey[INTERFACEKEY_STRING_A172].tokenname="STRING_A172";
	interfacekey[INTERFACEKEY_STRING_A173].tokenname="STRING_A173";
	interfacekey[INTERFACEKEY_STRING_A174].tokenname="STRING_A174";
	interfacekey[INTERFACEKEY_STRING_A175].tokenname="STRING_A175";
	interfacekey[INTERFACEKEY_STRING_A176].tokenname="STRING_A176";
	interfacekey[INTERFACEKEY_STRING_A177].tokenname="STRING_A177";
	interfacekey[INTERFACEKEY_STRING_A178].tokenname="STRING_A178";
	interfacekey[INTERFACEKEY_STRING_A179].tokenname="STRING_A179";
	interfacekey[INTERFACEKEY_STRING_A180].tokenname="STRING_A180";
	interfacekey[INTERFACEKEY_STRING_A181].tokenname="STRING_A181";
	interfacekey[INTERFACEKEY_STRING_A182].tokenname="STRING_A182";
	interfacekey[INTERFACEKEY_STRING_A183].tokenname="STRING_A183";
	interfacekey[INTERFACEKEY_STRING_A184].tokenname="STRING_A184";
	interfacekey[INTERFACEKEY_STRING_A185].tokenname="STRING_A185";
	interfacekey[INTERFACEKEY_STRING_A186].tokenname="STRING_A186";
	interfacekey[INTERFACEKEY_STRING_A187].tokenname="STRING_A187";
	interfacekey[INTERFACEKEY_STRING_A188].tokenname="STRING_A188";
	interfacekey[INTERFACEKEY_STRING_A189].tokenname="STRING_A189";
	interfacekey[INTERFACEKEY_STRING_A190].tokenname="STRING_A190";
	interfacekey[INTERFACEKEY_STRING_A191].tokenname="STRING_A191";
	interfacekey[INTERFACEKEY_STRING_A192].tokenname="STRING_A192";
	interfacekey[INTERFACEKEY_STRING_A193].tokenname="STRING_A193";
	interfacekey[INTERFACEKEY_STRING_A194].tokenname="STRING_A194";
	interfacekey[INTERFACEKEY_STRING_A195].tokenname="STRING_A195";
	interfacekey[INTERFACEKEY_STRING_A196].tokenname="STRING_A196";
	interfacekey[INTERFACEKEY_STRING_A197].tokenname="STRING_A197";
	interfacekey[INTERFACEKEY_STRING_A198].tokenname="STRING_A198";
	interfacekey[INTERFACEKEY_STRING_A199].tokenname="STRING_A199";
	interfacekey[INTERFACEKEY_STRING_A200].tokenname="STRING_A200";
	interfacekey[INTERFACEKEY_STRING_A201].tokenname="STRING_A201";
	interfacekey[INTERFACEKEY_STRING_A202].tokenname="STRING_A202";
	interfacekey[INTERFACEKEY_STRING_A203].tokenname="STRING_A203";
	interfacekey[INTERFACEKEY_STRING_A204].tokenname="STRING_A204";
	interfacekey[INTERFACEKEY_STRING_A205].tokenname="STRING_A205";
	interfacekey[INTERFACEKEY_STRING_A206].tokenname="STRING_A206";
	interfacekey[INTERFACEKEY_STRING_A207].tokenname="STRING_A207";
	interfacekey[INTERFACEKEY_STRING_A208].tokenname="STRING_A208";
	interfacekey[INTERFACEKEY_STRING_A209].tokenname="STRING_A209";
	interfacekey[INTERFACEKEY_STRING_A210].tokenname="STRING_A210";
	interfacekey[INTERFACEKEY_STRING_A211].tokenname="STRING_A211";
	interfacekey[INTERFACEKEY_STRING_A212].tokenname="STRING_A212";
	interfacekey[INTERFACEKEY_STRING_A213].tokenname="STRING_A213";
	interfacekey[INTERFACEKEY_STRING_A214].tokenname="STRING_A214";
	interfacekey[INTERFACEKEY_STRING_A215].tokenname="STRING_A215";
	interfacekey[INTERFACEKEY_STRING_A216].tokenname="STRING_A216";
	interfacekey[INTERFACEKEY_STRING_A217].tokenname="STRING_A217";
	interfacekey[INTERFACEKEY_STRING_A218].tokenname="STRING_A218";
	interfacekey[INTERFACEKEY_STRING_A219].tokenname="STRING_A219";
	interfacekey[INTERFACEKEY_STRING_A220].tokenname="STRING_A220";
	interfacekey[INTERFACEKEY_STRING_A221].tokenname="STRING_A221";
	interfacekey[INTERFACEKEY_STRING_A222].tokenname="STRING_A222";
	interfacekey[INTERFACEKEY_STRING_A223].tokenname="STRING_A223";
	interfacekey[INTERFACEKEY_STRING_A224].tokenname="STRING_A224";
	interfacekey[INTERFACEKEY_STRING_A225].tokenname="STRING_A225";
	interfacekey[INTERFACEKEY_STRING_A226].tokenname="STRING_A226";
	interfacekey[INTERFACEKEY_STRING_A227].tokenname="STRING_A227";
	interfacekey[INTERFACEKEY_STRING_A228].tokenname="STRING_A228";
	interfacekey[INTERFACEKEY_STRING_A229].tokenname="STRING_A229";
	interfacekey[INTERFACEKEY_STRING_A230].tokenname="STRING_A230";
	interfacekey[INTERFACEKEY_STRING_A231].tokenname="STRING_A231";
	interfacekey[INTERFACEKEY_STRING_A232].tokenname="STRING_A232";
	interfacekey[INTERFACEKEY_STRING_A233].tokenname="STRING_A233";
	interfacekey[INTERFACEKEY_STRING_A234].tokenname="STRING_A234";
	interfacekey[INTERFACEKEY_STRING_A235].tokenname="STRING_A235";
	interfacekey[INTERFACEKEY_STRING_A236].tokenname="STRING_A236";
	interfacekey[INTERFACEKEY_STRING_A237].tokenname="STRING_A237";
	interfacekey[INTERFACEKEY_STRING_A238].tokenname="STRING_A238";
	interfacekey[INTERFACEKEY_STRING_A239].tokenname="STRING_A239";
	interfacekey[INTERFACEKEY_STRING_A240].tokenname="STRING_A240";
	interfacekey[INTERFACEKEY_STRING_A241].tokenname="STRING_A241";
	interfacekey[INTERFACEKEY_STRING_A242].tokenname="STRING_A242";
	interfacekey[INTERFACEKEY_STRING_A243].tokenname="STRING_A243";
	interfacekey[INTERFACEKEY_STRING_A244].tokenname="STRING_A244";
	interfacekey[INTERFACEKEY_STRING_A245].tokenname="STRING_A245";
	interfacekey[INTERFACEKEY_STRING_A246].tokenname="STRING_A246";
	interfacekey[INTERFACEKEY_STRING_A247].tokenname="STRING_A247";
	interfacekey[INTERFACEKEY_STRING_A248].tokenname="STRING_A248";
	interfacekey[INTERFACEKEY_STRING_A249].tokenname="STRING_A249";
	interfacekey[INTERFACEKEY_STRING_A250].tokenname="STRING_A250";
	interfacekey[INTERFACEKEY_STRING_A251].tokenname="STRING_A251";
	interfacekey[INTERFACEKEY_STRING_A252].tokenname="STRING_A252";
	interfacekey[INTERFACEKEY_STRING_A253].tokenname="STRING_A253";
	interfacekey[INTERFACEKEY_STRING_A254].tokenname="STRING_A254";
	interfacekey[INTERFACEKEY_STRING_A255].tokenname="STRING_A255";
}

interfacest::~interfacest()
{
	//GO AHEAD
	while(view.child!=NULL)
		{
		removescreen(view.child);
		}
}

char interfacest::keypress(short key)
{
	if(key<0||key>=INTERFACEKEYNUM)return 0;

	if(interfacekey[key].ctrl!=ctrl)return 0;
	if(interfacekey[key].alt!=alt)return 0;

	if(c>='A'&&c<='Z'&&caps)
		{
		if(interfacekey[key].binding==c&&interfacekey[key].shift==(!shift))return 1;
		}
	else if(interfacekey[key].binding==c&&interfacekey[key].shift==shift)return 1;

	return 0;
}

void getstring_interfacechar(string &str,interfacekeyst &key)
{
	if(!gview.valid_held_key(key.binding))
		{
		str="Not Supported";
		return;
		}

	short ind=0;
	if(key.shift)ind++;
	if(key.ctrl)ind+=2;
	if(key.alt)ind+=4;
	if(!gview.display_string[key.binding][ind].empty())
		{
		str=gview.display_string[key.binding][ind];
		return;
		}

	str.erase();

	if(key.ctrl)str+="Ctrl+";
	if(key.alt)str+="Alt+";
	if(key.shift)str+="Shft+";
	switch(key.binding)
		{
		case VK_BACK:str+="Backspace";break;
		case VK_TAB:str+="Tab";break;
		case VK_CLEAR:str+="Clear";break;
		case VK_RETURN:str+="Enter";break;
		case VK_SHIFT:str+="Shift";break;
		case VK_CONTROL:str+="Ctrl";break;
		case VK_MENU:str+="Alt";break;
		case VK_PAUSE:str+="Pause";break;
		case VK_CAPITAL:str+="Caps";break;
		case VK_ESCAPE:str+="Escape";break;
		case VK_SPACE:str+="Space";break;
		case VK_PRIOR:str+="Page Up";break;
		case VK_NEXT:str+="Page Down";break;
		case VK_END:str+="End";break;
		case VK_HOME:str+="Home";break;
		case VK_LEFT:str+="Left";break;
		case VK_UP:str+="Up";break;
		case VK_RIGHT:str+="Right";break;
		case VK_DOWN:str+="Down";break;
		case VK_SELECT:str+="Select";break;
		case VK_PRINT:str+="Print";break;
		case VK_EXECUTE:str+="Execute";break;
		case VK_SNAPSHOT:str+="Print Screen";break;
		case VK_INSERT:str+="Insert";break;
		case VK_DELETE:str+="Delete";break;
		case VK_HELP:str+="Help";break;
		case 0x30://0
		case 0x31:
		case 0x32:
		case 0x33:
		case 0x34:
		case 0x35:
		case 0x36:
		case 0x37:
		case 0x38:
		case 0x39://9
			str+=key.binding;
			break;
		case 0x41://A
		case 0x42:
		case 0x43:
		case 0x44:
		case 0x45:
		case 0x46://F
		case 0x47:
		case 0x48:
		case 0x49:
		case 0x4A:
		case 0x4B://K
		case 0x4C:
		case 0x4D:
		case 0x4E:
		case 0x4F:
		case 0x50://P
		case 0x51:
		case 0x52:
		case 0x53:
		case 0x54:
		case 0x55://U
		case 0x56:
		case 0x57:
		case 0x58:
		case 0x59:
		case 0x5A://Z
			str+=(key.binding-'A')+'a';
			break;
		case VK_NUMPAD0:str+="Numpad 0";break;
		case VK_NUMPAD1:str+="Numpad 1";break;
		case VK_NUMPAD2:str+="Numpad 2";break;
		case VK_NUMPAD3:str+="Numpad 3";break;
		case VK_NUMPAD4:str+="Numpad 4";break;
		case VK_NUMPAD5:str+="Numpad 5";break;
		case VK_NUMPAD6:str+="Numpad 6";break;
		case VK_NUMPAD7:str+="Numpad 7";break;
		case VK_NUMPAD8:str+="Numpad 8";break;
		case VK_NUMPAD9:str+="Numpad 9";break;
		case VK_SEPARATOR:str+="Separator";break;
		case VK_SUBTRACT:str+="Subtract";break;
		case VK_ADD:str+="Add";break;
		case VK_MULTIPLY:str+="Multiply";break;
		case VK_DECIMAL:str+="Decimal";break;
		case VK_DIVIDE:str+="Divide";break;
		case VK_F1:str+="F1";break;
		case VK_F2:str+="F2";break;
		case VK_F3:str+="F3";break;
		case VK_F4:str+="F4";break;
		case VK_F5:str+="F5";break;
		case VK_F6:str+="F6";break;
		case VK_F7:str+="F7";break;
		case VK_F8:str+="F8";break;
		case VK_F9:str+="F9";break;
		case VK_F10:str+="F10";break;
		case VK_F11:str+="F11";break;
		case VK_F12:str+="F12";break;
		case VK_F13:str+="F13";break;
		case VK_F14:str+="F14";break;
		case VK_F15:str+="F15";break;
		case VK_F16:str+="F16";break;
		case VK_F17:str+="F17";break;
		case VK_F18:str+="F18";break;
		case VK_F19:str+="F19";break;
		case VK_F20:str+="F20";break;
		case VK_F21:str+="F21";break;
		case VK_F22:str+="F22";break;
		case VK_F23:str+="F23";break;
		case VK_F24:str+="F24";break;
		case VK_NUMLOCK:str+="Numlock";break;
		case VK_SCROLL:str+="Scroll";break;
		case VK_LSHIFT:str+="L Shift";break;
		case VK_RSHIFT:str+="R Shift";break;
		case VK_LCONTROL:str+="L Control";break;
		case VK_RCONTROL:str+="R Control";break;
		case VK_LMENU:str+="L Menu";break;
		case VK_RMENU:str+="R Menu";break;
		case 0xBA:str+="Key BA";break;
		case 0xBB:str+="Plus";break;
		case 0xBC:str+="Comma";break;
		case 0xBD:str+="Minus";break;
		case 0xBE:str+="Period";break;
		case 0xBF:str+="Key BF";break;
		case 0xC0:str+="Key C0";break;
		case 0xDB:str+="Key DB";break;
		case 0xDC:str+="Key DC";break;
		case 0xDD:str+="Key DD";break;
		case 0xDE:str+="Key DE";break;
		case 0xDF:str+="Key DF";break;
		case 0xE1:str+="Key E1";break;
		case 0xE2:str+="Key E2";break;
		case 0xE3:str+="Key E3";break;
		case 0xE4:str+="Key E4";break;
		case 0xE9:str+="Key E9";break;
		case 0xEA:str+="Key EA";break;
		case 0xEB:str+="Key EB";break;
		case 0xEC:str+="Key EC";break;
		case 0xED:str+="Key ED";break;
		case 0xEE:str+="Key EE";break;
		case 0xEF:str+="Key EF";break;
		case 0xF1:str+="Key F1";break;
		case 0xF2:str+="Key F2";break;
		case 0xF3:str+="Key F3";break;
		case 0xF4:str+="Key F4";break;
		case 0xF5:str+="Key F5";break;
		case 0x15:str+="Key Hangul/Kana";break;
		case 0x17:str+="Key Junja";break;
		case 0x18:str+="Key Final";break;
		case 0x19:str+="Key Hanja/Kanji";break;
		case 0x1C:str+="Key Convert";break;
		case 0x1D:str+="Key Nonconvert";break;
		case 0x1E:str+="Key Accept";break;
		case 0x1F:str+="Key Mode Change";break;
		case 0x92:str+="Key 92";break;
		case 0x93:str+="Key 93";break;
		case 0x94:str+="Key 94";break;
		case 0x95:str+="Key 95";break;
		case 0x96:str+="Key 96";break;
		default:str="Not Supported";break;
		}
}

void getstring_interfacechar_save(string &str,interfacekeyst &key)
{
	if(!gview.valid_held_key(key.binding))
		{
		str="NOT_SUPPORTED";
		return;
		}

	str.erase();

	if(key.ctrl)str+="CTRL+";
	if(key.alt)str+="ALT+";
	if(key.shift)str+="SHIFT+";
	switch(key.binding)
		{
		case VK_BACK:str+="BACKSPACE";break;
		case VK_TAB:str+="TAB";break;
		case VK_CLEAR:str+="CLEAR";break;
		case VK_RETURN:str+="ENTER";break;
		case VK_SHIFT:str+="SHIFT";break;
		case VK_CONTROL:str+="CTRL";break;
		case VK_MENU:str+="ALT";break;
		case VK_PAUSE:str+="PAUSE";break;
		case VK_CAPITAL:str+="CAPS";break;
		case VK_ESCAPE:str+="ESCAPE";break;
		case VK_SPACE:str+="SPACE";break;
		case VK_PRIOR:str+="PAGEUP";break;
		case VK_NEXT:str+="PAGEDOWN";break;
		case VK_END:str+="END";break;
		case VK_HOME:str+="HOME";break;
		case VK_LEFT:str+="LEFT";break;
		case VK_UP:str+="UP";break;
		case VK_RIGHT:str+="RIGHT";break;
		case VK_DOWN:str+="DOWN";break;
		case VK_SELECT:str+="SELECT";break;
		case VK_PRINT:str+="PRINT";break;
		case VK_EXECUTE:str+="EXECUTE";break;
		case VK_SNAPSHOT:str+="PRINTSCREEN";break;
		case VK_INSERT:str+="INSERT";break;
		case VK_DELETE:str+="DELETE";break;
		case VK_HELP:str+="HELP";break;
		case 0x30://0
		case 0x31:
		case 0x32:
		case 0x33:
		case 0x34:
		case 0x35:
		case 0x36:
		case 0x37:
		case 0x38:
		case 0x39://9
		case 0x41://A
		case 0x42:
		case 0x43:
		case 0x44:
		case 0x45:
		case 0x46://F
		case 0x47:
		case 0x48:
		case 0x49:
		case 0x4A:
		case 0x4B://K
		case 0x4C:
		case 0x4D:
		case 0x4E:
		case 0x4F:
		case 0x50://P
		case 0x51:
		case 0x52:
		case 0x53:
		case 0x54:
		case 0x55://U
		case 0x56:
		case 0x57:
		case 0x58:
		case 0x59:
		case 0x5A://Z
			str+=key.binding;
			break;
		case VK_NUMPAD0:str+="NUMPAD0";break;
		case VK_NUMPAD1:str+="NUMPAD1";break;
		case VK_NUMPAD2:str+="NUMPAD2";break;
		case VK_NUMPAD3:str+="NUMPAD3";break;
		case VK_NUMPAD4:str+="NUMPAD4";break;
		case VK_NUMPAD5:str+="NUMPAD5";break;
		case VK_NUMPAD6:str+="NUMPAD6";break;
		case VK_NUMPAD7:str+="NUMPAD7";break;
		case VK_NUMPAD8:str+="NUMPAD8";break;
		case VK_NUMPAD9:str+="NUMPAD9";break;
		case VK_SEPARATOR:str+="SEPARATOR";break;
		case VK_SUBTRACT:str+="SUBTRACT";break;
		case VK_ADD:str+="ADD";break;
		case VK_MULTIPLY:str+="MULTIPLY";break;
		case VK_DECIMAL:str+="DECIMAL";break;
		case VK_DIVIDE:str+="DIVIDE";break;
		case VK_F1:str+="F1";break;
		case VK_F2:str+="F2";break;
		case VK_F3:str+="F3";break;
		case VK_F4:str+="F4";break;
		case VK_F5:str+="F5";break;
		case VK_F6:str+="F6";break;
		case VK_F7:str+="F7";break;
		case VK_F8:str+="F8";break;
		case VK_F9:str+="F9";break;
		case VK_F10:str+="F10";break;
		case VK_F11:str+="F11";break;
		case VK_F12:str+="F12";break;
		case VK_F13:str+="F13";break;
		case VK_F14:str+="F14";break;
		case VK_F15:str+="F15";break;
		case VK_F16:str+="F16";break;
		case VK_F17:str+="F17";break;
		case VK_F18:str+="F18";break;
		case VK_F19:str+="F19";break;
		case VK_F20:str+="F20";break;
		case VK_F21:str+="F21";break;
		case VK_F22:str+="F22";break;
		case VK_F23:str+="F23";break;
		case VK_F24:str+="F24";break;
		case VK_NUMLOCK:str+="NUMLOCK";break;
		case VK_SCROLL:str+="SCROLL";break;
		case VK_LSHIFT:str+="LSHIFT";break;
		case VK_RSHIFT:str+="RSHIFT";break;
		case VK_LCONTROL:str+="LCTRL";break;
		case VK_RCONTROL:str+="RCTRL";break;
		case VK_LMENU:str+="LMENU";break;
		case VK_RMENU:str+="RMENU";break;
		case 0xBA:str+="KEYBA";break;
		case 0xBB:str+="PLUS";break;
		case 0xBC:str+="COMMA";break;
		case 0xBD:str+="MINUS";break;
		case 0xBE:str+="PERIOD";break;
		case 0xBF:str+="KEYBF";break;
		case 0xC0:str+="KEYC0";break;
		case 0xDB:str+="KEYDB";break;
		case 0xDC:str+="KEYDC";break;
		case 0xDD:str+="KEYDD";break;
		case 0xDE:str+="KEYDE";break;
		case 0xDF:str+="KEYDF";break;
		case 0xE1:str+="KEYE1";break;
		case 0xE2:str+="KEYE2";break;
		case 0xE3:str+="KEYE3";break;
		case 0xE4:str+="KEYE4";break;
		case 0xE9:str+="KEYE9";break;
		case 0xEA:str+="KEYEA";break;
		case 0xEB:str+="KEYEB";break;
		case 0xEC:str+="KEYEC";break;
		case 0xED:str+="KEYED";break;
		case 0xEE:str+="KEYEE";break;
		case 0xEF:str+="KEYEF";break;
		case 0xF1:str+="KEYF1";break;
		case 0xF2:str+="KEYF2";break;
		case 0xF3:str+="KEYF3";break;
		case 0xF4:str+="KEYF4";break;
		case 0xF5:str+="KEYF5";break;
		case 0x15:str+="KEYHANGULKANA";break;
		case 0x17:str+="KEYJUNJA";break;
		case 0x18:str+="KEYFINAL";break;
		case 0x19:str+="KEYHANJAKANJI";break;
		case 0x1C:str+="KEYCONVERT";break;
		case 0x1D:str+="KEYNONCONVERT";break;
		case 0x1E:str+="KEYACCEPT";break;
		case 0x1F:str+="KEYMODECHANGE";break;
		case 0x92:str+="KEY92";break;
		case 0x93:str+="KEY93";break;
		case 0x94:str+="KEY94";break;
		case 0x95:str+="KEY95";break;
		case 0x96:str+="KEY96";break;
		default:str="NONE";break;
		}
}

void convertstring_interfacechar_save(string &str,interfacekeyst &key)
{
	if(str.length()==0)return;

	key.binding=0;
	key.shift=0;
	key.alt=0;
	key.ctrl=0;

	string::size_type wpos;
	string sr;

	sr="CTRL+";
	while ((wpos = str.find(sr)) != string::npos)
		{
		string str2="";
		str.replace(wpos,sr.size(),str2);
		key.ctrl=1;
		}
	sr="ALT+";
	while ((wpos = str.find(sr)) != string::npos)
		{
		string str2="";
		str.replace(wpos,sr.size(),str2);
		key.alt=1;
		}
	sr="SHIFT+";
	while ((wpos = str.find(sr)) != string::npos)
		{
		string str2="";
		str.replace(wpos,sr.size(),str2);
		key.shift=1;
		}

	if(!str.compare("BACKSPACE")){key.binding=VK_BACK;return;}
	if(!str.compare("TAB")){key.binding=VK_TAB;return;}
	if(!str.compare("CLEAR")){key.binding=VK_CLEAR;return;}
	if(!str.compare("ENTER")){key.binding=VK_RETURN;return;}
	if(!str.compare("SHIFT")){key.binding=VK_SHIFT;return;}
	if(!str.compare("CTRL")){key.binding=VK_CONTROL;return;}
	if(!str.compare("ALT")){key.binding=VK_MENU;return;}
	if(!str.compare("PAUSE")){key.binding=VK_PAUSE;return;}
	if(!str.compare("CAPS")){key.binding=VK_CAPITAL;return;}
	if(!str.compare("ESCAPE")){key.binding=VK_ESCAPE;return;}
	if(!str.compare("SPACE")){key.binding=VK_SPACE;return;}
	if(!str.compare("PAGEUP")){key.binding=VK_PRIOR;return;}
	if(!str.compare("PAGEDOWN")){key.binding=VK_NEXT;return;}
	if(!str.compare("END")){key.binding=VK_END;return;}
	if(!str.compare("HOME")){key.binding=VK_HOME;return;}
	if(!str.compare("LEFT")){key.binding=VK_LEFT;return;}
	if(!str.compare("UP")){key.binding=VK_UP;return;}
	if(!str.compare("RIGHT")){key.binding=VK_RIGHT;return;}
	if(!str.compare("DOWN")){key.binding=VK_DOWN;return;}
	if(!str.compare("SELECT")){key.binding=VK_SELECT;return;}
	if(!str.compare("PRINT")){key.binding=VK_PRINT;return;}
	if(!str.compare("EXECUTE")){key.binding=VK_EXECUTE;return;}
	if(!str.compare("PRINTSCREEN")){key.binding=VK_SNAPSHOT;return;}
	if(!str.compare("INSERT")){key.binding=VK_INSERT;return;}
	if(!str.compare("DELETE")){key.binding=VK_DELETE;return;}
	if(!str.compare("HELP")){key.binding=VK_HELP;return;}
	if(!str.compare("NUMPAD0")){key.binding=VK_NUMPAD0;return;}
	if(!str.compare("NUMPAD1")){key.binding=VK_NUMPAD1;return;}
	if(!str.compare("NUMPAD2")){key.binding=VK_NUMPAD2;return;}
	if(!str.compare("NUMPAD3")){key.binding=VK_NUMPAD3;return;}
	if(!str.compare("NUMPAD4")){key.binding=VK_NUMPAD4;return;}
	if(!str.compare("NUMPAD5")){key.binding=VK_NUMPAD5;return;}
	if(!str.compare("NUMPAD6")){key.binding=VK_NUMPAD6;return;}
	if(!str.compare("NUMPAD7")){key.binding=VK_NUMPAD7;return;}
	if(!str.compare("NUMPAD8")){key.binding=VK_NUMPAD8;return;}
	if(!str.compare("NUMPAD9")){key.binding=VK_NUMPAD9;return;}
	if(!str.compare("SEPARATOR")){key.binding=VK_SEPARATOR;return;}
	if(!str.compare("SUBTRACT")){key.binding=VK_SUBTRACT;return;}
	if(!str.compare("ADD")){key.binding=VK_ADD;return;}
	if(!str.compare("MULTIPLY")){key.binding=VK_MULTIPLY;return;}
	if(!str.compare("DECIMAL")){key.binding=VK_DECIMAL;return;}
	if(!str.compare("DIVIDE")){key.binding=VK_DIVIDE;return;}
	if(!str.compare("F1")){key.binding=VK_F1;return;}
	if(!str.compare("F2")){key.binding=VK_F2;return;}
	if(!str.compare("F3")){key.binding=VK_F3;return;}
	if(!str.compare("F4")){key.binding=VK_F4;return;}
	if(!str.compare("F5")){key.binding=VK_F5;return;}
	if(!str.compare("F6")){key.binding=VK_F6;return;}
	if(!str.compare("F7")){key.binding=VK_F7;return;}
	if(!str.compare("F8")){key.binding=VK_F8;return;}
	if(!str.compare("F9")){key.binding=VK_F9;return;}
	if(!str.compare("F10")){key.binding=VK_F10;return;}
	if(!str.compare("F11")){key.binding=VK_F11;return;}
	if(!str.compare("F12")){key.binding=VK_F12;return;}
	if(!str.compare("F13")){key.binding=VK_F13;return;}
	if(!str.compare("F14")){key.binding=VK_F14;return;}
	if(!str.compare("F15")){key.binding=VK_F15;return;}
	if(!str.compare("F16")){key.binding=VK_F16;return;}
	if(!str.compare("F17")){key.binding=VK_F17;return;}
	if(!str.compare("F18")){key.binding=VK_F18;return;}
	if(!str.compare("F19")){key.binding=VK_F19;return;}
	if(!str.compare("F20")){key.binding=VK_F20;return;}
	if(!str.compare("F21")){key.binding=VK_F21;return;}
	if(!str.compare("F22")){key.binding=VK_F22;return;}
	if(!str.compare("F23")){key.binding=VK_F23;return;}
	if(!str.compare("F24")){key.binding=VK_F24;return;}
	if(!str.compare("NUMLOCK")){key.binding=VK_NUMLOCK;return;}
	if(!str.compare("SCROLL")){key.binding=VK_SCROLL;return;}
	if(!str.compare("LSHIFT")){key.binding=VK_LSHIFT;return;}
	if(!str.compare("RSHIFT")){key.binding=VK_RSHIFT;return;}
	if(!str.compare("LCTRL")){key.binding=VK_LCONTROL;return;}
	if(!str.compare("RCTRL")){key.binding=VK_RCONTROL;return;}
	if(!str.compare("LMENU")){key.binding=VK_LMENU;return;}
	if(!str.compare("RMENU")){key.binding=VK_RMENU;return;}
	if(!str.compare("KEYBA")){key.binding=0xBA;return;}
	if(!str.compare("PLUS")){key.binding=0xBB;return;}
	if(!str.compare("COMMA")){key.binding=0xBC;return;}
	if(!str.compare("MINUS")){key.binding=0xBD;return;}
	if(!str.compare("PERIOD")){key.binding=0xBE;return;}
	if(!str.compare("KEYBF")){key.binding=0xBF;return;}
	if(!str.compare("KEYC0")){key.binding=0xC0;return;}
	if(!str.compare("KEYDB")){key.binding=0xDB;return;}
	if(!str.compare("KEYDC")){key.binding=0xDC;return;}
	if(!str.compare("KEYDD")){key.binding=0xDD;return;}
	if(!str.compare("KEYDE")){key.binding=0xDE;return;}
	if(!str.compare("KEYDF")){key.binding=0xDF;return;}
	if(!str.compare("KEYE1")){key.binding=0xE1;return;}
	if(!str.compare("KEYE2")){key.binding=0xE2;return;}
	if(!str.compare("KEYE3")){key.binding=0xE3;return;}
	if(!str.compare("KEYE4")){key.binding=0xE4;return;}
	if(!str.compare("KEYE9")){key.binding=0xE9;return;}
	if(!str.compare("KEYEA")){key.binding=0xEA;return;}
	if(!str.compare("KEYEB")){key.binding=0xEB;return;}
	if(!str.compare("KEYEC")){key.binding=0xEC;return;}
	if(!str.compare("KEYED")){key.binding=0xED;return;}
	if(!str.compare("KEYEE")){key.binding=0xEE;return;}
	if(!str.compare("KEYEF")){key.binding=0xEF;return;}
	if(!str.compare("KEYF1")){key.binding=0xF1;return;}
	if(!str.compare("KEYF2")){key.binding=0xF2;return;}
	if(!str.compare("KEYF3")){key.binding=0xF3;return;}
	if(!str.compare("KEYF4")){key.binding=0xF4;return;}
	if(!str.compare("KEYF5")){key.binding=0xF5;return;}
	if(!str.compare("KEYHANGULKANA")){key.binding=0x15;return;}
	if(!str.compare("KEYJUNJA")){key.binding=0x17;return;}
	if(!str.compare("KEYFINAL")){key.binding=0x18;return;}
	if(!str.compare("KEYHANJAKANJI")){key.binding=0x19;return;}
	if(!str.compare("KEYCONVERT")){key.binding=0x1C;return;}
	if(!str.compare("KEYNONCONVERT")){key.binding=0x1D;return;}
	if(!str.compare("KEYACCEPT")){key.binding=0x1E;return;}
	if(!str.compare("KEYMODECHANGE")){key.binding=0x1F;return;}
	if(!str.compare("KEY92")){key.binding=0x92;return;}
	if(!str.compare("KEY93")){key.binding=0x93;return;}
	if(!str.compare("KEY94")){key.binding=0x94;return;}
	if(!str.compare("KEY95")){key.binding=0x95;return;}
	if(!str.compare("KEY96")){key.binding=0x96;return;}

	if(str.compare("NONE")&&str.compare("NOT_SUPPORTED"))
		{
		if(str[0]>='0'&&str[0]<='9')key.binding=str[0];
		if(str[0]>='A'&&str[0]<='Z')key.binding=str[0];
		return;
		}
}

viewscreen_optionst *viewscreen_optionst::create(char pushtype,viewscreenst *scr)
{
	viewscreen_optionst *newv=new viewscreen_optionst();
	gview.addscreen(newv,pushtype,scr);

	return newv;
}

viewscreen_optionst::viewscreen_optionst()
{
	selected=0;
}

void viewscreen_optionst::view()
{
	enabler.flag&=~ENABLERFLAG_MAXFPS;
	enabler.qprate=init.display.dwarf_frame_rate;

	drawborder("  Options  ");

	long i;
	for(i=0;i<MAINMENU_OPTIONNUM;i++)
		{
		if(i==selected)gps.changecolor(7,0,1);
		else gps.changecolor(7,0,0);

		gps.locate(i+2,30);

		switch(i)
			{
			case MAINMENU_OPTION_RETURN:
				gps.addst("Return to Game");
				break;
			case MAINMENU_OPTION_KEYBINDINGS:
				gps.addst("Key Bindings");
				break;
			case MAINMENU_OPTION_QUIT:
				gps.addst("Quit");
				break;
			}
		}

	gps.renewscreen();

	if(gview.keypress(INTERFACEKEY_SELECT))
		{
		switch(selected)
			{
			case MAINMENU_OPTION_RETURN:
				breakdownlevel=INTERFACE_BREAKDOWN_STOPSCREEN;
				break;
			case MAINMENU_OPTION_KEYBINDINGS:
				viewscreen_keybindingsst::create(INTERFACE_PUSH_AT_BACK);
				break;
			case MAINMENU_OPTION_QUIT:
				breakdownlevel=INTERFACE_BREAKDOWN_QUIT;
				break;
			}

		return;
		}

	standardscrolling(selected,0,MAINMENU_OPTIONNUM-1,21);

	if(gview.keypress(INTERFACEKEY_LEAVESCREEN))
		{
		breakdownlevel=INTERFACE_BREAKDOWN_STOPSCREEN;
		return;
		}
}


viewscreen_keybindingsst *viewscreen_keybindingsst::create(char pushtype,viewscreenst *scr)
{
	viewscreen_keybindingsst *newv=new viewscreen_keybindingsst();
	gview.addscreen(newv,pushtype,scr);

	return newv;
}

viewscreen_keybindingsst::viewscreen_keybindingsst()
{
	selected=0;
	binding=0;

	allowed_key.push_back(INTERFACEKEY_SELECT);
	allowed_key.push_back(INTERFACEKEY_DESELECT);
	allowed_key.push_back(INTERFACEKEY_SELECT_ALL);
	allowed_key.push_back(INTERFACEKEY_DESELECT_ALL);
	allowed_key.push_back(INTERFACEKEY_LEAVESCREEN);
	allowed_key.push_back(INTERFACEKEY_LEAVESCREEN_TEXT);
	allowed_key.push_back(INTERFACEKEY_LEAVESCREEN_ALL);
	allowed_key.push_back(INTERFACEKEY_OPTIONS);
	allowed_key.push_back(INTERFACEKEY_OPTION_EXPORT);
	allowed_key.push_back(INTERFACEKEY_MENU_CONFIRM);
	allowed_key.push_back(INTERFACEKEY_SAVE_BINDINGS);
	allowed_key.push_back(INTERFACEKEY_CHANGE_BINDINGS);
	allowed_key.push_back(INTERFACEKEY_HELP);
	allowed_key.push_back(INTERFACEKEY_TOGGLE_FULLSCREEN);
	allowed_key.push_back(INTERFACEKEY_MOVIES);
	allowed_key.push_back(INTERFACEKEY_MOVIE_RECORD);
	allowed_key.push_back(INTERFACEKEY_MOVIE_PLAY);
	allowed_key.push_back(INTERFACEKEY_MOVIE_SAVE);
	allowed_key.push_back(INTERFACEKEY_MOVIE_LOAD);
	allowed_key.push_back(INTERFACEKEY_CHANGETAB);
	allowed_key.push_back(INTERFACEKEY_STANDARDSCROLL_UP);
	allowed_key.push_back(INTERFACEKEY_STANDARDSCROLL_DOWN);
	allowed_key.push_back(INTERFACEKEY_STANDARDSCROLL_LEFT);
	allowed_key.push_back(INTERFACEKEY_STANDARDSCROLL_RIGHT);
	allowed_key.push_back(INTERFACEKEY_STANDARDSCROLL_PAGEUP);
	allowed_key.push_back(INTERFACEKEY_STANDARDSCROLL_PAGEDOWN);
	allowed_key.push_back(INTERFACEKEY_SECONDSCROLL_UP);
	allowed_key.push_back(INTERFACEKEY_SECONDSCROLL_DOWN);
	allowed_key.push_back(INTERFACEKEY_SECONDSCROLL_PAGEUP);
	allowed_key.push_back(INTERFACEKEY_SECONDSCROLL_PAGEDOWN);
	allowed_key.push_back(INTERFACEKEY_CURSOR_UP);
	allowed_key.push_back(INTERFACEKEY_CURSOR_DOWN);
	allowed_key.push_back(INTERFACEKEY_CURSOR_LEFT);
	allowed_key.push_back(INTERFACEKEY_CURSOR_RIGHT);
	allowed_key.push_back(INTERFACEKEY_CURSOR_UPLEFT);
	allowed_key.push_back(INTERFACEKEY_CURSOR_UPRIGHT);
	allowed_key.push_back(INTERFACEKEY_CURSOR_DOWNLEFT);
	allowed_key.push_back(INTERFACEKEY_CURSOR_DOWNRIGHT);
	allowed_key.push_back(INTERFACEKEY_CURSOR_UP_FAST);
	allowed_key.push_back(INTERFACEKEY_CURSOR_DOWN_FAST);
	allowed_key.push_back(INTERFACEKEY_CURSOR_LEFT_FAST);
	allowed_key.push_back(INTERFACEKEY_CURSOR_RIGHT_FAST);
	allowed_key.push_back(INTERFACEKEY_CURSOR_UPLEFT_FAST);
	allowed_key.push_back(INTERFACEKEY_CURSOR_UPRIGHT_FAST);
	allowed_key.push_back(INTERFACEKEY_CURSOR_DOWNLEFT_FAST);
	allowed_key.push_back(INTERFACEKEY_CURSOR_DOWNRIGHT_FAST);
	allowed_key.push_back(INTERFACEKEY_CURSOR_UP_Z);
	allowed_key.push_back(INTERFACEKEY_CURSOR_DOWN_Z);
	allowed_key.push_back(INTERFACEKEY_CURSOR_UP_Z_AUX);
	allowed_key.push_back(INTERFACEKEY_CURSOR_DOWN_Z_AUX);

	allowed_key.push_back(INTERFACEKEY_STRING_A000);
	allowed_key.push_back(INTERFACEKEY_STRING_A001);
	allowed_key.push_back(INTERFACEKEY_STRING_A002);
	allowed_key.push_back(INTERFACEKEY_STRING_A003);
	allowed_key.push_back(INTERFACEKEY_STRING_A004);
	allowed_key.push_back(INTERFACEKEY_STRING_A005);
	allowed_key.push_back(INTERFACEKEY_STRING_A006);
	allowed_key.push_back(INTERFACEKEY_STRING_A007);
	allowed_key.push_back(INTERFACEKEY_STRING_A008);
	allowed_key.push_back(INTERFACEKEY_STRING_A009);
	allowed_key.push_back(INTERFACEKEY_STRING_A010);
	allowed_key.push_back(INTERFACEKEY_STRING_A011);
	allowed_key.push_back(INTERFACEKEY_STRING_A012);
	allowed_key.push_back(INTERFACEKEY_STRING_A013);
	allowed_key.push_back(INTERFACEKEY_STRING_A014);
	allowed_key.push_back(INTERFACEKEY_STRING_A015);
	allowed_key.push_back(INTERFACEKEY_STRING_A016);
	allowed_key.push_back(INTERFACEKEY_STRING_A017);
	allowed_key.push_back(INTERFACEKEY_STRING_A018);
	allowed_key.push_back(INTERFACEKEY_STRING_A019);
	allowed_key.push_back(INTERFACEKEY_STRING_A020);
	allowed_key.push_back(INTERFACEKEY_STRING_A021);
	allowed_key.push_back(INTERFACEKEY_STRING_A022);
	allowed_key.push_back(INTERFACEKEY_STRING_A023);
	allowed_key.push_back(INTERFACEKEY_STRING_A024);
	allowed_key.push_back(INTERFACEKEY_STRING_A025);
	allowed_key.push_back(INTERFACEKEY_STRING_A026);
	allowed_key.push_back(INTERFACEKEY_STRING_A027);
	allowed_key.push_back(INTERFACEKEY_STRING_A028);
	allowed_key.push_back(INTERFACEKEY_STRING_A029);
	allowed_key.push_back(INTERFACEKEY_STRING_A030);
	allowed_key.push_back(INTERFACEKEY_STRING_A031);
	allowed_key.push_back(INTERFACEKEY_STRING_A032);
	allowed_key.push_back(INTERFACEKEY_STRING_A033);
	allowed_key.push_back(INTERFACEKEY_STRING_A034);
	allowed_key.push_back(INTERFACEKEY_STRING_A035);
	allowed_key.push_back(INTERFACEKEY_STRING_A036);
	allowed_key.push_back(INTERFACEKEY_STRING_A037);
	allowed_key.push_back(INTERFACEKEY_STRING_A038);
	allowed_key.push_back(INTERFACEKEY_STRING_A039);
	allowed_key.push_back(INTERFACEKEY_STRING_A040);
	allowed_key.push_back(INTERFACEKEY_STRING_A041);
	allowed_key.push_back(INTERFACEKEY_STRING_A042);
	allowed_key.push_back(INTERFACEKEY_STRING_A043);
	allowed_key.push_back(INTERFACEKEY_STRING_A044);
	allowed_key.push_back(INTERFACEKEY_STRING_A045);
	allowed_key.push_back(INTERFACEKEY_STRING_A046);
	allowed_key.push_back(INTERFACEKEY_STRING_A047);
	allowed_key.push_back(INTERFACEKEY_STRING_A048);
	allowed_key.push_back(INTERFACEKEY_STRING_A049);
	allowed_key.push_back(INTERFACEKEY_STRING_A050);
	allowed_key.push_back(INTERFACEKEY_STRING_A051);
	allowed_key.push_back(INTERFACEKEY_STRING_A052);
	allowed_key.push_back(INTERFACEKEY_STRING_A053);
	allowed_key.push_back(INTERFACEKEY_STRING_A054);
	allowed_key.push_back(INTERFACEKEY_STRING_A055);
	allowed_key.push_back(INTERFACEKEY_STRING_A056);
	allowed_key.push_back(INTERFACEKEY_STRING_A057);
	allowed_key.push_back(INTERFACEKEY_STRING_A058);
	allowed_key.push_back(INTERFACEKEY_STRING_A059);
	allowed_key.push_back(INTERFACEKEY_STRING_A060);
	allowed_key.push_back(INTERFACEKEY_STRING_A061);
	allowed_key.push_back(INTERFACEKEY_STRING_A062);
	allowed_key.push_back(INTERFACEKEY_STRING_A063);
	allowed_key.push_back(INTERFACEKEY_STRING_A064);
	allowed_key.push_back(INTERFACEKEY_STRING_A065);
	allowed_key.push_back(INTERFACEKEY_STRING_A066);
	allowed_key.push_back(INTERFACEKEY_STRING_A067);
	allowed_key.push_back(INTERFACEKEY_STRING_A068);
	allowed_key.push_back(INTERFACEKEY_STRING_A069);
	allowed_key.push_back(INTERFACEKEY_STRING_A070);
	allowed_key.push_back(INTERFACEKEY_STRING_A071);
	allowed_key.push_back(INTERFACEKEY_STRING_A072);
	allowed_key.push_back(INTERFACEKEY_STRING_A073);
	allowed_key.push_back(INTERFACEKEY_STRING_A074);
	allowed_key.push_back(INTERFACEKEY_STRING_A075);
	allowed_key.push_back(INTERFACEKEY_STRING_A076);
	allowed_key.push_back(INTERFACEKEY_STRING_A077);
	allowed_key.push_back(INTERFACEKEY_STRING_A078);
	allowed_key.push_back(INTERFACEKEY_STRING_A079);
	allowed_key.push_back(INTERFACEKEY_STRING_A080);
	allowed_key.push_back(INTERFACEKEY_STRING_A081);
	allowed_key.push_back(INTERFACEKEY_STRING_A082);
	allowed_key.push_back(INTERFACEKEY_STRING_A083);
	allowed_key.push_back(INTERFACEKEY_STRING_A084);
	allowed_key.push_back(INTERFACEKEY_STRING_A085);
	allowed_key.push_back(INTERFACEKEY_STRING_A086);
	allowed_key.push_back(INTERFACEKEY_STRING_A087);
	allowed_key.push_back(INTERFACEKEY_STRING_A088);
	allowed_key.push_back(INTERFACEKEY_STRING_A089);
	allowed_key.push_back(INTERFACEKEY_STRING_A090);
	allowed_key.push_back(INTERFACEKEY_STRING_A091);
	allowed_key.push_back(INTERFACEKEY_STRING_A092);
	allowed_key.push_back(INTERFACEKEY_STRING_A093);
	allowed_key.push_back(INTERFACEKEY_STRING_A094);
	allowed_key.push_back(INTERFACEKEY_STRING_A095);
	allowed_key.push_back(INTERFACEKEY_STRING_A096);
	allowed_key.push_back(INTERFACEKEY_STRING_A097);
	allowed_key.push_back(INTERFACEKEY_STRING_A098);
	allowed_key.push_back(INTERFACEKEY_STRING_A099);
	allowed_key.push_back(INTERFACEKEY_STRING_A100);
	allowed_key.push_back(INTERFACEKEY_STRING_A101);
	allowed_key.push_back(INTERFACEKEY_STRING_A102);
	allowed_key.push_back(INTERFACEKEY_STRING_A103);
	allowed_key.push_back(INTERFACEKEY_STRING_A104);
	allowed_key.push_back(INTERFACEKEY_STRING_A105);
	allowed_key.push_back(INTERFACEKEY_STRING_A106);
	allowed_key.push_back(INTERFACEKEY_STRING_A107);
	allowed_key.push_back(INTERFACEKEY_STRING_A108);
	allowed_key.push_back(INTERFACEKEY_STRING_A109);
	allowed_key.push_back(INTERFACEKEY_STRING_A110);
	allowed_key.push_back(INTERFACEKEY_STRING_A111);
	allowed_key.push_back(INTERFACEKEY_STRING_A112);
	allowed_key.push_back(INTERFACEKEY_STRING_A113);
	allowed_key.push_back(INTERFACEKEY_STRING_A114);
	allowed_key.push_back(INTERFACEKEY_STRING_A115);
	allowed_key.push_back(INTERFACEKEY_STRING_A116);
	allowed_key.push_back(INTERFACEKEY_STRING_A117);
	allowed_key.push_back(INTERFACEKEY_STRING_A118);
	allowed_key.push_back(INTERFACEKEY_STRING_A119);
	allowed_key.push_back(INTERFACEKEY_STRING_A120);
	allowed_key.push_back(INTERFACEKEY_STRING_A121);
	allowed_key.push_back(INTERFACEKEY_STRING_A122);
	allowed_key.push_back(INTERFACEKEY_STRING_A123);
	allowed_key.push_back(INTERFACEKEY_STRING_A124);
	allowed_key.push_back(INTERFACEKEY_STRING_A125);
	allowed_key.push_back(INTERFACEKEY_STRING_A126);
	allowed_key.push_back(INTERFACEKEY_STRING_A127);
	allowed_key.push_back(INTERFACEKEY_STRING_A128);
	allowed_key.push_back(INTERFACEKEY_STRING_A129);
	allowed_key.push_back(INTERFACEKEY_STRING_A130);
	allowed_key.push_back(INTERFACEKEY_STRING_A131);
	allowed_key.push_back(INTERFACEKEY_STRING_A132);
	allowed_key.push_back(INTERFACEKEY_STRING_A133);
	allowed_key.push_back(INTERFACEKEY_STRING_A134);
	allowed_key.push_back(INTERFACEKEY_STRING_A135);
	allowed_key.push_back(INTERFACEKEY_STRING_A136);
	allowed_key.push_back(INTERFACEKEY_STRING_A137);
	allowed_key.push_back(INTERFACEKEY_STRING_A138);
	allowed_key.push_back(INTERFACEKEY_STRING_A139);
	allowed_key.push_back(INTERFACEKEY_STRING_A140);
	allowed_key.push_back(INTERFACEKEY_STRING_A141);
	allowed_key.push_back(INTERFACEKEY_STRING_A142);
	allowed_key.push_back(INTERFACEKEY_STRING_A143);
	allowed_key.push_back(INTERFACEKEY_STRING_A144);
	allowed_key.push_back(INTERFACEKEY_STRING_A145);
	allowed_key.push_back(INTERFACEKEY_STRING_A146);
	allowed_key.push_back(INTERFACEKEY_STRING_A147);
	allowed_key.push_back(INTERFACEKEY_STRING_A148);
	allowed_key.push_back(INTERFACEKEY_STRING_A149);
	allowed_key.push_back(INTERFACEKEY_STRING_A150);
	allowed_key.push_back(INTERFACEKEY_STRING_A151);
	allowed_key.push_back(INTERFACEKEY_STRING_A152);
	allowed_key.push_back(INTERFACEKEY_STRING_A153);
	allowed_key.push_back(INTERFACEKEY_STRING_A154);
	allowed_key.push_back(INTERFACEKEY_STRING_A155);
	allowed_key.push_back(INTERFACEKEY_STRING_A156);
	allowed_key.push_back(INTERFACEKEY_STRING_A157);
	allowed_key.push_back(INTERFACEKEY_STRING_A158);
	allowed_key.push_back(INTERFACEKEY_STRING_A159);
	allowed_key.push_back(INTERFACEKEY_STRING_A160);
	allowed_key.push_back(INTERFACEKEY_STRING_A161);
	allowed_key.push_back(INTERFACEKEY_STRING_A162);
	allowed_key.push_back(INTERFACEKEY_STRING_A163);
	allowed_key.push_back(INTERFACEKEY_STRING_A164);
	allowed_key.push_back(INTERFACEKEY_STRING_A165);
	allowed_key.push_back(INTERFACEKEY_STRING_A166);
	allowed_key.push_back(INTERFACEKEY_STRING_A167);
	allowed_key.push_back(INTERFACEKEY_STRING_A168);
	allowed_key.push_back(INTERFACEKEY_STRING_A169);
	allowed_key.push_back(INTERFACEKEY_STRING_A170);
	allowed_key.push_back(INTERFACEKEY_STRING_A171);
	allowed_key.push_back(INTERFACEKEY_STRING_A172);
	allowed_key.push_back(INTERFACEKEY_STRING_A173);
	allowed_key.push_back(INTERFACEKEY_STRING_A174);
	allowed_key.push_back(INTERFACEKEY_STRING_A175);
	allowed_key.push_back(INTERFACEKEY_STRING_A176);
	allowed_key.push_back(INTERFACEKEY_STRING_A177);
	allowed_key.push_back(INTERFACEKEY_STRING_A178);
	allowed_key.push_back(INTERFACEKEY_STRING_A179);
	allowed_key.push_back(INTERFACEKEY_STRING_A180);
	allowed_key.push_back(INTERFACEKEY_STRING_A181);
	allowed_key.push_back(INTERFACEKEY_STRING_A182);
	allowed_key.push_back(INTERFACEKEY_STRING_A183);
	allowed_key.push_back(INTERFACEKEY_STRING_A184);
	allowed_key.push_back(INTERFACEKEY_STRING_A185);
	allowed_key.push_back(INTERFACEKEY_STRING_A186);
	allowed_key.push_back(INTERFACEKEY_STRING_A187);
	allowed_key.push_back(INTERFACEKEY_STRING_A188);
	allowed_key.push_back(INTERFACEKEY_STRING_A189);
	allowed_key.push_back(INTERFACEKEY_STRING_A190);
	allowed_key.push_back(INTERFACEKEY_STRING_A191);
	allowed_key.push_back(INTERFACEKEY_STRING_A192);
	allowed_key.push_back(INTERFACEKEY_STRING_A193);
	allowed_key.push_back(INTERFACEKEY_STRING_A194);
	allowed_key.push_back(INTERFACEKEY_STRING_A195);
	allowed_key.push_back(INTERFACEKEY_STRING_A196);
	allowed_key.push_back(INTERFACEKEY_STRING_A197);
	allowed_key.push_back(INTERFACEKEY_STRING_A198);
	allowed_key.push_back(INTERFACEKEY_STRING_A199);
	allowed_key.push_back(INTERFACEKEY_STRING_A200);
	allowed_key.push_back(INTERFACEKEY_STRING_A201);
	allowed_key.push_back(INTERFACEKEY_STRING_A202);
	allowed_key.push_back(INTERFACEKEY_STRING_A203);
	allowed_key.push_back(INTERFACEKEY_STRING_A204);
	allowed_key.push_back(INTERFACEKEY_STRING_A205);
	allowed_key.push_back(INTERFACEKEY_STRING_A206);
	allowed_key.push_back(INTERFACEKEY_STRING_A207);
	allowed_key.push_back(INTERFACEKEY_STRING_A208);
	allowed_key.push_back(INTERFACEKEY_STRING_A209);
	allowed_key.push_back(INTERFACEKEY_STRING_A210);
	allowed_key.push_back(INTERFACEKEY_STRING_A211);
	allowed_key.push_back(INTERFACEKEY_STRING_A212);
	allowed_key.push_back(INTERFACEKEY_STRING_A213);
	allowed_key.push_back(INTERFACEKEY_STRING_A214);
	allowed_key.push_back(INTERFACEKEY_STRING_A215);
	allowed_key.push_back(INTERFACEKEY_STRING_A216);
	allowed_key.push_back(INTERFACEKEY_STRING_A217);
	allowed_key.push_back(INTERFACEKEY_STRING_A218);
	allowed_key.push_back(INTERFACEKEY_STRING_A219);
	allowed_key.push_back(INTERFACEKEY_STRING_A220);
	allowed_key.push_back(INTERFACEKEY_STRING_A221);
	allowed_key.push_back(INTERFACEKEY_STRING_A222);
	allowed_key.push_back(INTERFACEKEY_STRING_A223);
	allowed_key.push_back(INTERFACEKEY_STRING_A224);
	allowed_key.push_back(INTERFACEKEY_STRING_A225);
	allowed_key.push_back(INTERFACEKEY_STRING_A226);
	allowed_key.push_back(INTERFACEKEY_STRING_A227);
	allowed_key.push_back(INTERFACEKEY_STRING_A228);
	allowed_key.push_back(INTERFACEKEY_STRING_A229);
	allowed_key.push_back(INTERFACEKEY_STRING_A230);
	allowed_key.push_back(INTERFACEKEY_STRING_A231);
	allowed_key.push_back(INTERFACEKEY_STRING_A232);
	allowed_key.push_back(INTERFACEKEY_STRING_A233);
	allowed_key.push_back(INTERFACEKEY_STRING_A234);
	allowed_key.push_back(INTERFACEKEY_STRING_A235);
	allowed_key.push_back(INTERFACEKEY_STRING_A236);
	allowed_key.push_back(INTERFACEKEY_STRING_A237);
	allowed_key.push_back(INTERFACEKEY_STRING_A238);
	allowed_key.push_back(INTERFACEKEY_STRING_A239);
	allowed_key.push_back(INTERFACEKEY_STRING_A240);
	allowed_key.push_back(INTERFACEKEY_STRING_A241);
	allowed_key.push_back(INTERFACEKEY_STRING_A242);
	allowed_key.push_back(INTERFACEKEY_STRING_A243);
	allowed_key.push_back(INTERFACEKEY_STRING_A244);
	allowed_key.push_back(INTERFACEKEY_STRING_A245);
	allowed_key.push_back(INTERFACEKEY_STRING_A246);
	allowed_key.push_back(INTERFACEKEY_STRING_A247);
	allowed_key.push_back(INTERFACEKEY_STRING_A248);
	allowed_key.push_back(INTERFACEKEY_STRING_A249);
	allowed_key.push_back(INTERFACEKEY_STRING_A250);
	allowed_key.push_back(INTERFACEKEY_STRING_A251);
	allowed_key.push_back(INTERFACEKEY_STRING_A252);
	allowed_key.push_back(INTERFACEKEY_STRING_A253);
	allowed_key.push_back(INTERFACEKEY_STRING_A254);
	allowed_key.push_back(INTERFACEKEY_STRING_A255);
}

void merge_binding(unsigned char &c)
{
	switch(c)
		{
		case VK_UP:c='8';break;
		case VK_DOWN:c='2';break;
		case VK_LEFT:c='4';break;
		case VK_RIGHT:c='6';break;
		case VK_CLEAR:c='5';break;
		case VK_PRIOR:c='9';break;
		case VK_NEXT:c='3';break;
		case VK_END:c='1';break;
		case VK_HOME:c='7';break;
		case VK_NUMPAD0:c='0';break;
		case VK_NUMPAD1:c='1';break;
		case VK_NUMPAD2:c='2';break;
		case VK_NUMPAD3:c='3';break;
		case VK_NUMPAD4:c='4';break;
		case VK_NUMPAD5:c='5';break;
		case VK_NUMPAD6:c='6';break;
		case VK_NUMPAD7:c='7';break;
		case VK_NUMPAD8:c='8';break;
		case VK_NUMPAD9:c='9';break;
		case VK_SEPARATOR:c=VK_RETURN;break;
		}
}

void viewscreen_keybindingsst::view()
{
	enabler.flag&=~ENABLERFLAG_MAXFPS;
	enabler.qprate=init.display.dwarf_frame_rate;

#ifndef NO_FMOD
	musicsound.startbackgroundmusic(SONG_GAME);
#endif

	drawborder("  Options: Key Bindings  ");

	string ikey;
	long scroll=(selected/21)*21;
	long i;
	for(i=scroll;i<allowed_key.size()&&i<scroll+21;i++)
		{
		if(i==selected&&binding)gps.changecolor(3,0,1);
		else if(i==selected)gps.changecolor(7,0,1);
		else gps.changecolor(7,0,0);

		gps.locate(i-scroll+2,2);
		gps.addst(gview.interfacekey[allowed_key[i]].name);

		gps.locate(i-scroll+2,40);
		getstring_interfacechar(ikey,gview.interfacekey[allowed_key[i]]);
		gps.addst(ikey);
		}

	gps.changecolor(7,0,1);
	gps.locate(2,55);
	game.print_interface_token(INTERFACEKEY_SAVE_BINDINGS);
	gps.addst(" - Export to txt");

	gps.changecolor(7,0,1);
	gps.locate(4,55);
	gps.addst("Press ");
	game.print_interface_token(INTERFACEKEY_CHANGE_BINDINGS);
	gps.addst(" and a key");
	gps.locate(5,55);
	gps.addst("to change a key binding.");

	gps.renewscreen();

	if(binding&&gview.c!=0)
		{
		gview.interfacekey[allowed_key[selected]].binding=gview.c;
		if(gview.c>='A'&&gview.c<='Z'&&gview.caps)gview.interfacekey[allowed_key[selected]].shift=(!gview.shift);
		else gview.interfacekey[allowed_key[selected]].shift=gview.shift;
		gview.interfacekey[allowed_key[selected]].ctrl=gview.ctrl;
		gview.interfacekey[allowed_key[selected]].alt=gview.alt;
		binding=0;
		gview.c=0;
		}
	else
		{
		if(gview.keypress(INTERFACEKEY_CHANGE_BINDINGS))
			{
			//START THE BINDING PROCESS
			binding=1;
			}

		standardscrolling(selected,0,allowed_key.size()-1,21);

		if(gview.keypress(INTERFACEKEY_SAVE_BINDINGS))
			{
			//SAVE THE INTERFACE
			std::ofstream fseed("data/init/interface.txt");
			if(fseed.is_open())
				{
				string str;

				interfacekeyst key;
				long i,j;
				for(i=1;i<256;i++)
					{
					for(j=0;j<8;j++)
						{
						if(!gview.display_string[i][j].empty())
							{
							key.binding=i;
							key.shift=((j%2)==1);
							key.ctrl=(((j/2)%2)==1);
							key.alt=(((j/4)%2)==1);

							getstring_interfacechar_save(str,key);

							if(str!="NOT_SUPPORTED")
								{
								fseed<<"[DISPLAY_STRING:"<<str.c_str()<<':'<<gview.display_string[i][j].c_str()<<']'<<std::endl;
								}
							}
						}
					}

				fseed<<std::endl;

				for(i=0;i<INTERFACEKEYNUM;i++)
					{
					getstring_interfacechar_save(str,gview.interfacekey[i]);
					fseed<<'['<<gview.interfacekey[i].tokenname.data()<<':'<<str.c_str()<<']'<<std::endl;
					}
				}
			fseed.close();
			gview.c=0;
			}

		if(gview.keypress(INTERFACEKEY_LEAVESCREEN))
			{
			breakdownlevel=INTERFACE_BREAKDOWN_STOPSCREEN;
			return;
			}
		}
}

void interfacest::addscreen(viewscreenst *scr,char pushtype,viewscreenst *relate)
{
	switch(pushtype)
		{
		case INTERFACE_PUSH_AS_PARENT:insertscreen_as_parent(scr,relate);break;
		case INTERFACE_PUSH_AS_CHILD:insertscreen_as_child(scr,relate);break;
		case INTERFACE_PUSH_AT_FRONT:insertscreen_at_front(scr);break;
		default:insertscreen_at_back(scr);break;
		}
}

void interfacest::insertscreen_as_parent(viewscreenst *scr,viewscreenst *child)
{
	if(child==NULL)
		{
		insertscreen_at_back(scr);
		return;
		}

	scr->child=child;
	scr->parent=child->parent;

	if(scr->parent!=NULL)scr->parent->child=scr;
	child->parent=scr;
}

void interfacest::insertscreen_as_child(viewscreenst *scr,viewscreenst *parent)
{
	if(parent==NULL)
		{
		insertscreen_at_back(scr);
		return;
		}

	scr->child=parent->child;
	scr->parent=parent;

	if(scr->child!=NULL)scr->child->parent=scr;
	parent->child=scr;
}

void interfacest::insertscreen_at_back(viewscreenst *scr)
{
	//GRAB CURRENT SCREEN AT THE END OF THE LIST
	viewscreenst *currentscreen=&view;
	while(currentscreen->child!=NULL)currentscreen=currentscreen->child;

	//PUT IT ON TO THE BACK SCREEN
	insertscreen_as_child(scr,currentscreen);
}

void interfacest::insertscreen_at_front(viewscreenst *scr)
{
	//PUT IT ON TO THE BASE
	insertscreen_as_child(scr,&view);
}

char interfacest::valid_held_key(unsigned char c)
{
	switch(c)
		{
		case VK_BACK:
		case VK_TAB:
		case VK_CLEAR:
		case VK_RETURN:
		//case VK_SHIFT:
		//case VK_CONTROL:
		//case VK_MENU:
		case VK_PAUSE:
		//case VK_CAPITAL:
		case VK_ESCAPE:
		case VK_SPACE:
		case VK_PRIOR:
		case VK_NEXT:
		case VK_END:
		case VK_HOME:
		case VK_LEFT:
		case VK_UP:
		case VK_RIGHT:
		case VK_DOWN:
		case VK_SELECT:
		case VK_PRINT:
		case VK_EXECUTE:
		case VK_SNAPSHOT:
		case VK_INSERT:
		case VK_DELETE:
		case VK_HELP:
		case 0x30://0
		case 0x31:
		case 0x32:
		case 0x33:
		case 0x34:
		case 0x35:
		case 0x36:
		case 0x37:
		case 0x38:
		case 0x39://9
		case 0x41://A
		case 0x42:
		case 0x43:
		case 0x44:
		case 0x45:
		case 0x46://F
		case 0x47:
		case 0x48:
		case 0x49:
		case 0x4A:
		case 0x4B://K
		case 0x4C:
		case 0x4D:
		case 0x4E:
		case 0x4F:
		case 0x50://P
		case 0x51:
		case 0x52:
		case 0x53:
		case 0x54:
		case 0x55://U
		case 0x56:
		case 0x57:
		case 0x58:
		case 0x59:
		case 0x5A://Z
		case VK_NUMPAD0:
		case VK_NUMPAD1:
		case VK_NUMPAD2:
		case VK_NUMPAD3:
		case VK_NUMPAD4:
		case VK_NUMPAD5:
		case VK_NUMPAD6:
		case VK_NUMPAD7:
		case VK_NUMPAD8:
		case VK_NUMPAD9:
		case VK_SEPARATOR:
		case VK_SUBTRACT:
		case VK_ADD:
		case VK_MULTIPLY:
		case VK_DECIMAL:
		case VK_DIVIDE:
		case VK_F1:
		case VK_F2:
		case VK_F3:
		case VK_F4:
		case VK_F5:
		case VK_F6:
		case VK_F7:
		case VK_F8:
		case VK_F9:
		case VK_F10:
		case VK_F11:
		case VK_F12:
		case VK_F13:
		case VK_F14:
		case VK_F15:
		case VK_F16:
		case VK_F17:
		case VK_F18:
		case VK_F19:
		case VK_F20:
		case VK_F21:
		case VK_F22:
		case VK_F23:
		case VK_F24:
		case VK_NUMLOCK:
		case VK_SCROLL:
		//case VK_LSHIFT:
		//case VK_RSHIFT:
		//case VK_LCONTROL:
		//case VK_RCONTROL:
		//case VK_LMENU:
		//case VK_RMENU:
		case 0xBA:
		case 0xBB:
		case 0xBC:
		case 0xBD:
		case 0xBE:
		case 0xBF:
		case 0xC0:
		case 0xDB:
		case 0xDC:
		case 0xDD:
		case 0xDE:
		case 0xDF:
		case 0xE1:
		case 0xE2:
		case 0xE3:
		case 0xE4:
		case 0xE9:
		case 0xEA:
		case 0xEB:
		case 0xEC:
		case 0xED:
		case 0xEE:
		case 0xEF:
		case 0xF1:
		case 0xF2:
		case 0xF3:
		case 0xF4:
		case 0xF5:
		case 0x15:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1C:
		case 0x1D:
		case 0x1E:
		case 0x1F:
		case 0x92:
		case 0x93:
		case 0x94:
		case 0x95:
		case 0x96:
			return 1;
		}

	return 0;
}

char interfacest::loop()
{
#ifdef ENABLER
	//SET THE HELD STATE OF THE INTERFACE KEYS
	char didkey[256];
	memset(didkey,0,sizeof(char)*256);
	long i;
	long i2;
	for(i2=0;i2<INTERFACEKEYNUM;i2++)interfacekey[i2].held=2;
	unsigned char heldc;
	bool c_shift=((GetKeyState(VK_SHIFT)>>1)!=0);
	bool c_caps=(GetKeyState(VK_CAPITAL)!=0);
	bool c_ctrl=((GetKeyState(VK_CONTROL)>>1)!=0);
	bool c_alt=((GetKeyState(VK_MENU)>>1)!=0);
	for(i=1;i<256;i++)
		{
		if(!valid_held_key(i))continue;
		if(!(enabler.keys.keyDown[i]))continue;
		//DO A STUCK KEY CHECK
		if(!(GetKeyState(i)>>1))
			{
			enabler.keys.keyDown[i]=FALSE;
			continue;
			}

		heldc=i;
		merge_binding(heldc);

		for(i2=0;i2<INTERFACEKEYNUM;i2++)
			{
			switch(i2)
				{
				case INTERFACEKEY_STANDARDSCROLL_UP:
				case INTERFACEKEY_STANDARDSCROLL_DOWN:
				case INTERFACEKEY_STANDARDSCROLL_LEFT:
				case INTERFACEKEY_STANDARDSCROLL_RIGHT:
				case INTERFACEKEY_STANDARDSCROLL_PAGEUP:
				case INTERFACEKEY_STANDARDSCROLL_PAGEDOWN:
				case INTERFACEKEY_SECONDSCROLL_UP:
				case INTERFACEKEY_SECONDSCROLL_DOWN:
				case INTERFACEKEY_SECONDSCROLL_PAGEUP:
				case INTERFACEKEY_SECONDSCROLL_PAGEDOWN:
				case INTERFACEKEY_CURSOR_UP:
				case INTERFACEKEY_CURSOR_DOWN:
				case INTERFACEKEY_CURSOR_LEFT:
				case INTERFACEKEY_CURSOR_RIGHT:
				case INTERFACEKEY_CURSOR_UPLEFT:
				case INTERFACEKEY_CURSOR_UPRIGHT:
				case INTERFACEKEY_CURSOR_DOWNLEFT:
				case INTERFACEKEY_CURSOR_DOWNRIGHT:
				case INTERFACEKEY_CURSOR_UP_FAST:
				case INTERFACEKEY_CURSOR_DOWN_FAST:
				case INTERFACEKEY_CURSOR_LEFT_FAST:
				case INTERFACEKEY_CURSOR_RIGHT_FAST:
				case INTERFACEKEY_CURSOR_UPLEFT_FAST:
				case INTERFACEKEY_CURSOR_UPRIGHT_FAST:
				case INTERFACEKEY_CURSOR_DOWNLEFT_FAST:
				case INTERFACEKEY_CURSOR_DOWNRIGHT_FAST:
				case INTERFACEKEY_CURSOR_UP_Z:
				case INTERFACEKEY_CURSOR_DOWN_Z:
				case INTERFACEKEY_CURSOR_UP_Z_AUX:
				case INTERFACEKEY_CURSOR_DOWN_Z_AUX:
					if(interfacekey[i2].binding==heldc)
						{
						if(!(heldc>='A'&&heldc<='Z')||(!caps&&interfacekey[i2].shift==c_shift)||(caps&&interfacekey[i2].shift==c_shift))
							{
							interfacekey[i2].held=1;
							if(GetTickCount()-interfacekey[i2].last_used_for_held>=init.input.hold_time||
								interfacekey[i2].last_used_for_held>GetTickCount())
								{
								//IF THE KEY HAS BEEN HELD FOR A WHILE,
									//SEND OFF SOME MORE INPUT TO gview
								if(inputbuffer.size()<100&&!didkey[heldc])
									{
									inputbuffer.push_back(heldc);
									if(c_caps)c_caps=1;
									if(c_shift)c_shift=1;
									if(c_ctrl)c_ctrl=1;
									if(c_alt)c_alt=1;
									inputbuffer_caps.push_back(c_caps);
									inputbuffer_shift.push_back(c_shift);
									inputbuffer_ctrl.push_back(c_ctrl);
									inputbuffer_alt.push_back(c_alt);
									didkey[heldc]=1;
									}

								//RESET COUNTER
								interfacekey[i2].last_used_for_held=GetTickCount();
								}
							}
						}
					break;
				}
			}
		}
	//THESE ARE NOT FRESHLY HELD
	for(i2=0;i2<INTERFACEKEYNUM;i2++)
		{
		if(interfacekey[i2].held==2)
			{
			interfacekey[i2].held=0;
			interfacekey[i2].last_used_for_held=GetTickCount();
			}
		}

	if(shutdown_interface_for_ms>0)
		{
		//CLEAR ALL THE KEYS
		enabler.clear_input();

		inputbuffer.clear();
		inputbuffer_shift.clear();
		inputbuffer_caps.clear();
		inputbuffer_ctrl.clear();
		inputbuffer_alt.clear();

		long gt=GetTickCount();
		for(i2=0;i2<INTERFACEKEYNUM;i2++)
			{
			interfacekey[i2].held=0;
			interfacekey[i2].last_used_for_held=gt;
			}

		//DONE
		if(gt-shutdown_interface_tickcount>=shutdown_interface_for_ms||
			shutdown_interface_tickcount>gt)
			{
			shutdown_interface_for_ms=0;
			}
		}

#endif

	//GRAB CURRENT SCREEN AT THE END OF THE LIST
	viewscreenst *currentscreen=&view;
	while(currentscreen->child!=NULL)currentscreen=currentscreen->child;

	//NO INTERFACE LEFT, QUIT
	if(currentscreen==&view)return 1;

	//MOVE SCREENS BACK
	switch(currentscreen->breakdownlevel)
		{
		case INTERFACE_BREAKDOWN_NONE:
			{
			//GATHER INPUT
			#ifdef CURSES
				char newc;
				do
					{
					newc=getch();
					if(newc!=0&&inputbuffer.size()<100)
						{
						if(valid_held_key(newc))
							{
							inputbuffer.push_back(newc);
							inputbuffer_caps.push_back(0);
							inputbuffer_shift.push_back(0);
							inputbuffer_ctrl.push_back(0);
							inputbuffer_alt.push_back(0);
							}
						}
					}while(newc!=0);
			#endif
			#ifdef ENABLER
				enabler_inputst input;
				do
					{
					input=enabler.getinput();

					if(input.key!=0&&inputbuffer.size()<100)
						{
						if(valid_held_key(input.key))
							{
							inputbuffer.push_back(input.key);
							inputbuffer_caps.push_back(input.caps);
							inputbuffer_shift.push_back(input.shift);
							inputbuffer_ctrl.push_back(input.ctrl);
							inputbuffer_alt.push_back(input.alt);
							}
						input.key=0;
						}
					}while(input.key!=0);
			#endif

			if(inputbuffer.size()>0)
				{
				if(c==0||!(flag & INTERFACEFLAG_RETAIN_NONZERO_INPUT))
					{
					c=inputbuffer[0];
					merge_binding(c);

					caps=inputbuffer_caps[0];
					shift=inputbuffer_shift[0];
					ctrl=inputbuffer_ctrl[0];
					alt=inputbuffer_alt[0];

					if(shift)shift=1;
					inputbuffer.erase(0);
					inputbuffer_caps.erase(0);
					inputbuffer_shift.erase(0);
					inputbuffer_ctrl.erase(0);
					inputbuffer_alt.erase(0);
					}
				}
			else if(!(flag & INTERFACEFLAG_RETAIN_NONZERO_INPUT))c=0;
			flag&=~INTERFACEFLAG_RETAIN_NONZERO_INPUT;

			//TOGGLE SCREEN
			if(gview.keypress(INTERFACEKEY_TOGGLE_FULLSCREEN))
				{
				enabler.toggle_fullscreen();
				gview.c=0;
				}

			//FRAME COUNT
			if(gps.display_frames && !enabler.doing_buffer_draw())
				{
				QueryPerformanceCounter(&gps.print_time[gps.print_index]);
				gps.print_index=(gps.print_index+1)%100;
				}

			if(currentscreen->is_legacy_screen())
				{
				//GAME OPTIONS
				if(gview.keypress(INTERFACEKEY_OPTIONS)&&!currentscreen->key_conflict(INTERFACEKEY_OPTIONS))
					{
					//PEEL BACK ALL SCREENS TO THE CURRENT OPTION SCREEN IF THERE IS ONE
						//UNLESS THERE IS A BLOCKING SCREEN LIKE THE REGION MAKER
					viewscreenst *opscreen=&view;
					while(opscreen!=NULL)
						{
						if(opscreen->is_option_screen())
							{
							opscreen->option_key_pressed=1;
							while(opscreen->child!=NULL)
								{
								if(opscreen->child->is_option_screen()==2)
									{
									opscreen->child->option_key_pressed=1;
									opscreen->option_key_pressed=0;
									break;
									}
								removescreen(opscreen->child);
								}
							break;
							}

						opscreen=opscreen->child;
						}

					//NEED A NEW OPTIONS SCREEN?
					if(opscreen==NULL)viewscreen_optionst::create(INTERFACE_PUSH_AT_BACK);

					//REFRESH CURRENT SCREEN
						//GRAB CURRENT SCREEN AT THE END OF THE LIST
					currentscreen=&view;
					while(currentscreen->child!=NULL)currentscreen=currentscreen->child;

						//NO INTERFACE LEFT, QUIT
					if(currentscreen==&view)return 1;

					c=0;
					}
				//DO MOVIE COMMANDS
				else if(gview.keypress(INTERFACEKEY_MOVIES)&&!currentscreen->key_conflict(INTERFACEKEY_MOVIES))
					{
					if(currentscreen->movies_okay())use_movie_input();
					}
				//RUN THE INTERFACE AND SEE HOW FAR TO PEEL IT BACK
				else if(gview.keypress(INTERFACEKEY_HELP)&&!currentscreen->key_conflict(INTERFACEKEY_HELP))
					{
					//WE INTERCEPT THE HELP KEY NO MATTER WHAT
					currentscreen->help();
					c=0;
					}
				else currentscreen->view();
				}
			else
				{
				//GAME OPTIONS
				if(gview.keypress(INTERFACEKEY_OPTIONS)&&!currentscreen->key_conflict(INTERFACEKEY_OPTIONS))
					{
					//PEEL BACK ALL SCREENS TO THE CURRENT OPTION SCREEN IF THERE IS ONE
						//UNLESS THERE IS A BLOCKING SCREEN LIKE THE REGION MAKER
					viewscreenst *opscreen=&view;
					while(opscreen!=NULL)
						{
						if(opscreen->is_option_screen())
							{
							opscreen->option_key_pressed=1;
							while(opscreen->child!=NULL)
								{
								if(opscreen->child->is_option_screen()==2)
									{
									opscreen->child->option_key_pressed=1;
									opscreen->option_key_pressed=0;
									break;
									}
								removescreen(opscreen->child);
								}
							break;
							}

						opscreen=opscreen->child;
						}

					//NEED A NEW OPTIONS SCREEN?
					if(opscreen==NULL)viewscreen_optionst::create(INTERFACE_PUSH_AT_BACK);

					//REFRESH CURRENT SCREEN
						//GRAB CURRENT SCREEN AT THE END OF THE LIST
					currentscreen=&view;
					while(currentscreen->child!=NULL)currentscreen=currentscreen->child;

						//NO INTERFACE LEFT, QUIT
					if(currentscreen==&view)return 1;

					c=0;
					}
				//DO MOVIE COMMANDS
				else if(gview.keypress(INTERFACEKEY_MOVIES)&&!currentscreen->key_conflict(INTERFACEKEY_MOVIES))
					{
					if(currentscreen->movies_okay())use_movie_input();
					}
				//RUN THE INTERFACE AND SEE HOW FAR TO PEEL IT BACK
				else if(gview.keypress(INTERFACEKEY_HELP)&&!currentscreen->key_conflict(INTERFACEKEY_HELP))
					{
					//WE INTERCEPT THE HELP KEY NO MATTER WHAT
					currentscreen->help();
					c=0;
					}
				else
					{
					currentscreen->input();

					viewscreenst *n_currentscreen=&view;
					while(n_currentscreen->child!=NULL)n_currentscreen=n_currentscreen->child;

					if(currentscreen==n_currentscreen)currentscreen->logic();
					}
				}

			if(currentscreen->movies_okay())
				{
				//HANDLE MOVIES
				handlemovie(0);
				}

			//PRINT THE MOUSE
			if(!init.input.flag.has_flag(INIT_INPUT_FLAG_MOUSE_OFF))
				{
				if(enabler.tracking_on)
					{
					if(init.input.flag.has_flag(INIT_INPUT_FLAG_MOUSE_PICTURE))
						{
						enabler.set_color(1,1,1);
						enabler.locate(enabler.mouse_x,enabler.mouse_y);
						enabler.add_tile(gps.tex_pos[TEXTURE_MOUSE]);
						while(ShowCursor(FALSE)>0);
						}
					else while(ShowCursor(TRUE)<=0);
					}
				else while(ShowCursor(TRUE)<=0);
				}
			else if(enabler.create_full_screen)
				{
				while(ShowCursor(FALSE)>0);
				}
			else  while(ShowCursor(TRUE)<=0);

			break;
			}
		case INTERFACE_BREAKDOWN_QUIT:
			{
			handlemovie(1);
			return 1;
			}
		case INTERFACE_BREAKDOWN_STOPSCREEN:
			if(currentscreen->movies_okay())
				{
				//HANDLE MOVIES
				handlemovie(0);
				}

			removescreen(currentscreen);
			break;
		case INTERFACE_BREAKDOWN_TOFIRST:
			if(currentscreen->movies_okay())
				{
				//HANDLE MOVIES
				handlemovie(0);
				}

			remove_to_first();
			break;
		}

	return 0;
}

void interfacest::remove_to_first()
{
	//GRAB LAST SCREEN AT THE END OF THE LIST
	viewscreenst *lastscreen=&view;
	while(lastscreen->child!=NULL)lastscreen=lastscreen->child;

	//NO INTERFACE LEFT
	if(lastscreen==&view)return;

	//GO AHEAD
	while(lastscreen->parent!=&view)
		{
		viewscreenst *par=lastscreen->parent;
		removescreen(lastscreen);
		lastscreen=par;
		}
}

void interfacest::removescreen(viewscreenst *scr)
{
	//FIX LINKS
	if(scr->parent!=NULL)scr->parent->child=scr->child;
	if(scr->child!=NULL)scr->child->parent=scr->parent;

	//WASTE SCREEN
	delete scr;
}

long interfacest::write_movie_chunk()
{
	long inputsize=supermovie_pos;
	if(inputsize>MOVIEBUFFSIZE)inputsize=MOVIEBUFFSIZE;

	//DUMP CURRENT BUFFER INTO A COMPRESSION STREAM
	z_stream c_stream;
	int err;

	c_stream.zalloc = (alloc_func)0;
	c_stream.zfree = (free_func)0;
	c_stream.opaque = (voidpf)0;

	err = deflateInit(&c_stream, 9);
	CHECK_ERR(err, "deflateInit");

	c_stream.next_out = (Bytef*)supermoviebuffer_comp;
	c_stream.avail_out = COMPMOVIEBUFFSIZE;

	c_stream.next_in  = (Bytef*)supermoviebuffer;
	c_stream.avail_in  = inputsize;

	while (c_stream.total_in != inputsize && c_stream.total_out < COMPMOVIEBUFFSIZE) {
		//c_stream.avail_in = c_stream.avail_out = 1; // force small buffers
		err = deflate(&c_stream, Z_NO_FLUSH);
		CHECK_ERR(err, "deflate");
		}

	// Finish the stream, still forcing small buffers:
	for (;;) {
		err = deflate(&c_stream, Z_FINISH);
		if (err == Z_STREAM_END) break;
		CHECK_ERR(err, "deflate");
		}

	err = deflateEnd(&c_stream);
	CHECK_ERR(err, "deflateEnd");

	long length=0;

	if(c_stream.total_out>0)
		{
		if(first_movie_write)
			{
			//GET RID OF ANY EXISTING MOVIES IF THIS IS THE FIRST TIME THROUGH
			unlink(movie_file.c_str());
			}

		//OPEN UP THE MOVIE FILE AND APPEND
		std::fstream f;
		f.open(movie_file.c_str(), fstream::out | fstream::binary | fstream::app);

		if(f.is_open())
			{
			//WRITE A HEADER
			if(first_movie_write)
				{
				long swp_l=byteswap(movie_version);
				f.write((const char *)&swp_l,sizeof(long));


				cursesmovie_headerst cmh;
					cmh.dimx=init.display.grid_x;
					cmh.dimy=init.display.grid_y;
					cmh.delayrate=supermovie_delayrate;
					cmh.dimx=byteswap(cmh.dimx);
					cmh.dimy=byteswap(cmh.dimy);
					cmh.delayrate=byteswap(cmh.delayrate);
				f.write((const char *)&cmh,sizeof(cursesmovie_headerst));

				long s;
				s=byteswap(gview.supermovie_sound.str.size());
				f.write((const char *)&s,sizeof(long));
				char buf[50];
				for(s=0;s<gview.supermovie_sound.str.size();s++)
					{
					strcpy(buf,gview.supermovie_sound.str[s]->dat.c_str());
					f.write(buf,sizeof(char)*50);
					}

				long i1,i2;
				for(i1=0;i1<200;i1++)
					{
					for(i2=0;i2<SOUND_CHANNELNUM;i2++)
						{
						swp_l=byteswap(gview.supermovie_sound_time[i1][i2]);
						f.write((const char *)&swp_l,sizeof(long));
						}
					}
				}

			//WRITE IT
			long compsize=byteswap(c_stream.total_out);
			f.write((const char *)&compsize,sizeof(long));
			f.write((const char *)supermoviebuffer_comp,c_stream.total_out);

			f.seekg(0,ios::beg);
			long beg=f.tellg();
			f.seekg(0,ios::end);
			long end=f.tellg();
			length=end-beg;

			f.close();
			}
		else supermovie_on=0;

		first_movie_write=0;
		}

	return length;
}

void interfacest::read_movie_chunk(long &maxmoviepos,char &is_playing)
{
	//OPEN UP THE MOVIE FILE AND MOVE TO CORRECT POSITION
	std::fstream f;
	f.open(movie_file.c_str(), fstream::in | fstream::out | fstream::binary);

	if(f.is_open())
		{
		f.seekg(0,ios::beg);
		long beg=f.tellg();
		f.seekg(0,ios::end);
		long end=f.tellg();
		long file_size=end-beg;

		if(gview.nextfilepos<file_size)
			{
			f.seekg(gview.nextfilepos,ios::beg);

			//LOAD THE HEADER
			char fail=0;
			if(gview.nextfilepos==0)
				{
				long loadversion;
				f.read((char *)&loadversion,sizeof(long));
				loadversion=byteswap(loadversion);

				if(loadversion>movie_version)fail=1;

				cursesmovie_headerst cmh;
				f.read((char *)&cmh,sizeof(cursesmovie_headerst));
					cmh.dimx=byteswap(cmh.dimx);
					cmh.dimy=byteswap(cmh.dimy);
					cmh.delayrate=byteswap(cmh.delayrate);

				init.display.grid_x=cmh.dimx;
				init.display.grid_y=cmh.dimy;
				gps.prepare_rect(0);

				gview.supermovie_delayrate=cmh.delayrate;
				gview.supermovie_delaystep=cmh.delayrate;

				gview.supermovie_sound.clean();
				if(loadversion>=10001)
					{
					long num;
					f.read((char *)&num,sizeof(long));
					num=byteswap(num);
					gview.nextfilepos+=sizeof(long);
					char buf[50];
					long s;
					for(s=0;s<num;s++)
						{
						f.read(buf,sizeof(char)*50);
						string str=buf;
						gview.supermovie_sound.add_string(str);
						gview.nextfilepos+=sizeof(char)*50;
						}

					long i1,i2,swp_l;
					for(i1=0;i1<200;i1++)
						{
						for(i2=0;i2<SOUND_CHANNELNUM;i2++)
							{
							f.read((char *)&swp_l,sizeof(long));
							gview.supermovie_sound_time[i1][i2]=byteswap(swp_l);
							}
						}

					gview.nextfilepos+=sizeof(long)*200*SOUND_CHANNELNUM;
					}
				else
					{
					long i,c;
					for(i=0;i<200;i++)
						{
						for(c=0;c<SOUND_CHANNELNUM;c++)gview.supermovie_sound_time[i][c]=-1;
						}
					}

				gview.nextfilepos+=sizeof(long)+sizeof(cursesmovie_headerst);

#ifndef NO_FMOD
				//HANDLE SOUND LOADING
				long s;
				for(s=0;s<gview.supermovie_sound.str.size();s++)
					{
					string filename="data/sound/";
					filename+=gview.supermovie_sound.str[s]->dat;
					filename+=".ogg";
					
					musicsound.set_sound(filename,s);
					}
#endif
				}

			if(!fail)
				{
				//READ IT
				f.read((char *)&gview.currentblocksize,sizeof(long));
				gview.currentblocksize=byteswap(gview.currentblocksize);
				f.read((char *)gview.supermoviebuffer_comp,gview.currentblocksize);

				gview.nextfilepos+=gview.currentblocksize+sizeof(long);

				//UNCOMPRESS IT
				z_stream d_stream; // decompression stream

				d_stream.zalloc = (alloc_func)0;
				d_stream.zfree = (free_func)0;
				d_stream.opaque = (voidpf)0;

				d_stream.next_in  = (Bytef*)gview.supermoviebuffer_comp;
				d_stream.avail_in = gview.currentblocksize;

				int err = inflateInit(&d_stream);
				CHECK_ERR(err, "inflateInit");

				d_stream.next_out = gview.supermoviebuffer;
				d_stream.avail_out = MOVIEBUFFSIZE;

				while (d_stream.total_out < MOVIEBUFFSIZE && d_stream.total_in < gview.currentblocksize) {
					//d_stream.avail_in = d_stream.avail_out = 1; // force small buffers
					err = inflate(&d_stream, Z_NO_FLUSH);
					if (err == Z_STREAM_END) break;
					CHECK_ERR(err, "inflate");
					}

				err = inflateEnd(&d_stream);
				CHECK_ERR(err, "inflateEnd");

				gview.supermovie_pos=0;
				maxmoviepos=d_stream.total_out;
				}
			else
				{
				is_playing=0;
				init.display.grid_x=init.display.orig_grid_x;
				init.display.grid_y=init.display.orig_grid_y;
				gps.prepare_rect(1);
				}
			}
		else
			{
			is_playing=0;
			init.display.grid_x=init.display.orig_grid_x;
			init.display.grid_y=init.display.orig_grid_y;
			gps.prepare_rect(1);
			}

		f.close();
		}
	else
		{
		is_playing=0;
		init.display.grid_x=init.display.orig_grid_x;
		init.display.grid_y=init.display.orig_grid_y;
		gps.prepare_rect(1);
		}
}

void interfacest::handlemovie(char flushall)
{
	//SAVE A MOVIE FRAME INTO THE CURRENT MOVIE BUFFER
	if(supermovie_on==1)
		{
		if(supermovie_delaystep>0&&!flushall)supermovie_delaystep--;
		else
			{
			if(!flushall)supermovie_delaystep=supermovie_delayrate;

			if(!flushall||supermovie_delaystep==0)
				{
				//SAVING CHARACTERS, THEN COLORS
				short x2,y2;
				for(x2=0;x2<init.display.grid_x;x2++)
					{
					for(y2=0;y2<init.display.grid_y;y2++)
						{
						supermoviebuffer[supermovie_pos]=gps.screen[x2][y2][0];

						supermovie_pos++;
						}
					}
				char frame_col;
				for(x2=0;x2<init.display.grid_x;x2++)
					{
					for(y2=0;y2<init.display.grid_y;y2++)
						{
						frame_col=gps.screen[x2][y2][1];
						frame_col|=(gps.screen[x2][y2][2]<<3);
						if(gps.screen[x2][y2][3])frame_col|=64;
						supermoviebuffer[supermovie_pos]=frame_col;

						supermovie_pos++;
						}
					}
				}

			long frame_size=init.display.grid_x*init.display.grid_y*2;
			if(supermovie_pos+frame_size>=MOVIEBUFFSIZE||flushall)
				{
				long length=write_movie_chunk();

				if(length>5000000)
					{
					finish_movie();
					}
				else supermovie_pos=0;
				}
			}
		}
}

void interfacest::finish_movie()
{
	supermovie_on=0;
	currentblocksize=0;
	nextfilepos=0;
	supermovie_pos=0;
	viewscreen_movieplayerst::create(INTERFACE_PUSH_AT_BACK);
}

void interfacest::use_movie_input()
{
	if(supermovie_on)handlemovie(1);
	finish_movie();
	c=0;
}

viewscreen_movieplayerst *viewscreen_movieplayerst::create(char pushtype,viewscreenst *scr)
{
	viewscreen_movieplayerst *newv=new viewscreen_movieplayerst();
	gview.addscreen(newv,pushtype,scr);

	return newv;
}

void viewscreen_movieplayerst::force_play(string &file)
{
	force_file=file;
	is_forced_play=1;
}

void viewscreen_movieplayerst::view()
{
	enabler.flag&=~ENABLERFLAG_MAXFPS;
	enabler.qprate=enabler.main_qprate;//USE THE MAIN RATE FOR MOVIES

	if(!force_file.empty()&&!is_playing&&!quit_if_no_play&&is_forced_play)
		{
		is_playing=1;
		quit_if_no_play=1;
		gview.movie_file=force_file;
		gview.supermovie_on=0;
		gview.currentblocksize=0;
		gview.nextfilepos=0;
		gview.supermovie_pos=0;
		maxmoviepos=0;
		}

	if(!is_playing&&quit_if_no_play)
		{
		breakdownlevel=INTERFACE_BREAKDOWN_STOPSCREEN;
		init.display.grid_x=init.display.orig_grid_x;//JUST IN CASE
		init.display.grid_y=init.display.orig_grid_y;
		gps.prepare_rect(1);
		return;
		}

	if(!quit_if_no_play)
		{
		if(editing)drawborder(NULL);
		else drawborder("  Moving Records  ");
		}

	//LOAD A MOVIE BUFFER BY BUFFER
	if(is_playing)
		{
		if(gview.supermovie_pos>=MOVIEBUFFSIZE||gview.currentblocksize==0)
			{
			gview.read_movie_chunk(maxmoviepos,is_playing);
			}

		if(is_playing)
			{
			long half_frame_size=init.display.grid_x*init.display.grid_y;

			//PLAY ANY RELEVANT SOUNDS
			if(gview.supermovie_delaystep==gview.supermovie_delayrate)
				{
				long fr=gview.supermovie_pos/(half_frame_size*2);
				if(fr>=0&&fr<200)
					{
					long c,sd;
					for(c=0;c<16;c++)
						{
						sd=gview.supermovie_sound_time[fr][c];
						if(sd>=0&&sd<gview.supermovie_sound.str.size())
							{
#ifndef NO_FMOD
							musicsound.playsound(sd,c);
#endif
							}
						}
					}
				}

			//PRINT THE NEXT FRAME AND ADVANCE POSITION
			drawborder(NULL,-1);
			
			short x2,y2;
			for(x2=0;x2<init.display.grid_x;x2++)
				{
				for(y2=0;y2<init.display.grid_y;y2++)
					{
					gps.locate(y2,x2);

					gps.changecolor((gview.supermoviebuffer[gview.supermovie_pos+half_frame_size] & 7),
						(gview.supermoviebuffer[gview.supermovie_pos+half_frame_size] & 56)>>3,
						(gview.supermoviebuffer[gview.supermovie_pos+half_frame_size] & 64));

					gps.addchar(gview.supermoviebuffer[gview.supermovie_pos]);

					gview.supermovie_pos++;
					}
				}
			if(gview.supermovie_delaystep==0)
				{
				gview.supermovie_pos+=half_frame_size;
				gview.supermovie_delaystep=gview.supermovie_delayrate;
				}
			else
				{
				gview.supermovie_pos-=half_frame_size;//RETURN TO LAST FRAME
				gview.supermovie_delaystep--;
				}

			//DONE
			if(gview.supermovie_pos>=maxmoviepos&&
				maxmoviepos+half_frame_size*2<MOVIEBUFFSIZE)
				{
				is_playing=0;
				init.display.grid_x=init.display.orig_grid_x;
				init.display.grid_y=init.display.orig_grid_y;
				//NOTE: THIS CAUSES IT TO LOSE THE LAST FRAME DUE TO CLEARING
				gps.prepare_rect(1);
				}
			}
		}
	else if(loading)
		{
		int scroll=selfile/21*21;
		int l;
		for(l=scroll;l<filelist.size() && l<scroll+21;l++)
			{
			if(l==selfile)gps.changecolor(7,0,1);
			else gps.changecolor(7,0,0);
			gps.locate(l-scroll+2,2);
			gps.addst(filelist[l]);
			}
		}
	else
		{
		gps.changecolor(7,0,1);
		gps.locate(2,2);
		game.print_interface_token(INTERFACEKEY_MOVIE_RECORD);
		gps.addst(": Start recording (active record is erased, stops when you return here)");
		gps.locate(3,2);
		game.print_interface_token(INTERFACEKEY_MOVIE_PLAY);
		gps.addst(": Play the active moving record");
		gps.locate(4,2);
		game.print_interface_token(INTERFACEKEY_MOVIE_SAVE);
		gps.addst(": Save the active moving record (you will be prompted for a name)");
		gps.locate(5,2);
		game.print_interface_token(INTERFACEKEY_MOVIE_LOAD);
		gps.addst(": Load a moving record");

		if(saving)
			{
			gps.locate(10,2);
			gps.addst("Name: ");
			gps.addst(savename);
			}
		}

	gps.renewscreen();

	if(gview.keypress(INTERFACEKEY_LEAVESCREEN))
		{
		if(is_playing)
			{
			is_playing=0;
			init.display.grid_x=init.display.orig_grid_x;
			init.display.grid_y=init.display.orig_grid_y;
			gps.prepare_rect(1);
			gview.supermovie_on=0;
			gview.currentblocksize=0;
			gview.nextfilepos=0;
			gview.supermovie_pos=0;
			maxmoviepos=0;

#ifndef NO_FMOD
			musicsound.stop_sound();
#endif
			}
		else if(saving)saving=0;
		else if(loading)loading=0;
		else
			{
			is_playing=0;
			init.display.grid_x=init.display.orig_grid_x;
			init.display.grid_y=init.display.orig_grid_y;
			gps.prepare_rect(1);
			gview.supermovie_on=0;
			gview.currentblocksize=0;
			gview.nextfilepos=0;
			gview.supermovie_pos=0;
			maxmoviepos=0;

			breakdownlevel=INTERFACE_BREAKDOWN_STOPSCREEN;
			return;
			}
		}
	else if(saving)
		{
		standardstringentry(savename,39,STRINGENTRY_LETTERS|STRINGENTRY_SPACE|STRINGENTRY_NUMBERS|STRINGENTRY_SYMBOLS);

		if(gview.keypress(INTERFACEKEY_SELECT))
			{
			string filename;
			filename="data/movies/";
			filename+=savename;
			filename+=".cmv";

			game.copy_file(gview.movie_file,filename);
			saving=0;
			}
		}
	else if(loading)
		{
		standardscrolling(selfile,0,filelist.size()-1,21);

		if(gview.keypress(INTERFACEKEY_SELECT))
			{
			string filename;
			filename="data/movies/";
			filename+=filelist[selfile];

			if(filename!=gview.movie_file)
				{
				game.copy_file(filename,gview.movie_file);
				}
			loading=0;
			}
		}
	else
		{
		if(is_playing)
			{
			}
		else
			{
			if(gview.keypress(INTERFACEKEY_MOVIE_RECORD))
				{
				//TURN ON THE MOVIE RECORDER
				is_playing=0;
				init.display.grid_x=init.display.orig_grid_x;
				init.display.grid_y=init.display.orig_grid_y;
				gps.prepare_rect(1);
				gview.supermovie_on=1;
				gview.currentblocksize=0;
				gview.nextfilepos=0;
				gview.supermovie_pos=0;
				gview.supermovie_delayrate=0;
				gview.first_movie_write=1;
				maxmoviepos=0;

				breakdownlevel=INTERFACE_BREAKDOWN_STOPSCREEN;
				}
			if(gview.keypress(INTERFACEKEY_MOVIE_PLAY))
				{
				is_playing=1;
				gview.supermovie_on=0;
				gview.currentblocksize=0;
				gview.nextfilepos=0;
				gview.supermovie_pos=0;
				maxmoviepos=0;
				}
			if(gview.keypress(INTERFACEKEY_MOVIE_SAVE))
				{
				savename.erase();
				saving=1;
				}
			if(gview.keypress(INTERFACEKEY_MOVIE_LOAD))
				{
				selfile=0;

				clearfilelist();

				find_files_by_pattern("data/movies/*.cmv",filelist);

				if(filelist.size()>0)loading=1;
				}
			}
		}
}

void viewscreen_movieplayerst::clearfilelist()
{
	int f;
	for(f=0;f<filelist.size();f++)delete[] filelist[f];
	filelist.clear();
}

viewscreen_movieplayerst::viewscreen_movieplayerst()
{
	force_file.erase();
	gview.movie_file="data/movies/last_record.cmv";
	is_playing=0;
	init.display.grid_x=init.display.orig_grid_x;
	init.display.grid_y=init.display.orig_grid_y;
	gps.prepare_rect(1);
	is_forced_play=0;
	quit_if_no_play=0;
	gview.supermovie_on=0;
	gview.currentblocksize=0;
	gview.nextfilepos=0;
	gview.supermovie_pos=0;
	maxmoviepos=0;
	saving=0;
	loading=0;
	editing=0;
	text_mode=0;
	editing_copy_from=0;
	editing_char=219;
	editing_screenf=7;
	editing_screenb=0;
	editing_screenbright=0;
	editing_menu=0;
	editing_selected_sound=0;
	end_frame_pos=0;
	gview.supermovie_sound.clean();
	long i,c;
	for(i=0;i<200;i++)
		{
		for(c=0;c<SOUND_CHANNELNUM;c++)gview.supermovie_sound_time[i][c]=-1;
		}
}

bool viewscreen_keybindingsst::key_conflict(InterfaceKey test_key)
{
	if(test_key!=INTERFACEKEY_CHANGE_BINDINGS&&test_key>=(InterfaceKey)0&&test_key<INTERFACEKEYNUM)
		{
		if(gview.interfacekey[test_key].binding==gview.interfacekey[INTERFACEKEY_CHANGE_BINDINGS].binding&&
			gview.interfacekey[test_key].shift==gview.interfacekey[INTERFACEKEY_CHANGE_BINDINGS].shift&&
			gview.interfacekey[test_key].ctrl==gview.interfacekey[INTERFACEKEY_CHANGE_BINDINGS].ctrl&&
			gview.interfacekey[test_key].alt==gview.interfacekey[INTERFACEKEY_CHANGE_BINDINGS].alt)
			{
			return true;
			}
		}
	return false;
}

void viewscreen_titlest::input()
{
	if(gview.keypress(INTERFACEKEY_SELECT))
		{
		switch(choice[selected])
			{
			case 0:
				viewscreen_mapst::create(INTERFACE_PUSH_AT_BACK);

				breakdownlevel=INTERFACE_BREAKDOWN_STOPSCREEN;
				break;
			case 1:
				breakdownlevel=INTERFACE_BREAKDOWN_QUIT;
				break;
			case 2:
				//*************************** TITLE
					//load a save
				break;
			}
		}

	standardscrolling(selected,0,choice.size()-1,init.display.grid_y-2);
}

void viewscreen_titlest::logic()
{
	enabler.flag&=~ENABLERFLAG_MAXFPS;
	enabler.qprate=init.display.dwarf_frame_rate;

	//SET UP RENDER
	enabler.flag|=ENABLERFLAG_RENDER;

#ifndef NO_FMOD
	musicsound.startbackgroundmusic(SONG_GAME);
#endif
}

void viewscreen_titlest::render()
{
	drawborder("BATTLE CHAMPS");

	long y=2;
	long scroll=selected/(init.display.grid_y-2)*(init.display.grid_y-2);
	long i;
	for(i=scroll;i<scroll+(init.display.grid_y-2)&&i<choice.size();i++)
		{
		if(i==selected)gps.changecolor(7,0,1);
		else gps.changecolor(7,0,0);
		gps.locate(y,0);
		switch(choice[i])
			{
			case 0:
				gps.addst("New game");
				break;
			case 1:
				gps.addst("Quit");
				break;
			case 2:
				//*************************** TITLE
					//print save name
				break;
			}
		y++;
		}

	gps.locate(5,2);
	gps.changecolor(4,0,1);
	gps.addst("This is an unfinished vehicle for distributing portions of DF code.");
	gps.locate(6,2);
	gps.changecolor(4,0,1);
	gps.addst("There are no win conditions and there's no way to save games.");

	gps.renewscreen();
}

viewscreen_titlest::viewscreen_titlest()
{
	selected=0;

	choice.push_back(0);
	choice.push_back(1);
	//*************************** TITLE
		//enumerate save file names
}

viewscreen_titlest::~viewscreen_titlest()
{
}

void viewscreen_mapst::input()
{
	if(advance)return;

	unsigned char entry=0;
	if(gview.keypress(INTERFACEKEY_STRING_A049))entry='1';
	if(gview.keypress(INTERFACEKEY_STRING_A050))entry='2';
	if(gview.keypress(INTERFACEKEY_STRING_A051))entry='3';
	if(gview.keypress(INTERFACEKEY_STRING_A052))entry='4';
	if(gview.keypress(INTERFACEKEY_STRING_A053))entry='5';
	if(gview.keypress(INTERFACEKEY_STRING_A054))entry='6';
	if(gview.keypress(INTERFACEKEY_STRING_A055))entry='7';
	if(gview.keypress(INTERFACEKEY_STRING_A056))entry='8';
	if(gview.keypress(INTERFACEKEY_STRING_A057))entry='9';
	if(gview.keypress(INTERFACEKEY_STRING_A097))entry='a';
	if(gview.keypress(INTERFACEKEY_STRING_A098))entry='b';
	if(gview.keypress(INTERFACEKEY_STRING_A099))entry='c';
	if(gview.keypress(INTERFACEKEY_STRING_A100))entry='d';
	if(gview.keypress(INTERFACEKEY_STRING_A101))entry='e';
	if(gview.keypress(INTERFACEKEY_STRING_A102))entry='f';
	if(gview.keypress(INTERFACEKEY_STRING_A103))entry='g';
	if(gview.keypress(INTERFACEKEY_STRING_A104))entry='h';
	if(gview.keypress(INTERFACEKEY_STRING_A105))entry='i';
	if(gview.keypress(INTERFACEKEY_STRING_A106))entry='j';
	if(gview.keypress(INTERFACEKEY_STRING_A107))entry='k';
	if(gview.keypress(INTERFACEKEY_STRING_A108))entry='l';
	if(gview.keypress(INTERFACEKEY_STRING_A109))entry='m';
	if(gview.keypress(INTERFACEKEY_STRING_A110))entry='n';
	if(gview.keypress(INTERFACEKEY_STRING_A111))entry='o';
	if(gview.keypress(INTERFACEKEY_STRING_A112))entry='p';
	if(gview.keypress(INTERFACEKEY_STRING_A113))entry='q';
	if(gview.keypress(INTERFACEKEY_STRING_A114))entry='r';
	if(gview.keypress(INTERFACEKEY_STRING_A115))entry='s';
	if(gview.keypress(INTERFACEKEY_STRING_A116))entry='t';
	if(gview.keypress(INTERFACEKEY_STRING_A117))entry='u';
	if(gview.keypress(INTERFACEKEY_STRING_A118))entry='v';
	if(gview.keypress(INTERFACEKEY_STRING_A119))entry='w';
	if(gview.keypress(INTERFACEKEY_STRING_A120))entry='x';
	if(gview.keypress(INTERFACEKEY_STRING_A121))entry='y';
	if(gview.keypress(INTERFACEKEY_STRING_A122))entry='z';
	if(gview.keypress(INTERFACEKEY_STRING_A065))entry='A';
	if(gview.keypress(INTERFACEKEY_STRING_A066))entry='B';
	if(gview.keypress(INTERFACEKEY_STRING_A067))entry='C';
	if(gview.keypress(INTERFACEKEY_STRING_A068))entry='D';
	if(gview.keypress(INTERFACEKEY_STRING_A069))entry='E';
	if(gview.keypress(INTERFACEKEY_STRING_A070))entry='F';
	if(gview.keypress(INTERFACEKEY_STRING_A071))entry='G';
	if(gview.keypress(INTERFACEKEY_STRING_A072))entry='H';
	if(gview.keypress(INTERFACEKEY_STRING_A073))entry='I';
	if(gview.keypress(INTERFACEKEY_STRING_A074))entry='J';
	if(gview.keypress(INTERFACEKEY_STRING_A075))entry='K';
	if(gview.keypress(INTERFACEKEY_STRING_A076))entry='L';
	if(gview.keypress(INTERFACEKEY_STRING_A077))entry='M';
	if(gview.keypress(INTERFACEKEY_STRING_A078))entry='N';
	if(gview.keypress(INTERFACEKEY_STRING_A079))entry='O';
	if(gview.keypress(INTERFACEKEY_STRING_A080))entry='P';
	if(gview.keypress(INTERFACEKEY_STRING_A081))entry='Q';
	if(gview.keypress(INTERFACEKEY_STRING_A082))entry='R';
	if(gview.keypress(INTERFACEKEY_STRING_A083))entry='S';
	if(gview.keypress(INTERFACEKEY_STRING_A084))entry='T';
	if(gview.keypress(INTERFACEKEY_STRING_A085))entry='U';
	if(gview.keypress(INTERFACEKEY_STRING_A086))entry='V';
	if(gview.keypress(INTERFACEKEY_STRING_A087))entry='W';
	if(gview.keypress(INTERFACEKEY_STRING_A088))entry='X';
	if(gview.keypress(INTERFACEKEY_STRING_A089))entry='Y';
	if(gview.keypress(INTERFACEKEY_STRING_A090))entry='Z';

	if(entry>='1'&&entry<='9')
		{
		if(selected!=-1)
			{
			if(game.map.territory[selected].army_id[entry-'1']!=-1&&
				game.map.territory[selected].nation_id==0)
				{
				selected_aid=game.map.territory[selected].army_id[entry-'1'];
				}
			}
		}
	else if(entry!=0&&!moving)
		{
		long t;
		for(t=0;t<init.feature.start_nation;t++)
			{
			if(game.map.territory[t].letter==entry)
				{
				selected=t;
				selected_aid=-1;
				break;
				}
			}
		}

	if(selected!=-1)
		{
		if(selected_aid!=-1)
			{
			if(!moving)
				{
				if(gview.keypress(INTERFACEKEY_SELECT))
					{
					moving=true;
					return;					
					}
				}
			else
				{
				long n;
				for(n=0;n<game.map.territory[selected].neighbor.size();n++)
					{
					if(entry==game.map.territory[game.map.territory[selected].neighbor[n]].letter)
						{
						nationst *nt=game.nation.get_nation_by_global_id(game.map.territory[selected].nation_id);
						if(nt!=NULL)
							{
							armyst *arm=get_from_global_id_vector(selected_aid,nt->army);
							if(arm!=NULL)arm->destination_territory=game.map.territory[selected].neighbor[n];
							}
						moving=false;
						selected_aid=-1;
						return;
						}
					}
				}
			}

		if(gview.keypress(INTERFACEKEY_LEAVESCREEN))
			{
			if(moving)
				{
				moving=false;

				nationst *nt=game.nation.get_nation_by_global_id(game.map.territory[selected].nation_id);
				if(nt!=NULL)
					{
					armyst *arm=get_from_global_id_vector(selected_aid,nt->army);
					if(arm!=NULL)arm->destination_territory=-1;
					}
				}
			else if(selected_aid!=-1)selected_aid=-1;
			else selected=-1;
			}
		}

	//ADVANCE PLAY
	if(selected_aid==-1)
		{
		if(gview.keypress(INTERFACEKEY_SELECT))
			{
			advance=true;
			return;
			}
		}
}

void viewscreen_mapst::logic()
{
	enabler.flag&=~ENABLERFLAG_MAXFPS;
	enabler.qprate=init.display.dwarf_frame_rate;

	//SET UP RENDER
	enabler.flag|=ENABLERFLAG_RENDER;

#ifndef NO_FMOD
	musicsound.startbackgroundmusic(SONG_GAME);
#endif

	while(advance)
		{
		if(advancing_territory!=-1)
			{
			if(advance_countdown>0)
				{
				advance_countdown--;
				return;
				}
			else
				{
				game.prepare_fight(advancing_territory);
				advancing_territory=-1;
				return;
				}
			}
		else
			{
			svector<long> candidate;

			long n,a;
			for(n=0;n<game.nation.global.size();n++)
				{
				for(a=0;a<game.nation.global[n]->army.size();a++)
					{
					if(game.nation.global[n]->army[a]->destination_territory!=-1)
						{
						add_unique_to_binary_vector(game.nation.global[n]->army[a]->destination_territory,candidate);
						}
					}
				}

			if(candidate.size()>0)
				{
				advancing_territory=candidate[trandom(candidate.size())];

				if(game.nation.global[0]->involved_in_conflict_in_territory(advancing_territory))
					{
					advance_countdown=300;
					return;
					}
				else
					{
					game.quick_resolve_conflict(advancing_territory);
					advancing_territory=-1;
					advance_countdown=0;
					//CONTINUE ON IN LOOP
					}
				}
			else
				{
				advance=false;

				svector<long> ter;
				nationst *nt;
				long n,t,count,a;
				for(n=0;n<game.nation.global.size();n++)
					{
					nt=game.nation.global[n];

					//ADD EMPTY NEW ARMIES TO ANY NATION THAT DOESN'T HAVE ENOUGH ACCORDING TO TERRITORY
						//THEY'LL GET GENERALS AND UNITS BELOW
					count=0;
					for(t=0;t<init.feature.start_nation;t++)
						{
						if(game.map.territory[t].nation_id==nt->global_id)
							{
							count++;
							if(game.map.territory[t].army_id[0]==-1)ter.push_back(t);
							}
						}
					while(count>nt->army.size()&&ter.size()>0)
						{
						long ind=trandom(ter.size());

						armyst *arm=new armyst;
							arm->global_id=nt->next_army_id;
							nt->next_army_id++;
							arm->nation_id=nt->global_id;
							arm->current_territory=ter[ind];
						add_to_global_id_vector(arm,nt->army);

						game.map.territory[ter[ind]].army_id[0]=arm->global_id;

						ter.erase(ind);
						count--;
						}
					}

				//ADD GENERALS TO ARMIES WITHOUT LEADERS
				for(t=0;t<init.feature.start_nation;t++)
					{
					nt=game.nation.get_nation_by_global_id(game.map.territory[t].nation_id);
					if(nt!=NULL)
						{
						for(a=0;a<9;a++)
							{
							if(game.map.territory[t].army_id[a]!=-1)
								{
								armyst *arm=get_from_global_id_vector(game.map.territory[t].army_id[a],nt->army);
								if((arm!=NULL)?(arm->get_leader()==NULL):false)
									{
									unitst *newu=new unitst;
										newu->def=nt->def->grab_leader_unit_def();
										newu->level=1;
										newu->num=1;
										text_infost ti;
										enabler.text_system.get_text(nt->def->word_list_index,ti);
										newu->name+=ti.get_string(0);
										enabler.text_system.get_text(nt->def->word_list_index,ti);
										newu->name+=ti.get_string(0);
										capitalize_string_first_word(newu->name);
									arm->unit.push_back(newu);
									}
								}
							}
						}
					}

				for(n=0;n<game.nation.global.size();n++)
					{
					nt=game.nation.global[n];

					//ADD RECRUITS TO ALL ARMIES
					long a;
					for(a=0;a<nt->army.size();a++)nt->add_points_to_army(nt->army[a],5000);
					}
				}
			}
		}
}

void viewscreen_mapst::render()
{
	gps.erasescreen();

	bool flash=(GetTickCount()%1000<500);

	map_territoryst *mt;
	short x,y;
	for(x=0;x<game.map.dimx;x++)
		{
		for(y=0;y<game.map.dimy;y++)
			{
			mt=&(game.map.territory[game.map.square[x][y].territory]);
			gps.locate(y,x);
			if(x==mt->main_x&&
				y==mt->main_y)
				{
				if(mt->nation_id==0)gps.changecolor(2,0,1);
				else gps.changecolor(4,0,1);
				gps.addchar(mt->letter);
				}
			else
				{
				if(selected==game.map.square[x][y].territory)
					{
					if(flash)gps.changecolor(mt->f,0,1-mt->br);
					else gps.changecolor(mt->f,0,mt->br);
					}
				else gps.changecolor(mt->f,0,mt->br);
				gps.addchar(mt->sym);
				}
			}
		}

	short start_x=init.display.grid_x-30;

	if(selected!=-1)
		{
		mt=&(game.map.territory[selected]);

		nationst *nt=game.nation.get_nation_by_global_id(mt->nation_id);
		if(nt!=NULL)
			{
			gps.locate(0,start_x+1);
			gps.changecolor(7,0,1);
			gps.addst(nt->name);

			if(selected_aid!=-1)
				{
				armyst *arm=get_from_global_id_vector(selected_aid,nt->army);
				if(arm!=NULL)
					{
					if(moving)
						{
						short y=2;
						long n;
						for(n=0;n<mt->neighbor.size();n++)
							{
							gps.changecolor(2,0,1);
							gps.locate(y,start_x+1);
							gps.addchar(game.map.territory[mt->neighbor[n]].letter);

							if(game.map.territory[mt->neighbor[n]].nation_id!=arm->nation_id)
								{
								nationst *nb=game.nation.get_nation_by_global_id(game.map.territory[mt->neighbor[n]].nation_id);
								if(nb!=NULL)
									{
									gps.changecolor(4,0,1);
									gps.locate(y,start_x+3);
									gps.addst("Attack ");
									gps.addst(nb->name);
									}
								}
							else 
								{
								gps.changecolor(2,0,1);
								gps.locate(y,start_x+3);
								gps.addst("Move");
								}

							y++;
							}
						}
					else
						{
						short y=2;
						long u;
						for(u=0;u<arm->unit.size();u++)
							{
							unitst *un=arm->unit[u];

							if(un->def->leader)
								{
								gps.locate(y+1,start_x+27);
								if(un->def->texpos!=-1)gps.add_tile(un->def->texpos,0);
								else
									{
									gps.changecolor(un->def->f,un->def->b,un->def->br);
									gps.addchar(un->def->sym);
									}

								gps.changecolor(7,0,1);
								gps.locate(y,start_x+3);
								gps.addst(un->name);

								gps.changecolor(7,0,0);
								gps.locate(y+1,start_x+4);
								gps.addst(un->def->name);

								gps.changecolor(3,0,1);
								gps.locate(y+1,start_x+28);
								string str;
								add_long_to_string(un->level,str);
								gps.addst(str);

								if(arm->destination_territory!=-1)
									{
									if(game.map.territory[arm->destination_territory].nation_id!=arm->nation_id)gps.changecolor(4,0,1);
									else gps.changecolor(2,0,1);
									gps.locate(y,start_x+27);
									gps.addchar(26);
									gps.addchar(game.map.territory[arm->destination_territory].letter);
									}
								}
							else
								{
								gps.locate(y+1,start_x+27);
								if(un->def->texpos!=-1)gps.add_tile(un->def->texpos,0);
								else
									{
									gps.changecolor(un->def->f,un->def->b,un->def->br);
									gps.addchar(un->def->sym);
									}

								gps.changecolor(7,0,1);
								gps.locate(y,start_x+3);
								gps.addst(un->def->name);

								gps.changecolor(7,0,0);
								gps.locate(y+1,start_x+4);
								string str="Force of ";
								add_long_to_string(un->num,str);
								gps.addst(str);
								}

							y+=2;
							}
						}
					}
				}
			else
				{
				short y=2;
				long a;
				for(a=0;a<9;a++)
					{
					armyst *arm=get_from_global_id_vector(mt->army_id[a],nt->army);
					if(arm!=NULL)
						{
						unitst *un=arm->get_leader();
						if(un!=NULL)
							{
							gps.locate(y+1,start_x+27);
							if(un->def->texpos!=-1)gps.add_tile(un->def->texpos,0);
							else
								{
								gps.changecolor(un->def->f,un->def->b,un->def->br);
								gps.addchar(un->def->sym);
								}

							gps.changecolor(7,0,1);
							gps.locate(y,start_x+3);
							gps.addst(un->name);

							gps.changecolor(7,0,0);
							gps.locate(y+1,start_x+4);
							gps.addst(un->def->name);

							gps.changecolor(3,0,1);
							gps.locate(y+1,start_x+28);
							string str;
							add_long_to_string(un->level,str);
							gps.addst(str);

							if(arm->destination_territory!=-1)
								{
								if(game.map.territory[arm->destination_territory].nation_id!=arm->nation_id)gps.changecolor(4,0,1);
								else gps.changecolor(2,0,1);
								gps.locate(y,start_x+27);
								gps.addchar(26);
								gps.addchar(game.map.territory[arm->destination_territory].letter);
								}

							if(mt->nation_id==0)
								{
								gps.locate(y,start_x+1);
								switch(a)
									{
									case 0:game.print_interface_token(INTERFACEKEY_STRING_A049);break;
									case 1:game.print_interface_token(INTERFACEKEY_STRING_A050);break;
									case 2:game.print_interface_token(INTERFACEKEY_STRING_A051);break;
									case 3:game.print_interface_token(INTERFACEKEY_STRING_A052);break;
									case 4:game.print_interface_token(INTERFACEKEY_STRING_A053);break;
									case 5:game.print_interface_token(INTERFACEKEY_STRING_A054);break;
									case 6:game.print_interface_token(INTERFACEKEY_STRING_A055);break;
									case 7:game.print_interface_token(INTERFACEKEY_STRING_A056);break;
									case 8:game.print_interface_token(INTERFACEKEY_STRING_A057);break;
									}
								}
							}
						}
					y+=2;
					}
				}
			}

		if(selected_aid!=-1)
			{
			if(!moving)
				{
				gps.changecolor(7,0,0);
				gps.locate(init.display.grid_y-1,start_x+1);
				game.print_interface_token(INTERFACEKEY_SELECT);
				gps.addst(": Move/Attack");
				}
			}
		else
			{
			gps.changecolor(7,0,0);
			gps.locate(init.display.grid_y-1,start_x+1);
			game.print_interface_token(INTERFACEKEY_SELECT);
			gps.addst(": Next turn");
			}
		}
	else
		{
		short x=start_x+1;
		short y=2;
		long num=0,anum,a;
		long t;
		for(t=0;t<init.feature.start_nation;t++)
			{
			if(game.map.territory[t].nation_id==0)
				{
				anum=0;
				for(a=0;a<9;a++)
					{
					if(game.map.territory[t].army_id[a]!=-1)anum++;
					}
				num++;
				if(anum>0)gps.changecolor(2,0,1);
				else gps.changecolor(2,0,0);
				gps.locate(y,x);
				gps.addchar(game.map.territory[t].letter);
				x++;
				if(x>=init.display.grid_x-1||x>start_x+26)
					{
					x=start_x+1;
					y++;
					}
				}
			}

		gps.locate(0,start_x+1);
		gps.changecolor(7,0,1);
		string str="You control ";
		add_long_to_string(num,str);
		if(num==1)str+=" territory.";
		else str+=" territories.";
		gps.addst(str);

		gps.changecolor(7,0,0);
		gps.locate(init.display.grid_y-1,start_x+1);
		game.print_interface_token(INTERFACEKEY_SELECT);
		gps.addst(": Next turn");
		}

	if(advance_countdown&&advancing_territory!=-1)
		{
		gps.changecolor(0,0,0);
		short x;
		for(x=5;x<init.display.grid_x-5;x++)
			{
			gps.locate(5,x);
			gps.addchar(' ');
			gps.locate(6,x);
			gps.addchar(' ');
			gps.locate(7,x);
			gps.addchar(' ');
			}

		gps.locate(6,6);
		if(game.map.territory[advancing_territory].nation_id==0)
			{
			gps.changecolor(4,0,1);
			gps.addst("Prepare for the defense of ");
			gps.changecolor(2,0,1);
			gps.addchar(game.map.territory[advancing_territory].letter);
			gps.changecolor(4,0,1);
			gps.addchar('!');
			}
		else
			{
			gps.changecolor(4,0,1);
			gps.addst("Prepare for the attack on ");
			gps.changecolor(2,0,1);
			gps.addchar(game.map.territory[advancing_territory].letter);
			gps.changecolor(4,0,1);
			gps.addchar('!');
			}
		}

	gps.renewscreen();
}

viewscreen_mapst::viewscreen_mapst()
{
	selected=-1;
	selected_aid=-1;
	moving=false;
	advance=false;
	advancing_territory=-1;
	advance_countdown=0;

	game.map.allocate(init.feature.world_map_x,init.feature.world_map_y);

	game.map.create_new_map();

	game.nation.create_new_nations();
}

viewscreen_mapst::~viewscreen_mapst()
{
	game.clean();
}

void viewscreen_fightst::input()
{
}

void viewscreen_fightst::logic()
{
	enabler.flag&=~ENABLERFLAG_MAXFPS;
	enabler.qprate=init.display.dwarf_frame_rate;

	//SET UP RENDER
	enabler.flag|=ENABLERFLAG_RENDER;

#ifndef NO_FMOD
	musicsound.startbackgroundmusic(SONG_GAME);
#endif

	if(stage_fight)
		{
		//PICK OUT TWO BATTLE ARMIES
		svector<battle_armyst *> cand;
		long a,a2,a3;
		for(a=(long)battle_army.size()-1;a>=0;a--)
			{
			for(a2=(long)battle_army[a]->army.size()-1;a2>=0;a2--)
				{
				//CLEANUP FROM THE PREVIOUS ROUND
				if(battle_army[a]->army[a2]->unit.size()==0)
					{
					nationst *nt=game.nation.get_nation_by_global_id(battle_army[a]->army[a2]->nation_id);
					if(nt!=NULL)
						{
						remove_from_global_id_vector(battle_army[a]->army[a2],nt->army);
						long t;
						for(t=0;t<init.feature.start_nation;t++)
							{
							if(game.map.territory[t].nation_id==nt->global_id)
								{
								for(a3=0;a3<9;a3++)
									{
									if(game.map.territory[t].army_id[a3]==battle_army[a]->army[a2]->global_id)
										{
										game.map.territory[t].army_id[a3]=-1;
										break;
										}
									}
								}
							}
						}

					delete battle_army[a]->army[a2];
					battle_army[a]->army.erase(a2);
					}
				}

			if(battle_army[a]->army.size()>0)cand.push_back(battle_army[a]);
			}
		if(cand.size()<=1)
			{
			breakdownlevel=INTERFACE_BREAKDOWN_STOPSCREEN;
			return;
			}
		else
			{
			memset(tile_ptr,0,sizeof(battle_unitst *)*MAX_BATTLE_X*MAX_BATTLE_Y);
			memset(row_count,0,sizeof(long)*MAX_BATTLE_Y);

			long ind;
			ind=trandom(cand.size());
			side[0]=cand[ind];
			cand.erase(ind);
			ind=trandom(cand.size());
			side[1]=cand[ind];
			cand.erase(ind);

			long total;
			long s,a,u,n;
			for(s=0;s<2;s++)
				{
				for(a=0;a<side[s]->army.size();a++)
					{
					total=0;
					for(u=0;u<side[s]->army[a]->unit.size();u++)
						{
						for(n=0;n<side[s]->army[a]->unit[u]->num;n++)
							{
							if(side[s]->army[a]->unit[u]->def->leader)continue;

							battle_unitst *bu=new battle_unitst;
								bu->side=s;
								bu->army=side[s]->army[a];
								bu->unit=side[s]->army[a]->unit[u];
								if(s==1)bu->x=init.display.grid_x;
								else bu->x=-1;
								if(total<30)bu->y=init.display.grid_y/2;
								else if(total<100)bu->y=init.display.grid_y/2+trandom(5)-2;
								else if(total<300)bu->y=init.display.grid_y/2+trandom(9)-4;
								else if(total<500)bu->y=init.display.grid_y/2+trandom(13)-6;
								else bu->y=trandom(init.display.grid_y);
								bu->delay=trandom(10);
								bu->life=side[s]->army[a]->unit[u]->def->life*side[s]->army[a]->unit[u]->level;
							unit.push_back(bu);

							total++;
							}
						}
					if(total<50)
						{
						for(u=0;u<side[s]->army[a]->unit.size();u++)
							{
							for(n=0;n<side[s]->army[a]->unit[u]->num;n++)
								{
								if(!side[s]->army[a]->unit[u]->def->leader)continue;

								battle_unitst *bu=new battle_unitst;
									bu->side=s;
									bu->army=side[s]->army[a];
									bu->unit=side[s]->army[a]->unit[u];
									if(s==1)bu->x=init.display.grid_x;
									else bu->x=-1;
									bu->y=init.display.grid_y/2;
									bu->delay=trandom(10);
									bu->life=side[s]->army[a]->unit[u]->def->life*side[s]->army[a]->unit[u]->level;
								unit.push_back(bu);

								total++;
								}
							}
						}
					}
				}

			stage_fight=false;
			}
		return;
		}

	//ADVANCE FIGHTERS
	long live_side_count[2]={0,0};
	battle_unitst *bu,*bu2;
	long u;
	for(u=(long)unit.size()-1;u>=0;u--)
		{
		bu=unit[u];
		if(bu->life<=0)continue;

		if(bu->side==0&&bu->x<init.display.grid_x)live_side_count[0]++;
		else if(bu->side==1&&bu->x>=0)live_side_count[1]++;

		if(bu->delay>0)bu->delay--;
		else
			{
			bu->delay=9;

			if(bu->side==0)
				{
				if(bu->x>=init.display.grid_x)continue;
				if(bu->x==init.display.grid_x-1)
					{
					tile_ptr[bu->x][bu->y]=NULL;
					row_count[bu->y][0]--;
					bu->x=init.display.grid_x;
					}
				else
					{
					if(tile_ptr[bu->x+1][bu->y]==NULL&&(trandom(2)||!(bu->unit->def->range>=1&&bu->unit->def->range_attack>0)))
						{
						tile_ptr[bu->x+1][bu->y]=bu;
						if(bu->x>=0)tile_ptr[bu->x][bu->y]=NULL;
						else row_count[bu->y][0]++;
						bu->x++;
						}
					else if(bu->x>=0)
						{
						if(bu->unit->def->range>=1&&bu->unit->def->range_attack>0)
							{
							if(trandom(2))
								{
								short x;
								for(x=bu->x+1;x<=bu->x+1+bu->unit->def->range&&x<init.display.grid_x;x++)
									{
									bu2=tile_ptr[x][bu->y];
									if(bu2==NULL)continue;
									if(bu2->side!=bu->side)
										{
										bu2->life-=trandom(bu->unit->def->range_attack*bu->unit->level+1);
										if(bu2->life<=0)
											{
											tile_ptr[bu2->x][bu2->y]=NULL;
											row_count[bu2->y][1]--;
											}
										break;
										}
									}
								continue;
								}
							}

						bu2=tile_ptr[bu->x+1][bu->y];
						if(bu2==NULL)continue;
						if(bu2->side!=bu->side)
							{
							bu2->life-=trandom(bu->unit->def->short_attack*bu->unit->level+1);
							if(bu2->life<=0)
								{
								tile_ptr[bu2->x][bu2->y]=NULL;
								row_count[bu2->y][1]--;
								}
							continue;
							}
						}
					}
				}
			if(bu->side==1)
				{
				if(bu->x<0)continue;
				if(bu->x==0)
					{
					tile_ptr[bu->x][bu->y]=NULL;
					row_count[bu->y][1]--;
					bu->x=-1;
					}
				else
					{
					if(tile_ptr[bu->x-1][bu->y]==NULL&&(trandom(2)||!(bu->unit->def->range>=1&&bu->unit->def->range_attack>0)))
						{
						tile_ptr[bu->x-1][bu->y]=bu;
						if(bu->x<init.display.grid_x)tile_ptr[bu->x][bu->y]=NULL;
						else row_count[bu->y][1]++;
						bu->x--;
						}
					else if(bu->x<init.display.grid_x)
						{
						if(bu->unit->def->range>=1&&bu->unit->def->range_attack>0)
							{
							if(trandom(2))
								{
								short x;
								for(x=bu->x-1;x>=bu->x-1-bu->unit->def->range&&x>=0;x--)
									{
									bu2=tile_ptr[x][bu->y];
									if(bu2==NULL)continue;
									if(bu2->side!=bu->side)
										{
										bu2->life-=trandom(bu->unit->def->range_attack*bu->unit->level+1);
										if(bu2->life<=0)
											{
											tile_ptr[bu2->x][bu2->y]=NULL;
											row_count[bu2->y][1]--;
											}
										break;
										}
									}
								continue;
								}
							}

						bu2=tile_ptr[bu->x-1][bu->y];
						if(bu2==NULL)continue;
						if(bu2->side!=bu->side)
							{
							bu2->life-=trandom(bu->unit->def->short_attack*bu->unit->level+1);
							if(bu2->life<=0)
								{
								tile_ptr[bu2->x][bu2->y]=NULL;
								row_count[bu2->y][0]--;
								}
							continue;
							}
						}
					}
				}
			}
		}

	//EVALUATE BATTLE
	if(live_side_count[0]==0||live_side_count[1]==0)
		{
		long u;
		for(u=(long)unit.size()-1;u>=0;u--)
			{
			if(unit[u]->life<=0)
				{
				unit[u]->unit->num--;
				if(unit[u]->unit->num<=0)
					{
					long u2;
					for(u2=(long)unit[u]->army->unit.size()-1;u2>=0;u2--)
						{
						if(unit[u]->army->unit[u2]==unit[u]->unit)
							{
							delete unit[u]->army->unit[u2];
							unit[u]->army->unit.erase(u2);
							break;
							}
						}
					}
				}

			delete unit[u];
			}
		unit.clear();

		stage_fight=true;
		}
}

void viewscreen_fightst::render()
{
	if(stage_fight)return;

	gps.erasescreen();

	battle_unitst *bu;
	long u;
	for(u=(long)unit.size()-1;u>=0;u--)
		{
		bu=unit[u];
		if(bu->x>=0&&bu->x<init.display.grid_x&&bu->life>0)
			{
			gps.locate(bu->y,bu->x);
			gps.changecolor(bu->unit->def->f,bu->unit->def->b,bu->unit->def->br);
			if(bu->unit->def->texpos!=-1)gps.add_tile(bu->unit->def->texpos,0);
			else gps.addchar(bu->unit->def->sym);
			}
		}

	gps.renewscreen();
}

viewscreen_fightst::viewscreen_fightst(svector<battle_armyst *> &ba)
{
	battle_army=ba;

	stage_fight=true;
}

viewscreen_fightst::~viewscreen_fightst()
{
	long a,a2,u;
	for(a=(long)battle_army.size()-1;a>=0;a--)
		{
		//SURVIVING LEADERS GAIN LEVELS
		for(a2=0;a2<battle_army[a]->army.size();a2++)
			{
			for(u=0;u<battle_army[a]->army[a2]->unit.size();u++)
				{
				if(battle_army[a]->army[a2]->unit[u]->def->leader)
					{
					if(battle_army[a]->army[a2]->unit[u]->level<99)battle_army[a]->army[a2]->unit[u]->level++;
					}
				}
			}

		delete battle_army[a];
		}
	for(a=(long)unit.size()-1;a>=0;a--)delete unit[a];
}

viewscreen_titlest *viewscreen_titlest::create(char pushtype,viewscreenst *scr)
{
	viewscreen_titlest *newv=new viewscreen_titlest();
	gview.addscreen(newv,pushtype,scr);

	return newv;
}

viewscreen_mapst *viewscreen_mapst::create(char pushtype,viewscreenst *scr)
{
	viewscreen_mapst *newv=new viewscreen_mapst();
	gview.addscreen(newv,pushtype,scr);

	return newv;
}

viewscreen_fightst *viewscreen_fightst::create(svector<battle_armyst *> &ba,char pushtype,viewscreenst *scr)
{
	viewscreen_fightst *newv=new viewscreen_fightst(ba);
	gview.addscreen(newv,pushtype,scr);

	return newv;
}