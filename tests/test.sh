green="\033[32m"
red="\033[31m"
color_end="\033[0m"
binary="ifj13"
success=0
fail=0

rm -f files/*.out.tmp 2> /dev/null >&2

ls files/*.php | while read testfile
do
	codeShould=`./getCode $testfile`
	./${binary} $testfile > ${testfile%.php}.out.tmp 2>/dev/null
	codeReal=$?
	printf "%11s: %d (%d) " ${testfile:6} ${codeReal} ${codeShould}

	if [ $codeReal -eq $codeShould ];
	then
		printf "${green}OK${color_end}"

		if [ -f ${testfile%.php}.out ];
		then
			diff ${testfile%.php}.out ${testfile%.php}.out.tmp > /dev/null
			if [ $? -eq 0 ];
			then
				printf " output: ${green}OK${color_end}"
				success=`expr ${success} + 1`

			else
				printf " output: ${red}KO${color_end}"
				fail=`expr ${success} + 1`
			fi
		else
			success=`expr ${success} + 1`
		fi

	else
		printf "${red}KO${color_end}"
		fail=`expr ${fail} + 1`
	fi

	printf "\n"
done

# printf "${green}${success}${color_end}/${red}${fail}${color_end}\n"
