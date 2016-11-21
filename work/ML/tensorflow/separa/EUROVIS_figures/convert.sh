for file in $(ls ./)
do
	echo ${file}
	convert ${file} "`basename ${file} pdf`png"
done
