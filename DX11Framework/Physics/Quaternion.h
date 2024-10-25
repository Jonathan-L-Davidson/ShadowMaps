#ifndef H_QUATERNION
#define H_QUATERNION

#define _USE_MATH_DEFINES
#include <math.h>
#include "Core.h"
#include "Vector3.h"

namespace Physics {
    //------------------------------------------------------------------------
    // Quaternion Class and Quaternion functions
    //------------------------------------------------------------------------

    class Quaternion {
    public:
        float      n;     // number (scalar) part
        Vector3    v;     // vector part: v.x, v.y, v.z

        Quaternion(void);
        Quaternion(float e0, float e1, float e2, float e3);
        Quaternion(Vector3 _v);

        float      Magnitude(void);
        float      MagnitudeSquared(void);
        Vector3    GetVector(void);
        float      GetScalar(void);
        void       Normalise(void);
        Quaternion operator+=(Quaternion q);
        Quaternion operator-=(Quaternion q);
        Quaternion operator*=(float s);
        Quaternion operator/=(float s);
        Quaternion operator~(void) const;
    };

    // Default Constructor
    inline Quaternion::Quaternion(void)
    {
        n = 1;
        v.x = 0;
        v.y = 0;
        v.z = 0;
    }

    // Constructor
    inline Quaternion::Quaternion(float e0, float e1, float e2, float e3)
    {
        n = e0;
        v.x = e1;
        v.y = e2;
        v.z = e3;
    }
    
    // Constructor
    inline Quaternion::Quaternion(Vector3 _v)
    {
        n = 1;
        v = _v;
    }

    inline float Quaternion::Magnitude(void)
    {
        return (float)sqrt(n * n + v.x * v.x + v.y * v.y + v.z * v.z);
    }

    inline float Quaternion::MagnitudeSquared(void)
    {
        return (float)n * n + v.x * v.x + v.y * v.y + v.z * v.z;
    }

    inline Vector3 Quaternion::GetVector(void)
    {
        return Vector3(v.x, v.y, v.z);
    }

    inline float Quaternion::GetScalar(void)
    {
        return n;
    }
   
    inline void Quaternion::Normalise(void)
    {
        real d = static_cast<float>(1.0) / MagnitudeSquared();
        n *= d;
        v.x *= d;
        v.y *= d;
        v.z *= d;
    }

    inline Quaternion Quaternion::operator+=(Quaternion q)
    {
        n += q.n;
        v.x += q.v.x;
        v.y += q.v.y;
        v.z += q.v.z;
        return *this;
    }

    inline Quaternion Quaternion::operator-=(Quaternion q)
    {
        n -= q.n;
        v.x -= q.v.x;
        v.y -= q.v.y;
        v.z -= q.v.z;
        return *this;
    }

    inline Quaternion Quaternion::operator*=(float s)
    {
        n *= s;
        v.x *= s;
        v.y *= s;
        v.z *= s;
        return *this;
    }

    inline Quaternion Quaternion::operator/=(float s)
    {
        n /= s;
        v.x /= s;
        v.y /= s;
        v.z /= s;
        return *this;
    }

    inline Quaternion Quaternion::operator~(void) const
    {
        return Quaternion(n,
            -v.x,
            -v.y,
            -v.z);
    }

    inline Quaternion operator+(Quaternion q1, Quaternion q2)
    {
        return Quaternion(q1.n + q2.n,
            q1.v.x + q2.v.x,
            q1.v.y + q2.v.y,
            q1.v.z + q2.v.z);
    }

    inline Quaternion operator-(Quaternion q1, Quaternion q2)
    {
        return Quaternion(q1.n - q2.n,
            q1.v.x - q2.v.x,
            q1.v.y - q2.v.y,
            q1.v.z - q2.v.z);
    }

    inline Quaternion operator*(Quaternion q1, Quaternion q2)
    {
        return Quaternion(q1.n * q2.n - q1.v.x * q2.v.x
            - q1.v.y * q2.v.y - q1.v.z * q2.v.z,
            q1.n * q2.v.x + q1.v.x * q2.n
            + q1.v.y * q2.v.z - q1.v.z * q2.v.y,
            q1.n * q2.v.y + q1.v.y * q2.n
            + q1.v.z * q2.v.x - q1.v.x * q2.v.z,
            q1.n * q2.v.z + q1.v.z * q2.n
            + q1.v.x * q2.v.y - q1.v.y * q2.v.x);
    }

