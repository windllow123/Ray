#include <iostream>
#include "menu.h"
#include "ConsoleUtils.h"
#include <string>
#include <sstream>



using namespace std;

const string menuItems[5]={
    "New Game",
    "Load Game",
    "How to Play",
    "Archive",
    "Quit"
};
const int menuSize=5; //hard coded, change when adding

void printBoxedText(const string &line){
    int terminalWidth=getTerminalWidth();
        int maxLineSize=14+4; //max menu item length + padding
        int boxWidth=maxLineSize+2;
        int borderSize=boxWidth+2;
        int leftPadding=(terminalWidth-borderSize)/2;
        string indent=string(leftPadding,' ');

        string horizontalLine="";
        for (int i=0; i<boxWidth; i++){
            horizontalLine+="─";
        }

        cout<<indent<<"┌"<<horizontalLine<<"┐"<<endl;
        cout<<indent<<"│"<<string(boxWidth, ' ')<<"│"<<endl;
        int padding=boxWidth-line.length();
        int leftPaddingInside=(padding)/2;
        int rightPaddingInside=padding-leftPaddingInside;
        cout<<indent<<"│"<<string(leftPaddingInside,' ')<<line<<string(rightPaddingInside,' ')<<"│"<<endl;
        cout<<indent<<"│"<<string(boxWidth, ' ')<<"│"<<endl;
        cout<<indent<<"└"<<horizontalLine<<"┘"<<endl;
}

void showMainMenu(){
    int selectedIdx=0;

    while (true){
        clearScreen();

        string banner = R"(
 ███████████            ███   █████████             ███                    
░█░░░███░░░█           ░░░   ███░░░░░███           ░░░                     
░   ░███  ░  ████████  ████ ░███    ░░░  ████████  ████  ████████   ██████ 
    ░███    ░░███░░███░░███ ░░█████████ ░░███░░███░░███ ░░███░░███ ███░░███
    ░███     ░███ ░░░  ░███  ░░░░░░░░███ ░███ ░███ ░███  ░███ ░░░ ░███████ 
    ░███     ░███      ░███  ███    ░███ ░███ ░███ ░███  ░███     ░███░░░  
    █████    █████     █████░░█████████  ░███████  █████ █████    ░░██████ 
   ░░░░░    ░░░░░     ░░░░░  ░░░░░░░░░   ░███░░░  ░░░░░ ░░░░░      ░░░░░░  
                                         ░███                              
                                         █████                             
                                        ░░░░░                                           
)";
        int bannerWidth=76;
        int terminalWidth=getTerminalWidth();
        int leftPadding=(terminalWidth-bannerWidth)/2;
        string indent=string(leftPadding,' ');
        istringstream ss(banner);
        string line;
        while (getline(ss,line)){
            cout<<indent<<line<<endl;
        }

  
        string summary="A Roguelike Deckbuilder Inspired by Slay the Spire and Sanguosha";
        string instructions="Use Arrow Keys to navigate and Enter to select";
        int summaryPadding=(terminalWidth-summary.length())/2;
        int instructionsPadding=(terminalWidth-instructions.length())/2;
        cout<<endl<<string(summaryPadding,' ')<<summary<<endl;
        cout<<string(instructionsPadding,' ')<<instructions<<endl<<endl;

        for (int i=0; i<menuSize; i++){
            string line=menuItems[i];
            if (selectedIdx==i){
                line="> "+line;
            }
            else{
                line="  "+line;
            }
            printBoxedText(line);
        }

        int command=getKey();
        if (command==enter_key_idx){
            switch (selectedIdx)
            {
            case 0:
                return;//start game
            case 1:
                cout<<"Load Game in progress..."<<endl;
                sleepMs(1000);
                //loadGame();
                break;
            case 2:
                cout<<"How to Play in progress..."<<endl;
                sleepMs(1000);
                //showHowToPlay(); place 玩法介绍 into a page
                break;
            case 3:
                cout<<"Archive in progress..."<<endl;
                sleepMs(1000);
                //showArchive(); desc of all skills and cards, optional
                break;
            case 4:
                exit(0);
            }
        }
        else{
            if (command==up_key_idx){
                selectedIdx=(selectedIdx+menuSize-1)%menuSize;
            }
            else if (command==down_key_idx){
                selectedIdx=(selectedIdx+1)%(menuSize);
            }
        }
    }
}
