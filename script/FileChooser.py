from tkinter import Tk, filedialog
def fileChoose():
    root = Tk()
    root.withdraw()
    cur = filedialog.askopenfilenames()

    if cur:
        print(cur)
    else:
        print("没有选择文件夹")
    return cur


if __name__ == "__main__":
    fileChoose()