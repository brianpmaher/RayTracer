#!/bin/bash

cd "$(dirname "$0")"

ctest --test-dir Build -C Debug
