#pragma once

/**
 * Copyright (C) 2016, Markus Sprunck
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials provided
 *   with the distribution.
 *
 * - The name of its contributor may be used to endorse or promote
 *   products derived from this software without specific prior
 *   written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


const map_string getReplacePrepocessing() {
    map_string replace;
    replace[")"] = " ) ";
    replace["("] = " ( ";
    replace[","] = " , ";
    replace["="] = " = ";
    return replace;
}

const map_string getReplacePostprocessing() {
    map_string replace;
    replace[" ("] = "(";
    replace["  ="] = "=";
    replace[" ="] = "=";
    replace["=  "] = "=";
    replace["= "] = "=";
    replace[" ,"] = ",";
    replace[" )"] = ")";
    replace["( "] = "(";
    replace[") `"] = ")`";
    replace[",  "] = ", ";
    replace[")  "] = ") ";
    return replace;
}

const map_string getReplaceHtml() {
    map_string replace;
    replace["<"] = "&lt;";
    replace[">"] = "&gt;";
    replace[" "] = "&nbsp;";
    replace["\t"] = "&nbsp;&nbsp;&nbsp;";
    return replace;
}

enum eCommand {
    KEYWORD = 1, MARK = 2, INCREMENT = 4, DECREMENT = 8, INCREMENTONCE = 16, DOUBLE_INCREMENTONCE = 32
};

const map_command getCommand() {
    map_command command;

    command["|"] = MARK | INCREMENTONCE;
    command[","] = MARK | DOUBLE_INCREMENTONCE;
    command["["] = MARK | INCREMENT;
    command["]"] = MARK | INCREMENTONCE | DECREMENT;

    command["if"] = KEYWORD;
    command["by"] = KEYWORD;
    command["as"] = KEYWORD;
    command["and"] = KEYWORD;
    command["or"] = KEYWORD;
    command["avg"] = KEYWORD;
    command["tostring"] = KEYWORD;

    command["index" ] = KEYWORD;
    command["table" ] = KEYWORD;
    command["untable" ] = KEYWORD;
    command["first" ] = KEYWORD;
    command["last" ] = KEYWORD;
    command["earliest" ] = KEYWORD;
    command["latest" ] = KEYWORD;
    command["coalesce" ] = KEYWORD;
    command["sourcetype" ] = KEYWORD;
    command["field" ] = KEYWORD;
    command["savedsearch" ] = KEYWORD;
    command["case" ] = KEYWORD;
    command["source" ] = KEYWORD;
    command["type" ] = KEYWORD;
    command["sum" ] = KEYWORD;
    

    // Streaming Commands | START
    command["addinfo" ] = KEYWORD;
    command["anomalydetection" ] = KEYWORD;
    command["append" ] = KEYWORD;
    command["arules" ] = KEYWORD;
    command["bin" ] = KEYWORD;
    command["bucketdir" ] = KEYWORD;
    command["cluster" ] = KEYWORD;
    command["convert" ] = KEYWORD;
    command["dedup" ] = KEYWORD;
    command["eval" ] = KEYWORD;
    command["extract" ] = KEYWORD;
    command["fieldformat" ] = KEYWORD;
    command["fields" ] = KEYWORD;
    command["fillnull" ] = KEYWORD;
    command["head" ] = KEYWORD;
    command["highlight" ] = KEYWORD;
    command["iconify" ] = KEYWORD;
    command["iplocation" ] = KEYWORD;
    command["join" ] = KEYWORD;
    command["lookup" ] = KEYWORD;
    command["makemv" ] = KEYWORD;
    command["multikv" ] = KEYWORD;
    command["mvexpand" ] = KEYWORD;
    command["nomv" ] = KEYWORD;
    command["rangemap" ] = KEYWORD;
    command["regex" ] = KEYWORD;
    command["reltime" ] = KEYWORD;
    command["rename" ] = KEYWORD;
    command["replace" ] = KEYWORD;
    command["rex" ] = KEYWORD;
    command["search" ] = KEYWORD;
    command["spath" ] = KEYWORD;
    command["strcat" ] = KEYWORD;
    command["streamstats" ] = KEYWORD;
    command["tags" ] = KEYWORD;
    command["transaction" ] = KEYWORD;
    command["typer" ] = KEYWORD;
    command["where" ] = KEYWORD;
    command["untable" ] = KEYWORD;
    command["xmlkv" ] = KEYWORD;
    command["xmlunescape" ] = KEYWORD;
    command["xpath" ] = KEYWORD;
    command["xyseries" ] = KEYWORD;
    // Streaming Commands | END

    // Generating commands | START
    command["crawl" ] = KEYWORD;
    command["datamodel" ] = KEYWORD;
    command["dbinspect" ] = KEYWORD;
    command["eventcount" ] = KEYWORD;
    command["gentimes" ] = KEYWORD;
    command["inputcsv" ] = KEYWORD;
    command["Inputlookup" ] = KEYWORD;
    command["loadjob" ] = KEYWORD;
    command["makeresults" ] = KEYWORD;
    command["metadata" ] = KEYWORD;
    command["multisearch" ] = KEYWORD;
    command["pivot" ] = KEYWORD;
    command["searchtxn" ] = KEYWORD;
    command["set" ] = KEYWORD;
    command["tstats" ] = KEYWORD;
    // Generating commands | END

    // Transforming commands | START
    command["addtotals" ] = KEYWORD;
    command["chart" ] = KEYWORD;
    command["cofilter" ] = KEYWORD;
    command["contingency" ] = KEYWORD;
    command["makecontinuous" ] = KEYWORD;
    command["mvcombine" ] = KEYWORD;
    command["rare" ] = KEYWORD;
    command["stats" ] = KEYWORD;
    command["timechart" ] = KEYWORD;
    command["top" ] = KEYWORD;
    command["xyseries" ] = KEYWORD;
    // Transforming commands | END

    return command;
}
