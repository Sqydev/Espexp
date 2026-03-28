{
  	description = "PlatformIO ESP32 Fix for NixOS";

  	inputs = {
    	nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
    	utils.url = "github:numtide/flake-utils";
  	};

  	outputs = { self, nixpkgs, utils }:
	utils.lib.eachDefaultSystem (system:
      	let
        	pkgs = import nixpkgs {
          		inherit system;
          		config.allowUnfree = true;
        	};

        	pythonWithDeps = pkgs.python3.withPackages (ps: with ps; [
          		pip
          		setuptools
          		wheel
          		pyserial
          		cryptography
          		bitstring
          		reedsolo
          		intelhex
          		ecdsa
        	]);
      	in
      	{
        	devShells.default = (pkgs.buildFHSEnv {
          		name = "platformio-fhs";
          		targetPkgs = pkgs: (with pkgs; [
            		platformio
            		pythonWithDeps
            		esptool
            
            		gcc
            		gnumake
            		pkgsi686Linux.glibc.dev
            		glibc.dev
            
            		libffi
            		openssl
            		libusb1
            		zlib
            		ncurses
            		expat
          		]);
          
			profile = ''
            	export NIX_CFLAGS_COMPILE=""
            	export NIX_LDFLAGS=""
            
            	unset CPATH
            	unset C_INCLUDE_PATH
            	unset CPLUS_INCLUDE_PATH

            	export PYTHONPATH="${pythonWithDeps}/${pkgs.python3.sitePackages}:''${PYTHONPATH:-}"
            	export PLATFORMIO_PYTHON_PATH="${pythonWithDeps}/bin/python3"
            
            	mkdir -p ~/.platformio/packages/tool-esptoolpy
            
            	cat << 'EOF' > ~/.platformio/packages/tool-esptoolpy/esptool.py
#!/usr/bin/env python3
import os
import sys
os.execv("${pkgs.esptool}/bin/esptool.py", ["esptool.py"] + sys.argv[1:])
EOF
            chmod +x ~/.platformio/packages/tool-esptoolpy/esptool.py
            
            if [ ! -f ~/.platformio/packages/tool-esptoolpy/package.json ]; then
              	echo '{"name": "tool-esptoolpy", "version": "4.6.2", "description": "esptool.py"}' > ~/.platformio/packages/tool-esptoolpy/package.json
            fi
        '';
          	runScript = "bash";
        	}).env;
    	}
	);
}
