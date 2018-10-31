#include "stdafx.h"
#include "Generation.h"


ofstream outfile("D://FIRST//KP//MVS-2017//Generation.py");
bool isFunction = false;
int idFunc;
int buf;


void Generation(LT::LexTable &Lextable, In::StToken *tokens, IT::IdTable &idtable)
{
	outfile << Head;
	for (int i = 0; i < Lextable.size; i++)
	{
		switch (Lextable.table[i].lexema)
		{
		case LEX_NUM:
			break;
		case LEX_GLAVN:
		{
			isFunction = true;
			outfile << "\ndef glavn():";
			break;
		}
		case LEX_FUNCTION:
		{
			isFunction = true;
			idFunc = Lextable.table[i + 1].idxTI;
			buf = Lextable.table[i + 1].idxTI;
			outfile << "def " << idtable.table[buf].id;
			i++;
			break;
		}
		case LEX_LEFTBRACE:
		{
			outfile<<"\n" << "    ";
			break;
		}
		case LEX_BRACELET:
		{
			if (isFunction) 
			    outfile << "\n" << "\r";
			break;
		}
		case  LEX_DEF:
		{
			if (Lextable.table[i + 1].lexema == LEX_NUM && Lextable.table[i + 3].lexema == LEX_EQUAL)
			{
				outfile << tokens[i + 2].token << '=' << tokens[i + 4].token << "\n    ";
				i += 5;
				break;
			}
			while (Lextable.table[i].lexema != LEX_SEPARATOR)
				i++;
			break;
		}
		case LEX_STANDART:
		{
			outfile << "import MyLibrary as My" << "\n";
			break;
		}
		case LEX_ID:
		{
			int y;
			y = Lextable.table[i].idxTI;
			if (Lextable.table[i - 2].lexema == LEX_OUT)
				outfile << idtable.table[y].id;
			else
			{
				if (idtable.table[y].iddatatype == IT::STR || IT::NUM && Lextable.table[i - 2].lexema != LEX_OUT)
					outfile << idtable.table[y].id;
			}
			break;
		}
		case LEX_EQUAL:
		{
			outfile << "=";
			break;
		}
		case LEX_SEPARATOR:
		{
			if(isFunction)
				outfile << "\n    ";
			break;
		}
		case LEX_STRLEN:
		{
			outfile << "len";
			break;
		}
		case LEX_SUBSTR:
		{
			outfile << "My.Substr";
			break;
		}
		case LEX_LITERAL:
		{
			if (tokens[i].isLiteral ==true)
			{
				if (tokens[i].isStr == true)
					outfile << tokens[i].token; 
				else
				{
					int tp;
					tp = atoi(tokens[i].token);
					if (tp > INT_MAXSIZE)
					{
						throw ERROR_THROW(6);
					}
					else
					{
						if (tp < INT_MIN)
							throw ERROR_THROW(6);
					}
					outfile << tp;
					break;
				}
			}
			break;
		}
		case LEX_OUT:
		{
			outfile << "print ";
			break;
		}
		case LEX_LEFTHESIS:
		{
			outfile << "(";
			break;
		}
		case LEX_RIGHTTHESIS:
		{
			outfile << ")";
			if (Lextable.table[i + 1].lexema == LEX_LEFTBRACE)
				outfile << ':';
			break;
		}
		case LEX_PLUS:
		{
			outfile << "+";
			break;
		}
		case LEX_STAR:
		{
			outfile << "*";
			break;
		}
		case LEX_MINUS:
		{
			outfile << "-";
			break;
		}
		case LEX_DIRSLASH:
		{
			outfile << "/";
			break;
		}
		case LEX_COMMA:
		{
			outfile << ",";
			break;
		}
		case LEX_BACK:
		{
			if (isFunction) 
				outfile <<"return ";
			break;
		}
		case LEX_STEPEN:
		{
			outfile << "My.Stepen";
			break;
		}
		default:
		{
			outfile << tokens[i].token;
			break;
		}
		}
	}
	outfile << "\nglavn()";
	outfile << "\ninput()";
	outfile.close();
}