..\dist\Debug\Cygwin-Windows\spl2html.exe toString.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe simple.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe long.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe subsearch.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe join.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe eval-if.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe strings.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe strings-single-quote.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe append.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe brackets.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe to_string_commas_locale.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe to_string_commas_locale_hair_space_before_point.txt
..\dist\Debug\Cygwin-Windows\spl2html.exe not_existing_file.txt

cd ./folder1
..\..\dist\Debug\Cygwin-Windows\spl2html.exe .\savedsearches.conf
copy .\savedsearches.conf.formated ..\folder2\savedsearches.conf.formated
cd..

cd ./folder2
..\..\dist\Debug\Cygwin-Windows\spl2html.exe savedsearches.conf.formated
cd..


