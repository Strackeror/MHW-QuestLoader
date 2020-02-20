from zipfile import ZipFile
import os
import sys


if len(sys.argv) > 1:
    pname = sys.argv[1]
else:
    pname = os.path.basename(os.path.dirname(os.path.abspath(__file__)))

with ZipFile(f"x64/{pname}.zip", 'w') as zip:
    zip.write(f"x64/Release/{pname}.dll", f"nativePC/plugins/{pname}.dll")