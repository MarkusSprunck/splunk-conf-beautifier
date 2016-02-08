#pragma once
//
// file: formater_parameter.h
//

const map_string getReplace() {
    map_string replace;

    replace["\t"] = " ";
    replace["  "] = " ";

    return replace;
}

const map_string getReplaceHtml() {
    map_string replace;

    replace["<"] = "&lt;";
    replace[">"] = "&gt;";
    replace["   "] = "&nbsp;&nbsp;&nbsp; ";
    replace["\t"] = "&nbsp;&nbsp;&nbsp; ";

    return replace;
}

enum eCommand {
    KEYWORD = 1, MARK = 2, INCREMENT = 4
};

const map_command getCommand() {
    map_command command;

    command["by"] = KEYWORD;
    command["as"] = KEYWORD;
    command["and"] = KEYWORD;
    command["or"] = KEYWORD;
    command["avg"] = KEYWORD;
    command["tostring"] = KEYWORD;

    command["index" ] = KEYWORD;
    command["table" ] = KEYWORD | INCREMENT;

    // Streaming Commands | START
    command["addinfo" ] = KEYWORD | INCREMENT;
    command["anomalydetection" ] = KEYWORD | INCREMENT;
    command["append" ] = KEYWORD | INCREMENT;
    command["arules" ] = KEYWORD | INCREMENT;
    command["bin" ] = KEYWORD | INCREMENT;
    command["bucketdir" ] = KEYWORD | INCREMENT;
    command["cluster" ] = KEYWORD | INCREMENT;
    command["convert" ] = KEYWORD | INCREMENT;
    command["dedup" ] = KEYWORD | INCREMENT;
    command["eval" ] = KEYWORD | INCREMENT;
    command["extract" ] = KEYWORD | INCREMENT;
    command["fieldformat" ] = KEYWORD | INCREMENT;
    command["fields" ] = KEYWORD | INCREMENT;
    command["fillnull" ] = KEYWORD | INCREMENT;
    command["head" ] = KEYWORD | INCREMENT;
    command["highlight" ] = KEYWORD | INCREMENT;
    command["iconify" ] = KEYWORD | INCREMENT;
    command["iplocation" ] = KEYWORD | INCREMENT;
    command["join" ] = KEYWORD | INCREMENT;
    command["lookup" ] = KEYWORD | INCREMENT;
    command["makemv" ] = KEYWORD | INCREMENT;
    command["multikv" ] = KEYWORD | INCREMENT;
    command["mvexpand" ] = KEYWORD | INCREMENT;
    command["nomv" ] = KEYWORD | INCREMENT;
    command["rangemap" ] = KEYWORD | INCREMENT;
    command["regex" ] = KEYWORD | INCREMENT;
    command["reltime" ] = KEYWORD | INCREMENT;
    command["rename" ] = KEYWORD | INCREMENT;
    command["replace" ] = KEYWORD | INCREMENT;
    command["rex" ] = KEYWORD | INCREMENT;
    command["search" ] = KEYWORD;
    command["spath" ] = KEYWORD | INCREMENT;
    command["strcat" ] = KEYWORD | INCREMENT;
    command["streamstats" ] = KEYWORD | INCREMENT;
    command["tags" ] = KEYWORD | INCREMENT;
    command["transaction" ] = KEYWORD | INCREMENT;
    command["typer" ] = KEYWORD | INCREMENT;
    command["where" ] = KEYWORD | INCREMENT;
    command["untable" ] = KEYWORD | INCREMENT;
    command["xmlkv" ] = KEYWORD | INCREMENT;
    command["xmlunescape" ] = KEYWORD | INCREMENT;
    command["xpath" ] = KEYWORD | INCREMENT;
    command["xyseries" ] = KEYWORD | INCREMENT;
    // Streaming Commands | END

    // Generating commands | START
    command["crawl" ] = KEYWORD | INCREMENT;
    command["datamodel" ] = KEYWORD | INCREMENT;
    command["dbinspect" ] = KEYWORD | INCREMENT;
    command["eventcount" ] = KEYWORD | INCREMENT;
    command["gentimes" ] = KEYWORD | INCREMENT;
    command["inputcsv" ] = KEYWORD | INCREMENT;
    command["Inputlookup" ] = KEYWORD | INCREMENT;
    command["loadjob" ] = KEYWORD | INCREMENT;
    command["makeresults" ] = KEYWORD | INCREMENT;
    command["metadata" ] = KEYWORD | INCREMENT;
    command["multisearch" ] = KEYWORD | INCREMENT;
    command["pivot" ] = KEYWORD | INCREMENT;
    command["searchtxn" ] = KEYWORD | INCREMENT;
    command["set" ] = KEYWORD | INCREMENT;
    command["tstats" ] = KEYWORD | INCREMENT;
    // Generating commands | END

    // Transforming commands | START
    command["addtotals" ] = KEYWORD | INCREMENT;
    command["chart" ] = KEYWORD | INCREMENT;
    command["cofilter" ] = KEYWORD | INCREMENT;
    command["contingency" ] = KEYWORD | INCREMENT;
    command["makecontinuous" ] = KEYWORD | INCREMENT;
    command["mvcombine" ] = KEYWORD | INCREMENT;
    command["rare" ] = KEYWORD | INCREMENT;
    command["stats" ] = KEYWORD | INCREMENT;
    command["timechart" ] = KEYWORD | INCREMENT;
    command["top" ] = KEYWORD | INCREMENT;
    command["xyseries" ] = KEYWORD | INCREMENT;
    // Transforming commands | END

    return command;
}

/* Copyright (c) 2003-2004 by Markus W. Sprunck. ALL RIGHTS RESERVED. */
