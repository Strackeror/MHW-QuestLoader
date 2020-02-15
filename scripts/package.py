import os
from zipfile import ZipFile
import shutil

os.chdir(os.path.dirname(os.path.abspath(__file__)))

with ZipFile('../x64/Loader-Release.zip', 'w') as zip:
    zip.write("../x64/Release/dinput8.dll", "dinput8.dll")
    zip.write("../x64/Release/dinput-config.json", "dinput-config.json")

shutil.copyfile("../x64/Release/dinput8.lib", "../Plugins/ExamplePlugin/dependencies/dinput8.lib")
shutil.copyfile("../dinput8-mhw/log.h", "../Plugins/ExamplePlugin/dependencies/log.h")





