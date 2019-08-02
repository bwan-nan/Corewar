POWDER_BLUE=$(tput setaf 153)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
NORMAL=$(tput sgr0)
UNDERLINE=$(tput smul)
RED=$(tput setaf 1)

validDirectory='../vm_champs/Valid_files'
invalidDirectory='../vm_champs/Invalid_files'

if [ -d $validDirectory ] ; then
	rm -rf $validDirectory
fi

if [ -d $invalidDirectory ] ; then
	rm -rf $invalidDirectory
fi

mkdir $validDirectory
mkdir $validDirectory/zaz_cor_files
mkdir $validDirectory/files
mkdir $invalidDirectory

for file in $(find .. -type f -name "*.s")
do
#	sleep 0.5
	if [ -f "compiling_msg" ] ; then
		rm compiling_msg
	fi
	../vm_champs/asm $file > compiling_msg
	if [ `head -n 1 compiling_msg | awk '{print $1}'` == 'Writing' ] ; then
		cp $(echo $file) $validDirectory/files
		mv $(echo $file | rev | cut -c 3- | rev).cor $validDirectory/zaz_cor_files
	else
		cp $(echo $file) $invalidDirectory
	fi
done

if [ -f "compiling_msg" ] ; then
	rm compiling_msg
fi

printf "${BRIGHT}${POWDER_BLUE}Separated valid and invalid files from vm_champs successfully.\n${NORMAL}"
