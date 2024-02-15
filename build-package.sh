#!/bin/sh
#https://gist.github.com/mjakeman/0add69647a048a5e262d591072c7facb

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


cp -rp $PLATFORM/lib/gdk-pixbuf-2.0 $DIRECTORY/lib/
cp -rp $PLATFORM/share/icons $DIRECTORY/share/

mkdir -p $DIRECTORY/share/glib-2.0/schemas
cp -rp $PLATFORM/share/glib-2.0/schemas/* $DIRECTORY/share/glib-2.0/schemas
glib-compile-schemas $DIRECTORY/share/glib-2.0/schemas
cp desk/config-dev $DIRECTORY

echo "copiying octetos deps.."
cp core/bin/$TARGET/muposys-core-1.dll $DIRECTORY
cp ../cave/bin/$TARGET/cave-mmsql-0.dll $DIRECTORY
cp ../cave/bin/$TARGET/cave-mmsql-1.dll $DIRECTORY
cp desk/bin/$TARGET/mps-desk-v1.exe $DIRECTORY
cp desk/bin/$TARGET/muposys-desk-1.dll $DIRECTORY


echo "copiying platform deps.."
list=`ntldd desk/bin/$TARGET/$1`
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
		echo "$dll"
		continue
	fi
	echo "Procesando $dll.."
	cp -v $dll $DIRECTORY
	$0 $dll $DIRECTORY
done
