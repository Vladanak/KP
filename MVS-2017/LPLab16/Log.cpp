#include "stdafx.h"


namespace Log {

	LOG getlog(wchar_t  logfile[]) {
		LOG logFile;
		logFile.stream = new std::ofstream;
		(*logFile.stream).open(logfile);
		if (!(*logFile.stream).is_open())
			throw ERROR_THROW(110);
		wcscpy_s(logFile.logfile, logfile);
		return logFile;
	}

	void writeLine(LOG &log, char *c, ...) {
		char **p = &c;
		while (*p != 0x00)
			*log.stream << *p;
	}

	void writeLine(const LOG &log, wchar_t *c, ...) {
		wchar_t **p = &c;
		wchar_t *str = new wchar_t[ERROR_MAXSIZE_MESSAGE];
		wcscpy(str, *(p++));
		while (*p != L"")		
			wcscat(str, *(p++));
		char *conv = new char[ERROR_MAXSIZE_MESSAGE];
		wcstombs(conv, str, wcslen(str) + 1);
		*log.stream << conv;
		delete[] conv;
		delete[] str;
	}

	void writeLog(const LOG &log) {
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		char* format = "%d.%m.%Y %H:%M:%S";
		strftime(buffer, 80, format, timeinfo);
		*log.stream << "\n----- Протокол ------ Дата: " << buffer << " --------";
	}

	void writeParm(const LOG &log, const Parm::PARM &parm)
	{
		char inTxt[PARM_MAX_SIZE],
			outTxt[PARM_MAX_SIZE],
			logTxt[PARM_MAX_SIZE];
		wcstombs(inTxt, parm.in, wcslen(parm.in) + 1);
		wcstombs(outTxt, parm.out, wcslen(parm.out) + 1);
		wcstombs(logTxt, parm.log, wcslen(parm.log) + 1);
		*log.stream << "\n----- Параметры --------";
		*log.stream << "\n-in: " << inTxt << "\n-out: " << outTxt << "\n-log: " << logTxt;
	}

	void writeIn(const LOG &log, const In::IN &in) {
		*log.stream << "\n---- Исходные данные ------";
		*log.stream << "\nКоличество символов: " << setw(3) << in.size
			<< "\nПроигнорировано	   :" << setw(3) << in.ignor
			<< "\nКоличество строк   :" << setw(3) << in.lines;
	}

	void writeError(const LOG &log, const Error::ERROR &e) {
		if (log.stream == NULL)
		{
			cout << "\nОшибка " << e.id << ": " << e.message << ", строка " << e.inext.line << ", позиция "
		    << e.inext.col << endl << endl;
		}
		else 
		{

			*log.stream << "\nОшибка " << e.id << ": " << e.message << ", строка " << e.inext.line << ", позиция "
				<< e.inext.col << endl << endl;
		}
	}

	void writeLexicalTable(const LOG &log, LT::LexTable &Lextable)
	{
		int x = 0;
		*log.stream << "\n---- Таблица лексем ------\n";
		if (Lextable.size > 0)
			*log.stream << setw(10) << left << x + 1;
		for (int i = 0; i < Lextable.size; i++)
		{
			if (x < Lextable.table[i].sn)
			{
				x = Lextable.table[i].sn;
				*log.stream << endl << setw(10) << left << x + 1;
			}
			*log.stream << Lextable.table[i].lexema;
		}
	}

	void writeAllTokens(const LOG &log, In::IN &In)
	{
		*log.stream << "\n---- Таблица слов ------\n" <<
			setw(5) << left << "№" <<
			setw(10) << left << "Line" <<
			setw(15) << left << "isLiteral" <<
			setw(20) << left << "Token" << endl;
		for (int i = 0; i < In.TokenCount; i++)
		{
			*log.stream <<
				setw(5) << left << i <<
				setw(10) << left << In.tokens[i].line <<
				setw(15) << left << ((In.tokens[i].isLiteral) ? ("true") : ("false")) <<
				setw(20) << left << In.tokens[i].token << endl;
		}
	}

	void writeIDtable(const LOG &log, IT::IdTable &IDtable)
	{
		*log.stream << "\n---- Таблица идентификаторов ------\n" <<
			setw(5) << left << "№" <<
			setw(10) << left << "Name" <<
			setw(13) << left << "DataType" <<
			setw(15) << left << "IdType" <<
			setw(17) << left << "Ind tokenlist" <<
			setw(20) << left << "Value" << endl;
		for (int i = 0; i < IDtable.size; i++)
		{
			*log.stream << setw(5) << left << i <<
				setw(10) << left <<
				setw(10) << left << IDtable.table[i].id <<
				setw(13) << left;
			if (IDtable.table[i].iddatatype == IT::NUM)
				*log.stream << LEX_TYPE_NUM;
			if (IDtable.table[i].iddatatype == IT::STR)
				*log.stream << LEX_TYPE_STR;
			*log.stream << setw(15) << left;
			switch (IDtable.table[i].idtype)
			{
			case IT::F:*log.stream << LEX_TYPE_FUNCTION; break;
			case IT::V:*log.stream << LEX_TYPE_VARIABLE; break;
			case IT::P:*log.stream << LEX_TYPE_PARAMETR; break;
			case IT::L:*log.stream << LEX_TYPE_LITERAL; break;
			case IT::S:*log.stream << LEX_TYPE_STANDART; break;
			}
			*log.stream << setw(17) << left;
			if (IDtable.table[i].idxfirstLE == -1)
				*log.stream << ("default");
			else
				*log.stream << IDtable.table[i].idxfirstLE;

			if (IDtable.table[i].iddatatype == IT::NUM)
				*log.stream << IDtable.table[i].value.vint;
			else
				if (IDtable.table[i].iddatatype == IT::STR)
					*log.stream << ((IDtable.table[i].value.vstr.len > 0) ? (IDtable.table[i].value.vstr.str) : (""));
			*log.stream << endl;
		}
	}
	void writeIntermediateCode(LOG &log, LT::LexTable &Lextable)
	{
		int pb = NULL;
		char*buffer = new char[1024];
		*log.stream << "\n---------Промежуточный код------------------------------\n";
		for (int i = 0; i < Lextable.size; i++)
		{
			buffer[pb] = Lextable.table[i].lexema;
			pb++;
			if (Lextable.table[i + 1].sn != Lextable.table[i].sn)
			{
				buffer[pb] = '\0';
				if (Lextable.table[i].sn < 10)
					*log.stream << '0';

				*log.stream << Lextable.table[i].sn << ' ';
				*log.stream << buffer << endl;
				pb = NULL;
			}
		}
	}
	void Close(const LOG &log)
	{
		(*log.stream).close();
	};
}