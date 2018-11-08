/*
 Autor: Gilson de Freitas - Rondonópolis-MT - 66-9-9998-6062 
 Cliente: Alan - Rio de Janeiro - 22-9-9901-9517
 Data: 08/11/2018
 Versão do Arduíno: 1.8.5
 
 Descrição: Uma botoeira para acionar um motor de portão eletrônico
 Botoeria 1 (pino2): Ao ser pressionada, irá controlar o relé (pino8)                     
                     -> Ligado 1 vez por 2 segundos,
                     -> Desligado 1 vez por 30 segundos
                     -> Ligado 1 vez por 2 segundos 
                     Obs: Não recomeçar outro processo, caso pressionar
                          novamente o botão durante o processo já iniciado
*/

byte pinBt2 = 2;// pino do botão 2;
byte pinR8  = 8;// pino que acionarão ou não o relés;

byte lnSeg    = 0; //linha de tempos dos relés
byte lnOnOf   = 1; //linha se irá ligar ou desligar

long tempoRele;    //variavel de auxílio para tempo do relé;

// inicio relé pino8
byte releT8colunas = 4;      //qtd colunas
String releT8[2] [4] = {
   {"2","30","2","1"} //lnSeg, contendo o número de tempos do releT8colunas ;
  ,{"L", "D","L","D"} //lnOnOf, contendo o número de releT8colunas valores. L:liga, D:desliga
  };  
//fim relé pino8


void setup() {
  Serial.begin(9600); 

  pinMode(pinBt2,INPUT_PULLUP);// Define pinBt2 como entrada;

  pinMode(pinR8,OUTPUT);       // Habilita o pino 8 como saída;
  digitalWrite(pinR8,1);       // 0:Liga o relé, 1:Desliga o relé do pino 8;

  Serial.println("Iniciado");
}

void loop() {
  //inicio Botoeira 1(pino2) - Relé1 (pino8)
  if (digitalRead(pinBt2) == LOW) {
    Serial.println("botao 1 pressionado");
    acionaRele8();
  }
}

void acionaRele8(){
  for (int coluna = 0; coluna <= releT8colunas; coluna++){
    // pega o tempo do array releT8[] [] * 1000 para executar os segundos
    tempoRele = releT8[lnSeg][coluna].toInt() * 1000;  
    
    if (releT8[lnOnOf][coluna] == "L"){
      digitalWrite(pinR8,0);//liga o relé Normalmente Aberto. 0:fecha o contato do rele, 1: abre o contato
    }else{
      digitalWrite(pinR8,1);//desliga o relé Normalmente Aberto. 0:fecha o contato do rele, 1: abre o contato
    }
    Serial.print("rele8: ");Serial.println(tempoRele);
    delay(tempoRele);    
  }
}
