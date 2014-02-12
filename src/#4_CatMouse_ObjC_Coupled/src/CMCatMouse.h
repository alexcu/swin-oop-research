// Include parent for both animals, CMAnimal
#include "CMAnimal.h"
#import <Foundation/Foundation.h>

/**
 * @class   CMCat
 * @author  Alex Cummaudo
 * @date    24 Oct 2013
 * @brief   Defines an class for a playable
 *          chaser (i.e. the chasing cat)
 */

// No extra encapsulation
@interface CMCat : CMAnimal @end


/**
 * @class   CMMouse
 * @author  Alex Cummaudo
 * @date    18 Oct 2013
 * @brief   Defines an class for a playable
 *          chasee (i.e. the hunted mouse)
 */

// No extra encapsulation
@interface CMMouse : CMAnimal @end
