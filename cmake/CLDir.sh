#!/bin/bash

GIVEN_PATH="$1"
GIVEN_CL_PATH="$2"
GIVEN_COMPILER="$3"
HERE="$4"

PRM_INCLUDE="$HERE/clinclude/"

echo "Hello World! BmpCLConfig is running..."
echo "Current Position: $HERE"
echo "Given Path: $GIVEN_PATH"
echo "Given Compiler: $GIVEN_COMPILER"

rm ${GIVEN_PATH}/__PROCESSED.cl.c

# Preprocess 0: Get all source and throw it to ...cl
find "$GIVEN_PATH" -name '*.cl.c' | while read -r file; do
	if [[ $file != "__PROCESSED.cl.c" ]]; then
		cat $file >> ${GIVEN_PATH}/__PROCESSED.cl.c
	fi
done

sh CLFile.sh ${GIVEN_PATH}/__PROCESSED.cl.c $GIVEN_CL_PATH $GIVEN_COMPILER $HERE
rm ${GIVEN_PATH}/__PROCESSED.cl.c
