 /*
 * DT78XX Javascript graph functions
 *
 * Copyright (C) 2014 Data Translation Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * You are free to use this source code under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 */ 
function Point(x,y)
{
    this.x=x;
    this.y=y;
}
function Rectangle(x,y,width, height)
{
    this.topLeft = new Point(x,y);
    this.bottomRight = new Point(x+width, y+height);
}
Rectangle.prototype.width = function()
{
    return (this.bottomRight.x - this.topLeft.x);
};
Rectangle.prototype.height = function()
{
    return (this.bottomRight.y - this.topLeft.y);
};

function Plot(config)
{
    this.lineColor = config.lineColor;
    this.lineWidth = config.lineWidth;
    this.legend = config.legend;
    this.value = new Array(config.maxIndex);
}

function Axis(config)
{
    this.min = config.min;
    if (this.min==='undefined')
        console.log("Axis minimum missing");
    this.max = config.max;
    if (this.max==='undefined')
        console.log("Axis maximum missing");
    if (this.max <= this.min)
        console.log("Axis max/min invalid");
    this.tickSpacing = config.tickSpacing;
    if (config.minValue !== 'undefined')
        this.minValue = config.minValue;
    else
        this.minValue = this.min;
    if (config.maxValue !== 'undefined')
        this.maxValue = config.maxValue;
    else
        this.maxValue = this.max;
    this.label = config.label;
    this.drawGrid = config.drawGrid;
}

Axis.prototype.range = function()
{
    return (Math.abs(this.max - this.min));
};

function Graph(config) 
{
    // user defined properties
    this.canvas = document.getElementById(config.canvasId);
    this.title = config.title;
    this.plots = config.plots;
    this.XAxis = config.XAxis;
    this.YAxis = config.YAxis;
    // constants
    this.axisColor = '#848484';
    this.font = '8pt Calibri';
    this.labelFont = '11pt Calibri';
    this.tickSize = 2;
    this.drawYGrid = true; //draw Y axis horizontal grids
    this.gridColor = '#e6e6e6'; //grid color used if either drawYGrid/drawXGrid
    this.context = this.canvas.getContext('2d');

    // relationships reset on resize()
    this.plotRect = new Rectangle(40,30, 0, 0);  
    this.centerY = Math.round(Math.abs(this.YAxis.min / this.YAxis.range()) * this.plotRect.height());
    this.centerX = Math.round(Math.abs(this.XAxis.min / this.XAxis.range()) * this.plotRect.width());
    this.scaleX = this.plotRect.width() / this.XAxis.range();
    this.scaleY = this.plotRect.height() / this.YAxis.range();
    /*
     * Offscreen canvas on which the axes, legends and static background is
     * drawn once and saved
     */
    this.offScrnCanvas = document.createElement('canvas');
    this.offSrcnCtx = this.offScrnCanvas.getContext('2d');
}

Graph.prototype.drawLegends = function()
{
    var txtWidth = 0;
    var offSrcnCtx = this.offSrcnCtx;
    offSrcnCtx.save();
    
    //draw the legends for each plot
    offSrcnCtx.font = this.labelFont;
    offSrcnCtx.textAlign = 'right';
    offSrcnCtx.textBaseline = 'bottom';
    for (var i=0; (this.plots != null) && (i<this.plots.length); ++i)
    {
        if (this.plots[i].legend.length > 0)
        {
            offSrcnCtx.fillStyle = this.plots[i].lineColor;;
            offSrcnCtx.fillText(this.plots[i].legend, 
                                this.plotRect.bottomRight.x-txtWidth, 
                                this.plotRect.topLeft.y);
            var w = offSrcnCtx.measureText(this.plots[i].legend);
            txtWidth += w.width+2;                    
        }
    }
    
    //draw the chart title
    offSrcnCtx.font = 'bold 12pt Calibri';
    offSrcnCtx.textAlign = 'center';
    offSrcnCtx.textBaseline = 'bottom';
    offSrcnCtx.fillStyle =this.axisColor;
    offSrcnCtx.fillText(this.title, 
                        this.plotRect.topLeft.x+this.plotRect.width()/2, 
                        this.plotRect.topLeft.y);
    
    offSrcnCtx.restore();
};


