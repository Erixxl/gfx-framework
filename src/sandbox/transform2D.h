#pragma once

#include <cmath>
#include <string>

#include "utils/glm_utils.h"

namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        glm::mat3 result = {
            1, 0, translateX,
            0, 1, translateY,
            0, 0,          1
        };

        return glm::transpose(result);
    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        glm::mat3 result = {
            scaleX,      0, 0,
                 0, scaleY, 0,
                 0,      0, 1
        };

        return glm::transpose(result);
    }

    // Scale from point matrix
    inline glm::mat3 ScaleFrom(float coordX, float coordY, float scaleX, float scaleY)
    {
        return Translate(coordX, coordY)
            * Scale(scaleX, scaleY)
            * Translate(-coordX, -coordY);
    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        glm::mat3 result = {
            std::cos(radians), std::sin(-radians), 0,
            std::sin(radians), std::cos(radians),  0,
                            0,                 0,  1
        };

        return glm::transpose(result);
    }

    // Rotate from point matrix
    inline glm::mat3 RotateFrom(float coordX, float coordY, float radians)
    {
        return Translate(coordX, coordY)
            * Rotate(radians)
            * Translate(-coordX, -coordY);
    }

    // Mirror x-axis matrix
    inline glm::mat3 MirrorX()
    {
        // Same as scaling y with -1
        return glm::mat3(
            1,  0, 0,
            0, -1, 0,
            0,  0, 1
        );
    }

    // Mirror y-axis matrix
    inline glm::mat3 MirrorY()
    {
        // Same as scaling x with -1
        return glm::mat3(
            -1, 0, 0,
            0,  1, 0,
            0,  0, 1
        );
    }

    // Mirror origin matrix
    inline glm::mat3 MirrorOrig()
    {
        // Same as scaling x and y with -1
        return glm::mat3(
            -1,  0, 0,
             0, -1, 0,
             0,  0, 1
        );
    }

    // Mirror matrix
    inline glm::mat3 MirrorSlope(float slope, float intercept)
    {
        // Translate until origin sits on mirror axis
        if (intercept != 0)
        {
            if (slope == INFINITY || slope == -INFINITY)
            {
                return Translate(intercept, 0)
					* MirrorSlope(slope, 0)
					* Translate(-intercept, 0);
            }

            return Translate(0, intercept)
                * MirrorSlope(slope, 0)
                * Translate(0, -intercept);
        }

        if (slope == INFINITY || slope == -INFINITY)
        {
            // Y-axis mirroring
            return MirrorY();
        }

        if (slope == 0)
        {
            // X-axis mirroring
            return MirrorX();
        }

        // First align with x-axis
        float angle = std::atan(slope);

        return Rotate(angle)
            * MirrorX()
            * Rotate(-angle);
    }

    inline glm::mat3 MirrorAngle(float radians, float intercept)
    {
        // Translate until origin sits on mirror axis
        if (intercept != 0)
        {
            if (radians == AI_MATH_PI || radians == -AI_MATH_PI)
            {
                return Translate(intercept, 0)
					* MirrorAngle(radians, 0)
					* Translate(-intercept, 0);
            }

            return Translate(0, intercept)
                * MirrorAngle(radians, 0)
                * Translate(0, -intercept);
        }

        if (radians == AI_MATH_PI || radians == -AI_MATH_PI)
        {
            // Y-axis mirroring
            return MirrorY();
        }

        if (radians == 0)
        {
            // X-axis mirroring
            return MirrorX();
        }

        // First align with x-axis
        return Rotate(radians)
            * MirrorX()
            * Rotate(-radians);
    }

    // Shear matrix
    inline glm::mat3 Shear(float shearX, float shearY)
    {
        glm::mat3 result = {
                 1, shearX, 0,
            shearY,      1, 0,
                 0,      0, 1
        };

        return glm::transpose(result);
    }

    // Shear from point matrix
    inline glm::mat3 ShearFrom(float coordX, float coordY, float shearX, float shearY)
    {
        return Translate(coordX, coordY)
            * Shear(shearX, shearY)
            * Translate(-coordX, -coordY);
    }

}   // namespace transform2D


