green="\033[32m"
red="\033[31m"
color_end="\033[0m"
tmp_file=`mktemp`
folder=${PWD##*/}
binary_file=""


print_result()
{
	if [ $2 -eq 0 ];
	then
		color_start=$green
	else
		color_start=$red
		echo ${folder}${1:1} >> tests.failed
	fi

	printf "${color_start}%s%s${color_end}\n" ${folder}${1:1}
}

test_directory()
{
	ls ${1}*.tst 2> /dev/null | while read file;
	do
		# echo $file;
		./${binary_file} ${file} > ${tmp_file}
		diff ${file%tst}should ${tmp_file} > ${file%tst}diff
		print_result ${file} $?
	done

	ls $1 -1p | grep -E '/$' | while read directory;
	do
		test_directory ${1}${directory}
	done
}

