import glob
import os
from tkinter import *
from tkinter.ttk import *
import sys

fileadj_pref = {
    'suppress-noprocessed': False,
    'suppress-excluded': False,
    'suppress-ncm': False
}

def adjust(inp):
    if 'namespace kat' not in inp:
        lines = inp.split('\n')
        cline = None
        i = 0
        for l in lines:
            if l.startswith("class"):
                cline = i
                break
            i += 1
        lines.insert(cline, 'namespace kat {\n')
        for i in range(cline + 1, len(lines)):
            lines[i] = "    " + lines[i]
        lines.append('}')
        inp = '\n'.join(lines)

    if '#include "kat/core.h"' not in inp:
        lines = inp.split('\n')
        cline = None
        i = 0
        nol = False
        for l in lines:
            if l.strip() == '#pragma once':
                cline = i + 1
                if lines[cline + 1] == '' and lines[cline] == '':
                    nol = True
                    cline = i + 2
                break
            i += 1
        if nol:
            lines.insert(cline, '#include "kat/core.h"')
        else:
            lines.insert(cline, '\n#include "kat/core.h"')
        inp = '\n'.join(lines)
    return inp

headers_done = []
headers_exc = []

headers_ = glob.glob("**/*.h", recursive = True)
print(len(headers_))

def do_process(interactive = True):
    headers = glob.glob("**/*.h", recursive = True)
    if all(h in headers_done or h in headers_exc for h in headers):
        print("No work to do")
        return
    for h in headers:
        if h in headers_done:
            if not fileadj_pref['suppress-noprocessed']:
                print(f"Header {h} has already been processed")
            continue

        with open(h, 'r') as f:
            inp = f.read()
            if '// hfixer excludefile' in inp:
                if not fileadj_pref['suppress-excluded']:
                    print(f"Header {h} is excluded")
                headers_exc.append(h)
                continue
            adjs = adjust(inp)
            if adjs == inp:
                if not fileadj_pref['suppress-ncm']:
                    print(f"No changes made to {h}")
                headers_done.append(h)
                continue
        print(f"Processed: {h}")
        if interactive:
            print(adjs)
            if input("Continue? ") != 'y':
                break
        with open(h, 'w+') as f:
            f.write(adjs)
        headers_done.append(h)

def reset(*args):
    del headers_done[:]
    del headers_exc[:]
    print("Reset Progress")


class RedirectText(object):
    def __init__(self, text_widget, out):
        """Constructor"""
        self.output = text_widget
        self.stdout = out

    def write(self, string):
        """Add text to the end and scroll to the end"""
        self.output.insert('end', string)
        self.output.see('end')
        self.stdout.write(string)

    def flush(self, *args, **kwargs):
        self.stdout.flush(*args, **kwargs)




