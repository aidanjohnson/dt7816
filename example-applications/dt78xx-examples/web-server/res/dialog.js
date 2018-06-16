//The magic code to add show/hide custom event triggers
(function ($) {
      $.each(['show', 'hide'], function (i, ev) {
        var el = $.fn[ev];
        $.fn[ev] = function () {
          this.trigger(ev);
          return el.apply(this, arguments);
        };
      });
    })(jQuery);

/*Popup dialog. 
 * form_id is the form element with class="dialog-content" that will be displayed as
 * a dialog box. form_id must be prepended with # as per jQuery rules
 * The values in the specified form will be read from the DT78xx by GETing URL
 * form_id.io, i.e. if form_id is #foo then the URL will be foo.io
 */
function popup(form_id) 
{
    // get the screen height and width  
    var maskHeight = $(document).height();  
    var maskWidth = $(window).width();
    
    // calculate the values for center alignment
    var dialogTop =  (maskHeight/3) - ($('#dialog-box').height());  
    var dialogLeft = (maskWidth/2) - ($('#dialog-box').width()/2); 
    
    // assign values to the overlay and dialog box
    $('#dialog-overlay').css({height:maskHeight, width:maskWidth}).show();
    $('#dialog-box').css({top:dialogTop, left:dialogLeft}).show();
    
    //update the elements by XMLHttp GETing it from URL
    var url = form_id.slice(1)+".io";
    $.get(url, function(data, status)
    {
        /*
         * Response is a list of id=value pairs separated by &. 
         * The id is the id of the HTML element in the page and the value 
         * is that element's value
         */
        var cfg = data.split("&");
        for (i=0; i< cfg.length; ++i)
        {
            var token = cfg[i].split("=");
            var id = token[0];
            if (id === "")
                continue;
            var value = token[1];
            var tag=$(id).prop("tagName");
            var attr=$(id).attr("type");
            console.log(id + "=" + value +";"+tag+","+attr);
            //special cases
            if (($(id).attr("type") === "checkbox") ||
                ($(id).attr("type") === "radio"))
            {
                $(id).prop('checked', (value > 0)?true:false);
            }
            else if ($(id).prop("tagName").toLowerCase() === "span")
                $(id).text(value);
            else
                $(id).val(value);
        }
        // show the "dialog-content" whose id is specified AFTER the AJAX Get
        // function above has updated DOM elements
        $(form_id).show();
    });     
}
//Dismiss the dialog
function dismiss()
{
    $("#dialog-overlay, #dialog-box").hide();
    $("#dialog-box").children().hide(); 
}
    
// if user resizes the window, call the same function again
// to make sure the overlay fills the screen and dialogbox aligned to center    
$(window).resize(function () 
{
    //only do it if the dialog box is not hidden
    if (!$('#dialog-box').is(':hidden')) popup();       
}); 



