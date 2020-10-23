
#include <ArduinoJson.h>
int ledpin[3]; //stocke les numeros de pin qui ont été mise en mode output
String inputString = "";
boolean stringComplete = false;
int state=0; //Etat de la led
int cpt=0; //pour se déplacer dans le tableau
int pin=0; //numéro de la pin



StaticJsonDocument<255> doc;

void setup() {
    Serial.begin(9600);

}

void loop() {
    while (Serial.available()) {
        char inChar = (char)Serial.read();  // lecture octet par octet stockage dans un char:
        inputString += inChar;              // ajout dans la chaine provisoire
        if (inChar == '}') {               // si retour)à la ligne
            stringComplete = true;          // la chaine est complète
            break;                          //casse la boucle
        }
    }

    if (stringComplete){

        DeserializationError error = deserializeJson(doc, inputString);


        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }
        pin=doc["pin"]; //je recupere la pin de la led
        if(!isPresent(pin))  //si la pin n'est pas dans le tableau
        {
            pinMode(pin,OUTPUT); //passe la pin en mode output
            ledpin[cpt]=pin; //ajoute la pin dans le tableau
            cpt++; //on passe à la case suivante
        }


        state=doc["state"]; //on récupere l'état
        inputString = "";
    }

    digitalWrite(pin, state);


}


boolean isPresent(int pin)
{
    for(int i=0;i<3;i++)
    {
        if(ledpin[i]==pin)
        {
            return true;
        }
    }
    return false;
}