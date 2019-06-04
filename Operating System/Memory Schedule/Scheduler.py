from DataStructure import PageTable


class AbstractMemoryScheduler(object):
    def __init__(self, maxsize):
        super().__init__()
        self.pageTable = PageTable(maxsize)
        self.requestTimes = 0
        self.hitTimes = 0

    def hit(self):
        self.requestTimes += 1
        self.hitTimes += 1

    def notHit(self):
        self.requestTimes += 1

    def put(self):
        pass

    def report(self):
        print("完成调度，缺页次数" + str(self.requestTimes - self.hitTimes) + "，缺页率" +
              str((self.requestTimes - self.hitTimes) / self.requestTimes) + "。")


class LRUMemoryScheduler(AbstractMemoryScheduler):
    def __init__(self, maxsize):
        super().__init__(maxsize)

    def put(self, page):
        if self.pageTable.exist(page):
            self.hit()
            for k, v in self.pageTable.data.items():
                self.pageTable.data.update({k: 0} if k == page else {k: v + 1})
        elif not self.pageTable.full():
            self.notHit()
            for k, v in self.pageTable.data.items():
                self.pageTable.data.update({k: v + 1})
            self.pageTable.data.update({page: 0})
        else:
            self.notHit()
            lruPage, lruCost = None, -1
            for k, v in self.pageTable.data.items():
                if lruPage is None or v > lruCost:
                    lruPage, lruCost = k, v
            self.pageTable.data.pop(lruPage[0])
            print("Drop Page {}".format(lruPage[0]))
            for k, v in self.pageTable.data.items():
                self.pageTable.data.update({k: v + 1})
            self.pageTable.data.update({page: 0})
        print(self.pageTable)


class FIFOMemoryScheduler(AbstractMemoryScheduler):
    def __init__(self, maxsize):
        super().__init__(maxsize)

    def put(self, page):
        if self.pageTable.exist(page):
            self.hit()
        elif not self.pageTable.full():
            self.notHit()
            self.pageTable.data.update({page: 0})
        else:
            self.notHit()
            fifoPage = self.pageTable.data.popitem(last=False)
            print("Drop Page {}".format(fifoPage[0]))
            self.pageTable.data.update({page: 0})
        print(self.pageTable)


if __name__ == "__main__":
    #lru = LRUMemoryScheduler(3)
    lru = FIFOMemoryScheduler(3)
    lru.put('2')
    lru.put('3')
    lru.put('2')
    lru.put('1')
    lru.put('5')
    lru.put('2')
    lru.put('4')
    lru.put('5')
    lru.put('3')
    lru.put('2')
    lru.put('5')
    lru.put('2')
    lru.report()
