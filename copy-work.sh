#/bin/sh
src="./work"
backup="/home/elvis/Backup"
origin="/home/elvis/work"
if [ ! -d "${src}" ];
then
    echo "Direct for ${src} not exists . Generate it."
    mkdir "${src}"
fi
if [ ! -d "${backup}" ];
then
    echo "Not enough privilege for generate the ${backup}."
    exit 1
fi
if [ ! -d "${origin}" ];
then
    echo "Sources not exists.Terminated here."
    exit 1
fi
rm -rf "${backup}"
mkdir "${backup}"
mv ${src} ${backup}
cp -rf ${origin} .
