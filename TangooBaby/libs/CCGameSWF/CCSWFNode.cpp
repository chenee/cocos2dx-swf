//
//  CCSWFNode.m
//  GSGGameSWF
//
//  Created by dario on 13-02-25.
//  Modify by chenee (chenee543216@gmail.com) on 13-05-20
//  @chenee: 1\change Objective-C to C++ ;2\change opengl es 1.1 to opengl es 2.0
//

#import "CCSWFNode.h"
#import "CCGameSWF.h"
#import "cocos2d.h"
#import "gameswf.h"
#import "gameswf_player.h"
#import "gameswf_root.h"
#import "ccMacros.h"
#import "gameswf_types.h"
#import "gameswf_impl.h"

using namespace cocos2d;

//@interface CCSWFNode_touchContainer : NSObject
//{
//    CGPoint m_position;
//    int m_state;
//}
//
//@property (readonly) CGPoint position;
//@property (readonly) int state;
//
//+(id) touchContainerWithPosition:(CGPoint)position andState:(int)state;
//-(id) initWithPosition:(CGPoint)position andState:(int)state;
//
//@end
class CCSWFNode_touchContainer : public cocos2d::CCNode
{
    CCPoint m_position;
    int m_state;
    CCSWFNode_touchContainer(CCPoint position,int state);
//    bool touchContainerWithPosition(CCPoint position, int state);

};


//@implementation CCSWFNode_touchContainer

//@synthesize position = m_position;
//@synthesize state = m_state;
CCSWFNode_touchContainer::CCSWFNode_touchContainer(CCPoint position, int state)
{
    m_position = position;
    m_state = state;
}
//bool CCSWFNode_touchContainer::touchContainerWithPosition(CCPoint position, int state)
//{
////    return [[CCSWFNode_touchContainer alloc] initWithPosition:position andState:state];
//    return true;
//}
//
//void CCSWFNode_touchContainer::initWithPositionAndState(CCPoint position, int state)
//{
////    self = [super init];
////    if (self)
////    {
//        m_position = position;
//        m_state = state;
////    }
////    return self;
//}
//
//@end



//@interface CCSWFNode_imp : NSObject
//{
//@public
//    gameswf::gc_ptr<gameswf::player> m_player;
//    gameswf::gc_ptr<gameswf::root>	m_movie;
//}
//
//-(id) initWithSWFFile:(NSString*)file;
//
//@end
class CCSWFNode_imp : public cocos2d::CCNode
{
public:
    gameswf::gc_ptr<gameswf::player> m_player;
    gameswf::gc_ptr<gameswf::root>	m_movie;
    
    bool initWithSWFFile(const char *file);
//    void dealloc();

};

//@implementation CCSWFNode_imp

bool CCSWFNode_imp::initWithSWFFile(const char *file)
{
    std::string pathKey = file;
    
    pathKey = CCFileUtils::sharedFileUtils()->fullPathForFilename(pathKey.c_str());
    if (pathKey.size() == 0)
    {
        return false;
    }
//    self = [super init];
//    if (self)
//    {
        // make sure CCGameSWF is initialized //
//        [CCGameSWF sharedInstance];
        CCGameSWF::sharedInstance();
        m_player = new gameswf::player();
        m_movie = m_player->load_file(pathKey.c_str());
        if (m_movie == NULL)
        {
            printf("ERROR: Cannot open input file %s", file);
//            [self release];
            return false;
        }
//    }
//	
//	return self;
    return true;
}

//void CCSWFNode_imp::dealloc()
//{
//    delete m_movie;
//    delete m_player;
////    [super dealloc];
//}

//@end



//@implementation CCSWFNode
CCSWFNode::CCSWFNode()
{
//    CCLOG("CCSWFNode init ....");
}
CCSWFNode::~CCSWFNode()
{
    this->stopAction();
    this->removeFromParentAndCleanup(true);
    this->imp->m_movie = NULL;
    this->imp->m_player = NULL;
    
    delete imp;
//    CCLOG("CCSWFNode delete ....");
}

