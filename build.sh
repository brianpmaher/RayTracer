#!/bin/bash

cd "$(dirname "$0")"

cmake --workflow configure-and-build
