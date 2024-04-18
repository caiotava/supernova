//
// (c) 2024 Eduardo Doria.
//

#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "Image.h"
#include "Text.h"
#include "Container.h"

namespace Supernova{
    class Scrollbar: public Image{

    public:
        Scrollbar(Scene* scene);

        Image getBarObject() const;

        void setBarTexture(std::string path);
        void setBarTexture(Framebuffer* framebuffer);

        void setBarColor(Vector4 color);
        void setBarColor(const float red, const float green, const float blue, const float alpha);
        void setBarColor(const float red, const float green, const float blue);
        void setBarAlpha(const float alpha);
        Vector4 getBarColor() const;
        float getBarAlpha() const;
    };
}

#endif //SCROLLBAR_H