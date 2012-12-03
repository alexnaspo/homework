#!/bin/ksh
file="/Users/Alex/CompSci/homework/processes.txt"
IFS=': \;'
i=0
if [[ ${1} = "FCFS" ]]; then   
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
elif [[ ${1} = "SRT" ]]; then
  file="/Users/Alex/CompSci/homework/processes.txt"

  i=0
  cat $file | while IFS=': \;' read -r f1 f2 f3 f4 f5 f6  
    do 
      integer id[i]="$f2"
      integer at[i]="$f4" #arrival time
      integer et[i]="$f6" #exec time 
      integer rt[i]=0 #run time so far
      integer current[i]=i

      ((i++))
    done


    currTime=0
    shortest=0
    while [[ ${current[@]} ]]; do
      #while there are processes still left

      if(( et[$shortest] == 0 )); then
        #if the proccess has completed, unset from array
        unset current[$shortest]
        for x in ${current[@]}; do
          #set shortest to first index in array of current proccesses
          shortest=$x
          break
        done
      fi
      for y in ${current[@]}; do
        #loop through processes that are still available
        if (( at[$y] <= currTime )); then
          #has this proccess arrived yet?
          if (( et[$y] < et[$shortest] )); then
            #set shortest process index
            shortest=$y            
          fi
        fi
      done
      (( et[$shortest]-- ))
      if (( et[$shortest] >= 0 )); then
        print "Current Time: $currTime"
        print "\tProcess ID: ${id[$shortest]}"
        schedule[$currTime]=$y
        
        (( currTime++ ))
      fi
    done  
    
else 
  echo "Please supply FCFS or SRT as an arg"
fi