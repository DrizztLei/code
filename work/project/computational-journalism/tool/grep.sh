#!/bin/bash

grep -a -s "^.*<li><a href=\"http://.*<\/a><\/li>[^M]$" "$1" 1>"$2" 2>"$3"
