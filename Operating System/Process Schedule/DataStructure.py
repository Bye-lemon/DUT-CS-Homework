from collections import OrderedDict


class TaskQueue(object):
    def __init__(self, task):
        super().__init__()
        self.data = OrderedDict(task)

    def terminate(self):
        return len(dict(filter(lambda x: x[1]['finish'] == -1, self.data.items()))) == 0

    def get(self):
        return list(filter(lambda x: x[1]['finish'] == -1, self.data.items()))

    def size(self):
        return len(self.data)

    def done(self, index, time):
        self.data[index]['finish'] = time
        self.data[index]['wait'] = time - self.data[index]['arrive']
        self.data[index]['wwait'] = self.data[index]['wait'] / \
            self.data[index]['require']

    def __repr__(self):
        ret = []
        for item in self.data.items():
            k, v = item[0], item[1]
            ret.append((7 * ' ').join([k, str(v['arrive']), str(v['require']),
                                       str(v['finish']), str(v['wait']), str(v['wwait'])[:4]]))
        return '\n'.join(ret)
