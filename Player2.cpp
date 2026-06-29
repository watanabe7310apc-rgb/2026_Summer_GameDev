#include <DxLib.h>
#include "Player2.h"


Player2::Player2()
{
    // 座標
    pos.x = 960;
    pos.y = 420;

    image = -1;

    isRight = true;

    oldMouse = false;

    shotCoolTime = 0;

    shotSE = LoadSoundMem("Image/Sound/Arrow.mp3");
}

void Player2::Update()
{
    // 移動しない

    // マウスの方向を向く
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    if (mouseX < pos.x)
    {
        isRight = false;
    }
    else
    {
        isRight = true;
    }

    bool nowMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

    //発射間隔
    if (shotCoolTime > 0)
    {
        shotCoolTime--;
    }

    // クリックした瞬間だけ発射
    if (nowMouse && !oldMouse && shotCoolTime == 0)
    {
        Vector2 target(mouseX, mouseY);

        for (int i = 0; i < ARROW_MAX; i++)
        {
            if (!arrow[i].isAlive)
            {
                arrow[i].Shot(pos, target);

                PlaySoundMem(shotSE, DX_PLAYTYPE_BACK);

                shotCoolTime = SHOT_INTERVAL;

                break;
            }
        }
    }

    // マウス状態を保存
    oldMouse = nowMouse;

    // 全ての矢を更新
    for (int i = 0; i < ARROW_MAX; i++)
    {
        arrow[i].Update();
    }
}

void Player2::Draw()
{
    // 仮のプレイヤー2（青い四角）
    DrawBox(
        pos.x - 25,
        pos.y - 25,
        pos.x + 40,
        pos.y + 60,
        GetColor(0, 0, 255),
        TRUE);

    if (isRight)
    {
        DrawGraph(pos.x, pos.y, image, TRUE);
    }
    else
    {
        DrawRotaGraph(pos.x, pos.y, 1.0, 0.0, image, TRUE, TRUE);

    }

    for (int i = 0; i < ARROW_MAX; i++)
    {
        arrow[i].Draw();
    }
}

void Player2::Release()
{
    DeleteSoundMem(shotSE);
}