#ifndef RENDERLIST_H
#define RENDERLIST_H

#include <vector>
#include <iostream>

#include "Renderable.h"

class RenderList {
    
    public:
        
        RenderList();
        
        virtual ~RenderList();
        
        bool hasNext();
        
        Renderable* getNext();
        
        void reset();
        
        
        void addRenderable(Renderable*); //remember to make thread safe
        
        void removeRenderable(Renderable*);
        
        void clearList();
        
    
    protected:
    
    
    private:
        
        void destroyRenderable(Renderable* renderable);
        
        unsigned int index; //counter used to cycle through the renderables each frame
        
        std::vector<Renderable*> opaqueRenderables;
        
        std::vector<Renderable*> transparentRenderables;
        
        std::vector<Renderable*> toBeAdded;
        
        std::vector<Renderable*> toBeRemoved;
};

#endif // RENDERLIST_H
