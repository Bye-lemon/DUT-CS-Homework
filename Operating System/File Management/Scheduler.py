from collections import OrderedDict

class FreeTable(object):
    def __init__(self, disk):
        self.disk = disk
        self.data = OrderedDict()

    def update(self):
        self.data = OrderedDict()
        index, cnt = -1, -1
        for k, v in self.disk.get():
            if v == -1:
                if index == -1:
                    index, cnt = k, 1
                else:
                    cnt += 1
            elif v != -1 and index != -1:
                self.data.update({index: cnt})
                index, cnt = -1, -1
        if index != -1:
            self.data.update({index: cnt})
            index, cnt = -1, -1

    def get(self, size):
        for k, v in self.data.items():
            if v >= size:
                return k

    def __repr__(self):
        return self.data

