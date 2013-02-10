grep data-context-item index.html | while read x; do 
  user=`expr "$x" : ".*data-context-item-user=\"\(.*\)\" data.*"`
  echo $user
done 

grep data-context-item index.html | while read x; do 
  views=`expr "$x" : ".*data-context-item-views=\"\(.*\) views\".*"`
  echo ${views//,/}
done 

grep data-context-item index.html | while read x; do 
  duration=`expr "$x" : ".*data-context-item-time=\"\([0-9:]*\)\" data-context.*"`
  echo $duration
done

grep data-context-item index.html | while read x; do 
  title=`expr "$x" : ".*data-context-item-title=\"\(.*\)\""`
  echo $title
done 





#<div class="lohp-category-shelf-item context-data-item first-shelf-item last-shelf-item" data-context-item-id="TtSejMmsj-0" data-context-item-type="video" data-context-item-time="0:20" data-context-item-views="2,436,842 views" data-context-item-user="Stealing Axion" data-context-item-title="Ultimate Robot Takeover">
