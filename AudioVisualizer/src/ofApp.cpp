#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(1280, 900);
    ofSetWindowPosition(50, 100);
    ofSetFrameRate(60);

    m_AlisPart = BACKUP;
    m_speed = 1.0f;
    m_volume = 1.0f;
    m_alpha = 255.0f;
    m_aPoly = 255.0f;

    m_HexCol = ofVec3f(255, 94, 53);
    m_OctCol = ofVec3f( 255, 255, 255);

    m_activateGUI = false;
    m_pauseSound = false;
    m_mute = false;
    ofSetVerticalSync(true);

    m_font.load("fonts/font.ttf", 12, true);
    m_soundPlayer.load("DMC5 Devil May Cry 5 OST - Neros Battle Theme.mp3");
    m_soundPlayer.setLoop(true);
    m_soundPlayer.play();

    m_audioAnalyser.init(&m_soundPlayer, 20);

    m_soundPlayer.setPositionMS(100000);
    //m_soundPlayer.setVolume(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    m_audioAnalyser.update();
    if (m_soundPlayer.getPosition() <= 0.001f && m_AlisPart != BACKUP) {
        m_AlisPart = BACKUP;
    }

    if (m_soundPlayer.getPositionMS() > 29910 && m_AlisPart == BACKUP) {
        m_AlisPart = AFTERCASEY;
    }
    else if (m_soundPlayer.getPositionMS() > 66261 && m_AlisPart == AFTERCASEY) {
        m_AlisPart = CHORUS_1;
    }
    else if (m_soundPlayer.getPositionMS() > 116955 && m_AlisPart == CHORUS_1) {
        m_AlisPart = CHORUS_2;
    }

    trackedObjectsCalc(LIN, 05, &m_cBright_1, ofVec2f(05.0f, 20.0f));       //casey edwards

    switch (m_AlisPart) {                                                   //ali edwards
    case BACKUP:
        trackedObjectsCalc(LIN, 10, &m_cBright_2, ofVec2f(4.5f, 20.0f));
        break;
    case AFTERCASEY:
        trackedObjectsCalc(LIN, 16, &m_cBright_2, ofVec2f(2.0f, 25.0f));
        break;
    case CHORUS_1:
        trackedObjectsCalc(LIN, 9, &m_cBright_2, ofVec2f(2.0f, 22.0f ));

        if (m_soundPlayer.getPositionMS() > 81151 && m_alpha > 0) {
            m_alpha -= 8.5f;
            m_aPoly -= 8.5f;
            if (m_alpha < 0) {
                m_alpha = 0;
            }
            if (m_aPoly < 0) {
                m_aPoly = 0;
            }
        }
        break;
    case CHORUS_2:
        trackedObjectsCalc(LIN, 21, &m_cBright_2, ofVec2f(3.0f, 55.0f));

        if (81151 < m_soundPlayer.getPositionMS() < 153152 && m_alpha < 255) {
            m_alpha += 8.5f;
            m_aPoly += 8.5f;
            if (m_alpha > 255) {
                m_alpha = 255;
            }
            if (m_aPoly > 255) {
                m_aPoly = 255;
            }
        }
        if (m_soundPlayer.getPositionMS() > 153152 && m_alpha > 0) {
            m_alpha -= 10.5f;
            m_aPoly -= 10.5f;
            if (m_alpha < 0) {
                m_alpha = 0;
            }
            if (m_aPoly < 0) {
                m_aPoly = 0;
            }
        }

        if (m_soundPlayer.getPositionMS() > 189570 && m_alpha < 255) {
            m_alpha += 8.5f;
            m_aPoly += 8.5f;
            if (m_alpha > 255) {
                m_alpha = 255;
            }
            if (m_aPoly > 255) {
                m_aPoly = 255;
            }
        }
        break;
    }

    trackedObjectsCalc(SPEC, 01, &m_cBright_3, ofVec2f(18.0f, 200.0f));     //beat
    trackedObjectsCalc(SPEC, 02, &m_cBright_4, ofVec2f(30.0f, 170.0f));     //secondary beat
    trackedObjectsCalc(SPEC, 30, &m_cBright_5, ofVec2f(5.0f, 30.0f));       //Undertones

    //cout << m_soundPlayer.getPositionMS() << endl;

}

