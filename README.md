shell
=====

Project to build a UNIX shell from scratch.

Builtin commands:
  'quit','exit' or ':q'     - to quit shell
   
   'history'                - view prevoiusly entered commands
  
    '(%) &''            - use '&' as an argument at the end of any command to run it in the background.

    '!%d' where %d is an int - prefix an int with '!' to rerun the %dth command entered 


Features:

The shell currently reapes finsihed backgrounf processes/


The shell purosely does not exit on Ctrl-C, use a command to quit instead


Simple IO redirection is also currently supported -
'>' will redirect the output of a command to a specifies file e.g. ls > dir.txt
'>' will redirect stdin of a command from a file eg. sort < dir.txt

These can be uses in conjuntion but '<' must precede '>' e.g sort < dir.txt > sorted.txt

TODO:
Improve builting commands - more arguments, help, more commands, etc

Allow for inline editing.

Implement pipelining   

Author: Ewan Crawford
        ewan.cr@gmail.com
