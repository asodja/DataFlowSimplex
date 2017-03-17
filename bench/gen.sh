#!/bin/bash

GENLP=../ORIG/genlp
format=${1:-bg}

DST=.
#mkdir -f $DST

function gen {
	for size in $*; do
		echo Generating $size ...
		m=$size
		n=$size
		f="$DST/${m}x${n}-d1-s42.bg"
		test -f "$f" && continue
		$GENLP bg $m $n -d1 -s42 --int >"$f"
	done
}

gen 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000

