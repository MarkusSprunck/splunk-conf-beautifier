# spl2html
Splunk search processing language beautifier and to html converter

Function
--------
- the executable spl2html.exe (takes an input file and as parameter '-h')

	  	./spl2html.exe -h simple.txt

- formats the file (line breaks, intending, etc.)
- creates a formated text file (with the extension .result)
- creates a second html file (with the extension .html)

Expected Result
---------------
- Input file:

search source = mytabl1 mycolumn = value | stats avg( mycolumn ) by mycolumn | search TST123 = value | fields mycolumn, avg(mycolumn) | eval test = "abc"."xyz".'ghf'."'hij'".'hhh' | search source = mytabl1 mycolumn = value | table ABC

- Output file:

<style TYPE='text/css'> <!-- p { line-height: 100%; } body { font-family: 'courier new'; line-height: 100%; } --> </style>
</font><font color=black></font><font color=blue>search</font><font color=black> </font><font color=blue>source</font><font color=black>=mytabl1 mycolumn=value</p>
&nbsp;&nbsp;&nbsp;</font><font color=black></font><font color=black>|</font><font color=black> </font><font color=blue>stats</font><font color=black> </font><font color=blue>avg</font><font color=black>(mycolumn) </font><font color=blue>by</font><font color=black> mycolumn</p>
&nbsp;&nbsp;&nbsp;</font><font color=black></font><font color=black>|</font><font color=black> </font><font color=blue>search</font><font color=black> TST123=value</p>
&nbsp;&nbsp;&nbsp;</font><font color=black></font><font color=black>|</font><font color=black> </font><font color=blue>fields</font><font color=black> mycolumn</p>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><font color=black></font><font color=black>,</font><font color=black>  avg(mycolumn)</p>
&nbsp;&nbsp;&nbsp;</font><font color=black></font><font color=black>|</font><font color=black> </font><font color=blue>eval</font><font color=black> test=</font><font color=#04B404>"abc"</font><font color=black>.</font><font color=#04B404>"xyz"</font><font color=black>.</font><font color=gold>'ghf'</font><font color=black>.</font><font color=#04B404>"'hij'"</font><font color=black>.</font><font color=gold>'hhh'</font><font color=black></p>
&nbsp;&nbsp;&nbsp;</font><font color=black></font><font color=black>|</font><font color=black> </font><font color=blue>search</font><font color=black> </font><font color=blue>source</font><font color=black>=mytabl1 mycolumn=value</p>
&nbsp;&nbsp;&nbsp;</font><font color=black></font><font color=black>|</font><font color=black> </font><font color=blue>table</font><font color=black> ABC</p>



Development
-----------
- Compiler: cygwin c++ (windows 7)
- IDE:      netbeans 8 
- Status:   first draft

