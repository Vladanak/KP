#include "stdafx.h"


namespace LT
{
	Entry::Entry(char lexema, int snn, int idxti)
	{
		this->lexema = lexema;
		this->sn = snn;
		this->idxTI = idxti;
	}

	Entry::Entry(char lexema, int snn, char v, int idxti)
	{
		this->operation = v;
		this->lexema = lexema;
		this->sn = snn;
		this->idxTI = idxti;
	}

	LexTable Create(int size)
	{
		if (size >= LT_MAXSIZE) throw ERROR_THROW(117);
		LexTable lextable;
		lextable.maxsize = size;
		lextable.size = NULL;
		lextable.table = new Entry[size];
		return lextable;
	}

	void Add(LexTable &lextable, Entry entry)
	{
		if (lextable.size >= LT_MAXSIZE) throw ERROR_THROW(117);
		lextable.table[lextable.size].idxTI = entry.idxTI;
		lextable.table[lextable.size].lexema = entry.lexema;
		lextable.table[lextable.size].sn = entry.sn;
		lextable.table[lextable.size].operation = entry.operation;
		lextable.table[lextable.size].tokenId = entry.tokenId;
		lextable.size++;
	}

	Entry GetEntry(LexTable &lextable, int n)
	{
		return lextable.table[n];
	}

	void Delete(LexTable &lextable)
	{
		delete lextable.table;
	}
}