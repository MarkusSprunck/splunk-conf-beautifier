rm .\folder1\savedsearches.conf.formated
rm .\folder1\macros.conf.formated
rm .\folder2\savedsearches.conf
rm .\folder2\savedsearches.conf.formated
rm .\folder2\macros.conf
rm .\folder2\macros.conf.formated

cd .\folder1
..\..\dist\Debug\Cygwin-Windows\spl2html.exe savedsearches.conf
..\..\dist\Debug\Cygwin-Windows\spl2html.exe macros.conf
copy .\savedsearches.conf.formated ..\folder2\savedsearches.conf.formated
copy .\macros.conf.formated ..\folder2\macros.conf.formated
cd..

cd ./folder2
..\..\dist\Debug\Cygwin-Windows\spl2html.exe savedsearches.conf.formated
..\..\dist\Debug\Cygwin-Windows\spl2html.exe macros.conf.formated
cd..


