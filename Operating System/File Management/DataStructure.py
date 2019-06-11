import random
import math

class FileList(object):
    def __init__(self, maxNum):
        super().__init__()
        self.capacity = maxNum
        self.data = dict()

    def random(self):
        for i in range(self.capacity):
            fileSize = random.randint(20, 100) / 10
            self.data.update({i: fileSize})

    def get(self):
        return list(map(lambda x: math.ceil(x[1] / 2.0), self.data.items()))

class Disk(object):
    def __init__(self, capacity):
        super().__init__()
        self.capacity = capacity
        self.data = dict()
        for i in range(self.capacity):
            self.data.update({i: -1})

    def set(self, start, count, file):
        for i in range(count):
            self.data.update({start + i: file})

    def get(self):
        return self.data.items()

if __name__ == "__main__":
    foo = FileList(50)
    print(foo.get())