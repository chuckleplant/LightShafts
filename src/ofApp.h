#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void drawShafts();
    void drawScene();
    
    ofImage lightBillboard;
    ofImage sceneImage;
    ofShader shader;
    
    ofFbo lightShaftMask;
    ofFbo lightShaftResult;
    ofFbo mainRender;
    
    unsigned int downsampleFactor;
    unsigned int renderWidth;
    unsigned int renderHeight;
    ofRectangle renderLayout;
    ofVec2f sunPosition;
    ofxPanel gui;
    
    ofParameter<float> sunRadius;
    ofParameter<float> decay;
    ofParameter<float> exposure;
    ofParameter<float> density;
    ofParameter<float> weight;
    ofParameter<int> numSamples;
    
    ofxColorSlider baseColor;
    ofxColorSlider accentColor;
    ofxColorSlider sunColor;
    
    ofParameterGroup parameters;
    ofXml settings;
    ofTrueTypeFont font;
private:
    void setupImageResourcesFromImage(string const & imageFilename);
    void setupSceneParameters();
    void recomputeRenderLayout(unsigned int windowWidth, unsigned int windowHeight);
    void renderBackground();
};
