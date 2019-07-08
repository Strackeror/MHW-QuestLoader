import glob
import os

from tkinter import *
from tkinter import filedialog
from tkinter.ttk import *

def move_subspecies(monster_path : str, old_variant_id : int, new_variant_id : int):
    monster_path_name = os.path.basename(monster_path)
    lst = glob.glob(os.path.join(monster_path, "{0:02d}\\**".format(old_variant_id)), recursive=True)
    progress['maximum'] = len(lst)
    progress.start()
    progress['value'] = 0
    for filename in lst:
        progress['value'] += 1
        win.update_idletasks()
        if not os.path.isfile(filename): 
            continue
        aob = open(filename, 'rb').read()
        replacements = [
            (
                "em\\{0}\\{1:02d}".format(monster_path_name, old_variant_id),
                "em\\{0}\\{1:02d}".format(monster_path_name, new_variant_id),
            ),
            (
                "em\\{0}\\{1:02d}\\mod\\{0}_{2:02d}".format(monster_path_name, new_variant_id, old_variant_id),
                "em\\{0}\\{1:02d}\\mod\\{0}_{2:02d}".format(monster_path_name, new_variant_id, new_variant_id),
            )
        ]
        for (r, w) in replacements:
            aob = aob.replace(r.encode('ascii'), w.encode('ascii'))
        local_filename = os.path.relpath(filename, start=monster_path)
        local_filename = local_filename.replace(
            f"{old_variant_id:02d}\\mod\\{monster_path_name}_{old_variant_id:02d}",
            f"{new_variant_id:02d}\\mod\\{monster_path_name}_{new_variant_id:02d}"
                )
        local_filename = f"{new_variant_id:02d}" + local_filename[2:]
        final_filename = os.path.join(monster_path, local_filename)
        os.makedirs(os.path.dirname(final_filename), exist_ok=True)
        open(final_filename, 'wb').write(aob)
    progress.stop()
    repopulate_comboboxes()

targets = [f"{i:02d}" for i in range(100)]

def repopulate_comboboxes():
    if not os.path.isdir(entry.get()):
        return False
    lst = []
    for i in os.listdir(entry.get()):
        if os.path.isdir(os.path.join(entry.get(), i)) and i.isdigit() and len(i) == 2:
            lst += [i]
    monster_label['text'] = 'Monster ID:'
    if not lst:
        source_variant['values'] = []
        target_variant['values'] = []
        return False
    
    monster_label['text'] += f"{os.path.basename(entry.get())}"

    source_variant['values'] = lst
    source_variant.current(0)

    target_lst = [i for i in targets if i not in lst]
    target_variant['values'] = target_lst
    target_variant.current(0)
    return True

def browse():
    entry.delete(0, END)
    entry.insert(0, filedialog.askdirectory(title="Select Monster Folder"))
    repopulate_comboboxes()

def launch():
    move_subspecies(entry.get(), int(source_variant.get()), int(target_variant.get()))

win = Tk()
win.title("Subspecies resource changer")
win.grid_columnconfigure(0, weight=1)
window = Frame(win)
window.grid(column = 0, row= 0, padx=2, pady=2, sticky='NSEW')
window.grid_columnconfigure(4, weight=1)
window.grid_rowconfigure(3, weight=1)

entry = Entry(window, width=50, validate="focusout", validatecommand=repopulate_comboboxes)
entry.grid(column=0, row=0, columnspan=5, sticky='EW')
browse_button = Button(window, text="Browse Monster Folder", command=browse)
browse_button.grid(column=5, row=0)
variants_grid = Grid()
source_label = Label(window, text="Source")
source_label.grid(column = 0, row = 1, sticky = W)
source_variant = Combobox(window, values = {}, width=5)
source_variant.grid(column = 1, row = 1, sticky = W)
target_label = Label(window, text="Target")
target_label.grid(column = 2, row = 1, sticky = W, padx=(20, 0))
target_variant = Combobox(window, values = {}, width=5)
target_variant.grid(column = 3, row = 1, sticky = W)
monster_label = Label(window, text="Monster ID:")
monster_label.grid(column = 5, row=1, sticky="W")

progress = Progressbar(window, mode="determinate")
progress.grid(column = 0, columnspan=6, row=2, pady=2, sticky='EW')

launch_button = Button(window, text="Copy Subspecies", command=launch)
launch_button.grid(column = 0, columnspan=2, row=4, pady=2)



window.mainloop()


