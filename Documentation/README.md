# Controle remote para Antena Loop Magnética com SmartPhone Android e Arduino 

Este projeto é uma versão simplificada de um controle remoto implementado em Arduino e controlado por um dispositivo móvel baseado em Android. Com este projeto, será piossível controlar, por exemplo,  uma Antena Loop Magnética no estilo da [Alexloop](http://www.alexloop.com/index.html) ou de contrução caseira, via Bluetooth, a partir do seu dispositivo móvel baseado em Android. Veja os videos referênciados no final desta página. Acredito que este projeto possa oferecer os elementos básicos para projetos mais robustos envolvendo as tecnologias utilizadas aqui. 

Fortaleza, 3 de abril de 2019.
Por PU2CLR,
Ricardo Lima Caratti..

# Sumário
1. [Estrutura de pastas e arquivos](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#estrutura-de-pastas-e-arquivos)
2. [Código-fonte](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#código-fonte) 
3. [Esquema](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#esquema-elétrico)
   1. [Com um capacitor](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#versão-de-um-capacitor)
   2. [Com dois capacitores](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#versão-com-dois-capacitores)
4. [The Bluetooth shield used with Arduino](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner#the-bluetooth-shield-used-with-arduino)
5. [Android prototype](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner#arduino-circuit-built-on-protoboard)
6. [Messages received by Arduino via Bluetooth](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner#messages-received-by-arduino-via-bluetooth)
7. [Videos](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner#videos-about-this-project)




## Estrutura de pastas e arquivos

- A pasta [Box_3D_Printer](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Box_3D_Printer) contem o projeto de uma caixa construída em uma impressora 3D especialmente para a Alexloop ou similar. [Clique aqui](https://youtu.be/PbnP8gIDb78) para assistir a um vídeo sobre este projeto;
- A pasta [images](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/images) contém fotos sobre este projeto;
- A pasta [schematic](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/schematic) contém dois esquemas construído por meio do software  [fritzing](http://fritzing.org/home/), um programa livre para construção de esquemas elétricos. Há duas versões do projeto: uma utilizando um Servo para trabalhar somente com um capacitor; e outra utilizando dois servos para trabalhar com um capacitor principal e outro de sintonia fina;
- A pasta [sources](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/sources) contém os códigos-fonte do Aplicativo para SmartPhone para Android,  e dois sketchs (programas para Arduino).  

### Código-fonte

Todos os fontes utilizados neste projeto estão disponíveis na [pasta 'sources'](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Sources).  __Durante o upload para do sketch para o Arduino, você deve desconectar o Bluetooth do arduino__. É recomendável acompanhar a documentação escrita no programa.

Dependendo da configuração que você optar, um ou dois capacitores, bem como as especificações técnicas do servo que você utiliza, é possível que você precise modificar alguns parâmetros no sketch do Arduino e também no Aplicativo Android. 
Veja a documentação nos fontes [ArduinoOneCapacitor.ino][arduino-one-capacitor], [ArduinoTwoCapacitors.ino][arduino-two-capacitor] e [BluetoothTuner.java][bluetooth-tuner]. 


## Esquema elétrico

Há duas versões do sintonizador de antena. Uma com um capacitor e outra com dois capacitores. A opção com dois capacitores sugere que o capacitor de sintonia fina seja de baixa capacitância. Dessa forma, o processo de sintonia ficará mais fácil e mais preciso. Este [vídeo (clique aqui)](https://youtu.be/w_jXJsiMKIk) ilustra a o sintonizador com dois capacitores.  

### Versão de um capacitor 

O esquema a seguir ilustra a versão do sintonizador de antena configurado para somente um capacitor acoplado a um servo. Esta versão se aplica para antenas no estilo da Alexloop ou loop magnética de construção caseira que utiliza capacitores váriáveis com duas ou mais seções.  

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/schematic/minimalist_schematic.png" alt="One capacitor schematic" >


### Versão com dois capacitores 

O esquema a segui apresenta a versão do sintonizador com dois capacitores acoplados em dois servos.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/schematic/minimalist_schematic_tow_capacitors.png" alt="One capacitor schematic" >


### Dispositivo Bluetooth utilizado neste projeto

Os dispositivos HC-05 e HC-06 e HC07 funcionaram com sucesso. Não obtive sucesso com versões Bluetooth no padrão BLE. 

As fotos a seguir ilustra o Bluetooth utilizado neste projeto. 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/BT01.jpg" alt="Android Remote Control"  height="500" width="300" class="center" >

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/BT02.jpg" alt="Android Remote Control"  height="500" width="300" class="center" >



### Foto do protótipo utilizado

A foto a seguir mostra a configuração do  Android, Bluetooth e Servo. É recomendável que você verifique as especificações do servo que você estiver utilizado. É possível que você necessite alterar  algumas definições do servo no sketch.  Tente acompanhar a documentação existente no próprio sketch.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/arduino_prototype.png" alt="Android Remote Control"  height="500" width="300" class="center" >


#### Aplicativo Android

The version of Android Application used here was built in 2014. The last Android Studio used to build it was 3.3.2 (2019). Probable, you will need to do some adjust on your IDE environment to build this application.

##### Android Remote Controll - Photo 1

Connecting to Bluetooth you should press the Bluetooth button and select the paired Bluetooth, in this case it is HC07.  You have to pair the bluetooth before by using system interface. 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_01.png" alt="Android Remote Control"  height="500" width="300" class="center" >


##### Android Remote Controll - Photo 2

Selecting the paired bluetotth. 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_02.png" alt="Android Remote Control" height="500" width="300" class="center">


##### Android Remote Controll - Photo 3

Bluetooth paired and ready to send commands to Arduino circuit.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_03.png" alt="Android Remote Control" height="500" width="300" class="center">



Este [vídeo](https://youtu.be/OKky8gmOWz8) apresenta o projeto de caixa em impressora 3D e o controle remoto.



## References

- [Arduino](https://www.arduino.cc)
- [App Inventor](http://appinventor.mit.edu/explore/index-2.html)
- [Bluetooth HC-05 specification](https://electrosome.com/hc-05-serial-bluetooth-module/)

## Vídeos

- [A vertion of this project working (Youtube Video)](https://youtu.be/PbnP8gIDb78)
- [Remote Tuner for Alexloop (Part I)](https://youtu.be/ZKfOUCcYrz8)
- [Remote Tuner for Alexloop (Part II)](https://youtu.be/PbnP8gIDb78)
- [Antenna Tuner with two capacitors controlled by Arduino](https://youtu.be/Rwl3G2ET7Jw)
- [Antenna Tuner with two capacitors controlled by Arduino - Part II](https://youtu.be/hfnlE1sbnEk)
- [New Android Interface for Antenna Tuner](https://youtu.be/w_jXJsiMKIk)



[//]: References

[arduino-one-capacitor]: <https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/sources/ArduinoOneCapacitor/ArduinoOneCapacitor.ino>

[arduino-two-capacitor]: <https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/sources/ArduinoTwoCapacitors/ArduinoTwoCapacitors.ino>

[bluetooth-tuner]: <https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/sources/AndroidApplication/app/src/main/java/br/eti/caratti/AntennaTuner/BluetoothTuner.java>
