#!/bin/sh
#https://gist.github.com/mjakeman/0add69647a048a5e262d591072c7facb
	
echo " "
echo "Running for $1"
TARGET=""
DIRECTORY=""
PLATFORM="/ucrt64"

if [ -z "$1" ]
then
	echo "Usage:\tdeps-dll [library] [directory]"
	exit
fi

if [ -z "$2" ]
then
	DIRECTORY="desk/bin/desk-installer"
else 
	DIRECTORY=$2
fi

if [ -z "$3" ]
then
	TARGET="Debug"
else
	TARGET=$3
fi

if [ -f "$DIRECTORY/$NAME" ] ; then
	echo "Already exists $DIRECTORY/$NAME.."
	exit
fi

echo "copiying platform deps.."
list=`ntldd $1`
readarray -t lines <<<"$list"
#echo ${lines[0]}
mkdir -p $DIRECTORY
for line in "${lines[@]}"
do
	#echo "$dll.."
	dll=`sed 's/[^"]*\(C:[^"]*.dll\) ([^"]*)/\1/' <<< "$line"`
	#echo "$dll.."
	WINDIR="$(dirname "${dll}")"
	WINFILE="$(basename "${dll}")"
	if [ -f "$WINFILE" ] ; then
		echo "Skiping $dll.."
		continue
	fi
	#echo "dir:$WINDIR"
	if [ "$WINDIR" = "C:\Windows\SYSTEM32" ]; then
		echo "Skiping $dll.."
		continue
	fi
	if [ "$WINDIR" = "C:\Windows\SYSTEM32" ]; then
		echo "Skiping $dll.."
		continue
	fi
	if ! [ -f "$dll" ] ; then
		echo "Skiping $dll.."
		continue
	fi
	echo "Procesando $dll.."
	cp -v $dll $DIRECTORY
	NAME="$(basename -- $1)"
	if [ -f "$DIRECTORY/$NAME" ] ; then
		echo "Already exists $DIRECTORY/$NAME.."	
		if [ "$4" == "--check-againg" ]
		then
			$0 $dll $DIRECTORY $TARGET "--check-no"		
		fi			
	else 
		$0 $dll $DIRECTORY $TARGET "--check-no"	
	fi 
done
