//
//  HexagonMap.hpp
//
//
//  Created by enrico on 29/08/17.
//
//

#ifndef HexagonMap_hpp
#define HexagonMap_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

#define MIN_TIME 10
#define MAX_TIME 20
#define MAX_HEXAGONS 4
#define NUM_VERTICES 7
#define MIN_FUCK_UP 10
#define MAX_FUCK_UP 20

class HexagonMap
{
    
public:
    enum DRAWING
    {
        NORMAL = 0,
        FORWARD,
        SCALED,
        COLORED,
        SCALED_COLORED,
        SIZE
    };
    
    struct HexagonSetting //setting per hexagon!!!
    {
        int     direction; // the stripe direction
        ofColor color;
        float   stripeWidth;
        int     drawingID;
        float   speed;
        bool    isMuted;
    };
    
    struct Scene
    {
        int     direction; // the stripe direction
        ofColor color; //rgb
        float   stripeWidth; //0-1
        int     drawingID; // 0 -> DRAWING::SIZE
        float   speed;// -1 -> +1
    };
    
    
    HexagonMap();
    ~HexagonMap(){};
    
    void addHexagon( ofxOscMessage& m);
    void addHexagon(ofVec2f * verts,int length);
    void addTexCoords(ofMesh &m);
    void mapPoint(ofxOscMessage &m);
    void muteHexagon(ofxOscMessage &m);
    void revert(ofxOscMessage &m);
    void moveHexagon(ofxOscMessage &m);
    void movePoint(ofxOscMessage &m);
    void setEditMode(ofxOscMessage &m);
    void setActiveHexagon(int i);
    void setActiveVertex(int i);
    void update();
    void createNewSetting();
    void draw();
    void drawSingleHexagon(int &id);
    void drawScaled();
    void drawNormal();
    
    void load();
    void loadScenes();
    void save(ofxOscMessage &m);
    void save();
    
    
private:
    
    ofxOscReceiver              receiver;
    vector<ofMesh>              hexagons;
    vector<ofVec2f>             hexCenters;
    vector<HexagonSetting>      hexSettings;
    vector<Scene>               scenes;
    
    ofShader                    shader;
    bool                        isEditMode;
    int                         activeHexagon;
    int                         activeVertex;
    
    float                       nextTimeEvent;
    float                       globalSpeedLow;
    float                       globalSpeedHigh;
    int                         actualScene;
    int                         fuckUpCounter; // how many changes till one is changed
    int                         nextFuckUpAt; // which one
};

#endif /* HexagonMap_hpp */
