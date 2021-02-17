from tkinter import Tk, filedialog

if __name__ == "__main__":
    root = Tk()
    root.withdraw()
    cur = filedialog.askopenfilenames()

    if cur:
        print(cur)
    else:
        print("没有选择文件夹")