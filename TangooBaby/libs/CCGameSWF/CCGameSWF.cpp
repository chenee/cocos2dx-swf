//
//  CCGameSWF.m
//  CCGameSWF
//
//  Created by dario on 13-02-22.
//  Modify by chenee (chenee543216@gmail.com) on 13-05-20
//  @chenee: 1\change Objective-C to C++ ;2\change opengl es 1.1 to opengl es 2.0
//
//

#import "CCGameSWF.h"
#import "CCGameSWF.h"
#import "gameswf.h"
#import "gameswf_character.h"
#import "tu_file.h"

using namespace cocos2d;

#pragma mark - Callback declarations
// handler functions //
static void     CCGameSWF_fscommand_handler     (gameswf::character* movie, const char* command, const char* arg);  // fscommand handler //
static tu_file* CCGameSWF_file_opener           (const char* url_or_path);                                          // file opener //
static void     CCGameSWF_log_handler           (bool error, const char* message);                                  // log handler //

#pragma mark - CCGameSWF implementation
//@implementation CCGameSWF

CCGameSWF* CCGameSWF::sharedInstance()
{
    static CCGameSWF *s_ccGameSWF_sharedInstance = NULL;
    if (!s_ccGameSWF_sharedInstance)
    {
        s_ccGameSWF_sharedInstance = new CCGameSWF();
        s_ccGameSWF_sharedInstance->init();
    }
    return s_ccGameSWF_sharedInstance;
}

bool CCGameSWF::init()
{
//    self = [super init];
//    if (self)
//    {
//        m_fscommandListeners = [[NSMutableDictionary alloc] init];
        m_fscommandListeners  = new cocos2d::CCArray();
        gameswf::register_file_opener_callback(&CCGameSWF_file_opener);
        gameswf::register_fscommand_callback(&CCGameSWF_fscommand_handler);
#ifdef DEBUG
        gameswf::register_log_callback(&CCGameSWF_log_handler);
#endif
        
        // TODO: Enable audio //
        //    sound = gameswf::create_sound_handler_openal();
        //    gameswf::set_sound_handler(sound);
        gameswf::set_sound_handler(0);
        
        gameswf::render_handler* render = gameswf::create_render_handler_ogles();
        gameswf::set_render_handler(render);
        
        gameswf::set_glyph_provider(gameswf::create_glyph_provider_tu());
//    }
	
//	return self;
    return true;
}

void CCGameSWF::dealloc()
{
//    [m_fscommandListeners release];
    m_fscommandListeners->release();
    
//    [super dealloc];
}

#pragma mark - fscommand handlers
//void addFscommandResponder:(id<CCSWFFscommandResponder>)responder forMovieNamed:(NSString*)movieName
//{
//    NSMutableArray *movieResponders = [m_fscommandListeners objectForKey:movieName];
//    if (!movieResponders)
//    {
//        movieResponders = [NSMutableArray array];
//        [m_fscommandListeners setObject:movieResponders forKey:movieName];
//    }
//    
//    [movieResponders addObject:responder];
//}
//
//-(void) removeFscommandResponder:(id<CCSWFFscommandResponder>)responder forMovieNamed:(NSString*)movieName
//{
//    NSMutableArray *movieResponders = [m_fscommandListeners objectForKey:movieName];
//    if (!movieResponders)
//    {
//        NSLog(@"ERROR: trying to remove fscommand responder from empty responder list, did you pass the correct movie name?");
//        return;
//    }
//    
//    [movieResponders removeObject:responder];
//    
//    if ([movieResponders count] == 0)
//    {
//        [m_fscommandListeners removeObjectForKey:movieName];
//    }
//}

