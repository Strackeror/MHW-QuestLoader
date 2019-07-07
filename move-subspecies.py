import glob
import os

for filename in glob.iglob("01/**", recursive=True):
    if not os.path.isfile(filename): continue
    aob = open(filename, 'rb').read()
    aob = aob.replace(b'em\\em103\\00', b'em\\em103\\01')
    aob = aob.replace(b'em\\em103\\01\\mod\\em103_00', b'em\\em103\\01\\mod\\em103_01')
    nfilename = filename[:]
    nfilename = nfilename.replace("01\\mod\\em103_00",  "01\\mod\\em103_01")
    if nfilename != filename:
        os.remove(filename)
    open(nfilename, 'wb').write(aob)


