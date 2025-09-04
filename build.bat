@echo off

cd %~dp0

cmake --workflow configure-and-build
