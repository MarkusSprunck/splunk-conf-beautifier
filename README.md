###Splunk search processing language beautifier and to html converter (spl2html)

####Function

1) Call spl2html.exe (takes an input file and as parameter '-h') 
 
```cmd
./spl2html.exe -h simple.txt
```

2) Input not formated text file:

```txt
search source = mytabl1 mycolumn = value | stats avg( mycolumn ) by mycolumn | search TST123 = value | fields mycolumn, avg(mycolumn) | eval test = "abc"."xyz".'ghf'."'hij'".'hhh' | search source = mytabl1 mycolumn = value | table ABC
```

3) Expected Resul: Output formated text file (with the extension .result):

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

####Development
-----------
- Compiler: cygwin c++ (windows 7)
- IDE:      netbeans 8 
- Status:   first draft

