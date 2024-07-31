#!/bin/sh

salutation="Hello"
echo $salutation
echo "The program $0 is now running"
echo "The second parameter was $2"
echo "The first parameter was $1"
echo "The parameter list was $*"
echo "The parameter list was $#"
echo "The user's home directory is $HOME"

echo "Please enter a new freeting"
read salutation 

echo $salutation
echo "$IFS"
echo "Prompt, right? $PS1 of $PS2"
echo "Process id: $$"
exit 0