CCString* CCSWFNode::movieName()
{
//    return [NSString stringWithUTF8String:imp->m_movie->m_movie->m_name.c_str()];
    return CCString::createWithFormat(imp->m_movie->m_movie->m_name.c_str());
}

void CCSWFNode::setMovieName(char *movieName)
{
    imp->m_movie->m_movie->m_name = movieName;// UTF8String];
}

//+(id) nodeWithSWFFile:(NSString*)file
//{
//    return [[[CCSWFNode alloc] initWithSWFFile:file] autorelease];
//}
CCSWFNode* CCSWFNode::create(const char* file)
{
    CCSWFNode* swf = new CCSWFNode();
    if (! swf->initWithSWFFile(file)) {
        swf->release();
        return NULL;
    }
    
    return swf;
}

bool CCSWFNode::initWithSWFFile(const char* file)
{
//    self = [super init];
//    if (self)
//    {
//        imp = [[CCSWFNode_imp alloc] initWithSWFFile:file];
    imp = new CCSWFNode_imp();
    if (!imp->initWithSWFFile(file))
    {
//            [self release];
        imp->release();
        return false;
    }
    m_movieWidth = imp->m_movie->m_def->m_frame_size.m_x_max - imp->m_movie->m_def->m_frame_size.m_x_min;
    m_movieHeight = imp->m_movie->m_def->m_frame_size.m_y_max - imp->m_movie->m_def->m_frame_size.m_y_min;
    m_localScaleX = (imp->m_movie->get_movie_width() / m_movieWidth);
    m_localScaleY = -(imp->m_movie->get_movie_height() / m_movieHeight);
    m_scaleX = 1.0;
    m_scaleY = 1.0;
    
    m_touchEvents = new CCArray();//[[NSMutableArray alloc] init];
    
    this->setContentSize(CCSize(m_movieWidth, m_movieHeight));
    this->setScale(1.0f);
    this->setAnchorPoint(ccp(0.5,0.5));
    
    this->isGrouped = false;
    this->isRuning = false;
    this->m_listener = NULL;
    this->m_endListener = NULL;
    this->repeat = false;
    this->iFrameCount = imp->m_movie->get_frame_count();

//        [self setContentSize:CGSizeMake(m_movieWidth, m_movieHeight)];
//        [self setScale:1.0];
//        [self setAnchorPoint:ccp(0.5f, 0.5f)];
//    }
    return true;
}
void CCSWFNode::setFlipX(bool flipX)
{
//    [super setFlipX:flipX];
    if (flipX) {
//        m_localScaleX *= -1;
//        m_scaleX = m_scaleX*-1;
//        [super setScaleX:m_localScaleX*-1];
        setScaleX(m_localScaleX * -1);
        
    }
}
void CCSWFNode::setFlipY(bool flipY)
{
    if (flipY) {
        setScaleY(m_localScaleY * -1);
    }
}
float CCSWFNode::scale()
{
    CCAssert(m_scaleX == m_scaleY, "CCNode#scale. ScaleX != ScaleY. Don't know which one to return");
	return m_scaleX;
}

void CCSWFNode::setScale(float scale)
{
    m_scaleX = m_scaleY = scale;
//    [super setScaleX:m_localScaleX * m_scaleX];
//    [super setScaleY:m_localScaleY * m_scaleY];
    setScaleX(m_localScaleX*m_scaleX);
    setScaleY(m_localScaleY*m_scaleY);
}

float CCSWFNode::scaleX()
{
    return m_scaleX;
}

void CCSWFNode::setScaleX(float scaleX)
{
    m_scaleX = scaleX;
//    [super setScaleX:m_localScaleX * m_scaleX];
//    setScaleX(m_localScaleX*m_scaleX);
    cocos2d::CCSprite::setScaleX(m_scaleX);
}

