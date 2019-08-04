if [[ "$1" == "" ]] || [[ "$2" == "" ]] ; then
	echo "Usage: ./winner.sh [champ1] [champ2]"
	exit -1
fi


echo "Comparing winners..."
echo "Our VM:"
./corewar $1 $2 > a
tail -n 1 a
echo "Zaz's VM:"
./vm_champs/corewar $1 $2 > b
tail -n 1 b
