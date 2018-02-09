#include "stdafx.h"
#include "Generation.h"
#include "SA.h"
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "");
	Log::LOG log = Log::INITLOG;
	bool sintaksis = false;
	bool semantika = false;
	try
	{               
		Parm::PARM parm = Parm::getparm(argc, argv);					// Получение аргументов		
		log = Log::getlog(parm.log);									// Создание log				
		Log::LOG out = Log::INITLOG;									// Инициализация log файла	
		out = Log::getlog(parm.out);									// Создаие out файла		
		Log::writeLog(log);												// Запись протокола			
		Log::writeParm(log, parm);										// Запись параметров		
		In::IN in = In::getin(parm.in, parm.out);						// Получение входящих параметров
		Log::writeIn(log, in);											// Запись входящих параметров	
		LeX::LEX tables = LeX::INITLEX(in, log);				     	// Получение таблицы лексем		
		Log::writeAllTokens(log, in);									// Запись всех фраз			
		Log::writeLexicalTable(log, tables.Lextable);	             	// Запись таблицы лекс.		
		Log::writeIDtable(log, tables.IDtable);	                     	// Запись таблицы индент.	
		Log::writeIntermediateCode(log, tables.Lextable);               // Запись промежуточного кода
		semantika = SemanticAnalyze(tables.Lextable, in, tables.IDtable, log); //запуск семантического анализа
		if (semantika == true)
		{
			MFST::Mfst mfst(tables, GRB::getGreibach());                    // Инициализация для синтаксического анализатора
			MFST_TRACE_START(log);                                          // Шапка
			sintaksis = mfst.start(log);                                    // Старт синтаксического анализа
			if (sintaksis == false)
				throw ERROR_THROW(8);
			mfst.savededucation();                                          // Сохранить правила вывода
			mfst.printrules(log);                                           // Печать дерева разбора
		}
		if (sintaksis == true)
		{
			Generation(tables.Lextable, in.tokens, tables.IDtable);         // Трансляция кода
			PN Polish;                                                      // Объявление переменной Polish польз.типа PN
			if (Polish.CreatePolishNotation(&tables))                       // Построение польской нотации
			{
				*log.stream << "\n-------Polish Notation completed!-------------------";
				Log::writeIntermediateCode(log, tables.Lextable);
			}
		}
		Log::Close(log);												// Закрытие log файла		
		Log::Close(out);												// Закрытие out файла
		system("start.bat");
	}
	catch (Error::ERROR e)
	{
		cout << e.id <<","<< e.message << endl;
		Log::writeError(log, e);                                        // Проброс ошибок в случае их появления
	}
	return 0;
}

