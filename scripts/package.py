import os
from zipfile import ZipFile
import shutil

os.chdir(os.path.dirname(os.path.abspath(__file__)) + '/..')

with ZipFile('x64/Loader-Release.zip', 'w') as zip:
    zip.write("x64/Release/loader.dll", "loader.dll")
    zip.write("x64/Release/dinput8.dll", "dinput8.dll")
    zip.write("x64/Release/loader-config.json", "loader-config.json")
    zip.write("x64/Release/QuestLoader.dll", "nativePC/plugins/QuestLoader.dll")
    zip.write("x64/Release/MonsterLoader.dll", "nativePC/plugins/MonsterLoader.dll")

shutil.copyfile("x64/Release/loader.lib", "Plugins/dependencies/loader.lib")
shutil.copyfile("MHWLoader/loader.h", "Plugins/dependencies/loader.h")





