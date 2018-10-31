#pragma once
#include "stdafx.h"
typedef short GRBALPHABET;                      //объявление своего пользовательского типа(тип short)


namespace GRB
{
	struct Rule									//правило в грамматике Грейбах
	{
		GRBALPHABET  nn;						//нетерминал(левый символ правила) <0
		int iderror;							//идентификатор диагностического сообщения
		short size;								//количество цепочек - правых частей правила
		struct Chain							//цепочка(правая часть правила)
		{
			short size;							//длина цепочки
			GRBALPHABET* nt;					//цепочка терминалов(>0 и нетерминалов (<0)
			Chain() { size = 0; nt = 0; };      //конструктор
			Chain(
				short psize,					//количество символов в цепочке
				GRBALPHABET s, ...				//символы (терминал или нетерминал)
			);
			char* getCChain(char*b);			//получить правую сторону правила
			static GRBALPHABET T(char t) { return GRBALPHABET(t); };		//терминал
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); };		//нетерминал
			static bool isT(GRBALPHABET s) { return s > 0; }				//терминал?
			static bool isN(GRBALPHABET s) { return !isT(s); }				//нетерминал?
			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); };	//GRBALPHABET->char
		}*chains;								//массив цепочек - правых частей правила

		Rule() { nn = 0x00; size = 0; }
		Rule(
			GRBALPHABET pnn,					//нетерминал (<0)
			int iderror,						//идентификатор диагностического сообщения
			short psize,						//количество цепочек - правых частей правила
			Chain c, ...						//множество цепочек - правых частей правила
		);
		char* getCRule(							//получить правило в виде N->цепочка(для распечатки)
			char* b,							//буфер
			short nchain						//номер цепочки(правой части) в правиле
		);
		short Rule::getNextChain(				//получить следующую за j подходящую цепочку, вернуть её номер или -1
			GRBALPHABET t,						//первый символ цепочки
			Rule::Chain & pchain,				//возвращаемая цепочка
			short j								//номер цепочки
		);
	};
	struct Greibach								//грамматика Грейбах
	{
		short size;								//количество правил
		GRBALPHABET startN;						//стартовый символ
		GRBALPHABET stbottomT;					//дно стека
		Rule *rules;							//множество правил
		Greibach() { short size = 0; startN = 0; stbottomT = 0; rules = 0; };
		Greibach(
			GRBALPHABET pstartN,				//стартовый символ
			GRBALPHABET pstbootomT,				//дно стека
			short psize,						//количество правил
			Rule r, ...							//правила
		);
		short getRule(							//получить правило, возвращается номер правила или -1
			GRBALPHABET pnn,					//левый символ правила
			Rule& prule							//возвращаемое правило грамматики
		);
		Rule getRule(short n);					//получить правило по номеру
	};
	Greibach getGreibach();						//получить грамматику
}