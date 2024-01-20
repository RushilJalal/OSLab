find . -type f -name '*.txt' -print | while read filename
do
newname=$(echo $filename | sed 's/\.txt$/.text/')
mv "$filename" "$newname"
echo "Renamed: $filename to $newname" 
done
