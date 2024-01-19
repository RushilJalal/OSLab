echo "enter file/directory name"
read path
if [[ -d $path ]]
then
echo "It is a directory"
elif [[ -f  $path ]]
then
echo "It is a regular file"
else
echo "not found"
fi
