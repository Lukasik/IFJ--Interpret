#!/bin/bash
. ../common.sh
> tests.failed
binary_file=parser
make "test" > /dev/null
test_directory ./