Graph.prototype.drawXAxis = function() 
{
    var xPosIncrement = this.XAxis.tickSpacing * this.scaleX;
    var xValueIncrement = (this.XAxis.maxValue-this.XAxis.minValue)/
                            (this.XAxis.range()/this.XAxis.tickSpacing);
    var xPos, yPos, unit;
    var offSrcnCtx = this.offSrcnCtx;
    offSrcnCtx.save();

    //daw vertical grids
    if (this.XAxis.drawGrid)
    {
        offSrcnCtx.beginPath();
        offSrcnCtx.lineWidth = 1;
        offSrcnCtx.strokeStyle = this.gridColor;
        xPos = this.centerX - xPosIncrement;
        while(xPos > this.plotRect.topLeft.x)
        {
            offSrcnCtx.moveTo(xPos, this.centerY - this.tickSize / 2);
            offSrcnCtx.lineTo(xPos, this.plotRect.topLeft.y);
            offSrcnCtx.stroke();
            offSrcnCtx.moveTo(xPos, this.centerY + this.tickSize / 2);
            offSrcnCtx.lineTo(xPos, this.plotRect.bottomRight.y);
            offSrcnCtx.stroke();
            xPos = Math.round(xPos - xPosIncrement);
        }
        
        xPos = this.centerX + xPosIncrement;
        while(xPos < this.plotRect.bottomRight.x) 
        {
            offSrcnCtx.moveTo(xPos, this.centerY - this.tickSize / 2);
            offSrcnCtx.lineTo(xPos, this.plotRect.topLeft.y);
            offSrcnCtx.stroke();
            offSrcnCtx.moveTo(xPos, this.centerY + this.tickSize / 2);
            offSrcnCtx.lineTo(xPos, this.plotRect.bottomRight.y);
            offSrcnCtx.stroke();
            xPos = Math.round(xPos + xPosIncrement);
        }
    }
    
    // draw tick marks  
    offSrcnCtx.beginPath();
    offSrcnCtx.moveTo(this.plotRect.topLeft.x, this.centerY);
    offSrcnCtx.lineTo(this.plotRect.bottomRight.x, this.centerY);
    offSrcnCtx.strokeStyle = this.axisColor;
    offSrcnCtx.lineWidth = 2;
    offSrcnCtx.stroke();

    offSrcnCtx.font = this.font;
    offSrcnCtx.textAlign = 'center';
    if (this.centerY < this.plotRect.bottomRight.y)
    {
        offSrcnCtx.textBaseline = 'top';
        yPos = 2;
    }
    else
    {
        offSrcnCtx.textBaseline = 'bottom';
        yPos = -2;
    }
        
    // draw left tick marks
    xPos = this.centerX - xPosIncrement;
    unit = -1 * this.XAxis.tickSpacing;
    while(xPos > this.plotRect.topLeft.x) 
    {
      offSrcnCtx.moveTo(xPos, this.centerY - this.tickSize / 2);
      offSrcnCtx.lineTo(xPos, this.centerY + this.tickSize / 2);
      offSrcnCtx.stroke();
      offSrcnCtx.fillText(unit, xPos, this.centerY + this.tickSize / 2 + yPos);
      unit -= this.XAxis.tickSpacing;
      xPos = Math.round(xPos - xPosIncrement);
    }
    offSrcnCtx.textAlign = 'left';
    xPos = this.centerX;
    unit = this.XAxis.minValue;
    offSrcnCtx.fillText(unit, xPos, this.centerY + yPos);
  
    //draw right tick marks
    offSrcnCtx.textAlign = 'center';
    xPos += xPosIncrement;
    unit += xValueIncrement;
    while(xPos < this.plotRect.bottomRight.x) 
    {
      offSrcnCtx.moveTo(xPos, this.centerY - this.tickSize / 2);
      offSrcnCtx.lineTo(xPos, this.centerY);
      offSrcnCtx.stroke();
      offSrcnCtx.fillText(unit, xPos, this.centerY + yPos);
      unit += xValueIncrement;
      xPos = Math.round(xPos + xPosIncrement);
    }
    offSrcnCtx.textAlign = 'right';
    offSrcnCtx.fillText(this.XAxis.maxValue, this.plotRect.bottomRight.x, 
                        this.centerY + yPos);
    
    //X Axis Label
    if (typeof this.XAxis.label !== 'undefined')
    {
        offSrcnCtx.font = this.labelFont;
        offSrcnCtx.textAlign = "center";
        if (this.centerY > this.plotRect.topLeft.y)
        {
            yPos = this.centerY;
            offSrcnCtx.textBaseline = 'bottom';
        } 
        else
        {
            yPos = this.centerY + 10;
            offSrcnCtx.textBaseline = 'top';
        }
        offSrcnCtx.fillText(this.XAxis.label, 
                            this.centerX+this.plotRect.width()/2,yPos);
    }
    offSrcnCtx.restore();
};

