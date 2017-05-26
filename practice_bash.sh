#!/bin/bash

echo try out bash

function read_array {
	echo Enter your array:
	read -a vals
#length of an array
	len=${#vals[@]}
	echo len=$len
	for (( i=0; i<$len; i++))
	do
		echo vals[$i] = ${vals[$i]}
	done
}


function list_all_files {
	for file in `ls` ; do
		echo $file
	done
}

function read_file_linewise {
	i=1
	cat $0 | while read line
		do
			echo $i: $line
			((i++))
		done
}


#read_array
#list_all_files
read_file_linewise
