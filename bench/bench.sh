#!/bin/bash


EXE=$1

name=${EXE#../}
name=${name%%/*}
logfile="$name.csv"

# DFE warmup
$EXE 1000x1000-d1-s42.bg

for f in $(ls -v *.bg); do
	b=$(basename $f)
	echo "***** $b *****" >&2

	m=${b%%x*}
	egrep "^${m} " $logfile 2>/dev/null && continue

	sleep 2
	$EXE $f | tee -a $logfile
done


