
spl2html.exe : build/spl2html.o build/formater.o build/formater_test.o  build/line_status.o build/string_utils.o

	g++ -g -o spl2html build/spl2html.o build/formater.o  build/formater_test.o build/line_status.o  build/string_utils.o -lstdc++ 

build/formater.o : source/formater.cpp
	g++ -g  -std=c++11  -c source/formater.cpp -o build/formater.o
	
build/formater_test.o : source/formater_test.cpp
	g++ -g  -std=c++11 -c source/formater_test.cpp -o build/formater_test.o

build/spl2html.o : source/spl2html.cpp
	g++ -g -std=c++11 -c source/spl2html.cpp -o build/spl2html.o

build/line_status.o : source/line_status.cpp
	g++ -g -std=c++11 -c source/line_status.cpp -o build/line_status.o
	
build/string_utils.o : source/string_utils.cpp
	g++ -g -std=c++11 -c source/string_utils.cpp -o build/string_utils.o
	
all : spl2html.exe
     
clean :
	-rm spl2html.exe build/spl2html.o build/formater.o build/formater_test.o build/line_status.o build/string_utils.o
