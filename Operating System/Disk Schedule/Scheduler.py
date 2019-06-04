from DataStructure import Requirement


class AbstractDiskScheduler(object):
    def __init__(self, req, pos, capacity):
        super().__init__()
        self.queue = Requirement(req)
        self.cost = 0
        self.position = pos
        self.capacity = capacity

    def require(self):
        pass

    def report(self):
        print("移臂总量：" + str(self.cost))


class SSTFDiskScheduler(AbstractDiskScheduler):
    def __init__(self, req, pos, capacity):
        super().__init__(req, pos, capacity)

    def require(self):
        if self.queue.empty():
            return False
        else:
            pool = self.queue.get()
            cost = list(map(lambda x: abs(self.position - x), pool))
            zipped = dict(zip(cost, pool))
            next = zipped.get(min(cost))
            for index, item in enumerate(pool):
                if item == next:
                    self.position = item
                    self.queue.drop(index)
                    self.cost += min(cost)
                    break
            print("Next Position: " + str(next))
            return True


class SCANDiskScheduler(AbstractDiskScheduler):
    def __init__(self, req, pos, capacity):
        super().__init__(req, pos, capacity)
        self.direction = 1  # 1: ASC 0: DESC

    def require(self):
        if self.queue.empty():
            return False
        else:
            pool = self.queue.get()
            delta = list(map(lambda x: x - self.position, pool))
            if self.direction and all(map(lambda x: x < 0, delta)):
                self.direction = 0
            elif self.direction == 0 and all(map(lambda x: x > 0, delta)):
                self.direction = 1
            cost = filter(lambda x: x >= 0, delta) if self.direction else filter(
                lambda x: x <= 0, delta)
            target = min(cost) if self.direction else max(cost)
            for index, item in enumerate(pool):
                if item - self.position == target:
                    self.position = item
                    self.queue.drop(index)
                    self.cost += abs(target)
                    print("Next Position: " + str(item))
                    break
            return True
