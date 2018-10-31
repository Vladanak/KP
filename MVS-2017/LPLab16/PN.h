#pragma once
#include "stdafx.h"


struct PN
{
	LT::Entry result[10000]; // ’ранит преобразованное выражение в польской нотации
	int size = 0;
	enum { LH = '(', RH = ')', PLUS = '+', MINUS = '-', MULT = '*', DEV = '/', EQUAL = '=' };

	int prior(char operation); // ѕриоритет операции
	int searchExpression(int number, LeX::LEX *tables); // ѕоиск начала выражени€ в таблице лексем
	bool CreatePolishNotation(LeX::LEX *tables);
};