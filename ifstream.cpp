#include <ifstream>
#include <stdio.h>
#include <stdarg.h>

namespace ppcStreams
{
/**************************************************************/
ifstream::ifstream()
/**************************************************************/
{
	_fileHandle = NULL;
}

/**************************************************************/
ifstream::ifstream(string filename)
/**************************************************************/
{
	open(filename);
}

/**************************************************************/
ifstream::~ifstream()
/**************************************************************/
{
}

/**************************************************************/
int ifstream::InFunction(const char* format, ...)
/**************************************************************/
{
	va_list argList;
	va_start(argList, format);
	return(fscanf(_fileHandle, format, va_arg(argList, double))); //Sloppy, stack manip problems
}

/**************************************************************/
bool ifstream::operator==(bool val)
/**************************************************************/
{
	return(is_open()==val);
}

/**************************************************************/
ifstream::operator void*()
/**************************************************************/
{
	if (is_open())
		return ((void*)this);
	else
		return NULL;
}

/**************************************************************/
bool ifstream::eof()
/**************************************************************/
{
	if(feof(_fileHandle))
	{
		ios::setstate(ios::eofbit);
		return true;
	}
	else
		return false;
}

/**************************************************************/
bool ifstream::open(string filename, ios::openmode mode)
/**************************************************************/
{
	if (mode==ios::in)
		_fileHandle = fopen(filename.c_str(), "r");
	else //Invalid open mode
	{
		_fileHandle = NULL;
		throw;
	}
	return (is_open());
}

/**************************************************************/
bool ifstream::is_open()
/**************************************************************/
{
	if (_fileHandle!=NULL)
		return true;
	else
		return false;
}

/**************************************************************/
void ifstream::close()
/**************************************************************/
{
	if(_fileHandle!=NULL)
		fclose(_fileHandle);
}

}; /*end namespace ppcStreams*/
