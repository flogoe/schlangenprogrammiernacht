// You can use the entire C/C++ standard library, just add the relevant
// #includes. We recommend math.h ;-)

#include "usercode.h"
#include "math.h"
#include <string>


#define OTHER_SNEK_PANIC_DISTANCE 100
#define OTHER_SNEK_PANIC_ANGLE 1.6
/*
 * This is your bot's startup function. Here you can set your snake's colors,
 * set up persistent variables, etc.
 */
bool init(Api *api)
{
    // remove the default color
    api->clearColors();

    // robocolors
    api->addColor(0, 255, 0);
    api->addColor(0, 0, 0);
    api->addColor(0, 255, 0);
    api->addColor(255, 255, 255);

    // indicate successful startup. If anything goes wrong,
    // return false and we'll clean you up.
    return true;
}

/*
 * This function will be called by the framework on every step. Here you decide
 * where to move next!
 *
 * Use the provided Api object to interact with the world and make sure you set
 * the following outputs:
 *
 * - api->angle: Set your relative movement angle
 * - api->boost: Set this to true to move faster, but you will loose mass.
 *
 * The Api object also provides information about the world around you. See the
 * documentation for more details.
 */
bool step(Api *api)
{
    //get info about myself
    const IpcSelfInfo *self_info = api->getSelfInfo();
    api->log(std::to_string(self_info->mass).c_str());
    
    
    // get food list and steer towards nearest food
    const IpcFoodInfo* food_list = api->getFood();
    int food_length = api->getFoodCount();
    float angle_to_next_food = food_list[0].dir;
    api->angle = angle_to_next_food;
    
    // check for other snakes
    for(size_t i = 0; i < api->getSegmentCount(); i++) {
        const IpcSegmentInfo &seg = api->getSegments()[i];

        if(!seg.is_self && seg.dist < OTHER_SNEK_PANIC_DISTANCE && fabs(seg.dir) < OTHER_SNEK_PANIC_ANGLE) {
            //if we're here we are on collision course with another SNEK
            
            //steer away from the other SNEK
            if(seg.dir < 0){
                api->angle = 3.14;
            } else {
                api->angle = -3.14;
            }
            break;
        }
    }
    
    
    
    
    
    
    
    
    
    

    // Signal that everything is ok. Return false here if anything goes wrong but
    // you want to shut down cleanly.
    return true;
}



