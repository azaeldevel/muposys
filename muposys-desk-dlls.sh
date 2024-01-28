#!/bin/sh

../core/tools/deps-dll.sh desk/bin/Release/muposys-desk-1.dll desk/bin/desk-installer
../core/tools/deps-dll.sh core/bin/Release/muposys-core-1.dll desk/bin/desk-installer
../core/tools/deps-dll.sh ../cave/bin/Release/cave-mmsql-1.dll desk/bin/desk-installer