from Config import *
from Scheduler import LRUMemoryScheduler, FIFOMemoryScheduler


def LRUDemo():
    lru = LRUMemoryScheduler(CAPACITY)
    for item in REQUIRES:
        lru.put(item)
    lru.report()


def FIFODemo():
    fifo = FIFOMemoryScheduler(CAPACITY)
    for item in REQUIRES:
        fifo.put(item)
    fifo.report()


if __name__ == "__main__":
    target = eval(input("Choose An Algorithm, '1' for LRU '2' for FIFO:"))
    if target == 1:
        LRUDemo()
    elif target == 2:
        FIFODemo()
