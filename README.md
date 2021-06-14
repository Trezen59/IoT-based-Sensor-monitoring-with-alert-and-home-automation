# IoT-based-Sensor-monitoring-with-alert-and-home-automation
<b>Working Model :</b>

![IMG_20210607_155026](https://user-images.githubusercontent.com/72198810/121846411-9e0ac000-cd04-11eb-8607-25bbb9a75ed8.jpg)
<b>Schematics :</b>


![mini project_bb](https://user-images.githubusercontent.com/72198810/121846496-b4188080-cd04-11eb-9c3f-46e22dbd9a2e.jpg)


<b>Detailed Working :</b>

Have you ever wished you have a fully automatic monitoring system for even the smallest things that gives data and need to be monitored ?

Have you imagined controlling your house remotely whenever you like, even to avoid a hazardous circumstance ?

Yes, This is what my mini-project is all about.

My mini-project "IoT based sensor monitoring with alert and home automation" gives you full control over the enviroment you install it in. for example take a vegetation, this vegitation is very sensitive to the surrounding enviroment, you want to control the temperature, humidity and light of the place where you grow the vegetation and monitor these values continuously. If you see any changes in the specified values of temperature, humidity and light you will immediately get a notification on your hand-held device and then you can control the controlling parameters however you like, if the temperature is increased the system will give you a notification and then by the web interface you can decrease the temperature so that no harm is caused to the vegetation. 

I have used NodeMCU which has ESP8266 Wi-Fi module to connect to the internet. I have also interfaced a LCD to display the IP address alloted to connect the devices and control them further. first of all we will have to configure all sensors to the microcontroller and then connect the microcontroller to Thingspeak IoT cloud service to send data to the respective sensor channel. Make sensor channels to store data specifically. Using React application in Thingspeak we can react upon the data, this React application will trigger the ThingHTTP to send a HTTP request to IFTTT where we have already configured the webhooks and notifier. IFTTT then sends us a notification on our device whenever the sensor data breaches the predefined sensor value. 

On recieving the notification we can open our web interface immediately and control the devices accordigly to the notification recieved, I have used relay module to control the AC load but you can aso use any switching devices ap per your load.


<b>Web UI :</b>

![web_ui](https://user-images.githubusercontent.com/72198810/121849665-3efb7a00-cd09-11eb-9c1d-eb76472ac40d.JPG)








