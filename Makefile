.NOTPARALLEL: rebuild

run: build
	cd build/release && Engine.exe

cleanRun: rebuild
	@echo "Running"
	cd build/release && Engine.exe

rebuild: clean build

build: 
	@echo "Building"
	@meson setup build --reconfigure
	@cd build && meson compile
	
clean:
	@echo "Cleaning"
	@if exist build rmdir /s /q build