//#include <EEPROM.h>
// Test: F000 010 000 010 101 010 000 010 000
const int r1 = 5;    // LED connected to digital pin 9
const int r2 = 6;
const int r3 = 7;
const int c1 = 9;
const int c2 = 10;
const int c3 = 11;
const int c4 = 14; // a0
const int c5 = 15; // a1
const int c6 = 16; // a2
const int c7 = 17; // a3
const int c8 = 18; // a4
const int c9 = 19; // a5

const int maxFrames = 50;

boolean debug = false;


boolean cube[maxFrames][3][3][3];
int frames = 0;
int rate = 5;
int animspeed = 20;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.println("<startsetup>Erfolgreich Verbunden<stop>");
}

int cube2int(boolean Cube[3][3][3]){
  boolean array[27];
  int x=0;
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      for(int k=0; k<3; k++){
        array[x]=Cube[i][j][k];
        x++;
      }
    }  
  }
  x=0;
  for(int i=0; i<27; i++){
    if(array[i]){x+=pow(2,i);}
  } 
}

void readCube() {
  int num = frames;
  int waiting=0;
  while (Serial.available() < 27){
    delay(10);
  }
  char neu[27];
  int i=0;
  for(int x=0; x<3; x++){
    for(int y=0; y<3; y++){
      for(int z=0; z<3; z++){
        char ein;
        do {
          ein=Serial.read();
        } while ( ein!='0' && ein!='1');
        cube[num][x][y][z]=(ein=='1');
        i++;
      }
    }
  }
  if(debug){
    Serial.print("<start>\n\r");
    Serial.print("Frame ");
    Serial.println(num+1);
    for(int x=0; x<3; x++){
      for(int y=0; y<3; y++){
        for(int z=0; z<3; z++){
          Serial.print(cube[num][x][y][z]?'1':'0');
          Serial.print(" ");
        }
        Serial.println("\n\r");
      }
      Serial.println("\n\r");
    }
    Serial.println("<stop>");
  }   
  frames++;
  Serial.print("<startok>Übertragung von Cube ");
  Serial.print(num+1);
  Serial.println(" beendet.<stop>");
}

void readConf() {
  rate = Serial.parseInt();
  if (Serial.read() == '#'){
    animspeed = Serial.parseInt();
  } else {
    Serial.println("<startfehler>Fehler: Animationspeed fehlt. (# zur Trennung)<stop>");
  }
  if(debug){
    Serial.print("Refreshrate: ");
    Serial.println(rate);
    Serial.print("Aniamtionsgeschwindigkeit: ");
    Serial.println(animspeed);
  }
  Serial.println("<startok>Übertragung von Conf beendet.<stop>");
}

void getCom(){
  if ( Serial.available() > 0 ) { delay(100); }
  while ( Serial.available() > 0 ) {
    char flag = Serial.read();
    switch (flag) { 
      case 'C': case 'c': readConf();   break; // Conf lesen
      case 'F': case 'f': readCube();   break; // neue Frame
      case 'D': case 'd': // Delete
        frames=0;
        Serial.println("<startok>Cube geleert.<stop>");    
      break; 
      case 'B': case 'b': // toggle deBuging-Modus
        debug=!debug; 
        Serial.print("<startok>Debugging "); 
        Serial.println(debug?"ein.<stop>":"aus.<stop>");
        break; 
      /*case 'E': case 'e':
        for(int i=0; i<frames; i++){
          if(debug){
            Serial.print("<start>");
            Serial.print(cube2int(cube[i]));
            Serial.print(" in ");
            Serial.print(i+1);
            Serial.println(" geschrieben. <stop>");
          }
        }
      break;
      */
      default:
        Serial.print("<startfehler>Kein gütiger Flag: ");
        Serial.print(flag);
        Serial.println("<stop>");
        Serial.println("<startok>Fehler, neues lesen.<stop>");
      break;
    }
  }
}

int toanalog(char ein){ return ein?255:0; }

void showCube(int num) {
 // Row 1
    analogWrite(c1, toanalog(cube[num][0][0][0]));
    analogWrite(c2, toanalog(cube[num][0][0][1]));
    analogWrite(c3, toanalog(cube[num][0][0][2]));
    analogWrite(c4, toanalog(cube[num][0][1][0]));
    analogWrite(c5, toanalog(cube[num][0][1][1]));
    analogWrite(c6, toanalog(cube[num][0][1][2]));
    analogWrite(c7, toanalog(cube[num][0][2][0]));
    analogWrite(c8, toanalog(cube[num][0][2][1]));
    analogWrite(c9, toanalog(cube[num][0][2][2]));
  analogWrite(r1, 255);
  delay(rate);
  analogWrite(r1, 0);
  // Row 2
    analogWrite(c1, toanalog(cube[num][1][0][0]));
    analogWrite(c2, toanalog(cube[num][1][0][1]));
    analogWrite(c3, toanalog(cube[num][1][0][2]));
    analogWrite(c4, toanalog(cube[num][1][1][0]));
    analogWrite(c5, toanalog(cube[num][1][1][1]));
    analogWrite(c6, toanalog(cube[num][1][1][2]));
    analogWrite(c7, toanalog(cube[num][1][2][0]));
    analogWrite(c8, toanalog(cube[num][1][2][1]));
    analogWrite(c9, toanalog(cube[num][1][2][2]));
  analogWrite(r2, 255);
  delay(rate);
  analogWrite(r2, 0);
  // Row 3
    analogWrite(c1, toanalog(cube[num][2][0][0]));
    analogWrite(c2, toanalog(cube[num][2][0][1]));
    analogWrite(c3, toanalog(cube[num][2][0][2]));
    analogWrite(c4, toanalog(cube[num][2][1][0]));
    analogWrite(c5, toanalog(cube[num][2][1][1]));
    analogWrite(c6, toanalog(cube[num][2][1][2]));
    analogWrite(c7, toanalog(cube[num][2][2][0]));
    analogWrite(c8, toanalog(cube[num][2][2][1]));
    analogWrite(c9, toanalog(cube[num][2][2][2]));
  analogWrite(r3, 255);
  delay(rate);
  analogWrite(r3, 0);  
}  


void loop()  { 
  getCom(); 
  for(int i=0; i<frames; i++){
    for(int j=0; j<animspeed; j++){
      showCube(i);
    } 
  }
}







