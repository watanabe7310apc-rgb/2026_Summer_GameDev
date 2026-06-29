#include <DxLib.h>
#include <math.h>
#include "Arrow.h"

Arrow::Arrow()
{
    isAlive = false;
    image = LoadGraph("Image/Archer/Arrow.png");
}

void Arrow::Shot(Vector2 start, Vector2 target)
{
    pos = start;

    dir.x = (float)(target.x - start.x);
    dir.y = (float)(target.y - start.y);

    float len = sqrt(dir.x * dir.x + dir.y * dir.y);

    if (len == 0.0f) return;

    dir.x /= len;
    dir.y /= len;

    isAlive = true;
}

void Arrow::Update()
{
    if (!isAlive) return;

    float speed = 15;

    pos.x += (int)(dir.x * speed);
    pos.y += (int)(dir.y * speed);

    if (pos.x < 0 || pos.x > 1920 ||
        pos.y < 0 || pos.y > 1080)
    {
        isAlive = false;
    }
}

void Arrow::Draw()
{
    if (!isAlive) return;

    // ”ò‚Ô•ûŒü‚ÌŠp“x‚ðŒvŽZ
    float angle = atan2(dir.y, dir.x);

    DrawRotaGraph(
        pos.x,
        pos.y,
        1.5,
        angle,
        image,
        TRUE
    );
}