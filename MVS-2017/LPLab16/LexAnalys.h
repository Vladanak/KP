#pragma once
#include "IT.h"
#include "LT.h"
#include "In.h"
#include "FST.h"
#include "Log.h"


namespace LeX
{
	struct LEX  //структура для лексем
	{
		LT::LexTable Lextable; //таблица лексем
		IT::IdTable	IDtable; //таблица идентификаторов
	};
	struct Graph //структура для графа
	{
		char Lexema;  //символ лексемы
		FST::FST graph; //граф 
	};
	LEX INITLEX(In::IN, Log::LOG &log); //прототип польз.типа
}