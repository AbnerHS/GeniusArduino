int btnVm = A0, btnAm = A1, btnVd = A2;
int ledVm = 7, ledAm = 6, ledVd = 5, buzzer = 3;
int sequencia[20], apertados[20];
int mapa[3] = {ledVm, ledAm, ledVd};
int nivel = 0, n = 0;
bool pronto = true;
long int sorteado;
void setup()
{
  pinMode(btnVm, INPUT);
  pinMode(btnAm, INPUT);
  pinMode(btnVd, INPUT);
  pinMode(ledVm, OUTPUT);
  pinMode(ledAm, OUTPUT);
  pinMode(ledVd, OUTPUT);
  pinMode(buzzer, OUTPUT);
  piscar();
  delay(1000);
  randomSeed(analogRead(A5));
  Serial.begin(9600);
}

void piscar(){
  for(int i = 0; i < 3; i++){
    digitalWrite(mapa[i], HIGH);
  }
  delay(300);
  for(int i = 0; i < 3; i++){
    digitalWrite(mapa[i], LOW);
    }
}

void acenderLeds(){
  int i;
  for(i = 0; i <= nivel; i++){
    digitalWrite(mapa[sequencia[i]], HIGH);
    tone(buzzer, (sequencia[i]+1)*100);
    delay(500);
    digitalWrite(mapa[sequencia[i]], LOW);
    noTone(buzzer);
    delay(500);
  }
}

int botaoApertado(){
  if(digitalRead(btnVm)){
    return 0;
  } else if(digitalRead(btnAm)){
    return 1;
  } else if(digitalRead(btnVd)){
    return 2;
  } else {
    return 3;
  }
}

bool verificar(int n){
  Serial.println(n);
  bool t = true;
  for(int i = 0; i <= n;i++){
    if(apertados[i] != sequencia[i]){
        t = false;
        break;
    }
  }  
  return t;
}

void resetar(){
    nivel = 0;
    n = 0;
    pronto = true;
    delay(1000);
}

void loop()
{
  if(pronto){
      //sorteia
      sorteado = random(0,3);
      sequencia[nivel] = sorteado;
      pronto = false;
  
      //mostra a sequencia
      acenderLeds();
      
    } else {
      //verifica sequencia
    int escolhido = botaoApertado();
    if(escolhido != 3){
        digitalWrite(mapa[escolhido], HIGH);
        tone(buzzer, (escolhido+1)*100);
        delay(500);
        digitalWrite(mapa[escolhido], LOW);
        noTone(buzzer);
        apertados[n] = escolhido;
        if(verificar(n)){
          n++;
        } else {
          delay(200);
          tone(buzzer, 80);
          delay(200);
          noTone(buzzer);
          piscar();
          resetar();
        }
        if(n == nivel+1){
          pronto = true;
          nivel++;
          n = 0;
          delay(1000);
        }
      }
    }
}
