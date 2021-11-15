# create the packages folder and apply the patch
package:
	mkdir -p packages
	cd packages;git clone https://gitlab.com/susurrus/serialport-rs.git --depth=1
	cd packages;git clone https://github.com/gregkh/usbutils.git --depth=1
	cd packages/serialport-rs;git apply ../../bugfix.patch

# remove the packages folder
clean:
	rm ./packages -rf
	rm ./target -rf
# display the commands in this file
help:
	@echo'Commands which can be used'
	@echo'package - create the packages folder and apply the patch'
	@echo'clean   - remove the packages folder'
