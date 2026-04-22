#include <iostream>
#include <windows.h>
#include <cstdlib>
#include "Card.h"
#include "Player.h"
#include "Enemy.h"
#include "Skill.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "===== 杀戮尖塔×三国杀 纯文字版 =====\n";
    Player player;
    Enemy enemy;

    while (true) {
        system("cls");
        // 死亡判断
        if (player.hp <= 0) {
            std::cout << "你战败了！游戏结束\n";
            Sleep(1000);
            break;
        }
        if (enemy.hp <= 0) {
            std::cout << "🎉 击败敌人！获得技能：\n";
            Sleep(1000);
            Skill s = Skill::getRandomSkill();
            player.addSkill(s);
            std::cout << "【" << s.name << "】" << s.desc << "\n";
            Sleep(1000);
            enemy = Enemy();
            system("pause");
            continue;
        }

        // 状态展示
        player.showStatus();
        enemy.showStatus();
        Sleep(1000);

        // 回合开始：重置杀次数+抽2张牌
        std::cout << "\n=== 回合开始 ===";
        Sleep(1000);
        player.resetShaCount();
        std::cout << "\n抽2张牌！\n";
        Sleep(1000);
        player.drawTwo();

        // 出牌阶段（可多次出牌）
        while (true) {
            player.showHand();
            std::cout << "\n选择操作：\n0-9 出牌 | -1 结束回合";
            if (player.hasSkill("苦肉")) std::cout << " | -2 使用苦肉";
            std::cout << "\n请输入：";
            int idx;
            std::cin >> idx;

            if (idx == -1) break; // 结束回合
            if (idx == -2) {
                player.useSkillKuRou();
                continue;
            }
            if (idx < 0 || idx >= static_cast<int>(player.hand.size())) {
                std::cout << "输入无效！\n";
                continue;
            }

            Card c = player.hand[idx];
            // 出杀限制
            if (c.type == CardType::SHA && player.current_sha_used >= player.max_sha_per_turn) {
                std::cout << "本回合出杀次数已用完！\n";
                continue;
            }

            // 打出卡牌
            player.deck.discardCard(c);
            player.hand.erase(player.hand.begin() + idx);

            // 卡牌效果
            if (c.type == CardType::SHA) {
                if (player.hasSkill("龙胆")) {
                    // 杀当闪
                    player.shan_defense++;
                    std::cout << "使用【杀】（龙胆），获得1次攻击抵挡！\n";
                    Sleep(1000);
                } else {
                    // 正常杀
                    player.current_sha_used++;
                    std::cout << "\n你对敌人使用【杀】！\n";
                    Sleep(1000);
                    bool forceHit = false;
                    if (enemy.shan_defense > 0 && player.hasSkill("铁骑")) {
                        if (rand() % 2 == 0) {
                            forceHit = true;
                            std::cout << "铁骑发动！杀强制命中！\n";
                            Sleep(1000);
                        }
                    }
                    if (enemy.shan_defense > 0 && !forceHit) {
                        enemy.shan_defense--;
                        std::cout << "敌人用闪抵挡了这次攻击！\n";
                        Sleep(1000);
                    } else {
                        enemy.takeDamage(1);
                    }
                }
            } else if (c.type == CardType::SHAN) {
                if (player.hasSkill("龙胆")) {
                    // 闪当杀
                    std::cout << "\n你对敌人使用【闪】（龙胆）！\n";
                    Sleep(1000);
                    if (enemy.shan_defense > 0) {
                        enemy.shan_defense--;
                        std::cout << "敌人用闪抵挡了这次攻击！\n";
                        Sleep(1000);
                    } else {
                        enemy.takeDamage(1);
                    }
                } else {
                    player.shan_defense++;
                    std::cout << "使用【闪】，获得1次攻击抵挡！\n";
                    Sleep(1000);
                }
            } else if (c.type == CardType::TAO) {
                player.hp += 1;
                if (player.hp > player.max_hp) player.hp = player.max_hp;
                std::cout << "使用【桃】，恢复1点血量！\n";
                Sleep(1000);
            }

            if (enemy.hp <= 0) {
                break;
            }
        }

        if (enemy.hp <= 0) {
            std::cout << "🎉 击败敌人！获得技能：\n";
            Sleep(1000);
            Skill s = Skill::getRandomSkill();
            player.addSkill(s);
            std::cout << "【" << s.name << "】" << s.desc << "\n";
            Sleep(1000);
            enemy = Enemy();
            system("pause");
            continue;
        }

        // 出牌阶段结束，弃牌阶段
        player.discardExcessCards();

        // 敌人回合
        if (enemy.hp > 0) {
            std::cout << "\n=== 敌人回合 ===";
            Sleep(1000);
            enemy.shan_defense = 0; // 重置闪防御
            enemy.drawOne();
            enemy.playCards();
            enemy.attack(player);
            enemy.discardExcessCards();
        }

        system("pause");
    }
    return 0;
}