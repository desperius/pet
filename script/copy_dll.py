import sys
import os
import re

def copy_dll():
    with open('pet.mk') as mk_file:
        lines = mk_file.readlines()

    for line in lines:
        # Tries to get a string with path to libraries from project mk file
        lib = re.match(r'(LIBS+.*)', line, flags=0)

        if lib != None:
            lib = lib.group()
            
            # Gets only a path to libraries
            path = re.search(r'-L[\w\:\\\.\-]+\s', lib, flags=0)
			
            if path != None:
                # Creates path to platform plugin library which will be needed to run an .exe file in future
                plugins = path.group().strip()[2:-3] + 'plugins\\platforms\\qwindows.dll'
                # Creates path to Qt libraries which will be needed to run .exe file
                path = path.group().strip()[2:-3] + 'bin\\'

            pattern = re.compile(r'-l[\w\d]+\s')
            libs = list()

            for l in re.finditer(pattern, lib):
                libs.append(l.group()[2:].strip() + ".dll")

            for lib in libs:
                copy_lib_str = 'xcopy ' + path + lib + ' .\\bin\\ /d /y'
                os.system(copy_lib_str)
                
            if plugins != None:
                copy_plg_str = 'xcopy ' + plugins + ' .\\bin\\platforms\\ /d /y'
                os.system(copy_plg_str)

            break 

copy_dll()
print('Copying finished')