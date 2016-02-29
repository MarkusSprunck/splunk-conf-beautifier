# spl2html
Splunk search processing language beautifier and to html converter

Function
--------
- the executable spl2html.exe (takes an input file and as parameter '-h'), e.g. 
 
```cmd
./spl2html.exe -h simple.txt
```

Expected Result
---------------
- Input not formated text file:

```txt
search source = mytabl1 mycolumn = value | stats avg( mycolumn ) by mycolumn | search TST123 = value | fields mycolumn, avg(mycolumn) | eval test = "abc"."xyz".'ghf'."'hij'".'hhh' | search source = mytabl1 mycolumn = value | table ABC
```

- Output formated text file (with the extension .result):

```txt
search source=mytabl1 mycolumn=value</br>
		| stats avg(mycolumn) by mycolumn</br>
		| search TST123=value</br>
		| fields mycolumn</br>
			, avg(mycolumn)</br>
		| eval test="abc"."xyz".'ghf'."'hij'".'hhh'</br>
		| search source=mytabl1 mycolumn=value</br>
		| table ABC</br>
```

Development
-----------
- Compiler: cygwin c++ (windows 7)
- IDE:      netbeans 8 
- Status:   first draft

