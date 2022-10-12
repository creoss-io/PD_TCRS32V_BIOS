set TIMEPAD=%TIME: =0%
7z a -r "WS__%DATE:~2,2%%DATE:~5,2%%DATE:~8,2%_%TIMEPAD:~0,2%%TIMEPAD:~3,2%%TIMEPAD:~6,2%__LAMBDA____".zip 	WS\*   -i!crs32v_crt0.o -xr!*.o -i!crs32v_crt0.o

:: 7z a -r "WS__%DATE:~2,2%%DATE:~5,2%%DATE:~8,2%_%TIMEPAD:~0,2%%TIMEPAD:~3,2%%TIMEPAD:~6,2%__LAMBDA____".zip 	WS\*   -xr!*\Release\*.o
:: 7z a -r "WS__%DATE:~2,2%%DATE:~5,2%%DATE:~8,2%_%TIMEPAD:~0,2%%TIMEPAD:~3,2%%TIMEPAD:~6,2%__LAMBDA____".zip 	WS\*   -i!crs32v_crt0.o -xr!*.o -i!crs32v_crt0.o

