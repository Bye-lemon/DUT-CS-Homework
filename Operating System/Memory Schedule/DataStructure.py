from collections import OrderedDict


class PageTable(object):
    def __init__(self, size):
        super().__init__()
        self.data = OrderedDict({})
        self.size = size

    def empty(self):
        return len(self.data) == 0

    def full(self):
        return len(self.data) == self.size

    def exist(self, page):
        return page in self.data.keys()

    def __repr__(self):
        return 'Page Table: ' + ' '.join(self.data.keys())