Graph.prototype.drawVerticalText = function(x,y, text)
{
    var offSrcnCtx = this.offSrcnCtx;
    offSrcnCtx.save();
    offSrcnCtx.translate(x,y);
    offSrcnCtx.rotate(-Math.PI/2);
    offSrcnCtx.textAlign = "center";
    offSrcnCtx.textBaseline = 'top';
    offSrcnCtx.fillText(text, 0, 0);
    offSrcnCtx.restore();    
};

Graph.prototype.drawYAxis = function() 
{
    var offSrcnCtx = this.offSrcnCtx;
    offSrcnCtx.save();
    //Major Y axis on left of plot rectangle
    offSrcnCtx.strokeStyle = this.axisColor;
    offSrcnCtx.lineWidth = 2;
    offSrcnCtx.beginPath();
    //offSrcnCtx.moveTo(this.plotRect.topLeft.x, this.plotRect.topLeft.y);
    //offSrcnCtx.lineTo(this.plotRect.topLeft.x, this.plotRect.bottomRight.y);
    offSrcnCtx.rect(this.plotRect.topLeft.x, this.plotRect.topLeft.y,
                    this.plotRect.width()-1, this.plotRect.height()-1);
    offSrcnCtx.stroke();

    //Y Axis Label
    offSrcnCtx.font = this.labelFont;
    this.drawVerticalText(2, this.plotRect.topLeft.y+this.plotRect.height()/2, 
                         this.YAxis.label);
 
    // draw tick marks
    var yPosIncrement = this.YAxis.tickSpacing * this.scaleY;
    var yPos, unit;
    offSrcnCtx.font = this.font;
    offSrcnCtx.textAlign = 'right';
    offSrcnCtx.textBaseline = 'middle';
    
    // draw top tick marks
    yPos = this.centerY - yPosIncrement;
    unit = this.YAxis.tickSpacing;
    while(yPos >= this.plotRect.topLeft.y) 
    {
      offSrcnCtx.moveTo(this.plotRect.topLeft.x - this.tickSize / 2, yPos);
      offSrcnCtx.lineTo(this.plotRect.topLeft.x + this.tickSize / 2, yPos);
      offSrcnCtx.stroke();
      offSrcnCtx.fillText(unit, this.plotRect.topLeft.x - this.tickSize / 2 - 3, yPos);
      unit += this.YAxis.tickSpacing;
      yPos = Math.round(yPos - yPosIncrement);
    }

    // draw bottom tick marks
    yPos = this.centerY + yPosIncrement;
    unit = -1 * this.YAxis.tickSpacing;
    while(yPos <= this.plotRect.bottomRight.y) 
    {
      offSrcnCtx.moveTo(this.plotRect.topLeft.x - this.tickSize / 2, yPos);
      offSrcnCtx.lineTo(this.plotRect.topLeft.x + this.tickSize / 2, yPos);
      offSrcnCtx.stroke();
      offSrcnCtx.fillText(unit, this.plotRect.topLeft.x - this.tickSize / 2 - 3, yPos);
      unit -= this.YAxis.tickSpacing;
      yPos = Math.round(yPos + yPosIncrement);
    }
  
    //draw the grid lines
    if (this.drawYGrid!=='undefined')
    {
        offSrcnCtx.beginPath();
        offSrcnCtx.lineWidth = 1;
        offSrcnCtx.strokeStyle = this.gridColor;        
        //offSrcnCtx.setLineDash([5, 5]);
        yPos = this.centerY - yPosIncrement;
        while(yPos > this.plotRect.topLeft.y) 
        {
            offSrcnCtx.moveTo(this.plotRect.topLeft.x + this.tickSize / 2, yPos);
            offSrcnCtx.lineTo(this.plotRect.bottomRight.x, yPos);
            offSrcnCtx.stroke();
            yPos = Math.round(yPos - yPosIncrement);
        }
        yPos = this.centerY + yPosIncrement;
        while(yPos < this.plotRect.bottomRight.y) 
        {
            offSrcnCtx.moveTo(this.plotRect.topLeft.x + this.tickSize / 2, yPos);
            offSrcnCtx.lineTo(this.plotRect.bottomRight.x, yPos);
            offSrcnCtx.stroke();
            yPos = Math.round(yPos + yPosIncrement);
        }
    }

    offSrcnCtx.restore();
};

