#pragma once
#define IN_MAX_LEN_TEXT 1024*1024  //директива для обозначения максимальной длины текста
#define IN_CODE_ENDL '\n'          //директива для обозначения перехода на новую строку


/* SIMBOLS:
SEP - ( ) * + - = , / { } ;
PR - пробел
NS - новая строка
QUOTE - ""
F - запрещённый
T - разрешённый
I - игнорируемый
*/


#define IN_CODE_TABLE {\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::STAB, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::STAB, IN::T, IN::QUOTE, IN::T, IN::T, IN::T, IN::T, IN::T, IN::SEP, IN::SEP, IN::SEP, IN::SEP, IN::SEP, IN::SEP, IN::T, IN::SEP, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::SEP, IN::T, IN::SEP, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::SEP, IN::SEP, IN::SEP, IN::T, IN::T, \
	\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::F, IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T \
}


namespace In
{
	struct StToken //структура для токена(слова)
	{
		int line;  // строка в которой находится фраза
		char token[1024]; //массив токенов типа char
		bool isLiteral; // Является ли литералом
		bool isStr = false;// Является ли литерал строкой
	};
	struct IN //структура для таблицы кодироков
	{
		enum { T = 1024, F = 2048, I = 4096, SEP = 8192, STAB = 16384, SEPS = 32768, QUOTE = 65536 };
		int code[256];
		int size = NULL;
		int lines = NULL;
		int ignor = NULL;
		int TokenCount;
		unsigned char* text;
		StToken *tokens;
	};
	IN getin(wchar_t infile[], wchar_t logfile[]);
	void add_token(IN &g, char* &buffer, int &pos_buf, bool &isLiteral, bool &isStr); //прототип для добавления токена(слова) с параметрами
}