//--------------------------------------------------------------
void ofApp::draw() {
    ofPushMatrix();
        loadBackground();
    ofPopMatrix();

    ofPushMatrix();
        ofTranslate(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

        loadPolygon(HEXAGON);
        loadPolygon(OCTAGON);
        
        loadTracks();

     ofPopMatrix();

     if (m_activateGUI) {
         GUI();
     }
}

void ofApp::GUI() {
    ofSetCircleResolution(200);
    ofSetColor(255);
    m_font.drawString("Volume Level", 140, 180);
    m_font.drawString("Left",          80, 300);
    m_font.drawString("Mix",          180, 300);
    m_font.drawString("Right", 280, 300);

    m_font.drawString(("Speed:      " + ofToString(m_soundPlayer.getSpeed())), 100, 50);
    m_font.drawString(("Volume:     " + ofToString(m_soundPlayer.getVolume())), 100, 70);
    m_font.drawString(("Play Time:  " + ofToString(m_soundPlayer.getPositionMS() / 1000)), 100, 90);

    m_font.drawString("Tracking", 985, 50);
    m_font.drawString("Casey", 875, 170);
    m_font.drawString("Ali", 1010, 170);
    m_font.drawString("Beat", 1130, 170);
    m_font.drawString("2nd Beat", 920, 290);
    m_font.drawString("Undertone", 1040, 290);
    
    ofPushMatrix();
    ofFill();
        loadLevels(100, 200, 300, 230, 200.f);
    ofPopMatrix();

    m_audioAnalyser.drawWaveform(      40, 360, 1200, 120);
    m_audioAnalyser.drawSpectrum(      40, 520, 1200, 120);
    m_audioAnalyser.drawLinearAverages(40, 680, 1200, 120);

    //Casey Edwards                                                                                                
    trackedObjectsDraw(ofFloatColor(m_cBright_1, 0.0f, 0.0f), ofVec2f(900, 110), ofVec2f(18623, 42197));           
                                                                                                                   
    //Ali Edwards                                                                                                  
    switch (m_AlisPart) {
    case BACKUP:
        trackedObjectsDraw(ofFloatColor(0.0f, m_cBright_2, 0.0f), ofVec2f(1025, 110), ofVec2f(24127, 29910)); 
        break;                                                                                                
    case AFTERCASEY:                                                                                          
        trackedObjectsDraw(ofFloatColor(0.0f, m_cBright_2, 0.0f), ofVec2f(1025, 110), ofVec2f(36223, 66261)); 
        break;                                                                                                
    case CHORUS_1:                                                                                            
        trackedObjectsDraw(ofFloatColor(0.0f, m_cBright_2, 0.0f), ofVec2f(1025, 110), ofVec2f(81151, 116955));
        break;                                                                                                
    case CHORUS_2:                                                                                            
        trackedObjectsDraw(ofFloatColor(0.0f, m_cBright_2, 0.0f), ofVec2f(1025, 110), ofVec2f(153152, 189120));
        break;
    }                                                                                    
                                                                                                                    
    //The Beat                                                                                                      
    trackedObjectsDraw(ofFloatColor(0.0f, m_cBright_3, m_cBright_3), ofVec2f(1150, 110), ofVec2f(0, 206500));       
                                                                                                                    
    //Secondary Beat                                                                                                
    trackedObjectsDraw(ofFloatColor(0.0f, 0.0f, m_cBright_4), ofVec2f(960, 230), ofVec2f(0, 206500));               
                                                                                                                    
    //Undertones                                                                                                    
    trackedObjectsDraw(ofFloatColor(m_cBright_5, m_cBright_5, m_cBright_5), ofVec2f(1085, 230), ofVec2f(0, 206500));



}

void ofApp::trackedObjectsCalc(int type, int bin, float * brightness, ofVec2f lowHigh) {
    float object;
    switch (type) {
    case(LIN):
        object = m_audioAnalyser.getLinearAverage(bin);
        break;
    case(SPEC):
        object = m_audioAnalyser.getSpectrum(bin);
        break;
    }

    *brightness = ofMap(object, lowHigh.x, lowHigh.y, 0.0f, 1.0f, true);
}

void ofApp::trackedObjectsDraw(ofFloatColor color, ofVec2f coord, ofVec2f startEndTime) {
    ofSetColor(0);
    ofDrawCircle(coord, 35);

    if (m_soundPlayer.getPositionMS() >= startEndTime.x && m_soundPlayer.getPositionMS() <= startEndTime.y) {
        ofSetColor(color);
        ofDrawCircle(coord, 30);
    }
}

void ofApp::keyPressed(int key) {
    //////////////////ACTIVATE GUI//////////////////
    if (key == OF_KEY_SPACEBAR && !m_activateGUI) {
        m_activateGUI = true;
    }
    else if (key == OF_KEY_SPACEBAR && m_activateGUI) {
        m_activateGUI = false;
    }

    //////////////////PAUSE AUDIO//////////////////
    if (key == OF_KEY_ENTER && !m_pauseSound) {
        m_pauseSound = true;
        m_soundPlayer.setPaused(m_pauseSound);
    }
    else if (key == OF_KEY_ENTER && m_pauseSound) {
        m_pauseSound = false;
        m_soundPlayer.setPaused(m_pauseSound);
    }

    //////////////////MUTE AUDIO//////////////////
    if (key == OF_KEY_SHIFT && !m_mute) {
        m_mute = true;
        m_soundPlayer.setVolume(0);
    }
    else if (key == OF_KEY_SHIFT && m_mute) {
        m_mute = false;
        m_soundPlayer.setVolume(1);
    }

    //////////////////CHANGE VOLUME//////////////////
    if (key == OF_KEY_UP) {
        if (m_volume < 1) {
            m_volume += .25;
            m_soundPlayer.setVolume(m_volume);
        }
    }

    else if (key == OF_KEY_DOWN) {
        if (m_volume > 0.0f) {
            m_volume -= .25;
            m_soundPlayer.setVolume(m_volume);
        }
    }
    //////////////////CHANGE SPEED//////////////////
    if (key == OF_KEY_RIGHT) {
        if (m_speed < 4) {
            m_speed += .25;
            m_soundPlayer.setSpeed(m_speed);
        }
    }
    else if (key == OF_KEY_LEFT) {
        if (m_speed > 1) {
            m_speed -= .25;
            m_soundPlayer.setSpeed(m_speed);
        }
    }


    if (key == OF_KEY_TAB) {
        m_soundPlayer.play();
    }
}

void ofApp::hexWave() {
    ofBeginShape();
        m_audioAnalyser.drawWaveformHex(-75, -130, 75, -130, 150, 220, 0);
        m_audioAnalyser.drawWaveformHex(-75, -130, 75, -130, 150, 220, 60);
        m_audioAnalyser.drawWaveformHex(-75, -130, 75, -130, 150, 220, 120);
        m_audioAnalyser.drawWaveformHex(-75, -130, 75, -130, 150, 220, 180);
        m_audioAnalyser.drawWaveformHex(-75, -130, 75, -130, 150, 220, 240);
        m_audioAnalyser.drawWaveformHex(-75, -130, 75, -130, 150, 220, 300);
    ofEndShape();
}

void ofApp::octWave() {
    ofBeginShape();
        m_audioAnalyser.drawWaveformHex(0, -150, 105, -107, 150, 220, 0);
        m_audioAnalyser.drawWaveformHex(0, -150, 105, -107, 150, 220, 45);
        m_audioAnalyser.drawWaveformHex(0, -150, 105, -107, 150, 220, 90);
        m_audioAnalyser.drawWaveformHex(0, -150, 105, -107, 150, 220, 135);
        m_audioAnalyser.drawWaveformHex(0, -150, 105, -107, 150, 220, 180);
        m_audioAnalyser.drawWaveformHex(0, -150, 105, -107, 150, 220, 225);
        m_audioAnalyser.drawWaveformHex(0, -150, 105, -107, 150, 220, 270);
        m_audioAnalyser.drawWaveformHex(0, -150, 105, -107, 150, 220, 315);
    ofEndShape();
}

void ofApp::loadBackground() {
    ofFill();
    if (m_AlisPart <= CHORUS_1) {
        //purple
        ofSetColor(51, 1, 54, m_alpha);
        ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        //red
        ofSetColor(143, 29, 44, 255 - m_alpha);
        ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    }
    else if (m_AlisPart == CHORUS_2 && m_AlisPart < 153152) {
        //red
        ofSetColor(143, 29, 44, 255 - m_alpha);
        ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        //blue
        ofSetColor(28, 36, 65, 0 + m_alpha);
        ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    }
    else if (m_AlisPart == CHORUS_2 && m_AlisPart > 153152) {
        //blue
        ofSetColor(28, 36, 65, 255 - m_alpha);
        ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        //red
        ofSetColor(143, 29, 44, 0 + m_alpha);
        ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    }

    else if (m_soundPlayer.getPositionMS() > 189575) {
        //red

        ofSetColor(143, 29, 44, 255 - m_alpha);
        ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

        //purple
        ofSetColor(51, 1, 54, m_alpha);
        ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    }

    if(m_activateGUI){
        //black
        ofSetColor(0, 0, 0, 100);
        ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    }
    cout << m_alpha << endl;
}

void ofApp::loadPolygon(int shape){
    ofNoFill();

    switch (shape) {
    case HEXAGON:
        ofSetColor(m_HexCol.x, m_HexCol.y, m_HexCol.z, m_aPoly);
        ofSetCircleResolution(6);
        ofDrawCircle(0, 0, 150);
        loadLevels(-50, 0, 50, 0, 100.0f);
        loadVolume(shape);
        hexWave();
        break;
    case OCTAGON:
        ofSetColor(m_OctCol.x, m_OctCol.y, m_OctCol.z, 255 - m_aPoly);
        ofSetCircleResolution(8);
        ofDrawCircle(0, 0, 150);
        loadLevels(-50, 0, 50, 0, 100.0f);
        loadVolume(shape);
        octWave();
        break;
    }

}

void ofApp::loadLevels(int x1, int x2, int x3, int y, float scalar) {
    ofPushMatrix();
        ofDrawCircle(x1, y, m_audioAnalyser.getLeftLevel()  * scalar);
        ofDrawCircle(x2, y, m_audioAnalyser.getMixLevel()   * scalar);
        ofDrawCircle(x3, y, m_audioAnalyser.getRightLevel() * scalar);
    ofPopMatrix();
}

void ofApp::loadVolume(int Shape) {
    float vol = m_soundPlayer.getVolume();
    //cout 
    switch (Shape) {
    case HEXAGON:
        
        if (m_soundPlayer.getVolume() == .25) {
            ofDrawCircle(0, 0, 175);
        }
        else if (m_soundPlayer.getVolume() == .50) {
            ofDrawCircle(0, 0, 200);
            ofDrawCircle(0, 0, 175);
        }
        else if (m_soundPlayer.getVolume() == .75) {
            ofDrawCircle(0, 0, 225);
            ofDrawCircle(0, 0, 200);
            ofDrawCircle(0, 0, 175);
        }
        else if (m_soundPlayer.getVolume() == 1) {
            ofDrawCircle(0, 0, 250);
            ofDrawCircle(0, 0, 225);
            ofDrawCircle(0, 0, 200);
            ofDrawCircle(0, 0, 175);
        }


        break;
        
    case OCTAGON:
        if (m_soundPlayer.getVolume() == .25) {
            ofDrawCircle(0, 0, 175);
        }
        else if (m_soundPlayer.getVolume() == .50) {
            ofDrawCircle(0, 0, 200);
            ofDrawCircle(0, 0, 175);
        }
        else if (m_soundPlayer.getVolume() == .75) {
            ofDrawCircle(0, 0, 225);
            ofDrawCircle(0, 0, 200);
            ofDrawCircle(0, 0, 175);
        }
        else if (m_soundPlayer.getVolume() == 1) {
            ofDrawCircle(0, 0, 250);
            ofDrawCircle(0, 0, 225);
            ofDrawCircle(0, 0, 200);
            ofDrawCircle(0, 0, 175);
        }


        break;
    }
}

void ofApp::loadTracks() {

    ofFill();
    ofSetColor(255, 255, 255, 100);

    ofDrawCircle(-300, 300, m_cBright_1 * 50.0f);
    ofDrawCircle(-450, 150, m_cBright_2 * 50.0f);
    ofDrawCircle(-500, 0, m_cBright_3 * 50.0f);
    ofDrawCircle(-450, -150, m_cBright_4 * 100.0f);
    ofDrawCircle(-300, -300, m_cBright_5 * 100.0f);

    ofDrawCircle(300, 300, m_cBright_5 * 100.0f);
    ofDrawCircle(450, 150, m_cBright_4 * 100.0f);
    ofDrawCircle(500, 0, m_cBright_3 * 50.0f);
    ofDrawCircle(450, -150, m_cBright_2 * 50.0f);
    ofDrawCircle(300, -300, m_cBright_1 * 50.0f);
}

