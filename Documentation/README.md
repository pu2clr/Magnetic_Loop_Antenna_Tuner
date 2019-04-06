# Antena Loop Magnética controlada por SmartPhone Android e Arduino 

Este projeto é uma versão básica de um Sintonizador de Antenas implementado com Arduino e controlado por um dispositivo móvel baseado em Android. Com este projeto, será piossível controlar, por exemplo, sintonizar remotamente uma Antena Loop Magnética no estilo da [Alexloop](http://www.alexloop.com/index.html) ou de contrução caseira, via Bluetooth, a partir do seu dispositivo móvel (celular ou tablet) baseado em Android. Veja os vídeos referênciados no final desta página. Acredito que este projeto possa oferecer os elementos básicos para projetos mais robustos envolvendo as tecnologias utilizadas aqui. 

Fortaleza, 3 de abril de 2019.

Por PU2CLR,

Ricardo Lima Caratti..


# Sumário
1. [Estrutura de pastas e arquivos](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#estrutura-de-pastas-e-arquivos)
2. [Como baixar os arquivos deste projeto (Download)]()
3. [Código-fonte](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#código-fonte) 
4. [Esquema](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#esquema-elétrico)
   1. [Com um capacitor](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#versão-de-um-capacitor)
   2. [Com dois capacitores](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#versão-com-dois-capacitores)
5. [Dispositivo Bluetooth utilizado neste projeto](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#dispositivo-bluetooth-utilizado-neste-projeto)
6. [Prtótipo Android](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner#arduino-circuit-built-on-protoboard)
7. [Protocolo de mensagem (Spartphone e Arduino via Bluetooth)]()
8. [Videos](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner#videos-about-this-project)




## Estrutura de pastas e arquivos

Este trabalho está organizado em pastas. Cada pasta possui o conteúdo descrito a seguir: 

- A pasta [Box_3D_Printer](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Box_3D_Printer) contem o projeto de uma caixa construída em uma impressora 3D especialmente para a Alexloop ou similar. [Clique aqui](https://youtu.be/OKky8gmOWz8) para assistir a um vídeo sobre este projeto;
- A pasta [images](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/images) contém fotos sobre este projeto;
- A pasta [schematic](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/schematic) contém dois esquemas construído por meio do software  [fritzing](http://fritzing.org/home/), um programa livre para construção de esquemas elétricos. Há duas versões do projeto: uma utilizando um Servo para trabalhar somente com um capacitor; e outra utilizando dois servos para trabalhar com um capacitor principal e outro de sintonia fina;
- A pasta [sources](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/sources) contém os códigos-fonte do Aplicativo para SmartPhone para Android,  e dois sketchs (programas para Arduino).  


## Como baixar os arquivos deste projeto (Download)

Toda a documentação deste projeto, incluindo código-fonte dos programas para Arduino e Android podem ser baixados clicando  [aqui](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner.git).


## Código-fonte

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

As fotos a seguir ilustram o Bluetooth utilizado neste projeto. 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/BT01.jpg" alt="Android Remote Control"  height="500" width="300" class="center" >

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/BT02.jpg" alt="Android Remote Control"  height="500" width="300" class="center" >



### Foto do protótipo utilizado um capacitor

A foto a seguir mostra a configuração do  Android, Bluetooth e Servo. É recomendável que você verifique as especificações do servo que você estiver utilizado. É possível que você necessite alterar  algumas definições do servo no sketch.  Tente acompanhar a documentação existente no próprio sketch.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/arduino_prototype.png" alt="Android Remote Control"  height="500" width="300" class="center" >


### Two Capacitors version

A foto a seguir apresenta a montágem da versão do protótipo utilizando dois servos que serão acoplados a dois capacitores. 
O sketch [ArduinoTwoCapacitor.ino][arduino-two-capacitor] implementa este versão.    

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/arduino_prototype_two_cap.png" alt="Android Remote Control"  height="500" width="300" class="center" >


#### Aplicativo Android

A aplicação para dispositivo android foi desenvolvido em 2014 utilizando os recursos nativos do ambiente de desenvolvimento para Android (conhecido atualmente como Android Studio). A última compilação deste aplicativo foi em 2019 utilizando o [Android Studio 3.3.2.](https://developer.android.com/studio/). O programa está bem documentado e poderá ajudá-lo a entender como foi feita a comunicação de um dispositivo Android com o Arduino via Bluetooth. O módulo principal do aplicativo é o [BluetoothTuner.java][bluetooth-tuner].  Baixe e instale o [Android Studio](https://developer.android.com/studio/) e siga as orientações do ambiente de desenvolvimento Android para abrir, compilar e instalar o aplicativo no seu dispositivo móvel. 

Atualmente há outros ambientes de desenvolvimento para Android mais fácies de utilizar e desenvolver esse tipo de aplicativo. Recomendo fortemente a utilização do [MIT App Inventor](http://appinventor.mit.edu/explore/index-2.html). Veja também outros ambientes de desenvolvimento multiplatafotma como [Apache Cordova](https://cordova.apache.org) e [Ionic](https://ionicframework.com).

##### Android Remote Controll - Photo 1

A figura a seguir ilustra a primeira tela do aplicativo. Você precisará parear o Bluetooth previamente em seu dispositivo móvel (celular ou tablet). 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_01.png" alt="Android Remote Control"  height="500" width="300" class="center" >


##### Android Remote Controll - Photo 2

Na lista de dispositivos Bluetooth pareados, selecione o Bluetooth conectado ao Arduino (foi usando nos testes o HC-05, HC-06 e HC-07). 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_02.png" alt="Android Remote Control" height="500" width="300" class="center">


##### Android Remote Controll - Photo 3

Uma vez conectado o Bluetooth com sucesso, o Aplicativo pode ser utilizado para enviar comandos para o Arduino.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_03.png" alt="Android Remote Control" height="500" width="300" class="center">




## Protocolo de mensagem (Spartphone e Arduino via Bluetooth)

O Arduino recebe as mensagens enviadas pelo Aplicativo Android via conexão [UART](https://paginas.fe.up.pt/~hsm/docencia/comp/uart/). Qualquer programa que utiliza Bluetooth e for capaz de enviar sequencias de caracteres poderá ser utilizado. A tabela a seguir apresenta os comandos (mensagens) e as ações executadas pelo Arduino.   

Para mais informações, veja no sketch Arduino ([ArduinoOneCapacitor.ino][arduino-one-capacitor] ou [ArduinoTwoCapacitors.ino][arduino-two-capacitor]), as constantes definidas FINE_TUNE, NORMAL_TUNE, LARGE_TUNE, MIN_PULSE and MAX_PULSE.  Estas constantes definem a largura de pulso para rodar o servo vendidos. Embora a maioria dos servos encontrados no comércio utilizem especificações similares, é possível que você precise modificar os valores para adequar melhor ao seu servo. O condigo-fonte [BluetoothTuner.java][bluetooth-tuner] (do aplicativo Android) também pode precisar de ajustes dependendo do seu servo. 

### Tabela de comandos recebidos pelo Arduino via Bluetooth

| Character | Description |
| --------- | ----------- |
| + | Sintonia fina no sentido horário |
| - | Sintonia fina no sentido anti-horário |
| r | Sintonia média no sentido horário |
| l | Sintonia média no sentido anti-horário |
| R | Sintonia larga no sentido horário |
| L | Sintonia larga no sendito anti-horário |
| M | Faz com que o servo ou servos girem até a posição máxima |
| m | Faz com que o servo  ou servos girem até a posição mínima |
| C or c | Posiciona o servo ou servos no centro |
| F | Esta mensagem vem composta com número e conduz o servo para uma posição específica. Exemplo: a mensagem F1000# faz com que o servo vá para a posição 1000. | 
| T | Como descrito em  anteriormente ('F') este mensagem conduz o servo para ir para uma dada posição. Examplo: a mensagem  T1500# faz com que o servo vá para a posição 1500.|


##### IMPORTANT 

The files  [ArduinoOneCapacitor.ino][arduino-one-capacitor], [ArduinoTwoCapacitors.ino][arduino-two-capacitor] and [BluetoothTuner.java][bluetooth-tuner] will help you understand the Antenna Tuner comunication protocol. 




Este [vídeo](https://youtu.be/OKky8gmOWz8) apresenta o projeto de caixa em impressora 3D e o controle remoto.



## References

- [Arduino](https://www.arduino.cc)
- [App Inventor](http://appinventor.mit.edu/explore/index-2.html)
- [Bluetooth HC-05 specification](https://electrosome.com/hc-05-serial-bluetooth-module/)

## Vídeos

- [Sobre a versão deste projeto no Youtube](https://youtu.be/PbnP8gIDb78)
- [Remote Tuner for Alexloop (Part I)](https://youtu.be/ZKfOUCcYrz8)
- [Remote Tuner for Alexloop (Part II)](https://youtu.be/PbnP8gIDb78)
- [Antenna Tuner with two capacitors controlled by Arduino](https://youtu.be/Rwl3G2ET7Jw)
- [Antenna Tuner with two capacitors controlled by Arduino - Part II](https://youtu.be/hfnlE1sbnEk)
- [New Android Interface for Antenna Tuner](https://youtu.be/w_jXJsiMKIk)



[//]: References

[arduino-one-capacitor]: <https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/sources/ArduinoOneCapacitor/ArduinoOneCapacitor.ino>

[arduino-two-capacitor]: <https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/sources/ArduinoTwoCapacitors/ArduinoTwoCapacitors.ino>

[bluetooth-tuner]: <https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/sources/AndroidApplication/app/src/main/java/br/eti/caratti/AntennaTuner/BluetoothTuner.java>
