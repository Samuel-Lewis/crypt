
#include "lbLog.h"
#include "lbRNG.h"

#include "Region.h"
#include "Farm.h"

#include "Tile.h"

#include "House.h"

Farm::Farm() {}
Farm::Farm(int newWidth, int newHeight, float density): Region(newWidth, newHeight, density, "Farm")
{
    
    // Set standard background tile, with random chance of ocassional tree
    for (int x = 0; x < width(); x++)
    {
        for (int y = 0; y < height(); y++)
        {
            if (lbRNG::linear(0.0,1.0) < 0.02)
            {
                replace(x,y, new Tile("grass-light","tree-light"));
            } else {
                replace(x,y, new Tile("grass-light"));
            }
            
        }
    }

    int barnWidth = lbRNG::normDist(6, 1);
    int barnHeight = lbRNG::normDist(barnWidth, 1);
    
    int barnStartX = lbRNG::normDist((width()-barnWidth)/2, 8);
    int barnStartY = lbRNG::normDist((height()-barnHeight)/2, 8);
    
    House* barn = new House(barnWidth, barnHeight);
    
    replace(barnStartX, barnStartY, barn, true);
    
   
    int fieldWidth = barnWidth;
    int fieldHeight = barnHeight;
    
    int fieldStartX = barnStartX;
    int fieldStartY = barnStartY;
    
    // Work out what corner the barn is sitting in
    if (barnStartX+barnWidth/2 < width()/2 && barnStartY+barnHeight/2 < height()/2)
    {
        // Top left
        if (lbRNG::linear(0,1))
        {
            // Field goes right
            fieldWidth = lbRNG::normDist(6,1);
            fieldStartX += barnWidth;
        } else {
            // Field goes down
            fieldHeight = lbRNG::normDist(4,1);
            fieldStartY += barnHeight;
        }
        
    } else if (barnStartX+barnWidth/2 > width()/2 && barnStartY+barnHeight/2 < height()/2) {
        // Top right
        if (lbRNG::linear(0,1))
        {
            // Field goes left
            fieldWidth = lbRNG::normDist(6,1);
            fieldStartX -= fieldWidth;
        } else {
            // Field goes down
			fieldHeight = lbRNG::normDist(6,1);
            fieldStartY += barnHeight;
        }
        
    } else if (barnStartX+barnWidth/2 < width()/2 && barnStartY+barnHeight/2 > height()/2) {
        // Bottom left
        if (lbRNG::linear(0,1))
        {
            // Field goes up
            fieldHeight = lbRNG::normDist(6,1);
            fieldStartY -= fieldHeight;
            
        } else {
            // Field goes right
            fieldWidth = lbRNG::normDist(6,1);
            fieldStartX += barnWidth;
        }
        
    } else {
        // Bottom right
        if (lbRNG::linear(0,1))
        {
            // Field goes up
            fieldHeight = lbRNG::normDist(6,1);
            fieldStartY -= fieldHeight;
            
        } else {
            // Field goes left
            fieldWidth = lbRNG::normDist(6,1);
            fieldStartX -= fieldWidth;
        }
    }
    
    // Place down field
    for (int x = fieldStartX; x < fieldStartX+fieldWidth; x++)
    {
        for (int y = fieldStartY; y < fieldStartY+fieldHeight; y++)
        {
               replace(x,y,new Tile("field-light"));
        }
    }
    
	INFO("Generated Farm");
}
