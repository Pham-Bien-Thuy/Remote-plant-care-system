//HTML code for webpage
//=====================
const char webpageCode[] PROGMEM =
R"=====(
<!DOCTYPE HTML>
<html>
<head>
  <title>ESP32 Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
</head>
<!-------------------------------C S S------------------------------>
<style>
  #btn1
  {
    display: inline-block;
    text-decoration: none;
    background: #8CD460;
    color: rgba(255,255,255, 0.80);
    font-weight: bold;
    font: 60px arial, sans-serif;
    width: 150px;
    height: 150px;
    line-height: 150px;
    border-radius: 50%;
    text-align: center;
    vertical-align: middle;
    overflow: hidden;
    box-shadow: 0px 0px 0px 8px #8CD460;
    border: solid 2px rgba(255,255,255, 0.47);
    transition: 0.5s;
  }
  #btn2
  {
    display: inline-block;
    text-decoration: none;
    background: #8CD460;
    color: rgba(255,255,255, 0.80);
    font-weight: bold;
    font: 60px arial, sans-serif;
    width: 150px;
    height: 150px;
    line-height: 150px;
    border-radius: 50%;
    text-align: center;
    vertical-align: middle;
    overflow: hidden;
    box-shadow: 0px 0px 0px 8px #8CD460;
    border: solid 2px rgba(255,255,255, 0.47);
    transition: 0.5s;
  }
  html {
    font-family: Arial;
    display: inline-block;
    margin: 0px auto;
    text-align: center;
  }
  h2 { font-size: 3.0rem; }
  p { font-size: 3.0rem; }
  .unit { font-size: 1.2rem; }
  .dht-labels{
    font-size: 1.5rem;
    vertical-align:middle;
    padding-bottom: 15px;
  }
  body {text-align:center; font-family:"Calibri"; background-color:rgba(0, 3, 8, 0.26)}
  h1   {color: rgba(0, 0, 255, 0.87); font-size: 50px;}
</style>
<!------------------------------H T M L----------------------------->
<body>
   <h1>ESP32 Server</h1>
   <p>
      <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
      <span class="dht-labels">Temperature</span>
      <span id="temperature">36</span>
      <sup class="units">&deg;C</sup>
   </p>
   <p>
      <i class="fas fa-tint" style="color:#00add6;"></i>
      <span class="dht-labels">Humidity</span>
      <span id="humidity">61</span>
      <sup class="units">%</sup>
   </p>
   <p>
    <i class="fa fa-lightbulb" style="color:#e2e610;">&nbsp&nbsp&nbsp</i>
    <a href="#" id="btn1" ONCLICK='button1()'></a>
  </p>
  <p>
    <i class="fa fa-shower" style="color:#0076d6;">&nbsp&nbsp&nbsp</i> 
    <a href="#" id="btn2" ONCLICK='button2()'></a>
  </p>
<!-----------------------------JavaScript--------------------------->
  <script>
     InitWebSocket()
     function InitWebSocket()
     {
       websock = new WebSocket('ws://'+window.location.hostname+':81/'); 
       websock.onmessage = function(evt)
       {
          JSONobj = JSON.parse(evt.data);
          document.getElementById('btn1').innerHTML = JSONobj.LEDonoff;
          document.getElementById('btn2').innerHTML = JSONobj.PUMPonoff;

          if(JSONobj.LEDonoff == 'ON')
          {
            document.getElementById('btn1').style.background = '#FF0000';
            document.getElementById('btn1').style["boxShadow"] = "0px 0px 0px 8px #FF0000";
          }
          else
          {
            document.getElementById('btn1').style.background = '#111111';
            document.getElementById('btn1').style["boxShadow"] = "0px 0px 0px 8px #111111";
          }

          if(JSONobj.PUMPonoff == 'ON')
          {
            document.getElementById('btn2').style.background = '#FF0000';
            document.getElementById('btn2').style["boxShadow"] = "0px 0px 0px 8px #FF0000";
          }
          else
          {
            document.getElementById('btn2').style.background = '#111111';
            document.getElementById('btn2').style["boxShadow"] = "0px 0px 0px 8px #111111";
          }

          document.getElementById("temperature").innerHTML = JSONobj.Temperature;
          document.getElementById("humidity").innerHTML = JSONobj.Humidity;
       }
     }
     //-------------------------------------------------------------
     function button1()
     {
        btn1 = 'LEDonoff=ON';
        if(document.getElementById('btn1').innerHTML == 'ON')
        {
          btn1 = 'LEDonoff=OFF';
        }
        websock.send(btn1);
     }
     function button2()
     {
        btn2 = 'PUMPonoff=ON';
        if(document.getElementById('btn2').innerHTML == 'ON')
        {
          btn2 = 'PUMPonoff=OFF';
        }
        websock.send(btn2);
     }
  </script>
</body>
</html>
)=====";