@echo off

cd %~dp0

cmake -S . -B Build
cmake --build Build
