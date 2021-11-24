build:
	mkdir build
	cd build;cmake -DCMAKE_BUILD_TYPE=Debug ..;make -j8

openocd:
	openocd" "-f" "interface/picoprobe.cfg" "-f" "target/rp2040.cfg"

gdb:
	@echo"------------------------------------------------------------"
	@echo" Run the commands below to connect to openocd in gdb"
	@echo"target remote localhost:3333"
	@echo"load"
	@echo"monitor reset init"
	@echo"continue"
	@echo"------------------------------------------------------------"
	arm-none-eabi-gdb

clean:
	rm -rf ./build

help:
	@echo"build   = make folder build and build the project"
	@echo"clean   = remove build folder"
	@echo"gdb     = run arm gdb"
	@echo"openocd = run openocd for picoprobe debuging"