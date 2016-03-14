from StackInterface import StackInterface

#your code here
class ListStack(StackInterface):
    def __init__(self, l=[]):
        self.l = l
        
    def push(self, value):
        self.l.append(value)
        return None
    
    def pop(self):
        if len(self.l)==0:
            return None
        temp = self.l[-1]
        self.l = self.l[:-1]
        return temp
    
    def peek(self):
        if len(self.l)==0:
            return None
        return self.l[-1]