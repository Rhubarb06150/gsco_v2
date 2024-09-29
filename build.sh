#!/bin/bash

echo "Building..."&&
if g++ -c src/*.cpp&&g++ *.o -o build/GSC_Build -lsfml-graphics -lsfml-window -lsfml-system&&rm *.o; then
	echo "Built!"
	echo -n "Run? [y/n] "
	read run
	if [ $run = "y" ] || [ $run = "Y" ]; then
		build/GSC_Build
	fi
else
	echo "\033[31mError!\033[0;0m"
	echo -n "Run previous build? [y/n]"
	read run
	if [ $run = "y" ] || [ $run = "Y" ]; then
		build/GSC_Build
	fi
fi
