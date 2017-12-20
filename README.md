# Mandelbrot
### Struct
![](http://obip31jcs.bkt.clouddn.com/17-12-20/46633520.jpg)
### Roles
    MandelbrotWidget:This requests a picture to display.It handles the drawing and the user interaction. This object livesin the UI thread.
    
    MandelbrotCalculator:This handles the picture requests andaggregates the resulting JobResults before sending it back to MandelbrotWidget.This object lives in its own thread.
    
    Job:This calculates a part of the final picture before transmitting the result back to MandelbrotCalculator.Each job lives in its own thread.