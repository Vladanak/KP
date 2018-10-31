#include "stdafx.h"
#define GRB_ERROR_SERIES 600


namespace GRB
{
	Greibach greibach(NS('S'), TS('$'), 6,
		Rule(NS('S'), GRB_ERROR_SERIES + 0, 5,   //  —труктура программы
			Rule::Chain(3, TS('B'), TS(';'), NS('S')),
			Rule::Chain(10,TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(11,TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(9, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(4, TS('g'), TS('{'), NS('N'), TS('}'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 3, 2,
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')),  // параметры ф-ии
			Rule::Chain(2, TS('t'), TS('i'))   
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 4, 7,  // возможные конструкции в ф-и€х
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(6, TS('o'), TS('('), NS('E'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('o'), TS('('), NS('E'), TS(')'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3, TS('b'), NS('E'), TS(';'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2, 17, // выражени€
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('i'), NS('E')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(3, TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(4, TS('s'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('e'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('p'), TS('('), NS('W'), TS(')')),
			Rule::Chain(5, TS('e'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(5, TS('s'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('p'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 5, 4, // принимаемые параметры ф-ии
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 1, 8, // знаки
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(2, TS('/'), NS('E')),
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(3, TS('/'), NS('E'), NS('M'))
		)
	);

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)  //конструктор цепочки - праыой части правила(кол-во символов в цепочке, терминал или нетерминал...)
	{
		nt = new GRBALPHABET[size = psize];    //цепочка терминалов
		int*p = (int*)&s;     //присваиваем символ указателю п
		for (short i = 0; i < psize; ++i)
			nt[i] = (GRBALPHABET)p[i]; //заполн€ем цепочку терминалов
	};

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) //конструктор правила
	{															//(нетерминал, идентификатор диагностического сообщени€, количество цепочек(правых частей правила), множество цепочек (правых частей правила)
		nn = pnn;    //нетерминал
		iderror = piderror; //идентификатор
		chains = new Chain[size = psize]; //место дл€ цепочки
		Chain* p = &c;
		for (int i = 0; i < size; i++)
			chains[i] = p[i]; //заполн€ем множество цепочек
	};

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)//конструктор гграматики √рейбаха(стартовый символ, дно стека, количество правил, правила...)
	{
		startN = pstartN; //стартовый символ
		stbottomT = pstbottom;//дно стека
		rules = new Rule[size = psize];//выдел€ем пам€ть
		Rule*p = &r;
		for (int i = 0; i < size; i++) 
			rules[i] = p[i];//заполн€ем правила
	};
	Greibach getGreibach() { return greibach; }; //получить грамматику

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule) //получить правило (левый символ правила, возвращаемое правило грамматики)
	{
		short rc = -1;
		short k = 0;
		while (k < size&&rules[k].nn != pnn)
			k++;   //пока   меньше количества правил и пока левый символ правила не равен парметру ф-ции
		if (k < size)
			prule = rules[rc = k];    //возвращаемое правило граматики равно правилу с индексом  
		return rc; //возвращаетс€ номер правила или -1
	};

	Rule Greibach::getRule(short n) //получить правило по номеру
	{
		Rule rc;      //создаЄм правило рц
		if (n < size)
			rc = rules[n];  //присваиваем правилу рц правило н
		return rc; //возвращаем созданное правило
	};

	char*Rule::getCRule(char*b, short nchain) //получить правило в виде N->цепочка (буфер, номер цепочки(правой части) в правиле)
	{
		char bchain[200]; //строка
		b[0] = Chain::alphabet_to_char(nn); b[1] = '-'; b[2] = '>'; b[3] = 0x00; //терминал -> 
		chains[nchain].getCChain(bchain); //получает правую сторонц правила
		strcat_s(b, sizeof(bchain) + 5, bchain);//добавл€ем строку (куда, с какого элемента, строку)
		return b;
	};

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j) //получить следующую за j подход€щую цепочку, вернуть еЄ номер или -1 
	{                                                                //(первый символ цепочки, возвращаема€ цепочка, номер цепочки)
		short rc = -1;
		while (j < size&&chains[j].nt[0] != t)
			++j;
		rc = (j < size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	};

	char* Rule::Chain::getCChain(char* b) //получить правую сторону правила
	{
		for (int i = 0; i < size; i++)
			b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	};
};