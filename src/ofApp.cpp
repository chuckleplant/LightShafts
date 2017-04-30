#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	renderWidth = 1280;
	renderHeight = 720;
    downsampleFactor = 1;
	int numBoxes = 50;

    decay.setMin(0.8);
    decay.setMax(1.0);
    exposure.setMin(0.0);
    exposure.setMax(2.0);
    weight.setMin(0.0);
    weight.setMax(2.0);
    density.setMin(0.0);
    density.setMax(2.0);
    numSamples.setMin(1);
    numSamples.setMax(200);
    sunRadius.setMin(10);
    sunRadius.setMax(500);
    
    
    parameters.setName("settings");
    parameters.add(decay.set("Decay", 0.96815));
    parameters.add(exposure.set("Exposure", 0.2));
    parameters.add(weight.set("Weight", 0.58767));
    parameters.add(density.set("Density", 0.926));
    parameters.add(numSamples.set("Samples", 100));
    parameters.add(sunRadius.set("Sun radius", 50.0));
    
    parameters.add(baseColor.set("Base color", ofColor(255,235,197)));
    parameters.add(accentColor.set("Accent color", ofColor(235,215,167)));
    parameters.add(sunColor.set("Sun color", ofColor::orangeRed));
    

    
    gui.setup(parameters);
    gui.setPosition(100, 100);
    setupSceneParameters();
    

    setupImageResourcesFromImage("firewatch_art.png");
	lightBillboard.load("rainbow.png");

	// Shader setup
	shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");	
}


void ofApp::setupSceneParameters(){
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    ofDisableDepthTest();
    ofEnableAlphaBlending();
}


void ofApp::setupImageResourcesFromImage(string const & imageFilename)
{
    if(sceneImage.load(imageFilename))
    {
        renderWidth = sceneImage.getWidth();
        renderHeight = sceneImage.getHeight();
        
        lightShaftMask.allocate(renderWidth, renderHeight, GL_RGBA);
        lightShaftResult.allocate(renderWidth, renderHeight, GL_RGBA);
        mainRender.allocate(renderWidth, renderHeight, GL_RGBA);
        
        ofSetWindowShape(renderWidth, renderHeight);
        
        recomputeRenderLayout(ofGetWindowWidth(), ofGetWindowHeight());
    }
    
}


void ofApp::recomputeRenderLayout(unsigned int windowWidth, unsigned int windowHeight){
    float imageAspect = renderWidth/(float)renderHeight;
    float windowAspect = windowWidth/(float)windowHeight;
    if(imageAspect > windowAspect){
        renderLayout.x = 0;
        renderLayout.width = windowWidth;
        renderLayout.height = windowWidth / imageAspect;
        renderLayout.y = (windowHeight - renderLayout.height)/2;
    }
    else{
        renderLayout.y = 0;
        renderLayout.height = windowHeight;
        renderLayout.width = windowHeight * imageAspect;
        renderLayout.x = (windowWidth - renderLayout.width)/2;
    }
}


//--------------------------------------------------------------
void ofApp::update(){
    unsigned int originMouseX = mouseX - renderLayout.x;
    unsigned int originMouseY = mouseY - renderLayout.y;
    ofVec2f normalizedMousePos = ofVec2f(originMouseX / renderLayout.width, originMouseY / renderLayout.height);
    sunPosition.x = normalizedMousePos.x * (renderWidth);
    sunPosition.y = normalizedMousePos.y * (renderHeight);
}


void ofApp::renderBackground()
{
    ofBackgroundGradient(accentColor, baseColor);
}


void ofApp::drawShaftsComposition(){
    ofSetColor(255);
    lightShaftResult.begin();
    ofClear(0, 0);
    ofVec2f normalizedLightPos = ofVec2f(sunPosition.x / (float)renderWidth, sunPosition.y / (float)renderHeight);
    shader.begin();
    shader.setUniform1f("decay", decay.get());
    shader.setUniform1f("exposure", exposure.get());
    shader.setUniform1f("weight", weight.get());
    shader.setUniform1f("density", density.get());
    shader.setUniform1i("numSamples", numSamples.get());
    shader.setUniformTexture("SceneSampler", mainRender.getTexture(), 1);
    shader.setUniformTexture("UserMapSampler", lightShaftMask.getTexture(), 2);
    shader.setUniform2f("lightPositionOnScreen", normalizedLightPos);
    ofFill();
    sceneImage.draw(0,0,renderWidth, renderHeight);
    shader.end();
    lightShaftResult.end();
}

void ofApp::drawShaftsMask(){
	lightShaftMask.begin();
    ofClear(0, 0);
    
    ofSetColor(sunColor);
    ofDrawCircle(sunPosition.x, sunPosition.y, sunRadius.get());
    
    ofSetColor(ofColor::black);
    sceneImage.draw(0,0);
    
	lightShaftMask.end();
}

void ofApp::drawScene()
{
    float fboScaleWidth = mainRender.getWidth() / ofGetWindowWidth();
    float fboScaleHeight = mainRender.getHeight() / ofGetWindowHeight();
	
    mainRender.begin();
	ofClear(0, 1);
    ofSetColor(255);
    ofPushMatrix();
    ofScale(fboScaleWidth, fboScaleHeight);
    renderBackground();
    ofPopMatrix();
    ofDrawCircle(sunPosition.x, sunPosition.y, sunRadius.get());
    sceneImage.draw(0,0);
	mainRender.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
	drawShaftsMask();
    drawScene();
    drawShaftsComposition();
    
    lightShaftResult.draw(renderLayout);
    ofSetColor(255);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    recomputeRenderLayout(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
