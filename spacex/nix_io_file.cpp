#include <cstdio>
#include "crt.h"
#include "io.h"

void printcnf(const char* text) {
}

io::file::file() : handle(0) {
}

io::file::file(const char* url, unsigned flags) : handle(0) {
	create(url, flags);
}

io::file::~file() {
	close();
}

io::file::find::find(const char* url) {
	path[0] = 0;
	zcpy(path, url);
	char temp[261];
	zcpy(temp, path);
	zcat(temp, "/*.*");
}

const char* io::file::find::fullname(char* result) {
	zcpy(result, path);
	if(result[0])
		zcat(result, "/");
	zcat(result, name());
	return result;
}

void io::file::find::next() {
	if(!handle)
		return;
}

io::file::find::~find() {
//	if(handle)
//		FindClose(handle);
//	handle = 0;
}

const char* io::file::find::name() {
	return "";
	//return ((WIN32_FIND_DATA*)&reserved)->cFileName;
}

bool io::file::create(const char* url, unsigned flags) {
	if(handle)
		return true;
	return (*this);
}

void io::file::close() {
	handle = 0;
}

char* io::file::getdir(char* url, int size) {
	return url;
}

char* io::file::getmodule(char* url, int size) {
	return url;
}

bool io::file::setdir(const char* url) {
	return false;
}

bool io::file::remove(const char* url) {
	return false;
}

int io::file::read(void* p, int size) {
	return 0;
}

int io::file::write(const void* p, int size) {
	return 0;
}

int io::file::seek(int pos, int rel) {
	return 0;
}

bool io::file::exist(const char* url) {
	return false;
}

bool io::file::makedir(const char* url) {
	return false;
}