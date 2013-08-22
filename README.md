shell
=====

Project to build a UNIX shell from scratch.

Builtin commands:
  'quit','exit' or ':q'     - to quit shell
   
   'history'                - view prevoiusly entered commands
  
    '(%) &''            - use '&' as an argument at the end of any command to run it in the background.

    '!%d' where %d is an int - prefix an int with '!' to rerun the %dth command entered 

    'cd'  - followed by the directroy to change to


Features:

The shell currently reapes finsihed background processes/

The shell purosely does not exit on Ctrl-C, use a command to quit instead


IO redirection is also currently supported 
'>' will redirect the output of a command to a specifies file e.g. ls > dir.txt
'>' will redirect stdin of a command from a file eg. sort < dir.txt
'>>' will append stdout to an existing file 
'>&' will redirect stderr as well as stderr the specified file


These can be uses in conjuntion but '<' must precede '>', '>>' or '>&' e.g sort < dir.txt >& sorted.txt


Pipeling is currently supported using the standard '|' symbol but at the moment only one pipeline can be used per command




Thanks to the GNU readline library for:

  Inline editing.

  Use of up and down arrow to scroll through previous commands


TODO:

Tab completion

mulitple pipes

ISSUES:

During piping there is a problem reaping child processes.


Author: Ewan Crawford
        ewan.cr@gmail.com
