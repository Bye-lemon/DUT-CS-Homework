from Config import *
from Scheduler import SSTFDiskScheduler, SCANDiskScheduler

if __name__ == "__main__":
    target = eval(input("Choose An Algorithm, '1' for SSTF '2' for SCAN:"))
    if target == 1:
        scheduler = SSTFDiskScheduler(REQ, POSITION, CAPACITY)
    elif target == 2:
        scheduler = SCANDiskScheduler(REQ, POSITION, CAPACITY)
    ret = True
    while ret:
        ret = scheduler.require()
    scheduler.report()
