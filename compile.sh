#!/bin/bash
########################################################################
# This script was created by: Rodrigo Oliveira - rodrigo@thecoreme.org #
# http://thecoreme.org/blog/projects                                   #
# Sep 10 2009                                                          #
# Last update on Sep 21 2011                                           #
#                                                                      #
# Simple script to complie KWarBots (by now)                           #
########################################################################

# test if 'build' dir already exist
if [ ! -d build ]
then
	mkdir build
fi

cd build
cmake ..
make

# if 'kwarbots' exists, the compilation finishes right
if [ ! -f src/kwarbots ]
then
	cd ..

	# just remove old 'kwarbots' compilation
	if [ -f kwarbots ]
	then
		rm kwarbots.shell
	fi

	exit -1
fi

mv src/kwarbots.shell ..
cd ..

echo ""
echo "KWarBots is under heavy development, run 'kwarbots.shell' to test the game."

