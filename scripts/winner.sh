POWDER_BLUE=$(tput setaf 153)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
NORMAL=$(tput sgr0)
GREEN=$(tput setaf 2)
UNDERLINE=$(tput smul)
RED=$(tput setaf 1)


validDirectory="Valid_files"
invalidDirectory="Invalid_files"

if [ ! -d "$validDirectory" ] || [ ! -d "$invalidDirectory" ] ; then
	./scripts/split_files.sh
fi

if [[ "$1" == "clean" ]] && [[ "$2" == "" ]] ; then
	rm w1 w2 verbosity *.txt
	exit 1
fi

if [ ! -f "corewar" ] ; then
	echo "You should compile first..."
	exit -1
fi




if [[ "$1" != "" ]] && [[ -f $validDirectory/zaz_cor_files/$1 ]] ; then
		player1=$validDirectory/zaz_cor_files/$1
		printf "${BRIGHT}${POWDER_BLUE}Looking for differences between Zaz's VM and ours....\n${NORMAL}"
		for player2 in $(find $validDirectory/zaz_cor_files -type f -name "*.cor")
		do
			if [ -f "verbosity" ] ; then
				rm verbosity
			fi
			if [ -f "w1" ] ; then
				rm w1
			fi
			if [ -f "w2" ] ; then
				rm w2
			fi
			printf "${BRIGHT}${WHITE}$(basename $player1 | rev | cut -c 5- | rev)   VS   %25s ...\n${NORMAL}" "$(basename $player2 | rev | cut -c 5- | rev)"
			./corewar $player1 $player2 | tail -n1 | cut -c 14- | rev | cut -c 12- > w1
			./vm_champs/corewar $player1 $player2 | tail -n1 | cut -c 15- | rev | cut -c 12- > w2
			DIFF=`diff w1 w2`
			if [[ "$DIFF" ]] ; then
				printf "${BRIGHT}${WHITE}$(basename $player1 | rev | cut -c 5- | rev)   VS   %25s %5c ${RED}KO\n${NORMAL}" "$(basename $player2 | rev | cut -c 5- | rev)" ':'
			else
				printf "${BRIGHT}${WHITE}$(basename $player1 | rev | cut -c 5- | rev)   VS   %25s %5c ${GREEN}OK\n${NORMAL}" "$(basename $player2 | rev | cut -c 5- | rev)" ':'
			fi
	done
else
	echo "Usage: ./scripts/winner.sh [champion.cor]"
fi
