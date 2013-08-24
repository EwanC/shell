Wee UNIX shell                                      
==============

Lerning project to build a UNIX shell from scratch.

Can be run from the Weeshell executable in the command line.


Builtin commands
------------------------------------------------------
   'quit','exit' or ':q'     - Quits the  shell
    
   'history'                 - Displays previously entered commands
  
   '[command] &'             - use '&' as an argument at the end of any command to run it in the background.

    '![index]'               - prefix an int with '!' to rerun the command at that index. Indexes can be viewed with the history command

    'cd [path]'              - changes the directory to the specified path. 'cd .' will take you to your home directory. 'cd ..' will take you back a level.

    'setenv [variable] [value]' - crate an environmental variable of specified value. Note enivironmental variables cannot be changed unless you have created them.


Features
-------------------------------------------------------

The shell will reap background processes.

The shell purposly does not exit on Ctrl-C, use a command to quit instead, but will terminate all child processes

IO redirection is also currently supported 
'>' will redirect the output of a command to a specifies file e.g. ls > dir.txt
'>' will redirect stdin of a command from a file eg. sort < dir.txt
'>>' will append stdout to an existing file 
'>&' will redirect stderr as well as stderr the specified file


These can be uses in conjuntion but '<' must precede '>', '>>' or '>&' e.g sort < dir.txt >& sorted.txt


Pipeling is currently supported using the standard '|' symbol but at the moment only one pipeline can be used per command.

Tab completeion for commands although there is some improvement to be done here as some commands are missing and some shouldn't be there.

Thanks to the GNU readline and history libraries there is also inline editing and the ability to scroll through recent commands with the up and doen arrows.


IMPROVEMENTS
-------------------------------------------------------

Allow multiple pipes per command.

Improve tab completion results.




Author: Ewan Crawford
        ewan.cr@gmail.com
