from Config import *
from Scheduler import FCFSProcessScheduler, RRProcessScheduler, SJFProcessScheduler, HRNProcessScheduler

if __name__ == "__main__":
    target = eval(
        input("Choose An Algorithm, 1 For FCFS, 2 For RR, 3 For SJF, 4 For HRN:"))
    if target == 1:
        scheduler = FCFSProcessScheduler(TASK)
    elif target == 2:
        scheduler = RRProcessScheduler(TASK)
    elif target == 3:
        scheduler = SJFProcessScheduler(TASK)
    elif target == 4:
        scheduler = HRNProcessScheduler(TASK)
    ret = True
    while ret:
        ret = scheduler.go()
    scheduler.report()
