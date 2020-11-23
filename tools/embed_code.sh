#!/usr/bin/env bash

EXEC_PATH=$(pwd)

for i in $(ls ${EXEC_PATH}/resources/images/*.png)
do
  FILENAME=$(basename $i)
  ./bin/hexembed $i ${FILENAME%%.*} > ${EXEC_PATH}/src/assets/images/${FILENAME%%.*}.h
done

for i in $(ls ${EXEC_PATH}/resources/fonts/*.ttf)
do
  FILENAME=$(basename $i)
  ./bin/hexembed $i ${FILENAME%%.*} > ${EXEC_PATH}/src/assets/images/${FILENAME%%.*}.h
done
