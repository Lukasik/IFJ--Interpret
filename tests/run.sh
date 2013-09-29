#!/bin/bash

>tests.failed

ls -1p | grep -E '/$' | while read folder;
do
	cd $folder
	./test.sh
	cat tests.failed >> ../tests.failed
	cd ../
done
