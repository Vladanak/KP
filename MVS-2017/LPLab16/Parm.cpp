#include "stdafx.h"


namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM myParm = { L"", L"", L"", false, false };
		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			if (wcsncmp(argv[i], PARM_IN, wcslen(PARM_IN)) == 0)
				wcscpy_s(myParm.in, argv[i] + wcslen(PARM_IN));
			else
			{
				if (wcsncmp(argv[i], PARM_OUT, wcslen(PARM_OUT)) == 0)
					wcscpy_s(myParm.out, argv[i] + wcslen(PARM_OUT));
				else
				{
					if (wcsncmp(argv[i], PARM_LOG, wcslen(PARM_LOG)) == 0)
						wcscpy_s(myParm.log, argv[i] + wcslen(PARM_LOG));
					else
					{
						// -- CONVERT WCHAR_T TO STRING -- //
						wstring ws(argv[i]);
						string str(ws.begin(), ws.end());
						// -- ------- ------- -- ------ -- //
						if (str.find(LT_FLAG) != string::npos)
							myParm.ltLogging = true;
						else
						{
							if (str.find(IT_FLAG) != string::npos)
								myParm.itLogging = true;
						}
					}
				}
			}
		}
		if (myParm.in[0] == NULL) { throw ERROR_THROW(100); }
		if (myParm.out[0] == NULL) { wcscpy_s(myParm.out, myParm.in); }
		if (myParm.log[0] == NULL)
		{
			wcscpy_s(myParm.log, myParm.in);
			wcsncat_s(myParm.log, PARM_LOG_DEFAULT_EXT, sizeof(PARM_LOG_DEFAULT_EXT));
		}
		return myParm;
	};
}