    inline Quaternion operator*(Quaternion q, float s)
    {
        return Quaternion(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
    }

    inline Quaternion operator*(float s, Quaternion q)
    {
        return Quaternion(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
    }

    inline Quaternion operator*(Quaternion q, Vector3 v)
    {
        return Quaternion(-(q.v.x * v.x + q.v.y * v.y + q.v.z * v.z),
            q.n * v.x + q.v.y * v.z - q.v.z * v.y,
            q.n * v.y + q.v.z * v.x - q.v.x * v.z,
            q.n * v.z + q.v.x * v.y - q.v.y * v.x);
    }

    inline Quaternion operator*(Vector3 v, Quaternion q)
    {
        return Quaternion(-(q.v.x * v.x + q.v.y * v.y + q.v.z * v.z),
            q.n * v.x + q.v.z * v.y - q.v.y * v.z,
            q.n * v.y + q.v.x * v.z - q.v.z * v.x,
            q.n * v.z + q.v.y * v.x - q.v.x * v.y);
    }

    inline Quaternion operator/(Quaternion q, float s)
    {
        return Quaternion(q.n / s, q.v.x / s, q.v.y / s, q.v.z / s);
    }

    inline float QGetAngle(Quaternion q)
    {
        return (float)(2 * acos(q.n));
    }

    inline Vector3 QGetAxis(Quaternion q)
    {
        Vector3 v;
        float m;

        v = q.GetVector();
        m = v.Magnitude();

        if (m <= 0)
            return Vector3();
        else
            return v / m;
    }

    inline Quaternion QRotate(Quaternion q1, Quaternion q2)
    {
        return q1 * q2 * (~q1);
    }

    inline Vector3 QVRotate(Quaternion q, Vector3 v)
    {
        Quaternion t;
        t = q * v * (~q);
        return t.GetVector();
    }

    inline float DegreesToRadians(float deg)
    {
        return deg * M_PI / 180.0f;
    }

    inline float RadiansToDegrees(float rad)
    {
        return rad * 180.0f / M_PI;
    }

    inline Quaternion MakeQFromEulerAngles(float x, float y, float z)
    {
        Quaternion     q;
        double     roll = DegreesToRadians(x);
        double     pitch = DegreesToRadians(y);
        double     yaw = DegreesToRadians(z);

        double     cyaw, cpitch, croll, syaw, spitch, sroll;
        double     cyawcpitch, syawspitch, cyawspitch, syawcpitch;

        croll = cos(0.5f * roll);
        sroll = sin(0.5f * roll);
        cyaw = cos(0.5f * yaw);
        syaw = sin(0.5f * yaw);
        cpitch = cos(0.5f * pitch);
        spitch = sin(0.5f * pitch);

        q.n = (float)(croll * cpitch * cyaw + sroll * spitch * syaw);
        q.v.x = (float)(sroll * cpitch * cyaw - croll * spitch * syaw);
        q.v.y = (float)(croll * spitch * cyaw + sroll * cpitch * syaw);
        q.v.z = (float)(croll * cpitch * syaw - sroll * spitch * cyaw);

        return q;
    }

    inline Vector3 MakeEulerAnglesFromQ(Quaternion q)
    {
        //double     r11, r21, r31, r32, r33, r12, r13;
        //double     q00, q11, q22, q33;
        //double     tmp;
        //Vector3     u;

        //q00 = q.n * q.n;
        //q11 = q.v.x * q.v.x;
        //q22 = q.v.y * q.v.y;
        //q33 = q.v.z * q.v.z;

        //r11 = q00 + q11 - q22 - q33;
        //r21 = 2 * (q.v.x * q.v.y + q.n * q.v.z);
        //r31 = 2 * (q.v.x * q.v.z - q.n * q.v.y);
        //r32 = 2 * (q.v.y * q.v.z + q.n * q.v.x);
        //r33 = q00 - q11 - q22 + q33;

        //tmp = fabs(r31);
        //if (tmp > 0.999999)
        //{
        //    r12 = 2 * (q.v.x * q.v.y - q.n * q.v.z);
        //    r13 = 2 * (q.v.x * q.v.z + q.n * q.v.y);

        //    u.x = RadiansToDegrees(0.0f); //roll
        //    u.y = RadiansToDegrees((float)(-(M_PI / 2) * r31 / tmp));   // pitch
        //    u.z = RadiansToDegrees((float)atan2(-r12, -r31 * r13)); // yaw
        //    return u;
        //}

        //u.x = RadiansToDegrees((float)atan2(r32, r33)); // roll
        //u.y = RadiansToDegrees((float)asin(-r31));      // pitch
        //u.z = RadiansToDegrees((float)atan2(r21, r11)); // yaw
        //return u;

        Vector3 vec;

        double sinr_cosp = 2 * (q.n * q.v.x + q.v.y * q.v.z);
        double cosr_cosp = 1 - 2 * (q.v.x * q.v.x + q.v.y * q.v.y);
        vec.x = atan2(sinr_cosp, cosr_cosp);

        double sinp = sqrt(1 + 2 * (q.n * q.v.y - q.v.x * q.v.z));
        double cosp = sqrt(1 - 2 * (q.n * q.v.y - q.v.x * q.v.z));
        vec.y = 2 * atan2(sinp, cosp) - M_PI_2;

        double siny_cosp = 2 * (q.n * q.v.z + q.v.x * q.v.y);
        double cosy_cosp = 1 - 2 * (q.v.y * q.v.y + q.v.z * q.v.z);
        vec.z = atan2(siny_cosp, cosy_cosp);

        return vec;
    }
}
#endif// !H_QUATERNION
