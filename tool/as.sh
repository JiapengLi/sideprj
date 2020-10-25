#!/bin/sh

SCRIPT=`realpath $0`
SCRIPTPATH=`dirname $SCRIPT`
REPOPATH="$SCRIPTPATH/.."
TOOLPATH="$REPOPATH/tool/toolbox"

$TOOLPATH/astyle --style=kr --indent=spaces=4 --pad-oper --pad-header --unpad-paren --suffix=none --align-pointer=name --indent-switches --lineend=windows --convert-tabs --verbose $1


: <<'END'
bla bla
blurfl
END