def win():
    import tkinter.filedialog as fd

    old_stdout = sys.stdout
    def setdir(*args):
        p = fd.askdirectory()
        if p == '': return
        os.chdir(p)
        l.config(text=p)

        if os.path.exists("katengine_header_fixer.state.json"):
            import json
            with open("katengine_header_fixer.state.json", 'r') as state:
                pstate = json.load(state)
                fileadj_pref = pstate['prefs']
                headers_done = pstate['headers_done']
                headers_exc = pstate['headers_done']
        else:
            headers_done = []
            headers_exc = []


    tk = Tk()
    tl = Toplevel()
    label = Label(tl, text="Preferences", font=("Helvetica", "18"))
    f_ = Frame(tl)
    suppress_already_proc_label = Label(f_, text="Suppress 'Already Processed' Messages")
    suppress_excluded_label = Label(f_, text="Suppress 'Excluded' Messages")
    suppress_ncm_label = Label(f_, text="Suppress 'No Changes Made' Messages")
    sapvr = IntVar()
    sevr = IntVar()
    sncmvr = IntVar()
    suppress_already_proc_cbox = Checkbutton(f_, offvalue = 0, onvalue = 1, variable = sapvr)
    suppress_excluded_cbox = Checkbutton(f_, offvalue = 0, onvalue = 1, variable = sevr)
    suppress_ncm_cbox = Checkbutton(f_, offvalue = 0, onvalue = 1, variable = sncmvr)

    if fileadj_pref['suppress-noprocessed']:
        sapvr.set(1)
    if fileadj_pref['suppress-excluded']:
        sevr.set(1)
    if fileadj_pref['suppress-ncm']:
        sncmvr.set(1)

    def close_pref(*args):
        fileadj_pref['suppress-noprocessed'] = sapvr.get() == 1
        fileadj_pref['suppress-excluded'] = sevr.get() == 1
        fileadj_pref['suppress-ncm'] = sncmvr.get() == 1
        tl.withdraw()
        tl.grab_release()

    closebtn = Button(tl, text="Close", command=close_pref)

    suppress_already_proc_label.grid(row=0,column=0)
    suppress_already_proc_cbox.grid(row=0,column=1)
    suppress_excluded_label.grid(row=1,column=0)
    suppress_excluded_cbox.grid(row=1,column=1)
    suppress_ncm_label.grid(row=2,column=0)
    suppress_ncm_cbox.grid(row=2,column=1)

    label.pack()
    f_.pack()
    closebtn.pack(expand=True,fill=BOTH)
    tl.title("Preferences")
    tl.resizable(False, False)
    tl.protocol("WM_DELETE_WINDOW", close_pref)
    tl.withdraw()

    ff = Frame(tk)

    def open_pref(*args):
        tl.deiconify()
        tl.grab_set()

        x = tk.winfo_x()
        y = tk.winfo_y()
        tl.geometry("+%d+%d" %(x+400,y+40))

        tl.focus()
        tl.mainloop()



    f = Frame(ff)
    rbtn = Button(f, text="Set Directory", command=setdir)
    rsbtn = Button(f, text="Reset Progress", command=reset)
    btn = Button(ff, text="Process", command=lambda *args: do_process(False))
    pref_btn = Button(f, text="Preferences", command=open_pref)
    btn.pack(expand=True,fill=BOTH)
    rbtn.grid(row=0,column=0,sticky='nsew')
    rsbtn.grid(row=0,column=1,sticky='nsew')
    pref_btn.grid(row=0,column=2,sticky='nsew')
    f.grid_columnconfigure(0, minsize=217, weight=1)
    f.grid_columnconfigure(1, minsize=216, weight=1)
    f.grid_columnconfigure(2, minsize=217, weight=1)
    f.grid_rowconfigure(0, minsize=24, weight=1)


    f.pack(fill=BOTH,expand=True)
    l = Label(ff, text=os.path.abspath(os.curdir))
    l.pack()
    text = Text(tk,state=DISABLED)

    global print
    oldprint = print
    def newprint(*args, **kwargs):
        text.configure(state=NORMAL)
        oldprint(*args, **kwargs)
        text.configure(state=DISABLED)
        text.see(END)
    print = newprint

    sys.stdout = RedirectText(text, old_stdout)
    ff.grid(row=0,column=0,sticky='nsew')
    text.grid(row=1,column=0,sticky='nsew')
    tk.grid_rowconfigure(0, minsize=100, weight=1)
    tk.grid_rowconfigure(1, minsize=400, weight=1)
    tk.wm_geometry("650x500")
    tk.resizable(False, False)
    try:
        tk.mainloop()
    except KeyboardInterrupt:
        tk.destroy()
        sys.stdout = old_stdout
        print = oldprint

    persist_state = {
        "prefs": fileadj_pref,
        "headers_done": headers_done,
        "headers_exc": headers_exc
    }

    import json
    with open("katengine_header_fixer.state.json", 'w+') as state:
        json.dump(persist_state, state)

if __name__ == '__main__':

    os.chdir(r"C:\Users\andy\source\repos\katenginisms\katengine\kat")

    if os.path.exists("katengine_header_fixer.state.json"):
        import json
        with open("katengine_header_fixer.state.json", 'r') as state:
            pstate = json.load(state)
            fileadj_pref = pstate['prefs']
            headers_done = pstate['headers_done']
            headers_exc = pstate['headers_done']
    else:
        fileadj_pref = {
            'suppress-noprocessed': False,
            'suppress-excluded': False,
            'suppress-ncm': False
        }
        headers_done = []
        headers_exc = []

win()
