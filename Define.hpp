#pragma once

#include <string>

static const int token_num = 10;

enum class TOKEN
{
	DIGIT,//number‚É’u‚«Š·‚¦‚ç‚ê‚é
	PLUS,
	MINUS,
	ASTER,
	SLASH,
	PERCENT,
	
	LEFTPER,
	RIGHTPER,
	SPACE,
	POW,
	
	NUMBER,
	
	END,
	ERROR = -1
};

const std::string char_group[] = {
	std::string("0123456789"),
	std::string("+"),
	std::string("-"),
	std::string("*"),
	std::string("/"),
	std::string("%"),
	
	std::string("("),
	std::string(")"),
	std::string(" \t\r\n"),
	std::string("^")
};

const std::string token_name[] = {
	std::string("DIGIT"),
	std::string("PLUS"),
	std::string("MINUS"),
	std::string("ASTAR"),
	std::string("SLASH"),
	std::string("PERCENT"),
	
	std::string("LEFTPER"),
	std::string("RIGHTPER"),
	std::string("SPACE"),
	std::string("POW"),
	
	std::string("NUMBER"),
	std::string("END"),
	std::string("ERROR")
};