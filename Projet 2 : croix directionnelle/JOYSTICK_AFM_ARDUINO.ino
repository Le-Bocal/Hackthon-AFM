/**
 * Gestion du Joystick comme un clavier
 * utilise les flèches directionnelles
 * 
 * A améliorer :
 * - bagottement lors du relachemet du joystick qui peut générer des touches inverses
 * 
 */



#include <Keyboard.h>

#define FIL_VERT    A3
#define FIL_BLEU    A2
#define FIL_JAUNE   A1
#define FIL_BLANC   A0

#define TOUCHE_HAUT   218
#define TOUCHE_BAS    217
#define TOUCHE_GAUCHE 216
#define TOUCHE_DROITE 215

#define LED1          17

#define SEUIL_MIN_REPOS     370
#define SEUIL_MAX_REPOS     620

#define SERIAL_KEYBOARD 0

boolean WITH_KEYBOARD = true;


int patteVerte_DiagHG;
int patteBleue_DiagHD;
int patteJaune_HB;
int patteBlanche_GD;


typedef enum
{
  Repos = 0,
  HautDroite,
  BasGauche
} e_direction_t;

typedef enum
{
  position_repos= 0,
  position_haut,
  position_bas,
  position_gauche,
  position_droite,
  position_haut_gauche,
  position_haut_droite,
  position_bas_gauche,
  position_bas_droite
} e_valeurDirection_t;

e_valeurDirection_t valeurDirection, valeurDirection_prec;
e_direction_t dirVerte_DiagHG,dirBleue_DiagHD,dirJaune_HB,dirBlanche_GD;


e_direction_t determinerDirection(int ValeurAnalogique);


void setup() {
  // put your setup code here, to run once:
  //Keyboard.begin();
  //Serial.begin(9600);
  
  valeurDirection_prec = position_repos;
  valeurDirection = position_repos;
  //if(WITH_KEYBOARD){
    Keyboard.begin();
  //}
#ifdef SERIAL_KEYBOARD
  Keyboard.println("Fin setup");
#endif
  
  }



void loop() {

    // lecture port analogique
    patteVerte_DiagHG = analogRead(FIL_VERT);
    patteBleue_DiagHD = analogRead(FIL_BLEU);
    patteJaune_HB = analogRead(FIL_JAUNE);
    patteBlanche_GD = analogRead(FIL_BLANC);
             
//    Serial.print("patteVerte:");
//    Serial.println(patteVerte);
//    Serial.print("patteBleue:");
//    Serial.println(patteBleue);
//    Serial.print("patteJaune:");
//    Serial.println(patteJaune);
//    Serial.print("patteBlanche:");
//    Serial.println(patteBlanche);

    dirVerte_DiagHG = determinerDirection(patteVerte_DiagHG);
    dirBleue_DiagHD = determinerDirection(patteBleue_DiagHD);
    dirJaune_HB = determinerDirection(patteJaune_HB);
    dirBlanche_GD = determinerDirection(patteBlanche_GD);

//  position_repos= 0,
//  position_haut,
//  position_bas,
//  position_gauche,
//  position_droite,
//  position_haut_gauche,
//  position_haut_droite,
//  position_bas_gauche,
//  position_bas_droite

//    dirVerte_DiagHG

//  Repos = 0,
//  HautDroite,
//  BasGauche


//    valeurDirection_prec = position_repos;
    valeurDirection = position_repos;
   
    if(dirVerte_DiagHG != Repos)
    {
      if(dirVerte_DiagHG == HautDroite)
      {
        valeurDirection = position_haut_gauche;
      }
      else //Bas droite
      {
        valeurDirection = position_bas_droite;
      }
    }
    else if(dirBleue_DiagHD != Repos)
    {
      if(dirBleue_DiagHD == HautDroite)
      {
        valeurDirection = position_haut_droite;
      }
      else
      {
        valeurDirection = position_bas_gauche;
      }   
    }
    else if(dirJaune_HB != Repos)
    {
      if(dirJaune_HB == HautDroite)
      {
        valeurDirection = position_haut;
      }
      else
      {
        valeurDirection = position_bas;
      }   
    }
    else if(dirBlanche_GD != Repos)
    {
      if(dirBlanche_GD == HautDroite)
      {
        valeurDirection = position_droite;
      }
      else
      {
        valeurDirection = position_gauche;
      }
    }

    if(valeurDirection_prec != valeurDirection){
      // nous avons une différence
      appuieTouche(valeurDirection);
      relacheTouche(valeurDirection_prec,valeurDirection);

      valeurDirection_prec = valeurDirection;
    }
    
    delay(1);
}