float CCSWFNode::scaleY()
{
    return m_scaleY;
}

void CCSWFNode::setScaleY(float scaleY)
{
    m_scaleY = scaleY;
//    [super setScaleY:m_localScaleY];
//    setScaleY(m_localScaleY);
    CCSprite::setScaleY(m_scaleY);
    
}

//void CCSWFNode::dealloc()
//{
////    m_touchEvents->release();
////    [m_touchEvents release];
////    [super dealloc];
//    this->stopAction();
////    this->imp->dealloc();
//    delete imp;
//}

void CCSWFNode::onEnterTransitionDidFinish()
{
    
//    [self scheduleUpdate];
//    if(isRuning)
//        return;
//    
//    this->isRuning = true;
////    this->imp->m_movie->goto_frame(48);
////    this->imp->m_movie->set_play_state((gameswf::character::play_state)1);
////    this->imp->m_movie->set_play_run();
//    schedule(schedule_selector(CCSWFNode::update),1/2);
    
//    schedule(schedule_selector(CCSWFNode::update));


//    [[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self priority:1 swallowsTouches:YES];
}

void CCSWFNode::onExit()
{
//    [self unscheduleAllSelectors];
    if(! isRuning)
        return;
    
    unschedule(schedule_selector(CCSWFNode::update));
    this->isRuning = false;
//    [[CCTouchDispatcher sharedDispatcher] removeDelegate:self];
}
void CCSWFNode::runAction()
{
    if(isRuning)
        return;
    
    //if in singleton group we stop other sibling.
    if (isGrouped) {
       CCSWFNodeGroup* g = (CCSWFNodeGroup*)this->getParent();
        if (g->getSingleton()) {
            g->stopAction();
        }
    }
    
    this->isRuning = true;
    //reset 
    this->imp->m_movie->goto_frame(0);
    this->imp->m_movie->set_play_run();
    
    schedule(schedule_selector(CCSWFNode::update),1/2);
}
void CCSWFNode::stopAction()
{
    if(! isRuning)
        return;
    unschedule(schedule_selector(CCSWFNode::update));
    this->isRuning = false;
}

void CCSWFNode::addFrameListener(int iFrame, CCObject* target,SEL_MenuHandler selector)
{
    CCAssert(target != NULL, "swf action should not be NULL");

    if(iFrame == -1){
        m_endListener = target;
        m_pfnEndSelector = selector;
    }else if(iFrame > 0){
        m_listener = target;
        m_pfnSelector = selector;
        iListenFrame = iFrame;
    }
}
void CCSWFNode::setNextAction(CCSWFNode* target)
{
    CCAssert(target != NULL, "next swf action should not be NULL");
    
    m_endListener = target;
    m_pfnEndSelector = menu_selector(CCSWFNode::runAction);
}
void CCSWFNode::setRepeat(bool flag)
{
    this->repeat = flag;
}
bool CCSWFNode::getRepeat()
{
    return repeat;
}

//-(CGPoint) getTouchInMovieCoordinates:(UITouch*)touch
//{
//    // find the movie rect in pixels //
//    CGRect movieRect = CGRectMake(
//                                  self.position.x - (self.contentSize.width * super.scaleX * self.anchorPoint.x),
//                                  self.position.y - (self.contentSize.height * -super.scaleY * self.anchorPoint.y),
//                                  self.contentSize.width * super.scaleX,
//                                  self.contentSize.height * -super.scaleY
//                                  );
//    
//    // find the touch position in pixels //
//    CGPoint touchPoint = ccpMult([[CCDirector sharedDirector] convertToGL:[touch locationInView:[touch view]]], CC_CONTENT_SCALE_FACTOR());
//    
//    // find the touch position in respect to the movie //
//    CGPoint touchInMovie = ccp(
//                               (touchPoint.x - movieRect.origin.x) / m_scaleX,
//                               ((self.contentSize.height * -super.scaleY) - (touchPoint.y - movieRect.origin.y)) / m_scaleY
//                               );
//    
//    return touchInMovie;
//}

