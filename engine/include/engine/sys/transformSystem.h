#pragma once

#include <engine/sys/_system.h>
#include <engine/common.h>
#include <engine/comp/transform.h>
#include <engine/comp/sprite.h>
#include <engine/comp/collider.h>

/**
 * @brief A system that handles transformations of points, sprites, and colliders.
 */
class TransformSystem : public System {
public:
    /**
     * @brief Translates a point by the given x and y offsets.
     *
     * @param point The point to translate.
     * @param x The offset along the x-axis.
     * @param y The offset along the y-axis.
     */
    static void TranslatePoint(Point& point, float x, float y);

    /**
     * @brief Scales a point by the given x and y scale factors.
     *
     * @param point The point to scale.
     * @param x_scale The scale factor along the x-axis.
     * @param y_scale The scale factor along the y-axis.
     */
    static void ScalePoint(Point& point, float x_scale, float y_scale);

    /**
     * @brief Rotates a point by the given angle.
     *
     * @param point The point to rotate.
     * @param angle The angle to rotate the point, in degrees.
     */
    static void RotatePoint(Point& point, float angle);

    /**
     * @brief Applies a transformation to a point.
     *
     * @param point The point to transform.
     * @param transform The transformation to apply.
     */
    static void ApplyTransformation(Point& point, Transform& transform);

    /**
     * @brief Transforms a sprite by applying a transformation.
     *
     * @param sprite The sprite to transform.
     * @param transform The transformation to apply.
     * @return The transformed sprite.
     */
    static Sprite TransformSprite(Sprite& sprite, Transform& transform);

    /**
     * @brief Transforms a collider by applying a transformation.
     *
     * @param collider The collider to transform.
     * @param transform The transformation to apply.
     * @return The transformed collider.
     */
    static Collider TransformCollider(Collider& collider, Transform& transform);
};