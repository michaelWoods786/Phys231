char webpage[] PROGMEM = R"=====(
<html>
   <head>
      <script src ='/Chart.js'></script>
   </head>
   <body onload="javascript:init()">
      Michael Woods Pot val:
      <div id="PotValue"></div>
      Uptime:
      <div id="Uptime"></div>
      <br>
      <canvas id = "line-chart" width = "400" height = "225"></canvas>
   </body>
   <script>
      var Socket, dataPlot;
      function addData(label, data){
        dataPlot.data.labels.push(label);
        dataPlot.data.datasets[0].data.push(data);
        dataPlot.update();
      }
      
      function init() {
        Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
        dataPlot = new Chart(document.getElementById("line-chart"),{
          type: 'line',
          data:{
            labels:[],
            datasets:[{
              data:[],
              label: "Pot Value",
              borderColor: "#56a0d10",
             fill: false,
            }]
          }
        });
        
        Socket.onmessage = function(event){
          var data = JSON.parse(event.data);
//          console.log(data); //debugging
          
          //Set up time 
          var today = new Date();
          var hours = today.getHours();
          var minutes = today.getMinutes();
          var seconds = today.getSeconds();
          var ampm = hours >= 12? 'pm' : 'am';
          hours = hours %12;
          hours = hours ? hours:12;
          minutes = minutes < 10 ? '0'+minutes : minutes;
          var t = hours + ':' + minutes + ':' + seconds+ ' ' + ampm;

          // Add data and update on screen pot value
          addData(t, data.value);
          document.getElementById("PotValue").innerHTML = data.value;
        }
      }  
   </script>
</html>
)=====";
