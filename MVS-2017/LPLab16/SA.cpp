#include "stdafx.h"
#include "SA.h"

bool  SemanticAnalyze(LT::LexTable &Lextable, In::IN &InStruct, IT::IdTable &idtable, Log::LOG &log)
{
	bool Standart_LIB = false;
	int isGlavn = 0;
	bool isFunction = false;
	bool choise = true;
	int isBrace = 0;
	bool isBack = false;
	bool Viragenia_Num = true;

	for (int i = 0,j; i < Lextable.size; i++)
	{
		switch (Lextable.table[i].lexema)
		{
		case LEX_NUM:
		{
			j = i;
			if (Lextable.table[i + 1].lexema == LEX_FUNCTION)
			{
				while (Lextable.table[j].lexema != LEX_SEPARATOR)
				{
					if (Lextable.table[j].lexema == LEX_LEFTBRACE)
						break;
					j++;
				}
				if (Lextable.table[j].lexema == LEX_SEPARATOR)
					throw ERROR_THROW(8);
				break;
			}
			break;
		}
		case LEX_FUNCTION:
		{

			if (Lextable.table[i - 1].lexema == LEX_NUM && Lextable.table[i + 1].lexema == LEX_ID && Lextable.table[i + 2].lexema == LEX_LEFTHESIS)
			{
				isFunction = true;
				isBack = true;
			}
			break;
		}
		case LEX_STANDART:
		{
			Standart_LIB = true;
			break;
		}
		case LEX_GLAVN:
		{
			if (isFunction == true || isBack==true)
			{
				throw ERROR_THROW_IN(126, Lextable.table[i].sn, NULL);
				choise = false;
				break;
			}
			isBack = true;
			isGlavn++;
			break;
		}
		case LEX_EQUAL:
		{
			if (Lextable.table[i - 1].lexema == LEX_ID && Lextable.table[i + 1].lexema == LEX_ID) 
			{
				if (idtable.table[Lextable.table[i - 1].idxTI].iddatatype != idtable.table[Lextable.table[i + 1].idxTI].iddatatype)
				{
					throw ERROR_THROW_IN(3, Lextable.table[i].sn, NULL);
					choise = false;
					break;
				}
			}
			if (Lextable.table[i + 1].lexema == LEX_ID && Lextable.table[i + 2].lexema != LEX_LEFTHESIS && Lextable.table[i + 2].lexema != LEX_SEPARATOR)
			{
				int  p = 0;
				while (Lextable.table[i].lexema != LEX_SEPARATOR)
				{
					if (Lextable.table[i].lexema == LEX_ID)
					{
						p = Lextable.table[i].idxTI;
						if (idtable.table[p].iddatatype != IT::NUM)
						{
							Viragenia_Num = false;
							break;
						}
					}
					i++;
				}
				if (Viragenia_Num == false)
				{
					throw ERROR_THROW_IN(107, Lextable.table[i].sn, NULL);
					choise = false;
					break;
				}
			}
			break;
		}
		case LEX_ID:
		{
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].idtype == IT::F && Lextable.table[i + 1].lexema == LEX_EQUAL)
			{
				throw ERROR_THROW_IN(119, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].idtype == IT::F)
			{
				int kol2 = 0;
				int a = idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].idxfirstLE;
				while (Lextable.table[a].lexema != LEX_RIGHTTHESIS)
				{
					if (Lextable.table[a].lexema == LEX_COMMA)
						kol2++;
					a++;
				}
				int kol = 0;
				while (Lextable.table[i].lexema != LEX_RIGHTTHESIS)
				{
					if (Lextable.table[i].lexema == LEX_COMMA)
						kol++;
					i++;
				}
				if (kol != kol2)
				{
					throw ERROR_THROW_IN(122, Lextable.table[i].sn, NULL);
					choise = false;
				}
				break;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i - 2].lexema == LEX_STEPEN)
			{
				int check;
				check = IT::IsId(idtable, InStruct.tokens[i].token);
				if (idtable.table[check].iddatatype == IT::STR &&  Lextable.table[i - 2].lexema == LEX_STEPEN)
				{
					throw ERROR_THROW_IN(121, Lextable.table[i].sn, NULL);
					choise = false;
					break;
				}
				break;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && (Lextable.table[i - 2].lexema == LEX_SUBSTR || Lextable.table[i - 2].lexema == LEX_STRLEN))
			{
				int check;
				check = IT::IsId(idtable, InStruct.tokens[i].token);
				if (idtable.table[check].iddatatype == IT::NUM && (Lextable.table[i - 2].lexema == LEX_SUBSTR || Lextable.table[i - 2].lexema == LEX_STRLEN))
				{
					throw ERROR_THROW_IN(120, Lextable.table[i].sn, NULL);
					choise = false;
					break;
				}
				break;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].iddatatype == IT::NUM && InStruct.tokens[i + 2].token[0] == char(34))
			{
				throw ERROR_THROW_IN(4, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i+2].lexema != LEX_SUBSTR && idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].iddatatype == IT::STR && Lextable.table[i - 1].lexema == LEX_SEPARATOR && InStruct.tokens[i + 2].token[0] != char(34))
			{
				throw ERROR_THROW_IN(4, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) == -1 && ((Lextable.table[i - 1].lexema != LEX_NUM && Lextable.table[i-2].lexema != LEX_DEF) || (Lextable.table[i - 1].lexema != LEX_FUNCTION && Lextable.table[i - 2].lexema != LEX_NUM )))
			{
				throw ERROR_THROW_IN(105, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if ((IT::IsId(idtable, InStruct.tokens[i].token) != -1 &&
				Lextable.table[i + 1].lexema == LEX_EQUAL &&
				Lextable.table[i + 2].lexema == LEX_ID && 
				Lextable.table[i + 3].lexema == LEX_SEPARATOR))
			{
				throw ERROR_THROW_IN(106, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if ((IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i + 1].lexema == LEX_EQUAL && InStruct.tokens[i+2].isStr==true && (Lextable.table[i + 3].lexema == LEX_PLUS || Lextable.table[i + 3].lexema == LEX_MINUS || Lextable.table[i + 3].lexema ==LEX_DIRSLASH || Lextable.table[i + 3].lexema == LEX_STAR) && InStruct.tokens[i+4].isStr==true))
			{
				throw ERROR_THROW_IN(108, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if ((IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i + 1].lexema == LEX_EQUAL && (Lextable.table[i + 2].lexema == LEX_ID || Lextable.table[i + 2].lexema == LEX_LITERAL) && Lextable.table[i + 3].lexema == LEX_DIRSLASH && InStruct.tokens[i+4].token[0] == char(48) && Lextable.table[i + 5].lexema == LEX_SEPARATOR))
			{
				throw ERROR_THROW_IN(109, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i + 1].lexema == LEX_EQUAL && (Lextable.table[i + 2].lexema == LEX_ID && idtable.table[IT::IsId(idtable, InStruct.tokens[i + 2].token)].iddatatype == IT::NUM) && (Lextable.table[i + 4].lexema == LEX_ID && idtable.table[IT::IsId(idtable, InStruct.tokens[i + 4].token)].iddatatype == IT::NUM))
				break;
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i + 1].lexema == LEX_EQUAL && (Lextable.table[i + 2].lexema == LEX_LITERAL && InStruct.tokens[i+2].isStr==false) && (Lextable.table[i + 4].lexema == LEX_LITERAL && InStruct.tokens[i + 4].isStr == false))
				break;
			if ((IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i + 1].lexema == LEX_EQUAL && (Lextable.table[i + 2].lexema == LEX_ID) || Lextable.table[i + 2].lexema == LEX_LITERAL) && (Lextable.table[i + 3].lexema == LEX_DIRSLASH || Lextable.table[i + 3].lexema == LEX_PLUS || Lextable.table[i + 3].lexema == LEX_MINUS || Lextable.table[i + 3].lexema == LEX_STAR)
				&& (Lextable.table[i + 4].lexema == LEX_LITERAL || Lextable.table[i + 4].lexema == LEX_ID) && Lextable.table[i + 5].lexema == LEX_SEPARATOR)
			{
				throw ERROR_THROW_IN(3, Lextable.table[i].sn, NULL);
				choise = false;
			}
			break;
		}
		case LEX_SUBSTR:
		{
			int schet = 0;
			int b = i;
			while (Lextable.table[b].lexema != LEX_RIGHTTHESIS)
			{
				if (Lextable.table[b].lexema == LEX_COMMA)
					schet++;
				b++;
			}
			if(schet!=2)
				throw ERROR_THROW_IN(122, Lextable.table[i].sn, NULL);
			if (Standart_LIB == false)
			{
				throw ERROR_THROW_IN(116, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (Lextable.table[i + 2].lexema == LEX_LITERAL && InStruct.tokens[i + 2].isStr == false)
			{
				throw ERROR_THROW_IN(120, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (Lextable.table[i + 4].lexema == LEX_LITERAL && InStruct.tokens[i + 4].isStr == true)
			{
				throw ERROR_THROW_IN(3, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (Lextable.table[i + 6].lexema == LEX_LITERAL && InStruct.tokens[i + 6].isStr == true)
			{
				throw ERROR_THROW_IN(3, Lextable.table[i].sn, NULL);
				choise = false;
			}
			break;
		}
		case LEX_BACK:
		{
			if (isFunction == true)
			{
				isBack = false;
				isFunction = false;
				break;
			}
			else 
			{ 
				if(isGlavn==0)
					throw ERROR_THROW_IN(126, Lextable.table[i].sn, NULL);
				isBack = false;
				break;
			}
			break;
		}
		case LEX_LEFTBRACE:
		{
			isBrace++;
			if (isBrace == 2)
				throw ERROR_THROW(8);
			break;
		}
		case LEX_BRACELET:
		{
			isBrace--;
			break;
		}
		case LEX_STEPEN:
		{
		int schet = 0;
		int b = i;
		while (Lextable.table[b].lexema != LEX_RIGHTTHESIS)
		{
			if (Lextable.table[b].lexema == LEX_COMMA)
				schet++;
			b++;
		}
		if (schet != 1)
			throw ERROR_THROW_IN(122, Lextable.table[i].sn, NULL);
			if (Standart_LIB == false)
			{
				throw ERROR_THROW_IN(116, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (Lextable.table[i + 2].lexema == LEX_LITERAL && InStruct.tokens[i + 2].isStr == true)
			{
				throw ERROR_THROW_IN(121, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (Lextable.table[i + 4].lexema == LEX_LITERAL && InStruct.tokens[i + 4].isStr == true)
			{
				throw ERROR_THROW_IN(121, Lextable.table[i].sn, NULL);
				choise = false;
			}
			break;
		}
		case LEX_STRLEN:
		{
			int schet = 0;
			int b = i;
			while (Lextable.table[b].lexema != LEX_RIGHTTHESIS)
			{
				if (Lextable.table[b].lexema == LEX_COMMA)
					schet++;
				b++;
			}
			if (schet != 0)
				throw ERROR_THROW_IN(122, Lextable.table[i].sn, NULL);
			if (Standart_LIB == false)
			{
				throw ERROR_THROW_IN(116, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (Lextable.table[i + 2].lexema == LEX_LITERAL && InStruct.tokens[i + 2].isStr == false)
			{
				throw ERROR_THROW_IN(120, Lextable.table[i].sn, NULL);
				choise = false;
			}
			break;
		}
		}
	}
	if (isBack == true)
	{
		throw ERROR_THROW(126);
		choise = false;
	}
	if (isGlavn == 0)
	{
		throw ERROR_THROW(123);
		choise = false;
	}
	else if (isGlavn > 1)
	{
		throw ERROR_THROW(118);
		choise = false;
	}
	return choise;
}