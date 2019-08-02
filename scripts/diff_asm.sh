POWDER_BLUE=$(tput setaf 153)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
NORMAL=$(tput sgr0)
GREEN=$(tput setaf 2)
UNDERLINE=$(tput smul)
RED=$(tput setaf 1)

validDirectory="../vm_champs/Valid_files"
invalidDirectory="../vm_champs/Invalid_files"

if [ ! -f "../asm" ] ; then
	echo "You should compile first..."
	exit -1
fi

if [ ! -d "$validDirectory" ] || [ ! -d "$invalidDirectory" ] ; then
	./split_files.sh
fi

if [ -d "$validDirectory/our_cor_files" ] ; then
	rm -rf $validDirectory/our_cor_files
fi

mkdir $validDirectory/our_cor_files

printf "${BRIGHT}${POWDER_BLUE}Looking for differences between Zaz's ASM and ours....\n${NORMAL}"

for file in $(find $validDirectory/files -type f -name '*.s')
do
	if [ -f "compiling_msg" ] ; then
		rm compiling_msg
	fi
	../asm $file > compiling_msg
	if [ `head -n 1 compiling_msg | awk '{print $1}'` == 'Writing' ] ; then
		mv $(echo $file | rev | cut -c 3- | rev).cor $validDirectory/our_cor_files/
	else
		echo "$(basename $file) is valid but generated an error"
	fi
done

if [ -f "compiling_msg" ] ; then
	rm compiling_msg
fi

for file in $(find $validDirectory/zaz_cor_files -type f -name "*.cor")
do
	if [ -f expected ]; then rm output; fi
	if [ -f output ]; then rm output; fi
	basename=$(basename $file)
	xxd $file > expected
	if [ -f "$validDirectory/our_cor_files/$basename" ] ; then
		xxd $validDirectory/our_cor_files/$basename > output
	else
		touch output
	fi
	DIFF=$(diff expected output)
	if [ "$DIFF" ]; then
		printf "${BRIGHT}${WHITE}%-30s%-5c${RED}KO\n${NORMAL}" $basename ':'
	else
		printf "${BRIGHT}${WHITE}%-30s%-5c${BRIGHT}${GREEN}OK\n${NORMAL}" $basename ':'
	fi
done

if [ -f expected ]; then rm expected; fi
if [ -f output ]; then rm output; fi
