import pprint

from DataStructure import FileList, Disk
from Scheduler import FreeTable
from Config import *

if __name__ == "__main__":
    filelist = FileList(NUM)
    filelist.random()
    file = filelist.get()
    disk = Disk(CAPACITY)
    scheduler = FreeTable(disk)
    scheduler.update()
    for index, size in enumerate(file):
        block = scheduler.get(size)
        disk.set(block, size, index + 1)
        scheduler.update()
    print("Finish Initial...\n")
    pprint.pprint(scheduler.data)
    for k, v in disk.get():
        if (v > -1) and (v % 2 != 0):
            disk.set(k, 1, -1)
    scheduler.update()
    print("\nDelete Initial...\n")
    pprint.pprint(scheduler.data)
    filelist = FileList(len(ADDITION))
    for index, item in enumerate(ADDITION):
        filelist.data.update({NUM + index: item})
    file = filelist.get()
    filename = ["A.txt", "B.txt", "C.txt", "D.txt", "E.txt"]
    print("\n")
    for index, size in enumerate(file):
        block = scheduler.get(size)
        disk.set(block, size, index)
        scheduler.update()
        print(filename[index - 1] + ": " + str(block))
    print("\nCreate Initial...\n")
    pprint.pprint(scheduler.data)