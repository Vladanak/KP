#include "stdafx.h"
#define MAX_STR_LIT_LEN 250

namespace In
{
	void add_token(IN &StrIn, char* &buffer, int &posbuf, bool &isLiteral,bool &isStr) //функция добавления токена(слова)
	{
		buffer[posbuf] = 0x00;
		strcpy_s((StrIn.tokens[StrIn.TokenCount].token), (posbuf + 1), buffer);
		StrIn.tokens[StrIn.TokenCount].line = StrIn.lines;
		StrIn.tokens[StrIn.TokenCount].isLiteral = isLiteral;
		StrIn.tokens[StrIn.TokenCount].isStr = isStr;
		StrIn.TokenCount++;
		buffer[0] = posbuf = NULL;
	}

	IN getin(wchar_t infile[], wchar_t logfile[]) // функция считывания из входного файла 
	{
		Log::LOG log = Log::getlog(logfile);
		std::ifstream txtfile(infile);
		if (!txtfile.is_open())
			throw ERROR_THROW(110);

		IN StrIn = { IN_CODE_TABLE, NULL, NULL, NULL, NULL };
		StrIn.text = new unsigned char[IN_MAX_LEN_TEXT];
		StrIn.tokens = new StToken[1024];

		bool isLiteral = false;
		bool isStr = false;
		unsigned char p;
		char *buffer = new char[IN_MAX_LEN_TEXT];
		int posbuf = NULL;
		reload:
		while ((p = txtfile.get()) && (!txtfile.eof()))
		{
			switch (StrIn.code[p])
			{
			case IN::STAB:
			{
				if (strlen(buffer))	add_token(StrIn, buffer, posbuf, isLiteral,isStr);
				if (p == IN_CODE_ENDL) StrIn.lines++;
				StrIn.size++;
				isLiteral = false;
				isStr = false;
				break;
			}
			case IN::SEP:
			{
				/*if (StrIn.code[p = txtfile.get()] == IN::SEP && StrIn.text[StrIn.size - 1] != IN::L)
				{
					ERROR_THROW_IN(23, StrIn.lines, NULL);
					StrIn.text[StrIn.size++] = a;
					StrIn.text[StrIn.size++] = p;
					p = txtfile.get();
					goto reload;
					break;
				}*/
				if (strlen(buffer))	add_token(StrIn, buffer, posbuf, isLiteral,isStr);
				buffer[posbuf] = p;
				posbuf++;
				add_token(StrIn, buffer, posbuf, isLiteral,isStr);
				StrIn.size++;
				isLiteral = false;
				isStr = false;
				break;
			}
			case IN::QUOTE:
			case IN::T:
			{
				buffer[posbuf] = p;
				posbuf++;
				StrIn.size++;
				if (p == '\'')
				{
					throw ERROR_THROW_IN(5, StrIn.lines, StrIn.size)
					break;
				}
				if (p == '\"')
				{
					while ((StrIn.code[p = txtfile.get()] != IN::QUOTE) && !txtfile.eof())
					{
						if (p == ';')
							throw ERROR_THROW(7);
						buffer[posbuf] = p;
						posbuf++;
						StrIn.size++;
						if (posbuf > MAX_STR_LIT_LEN) {throw ERROR_THROW(102);}
					}
					buffer[posbuf] = p;
					posbuf++;
					StrIn.size++;
					isLiteral = true;
					isStr = true;
					break;
				}
				break;
			}
			case IN::F:
			{
				throw ERROR_THROW_IN(111, StrIn.lines, StrIn.size);
				break;
			}
			case IN::I:
			{
				StrIn.ignor++;
				StrIn.size++;
				break;
			}
			}

		}
		return StrIn;
	}
}
