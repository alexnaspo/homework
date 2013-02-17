curl -o index.html http://www.youtube.com/index
grep data-context-item index.html | while read x; do 
  user=`expr "$x" : ".*data-context-item-user=\"\([^\"]*\)\".*"`
  echo $user
done > user.txt


grep data-context-item index.html | while read x; do 
  views=`expr "$x" : ".*data-context-item-views=\"\(.*\) views\".*"`
  echo ${views//,/}
done > views.txt

grep data-context-item index.html | while read x; do 
  duration=`expr "$x" : ".*data-context-item-time=\"\([0-9:]*\)\".*"`
  echo $duration
done > duration.txt

grep data-context-item index.html | while read x; do 
  title=`expr "$x" : ".*data-context-item-title=\"\([^\"]*\)\".*"`
  echo $title
done > title.txt

`paste user.txt views.txt duration.txt title.txt > mytable.txt`
