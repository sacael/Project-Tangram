// FAUVET
// v3.hpp
// Classe basique de vecteurs 3D

#ifndef _v3_HPP_
#define _v3_HPP_

#include <math.h>

#ifndef M_PI
#   define M_PI 3.14159f
#endif

class v3
{
public:
    // constructors
    v3()                                {v[0] = v[1] = v[2] = 0;}
    v3(float px, float py, float pz)    {v[0] = px; v[1] = py; v[2] = pz;}
    v3(const v3 &pVec)                  {v[0] = pVec.v[0]; v[1] = pVec.v[1]; v[2] = pVec.v[2];}
    v3(const float *pVec)               {v[0] = pVec[0]; v[1] = pVec[1]; v[2] = pVec[2];}

   
    // assign / equality / greater / less / etc
    //inline v3 operator=(const v3 &pVec)              {return v3(v[0] = pVec.v[0], v[1] = pVec.v[1], v[2] = pVec.v[2]);}
    //inline v3 operator=(const float *ptr)            {return v3(v[0] = ptr[0], v[1] = ptr[1], v[2] = ptr[2]);}
    inline v3 &operator=(const v3 &pVec)            {v[0] = pVec.v[0]; v[1] = pVec.v[1]; v[2] = pVec.v[2]; return (*this);}
    inline v3 &operator=(const float *ptr)          {v[0] = ptr[0]; v[1] = ptr[1]; v[2] = ptr[2]; return (*this);}
    inline bool operator==(const v3 &pVec) const    {return (v[0] == pVec.v[0] && v[1] == pVec.v[1] && v[2] == pVec.v[2]);}
    inline bool operator==(const float *pVec) const {return (v[0] == pVec[0] && v[1] == pVec[1] && v[2] == pVec[2]);}
    inline bool operator!=(const v3 &pVec) const    {return !((*this) == pVec);}
    inline bool operator!=(const float *pVec)       {return !((*this) == pVec);}
    inline bool operator<(const v3 vec) const       {return ((v[0] < vec[0]) && (v[1] < vec[1]) && (v[2] < vec[2]));}
    inline bool operator<=(const v3 vec) const      {return ((v[0] <= vec[0]) && (v[1] <= vec[1]) && (v[2] <= vec[2]));}
    inline bool operator>(const v3 vec) const       {return ((v[0] > vec[0]) && (v[1] > vec[1]) && (v[2] > vec[2]));}
    inline bool operator>=(const v3 vec) const      {return ((v[0] >= vec[0]) && (v[1] >= vec[1]) && (v[2] >= vec[2]));}

    // indexing into the array, no bound checks
    inline const float &operator[](int ndx) const   {return v[ndx];}
    inline float &operator[](int ndx)               {return v[ndx];}
    inline operator float*(void)                    {return static_cast<float*>(&v[0]);}
    inline float GetX()                             { return v[0]; }   
    inline float GetY()                             { return v[1]; }
    inline float GetZ()                             { return v[2]; }
    inline void SetX(float x)                       { v[0] = x; }
    inline void SetY(float y)                       { v[1] = y; }
    inline void SetZ(float z)                       { v[2] = z; }
    inline void Clear(void)                         {v[0] = v[1] = v[2] = 0;}
    inline void Set(float x, float y, float z)      {v[0] = x; v[1] = y; v[2] = z;}
    inline void Set(const v3 &p)                    {v[0] = p[0]; v[1] = p[1]; v[2] = p[2];}
           
    // + - / * operations
    inline v3 &operator+=(const v3 &pVec)   {*this = *this + pVec; return *this;}
    inline v3 &operator-=(const v3 &pVec)   {*this = *this - pVec; return *this;}
    inline v3 &operator*=(const v3 &pVec)   {*this = *this * pVec; return *this;}
    inline v3 &operator*=(float val)        {*this = *this * val; return *this;}
    inline v3 &operator/=(const v3 &pVec)   {*this = *this / pVec; return *this;}
    inline v3 &operator/=(float val)        {*this = *this / val; return *this;}

    inline v3 operator+(const v3 &pVec) const           {return v3(v[0] + pVec.v[0], v[1] + pVec.v[1], v[2] + pVec.v[2]);}
    inline v3 operator-(const v3 &pVec) const           {return v3(v[0] - pVec.v[0], v[1] - pVec.v[1], v[2] - pVec.v[2]);}
    inline v3 operator*(const v3 &pVec) const           {return v3(v[0] * pVec.v[0], v[1] * pVec.v[1], v[2] * pVec.v[2]);}
    inline v3 operator*(float val) const                {return v3(v[0] * val, v[1] * val, v[2] * val);}
    inline friend v3 operator*(float val, const v3 &v)  {return v3(v[0] * val, v[1] * val, v[2] * val);}
    inline v3 operator/(const v3 &pVec) const           {return v3(v[0] / pVec.v[0], v[1] / pVec.v[1], v[2] / pVec.v[2]);}
    inline v3 operator/(float val) const                {return v3(v[0] / val, v[1] / val, v[2] / val);}
    inline v3 operator-(void) const                     {return v3(-v[0], -v[1], -v[2]);} 

