//Copyright (c) 2008, Tarn Adams
//All rights reserved.  See game.cpp or license.txt for more information.

class command_linest
{
	public:
		string original;
		stringvectst arg_vect;

		void init(const string &str);
		char grab_arg(string &source,long &pos);
		void handle_arg(string &arg);

		command_linest()
			{
			}
};