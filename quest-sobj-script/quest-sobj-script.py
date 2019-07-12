from tkinter import *
from tkinter.ttk import *
import struct
import tkinter.filedialog

from Crypto.Cipher import Blowfish

def endianness_reversal(data):
    return b''.join(map(lambda x: x[::-1],chunks(data, 4)))

def CapcomBlowfish(file):
    cipher = Blowfish.new("TZNgJfzyD2WKiuV4SglmI6oN5jP2hhRJcBwzUooyfIUTM4ptDYGjuRTP".encode("utf-8"), Blowfish.MODE_ECB)
    return endianness_reversal(cipher.decrypt(endianness_reversal(file)))

def CapcomBlowfishEncrypt(file):
    cipher = Blowfish.new("TZNgJfzyD2WKiuV4SglmI6oN5jP2hhRJcBwzUooyfIUTM4ptDYGjuRTP".encode("utf-8"), Blowfish.MODE_ECB)
    return endianness_reversal(cipher.encrypt(endianness_reversal(file)))

def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]

id_to_folder = {
    -1:"INVALID",
    0:"em100_00",
    1:"em002_00",
    4:"em106_00",
    7:"em101_00",
    9:"em001_00",
    10:"em001_01",
    11:"em002_01",
    12:"em007_00",
    13:"em007_01",
    14:"em011_00",
    15:"em121_00",
    16:"em024_00",
    17:"em026_00",
    18:"em027_00",
    19:"em036_00",
    20:"em043_00",
    21:"em044_00",
    22:"em045_00",
    23:"em127_00",
    24:"em102_00",
    25:"em103_00",
    26:"em105_00",
    27:"em107_00",
    28:"em120_00",
    29:"em108_00",
    30:"em109_00",
    31:"em110_00",
    32:"em111_00",
    33:"em112_00",
    34:"em113_00",
    35:"em114_00",
    36:"em115_00",
    37:"em116_00",
    38:"em117_00",
    39:"em118_00",
}


class SobjChanger(Frame):
    @staticmethod
    def validate(nval):
        return nval.isdigit() or nval == ""

    def update(self):
        if self.sobj_entry.get() == "":
            self.sobj_entry.insert(0, "0")
        if self.monster_id == -1:
            self.full_name['text'] = 'INVALID'
            return
        self.monster_id = [id for id in id_to_folder if self.monster_id_editor.get() == id_to_folder[id]][0]
        self.sobj_id = int(self.sobj_entry.get())
        
        self.full_name['text'] = f"{self.monster_id_editor.get()}_st{current_stage:03d}_{int(self.sobj_entry.get()):02d}.sobj"
    
    def setvals(self, monster_id=None, sobj_id=None):
        if monster_id is not None:
            self.monster_id = monster_id
        if sobj_id is not None:
            self.sobj_id = sobj_id

        for id,m_id in enumerate(id_to_folder.keys()):
            if m_id == monster_id:
                self.monster_id_editor.current(id)
                break
        
        self.sobj_entry.delete(0, END)
        self.sobj_entry.insert(0, str(sobj_id))
        self.update()
        

    def __init__(self, parent, **kwargs):
        super().__init__(parent, **kwargs)
        self.grid(sticky='NSEW', padx=2, pady=2)
        self.monster_id_label = Label(self, text="Monster ID:")
        self.monster_id_label.grid(padx=2, pady=2)
        self.monster_id_editor = Combobox(self, width=10, values=[i for i in id_to_folder.values()], state='readonly')
        self.monster_id_editor.grid(row=0,column=1)
        self.monster_id_editor.current(0)
        self.sobj_id = Label(self, text="Sobj ID:")
        self.sobj_id.grid(row=0, column=2)
        self.sobj_entry = Entry(self, validate='key', width=8, validatecommand=(self.register(SobjChanger.validate), '%P'))
        self.sobj_entry.grid(row=0, column=3)
        self.full_name = Label(self)
        self.full_name.grid(columnspan=5)
        self.sobj_entry.bind('<Return>', self.register(self.update))
        self.monster_id_editor.bind('<<ComboboxSelected>>', lambda _: self.update())
        self.setvals(-1, 0)
        
current_stage = 101
current_file_data = b''
current_file_path = ""

def open_file():
    global current_file_path, current_file_data, current_stage, sobjs
    current_file_path = tkinter.filedialog.askopenfilename(title="Select mib", filetypes = (("quest file", "*.mib"),))
    if current_file_path == "":
        return
    current_file_data = bytearray(CapcomBlowfish(open(current_file_path, 'rb').read()))
    current_stage = struct.unpack('H', current_file_data[0x17: 0x19])[0]
    for i, sobj in enumerate(sobjs):
        offset = 0xAC + 0x41 * i
        monster_id, sobj_id = struct.unpack('ii', current_file_data[offset:offset+8])
        sobj.setvals(monster_id, sobj_id)

def save(path=None):
    if path is None:
        path = current_file_path
    for i, sobj in enumerate(sobjs):
        offset = 0xAC + 0x41 * i
        current_file_data[offset:offset+8] = struct.pack('ii', sobj.monster_id, sobj.sobj_id)
    open(path, 'wb').write(CapcomBlowfishEncrypt(current_file_data))

win = Tk()
win.title("Quest sobj editor")
win.grid_rowconfigure(0, weight=1)
win.grid_columnconfigure(0, weight=1)

menubar = Menu(win)
menubar.add_command(label="Open", command=open_file)
menubar.add_command(label="Save", command=save)
win.config(menu=menubar)

root = Frame(win)
root.grid(padx=2, pady=2, sticky='NSEW')
sobjs = []
for i in range(7):
    s = SobjChanger(root)
    s.grid(row=i)
    sobjs.append(s)

win.mainloop()




