#pragma once

#include "ofMain.h"
#include "AudioAnalyser.h"

class ofApp : public ofBaseApp{
	public:
        enum anaType {
            LIN = 0,
            SPEC
        };

        enum aliState {
            BACKUP,
            AFTERCASEY,
            CHORUS_1,
            CHORUS_2
        };

        enum shape {
            HEXAGON,
            OCTAGON
        };

		void setup();
		void update();
		void draw();
        void keyPressed(int key);
        void trackedObjectsCalc(int type, int bin, float * brightness, ofVec2f lowHigh);
        void trackedObjectsDraw(ofFloatColor color, ofVec2f coord, ofVec2f startEndTime);
        void hexWave();
        void octWave();
        void GUI();
        void loadBackground();
        void loadPolygon(int shape);
        void loadLevels(int x1, int x2, int x3, int y, float scalar);
        void loadVolume(int Shape);
        void loadTracks();
        
        ofFmodSoundPlayer m_soundPlayer;
        AudioAnalyser     m_audioAnalyser;
        ofTrueTypeFont    m_font;

        ofVec3f m_HexCol;
        ofVec3f m_OctCol;

        const int OF_KEY_SPACEBAR = 32;
        const int OF_KEY_ENTER = 13;

        int m_AlisPart;
        
        float m_alpha;
        float m_aPoly;
        float m_speed;
        float m_volume;
        float m_cBright_1;
        float m_cBright_2;
        float m_cBright_3;
        float m_cBright_4;
        float m_cBright_5;

        bool m_activateGUI;
        bool m_pauseSound;
        bool m_mute;
        bool m_check = true;


};
