#!/bin/sh

# Run test suite for xwadtools.
# Needs freedoom.wad from freedoom 0.7 (where it's named doom2.wad).

# usage: runtests.sh [-c] [path/to/wad]
# By default, wad is searched for in current dir, $DOOMWADDIR,
# /usr/share/games/doom
# -c: check pre-existing results only, don't run tests


# Have tests for:
#lswad
#spitwad
#wadext
#qmus2mid
#midi3mus
#wadwhat
#wadldc
#wadlc
#bsp
#waddwd
#idbsp
#wreject
#dm2au
#wadcat
#wadtex
#wadflat
#wadsprit
#wadpat
#wadtxls
#mkwad
#dmpsmap
#dmpsmu
#slige
#wadwhich
#raw2sfx
#idmultigen
#wadgc (need better tests though)
#deutex
#deusf
#warm
#wadps
#mkqmap
#trigcalc
#mkgipal
#mkpopal
#mkxppal
#pal2c
#wadconvgame

# Need tests for:
#acc-raven
#listacs
#mergewad
#swantbls... don't know how to tell if the output is correct
#mktran... don't know how to tell if the output is correct
#raw2ppm... I don't understand how to make it work
#wadconvgfx... requires netpbm

# No tests planned for:
#tkwadcad
#tkwadcad-extract-iwads
#slbsp.sh
#slidbsp.sh
#slwarm.sh
#xew

testcount=0
failcount=0
okcount=0
passed=""
failed=""

find_iwad() {
	if [ -n "$1" ]; then
		IWAD="$1"
	else
		for i in . "$DOOMWADDIR" /usr/share/games/doom; do
			if [ -z "$IWAD" -a -e "$i/freedoom.wad" ]; then
				IWAD="$i/freedoom.wad"
			fi
		done
	fi

	if [ -z "$IWAD" ]; then
		echo "Can't find freedoom.wad anywhere" 2>&1
		exit 1
	fi

#IWAD=$( readlink -f "$IWAD" )
	echo "Using IWAD: $IWAD"
}

passtest() {
	echo "PASSED"
	okcount=$(( okcount + 1 ))
	passed="$passed $1"
}

failtest() {
	echo "FAILED ($2)"
	failcount=$(( failcount + 1 ))
	failed="$failed $1"
}

run_one_test() {
	name="$( basename "$1" )"
	testcount=$(( testcount + 1 ))

	if [ "$checkonly" != "yes" ]; then
		echo -n "Running test: $name: "

		sh -e "tests/$name" > "output/$name.output" 2>"output/$name.stderr"
		local status="$?"

		if [ "$status" -ne 0 ]; then
			echo "warn: $name exited with non-zero status: $status, err output was:"
			cat "output/$name.stderr"
			echo "-----"
		fi
	else
		echo -n "Checking results of $name: "
	fi

	if ! diff -w "expected/$name.output" "output/$name.output"; then
		failtest "$name" stdout
	else
		passtest "$name"
	fi
}

while [ -n "$1" ]; do
	case "$1" in
		-c) checkonly="yes" ;;
		*) IWAD="$1" ;;
	esac
	shift
done

if [ -z "$IWAD" ]; then
	find_iwad
fi

export IWAD

for t in tests/*; do
	run_one_test "$t"
done

echo
echo "-----"
echo "Passed $okcount of $testcount tests, failed $failcount"
if [ -n "$failed" ]; then
	echo "Failed tests:$failed"
fi
if [ "$failcount" = "0" ]; then
	echo "=== PASSED"
else
	echo "=== FAIL"
fi
exit 0
