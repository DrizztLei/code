#!/usr/bin/env bash

WEB_PAGE="index.html"
OUT="out"
SEDOUT="filter"
ERR="err"
URL="url"
KEYWORD="keyword"

python download.py ${WEB_PAGE}
bash enconv.sh ${WEB_PAGE}
bash grep.sh ${WEB_PAGE} ${OUT} ${ERR}
bash sed.sh ${OUT} ${SEDOUT} ${ERR}
python string_deal.py ${SEDOUT} ${URL} ${KEYWORD}
mkdir  -p `cat keyword`
python director.py ${URL} ${KEYWORD}
