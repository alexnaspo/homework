#!/bin/ksh
file="/Users/Alex/CompSci/processes.txt"
IFS=': \;'
i=0
while read -r f1 f2 f3 f4 f5 f6  
  do 
    id[i]="$f2"
    at[i]="$f4"
    et[i]="$f6"

    ((i++))
  done <"$file"
i=0
currTime=0
for x in ${id[@]}
do
  for c in {1..${et[$i]}}
  do

      print "Current Time: $currTime"
      print "\tProcess Id: $x"
      ft[i]=$currTime

      ((currTime++))
  done

  print "Finish time ${ft[$i]}"
  ((i++))
done

  