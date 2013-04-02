#!/bin/bash
function get_youtube(){
  date=$1
  curl -o index.html http://www.youtube.com/index

  grep data-context-item index.html | while read x; do 
    user=`expr "$x" : ".*data-context-item-user=\"\([^\"]*\)\".*"`
    views=`expr "$x" : ".*data-context-item-views=\"\(.*\) views\".*"`
    duration=`expr "$x" : ".*data-context-item-time=\"\([0-9:]*\)\".*"`
    title=`expr "$x" : ".*data-context-item-title=\"\([^\"]*\)\".*"`
    echo ${views//,/}','$user','$duration','${title//,/"M_CM"}
  done > "youtube/"$date".txt"
}
x=1
while [[ $x -le 50 ]]; do
  date=`(date +"%Y-%m-%d-%H-%M")`
  echo $date
  get_youtube $date
  sleep 60
  x=`expr $x + 1`
done
