#pragma once
#define Head "import sys \n" //"шапка" нашей генерации

void Generation(LT::LexTable &Lextable, In::StToken *tokens, IT::IdTable & idtable); //создаём прототип для функции генерации