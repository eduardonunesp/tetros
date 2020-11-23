#!/usr/bin/env bash

set -e

if [ ! -d "bin" ]
then
scons wasm=1 -j 12 
fi

zip -r game.zip bin/{index.data,index.html,index.js,index.wasm} 
mv game.zip /tmp