    // + - * / operations that don't return a v3
    // There are here so we don't get killed for speed
    inline void Add(const v3 &a, const v3 &b)       {v[0] = a.v[0] + b.v[0]; v[1] = a.v[1] + b.v[1]; v[2] = a.v[2] + b.v[2];}
    inline void Add(const v3 &a)                    {v[0] += a.v[0]; v[1] += a.v[1]; v[2] += a.v[2];}
    inline void Subtract(const v3 &a, const v3 &b)  {v[0] = a.v[0] - b.v[0]; v[1] = a.v[1] - b.v[1]; v[2] = a.v[2] - b.v[2];}
    inline void Subtract(const v3 &a)               {v[0] -= a.v[0]; v[1] -= a.v[1]; v[2] -= a.v[2];}
    inline void Multiply(const v3 &a, const v3 &b)  {v[0] = a.v[0] * b.v[0]; v[1] = a.v[1] * b.v[1]; v[2] = a.v[2] * b.v[2];}
    inline void Multiply(const v3 &a)               {v[0] *= a.v[0]; v[1] *= a.v[1]; v[2] *= a.v[2];}
    inline void Divide(const v3 &a, const v3 &b)    {v[0] = a.v[0] / b.v[0]; v[1] = a.v[1] / b.v[1]; v[2] = a.v[2] / b.v[2];}
    inline void Divide(const v3 &a)                 {v[0] /= a.v[0]; v[1] /= a.v[1]; v[2] /= a.v[2];}
    inline void Scale(float val)                    {v[0] *= val; v[1] *= val; v[2] *= val;}
    inline void Fabs(const v3 &src)                 {v[0] = (float) fabs(src.v[0]); v[1] = (float) fabs(src.v[1]); v[2] = (float) fabs(src.v[2]);}
    inline void Fabs(void)                          {v[0] = (float) fabs(v[0]); v[1] = (float) fabs(v[1]); v[2] = (float) fabs(v[2]);}


    void Normalize(void);
    float Length(void) const;
    float Dot(const v3 &pVec) const;
    v3 operator^(const v3 &q) const;
    void Cross(const v3 &p, const v3 &q);
    void Clamp(float min, float max);

    float GetDistance(const v3 &dest) const;

   //protected:
    float v[3];
};

inline void v3::Normalize(void) 
{
	float length;

	length = Length();

	if (length == 0)
		return;

	length = 1.0f / length;

	v[0] *= length;
	v[1] *= length;
	v[2] *= length;
}

inline float v3::Length(void) const
{
    double length = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
    return (float) sqrt(length);
}

inline float v3::Dot(const v3 &pVec) const  
{
    return v[0] * pVec.v[0] + v[1] * pVec.v[1] + v[2] * pVec.v[2];
}

inline v3 v3::operator^(const v3 &q) const
{
    v3 V(  (v[1] * v[2]) - (v[2] * q.v[1]),
                (v[2] * v[0]) - (v[0] * q.v[2]),
                (v[0] * v[1]) - (v[1] * q.v[0]));    
    return V;
}
    
inline void v3::Cross(const v3 &p, const v3 &q)
{
	v[0] = (p.v[1] * q.v[2]) - (p.v[2] * q.v[1]);
	v[1] = (p.v[2] * q.v[0]) - (p.v[0] * q.v[2]);
	v[2] = (p.v[0] * q.v[1]) - (p.v[1] * q.v[0]);
}

inline void v3::Clamp(float min, float max)
{
   if (v[0] > max)
      v[0] = v[0] - max;
   if (v[0] < min)
      v[0] = min - v[0];
   if (v[1] > max)
      v[1] = v[1] - max;
   if (v[1] < min)
      v[1] = min - v[1];
   if (v[2] > max)
      v[2] = v[2] - max;
   if (v[2] < min)
      v[2] = min - v[2];
}

inline float v3::GetDistance(const v3 &dest) const
{
   float d1 = dest[0] - v[0];
   float d2 = dest[1] - v[1];
   float d3 = dest[2] - v[2];
   
   return (float) sqrt((d1 * d1) + (d2 * d2) + (d3 * d3));
}

#endif
