#include "RenderList.h"

#include <algorithm>

RenderList::RenderList(){
    
}

RenderList::~RenderList(){
    
}

bool RenderList::hasNext(){
    return this->index < opaqueRenderables.size() + transparentRenderables.size();
}


Renderable* RenderList::getNext(){
    if(index < opaqueRenderables.size()){
        index++;
        return opaqueRenderables.at(index - 1);
    }else if(index < opaqueRenderables.size() + transparentRenderables.size()){
        index++;
        return transparentRenderables.at(index - opaqueRenderables.size() - 1);
    }
    std::cerr << "Attempted to get too many Renderables, getNext called while hasNext is false" << std::endl;
    return NULL;
}


void RenderList::reset(){
    this->index = 0;
    //grab new renderables in thread safe way here if nessesary
    //also delete old renderables
    Renderable* ren;
    while(!this->toBeAdded.empty()){
        ren = toBeAdded.at(toBeAdded.size() - 1);
        toBeAdded.pop_back();
        if(ren->isOpaque()){
            this->opaqueRenderables.push_back(ren);
        }else{
            this->transparentRenderables.push_back(ren);
        }
    }
    
    while(!this->toBeRemoved.empty()){
        ren = toBeRemoved.at(toBeRemoved.size() - 1);
        toBeRemoved.pop_back();
        destroyRenderable(ren);
    }
}


void RenderList::addRenderable(Renderable* renderable){
    toBeAdded.push_back(renderable);
}


void RenderList::removeRenderable(Renderable* renderable){
    toBeRemoved.push_back(renderable);
}


void RenderList::destroyRenderable(Renderable* renderable){
    std::vector<Renderable*>* rList = renderable->isOpaque() ? &opaqueRenderables : &transparentRenderables;
    rList->erase(std::remove(rList->begin(), rList->end(), renderable), rList->end());
}







