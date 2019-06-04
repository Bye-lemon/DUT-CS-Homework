from collections import OrderedDict


class Requirement(object):
    def __init__(self, req):
        super().__init__()
        self.data = list([])
        for item in req:
            self.data.append(item)

    def empty(self):
        return len(self.data) == 0

    def get(self):
        return self.data

    def drop(self, index):
        del self.data[index]

    def __repr__(self):
        return ' '.join(map(str, self.data))
