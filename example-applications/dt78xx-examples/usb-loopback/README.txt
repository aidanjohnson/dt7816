This example has two applications; an application that runs in the host PC and
communicates over USB with a corresponding application executing in the DT78xx
board. The two applications communicate over USB pipes sending and receiving data.

The host application sends a block of data through an OUT USB pipe which the 
board application loops back through an IN USB pipe.