e_direction_t determinerDirection(int ValeurAnalogique)
{
  e_direction_t e_direction = Repos;
  
  if(ValeurAnalogique < SEUIL_MIN_REPOS)
  {
    e_direction = HautDroite;  
  }
  else if(ValeurAnalogique > SEUIL_MAX_REPOS)
  {
    e_direction = BasGauche;  
  }

  return e_direction;
}

void appuieTouche(e_valeurDirection_t i_e_touche)
{
if(SERIAL_KEYBOARD==1){  
    Keyboard.print("press ");
   Keyboard.println(getLabelTouche(i_e_touche,NULL));
}
  switch(i_e_touche)
  {
    case position_haut:
    {
      if(WITH_KEYBOARD){
        Keyboard.press(TOUCHE_HAUT);
      }
    }
    break;

    case position_bas:
    {
      if(WITH_KEYBOARD){
        Keyboard.press(TOUCHE_BAS);
      }
    }
    break;

      case position_gauche:
    {
      if(WITH_KEYBOARD){
        Keyboard.press(TOUCHE_GAUCHE);
      }
    }
    break;

    case position_droite:
    {
      if(WITH_KEYBOARD){
        Keyboard.press(TOUCHE_DROITE);
      }
    }
    break;

    case position_haut_gauche:
    {
      if(WITH_KEYBOARD){
        Keyboard.press(TOUCHE_HAUT);
        Keyboard.press(TOUCHE_GAUCHE);
      }
    }
    break;

    case position_haut_droite:
    {
      if(WITH_KEYBOARD){
        Keyboard.press(TOUCHE_HAUT);
        Keyboard.press(TOUCHE_DROITE);
      }
    }
    break;

    case position_bas_gauche:
    {
      if(WITH_KEYBOARD){
        Keyboard.press(TOUCHE_BAS);
        Keyboard.press(TOUCHE_GAUCHE);
      }
    }
    break;

    case position_bas_droite:
    {
      if(WITH_KEYBOARD){
        Keyboard.press(TOUCHE_BAS);
        Keyboard.press(TOUCHE_DROITE);
      }
    }
    break;
  }
}


void relacheTouche(e_valeurDirection_t i_e_touche,e_valeurDirection_t i_e_toucheAppuie )
{
  if(SERIAL_KEYBOARD==1){  
    Keyboard.print("release ");
   Keyboard.println(getLabelTouche(i_e_touche,i_e_toucheAppuie));
}

  switch(i_e_touche)
  {
    case position_haut:
    {
      if(WITH_KEYBOARD){
        Keyboard.release(TOUCHE_HAUT);
      }
    }
    break;

    case position_bas:
    {
      if(WITH_KEYBOARD){
        Keyboard.release(TOUCHE_BAS);
      }
    }
    break;

      case position_gauche:
    {
      if(WITH_KEYBOARD){
        Keyboard.release(TOUCHE_GAUCHE);
      }
    }
    break;

    case position_droite:
    {
      if(WITH_KEYBOARD){
        Keyboard.release(TOUCHE_DROITE);
      }
    }
    break;

    case position_haut_gauche:
    {
      if(WITH_KEYBOARD){
        if(i_e_toucheAppuie != position_haut){
          Keyboard.release(TOUCHE_HAUT);
        }
        if(i_e_toucheAppuie != position_gauche){
          Keyboard.release(TOUCHE_GAUCHE);
        }
      }
    }
    break;

    case position_haut_droite:
    {
      if(WITH_KEYBOARD){
        if(i_e_toucheAppuie != position_haut){
          Keyboard.release(TOUCHE_HAUT);
        }
        if(i_e_toucheAppuie != position_droite){
          Keyboard.release(TOUCHE_DROITE);
        }
      }
    }
    break;

    case position_bas_gauche:
    {
      if(WITH_KEYBOARD){
        if(i_e_toucheAppuie != position_bas){
          Keyboard.release(TOUCHE_BAS);
        }
        if(i_e_toucheAppuie != position_gauche){
          Keyboard.release(TOUCHE_GAUCHE);
        }
      }
    }
    break;

    case position_bas_droite:
    {
      if(WITH_KEYBOARD){
        if(i_e_toucheAppuie != position_bas){
          Keyboard.release(TOUCHE_BAS);
        }
        if(i_e_toucheAppuie != position_droite){
          Keyboard.release(TOUCHE_DROITE);
        }
      }
    }
    break;
  }
}

