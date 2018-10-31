#include "stdafx.h"
typedef stack<short> MFSTSTSTACK;	//стек автомата

#define NS(n) GRB::Rule::Chain::N(n)  //директива для нетерминала
#define TS(n) GRB::Rule::Chain::T(n)  //директива для терминала
#define ISNS(n) GRB::Rule::Chain::isN(n)  //проверка на нетерминал

#define MFST_DIAGN_MAXSIZE 2* ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

//ФОРМАТИРОВАННЫЙ ВЫВОД ДЛЯ СИНТАКСИЧЕСКОГО АНАЛИЗА

#define MFST_TRACE_START(LOG) *log.stream <<"\t \t Синтаксический Анализ"<< endl << setw(4) << left << "Шаг" <<":" \
	<< setw(20) << left << "Правило"  \
	<< setw(30) << left << "Входная лента" \
	<< setw(20) << left << "Стек" << endl;

#define MFST_TRACE1(LOG) *log.stream << setw(4) << left << ++FST_TRACE_n << ":" \
	<< setw(20) << left << rule.getCRule(rbuf, nrulechain)  \
	<< setw(30) << left << getCLenta(lbuf, lenta_position) \
	<< setw(20) << left << getCSt(sbuf) << endl;

#define MFST_TRACE2(LOG) *log.stream << setw(4) << left << FST_TRACE_n << ":" \
	<< setw(20) << left << " "  \
	<< setw(30) << left << getCLenta(lbuf, lenta_position) \
	<< setw(20) << left << getCSt(sbuf) << endl;

#define MFST_TRACE3(LOG) *log.stream << setw(4) << left << ++FST_TRACE_n << ":" \
	<< setw(20) << left << " "  \
	<< setw(30) << left << getCLenta(lbuf, lenta_position) \
	<< setw(20) << left << getCSt(sbuf) << endl;

#define MFST_TRACE4(LOG, c) *log.stream << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << c << endl;
#define MFST_TRACE5(LOG, c) *log.stream << setw(4) << left <<  FST_TRACE_n << ": " << setw(20) << left << c << endl;
#define MFST_TRACE6(LOG,c,k) *log.stream << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << c << k << endl;

#define MFST_TRACE7(LOG) *log.stream << setw(4) << left << state.lenta_position << ": "\
	<< setw(20) << left << rule.getCRule(rbuf, state.nrulechain) << endl;


namespace MFST
{
	struct MfstState				 //состояние автомата(для сохранения)
	{
		short lenta_position;		//позиция на ленте
		short nrule;				//номер текущего правила
		short nrulechain;			//номер текущей цепочки
		MFSTSTSTACK st;				//стек автомата
		MfstState();                //конструктор
		MfstState(
			short pposition,		//позиция на ленте
			MFSTSTSTACK pst,		//стек автомата
			short pnrulechain		//номер текущей цепочки, текущего правила
		);
		MfstState(
			short pposition,		//позиция на ленте
			MFSTSTSTACK pst,		//стек автомата
			short pnrule,			//номер текущего правила
			short pnrulechain		//номер текущей цепочки, текущего правила
		);
	};

	struct Mfst					//магазинный автомат	
	{
		enum RC_STEP			//код возврата функции step
		{
			NS_OK,				//найдено правило и цепочка, цепочка записана в стек
			NS_NORULE,			//не найдено правило грамматики (ошибки в грамматике)
			NS_NORULECHAIN,		//не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,			//неизвестный нетерминальный символ грамматики
			TS_OK,				//текущий символ ленты == вершине стека, продвинулась лента, рор стека
			TS_NOK,				//текущий символ ленты != вершине стека, восстановлено состояние
			LENTA_END,			//текущая позиция ленты >= lenta_size
			SURPRISE			//неожиданный код возврата ( ошибка в step)
		};
		struct MfstDiagnosis		//диагностика
		{
			short lenta_position;	//позиция на ленте
			RC_STEP rc_step;		//код завершения шага
			short nrule;			//номер правила
			short nrule_chain;		//номер цепочки правила
			MfstDiagnosis();
			MfstDiagnosis(			//диагностика
				short plenta_position,	//позиция на ленте
				RC_STEP prc_step,		//код завершения шага
				short pnrule,			//номер правила
				short pnrule_chain		//номер цепочки правила
			);
		}
		diagnosis[MFST_DIAGN_NUMBER];	//последние самые глубокие сообщения
		GRBALPHABET* lenta;				//перекодированная(TS/NS) лента (из LEX)
		short lenta_position;			//текущая позиция на ленте
		short nrule;					//номер текущего правила
		short nrulechain;				//номер текущей цепочки, текущего правила
		short lenta_size;				//размер ленты
		GRB::Greibach grebach;			//грамматика Грейбах
		LeX::LEX lex;					//результат работы лексического анализатора
		MFSTSTSTACK st;					//стек автомата		
		stack<MfstState> storestate;	//стек для сохранения состояний
		Mfst();
		Mfst(
			LeX::LEX plex,			    //результат работы лексического анализатора
			GRB::Greibach pgrebach		//грамматика Грейбах
		);
		char* getCSt(char*buf);			//получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25);  //лента: n символов с pos
		char* getDiagnosis(short n, char*buf);			//получить n-ую строку диагностики или 0х00
		bool savestate(const Log::LOG &log);			//сохранить состояние автомата
		bool reststate(const Log::LOG &log);			//восстановить состояние автомата
		bool push_chain(					//поместить цепочку правила в стек
			GRB::Rule::Chain chain  //цепочка правила
		);
		RC_STEP step(const Log::LOG &log);	//выполнить шаг автомата
		bool start(const Log::LOG &log);	//запустить автомат
		bool savediagnois(
			RC_STEP pprc_step			//код завершения шага
		);
		bool printrules(const Log::LOG &log);	//вывести последовательность правил
		struct Deducation	//вывод
		{
			short size;		//количество шагов в выводе
			short* nrules;	//номера правил нрамматики
			short* nrulechains; //номера цепочек правил грамматики (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; }; //конструктор
		}deducation;
		bool savededucation();	//сохранить дерево вывода
	};
};