POWDER_BLUE=$(tput setaf 153)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
NORMAL=$(tput sgr0)
GREEN=$(tput setaf 2)
UNDERLINE=$(tput smul)
RED=$(tput setaf 1)

validDirectory="Valid_files"
invalidDirectory="Invalid_files"

if [[ "$1" == "clean" ]] && [[ "$2" == "" ]] ; then
	rm a b verbosity *.txt
	rm -rf $validDirectory $invalidDirectory
	exit 1
fi

if [[ "$1" == "" ]] || [[ "$2" == "" ]] ; then
	echo "Usage: ./test.sh file1.cor file2.cor"
	exit -1
fi

if [ ! -f "corewar" ] ; then
	echo "You should compile first..."
	exit -1
fi

if [ ! -d "$validDirectory" ] || [ ! -d "$invalidDirectory" ] ; then
	./scripts/split_files.sh
fi

printf "${BRIGHT}${POWDER_BLUE}Looking for differences between Zaz's VM and ours....\n${NORMAL}"

	if [ -f "verbosity" ] ; then
		rm verbosity
	fi
	./vm_champs/corewar -v 2 $1 $2 > verbosity
	cycles=`tail -n 2 verbosity | head -n 1 | grep -Eo "\d+"`
	cycles=$(($cycles-1))
	for ((i=1; i<$cycles; i+=1000))
	do
		printf "Comparing the 2 VMs for cycle %-15d:" $i
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
			printf "${BRIGHT}${WHITE}${RED}%5s\n${NORMAL}" "KO"
			ko=1;
			break
		else
			printf "${BRIGHT}${WHITE}${GREEN}%5s\n${NORMAL}" "OK"
		fi
	done


	if [[ "$ko" == 1 ]] ; then
		for ((j=$i - 1000; j<=$i; j++))
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
				./vm_champs/corewar -d $j -v 4 $1 $2 > cycle_N.txt
				./vm_champs/corewar -d $(($j-1)) -v 4 $1 $2 > cycle_N-1.txt
				diff cycle_N.txt cycle_N-1.txt | grep -v 0x | grep P > cycle$j.txt
				rm cycle_N.txt
				rm cycle_N-1.txt
				printf "${BRIGHT}${RED}\nKO: cycle %d\n${NORMAL}" $j
				printf "${BRIGHT}This is what 'diff a b' returns: (a being your VM dump, and b Zaz's VM dump)\n${NORMAL}"
				diff a b
				printf "${BRIGHT}\nFor more details, see cycle$j.txt\n${NORMAL}"
				ko=1;
				break
			fi
		done
	elif [[ "$i" > "$cycles" ]] ; then
		printf "Comparing the 2 VMs for cycle $cycles (last cycle):"
		./corewar -d $cycles $1 $2 | grep -A300 0x0000 | sed 's/ $//g' > a
		./vm_champs/corewar -d $cycles $1 $2 | grep -A300 0x0000 | sed 's/ $//g' > b
		DIFF=`diff a b`
		ko=0;
		if [[ "$DIFF" ]] ; then
			printf "${BRIGHT}${RED}%5s\n${NORMAL}" "KO"
			break
		else
			printf "${BRIGHT}${GREEN}%5s\n${NORMAL}" "OK"
		fi
	fi
