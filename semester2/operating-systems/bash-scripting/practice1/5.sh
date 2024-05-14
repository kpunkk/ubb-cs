#!/bin/bash

# stergem aparitiile multiplu de 3 a unui cuvant, dintr-un fisier

if [ ! -f $1 ]; then
	echo $1 is not a file
fi

count=0

while read line; do
	for cuvant in $line; do
		if [ "$cuvant" = "$2" ]; then
			count=`expr $count + 1`
			if [ `expr $count % 3` -ne 0 ]; then
				echo $cuvant $count
			fi
 		else 
			echo $cuvant
		fi	
	done
done < $1	
