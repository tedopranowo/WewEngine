@echo off

rem Create the files
cd ../Source/

set /p ClassName="What is the name of the class?"

copy NUL %ClassName%.h
copy NUL %ClassName%.cpp

rem Generate the header
echo #pragma once > %ClassName%.h
echo >> %ClassName%.h
echo class %ClassName% >> %ClassName%.h
echo { >> %ClassName%.h
echo public: >> %ClassName%.h
echo 	%ClassName%(); >> %ClassName%.h
echo 	~%ClassName%(); >> %ClassName%.h
echo } >> %ClassName%.h