//- (BOOL)ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event
//{
//    // make rect for movie //
//    CGRect movieRect = CGRectMake(0, 0, (self.contentSize.width * super.scaleX), (self.contentSize.height * -super.scaleY));
//    // find the touch position in pixels //
//    CGPoint touchPoint = [self getTouchInMovieCoordinates:touch];
//    BOOL isInMovie = CGRectContainsPoint(movieRect, touchPoint);
//    [m_touchEvents addObject:[CCSWFNode_touchContainer touchContainerWithPosition:touchPoint andState:0]];
//    [m_touchEvents addObject:[CCSWFNode_touchContainer touchContainerWithPosition:touchPoint andState:1]];
//    return isInMovie;
//}
//
//- (void)ccTouchMoved:(UITouch *)touch withEvent:(UIEvent *)event
//{
//    [m_touchEvents addObject:[CCSWFNode_touchContainer touchContainerWithPosition:[self getTouchInMovieCoordinates:touch] andState:1]];
//}
//
//- (void)ccTouchEnded:(UITouch *)touch withEvent:(UIEvent *)event
//{
//    [m_touchEvents addObject:[CCSWFNode_touchContainer touchContainerWithPosition:[self getTouchInMovieCoordinates:touch] andState:0]];
//}
//
//- (void)ccTouchCancelled:(UITouch *)touch withEvent:(UIEvent *)event
//{
//    [m_touchEvents addObject:[CCSWFNode_touchContainer touchContainerWithPosition:[self getTouchInMovieCoordinates:touch] andState:0]];
//}

void CCSWFNode::update(float dt)
{
//    if (m_touchEvents.count)
//    {
//        CCSWFNode_touchContainer *touch = [m_touchEvents objectAtIndex:0];
//        imp->m_movie->notify_mouse_state(touch.position.x, touch.position.y, touch.state);
//        [m_touchEvents removeObjectAtIndex:0];
//    }
    bool tobestop = false;
    int iFrame = imp->m_movie->get_current_frame();
    if (m_listener && iFrame == iListenFrame) {
        (m_listener->*m_pfnSelector)(this);
    }
    if(! repeat){
        if (iFrame == iFrameCount - 1) {
            tobestop = true;
        }
    }
    imp->m_movie->advance(dt);
    
    if(tobestop){
        this->stopAction();
        if(m_endListener){
            (this->m_endListener->*m_pfnEndSelector)(this);
        }
    }

//    CCLOG(".....");
    // TODO: Enable sound //
    // sound->advance(dt);
}
#define STRINGIFY(A)  #A
const char* ColorVertexShader1 = STRINGIFY(
attribute vec4 a_position;
uniform mat4 Projection;
uniform mat4 u_MVPMatrix;
void main(void)
{
    vec4 tmp;
    tmp =  Projection * u_MVPMatrix * a_position;
//    tmp = u_MVPMatrix * a_position;
//    tmp = a_position;
    
    //    tmp.x *= -1.0;
//    tmp.y *= -1.0;
    gl_Position = tmp;
    
}
);

const char* ColorFragmentShader1 = STRINGIFY(
uniform lowp vec4 u_color;
                                            
void main(void)
{
    gl_FragColor = u_color;
}
);
unsigned int m_currentProgram = 0;

