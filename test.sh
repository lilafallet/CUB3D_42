#!/bin/sh

EXEC=$1
ARGS=$2
if [ -z $EXEC ] || [ -z $ARGS ]
then
	exit 1
fi
SAVE=--save
valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrin.log ./$EXEC $ARGS #$SAVE
cat valgrin.log | egrep --color -B4 -A4 " \([0-9a-zA-Z_]*\.c:[0-9]*\)"
