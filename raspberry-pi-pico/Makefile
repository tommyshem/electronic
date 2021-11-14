install:
	git clone https://github.com/raspberrypi/openocd.git --branch rp2040 --depth=1 --no-single
	git clone https://github.com/raspberrypi/pico-examples.git --depth=1
	git clone https://github.com/raspberrypi/pico-sdk.git --depth=1;cd pico-sdk;git submodule update --init
	git clone https://github.com/raspberrypi/pico-project-generator.git --depth=1
	git clone https://github.com/raspberrypi/picotool.git --depth=1
	git clone https://github.com/raspberrypi/picoprobe.git --depth=1

update:
	cd pico-sdk;git pull;git submodule update
