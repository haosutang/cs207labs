
import abc
class StackInterface(abc.ABC):
    """
    >>> a = Stack()
    >>> a.push(1)
    >>> a.push(2)
    >>> a.peek()
    2
    >>> a.pop()
    2
    >>> a.pop()
    1
    >>> a.peek()
    >>> a.pop()
    
    """
    
    @abc.abstractmethod
    def push(self, value):
        "Push value onto the stack. Return None"
        
    @abc.abstractmethod
    def pop(self):
        "Pop value from Stack. Return None if nothingon stack"
        
    @abc.abstractmethod
    def peek(self):
        "Peeak at top of stack. Return None if empty"