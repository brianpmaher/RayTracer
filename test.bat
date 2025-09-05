@echo off

cd %~dp0

ctest --test-dir Build -C Debug