Graph.prototype.update = function(xmarker, xmarker_label) 
{
    var context = this.context;
    context.save();
    //get the off screen image with X-Y grids, and other static data
    var image = this.offSrcnCtx.getImageData(0,0,this.offScrnCanvas.width,this.offScrnCanvas.width); 
    context.putImageData(image, 0, 0);
    
    //draw each plot 
    for (var i=0; (this.plots != null) && (i<this.plots.length); ++i)
    {
        context.save();
        // move context to center of canvas
        context.translate(this.centerX, this.centerY);
        //stretch grid to fit the canvas window, and invert the y scale so that 
        //that increments as you move upwards 
        context.scale(this.scaleX, -this.scaleY);
        context.beginPath();
        context.moveTo(this.XAxis.min, this.plots[i].value[0]);
        for(var x = this.XAxis.min + 1.0/this.scaleX; x <= this.XAxis.max; x += 1.0/this.scaleX) 
        {
            var tmp = Math.round(x);
            context.lineTo(tmp, this.plots[i].value[tmp]);
        }
        // reset current transformation matrix to the identity matrix
        context.setTransform(1, 0, 0, 1, 0, 0);
        context.lineJoin = 'round';
        context.lineWidth = this.plots[i].lineWidth;
        context.strokeStyle = this.plots[i].lineColor;
        context.stroke();
        context.restore();
    }
    //draw X marker if specified
    if (xmarker !== 'undefined')
    {
        if ((xmarker >= this.XAxis.min) && (xmarker <= this.XAxis.max))
        {
            context.save();
            context.translate(this.centerX, this.centerY);
            context.scale(this.scaleX, -this.scaleY);
            context.beginPath();
            context.moveTo(xmarker, this.YAxis.max);
            context.lineTo(xmarker, this.YAxis.min);
            context.lineWidth = 1; 
            context.strokeStyle = '#3399ff';
            context.setLineDash([5, 5]);
            context.stroke();
            context.restore();
            //Draw X marker label, if specified
            if (xmarker_label !== 'undefined')
            {
                context.translate(this.centerX, this.centerY);
                context.font = 'bold '+this.font;
                context.fillStyle = '#3399ff';
                context.textAlign = 'left';
                context.textBaseline = 'bottom';
                context.fillText(xmarker_label, xmarker*this.scaleX, 
                                 this.scaleY*this.YAxis.max);
            }
        }
    }

    context.restore();
};

Graph.prototype.resize = function()
{
    this.offScrnCanvas.width = this.canvas.width-10;
    this.offScrnCanvas.height = this.canvas.height-10; 
    this.plotRect.bottomRight.x= this.offScrnCanvas.width;  
    this.plotRect.bottomRight.y= this.offScrnCanvas.height; 
    if ((this.YAxis.min!==0)&&(this.YAxis.max!==0))
        this.centerY = Math.round(Math.abs(this.YAxis.min / this.YAxis.range()) * this.plotRect.height());
    else if (this.YAxis.min===0)
        this.centerY = this.plotRect.height();
    else
        this.centerY = 0;
    this.centerY += this.plotRect.topLeft.y;
    this.centerX = Math.round(Math.abs(this.XAxis.min / this.XAxis.range()) * this.plotRect.width());
    this.centerX += this.plotRect.topLeft.x;
    this.scaleX = this.plotRect.width() / this.XAxis.range();
    this.scaleY = this.plotRect.height() / this.YAxis.range();
    // draw x and y axis
    this.drawYAxis();  
    this.drawXAxis();        
    this.drawLegends();
    this.update();
};