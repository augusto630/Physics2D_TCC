#include <math.h>

/*
RETIRADO DE http://www.terathon.com/code/vector2d.html
*/

class Vector
{
    public:
    
        float   x;
        float   y;
        
        Vector() {x = 0;y = 0;}
        
        Vector(float x, float y)
        {
            Vector::x = x;
            Vector::y = y;
        }

        Vector& Set(float r, float s)
        {
            x = r;
            y = s;
            return (*this);
        }
        
        float& operator [](long k)
        {
            return ((&x)[k]);
        }
        
        const float& operator [](long k) const
        {
            return ((&x)[k]);
        }
        
        Vector& operator +=(const Vector& v)
        {
            x += v.x;
            y += v.y;
            return (*this);
        }
        
        Vector& operator -=(const Vector& v)
        {
            x -= v.x;
            y -= v.y;
            return (*this);
        }
        
        Vector& operator *=(float t)
        {
            x *= t;
            y *= t;
            return (*this);
        }
        
        Vector& operator /=(float t)
        {
            float f = 1.0F / t;
            x *= f;
            y *= f;
            return (*this);
        }
        
        Vector& operator &=(const Vector& v)
        {
            x *= v.x;
            y *= v.y;
            return (*this);
        }
        
        Vector operator -(void) const
        {
            return (Vector(-x, -y));
        }
        
        Vector operator +(const Vector& v) const
        {
            return (Vector(x + v.x, y + v.y));
        }
        
        Vector operator -(const Vector& v) const
        {
            return (Vector(x - v.x, y - v.y));
        }
        
        Vector operator *(float t) const
        {
            return (Vector(x * t, y * t));
        }
        
        Vector operator /(float t) const
        {
            float f = 1.0F / t;
            return (Vector(x * f, y * f));
        }
        
        float operator *(const Vector& v) const
        {
            return (x * v.x + y * v.y);
        }
        
        Vector operator &(const Vector& v) const
        {
            return (Vector(x * v.x, y * v.y));
        }
        
        bool operator ==(const Vector& v) const
        {
            return ((x == v.x) && (y == v.y));
        }
        
        bool operator !=(const Vector& v) const
        {
            return ((x != v.x) || (y != v.y));
        }
        
        Vector& Normalize(void)
        {
            return (*this /= sqrtf(x * x + y * y));
        }
        
        Vector& Rotate(float angle);
};


class Point : public Vector
{
    public:
        
        Point() {}
        
        Point(float r, float s) : Vector(r, s) {}
        
        Point& operator =(const Vector& v)
        {
            x = v.x;
            y = v.y;
            return (*this);
        }
        
        Point& operator *=(float t)
        {
            x *= t;
            y *= t;
            return (*this);
        }
        
        Point& operator /=(float t)
        {
            float f = 1.0F / t;
            x *= f;
            y *= f;
            return (*this);
        }
        
        Point operator -(void) const
        {
            return (Point(-x, -y));
        }
        
        Point operator +(const Vector& v) const
        {
            return (Point(x + v.x, y + v.y));
        }
        
        Point operator -(const Vector& v) const
        {
            return (Point(x - v.x, y - v.y));
        }
        
        Vector operator -(const Point& p) const
        {
            return (Vector(x - p.x, y - p.y));
        }
        
        Point operator *(float t) const
        {
            return (Point(x * t, y * t));
        }
        
        Point operator /(float t) const
        {
            float f = 1.0F / t;
            return (Point(x * f, y * f));
        }
};


inline Vector operator *(float t, const Vector& v)
{
    return (Vector(t * v.x, t * v.y));
}

inline Point operator *(float t, const Point& p)
{
    return (Point(t * p.x, t * p.y));
}

inline float Dot(const Vector& v1, const Vector& v2)
{
    return (v1 * v2);
}

inline float Magnitude(const Vector& v)
{
    return (sqrtf(v.x * v.x + v.y * v.y));
}

inline float InverseMag(const Vector& v)
{
    return (1.0F / sqrtf(v.x * v.x + v.y * v.y));
}

inline float SquaredMag(const Vector& v)
{
    return (v.x * v.x + v.y * v.y);
}


struct Origin_
{
    const Point& operator +(const Vector& v)
    {
        return (static_cast<const Point&>(v));
    }
    
    Point operator -(const Vector& v)
    {
        return (Point(-v.x, -v.y));
    }
};


extern Origin_ Origin;