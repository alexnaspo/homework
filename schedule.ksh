#!/bin/ksh
file="/Users/Alex/CompSci/homework/processes.txt"
i=0
cat $file | while IFS=': \;' read -r f1 f2 f3 f4 f5 f6  
do 
  integer id[i]="$f2"
  integer at[i]="$f4" #arrival time
  integer et[i]="$f6" #exec time 
  typeset -E servicetime[i]="$f6" #service time for final calculations
  integer rt[i]=0 #run time so far
  integer current[i]=i

  ((i++))
done
currTime=0

#FCFS NEEDS TO BE FIXED
if [[ ${1} = "FCFS" ]]; then   
  proccess=0
  while [[ ${current[@]} ]]; do
    echo "AVAIL PROJECTS ${current[@]}"
    for y in ${current[@]}; do
      if (( at[$y] <= currTime )); then
        echo "${id[$y]} ran"
        proccess=$y
        schedule[$currTime]=$proccess
        (( currTime++ ))
        (( et[$proccess]-- ))
        if(( et[$proccess] == 0 )); then
          #if the proccess has completed, unset from array
          ft[$proccess]=$currTime
          unset current[$proccess]
        fi
        break
        
      else
        schedule[$currTime]="NONE"
        echo "NO PROCESS AVAIL"
        (( currTime++ ))
        break
        
      fi
    done
  done

  for x in ${schedule[@]}; do
    echo $x
  done


#SRT
elif [[ ${1} = "SRT" ]]; then
  shortest=0
  while [[ ${current[@]} ]]; do
    #while there are processes still left
    if(( et[$shortest] == 0 )); then
      #if the proccess has completed, unset from array
      ft[$shortest]=$currTime
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
  
    if (( et[$shortest] >= 0 )); then
      print "Current Time: $currTime"
      print "\tProcess ID: ${id[$shortest]}"
      if (( at[$shortest] <= $currTime )); then
        schedule[$currTime]=$shortest
        (( et[$shortest]-- ))
      else
        schedule[$currTime]="NONE"
      fi      
      (( currTime++ ))
    fi
  done

  for x in ${schedule[@]}; do
    echo $x
  done

else 
  echo "Please supply FCFS or SRT as an arg"
  return
fi
#calculate stats
let total=${#id[@]}-1
for y in {0..$total}; do
  let turnaround=${ft[$y]}-${at[$y]}
  let servicetime=${servicetime[$y]}
  let TrTs=$(($turnaround/servicetime))
  echo "======================"
  echo "Process ID: ${id[$y]}"
  echo "Turnaround Time: $turnaround"
  echo "Tr/Ts: $TrTs"
  echo "Throughput: HARD CODED"
  echo "Processor Utilization: HARD CODED"
  echo "======================"
done