#!/bin/bash

sed '1d' "$1" | sed '23, $d' 1>"$2" 2>"$3"
# sed '2d' "$1" | sed '3d' | sed '9d' | sed '9d' | sed '17d' | sed '16d' 1>"$2" 2>"$3"
