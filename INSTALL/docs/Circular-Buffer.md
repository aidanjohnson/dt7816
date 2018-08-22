### Diagram of Circular Buffer Operation

![Circular Buffer](https://github.com/aidanjohnson/dt7816/blob/master/misc/circular_buffer.png)

The circular ([ring](https://github.com/wizard97/ArduinoRingBuffer)) buffer (queue) implemented in `recorder` serves to decouple the analog input stream (reading) from the digital output file stream (writing). This design choice was inspired by [this](http://www.luaforlabview.com/datalog_manual.htm#Reading%20from%20tags) documentation.