# Bluetooth Remote control for Magnetic Antenna Tuner 

This project is about a Remote Control for Magnetic Loop Antenna controlled by Arduino and Android via Bluetooth.

This project is being reviewed. 

The version with One Capacitor will be released soon.
The version with Two Capacitors need to be checked and tested.  

The Android Application is working.

## Folders structure

### Source code


All Arduino and Android Application code are avaiable on [Sources folder](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Sources). There are two kinds of Arduino Antenna Tuner Controllers that you can use.

#### One Capacitor setup

There is just one capacitor to control the Band, Tune and Fine Tune. [This video shows a example of this kind of Antenna Tuner](https://youtu.be/PbnP8gIDb78)

##### One Capacitor Schematic 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/schematic/minimalist_schematic.png" alt="One capacitor schematic" >


#### Two Capacitors setup

One Servo to control Band and regular Tune; and other Servo to control the fine Tune. [This video shows a example of this kind of Antenna Tuner](https://youtu.be/w_jXJsiMKIk)

##### Two Capacitors Schematic 


<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/schematic/two_capacitor.png" alt="Android Remote Control">


#### Android Application 

The version of Android Application used here was built in 2014. The last Android Studio used to build it was 3.3.2 (2019). Probable, you will need to do some adjust on your IDE environment to build this application.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_01.jpg" alt="Android Remote Control" height="889" width="500">

This [video](https://youtu.be/OKky8gmOWz8) shows the box 3D printer project, hardware and software working with an Alexloop Antenna.  




# References

Arduino
https://www.arduino.cc

Anyone Can Build Apps That Impact the World
http://appinventor.mit.edu/explore/index-2.html



