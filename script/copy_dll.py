import sys
import os
import re

def copy_dll():
    with open('pet.mk') as mk_file:
        lines = mk_file.readlines()

    for line in lines:
        lib = re.match(r'(LIBS+.*)', line, flags=0)

        if lib != None:
            lib = lib.group()
            print(lib)
            path = re.search(r'-L[\w\:\\\.\-]+\s', lib, flags=0)
            
            if path != None:
                path = path.group().strip()[2:-3] + 'bin\\'
                print(path)

            pattern = re.compile(r'-l[\w\d]+\s')
            libs = list()

            for l in re.finditer(pattern, lib):
                libs.append(l.group()[2:].strip() + ".dll")
                print(libs[-1])

            for lib in libs:
                copy_str = 'xcopy ' + path + lib + ' .\\bin\\ /d /y'
                os.system(copy_str)

            break 

copy_dll()
print('Copying finished')