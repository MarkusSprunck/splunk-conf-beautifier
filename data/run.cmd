rm .\folder1\savedsearches.conf.formatted
rm .\folder1\macros.conf.formatted
rm .\folder2\savedsearches.conf
rm .\folder2\savedsearches.conf.formatted
rm .\folder2\macros.conf
rm .\folder2\macros.conf.formatted

cd .\folder1
..\..\dist\Debug\Cygwin-Windows\splunk-conf-beautifier.exe savedsearches.conf
..\..\dist\Debug\Cygwin-Windows\splunk-conf-beautifier.exe macros.conf
copy .\savedsearches.conf.formatted ..\folder2\savedsearches.conf.formatted
copy .\macros.conf.formatted ..\folder2\macros.conf.formatted
cd..

cd ./folder2
..\..\dist\Debug\Cygwin-Windows\splunk-conf-beautifier.exe savedsearches.conf.formatted
..\..\dist\Debug\Cygwin-Windows\splunk-conf-beautifier.exe macros.conf.formatted
cd..


