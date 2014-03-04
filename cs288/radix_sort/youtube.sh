#!/bin/bash
curl -o index.html http://www.youtube.com/index

grep data-context-item index.html | while read x; do 
  user=`expr "$x" : ".*data-context-item-user=\"\([^\"]*\)\".*"`
  views=`expr "$x" : ".*data-context-item-views=\"\(.*\) views\".*"`
  duration=`expr "$x" : ".*data-context-item-time=\"\([0-9:]*\)\".*"`
  title=`expr "$x" : ".*data-context-item-title=\"\([^\"]*\)\".*"`
  echo ${views//,/}','$user','$duration','${title//,/"M_CM"}
done > newtable.txt