file_path=$1
line_number=$2

line=$(sed -n "${line_number}p" "$file_path")
echo "$line"
