import os
from zipfile import ZipFile
import shutil
import glob

os.chdir(os.path.dirname(os.path.abspath(__file__)) + '/..')

with ZipFile('build/Loader-Release.zip', 'w') as zip:
    zip.write("build/MHWLoader/Release/loader.dll", "loader.dll")
    zip.write("build/DllLoader/Release/injector.dll", "dtdata.dll")
    zip.write("MHWLoader/loader-config.json", "loader-config.json")
    zip.write("build/Plugins/QuestLoader/Release/QuestLoader.dll", "nativePC/plugins/QuestLoader.dll")
    zip.write("build/Plugins/MonsterLoader/Release/MonsterLoader.dll", "nativePC/plugins/MonsterLoader.dll")

try:
    with ZipFile('build/Clutch-Release.zip', 'w') as zip:
        zip.write('build/Plugins/ClutchRework/Release/ClutchRework.dll', 'nativePC/plugins/ClutchRework.dll')
        for path in glob.iglob(r'Plugins/ClutchRework/nativePC/**/*.col', recursive=True):
            zip.write(path, os.path.relpath(path, r'Plugins/ClutchRework/'))
except FileNotFoundError as e:
    print("ClutchRework was not built")
    print(e)
    os.remove("build/Clutch-Release.zip")

with ZipFile('build/StrackerLibs.zip', 'w') as zip:
    zip.write("build/MHWLoader/Release/loader.lib", "loader.lib")
    zip.write("MHWLoader/ghidra_export.h", "ghidra_export.h")
    zip.write("MHWLoader/loader.h", "loader.h")
    zip.write("MHWLoader/util.h", "util.h")
