# Antena Loop Magnética controlada por SmartPhone Android e Arduino 


# Sumário

1. [Introdução](/Documentation#introdução)
2. [Estrutura de pastas e arquivos](/Documentation#estrutura-de-pastas-e-arquivos)
3. [Como baixar os arquivos deste projeto (Download)](/Documentation#como-baixar-os-arquivos-deste-projeto-download)
4. [Trechos de código sensíveis ao tipo de servo utilizado](/Documentation#trechos-de-código-sens%C3%ADveis-ao-tipo-de-servo-utilizado)
5. [Esquema](/Documentation#esquema-elétrico)
   1. [Com um capacitor](/Documentation#versão-de-um-capacitor)
   2. [Com dois capacitores](/Documentation#versão-com-dois-capacitores)
6. [Dispositivo Bluetooth utilizado neste projeto](/Documentation#dispositivo-bluetooth-utilizado-neste-projeto)
8. [Protótipo Arduino](/Documentation#protótipo-arduino)
   1. [Bluetooth Clássico x BLE](/Documentation#bluetooth-clássico-x-ble)
   2. [Versão com um capacitor (Bluetooth Clássico)](/Documentation#versão-com-um-capacitor)
   3. [Versão com dois capacitores (Bluetooth Clássico)](/Documentation#versão-com-dois-capacitores-1)
7. [Aplicativo Android](/Documentation#aplicativo-android) 
8.  [Código-fonte](/Documentation#código-fonte) 
9. [Protocolo de mensagem (Spartphone e Arduino via Bluetooth)](/Documentation#protocolo-de-mensagem-spartphone-e-arduino-via-bluetooth)
10. [Fotos](/Documentation#fotos)
11. [Videos](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner#videos-about-this-project)


## Introdução 

Este projeto é uma versão básica de um Sintonizador de Antenas implementado com Arduino e controlado por um dispositivo móvel baseado em Android. Com este projeto, será possível controlar remotamente, por exemplo, uma Antena Loop Magnética no estilo da [Alexloop](http://www.alexloop.com/index.html) ou uma de construção caseira, via Bluetooth, a partir do seu dispositivo móvel (celular ou tablet) baseado em Android. Há duas opções preferencialmente sugeridas neste documento: uma utilizando o sintonizador de antenas com um capacitor e outra com dois capacitores. Essas duas versões utilizam o Bluetooth Clássico (HC-05, HC-07 etc). __Há também uma versão experimental do sintonizador de antenas utilizando um Bluetooth Low Energy (BLE). No entanto, até o presente momento o aplicativo para celular ainda não foi desenvolvido ou adaptado para esta versão com o BLE__. Assista aos vídeos referenciados no final desta página. Acredito que este projeto possa oferecer os elementos básicos para projetos mais robustos envolvendo as tecnologias utilizadas aqui. 

Fortaleza, 3 de abril de 2019.
Por PU2CLR,
Ricardo Lima Caratti.


## Estrutura de pastas e arquivos

Este trabalho está organizado em pastas. Cada pasta possui o conteúdo descrito a seguir: 

- A pasta [Box_3D_Printer](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Box_3D_Printer) contem o projeto de uma caixa construída em uma impressora 3D especialmente para a [Alexloop][alex-loop] ou similar. [Clique aqui](https://youtu.be/OKky8gmOWz8) para assistir a um vídeo sobre este projeto;
- A pasta [images](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/images) contém fotos sobre este projeto;
- A pasta [schematic](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/schematic) contém dois esquemas construídos por meio do software  [fritzing](http://fritzing.org/home/), um programa livre para construção de esquemas elétricos. Há duas versões do projeto: uma utilizando um Servo para trabalhar somente com um capacitor; e outra utilizando dois servos para trabalhar com um capacitor principal e outro de sintonia fina;
- A pasta [sources](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/sources) contém os códigos-fonte do Aplicativo para SmartPhone para Android,  e dois sketchs (programas para Arduino).  


## Como baixar os arquivos deste projeto (Download)

A estrutura de pastas e arquivos descrita no item anterior é apresentada neste repositório de projetos conforme ilustra a figura a seguir. Clique [aqui](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner.git) para entrar na página  e em seguida clique no botão verde, à direita,  identificado por "Clone or Download". 

[![Página para Download do projeto](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/figura_download.png)](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner.git/)



## Esquema elétrico

Há duas versões do sintonizador de antena. Uma com um capacitor e outra com dois capacitores. A opção com dois capacitores sugere que o capacitor de sintonia fina seja de baixa capacitância. Dessa forma, o processo de sintonia ficará mais fácil e mais preciso. [Clique aqui](https://youtu.be/w_jXJsiMKIk) para assistir a um vídeo que ilustra o sintonizador com dois capacitores.  

### Versão de um capacitor 

O esquema a seguir ilustra a versão do sintonizador de antena configurado para somente um capacitor acoplado a um servo. Esta versão se aplica para antenas no estilo da [Alexloop][alex-loop] ou loop magnética de construção caseira que utiliza capacitores variáveis com duas ou mais seções.  

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/schematic/minimalist_schematic.png" alt="One capacitor schematic" >


### Versão com dois capacitores 

O esquema a segui apresenta a versão do sintonizador com dois capacitores acoplados em dois servos.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/schematic/minimalist_schematic_tow_capacitors.png" alt="One capacitor schematic" >


### Dispositivo Bluetooth utilizado neste projeto

Os dispositivos HC-05 e HC-06 e HC07 funcionaram com sucesso. A versão utilizando um Bluetooth BLE pode ser vista clicando [aqui](/sources/ArduinoBLE). As figuras a seguir apresentam um bluetooth clássico (HC-05). 


#### Bluetooth Clássico HC-05 - Foto 1
<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/BT01.jpg" alt="Android Remote Control"  height="500" width="300" class="center" >

#### Bluetooth Clássico HC-05 - Foto 2

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/BT02.jpg" alt="Android Remote Control"  height="500" width="300" class="center" >



## Protótipo Arduino

Este projeto apresenta basicamente três opções para a construção de um Sintonizador de Antenas Loop Magnética controlado por Arduino e  Smartphone. A primeira opção propõe a utilização de um capacitor acoplado a um Servo conectado ao Arduino que, por sua vez, interage com um dispositivo Bluetooth clássico (HC-05, HC-07 ou similar). A segunda opção propõe a utilização de dois capacitores, um para sintonia normal e outro para sintonia fina, que operam de forma similar à versão anterior usando um Bluetooth clássico. A terceira opção utiliza praticamente a mesma configuração da primeira opção, exceto que no lugar do Bluetooth Clássico, é utilizado um BLE (HM10 / HMSoft). Os códigos para cada opção descrita anteriormente estão disponíveis na pasta [sources deste repositório](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/sources).

As duas primeiras opção funcionam perfeitamente em dispositivos móveis Android (Celular ou Tablet) por meio do [Aplicativo Android](/Documentation#aplicativo-android) desenvolvido para este projeto. Isto é, com o mesmo Aplicativo Android, é possível controlar um sintonizador de antena loop magnética com um ou dois capacitores usando o __Bluetooth Clássico__.

A terceira opção deste projeto implementa a comunicação do Arduino com BLE. No entanto, até o momento em que escrevo estas linhas, ainda não desenvolvi um programa específico para controlar remotamente o sintonizador de antenas via BLE. É possível porém, utilizar um Aplicativo qualquer de comunicação serial para este fim. Clique [aqui](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/sources/ArduinoBLE) para mais detalhes sobre como controlar o sintonizador de antenas loop magnética usando BLE. 


### Bluetooth Clássico x BLE

Inicialmente, o sintonizador remoto para antena loop magnética usando Smartphone via Bluetooth, foi projetado para funcionar com  dispositivos Bluetooth clássicos do tipo HC-05, HC-7 etc. No entanto, nos últimos 5 anos, a oferta de dispositivos Bluetooth com a especificação BLE (Bluetooth Low Energy) para plataformas de desenvolvimento como Arduino aumentou sobremaneira. Além disso, o custo destes dispositivos Bluetooth ficou bastante atrativo. Seguem algumas considerações e experiências sobre os dois tipos de Bluetooth observadas durante o desenvolvimento deste projeto:

- O Bluetooth Clássico oferece uma documentação mais rica e com mais exemplos e experiências de uso em projetos com Arduino
- Os dispositivos Bluetooth clássicos ainda são mais baratos e mais fáceis de serem adquiridos; 
- BLE permite conexão com dispositivos móveis da linha Apple. Com isso, é possível desenvolver ou obter um aplicativo de terceiro para iOS que possa ser utilizado com o sintonizador de antenas proposto neste projeto;
- Ainda que seja possível utilizar este projeto em ambiente iOS via BLE, o Bluetooth não aparece na lista padrão de dispositivos pareados do sistema da Apple. Ou seja, o BLE só é visualizado durante a execução do Aplicativo utilizado como controle remoto. Este comportamento pode confundir o usuário em sua primeira análise;
- Em dispositivos do tipo Android, o BLE funciona quase da mesma forma que o Bluetooth Clássico. Isto é, não há diferença visível para o usuário final entre o modelo clássico e o BLE. 
- No que tange à codificação de programas usando Bluetooth Clássico e BLE, tanto programa Arduino (sketch) como o programa para dispositivos móveis Android e iOS utilizam abordagens diferentes. Isto é, uma vez selecionado o tipo de Bluetooth que será utilizado, o código desenvolvido deve utilizar as blbliotecas e APIs (Application Program Interface) contruídas para o Bluetooth escolhido.   


## Propostas para construção do sintonizador de Antenas Controlado por Arduino e Smartphone


### Versão com um Capacitor

A foto a seguir mostra a configuração do  Android, Bluetooth __Clássico (HC-05, HC-07 etc)__ e Servo. É recomendável que você verifique as especificações do servo que você estiver utilizado. É possível que você necessite alterar  algumas definições do servo no sketch.  Tente acompanhar a documentação existente no próprio sketch.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/arduino_prototype.png" alt="Android Remote Control"  class="center" >


### Versão com dois capacitores

A foto a seguir apresenta a montagem da versão do protótipo utilizando dois servos que serão acoplados a dois capacitores. 
O sketch [ArduinoTwoCapacitor.ino][arduino-two-capacitor] implementa este versão.    

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/arduino_prototype_two_cap.png" alt="Android Remote Control"  class="center" >



## Aplicativo Android

A aplicação para dispositivo Android foi desenvolvido em 2014 utilizando os recursos nativos do ambiente de desenvolvimento para Android (conhecido atualmente como Android Studio). A última compilação deste aplicativo foi em 2019 utilizando o [Android Studio 3.3.2.](https://developer.android.com/studio/). O programa está bem documentado e poderá ajudá-lo a entender como foi feita a comunicação de um dispositivo Android com o Arduino via Bluetooth. O módulo principal do aplicativo é o [BluetoothTuner.java][bluetooth-tuner].  Baixe e instale o [Android Studio](https://developer.android.com/studio/) e siga as orientações do ambiente de desenvolvimento Android para abrir, compilar e instalar o aplicativo no seu dispositivo móvel. 

Atualmente há outros ambientes de desenvolvimento para Android mais fácies de utilizar e desenvolver esse tipo de aplicativo. Recomendo fortemente a utilização do [MIT App Inventor](http://appinventor.mit.edu/explore/index-2.html). Veja também outros ambientes de desenvolvimento multiplataforma como [Apache Cordova](https://cordova.apache.org) e [Ionic](https://ionicframework.com).




### Foto 1

A figura a seguir ilustra a primeira tela do aplicativo. Você precisará parear o Bluetooth previamente em seu dispositivo móvel (celular ou tablet). 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_01.png" alt="Android Remote Control"  height="500" width="300" class="center" >


### Foto 2

Na lista de dispositivos Bluetooth pareados, selecione o Bluetooth conectado ao Arduino (foi usando nos testes o HC-05, HC-06 e HC-07). 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_02.png" alt="Android Remote Control" height="500" width="300" class="center">


### Foto 3

Uma vez conectado o Bluetooth com sucesso, o Aplicativo pode ser utilizado para enviar comandos para o Arduino.

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/AndroidApp_Remote_COntrol_03.png" alt="Android Remote Control" height="500" width="300" class="center">


### Foto 4 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/photo05.jpg" alt="Android Remote Control" height="500" width="300" class="center">


## Código-fonte

Todos os fontes utilizados neste projeto estão disponíveis na [pasta 'sources'](https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/tree/master/Sources).  __Durante o upload do sketch para o Arduino, você deve desconectar o Bluetooth do arduino__. É recomendável acompanhar a documentação escrita no programa.

Dependendo da configuração que você optar, um ou dois capacitores, bem como as especificações técnicas do servo que você utiliza, é possível que você precise modificar alguns parâmetros no sketch do Arduino e também no Aplicativo Android. 
Veja a documentação nos fontes [ArduinoOneCapacitor.ino][arduino-one-capacitor], [ArduinoTwoCapacitors.ino][arduino-two-capacitor] e [BluetoothTuner.java][bluetooth-tuner]. 


### Trechos de código sensíveis ao tipo de servo utilizado

Os trechos de código a seguir ilustram a configuração no Aplicativo Android  (em Java) e Arduino (em C/C++) que permitem um ajuste fino do servo e capacitor utilizado por você. Caso não conheça os valores especificados pelo seu servo, inicie seus testes sem fazer alteração nos códigos

#### Trechos no Aplicativo Android (BluetoothTuner.java)

É nenessário um conhecimento mínimo em desenvolvimento de aplictivos para Android para elaborar algumas mudanças no Aplicativo. Caso você não se sinta seguro para fazer isso, é melhor iniciar os experimentos sem fazer alteração alguma. 

O código a seguir define os limites máximo (MAXPOS) e mínimo (OFFSET), bem como a posição central (CENTER) do servo no Aplicativo Android ([BluetoothTuner.java][bluetooth-tuner]). Os componentes de interface do aplicativo __SeekBar__ (barras Band, Tune e Fine Tune) utilizam estes valores como referência para enviar valores entre os limites (MAXPOS e OFFSET) para o servo na proporção que o usuário do aplicativo arrasta o dedo sobre os componentes de interface. 

```java
    // You might change this setup depending of your servo specification
    public int OFFSET = 800;   // Min. Pisition  (0 degree)
    public int MAXPOS = 2200;  // Max. position  (Max. degrre)
    public int CENTER = (MAXPOS - OFFSET)/2 + OFFSET /2;   // Center is CENTER + OFFSET
```

O código a seguir configura a sintonia fina (Tune e Fine Tune) e usa como referência as constantes descritas anteriormente. Note também que, dependendo da configuração selecionada (um ou dois capacitores), os valores para componentes de sintonia fina mudam. É possível que você encontre valores mais adequados para o seu tipo de servo e capacitância do seu capacitor.

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

#### Trechos no sketch (Android)

O código a seguir definem os valores máximos (MAX_PULSE) e mínimos (MIN_PULSE) dos servos no programa Arduino. Também define as constantes de sintonia fina (FINE_TUNE), sintonia (NORMAL_TUNE) e banda (LARGE_TUNE) que __não__ são utilizadas no caso do aplicativo Android. O Aplicativo Android já envia o valor exato da posição do servo.

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



## Protocolo de mensagem (Spartphone e Arduino via Bluetooth)

O Arduino recebe as mensagens enviadas pelo Aplicativo Android via conexão [UART](https://paginas.fe.up.pt/~hsm/docencia/comp/uart/). Qualquer programa que utiliza Bluetooth e for capaz de enviar sequências de caracteres poderá ser utilizado. A tabela a seguir apresenta os comandos (mensagens) e as ações executadas pelo Arduino.   

Para mais informações, veja no sketch Arduino ([ArduinoOneCapacitor.ino][arduino-one-capacitor] ou [ArduinoTwoCapacitors.ino][arduino-two-capacitor]), as constantes definidas FINE_TUNE, NORMAL_TUNE, LARGE_TUNE, MIN_PULSE and MAX_PULSE.  Estas constantes definem a largura de pulso para rodar o servo vendidos. Embora a maioria dos servos encontrados no comércio utilizem especificações similares, é possível que você precise modificar os valores para adequar melhor ao seu servo. O condigo-fonte [BluetoothTuner.java][bluetooth-tuner] (do aplicativo Android) também pode precisar de ajustes dependendo do seu servo. 

### Tabela de comandos recebidos pelo Arduino via Bluetooth

| Mensagem | Descrição |
| --------- | ----------- |
| + | Sintonia fina no sentido horário. |
| - | Sintonia fina no sentido anti-horário. |
| r | Sintonia média no sentido horário. |
| l | Sintonia média no sentido anti-horário. |
| R | Sintonia larga no sentido horário. |
| L | Sintonia larga no sentido anti-horário. |
| M | Faz com que o servo ou servos girem até a posição máxima. |
| m | Faz com que o servo  ou servos girem até a posição mínima. |
| C or c | Posiciona o servo ou servos no centro. |
| F | Esta mensagem vem composta com número e conduz o servo para uma posição específica. Exemplo: a mensagem F1000# faz com que o servo vá para a posição 1000. O caractere # indica o fim da mensagem para este caso. | 
| T | Como descrito em  anteriormente ('F') este mensagem conduz o servo para ir para uma dada posição. Exemplo: a mensagem  T1500# faz com que o servo vá para a posição 1500.|


#### IMPORTANTE 

Os arquivos (código-fonte) [ArduinoOneCapacitor.ino][arduino-one-capacitor], [ArduinoTwoCapacitors.ino][arduino-two-capacitor] and [BluetoothTuner.java][bluetooth-tuner] poderão ser úteis para o entendimento deste protocolo de comunicação.


# Fotos

### Foto 5 

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/photo05.jpg" alt="Android Remote Control"  class="center">


### Foto 6

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/photo09.jpg" alt="Android Remote Control" class="center">


### Foto 7

<img src="https://github.com/pu2clr/Magnetic_Loop_Antenna_Tuner/blob/master/images/photo10.jpg" alt="Android Remote Control"  class="center">



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

[alex-loop]: <http://www.alexloop.com>
