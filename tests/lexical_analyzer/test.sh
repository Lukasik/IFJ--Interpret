#!/bin/bash
. ../common.sh
> tests.failed
binary_file=lexical_analyzer
make "test" > /dev/null
test_directory ./
