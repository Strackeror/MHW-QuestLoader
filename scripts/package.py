import os
from zipfile import ZipFile
import shutil

os.chdir(os.path.dirname(os.path.abspath(__file__)) + '/..')

with ZipFile('build/Loader-Release.zip', 'w') as zip:
    zip.write("build/Release/loader.dll", "loader.dll")
    zip.write("build/Release/dinput8.dll", "dinput8.dll")
    zip.write("MHWLoader/loader-config.json", "loader-config.json")
    zip.write("build/Release/QuestLoader.dll", "nativePC/plugins/QuestLoader.dll")
    zip.write("build/Release/MonsterLoader.dll", "nativePC/plugins/MonsterLoader.dll")

shutil.copyfile("build/Release/loader.lib", "Plugins/dependencies/loader.lib")
shutil.copyfile("MHWLoader/loader.h", "Plugins/dependencies/loader.h")





