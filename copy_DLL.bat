@echo off

xcopy "C:\Siemens\Teamcenter13\bmide\workspace\13000.0.0\h2dev\output\wntx64\packaging\tc\bin\*.dll" "C:\Siemens\Teamcenter13\bin" /C /F /Y

xcopy "C:\Siemens\Teamcenter13\bmide\workspace\13000.0.0\h2dev\output\wntx64\packaging\tc\lib\*.lib" "C:\Siemens\Teamcenter13\lib" /C /F /Y

timeout /t 5

@echo on