.NOTPARALLEL: rebuild
.PHONY: build compile clean rebuild run buildRun cleanRun

ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
else
    DETECTED_OS := $(shell uname -s)
endif

ifeq ($(DETECTED_OS),Windows)
    EXE := Engine.exe
    RM := rmdir /s /q
    COPY := xcopy /E /I /Y
    PATH_SEP := \\
else
    EXE := Engine
    RM := rm -rf
    COPY := cp -r
    PATH_SEP := /
endif

run: compile
	@cd build/release && $(EXE)

buildRun: build
	@cd build/release && $(EXE)

cleanRun: rebuild run
	@echo Running

rebuild: clean build

build: 
	@echo Building
	@meson setup build --reconfigure
	@cd build && meson compile

compile: 
	@cd build && meson compile
	@$(COPY) src$(PATH_SEP)res build$(PATH_SEP)release
	
clean:
	@echo Cleaning
	@if exist build ${RM} build