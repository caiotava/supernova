//
// (c) 2022 Eduardo Doria.
//

#include "LuaBinding.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "sol.hpp"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Rect.h"

using namespace Supernova;

void LuaBinding::registerMathClasses(lua_State *L){
    sol::state_view lua(L);

    lua.new_usertype<Vector2>("Vector2",
        sol::constructors<Vector2(), Vector2(float, float)>(),
        "x", &Vector2::x,
        "y", &Vector2::y,
        sol::meta_function::to_string, &Vector2::toString,
        sol::meta_function::index, [](Vector2& v, const int index) { if (index < 0 or index > 1) return 0.0f; return v[index]; },
        sol::meta_function::new_index, [](Vector2& v, const int index, double x) { if (index < 0 or index > 1) return; v[index] = x; },
        sol::meta_function::equal_to, &Vector2::operator==,
        sol::meta_function::less_than, &Vector2::operator<,
        sol::meta_function::subtraction, sol::resolve<Vector2(const Vector2&) const>(&Vector2::operator-),
        sol::meta_function::addition, sol::resolve<Vector2(const Vector2&) const>(&Vector2::operator+),
        sol::meta_function::division, sol::resolve<Vector2(float) const>(&Vector2::operator/),
        sol::meta_function::multiplication, sol::overload( sol::resolve<Vector2(const Vector2&) const>(&Vector2::operator*), sol::resolve<Vector2(float) const>(&Vector2::operator*) ),
        sol::meta_function::unary_minus, sol::resolve<Vector2() const>(&Vector2::operator-),
        "swap", &Vector2::swap,
        "length", &Vector2::length,
        "squaredLength", &Vector2::squaredLength,
        "distance", &Vector2::distance,
        "squaredDistance", &Vector2::squaredDistance,
        "dotProduct", &Vector2::dotProduct,
        "normalize", &Vector2::normalize,
        "midPoint", &Vector2::midPoint,
        "makeFloor", &Vector2::makeFloor,
        "makeCeil", &Vector2::makeCeil,
        "perpendicular", &Vector2::perpendicular,
        "crossProduct", &Vector2::crossProduct,
        "normalizedCopy", &Vector2::normalizedCopy,
        "reflect", &Vector2::reflect
        );

    lua.new_usertype<Vector3>("Vector3",
        sol::constructors<Vector3(), Vector3(float, float, float)>(),
        "x", &Vector3::x,
        "y", &Vector3::y,
        "z", &Vector3::z,
        sol::meta_function::to_string, &Vector3::toString,
        sol::meta_function::index, [](Vector3& v, const int index) { if (index < 0 or index > 2) return 0.0f; return v[index]; },
        sol::meta_function::new_index, [](Vector3& v, const int index, double x) { if (index < 0 or index > 2) return; v[index] = x; },
        sol::meta_function::equal_to, &Vector3::operator==,
        sol::meta_function::less_than, &Vector3::operator<,
        sol::meta_function::subtraction, sol::resolve<Vector3(const Vector3&) const>(&Vector3::operator-),
        sol::meta_function::addition, sol::resolve<Vector3(const Vector3&) const>(&Vector3::operator+),
        sol::meta_function::division, sol::resolve<Vector3(float) const>(&Vector3::operator/),
        sol::meta_function::multiplication, sol::overload( sol::resolve<Vector3(const Vector3&) const>(&Vector3::operator*), sol::resolve<Vector3(float) const>(&Vector3::operator*) ),
        sol::meta_function::unary_minus, sol::resolve<Vector3() const>(&Vector3::operator-),
        //sol::meta_function::modulus, &Vector3::operator%
        "length", &Vector3::length,
        "squaredLength", &Vector3::squaredLength,
        "dotProduct", &Vector3::dotProduct,
        "absDotProduct", &Vector3::absDotProduct,
        "distance", &Vector3::distance,
        "squaredDistance", &Vector3::squaredDistance,
        "normalize", &Vector3::normalize,
        "normalizeL", &Vector3::normalizeL,
        "crossProduct", &Vector3::crossProduct,
        "midPoint", &Vector3::midPoint,
        "makeFloor", &Vector3::makeFloor,
        "makeCeil", &Vector3::makeCeil,
        "perpendicular", &Vector3::perpendicular
        );

    lua.new_usertype<Vector4>("Vector4",
        sol::constructors<Vector4(), Vector4(float, float, float, float)>(),
        "x", &Vector4::x,
        "y", &Vector4::y,
        "z", &Vector4::z,
        "w", &Vector4::w,
        sol::meta_function::to_string, &Vector4::toString,
        sol::meta_function::index, [](Vector4& v, const int index) { if (index < 0 or index > 2) return 0.0f; return v[index]; },
        sol::meta_function::new_index, [](Vector4& v, const int index, double x) { if (index < 0 or index > 2) return; v[index] = x; },
        sol::meta_function::equal_to, &Vector4::operator==,
        sol::meta_function::less_than, &Vector4::operator<,
        sol::meta_function::subtraction, sol::resolve<Vector4(const Vector4&) const>(&Vector4::operator-),
        sol::meta_function::addition, sol::resolve<Vector4(const Vector4&) const>(&Vector4::operator+),
        sol::meta_function::division, sol::resolve<Vector4(float) const>(&Vector4::operator/),
        sol::meta_function::multiplication, sol::overload( sol::resolve<Vector4(const Vector4&) const>(&Vector4::operator*), sol::resolve<Vector4(float) const>(&Vector4::operator*) ),
        sol::meta_function::unary_minus, sol::resolve<Vector4() const>(&Vector4::operator-),
        "swap", &Vector4::swap,
        "divideByW", &Vector4::divideByW,
        "dotProduct", &Vector4::dotProduct,
        "isNaN", &Vector4::isNaN
        );

    lua.new_usertype<Rect>("Rect",
        sol::constructors<Rect(), Rect(float, float, float, float)>(),
        "x", sol::property(&Rect::getX),
        "y", sol::property(&Rect::getY),
        "width", sol::property(&Rect::getWidth),
        "height", sol::property(&Rect::getHeight),
        sol::meta_function::to_string, &Rect::toString,
        sol::meta_function::equal_to, &Rect::operator==,
        "getVector", &Rect::getVector,
        "setRect", sol::overload( sol::resolve<void(float, float, float, float)>(&Rect::setRect), sol::resolve<void(Rect)>(&Rect::setRect) ),
        "fitOnRect", &Rect::fitOnRect,
        "isNormalized", &Rect::isNormalized,
        "isZero", &Rect::isZero
        );

    lua.new_usertype<Matrix3>("Matrix3",
        sol::constructors<Matrix3(), Matrix3(float, float, float, float, float, float, float, float, float)>(),
        sol::meta_function::to_string, &Matrix3::toString,
        //sol::meta_function::index, [](Matrix3& v, const int index) { if (index < 0 or index > 2) return 0.0f; return v[index]; },
        //sol::meta_function::new_index, [](Matrix3& v, const int index, double x) { if (index < 0 or index > 2) return; v[index] = x; },
        sol::meta_function::equal_to, &Matrix3::operator==,
        sol::meta_function::subtraction, sol::resolve<Matrix3(const Matrix3&) const>(&Matrix3::operator-),
        sol::meta_function::addition, sol::resolve<Matrix3(const Matrix3&) const>(&Matrix3::operator+),
        sol::meta_function::multiplication, sol::overload( sol::resolve<Matrix3(const Matrix3&) const>(&Matrix3::operator*), sol::resolve<Vector3(const Vector3 &) const>(&Matrix3::operator*) )
        );
}