###Splunk search processing language beautifier (spl2html)

####Function

1) Call spl2html.exe  
 
```cmd
./splunk-conf-formater.exe savedsearches.conf
```

2) Input not formated savedsearches.conf file:

```txt
[my search #4]
alert.digest_mode = True
alert.suppress = 0
alert.track = 0
auto_summarize = 1
auto_summarize.dispatch.earliest_time = -3mon@d
cron_schedule = 0 0 * * *
search = index=_internal sourcetype=s*| stats latest(source) as source latest(sourcetype) as sourcetype by message| table source message sourcetype

[my search #5]
auto_summarize.dispatch.earliest_time = -1d@h
cron_schedule = 0 0 * * *
search = index=_internal| head 1| eval numberString = tostring(123456.789, "commas")| table numberString

[my search #6]
auto_summarize.dispatch.earliest_time = -1d@h
cron_schedule = 0 0 * * *
enableSched = 1
search = index=_internal| head 1| eval first1 = "123 | search | 456"| eval second2= "123 | 'search | 456'"| eval third3= "123       | \"search | 456\""| table first1 second2 third3
```

3) Output formated text file with the name savedsearches.conf.formated:

```txt
[my search #4]
alert.digest_mode = True
alert.suppress = 0
alert.track = 0
auto_summarize = 1
auto_summarize.dispatch.earliest_time = -3mon@d
cron_schedule = 0 0 * * *
search = index=_internal sourcetype=s*
      | stats latest(source) as source latest(sourcetype) as sourcetype by message
      | table source message sourcetype

[my search #5]
auto_summarize.dispatch.earliest_time = -1d@h
cron_schedule = 0 0 * * *
search = index=_internal
         | head 1
         | eval numberString = tostring(123456.789, "commas") 
         | table numberString

[my search #6]
auto_summarize.dispatch.earliest_time = -1d@h
cron_schedule = 0 0 * * *
enableSched = 1
search = index=_internal
      | head 1
      | eval first1 = "123 | search | 456"
      | eval second2= "123 | 'search | 456'"
      | eval third3= "123       | \"search | 456\""
      | table first1 second2 third3
```

####Development
-----------
- Compiler: cygwin c++ (windows 7)
- IDE:      netbeans 8 
- Status:   first draft


####Limitations
-----------
- works with ASCII files (you have to convert from UTF-8 if needed)

