#!/bin/bash
. ../common.sh
> tests.failed
binary_file=scanner
make "test" > /dev/null
test_directory ./
