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


TODO:
Improve builting commands - more extensible, help, more commands, etc

Facilitate IO

Implement pipelining   

Author: Ewan Crawford
        ewan.cr@gmail.com
