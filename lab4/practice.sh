function_add() {
a=$1
b=$2
c=`echo $a+$b|bc`
echo $c
}
function_add 3 5
