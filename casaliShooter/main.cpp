#define FPS_LIMIT 60

#include <iostream>
#include <fstream>
#include <thread>

#include "MinGL2/include/mingl/mingl.h"
#include "MinGL2/include/mingl/gui/sprite.h"
#include "MinGL2/include/mingl/graphics/vec2d.h"
#include "MinGL2/include/mingl/shape/rectangle.h"
#include "MinGL2/include/mingl/gui/text.h"
#include "MinGL2/include/mingl/shape/line.h"
#include "MinGL2/include/mingl/audio/audioengine.h"
#include "MinGL2/include/mingl/gui/glut_font.h"
#include "MinGL2/include/mingl/transition/transition_engine.h"

#include "bgtext.h"
#include "menu.h"
#include "mystruct.h"
#include "move.h"
#include "check.h"
#include "generate.h"

using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;
using namespace nsAudio;

int main()
{

    Vec2D misPos;
    Vec2D torPos;

    srand(time(NULL));

    enemy open;
    open.rightOrLeft = 1;
    generateOPEN(open, 50);

    enemy classroom;
    classroom.rightOrLeft = 1;
    generateCLASSROOM(classroom, 125);

    vector<enemy> vecOvni;
    for (size_t i = 0; i < 5; ++i) {
        enemy ovni;
        ovni.rightOrLeft = 1;
        generateOVNI(ovni, "spritesi2/OVNI.si2");
        vecOvni.push_back(ovni);
    }

    enemy IPPs;
    IPPs.rightOrLeft = 1;
    generateVecSprite(IPPs, 50, "spritesi2/i++.si2");

    enemy JPPs;
    JPPs.rightOrLeft = 1;
    generateVecSprite(JPPs, 100, "spritesi2/j++.si2");

    enemy KPPs;
    KPPs.rightOrLeft = 1;
    generateVecSprite(KPPs, 150, "spritesi2/k++.si2");

    mugStruct mug;
    generateVecMug(mug);
    mug.index = 0;
    mug.vecMug[mug.index].setPosition(Vec2D(50+284, 138+500));


    // Initialise le système
    MinGL window("CasaliShooter", Vec2D(700, 1000), Vec2D(50, 0), KBlack);
    window.initGlut();
    window.initGraphic();
    // Initialise toutes les images
    Sprite background("img/fondarcade.si2", Vec2D(0, 0));
    Sprite backgroundpsg("img/fond_psg.si2", Vec2D(0, 0));
    Sprite scoreboardbg("img/scoreboard.si2", Vec2D(125, 250));
    Sprite titrescoreboard("img/titrescore.si2", Vec2D(0, 0));
    Sprite titreaccueil("img/casaliheader.si2", Vec2D(155, 138));
    Sprite startb("img/start-button.si2", Vec2D(222, 283));
    Sprite scoreb("img/scoreboard-button.si2", Vec2D(222, 378));
    Sprite settingsb("img/options-button.si2", Vec2D(222, 473));
    Sprite quitb("img/quit-button.si2", Vec2D(222, 568));
    Sprite casali("img/casali.si2", Vec2D(160, 305));
    Sprite moon("img/moon.si2", Vec2D(160, 350));
    Sprite sun("img/sun.si2", Vec2D(400, 338));
    Sprite arrow("img/arrow.si2", Vec2D(188, 460));
    Sprite backb("img/back-button.si2", Vec2D(66, 666));

    BgText choosethemode(Vec2D(150, 240), "Choose between light and dark theme with a or z", KWhite, KBlack);
    nsTransition::TransitionEngine transitionEngine;


    // On démarre les transitions sur notre objet custom
    transitionEngine.startContract(nsTransition::TransitionContract(choosethemode, choosethemode.TRANSITION_TEXT_COLOR, chrono::seconds(1), {0, 0, 0},
                                                                    chrono::seconds::zero(), nsTransition::Transition::MODE_LOOP_SMOOTH));
    transitionEngine.startContract(nsTransition::TransitionContract(choosethemode, choosethemode.TRANSITION_BACKGROUND_COLOR, chrono::seconds(1), {255, 255, 0},
                                                                    chrono::seconds::zero(), nsTransition::Transition::MODE_LOOP_SMOOTH));

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();
    unsigned choixobjet=0;
    unsigned choixpsgom=0;

    unsigned playerLifeUnsigned = 0;
    bool firstShootM = true;
    bool isPressed = false;
    bool firstShootT = true;
    //Vecteur pour savoir si un ovni tire
    bool ovniTorOne = true;
    bool ovniTorTwo = true;
    bool ovniTorThree = true;
    bool ovniTorFour = true;
    bool ovniTorFive = true;
    //Vecteur des Vec2D pour le tire des torpedos des ovnis
    vector<Vec2D> vecOvniTorpedo;
    for (size_t i = 0; i < vecOvni.size(); ++i) {
        Vec2D ovniTor;
        vecOvniTorpedo.push_back(ovniTor);
    }

    AudioEngine PPsMusic;
    PPsMusic.setMusic("music/I_Attack.wav", true);
    PPsMusic.toggleMusicPlaying();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        transitionEngine.update(frameTime);

        if (choixobjet==0) { //ouverture de l'écran d'accueil de casali shooter
            window.clearScreen();
            choixLightDark(window,choixpsgom, background, backgroundpsg);
            dessiner(window, titreaccueil);
            dessiner(window, startb);
            dessiner(window, scoreb);
            dessiner(window, settingsb);
            dessiner(window, quitb);
            dessiner(window, casali);
            menu(window, casali);
            choixobjet = entrerMenu(window, casali);
        }else if (choixobjet == 2){ //ouverture du menu scoreboard
            window.clearScreen();
            choixLightDark(window,choixpsgom, background, backgroundpsg);
            dessiner(window, scoreboardbg);
            dessiner(window, titrescoreboard);
            dessiner(window, backb);
            if (window.isPressed({'b', false})) {
                choixobjet = 0;
            }
            scoreboard(window);
        }else if (choixobjet == 3){ //ouverture du menu option
            window.clearScreen();
            choixLightDark(window,choixpsgom, background, backgroundpsg);
            window << choosethemode;
            dessiner(window, moon);
            dessiner(window, sun);
            dessiner(window, arrow);
            dessiner(window, backb);
            selectTheme(window, arrow);
            choixpsgom = chooseTheme(window, arrow, choixpsgom);
            if (window.isPressed({'b', false})) {
                choixobjet = 0;
            }
        }else if(choixobjet == 1){ // ouverture du jeu
            window.clearScreen();

            choixLightDark(window,choixpsgom, background, backgroundpsg);
            window << mug.vecMug[mug.index];

            IPPs.update(window);
            JPPs.update(window);
            KPPs.update(window);

            keyboard(window, mug.vecMug[mug.index]);

            moveVecSprite(IPPs);
            moveVecSprite(KPPs);
            moveVecSprite(JPPs);

            isPressed = missile(window, mug.vecMug[mug.index], IPPs, KPPs, JPPs, playerLifeUnsigned, firstShootM, isPressed, misPos);
            if(isPressed == true) window << nsShape::Rectangle(misPos, misPos + Vec2D(2, 10), KCyan);
            string playerLifeString = to_string(playerLifeUnsigned);
            //Points generator
            window << Text(Vec2D(60, 160), "Pts:", KWhite, GlutFont::BITMAP_9_BY_15);
            window << Text(Vec2D(100, 160), playerLifeString, KWhite, GlutFont::BITMAP_9_BY_15);

            if (torpedo(mug, IPPs, firstShootT, torPos)) window << nsShape::Rectangle(torPos, torPos + Vec2D(5, 10), KGreen);


            //Verify if enemies are still alive
            if (allDead(IPPs) && allDead(JPPs) && allDead(KPPs)) {
                PPsMusic.setMusicPlaying(false);
                AudioEngine openclassroomMusic;
                openclassroomMusic.setMusic("music/OCmusic.wav", true);
                openclassroomMusic.toggleMusicPlaying();
                while (!allDead(open) || !allDead(classroom)) {

                    // Récupère l'heure actuelle
                    //chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

                    window.clearScreen();

                    choixLightDark(window,choixpsgom, background, backgroundpsg);
                    window << mug.vecMug[mug.index];

                    keyboard(window, mug.vecMug[mug.index]);


                    for (size_t i = 0; i < vecOvni.size(); ++i) {
                        vecOvni[i].update(window);
                    }
                    open.update(window);
                    classroom.update(window);

                    //OPEN and CLASSROOM movements

                    for (size_t i = 0; i <  vecOvni.size(); ++i) {
                        moveOVNI(vecOvni[i]);
                    }
                    moveVecSprite(classroom);
                    moveOpen(open);

                    isPressed = missile(window, mug.vecMug[mug.index], open, classroom, JPPs, playerLifeUnsigned, firstShootM, isPressed, misPos);
                    if(isPressed == true) window << nsShape::Rectangle(misPos, misPos + Vec2D(2, 10), KCyan);
                    string playerLifeString = to_string(playerLifeUnsigned);
                    //Points generator
                    window << Text(Vec2D(60, 160), "Pts:", KWhite, GlutFont::BITMAP_9_BY_15);
                    window << Text(Vec2D(100, 160), playerLifeString, KWhite, GlutFont::BITMAP_9_BY_15);

                    //Open shooting
                    if (torpedo(mug, open, firstShootT, torPos)) window << nsShape::Rectangle(torPos, torPos + Vec2D(5, 10), KGreen);

                    //Ovnis shooting
                    if (ovniShoot(mug, vecOvni[0], ovniTorOne, vecOvniTorpedo[0])) window << nsShape::Rectangle(vecOvniTorpedo[0], vecOvniTorpedo[0] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[1], ovniTorTwo, vecOvniTorpedo[1])) window << nsShape::Rectangle(vecOvniTorpedo[1], vecOvniTorpedo[1] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[2], ovniTorThree, vecOvniTorpedo[2])) window << nsShape::Rectangle(vecOvniTorpedo[2], vecOvniTorpedo[2] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[3], ovniTorFour, vecOvniTorpedo[3])) window << nsShape::Rectangle(vecOvniTorpedo[3], vecOvniTorpedo[3] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[4], ovniTorFive, vecOvniTorpedo[4])) window << nsShape::Rectangle(vecOvniTorpedo[4], vecOvniTorpedo[4] + Vec2D(5, 10), KGreen);

                    // On finit la frame en cours
                    window.finishFrame();

                    // On vide la queue d'évènements
                    window.getEventManager().clearEvents();

                    // On attend un peu pour limiter le framerate et soulager le CPU
                    this_thread::sleep_for(chrono::milliseconds(2000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

                    // On récupère le temps de frame
                    frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

                }
                openclassroomMusic.setMusicPlaying(false);
                break;
            }
        }

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(2000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }


    return 0;
}