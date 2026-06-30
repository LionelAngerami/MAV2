#pragma once

enum class BodyType
{
    Unknown,
    Projectile,
    Target,
    Ground
};

struct BodyData
{
    BodyType type;

    void* owner;
};