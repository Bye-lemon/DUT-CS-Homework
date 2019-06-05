from DataStructure import TaskQueue


class AbstractProcessScheduler(object):
    def __init__(self, task):
        super().__init__()
        self.queue = TaskQueue(task)
        self.clk = 0
        self.flag = False

    def go(self):
        pass

    def report(self):
        print("任务 到达时间 服务时间 完成时间 周转时间 带权周转时间")
        print(self.queue)


class FCFSProcessScheduler(AbstractProcessScheduler):
    def __init__(self, task):
        super().__init__(task)

    def go(self):
        if self.queue.terminate():
            return False
        else:
            old = self.clk
            pool = self.queue.get()
            for item in pool:
                k, v = item[0], item[1]
                if v['arrive'] <= self.clk:
                    cnt = 0
                    while cnt < v['require']:
                        self.clk += 1
                        cnt += 1
                    self.queue.done(k, self.clk)
                print("Task " + k + " Done, Time " + str(self.clk))
                break
            if self.clk == old:
                self.clk += 1
            return True


class RRProcessScheduler(AbstractProcessScheduler):
    def __init__(self, task):
        super().__init__(task)
        keys = list(map(lambda x: x[0], self.queue.get()))
        values = list(map(lambda x: x[1]['require'], self.queue.get()))
        self.req = dict(zip(keys, values))

    def go(self):
        if self.queue.terminate():
            return False
        else:
            old = self.clk
            for k, v in self.queue.data.items():
                if v['arrive'] > self.clk or v['finish'] != -1:
                    continue
                else:
                    self.req[k] -= 1
                    self.clk += 1
                    if self.req[k] == 0:
                        self.queue.done(k, self.clk)
                        print("Task " + k + " Done, Time " + str(self.clk))
            if old == self.clk:
                self.clk += 1
            return True


class SJFProcessScheduler(AbstractProcessScheduler):
    def __init__(self, task):
        super().__init__(task)

    def go(self):
        if self.queue.terminate():
            return False
        else:
            pool = self.queue.get()
            arrive = list(filter(lambda x: x[1]['arrive'] <= self.clk, pool))
            if len(arrive) == 0:
                self.clk += 1
                return True
            cost = list(map(lambda x: x[1]['require'], arrive))
            for item in arrive:
                k, v = item[0], item[1]
                if v['require'] == min(cost):
                    cnt = 0
                    while cnt < v['require']:
                        self.clk += 1
                        cnt += 1
                    self.queue.done(k, self.clk)
                    print("Task " + k + " Done, Time " + str(self.clk))
                    break
            return True


class HRNProcessScheduler(AbstractProcessScheduler):
    def __init__(self, task):
        super().__init__(task)

    def go(self):
        if self.queue.terminate():
            return False
        else:
            pool = self.queue.get()
            arrive = list(filter(lambda x: x[1]['arrive'] <= self.clk, pool))
            if len(arrive) == 0:
                self.clk += 1
                return True
            cost = list(map(lambda x: (
                self.clk - x[1]['arrive'] + x[1]['require']) / x[1]['require'], arrive))
            for item in arrive:
                k, v = item[0], item[1]
                if (self.clk - v['arrive'] + v['require']) / v['require'] == min(cost):
                    cnt = 0
                    while cnt < v['require']:
                        self.clk += 1
                        cnt += 1
                    self.queue.done(k, self.clk)
                    print("Task " + k + " Done, Time " + str(self.clk))
                    break
            return True
