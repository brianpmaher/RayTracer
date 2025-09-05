#!/bin/bash

cd "$(dirname "$0")"

cmake -S . -B Build
cmake --build Build
