#include "qbpch.h"
#include "Font.h"

#undef INFINITE
#include "msdf-atlas-gen.h"
#include "FontGeometry.h"
#include "GlyphGeometry.h"

#include "MSDFData.h"

namespace Qbit {

	Font::Font(const std::filesystem::path& font)
	{
        if (msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype()) {
            if (msdfgen::FontHandle* font = loadFont(ft, "C:\\Windows\\Fonts\\arialbd.ttf")) {
                msdfgen::Shape shape;
                if (loadGlyph(shape, font, 'A', msdfgen::FONT_SCALING_EM_NORMALIZED)) {
                    shape.normalize();
                    //                      max. angle
                    edgeColoringSimple(shape, 3.0);
                    //          output width, height
                    msdfgen::Bitmap<float, 3> msdf(32, 32);
                    //                            scale, translation (in em's)
                    msdfgen::SDFTransformation t(msdfgen::Projection(32.0, msdfgen::Vector2(0.125, 0.125)), msdfgen::Range(0.125));
                    generateMSDF(msdf, shape, t);
                    msdfgen::savePng(msdf, "output.png");
                }
                destroyFont(font);
            }
            deinitializeFreetype(ft);
        }
	}



}