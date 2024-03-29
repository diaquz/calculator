﻿#include "Token.h"
string strExpression = "";
short index = 0;
bool invalidSym=false;
string invalidSym_mess="";

//Парсинг строки в число
double parseToDouble()
{
	string val = "";
	bool dot = false;
	while (isdigit(strExpression[index]) || (!dot && strExpression[index] == ','))
	{
		if (strExpression[index] == ',')
			dot = true;

		val += strExpression[index];
		index++;
	}
	return atof(val.c_str());
}

char getNextSymbol()
{
	index++;
	return strExpression[index - 1];
}

void backspaceFunct()
{
	if (strExpression.size() > 0)
	{
		strExpression.pop_back();
	}
}

void clearIndex()
{
	index = 0;
}

void clearFunct()
{
	strExpression = "";
	index = 0;
}

void Token_stream::clearBuffer()
{
	full = false;
}

void Token_stream::putback(Token t)
{
	buffer = t;
	full = true;
}

Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}
	char ch = getNextSymbol();
	double val=0;
	switch (ch)
	{
		case'=':
		case'(': case')': case'+':
		case'-': case'*': case'/':
		case'%': case'^': case'!':
		case sqrtSym:
			return Token{ ch };
		case'0': case'1': case'2': case'3': case'4':
		case'5': case'6': case'7': case'8': case'9':
			index--;
			val = parseToDouble();
			return Token{ digit,val };
		default:
			invalidSymbol("Invalid Symbol");
			break;
	}
}