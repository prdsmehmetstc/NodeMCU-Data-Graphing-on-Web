const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>

<head>
  <title>Data Graph | Mehmet SUTCU</title>
  <script src = "https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.3/Chart.min.js"></script>  
  <style>
  canvas{
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
  }

  /* Data Table Styling */
  #dataTable {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
  }

  #dataTable td, #dataTable th {
    border: 1px solid #ddd;
    padding: 8px;
  }

  #dataTable tr:nth-child(even){background-color: #f2f2f2;}

  #dataTable tr:hover {background-color: #ddd;}

  #dataTable th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #4CAF50;
    color: white;
  }
  </style>
</head>

<body>
    <div style="text-align:center;"><b>Mehmet SUTCU - mehmetsutcu.com</b><br>Data Logging with Plotting Graphs on ESP8266</div>
    <div class="chart-container" position: relative; height:350px; width:100%">
        <canvas id="Chart" width="400" height="400"></canvas>
    </div>
<div>
  <table id="dataTable">
    <tr><th>Time</th><th>NTC Temp (&deg;C)</th><th>Gyro Temp (&deg;C)</th><th>Ax</th><th>Ay</th><th>Az</th><th>Gx</th><th>Gy</th><th>Gz</th></tr>
  </table>
</div>
<br>
<br>  

<script>
var ADCvalues = [];
var Tvalues = [];
var Axvalues = [];
var Ayvalues = [];
var Azvalues = [];
var Gxvalues = [];
var Gyvalues = [];
var Gzvalues = [];
var timeStamp = [];
function showGraph()
{
    var ctx = document.getElementById("Chart").getContext('2d');
    var Chart2 = new Chart(ctx, {
        type: 'line',
        data: {
            labels: timeStamp,  //Bottom Labeling
            datasets: [{
                label: "NTC Temp",
                fill: false,  //Try with true
                backgroundColor: 'rgba( 243,18, 156 , 1)', //Dot marker color
                borderColor: 'rgba( 243, 18, 156 , 1)', //Graph Line Color
                data: ADCvalues,
            },{
                label: "Gyro Temp",
                fill: false,  //Try with true
                backgroundColor: 'rgba( 156, 200, 243 , 1)', //Dot marker color
                borderColor: 'rgba( 156, 200, 243 , 1)', //Graph Line Color
                data: Tvalues,
            },{
                label: "Ax",
                fill: false,  //Try with true
                backgroundColor: 'rgba( 100, 200, 100 , 1)', //Dot marker color
                borderColor: 'rgba( 100, 200, 100 , 1)', //Graph Line Color
                data: Axvalues,
            },{
                label: "Ay",
                fill: false,  //Try with true
                backgroundColor: 'rgba( 200, 100, 100 , 1)', //Dot marker color
                borderColor: 'rgba( 200, 100, 100 , 1)', //Graph Line Color
                data: Ayvalues,
            },{
                label: "Az",
                fill: false,  //Try with true
                backgroundColor: 'rgba( 200, 100, 200 , 1)', //Dot marker color
                borderColor: 'rgba( 200, 100, 200 , 1)', //Graph Line Color
                data: Azvalues,
            },{
                label: "Gx",
                fill: false,  //Try with true
                backgroundColor: 'rgba( 18, 50, 100 , 1)', //Dot marker color
                borderColor: 'rgba( 18, 50, 100 , 1)', //Graph Line Color
                data: Gxvalues,
            },{
                label: "Gy",
                fill: false,  //Try with true
                backgroundColor: 'rgba( 10, 150, 150 , 1)', //Dot marker color
                borderColor: 'rgba( 10, 150, 150 , 1)', //Graph Line Color
                data: Gyvalues,
            },
            {
                label: "Gz",
                fill: false,  //Try with true
                backgroundColor: 'rgba(100, 50, 18 , 1)', //Dot marker color
                borderColor: 'rgba(100, 50, 18 , 1)', //Graph Line Color
                data: Gzvalues,
            }],
        },
        options: {
            title: {
                    display: true,
                    text: "Data Graphs"
                },
            maintainAspectRatio: false,
            elements: {
            line: {
                    tension: 0.5 //Smoothening (Curved) of data lines
                }
            },
            scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero:true
                        }
                    }]
            }
        }
    });

}

//On Page load show graphs
window.onload = function() {
  console.log(new Date().toLocaleTimeString());
};

setInterval(function() {
  getData();
}, 1000); //1000 milliseconds update rate
 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
     //Push the data in array
  var time = new Date().toLocaleTimeString();
  var txt = this.responseText;
  var obj = JSON.parse(txt);
      ADCvalues.push(obj.ADC);
      Tvalues.push(obj.Temperature);
      Axvalues.push(obj.Ax);
      Ayvalues.push(obj.Ay);
      Azvalues.push(obj.Az);
      Gxvalues.push(obj.Gx);
      Gyvalues.push(obj.Gy);
      Gzvalues.push(obj.Gz);
      timeStamp.push(time);
      showGraph();  //Update Graphs
  //Update Data Table
    var table = document.getElementById("dataTable");
    var row = table.insertRow(1);
    var cell1 = row.insertCell(0);
    var cell2 = row.insertCell(1);
    var cell3 = row.insertCell(2);
    var cell4 = row.insertCell(3);
    var cell5 = row.insertCell(4);
    var cell6 = row.insertCell(5);
    var cell7 = row.insertCell(6);
    var cell8 = row.insertCell(7);
    var cell9 = row.insertCell(8);
    cell1.innerHTML = time;
    cell2.innerHTML = obj.ADC;
    cell3.innerHTML = obj.Temperature;
    cell4.innerHTML = obj.Ax;
    cell5.innerHTML = obj.Ay;
    cell6.innerHTML = obj.Az;
    cell7.innerHTML = obj.Gx;
    cell8.innerHTML = obj.Gy;
    cell9.innerHTML = obj.Gz;
    }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
}
    
</script>
</body>

</html>

)=====";
