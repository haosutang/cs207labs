
import doctest
from StackInterface import StackInterface 
from ListStack import ListStack
def test(cls, verbose=False):
    res=doctest.testfile('StackInterface.py', 
                         globs={'Stack':cls},
                        verbose = verbose,
                        optionflags = doctest.REPORT_ONLY_FIRST_FAILURE)
real_subclasses = StackInterface.__subclasses__()

for cls in real_subclasses:
    test(cls, True)