#include <ofstream>
#include <stdio.h>
#include <stdarg.h>

namespace ppcStreams
{

/**************************************************************/
ofstream::ofstream()
/**************************************************************/
{
	_fileHandle = NULL;
}

/**************************************************************/
ofstream::ofstream(string filename)
/**************************************************************/
{
	open(filename);
}

/**************************************************************/
ofstream::~ofstream()
/**************************************************************/
{
}

/**************************************************************/
int ofstream::OutFunction(const char* format, ...)
/**************************************************************/
{
	va_list argList;
	va_start(argList, format);
	return(fprintf(_fileHandle, format, va_arg(argList, double))); //Sloppy, stack manip problems
}

/**************************************************************/
bool ofstream::operator==(bool val)
/**************************************************************/
{
	return(is_open()==val);
}

/**************************************************************/
ofstream::operator void*()
/**************************************************************/
{
	if (is_open())
		return ((void*)this);
	else
		return NULL;
}

/**************************************************************/
int ofstream::eof()
/**************************************************************/
{
	return(feof(_fileHandle));
}

/**************************************************************/
bool ofstream::open(string filename, ios::openmode mode)
/**************************************************************/
{
	if (mode==ios::out)
		_fileHandle = fopen(filename.c_str(), "w");
	else if (mode == ios::app)
		_fileHandle = fopen(filename.c_str(), "a");
	else if (mode == (ios::app | ios::out))
		_fileHandle = fopen(filename.c_str(), "a");
	else  //Invalid open mode for an output stream
	{
		_fileHandle = NULL;
		throw;
	}

	return (is_open());
}

/**************************************************************/
bool ofstream::is_open()
/**************************************************************/
{
	if (_fileHandle!=NULL)
		return true;
	else
		return false;
}

/**************************************************************/
void ofstream::close()
/**************************************************************/
{
	if(_fileHandle!=NULL)
		fclose(_fileHandle);
}

}; /*end namespace ppcStreams*/