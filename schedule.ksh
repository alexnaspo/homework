#!/bin/ksh
file="/Users/Alex/CompSci/homework/processes.txt"
IFS=': \;'
i=0
while read -r f1 f2 f3 f4 f5 f6  
  do 
    integer id[i]="$f2"
    integer at[i]="$f4"
    integer et[i]="$f6"

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
        ((currTime++))
        integer ft[i]=$currTime
    done
  print "================="
  let finishTime=${ft[$i]}
  let arrivalTime=${at[$i]}
  typeset -E serviceTime=${et[$i]}
  let Turnaround=finishTime-arrivalTime

  let TrTs=$((Turnaround/serviceTime))
  print "Turnaround Time: $Turnaround"
  print "Tr/Ts: $TrTs"
  print "Throughput:"
  print "Processor Util:" 
  print "================="
  ((i++))
done

  