//void movieNamed:(NSString*)movieName sentCommand:(NSString*)command withArguments:(NSString*)args
////void movieNamedSentCommandWithArguments(CCString* movieName,CCString*command,CCString*args)
//{
//    NSMutableArray *movieResponders = [m_fscommandListeners objectForKey:movieName];
//    if (movieResponders)
//    {
//        for (int i = 0; i < [movieResponders count]; ++i)
//        {
//            id<CCSWFFscommandResponder> responder = [movieResponders objectAtIndex:i];
//            if ([responder respondsToSelector:@selector(movieNamed:sentCommand:withArguments:)])
//            {
//                [responder movieNamed:movieName sentCommand:command withArguments:args];
//            }
//        }
//    }
//}
//
//@end


#pragma mark - Callback implementations

void CCGameSWF_fscommand_handler (gameswf::character* movie, const char* command, const char* arg)
{
//    [[CCGameSWF sharedInstance] movieNamed:[NSString stringWithUTF8String:movie->m_name.c_str()] sentCommand:[NSString stringWithUTF8String:command] withArguments:[NSString stringWithUTF8String:arg]];
    
}

tu_file* CCGameSWF_file_opener (const char* url_or_path)
{
    assert(url_or_path);
	if (strncasecmp(url_or_path, "http://", 7) == 0)
	{
//		const char* slash = strchr(url_or_path + 7, '/');
//		if (slash == NULL)
//		{
//			return NULL;
//		}
//		
//		char host[256];
//		memset(host, 0, 256);
//		strncpy(host, url_or_path + 7, slash - url_or_path - 7);
//		
//		int len = 0;
//		const void* data = NULL;
//		tu_string swfile;
//		tu_string hisfile;
//		
//		NSString* swfFile = [NSString stringWithFormat: @"%@/Documents/my.swf", NSHomeDirectory()];
//		swfile = [swfFile UTF8String];
//		NSString* hisFile = [NSString stringWithFormat: @"%@/Documents/his.txt", NSHomeDirectory()];
//		hisfile = [hisFile UTF8String];
//		NSString* hostName = [NSString stringWithUTF8String: host];
//		NSString* pathToFile= [NSString stringWithUTF8String: slash];
//		NSURL* fileURL = [[NSURL alloc] initWithScheme:@"http" host:hostName path:pathToFile];
//		if (fileURL)
//		{
//			NSData* fileContents = [NSData dataWithContentsOfURL:fileURL];
//			if (fileContents)
//			{
//				len = [fileContents length];
//				data = [fileContents bytes];
//			}
//			else
//			{
//				return NULL;
//			}
//		}
//		else
//		{
//			return NULL;
//		}
//		
//		// write swf
//		{
//			tu_file fi(swfile.c_str(), "wb");
//			fi.write_bytes(data, len);
//		}
//		
//		// update history
//		
//		// read history
//		array<tu_string> his;
//		{
//			tu_file fi(hisfile.c_str(), "r");
//			if (fi.get_error() == TU_FILE_NO_ERROR)
//			{
//				char buf[1024];
//				while (fi.read_string(buf, 1024) > 1)	// !!!!
//				{
//					his.push_back(buf);
//				}
//			}
//		}
//		
//		// test for same
//		bool is_new = true;
//		for (int i = 0; i < his.size(); i++)
//		{
//			if (his[i] == url_or_path + 7)
//			{
//				is_new = false;
//				break;
//			}
//		}
//		
//		// append new item
//		if (is_new)
//		{
//			his.push_back(url_or_path + 7);
//		}
//		
//		// truncate to 20
//		while (his.size() > 20)
//		{
//			his.remove(0);
//		}
//		
//		// save history
//		{
//			tu_file fi(hisfile.c_str(), "w");
//			for (int i = 0; i < his.size(); i++)
//			{
//				fi.write_string(his[i].c_str());
//				fi.write_string("\n");
//			}
//		}
//        //	printf("%s as %s\n", url, swfile.c_str());
//		return new tu_file(swfile.c_str(), "rb");
	}
	return new tu_file(url_or_path, "rb");
}

static void CCGameSWF_log_handler (bool error, const char* message)
{
//    NSLog(@"%@: %s", (error ? @"::ERROR: " : @":::: "), message);

    if (error) {
        CCLOG("::ERROR:: %s",message);
    }else{
        CCLOG(":::: %s",message);
    }
}



