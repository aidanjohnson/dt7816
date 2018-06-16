var websocket=null;

function ws_open(url)
{
    if (websocket !== null)
        return;
    websocket = new WebSocket('ws://' + location.host + '/' + url);
    websocket.binaryType = "arraybuffer";
    websocket.onopen = function(ev) 
    {
        console.log("ws onopen");
    };
    websocket.onclose = function(ev) 
    {
        console.log("ws onclose " + ev.code);
        websocket=null;
    };
    websocket.onmessage = function(ev) 
    {
        console.log("ws onmessage");
        if (!ev.data) return;
        var buffer = ev.data;
        var status = new Uint32Array(buffer, 0, 3);
        if (status[0] === 1) //1=download data as CSV 
             $('#csv-download').show();
        else
             $('#csv-download').hide();
        if (status[2] > 0) //#of buffers completed since acquisition started
        {
            $('#buff-done').text(status[2] + " buffers completed");
        }
        console.log("Download " + status[0] + " overun " + status[1]);
    };
    websocket.onerror = function(ev) 
    {
        console.log("ws onerror");
    };
}
