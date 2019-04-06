# Antena Loop Magnética controlada por SmartPhone Android e Arduino 

Este projeto é uma versão básica de um Sintonizador de Antenas implementado com Arduino e controlado por um dispositivo móvel baseado em Android. Com este projeto, será piossível controlar, por exemplo, sintonizar remotamente uma Antena Loop Magnética no estilo da [Alexloop](http://www.alexloop.com/index.html) ou de contrução caseira, via Bluetooth, a partir do seu dispositivo móvel (celular ou tablet) baseado em Android. Há duas opções sugeridas aqui: uma utilizando o sintonizador de antenas com um capacitor e outra com dois capacitores. Assista aos vídeos referênciados no final desta página. Acredito que este projeto possa oferecer os elementos básicos para projetos mais robustos envolvendo as tecnologias utilizadas aqui. 

Fortaleza, 3 de abril de 2019.
Por PU2CLR,
Ricardo Lima Caratti.

# Sumário
1. [Estrutura de pastas e arquivos](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#estrutura-de-pastas-e-arquivos)
2. [Como baixar os arquivos deste projeto (Download)](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#como-baixar-os-arquivos-deste-projeto-download)
3. [Trechos de código sensíveis ao tipo de servo utilizado]()
4. [Código-fonte](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#código-fonte) 
5. [Esquema](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#esquema-elétrico)
   1. [Com um capacitor](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#versão-de-um-capacitor)
   2. [Com dois capacitores](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#versão-com-dois-capacitores)
6. [Dispositivo Bluetooth utilizado neste projeto](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#dispositivo-bluetooth-utilizado-neste-projeto)
7. [Protótipo Arduino](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#protótipo-arduino)
   1. [Versão com um capacitor](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#versão-com-um-capacitor)
   2. [Versão com dois capacitores](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#versão-com-dois-capacitores-1)
8. [Aplicativo Android](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#aplicativo-android) 
9. [Protocolo de mensagem (Spartphone e Arduino via Bluetooth)](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Documentation#protocolo-de-mensagem-spartphone-e-arduino-via-bluetooth)
10. [Videos](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner#videos-about-this-project)


## Estrutura de pastas e arquivos

Este trabalho está organizado em pastas. Cada pasta possui o conteúdo descrito a seguir: 

- A pasta [Box_3D_Printer](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Box_3D_Printer) contem o projeto de uma caixa construída em uma impressora 3D especialmente para a [Alexloop][alex-loop] ou similar. [Clique aqui](https://youtu.be/OKky8gmOWz8) para assistir a um vídeo sobre este projeto;
- A pasta [images](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/images) contém fotos sobre este projeto;
- A pasta [schematic](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/schematic) contém dois esquemas construído por meio do software  [fritzing](http://fritzing.org/home/), um programa livre para construção de esquemas elétricos. Há duas versões do projeto: uma utilizando um Servo para trabalhar somente com um capacitor; e outra utilizando dois servos para trabalhar com um capacitor principal e outro de sintonia fina;
- A pasta [sources](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/sources) contém os códigos-fonte do Aplicativo para SmartPhone para Android,  e dois sketchs (programas para Arduino).  


## Como baixar os arquivos deste projeto (Download)

A estrutura de pastas e arquivos descrita no item anterior é apresentada neste repositório de projetos conforme ilustra a figura a seguir. Clique [aqui](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner.git) para entrar na página  e em seguinda clique no botão verde, à direita,  identificado por "Clone or Download". 

[![Página para Download do projeto](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/figura_download.png)](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner.git/)


## Código-fonte

Todos os fontes utilizados neste projeto estão disponíveis na [pasta 'sources'](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Sources).  __Durante o upload para do sketch para o Arduino, você deve desconectar o Bluetooth do arduino__. É recomendável acompanhar a documentação escrita no programa.

Dependendo da configuração que você optar, um ou dois capacitores, bem como as especificações técnicas do servo que você utiliza, é possível que você precise modificar alguns parâmetros no sketch do Arduino e também no Aplicativo Android. 
Veja a documentação nos fontes [ArduinoOneCapacitor.ino][arduino-one-capacitor], [ArduinoTwoCapacitors.ino][arduino-two-capacitor] e [BluetoothTuner.java][bluetooth-tuner]. 


### Trechos de código sensíveis ao tipo de servo utilizado

Os trechos de coódigo a seguir ilustram a configuração no Aplicativo Android  (em Java) e Arduino (em C/C++) que permitem um ajuste fino do servo e capacitor utilizado por você. Caso não conheça os valores especificados pelo seu servo, inicie seus testes sem fazer alteração nos códigos

#### Techos no Aplicativo Android (BluetoothTuner.java)

O código a seguir define os limites máximo (MAXPOS) e mínimo (OFFSET), bem como a posição central (CENTER) do servo no Aplicativo Android. Os componentes de interface do aplicativo __SeekBar__ (barras Band, Tune e Fine Tune) utilizam estes valores como referência para enviar valores entre os limites (MAXPOS e OFFSET) para o servo na proporção que o usuário do aplicativo arrasta o dedo sobre os componentes de interface. 

```java
    // You might change this setup depending of your servo specification
    public int OFFSET = 800;   // Min. Pisition  (0 degree)
    public int MAXPOS = 2200;  // Max. position  (Max. degrre)
    public int CENTER = (MAXPOS - OFFSET)/2 + OFFSET /2;   // Center is CENTER + OFFSET
```

O código a seguir configura a sintonia fina (Tune e Fine Tune) e usa como referência as constantes descritas anteriormente. Note também que esses valores dependendo da configuração selecionada (um ou dois capacitores), os valores dos componentes de sintonia fina mudam. É possível que você encontre valores mais adequados para o seu tipo de servo e capacitância do seu capacitor.

```java 
    // Change parameters for one or two capacitors
    // You might change the values depending of your capacitance of your capacitor and servo specification
    public void onTwoCapacitorsClicked(View v) {

        boolean chk =((CheckBox) v).isChecked();
        if (chk ) { //
            MIDDLE_MAX_OFFSET = MAXPOS;
            MIDDLE_CENTER = CENTER;
            FINE_MAX_OFFSET = MAXPOS / 4;
            FINE_CENTER = CENTER / 4;
        } else {    // One Capacitor estimated values. You might need change it
            MIDDLE_MAX_OFFSET = MAXPOS / 4;
            MIDDLE_CENTER = CENTER / 4;
            FINE_MAX_OFFSET = MAXPOS / 8;
            FINE_CENTER = CENTER / 8;
        }

        seekbarMiddleTune.setMax(MIDDLE_MAX_OFFSET);
        seekbarMiddleTune.setProgress(MIDDLE_CENTER);

        seekbarFineTune.setMax(FINE_MAX_OFFSET);
        seekbarFineTune.setProgress(FINE_CENTER);

    }
```    

#### Techos no sketch (Android)

O código a seguir definem os valores máximos (MAX_PULSE) e mínimos (MIN_PULSE) dos servo no programa Arduino. Também define as constantes de sintonia fina (FINE_TUNE), sintonia (NORMAL_TUNE) e banda (LARGE_TUNE) que __não__ são utilizadas no caso do aplicativo Android. O Aplicativo Android já envia o valor exato da posição do servo.

```cpp
// Define pulse width modulation for fine, regular and large tune 
#define FINE_TUNE            5            // short pulse on servo
#define NORMAL_TUNE          15           // regular pulse on servo
#define LARGE_TUNE           50           // large pulse on servo

#define SERVO_PIN            9            // Pin where is connected the servo
#define CAP_LED_PIN         13            // Define the status LED pin of the capacitor

#define MIN_PULSE          800          // Min. pulse of the servo (you need to know abour you servo specification)
#define MAX_PULSE         2200          // Max. pulse of the servo (you need to know abour you servo specification)
```


## Esquema elétrico

Há duas versões do sintonizador de antena. Uma com um capacitor e outra com dois capacitores. A opção com dois capacitores sugere que o capacitor de sintonia fina seja de baixa capacitância. Dessa forma, o processo de sintonia ficará mais fácil e mais preciso. Este [vídeo (clique aqui)](https://youtu.be/w_jXJsiMKIk) ilustra a o sintonizador com dois capacitores.  

### Versão de um capacitor 

O esquema a seguir ilustra a versão do sintonizador de antena configurado para somente um capacitor acoplado a um servo. Esta versão se aplica para antenas no estilo da [Alexloop][alex-loop] ou loop magnética de construção caseira que utiliza capacitores váriáveis com duas ou mais seções.  

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/schematic/minimalist_schematic.png" alt="One capacitor schematic" >


### Versão com dois capacitores 

O esquema a segui apresenta a versão do sintonizador com dois capacitores acoplados em dois servos.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/schematic/minimalist_schematic_tow_capacitors.png" alt="One capacitor schematic" >


### Dispositivo Bluetooth utilizado neste projeto

Os dispositivos HC-05 e HC-06 e HC07 funcionaram com sucesso. Não obtive sucesso com versões Bluetooth no padrão BLE. 

As fotos a seguir ilustram o Bluetooth utilizado neste projeto. 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/BT01.jpg" alt="Android Remote Control"  height="500" width="300" class="center" >

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/BT02.jpg" alt="Android Remote Control"  height="500" width="300" class="center" >



## Protótipo Arduino

### Versão com um Capacitor

A foto a seguir mostra a configuração do  Android, Bluetooth e Servo. É recomendável que você verifique as especificações do servo que você estiver utilizado. É possível que você necessite alterar  algumas definições do servo no sketch.  Tente acompanhar a documentação existente no próprio sketch.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/arduino_prototype.png" alt="Android Remote Control"  height="500" width="300" class="center" >


### Versão com dois capacitores

A foto a seguir apresenta a montágem da versão do protótipo utilizando dois servos que serão acoplados a dois capacitores. 
O sketch [ArduinoTwoCapacitor.ino][arduino-two-capacitor] implementa este versão.    

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/arduino_prototype_two_cap.png" alt="Android Remote Control"  height="500" width="300" class="center" >


## Aplicativo Android

A aplicação para dispositivo android foi desenvolvido em 2014 utilizando os recursos nativos do ambiente de desenvolvimento para Android (conhecido atualmente como Android Studio). A última compilação deste aplicativo foi em 2019 utilizando o [Android Studio 3.3.2.](https://developer.android.com/studio/). O programa está bem documentado e poderá ajudá-lo a entender como foi feita a comunicação de um dispositivo Android com o Arduino via Bluetooth. O módulo principal do aplicativo é o [BluetoothTuner.java][bluetooth-tuner].  Baixe e instale o [Android Studio](https://developer.android.com/studio/) e siga as orientações do ambiente de desenvolvimento Android para abrir, compilar e instalar o aplicativo no seu dispositivo móvel. 

Atualmente há outros ambientes de desenvolvimento para Android mais fácies de utilizar e desenvolver esse tipo de aplicativo. Recomendo fortemente a utilização do [MIT App Inventor](http://appinventor.mit.edu/explore/index-2.html). Veja também outros ambientes de desenvolvimento multiplatafotma como [Apache Cordova](https://cordova.apache.org) e [Ionic](https://ionicframework.com).



### Foto 1

A figura a seguir ilustra a primeira tela do aplicativo. Você precisará parear o Bluetooth previamente em seu dispositivo móvel (celular ou tablet). 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_01.png" alt="Android Remote Control"  height="500" width="300" class="center" >


### Foto 2

Na lista de dispositivos Bluetooth pareados, selecione o Bluetooth conectado ao Arduino (foi usando nos testes o HC-05, HC-06 e HC-07). 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_02.png" alt="Android Remote Control" height="500" width="300" class="center">


### Foto 3

Uma vez conectado o Bluetooth com sucesso, o Aplicativo pode ser utilizado para enviar comandos para o Arduino.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_03.png" alt="Android Remote Control" height="500" width="300" class="center">


## Protocolo de mensagem (Spartphone e Arduino via Bluetooth)

O Arduino recebe as mensagens enviadas pelo Aplicativo Android via conexão [UART](https://paginas.fe.up.pt/~hsm/docencia/comp/uart/). Qualquer programa que utiliza Bluetooth e for capaz de enviar sequencias de caracteres poderá ser utilizado. A tabela a seguir apresenta os comandos (mensagens) e as ações executadas pelo Arduino.   

Para mais informações, veja no sketch Arduino ([ArduinoOneCapacitor.ino][arduino-one-capacitor] ou [ArduinoTwoCapacitors.ino][arduino-two-capacitor]), as constantes definidas FINE_TUNE, NORMAL_TUNE, LARGE_TUNE, MIN_PULSE and MAX_PULSE.  Estas constantes definem a largura de pulso para rodar o servo vendidos. Embora a maioria dos servos encontrados no comércio utilizem especificações similares, é possível que você precise modificar os valores para adequar melhor ao seu servo. O condigo-fonte [BluetoothTuner.java][bluetooth-tuner] (do aplicativo Android) também pode precisar de ajustes dependendo do seu servo. 

### Tabela de comandos recebidos pelo Arduino via Bluetooth

| Character | Description |
| --------- | ----------- |
| + | Sintonia fina no sentido horário. |
| - | Sintonia fina no sentido anti-horário. |
| r | Sintonia média no sentido horário. |
| l | Sintonia média no sentido anti-horário. |
| R | Sintonia larga no sentido horário. |
| L | Sintonia larga no sendito anti-horário. |
| M | Faz com que o servo ou servos girem até a posição máxima. |
| m | Faz com que o servo  ou servos girem até a posição mínima. |
| C or c | Posiciona o servo ou servos no centro. |
| F | Esta mensagem vem composta com número e conduz o servo para uma posição específica. Exemplo: a mensagem F1000# faz com que o servo vá para a posição 1000. O caractere # indica o fim da mensagem para este caso. | 
| T | Como descrito em  anteriormente ('F') este mensagem conduz o servo para ir para uma dada posição. Examplo: a mensagem  T1500# faz com que o servo vá para a posição 1500.|


#### IMPORTANT 

Os arquivos (código-fonte) [ArduinoOneCapacitor.ino][arduino-one-capacitor], [ArduinoTwoCapacitors.ino][arduino-two-capacitor] and [BluetoothTuner.java][bluetooth-tuner] poderão ser úteis para o entendiemento deste protocolo de comunicação.



## Referências

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

[alex-loop](http://www.alexloop.com)
