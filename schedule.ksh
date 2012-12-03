#!/bin/ksh
#file="/Users/Alex/CompSci/homework/processes.txt"
file=${1}
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

#FCFS 
if [[ ${2} = "FCFS" ]]; then   
  process=0
  while [[ ${current[@]} ]]; do
    #while there are processes still left
    for y in ${current[@]}; do
      #loop through avail processes
      if (( at[$y] <= currTime )); then
        #check to see if the process has arrived
        process=$y
        schedule[$currTime]=$process
        (( currTime++ ))
        (( et[$process]-- ))
        if(( et[$process] == 0 )); then
          #if the process has completed, unset from array
          ft[$process]=$currTime
          unset current[$process]
        fi
        break
      else
        schedule[$currTime]="NONE"
        (( currTime++ ))
        break
      fi
    done
  done

#SRT
elif [[ ${2} = "SRT" ]]; then
  shortest=0
  while [[ ${current[@]} ]]; do
    #while there are processes still left
    if(( et[$shortest] == 0 )); then
      #if the process has completed, unset from array
      ft[$shortest]=$currTime
      unset current[$shortest]
      for x in ${current[@]}; do
        #set shortest to first index in array of current processes
        shortest=$x
        break
      done
    fi
    if (( ${#current[@]} == 0 )); then
      #if the final process was finished kill the while loop
      break
    fi
    for y in ${current[@]}; do
      #loop through processes that are still available
      if (( at[$y] <= currTime )); then
        #has this process arrived yet?
        if (( et[$y] < et[$shortest] )); then
          #set shortest process index
          shortest=$y            
        fi
      fi
    done

    if (( et[$shortest] >= 0 )); then #might not be needed
      if (( at[$shortest] <= $currTime )); then
        schedule[$currTime]=$shortest
        (( et[$shortest]-- ))
      else
        schedule[$currTime]="NONE"
      fi      
      (( currTime++ ))
    fi
  done

else 
  echo "Please supply FCFS or SRT as an arg"
  return
fi
#print results
currTime=0
for x in ${schedule[@]}; do
  if (( $x == "NONE")); then
    process_id=$x
  else
    process_id="${id[$x]}"
  fi
  print "Current Time: $currTime"
  print "\tProcess ID: $process_id"
  (( currTime++ ))
done
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
  echo "Throughput: HARD CODED" #WTF IS THIS
  echo "Processor Utilization: HARD CODED" #WTF IS THIS
  echo "======================"
done