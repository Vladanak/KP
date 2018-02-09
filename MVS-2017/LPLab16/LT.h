#pragma once
#include"Error.h"
#include <string>

#define	LEXEMA_FIXSIZE	1			// Фиксированный размер таблицы лексем
#define	LT_MAXSIZE		65536		// Максимальный размер таблицы лексем
#define	LT_TI_NULLDX	0xffffffff	// Пустота в таблице лексем
#define	LEX_NUM		    't'			// Целый
#define	LEX_STR		    't'			// Строка
#define LEX_OBJECT      't'			// Обьект						
#define	LEX_ID			'i'			// Индентификатор
#define	LEX_LITERAL		'l'			// Литерал
#define	LEX_FUNCTION	'f'			// Функция
#define	LEX_DEF		    'd'			// Def
#define LEX_STANDART    'B'         // Объявления встроенной библиотеки
#define LEX_STRLEN      'e'         // Встроенная библиотека strlen
#define LEX_SUBSTR      's'         // Встроенная библиотека substr
#define LEX_STEPEN      'p'         // Встроенная библиотека stepen
#define	LEX_BACK		'b'			// Return
#define	LEX_OUT		    'o'			// Out
#define	LEX_GLAVN		'g'			// Glavn
#define	LEX_SEPARATOR	';'			// ;
#define	LEX_COMMA		','			// ,
#define	LEX_LEFTBRACE	'{'			// {
#define	LEX_BRACELET	'}'			// }
#define	LEX_LEFTHESIS	'('			// (
#define	LEX_RIGHTTHESIS	')'			// )
#define	LEX_PLUS		'+'			// +
#define	LEX_MINUS		'-'			// -
#define	LEX_STAR		'*'			// *
#define	LEX_DIRSLASH	'/'			// /
#define	LEX_EQUAL		'='			// =
#define	LEX_TYPE_NUM	    "num"	
#define	LEX_TYPE_STR	    "str"	
#define	LEX_TYPE_FUNCTION	"function"	
#define	LEX_TYPE_VARIABLE	"variable"	
#define LEX_TYPE_PARAMETR	"parametr"	
#define LEX_TYPE_LITERAL	"literal"
#define LEX_TYPE_STANDART	"vstroen"

namespace LT
{
	struct Entry
	{
		char lexema;			// Лексема
		int sn;					// Номер строки в исходном тексте
		int idxTI;				// Индекс в таблице идентификаторов или LT_TI_NULLIDX
		int tokenId = 0;        // Номер токена
		char operation;         // Операция
		std::string value;
		Entry() {};             // Конструктор по умолчанию
		Entry(char lexema, int snn, int idxti = LT_TI_NULLDX);	// Конструктор
		Entry(char lexema, int snn, char v, int idxti = LT_TI_NULLDX); // Конструктор

	};
	struct LexTable						// Экземпляр таблицы лексем
	{
		int maxsize;					// Ёмкость таблицы лексем
		int size;						// Текущий размер таблицы лексем
		Entry* table;					// Массив строк таблицы лексем
	};
	LexTable Create(int size);			// Ёмкость < LT_MAXSIZE
	void Add(LexTable &lextable, Entry entry);	// Экземпляр таблицы лексем, строка таблицы лексем
	Entry GetEntry(LexTable &lextable, int n);	// Экземпляр таблицы лексем, номер получаемой строки
	void Delete(LexTable &lextable);	// Удалить таблицу лексем (освободить память)
}