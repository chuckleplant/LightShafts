#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	renderWidth = 1280;
	renderHeight = 720;
	int numBoxes = 50;


	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ofEnableDepthTest();
	ofEnableAlphaBlending();
	ofSetSmoothLighting(true);

	// Setup random box positions;
	for (size_t i = 0; i < numBoxes; i++)
	{
		boxPositions.emplace_back(ofVec3f(
			100 - ofRandom(200),
			100 - ofRandom(200),
			100 - ofRandom(200)));
	}

	// Objects setup
	sphere.setRadius(50);
	sphere.setGlobalPosition(-50, -50, -50);
	box.setHeight(30);
	box.setWidth(30);
	box.setDepth(30);

	// Light setup
	lightBillboard.load("rainbow.png");
	light.setDiffuseColor(ofColor(255.f, 255.f, 255.f));
	light.setSpecularColor(ofColor(255.f, 255.f, 255.f));
	light.setPosition(200, 200, 200);

	// Material setup
	material.setShininess(64);

	// FBO setup
	lightShaftMask.allocate(renderWidth, renderHeight, GL_RGBA);
	lightShaftResult.allocate(renderWidth, renderHeight, GL_RGBA);
	mainRender.allocate(renderWidth, renderHeight, GL_RGBA);


	// Shader setup
	shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");	
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::drawShafts()
{
	ofDisableDepthTest();
	lightShaftMask.begin();
		ofClear(0, 0);
		ofVec3f light2DPosition = camera.worldToScreen(light.getGlobalPosition());
		lightBillboard.draw(light2DPosition.x - lightBillboard.getWidth()/2, light2DPosition.y - lightBillboard.getHeight()/2, light2DPosition.z);
		camera.begin();
			ofSetColor(ofColor::black);

			for (auto & position : boxPositions)
			{
				ofTranslate(position);
				box.draw();
			}
			
			sphere.draw();
		camera.end();
	lightShaftMask.end();
	
}

void ofApp::drawScene()
{
	ofEnableLighting();
	mainRender.begin();
	ofDisableBlendMode();
	ofEnableDepthTest();
	ofClear(0, 1);
    ofBackgroundGradient(ofColor::royalBlue, ofColor::darkBlue);
	camera.begin();
		light.enable();
		material.begin();
			ofFill();
			for (auto & position : boxPositions)
			{
				ofTranslate(position);
				box.draw();
			}
			sphere.draw();
		material.end();	
	camera.end();
	mainRender.end();
	ofDisableLighting();
}

//--------------------------------------------------------------
void ofApp::draw(){

	// Draw oppacity
	ofSetColor(255);
	drawShafts();

    
    
    
	// Draw shafts
	ofSetColor(255);
	lightShaftResult.begin();
	ofClear(0, 0);
	ofVec3f light2DPosition = camera.worldToScreen(light.getGlobalPosition());
	ofVec2f normalizedLightPos = ofVec2f(light2DPosition.x / (float)renderWidth, light2DPosition.y / (float)renderHeight);
	shader.begin();
		shader.setUniformTexture("UserMapSampler", lightShaftMask.getTexture(), 1);
		shader.setUniform2f("lightPositionOnScreen", normalizedLightPos);
		ofFill();
		lightBillboard.draw(0, 0, renderWidth, renderHeight);
	shader.end();
	lightShaftResult.end();

	// Draw scene
	ofSetColor(255);
	drawScene();

	//lightShaftMask.draw(0, 0);
	//lightShaftResult.draw(0, 0);
	//mainRender.draw(0, 0);
	//return;



	ofClear(0, 0);
	ofDisableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	mainRender.draw(0, 0);
	lightShaftResult.draw(0, 0);
    ofDisableBlendMode();

	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 10);

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
