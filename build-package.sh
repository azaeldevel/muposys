#!/bin/sh
#https://gist.github.com/mjakeman/0add69647a048a5e262d591072c7facb


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


./copy-deps.sh $1 $DIRECTORY $TARGET "--check-againg"
