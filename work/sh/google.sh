a=`ps -ef | grep google | wc -l `
count=0
while [ $a -le 2 ]
do
echo "we sleep " 
sleep 10
count=$((count+10))
a=`ps -ef | grep google | wc -l`
done
echo "we wait the $count"
