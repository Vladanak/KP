#pragma once
#define PARM_IN					L"-in:"
#define PARM_OUT				L"-out:"
#define	PARM_LOG				L"-log:"
#define	PARM_MAX_SIZE			300
#define	PARM_LOG_DEFAULT_EXT	L".log"
#define LT_FLAG					"-lt" 
#define IT_FLAG					"-it"


namespace Parm
{
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE], out[PARM_MAX_SIZE], log[PARM_MAX_SIZE]; //задаём параметры типа wchar_t с размером PARM_MAX_SIZE
		bool ltLogging, itLogging;
	};

	PARM getparm(int argc, _TCHAR* argv[]); //прототип типа PARM для принятия параметров
};