void ApplyOrtho(float maxX, float maxY)
{
    
    //        maxX = 1024*20/2;
    //        maxY = 768*20/2;
    float a = 1.0f / maxX;
    float b = 1.0f / maxY;
    float ortho[16] = {
        a, 0,  0, 0,
        0, b,  0, 0,
        0, 0, -1, 0,
        0, 0,  0, 1
    };
    
    GLint projectionUniform = glGetUniformLocation(m_currentProgram, "Projection");
    glUniformMatrix4fv(projectionUniform, 1, 0, &ortho[0]);
    CHECK_GL_ERROR_DEBUG();
}
void ApplyMatrix()
{
    float	mat[16]={
//        1.0f/512,    0,              0,              0,
//        0,              1.0f/384,    0,              0,
//        0,0,-0.000976562,   0,
//        -0.273438,-0.234375,0,1,
        
        1/512,0,0,0,
        0,-1/384,0,0,
        0,0,-1/1024,0,
//        0,0,0,1,
        -372,-474,0,1,
    };

    GLint modelviewUniform = glGetUniformLocation(m_currentProgram, "u_MVPMatrix");
    glUniformMatrix4fv(modelviewUniform, 1, 0, mat);
    CHECK_GL_ERROR_DEBUG();
}
static void ApplyColor()
{
    GLfloat color[4];
    {
        color[0] = 0.5;
        color[1] = 0.5;
        color[2] = 1.0;
        color[3] = 1.0;
    }
    
    GLint lineColorSlot = glGetUniformLocation(m_currentProgram, "u_color");
    glUniform4fv(lineColorSlot, 1, color);
    CHECK_GL_ERROR_DEBUG();
    
}
GLuint BuildShader(const char* source, GLenum shaderType)
{
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, 0);
    glCompileShader(shaderHandle);
    
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        printf("%s", messages);
        exit(1);
    }
    
    return shaderHandle;
}

GLuint BuildProgram(const char* vertexShaderSource,
                    const char* fragmentShaderSource) 
{
    GLuint vertexShader = BuildShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = BuildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        printf("%s", messages);
        
        exit(1);
    }
    
    return programHandle;
}
void render()
{
    m_currentProgram = BuildProgram(ColorVertexShader1, ColorFragmentShader1);
    CHECK_GL_ERROR_DEBUG();
    
    kmMat4 matrixP;
	kmMat4 matrixMV;
	kmMat4 matrixMVP;
	
	kmGLGetMatrix(KM_GL_PROJECTION, &matrixP );
	kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV );
	
	kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);
    
#if CC_ENABLE_GL_STATE_CACHE
    ccGLUseProgram(0);
#endif
    ApplyColor();
//    ApplyOrtho(512, 384);
//    ApplyMatrix();
    
    GLint projectionUniform = glGetUniformLocation(m_currentProgram, "Projection");
    glUniformMatrix4fv(projectionUniform, 1, 0, &matrixP.mat[0]);
    CHECK_GL_ERROR_DEBUG();

    GLint modelviewUniform = glGetUniformLocation(m_currentProgram, "u_MVPMatrix");
    glUniformMatrix4fv(modelviewUniform, 1, 0, &matrixMV.mat[0]);
    CHECK_GL_ERROR_DEBUG();
    
    GLuint positionSlot = glGetAttribLocation(m_currentProgram, "a_position");
    glEnableVertexAttribArray(positionSlot);
    float fcoords[8] ={
        80,-60,
        5680,-60,
        80,3540,
        5680,3540,
    };
    glVertexAttribPointer(positionSlot,2, GL_FLOAT,GL_FALSE, 0, fcoords);
    CHECK_GL_ERROR_DEBUG();
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CHECK_GL_ERROR_DEBUG();
}



void CCSWFNode::draw()
{
    if (! isRuning) {
        return;
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    kmMat4 matrixP;
	kmMat4 matrixMV;
	kmMat4 matrixMVP;
	
	kmGLGetMatrix(KM_GL_PROJECTION, &matrixP );
	kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV );
    kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);
    
#if CC_ENABLE_GL_STATE_CACHE
    ccGLUseProgram(0);//valid program is NON_ZERO unsigned int
#endif
	imp->m_movie->display(&matrixMVP.mat[0]);
    CHECK_GL_ERROR_DEBUG();

//    render();
    
    glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);

}

//@end
