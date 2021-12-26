#ifndef SKY_COMPONENT_H
#define SKY_COMPONENT_H

#include "buffer/Buffer.h"
#include "texture/Texture.h"

namespace Supernova{

    struct SkyComponent{
        bool loaded = false;

        Buffer* buffer;

        Matrix4 skyViewProjectionMatrix;

        ObjectRender render;
        std::shared_ptr<ShaderRender> shader;
        int slotVSParams = -1;

        Texture texture;

        bool needUpdateTexture = false;
    };
    
}

#endif //SKY_COMPONENT_H