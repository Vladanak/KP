#pragma once
#include "stdafx.h"
#include "Parm.h"
#include "In.h"
#include "Error.h"
#include "IT.h"
#include "LT.h"


namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		ofstream *stream;
	};
	//прототипы в основном
	static const LOG INITLOG = { L"", NULL };
	LOG getlog(wchar_t logfile[]);
	void writeLine(const LOG &log, char *c, ...);
	void writeLine(const LOG &log, wchar_t *c, ...);
	void writeLog(const LOG &log);
	void writeParm(const LOG &log, const Parm::PARM &parm);
	void writeIn(const LOG &log, const In::IN &in);
	void writeError(const LOG &log, const Error::ERROR &error);
	void writeLexicalTable(const LOG &log, LT::LexTable &lextable);
	void writeIDtable(const LOG &log, IT::IdTable &IDtable);
	void writeAllTokens(const LOG &log, In::IN &In);
	void writeIntermediateCode(LOG &log, LT::LexTable &lextable);
	void Close(const LOG &log);
}