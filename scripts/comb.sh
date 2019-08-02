POWDER_BLUE=$(tput setaf 153)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
NORMAL=$(tput sgr0)
GREEN=$(tput setaf 2)
UNDERLINE=$(tput smul)
RED=$(tput setaf 1)


validDirectory="../vm_champs/Valid_files"
invalidDirectory="../vm_champs/Invalid_files"

if [ ! -d "$validDirectory" ] || [ ! -d "$invalidDirectory" ] ; then
	./split_files.sh
fi

if [[ "$1" == "clean" ]] && [[ "$2" == "" ]] ; then
	rm a b verbosity *.txt
	exit 1
fi

if [ ! -f "corewar" ] ; then
	echo "You should compile first..."
	exit -1
fi

printf "${BRIGHT}${POWDER_BLUE}Looking for differences between Zaz's VM and ours....\n${NORMAL}"


if [[ "$1" != "" ]] && [[ -f $validDirectory/zaz_cor_files/$1 ]] ; then
	player1=$validDirectory/zaz_cor_files/$1
		for player2 in $(find $validDirectory/zaz_cor_files -type f -name "*.cor")
		do
			if [ -f "verbosity" ] ; then
				rm verbosity
			fi
			./vm_champs/corewar -v 2 $player1 $player2 > verbosity
			last_cycle=`tail -n 2 verbosity | head -n 1 | grep -Eo "\d+"`
			last_cycle=$((last_cycle-1))
			./corewar -d $last_cycle $player1 $player2 | grep -A300 0x0000 | sed 's/ $//g' > a
			./vm_champs/corewar -d $last_cycle $player1 $player2 | grep -A300 0x0000 | sed 's/ $//g' > b		
			DIFF=`diff a b`
			if [[ "$DIFF" ]] ; then
				printf "${BRIGHT}${WHITE}$(basename $player1 | rev | cut -c 5- | rev)   VS   %25s %5c ${RED}KO\n${NORMAL}" "$(basename $player2 | rev | cut -c 5- | rev)" ':'
			else
				printf "${BRIGHT}${WHITE}$(basename $player1 | rev | cut -c 5- | rev)   VS   %25s %5c ${GREEN}OK\n${NORMAL}" "$(basename $player2 | rev | cut -c 5- | rev)" ':'
			fi
	done
else
	for player1 in $(find $validDirectory/zaz_cor_files -type f -name "*.cor")
	do
		for player2 in $(find $validDirectory/zaz_cor_files -type f -name "*.cor")
		do
			if [ -f "verbosity" ] ; then
				rm verbosity
			fi
			./vm_champs/corewar -v 2 $player1 $player2 > verbosity
			last_cycle=`tail -n 2 verbosity | head -n 1 | grep -Eo "\d+"`
			last_cycle=$((last_cycle-1))
			./corewar -d $last_cycle $player1 $player2 | grep -A300 0x0000 | sed 's/ $//g' > a
			./vm_champs/corewar -d $last_cycle $player1 $player2 | grep -A300 0x0000 | sed 's/ $//g' > b		
			DIFF=`diff a b`
			if [[ "$DIFF" ]] ; then
				printf "${BRIGHT}${WHITE}$(basename $player1 | rev | cut -c 5- | rev)   VS   %25s %5c ${RED}KO\n${NORMAL}" "$(basename $player2 | rev | cut -c 5- | rev)" ':'
			else
				printf "${BRIGHT}${WHITE}$(basename $player1 | rev | cut -c 5- | rev)   VS   %25s %5c ${GREEN}OK\n${NORMAL}" "$(basename $player2 | rev | cut -c 5- | rev)" ':'
			fi
		done
	done
fi


