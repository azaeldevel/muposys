

#ifndef MUPOSYS_CONSOLE_COMMANDS_HH
#define MUPOSYS_CONSOLE_COMMANDS_HH

#include "commands.hh"

namespace muposys::commands
{

class Command
{
public:
	virtual bool command(int argc, const char* argv[]) = 0;
};

class Muposys : public Command
{
public:
	virtual bool command(int argc, const char* argv[]);
	virtual bool stock(int argc, const char* argv[]);
	virtual bool catalog(int argc, const char* argv[]);
};


} 

#endif