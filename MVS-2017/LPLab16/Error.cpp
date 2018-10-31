#include "stdafx.h"
#include <iostream>


namespace Error
{
	//массив ошибок
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "[Системная] Недопустимый код ошибки"),
		ERROR_ENTRY(1, "[Системная] Системный сбой"),ERROR_ENTRY_NODEF(2),
		ERROR_ENTRY(3, "[Семантическая] Несоответствие типов"),
		ERROR_ENTRY(4, "[Семантическая] Несоответствие присваиваемого типа типу переменной"),
		ERROR_ENTRY(5, "[Лексическая] Неопознанный символ"),
		ERROR_ENTRY(6, "[Семантическая] Выход за предел допустимого значения переменной"),
		ERROR_ENTRY(7, "[Семантическая] Не хватает закрывающей кавычки"),
		ERROR_ENTRY(8, "[Синтаксическая] Ошибка в синтакическом анализе.Неизвестное правило разбора!Сверьтесь с разрешёнными комбинациями цепочек!"),
        ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "[Системная] Параметр -in должен быть задан"),
		ERROR_ENTRY(101, "[Семантическая] Отсутствие главной функции"),
		ERROR_ENTRY(102, "[Входящая] Превышена длина строкового литерала "),
		ERROR_ENTRY(103, "[Лексическая] Попытка переопределения"),
		ERROR_ENTRY(104, "[Системная] Превышена длина входного параметра"),
		ERROR_ENTRY(105, "[Лексическая] Отсутствует предварительное определение"),
		ERROR_ENTRY(106, "[Семантическая] Попытка использования операции присваивания между двумя идентификаторами"),
		ERROR_ENTRY(107, "[Семантическая] Обнаружены str идентификаторы в целочисленном выражении"),
		ERROR_ENTRY(108, "[Семантическая] Обнаружена неопознанная операция между строками"),
		ERROR_ENTRY(109, "[Семантическая] Обнаруженно невозможное деление на ноль числа или попытка деления строки на ноль"),
		ERROR_ENTRY(110, "[Системная] Ошибка при открытии файла с исходным кодом(-in)"),
		ERROR_ENTRY(111, "[Лексическая] Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "[Системная] Ошибка при создании файла протокола(-log)"), ERROR_ENTRY_NODEF(113),
		ERROR_ENTRY(114, "[Семантическая] Несоответствие типов"),ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY(116, "[Семантическая] Использование встроенной функции без подключения библиотеки"),
		ERROR_ENTRY(117, "[Лексическая] Превышен размер таблицы лексем"),
		ERROR_ENTRY(118, "[Семантическая] Обнаружена вторая главная функция"),
		ERROR_ENTRY(119, "[Семантическая] Запрещено присваивать значение функции"),
		ERROR_ENTRY(120, "[Семантическая] NUM идентификатор - параметр функций SUBSTR и STRLEN"),
		ERROR_ENTRY(121, "[Семантическая] STR идентификатор - параметр функций STEPEN"),
		ERROR_ENTRY(122, "[Семантическая] Неверное количество параметров при вызове функции"),
		ERROR_ENTRY(123, "[Семантическая] Отсутствие главной функции"),
		ERROR_ENTRY(124, "[Лексическая] Не удалось разобрать слово"), ERROR_ENTRY_NODEF(125),
		ERROR_ENTRY(126, "[Семантическая] Отсутствует возвращение из функции"),
		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "[Синтаксическая] Неверная структура программы"),
		ERROR_ENTRY(601, "[Синтаксическая] Ошибка в операторах"),
		ERROR_ENTRY(602, "[Синтаксическая] Ошибка в выражении"),
		ERROR_ENTRY(603, "[Синтаксическая] Ошибка в параметрах функции"),
		ERROR_ENTRY(604, "[Синтаксическая] Ошибка в конструкции функции"),
		ERROR_ENTRY(605, "[Синтаксическая] Ошибка в принимаемых параметрах функции"),ERROR_ENTRY_NODEF10(610),
		ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		if (id < 0 || id >= ERROR_MAX_ENTRY) { throw ERROR_THROW(0); }
		else { return errors[id]; }
	};
	ERROR geterrorin(int id, int line = 0, int col = 0) //функция проброса ошибок с параметрами
	{
		ERROR a = geterror(id);
		a.inext.line = line;
		a.inext.col = col;
		return a;
	};
}