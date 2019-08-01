POWDER_BLUE=$(tput setaf 153)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
NORMAL=$(tput sgr0)
GREEN=$(tput setaf 2)
UNDERLINE=$(tput smul)
RED=$(tput setaf 1)

validDirectory="Valid_files"
invalidDirectory="Invalid_files"

if [[ "$1" == "" ]] || [[ "$2" == "" ]] ; then
	echo "Usage: ./test.sh file1.cor file2.cor"
	exit -1
fi

if [ ! -f "corewar" ] ; then
	echo "You should compile first..."
	exit -1
fi

if [ ! -d "$validDirectory" ] || [ ! -d "$invalidDirectory" ] ; then
	./split_files.sh
fi

printf "${BRIGHT}${POWDER_BLUE}Looking for differences between Zaz's VM and ours....\n${NORMAL}"

#for file in $(find $validDirectory/our_cor_files -type f -name '*.s')
#do
	if [ -f "verbosity" ] ; then
		rm verbosity
	fi
	./vm_champs/corewar -v 2 $1 $2 > verbosity
	cycles=`tail -n 2 verbosity | head -n 1 | grep -Eo "\d+"`
	for ((i=1; i<$cycles; i+=100))
	do
		if [ -f "a" ] ; then
			rm a
		fi
		if [ -f "b" ] ; then
			rm b
		fi
		./corewar -d $i $1 $2 | grep -A300 0x0000 | sed 's/ $//g' > a
		./vm_champs/corewar -d $i $1 $2 | grep -A300 0x0000 | sed 's/ $//g' > b
		DIFF=`diff a b`
		ko=0;
		if [[ "$DIFF" ]] ; then
			#printf "${BRIGHT}${WHITE}${RED}KO: cycle %d\n${NORMAL}" $i
			ko=1;
			break
		fi
	done
	if [[ "$ko" == 1 ]] ; then
		for ((j=$i - 100; j<=$i; j++))
		do
			if [ -f "a" ] ; then
				rm a
			fi
			if [ -f "b" ] ; then
				rm b
			fi
			./corewar -d $j $1 $2 | grep -A300 0x0000 | sed 's/ $//g' > a
			./vm_champs/corewar -d $j $1 $2 | grep -A300 0x0000 | sed 's/ $//g' > b
			DIFF=`diff a b`
			ko=0;
			if [[ "$DIFF" ]] ; then
				if [ -f "error.txt" ] ; then
					rm error.txt
				fi
				./vm_champs/corewar -d $j -v 4 $1 $2 > error.txt
				printf "${BRIGHT}${WHITE}${RED}KO: cycle %d\n${NORMAL}" $j
				printf "${BRIGHT}${WHITE}${RED}See more details in error.txt\n${NORMAL}"
				ko=1;
				break
			fi
		done
	else
		printf "${BRIGHT}${GREEN}OK\n"
		./corewar -d $cycles $1 $2 | grep -A300 0x0000 | sed 's/ $//g' > a
		./vm_champs/corewar -d $cycles $1 $2 | grep -A300 0x0000 | sed 's/ $//g' > b
		DIFF=`diff a b`
		ko=0;
		if [[ "$DIFF" ]] ; then
			printf "${BRIGHT}${WHITE}${RED}KO: cycle %d\n${NORMAL}" $i
			break
		else
			printf "${BRIGHT}${WHITE}${GREEN}OK\n${NORMAL}"
		fi
	fi
#done