String getLabelTouche(e_valeurDirection_t i_e_touche,e_valeurDirection_t i_e_toucheAppuie){
  String rValue="";
  switch(i_e_touche)
  {
    case position_repos:
    {
      if(i_e_toucheAppuie!=NULL){
        rValue="REPOS";
      }
    }
    break;
    case position_haut:
    {
      rValue="TOUCHE_HAUT";
    }
    break;

    case position_bas:
    {
      rValue="TOUCHE_BAS";
    }
    break;

    case position_gauche:
    {
     rValue="TOUCHE_GAUCHE";
    }
    break;

    case position_droite:
    {
      rValue="TOUCHE_DROITE";
    }
    break;

    case position_haut_gauche:
    {
      if(i_e_toucheAppuie==NULL){
        rValue="TOUCHE_HAUT TOUCHE_GAUCHE";
      }else if(i_e_toucheAppuie == position_haut){
        rValue=" PAS TOUCHE_HAUT / TOUCHE_GAUCHE";
      }else if(i_e_toucheAppuie == position_gauche){
         rValue=" TOUCHE_HAUT / PAS TOUCHE_GAUCHE";
      }else{
        rValue="TOUCHE_HAUT TOUCHE_GAUCHE";
      }
      
    }
    break;

    case position_haut_droite:
    {
      if(i_e_toucheAppuie==NULL){
        rValue="TOUCHE_HAUT TOUCHE_DROITE";
      }else if(i_e_toucheAppuie == position_haut){
        rValue=" PAS TOUCHE_HAUT / TOUCHE_DROITE";
      }else if(i_e_toucheAppuie == position_droite){
         rValue=" TOUCHE_HAUT / PAS TOUCHE_DROITE";
      }else{
        rValue="TOUCHE_HAUT TOUCHE_DROITE";
      }
    }
    break;

    case position_bas_gauche:
    {
      if(i_e_toucheAppuie==NULL){
        rValue="TOUCHE_BAS TOUCHE_GAUCHE";
      }else if(i_e_toucheAppuie == position_bas){
        rValue=" PAS TOUCHE_BAS / TOUCHE_GAUCHE";
      }else if(i_e_toucheAppuie == position_gauche){
         rValue=" TOUCHE_BAS / PAS TOUCHE_GAUCHE";
      }else{
        rValue="TOUCHE_BAS TOUCHE_GAUCHE";
      }
    }
    break;

    case position_bas_droite:
    {
      if(i_e_toucheAppuie==NULL){
        rValue="TOUCHE_BAS TOUCHE_DROITE";
      }else if(i_e_toucheAppuie == position_bas){
        rValue=" PAS TOUCHE_BAS / TOUCHE_DROITE";
      }else if(i_e_toucheAppuie == position_droite){
         rValue=" TOUCHE_BAS / PAS TOUCHE_DROITE";
      }else{
        rValue="TOUCHE_BAS TOUCHE_DROITE";
      }
    }
    break;
  }
  return rValue;
}
